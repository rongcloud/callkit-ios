//
//  RCCXCall.m
//  RongCallKit
//
//  Created by LiFei on 2018/1/17.
//  Copyright © 2018年 Rong Cloud. All rights reserved.
//

#import "RCCXCall.h"
#import "RCCall.h"
#import "RCUserInfoCacheManager.h"

#ifdef PUBLIC
#else
#import <CallKit/CallKit.h>
#endif

#import <AVFoundation/AVFoundation.h>
#import "RCCallKitUtility.h"

#define RCCXCallLocalizedName @"RongCloud"

#ifdef PUBLIC
@interface RCCXCall()
@end
#else
@interface RCCXCall() <CXProviderDelegate>
@property(nonatomic, strong) CXProvider *provider;
@property(nonatomic, strong) NSUUID *currentUUID;
@property(nonatomic, strong) CXCallController *controller;
@end
#endif


@implementation RCCXCall

+ (instancetype)sharedInstance {
    static RCCXCall *pCall;
    static dispatch_once_t onceToken;
    if (([UIDevice currentDevice].systemVersion.floatValue < 10.0)) {
        return nil;
    }
    dispatch_once(&onceToken, ^{
        if (pCall == nil) {
            pCall = [[RCCXCall alloc] init];
        }
    });
    return pCall;
}

- (void)startCall:(NSString *)userId {
#ifdef PUBLIC
#else
    NSUUID *uuid = [NSUUID UUID];
    self.currentUUID = uuid;
    CXHandle *handle = [[CXHandle alloc] initWithType:CXHandleTypeGeneric value:[userId copy]];
    CXStartCallAction *startAction = [[CXStartCallAction alloc] initWithCallUUID:uuid handle:handle];
    NSArray *array = [userId componentsSeparatedByString:@":::"];
    if (array.count == 1) {
        startAction.contactIdentifier = [[RCUserInfoCacheManager sharedManager] getUserInfo:userId].name;
    } else {
        NSString *str = @"";
        for (NSString *uId in array) {
            NSString *name = [[RCUserInfoCacheManager sharedManager] getUserInfo:uId].name;
            if (name.length > 0) {
                str = [str stringByAppendingFormat:@"%@、", name];
            }
        }
        str = [str substringToIndex:str.length - 1];
        startAction.contactIdentifier = str;
    }
    CXTransaction *transaction = [[CXTransaction alloc] init];
    [transaction addAction:startAction];
    [self.controller requestTransaction:transaction completion:^(NSError * _Nullable error) {
    }];
    [self.provider reportOutgoingCallWithUUID:uuid startedConnectingAtDate:nil];
#endif
}

- (void)reportOutgoingCallConnected {
#ifdef PUBLIC
#else
    [self.provider reportOutgoingCallWithUUID:self.currentUUID connectedAtDate:nil];
#endif
}

- (void)reportIncomingCallWithInviter:(NSString *)inviterId
                           userIdList:(NSArray<NSString *> *)userIdList
                              isVideo:(BOOL)isVideo {
#ifdef PUBLIC
#else
    [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayAndRecord error:nil];
    NSUUID *uuid = [[NSUUID alloc] init];
    self.currentUUID = uuid;
    CXCallUpdate *update = [[CXCallUpdate alloc] init];
    NSString *localizedCallerName = [[RCUserInfoCacheManager sharedManager] getUserInfo:inviterId].name;
    NSString *handleValue = inviterId;
    for (NSString *userId in userIdList) {
        if ([userId isEqualToString:inviterId]) {
            break;
        }
        NSString *name = [[RCUserInfoCacheManager sharedManager] getUserInfo:userId].name;
        if (name.length > 0) {
            localizedCallerName = [localizedCallerName stringByAppendingFormat:@"、%@", name];
        }
        handleValue = [handleValue stringByAppendingFormat:@":::%@", userId];
    }
    update.localizedCallerName = localizedCallerName;
    CXHandle *handle = [[CXHandle alloc] initWithType:CXHandleTypeGeneric value:handleValue];
    update.remoteHandle = handle;
    if (isVideo) {
        update.hasVideo = YES;
    }
    [self.provider reportNewIncomingCallWithUUID:uuid
                                          update:update
                                      completion:^(NSError * _Nullable error) {
                                          if (error == nil) {
                                          }
                                      }];
#endif
}

- (void)endCXCall {
#ifdef PUBLIC
#else
    if (self.currentUUID) {
        CXEndCallAction *endAction = [[CXEndCallAction alloc] initWithCallUUID:self.currentUUID];
        CXTransaction *transaction = [[CXTransaction alloc] init];
        [transaction addAction:endAction];
        [self.controller requestTransaction:transaction completion:^(NSError * _Nullable error) {
            self.currentUUID = nil;
        }];
    }
#endif
}

- (void)hangupIfNeedWithUUID:(NSString *)UUID {
#ifdef PUBLIC
#else
    if (UUID.length == 0) {
        return;
    }
    if (![UUID isEqualToString:self.currentUUID.UUIDString]) {
        [[RCCall sharedRCCall].currentCallSession hangup];
    }
#endif
}

#ifdef PUBLIC
#else
- (void)provider:(CXProvider *)provider performAnswerCallAction:(CXAnswerCallAction *)action {
    if ([self.currentUUID.UUIDString isEqualToString:action.callUUID.UUIDString]) {
        [[RCCall sharedRCCall].currentCallSession accept:[RCCall sharedRCCall].currentCallSession.mediaType];
    }
    [action fulfill];
}

- (void)provider:(CXProvider *)provider performEndCallAction:(CXEndCallAction *)action {
    if ([self.currentUUID.UUIDString isEqualToString:action.callUUID.UUIDString]) {
        [[RCCall sharedRCCall].currentCallSession hangup];
        self.currentUUID = nil;
    }
    [action fulfill];
}

- (void)provider:(CXProvider *)provider performStartCallAction:(CXStartCallAction *)action {
    //startCall的时候设置action的contactIdentifier并不会更新通话记录中的名字，这段代码是为了更新通话记录
    CXCallUpdate *update = [[CXCallUpdate alloc] init];
    update.remoteHandle = action.handle;
    update.localizedCallerName = action.contactIdentifier;
    [self.provider reportCallWithUUID:action.callUUID updated:update];
    [action fulfill];
}

- (void)providerDidReset:(CXProvider *)provider {
    //info.plist里面没有打开后台VoIP模式的情况下，在startCall之后会走这个回调，导致呼出的电话被hangup
//    if (self.currentUUID) {
//        self.currentUUID = nil;
//        if ([RCCall sharedRCCall].currentCallSession) {
//            [[RCCall sharedRCCall].currentCallSession hangup];
//        }
//    }
}

- (CXProvider *)provider {
    if (!_provider) {
        NSString *name = [RCCall sharedRCCall].appLocalizedName;
        if (name.length == 0) {
            name = RCCXCallLocalizedName;
        }
        CXProviderConfiguration *config = [[CXProviderConfiguration alloc] initWithLocalizedName:name];
        config.supportedHandleTypes = [NSSet setWithObject:@(CXHandleTypeGeneric)];
        config.maximumCallGroups = 1;
        config.maximumCallsPerCallGroup = 1;
        
        UIImage *img = [RCCallKitUtility imageFromVoIPBundle:@"voip/callkit_app_icon.png"];
        NSData *data = UIImagePNGRepresentation(img);
        config.iconTemplateImageData = data;
        _provider = [[CXProvider alloc] initWithConfiguration:config];
        [_provider setDelegate:self queue:nil];
    }
    return _provider;
}

- (CXCallController *)controller {
    if (!_controller) {
        _controller = [[CXCallController alloc] init];
    }
    return _controller;
}
#endif

@end
