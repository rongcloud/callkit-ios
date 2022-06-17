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

//RCCallKit_Delete_Start
#if PUBLIC
#else
#import <CallKit/CallKit.h>
#endif
//RCCallKit_Delete_end

#import <AVFoundation/AVFoundation.h>
#import "RCCallKitUtility.h"

#define RCCXCallLocalizedName @"RongCloud"

//RCCallKit_Delete_Start
#if PUBLIC
//RCCallKit_Delete_end
@interface RCCXCall ()
@property (nonatomic, strong) NSUUID *currentUUID;
@end
//RCCallKit_Delete_Start
#else
@interface RCCXCall () <CXProviderDelegate>
@property (nonatomic, strong) CXProvider *provider;
@property (nonatomic, strong) NSUUID *currentUUID;
@property (nonatomic, strong) CXCallController *controller;
@property (nonatomic, assign) BOOL connecting;
@end
#endif
//RCCallKit_Delete_end

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
            pCall.acceptedFromCallKit = NO;
//RCCallKit_Delete_Start
#if PUBLIC
#else
            [[NSNotificationCenter defaultCenter] addObserver:pCall selector:@selector(didCreateNewSession:) name:RCCallNewSessionCreationNotification object:nil];
#endif
            //RCCallKit_Delete_end
        }
    });
    return pCall;
}

- (void)startCallId:(NSString *)callId userId:(NSString *)userId {
    NSUUID *uuid = [[NSUUID alloc] initWithUUIDString:callId];
    self.currentUUID = uuid;
//RCCallKit_Delete_Start
#if PUBLIC
#else
    CXHandle *handle = [[CXHandle alloc] initWithType:CXHandleTypeGeneric value:userId];
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
        if (str.length > 0) {
            str = [str substringToIndex:str.length - 1];
        }
        startAction.contactIdentifier = str;
    }
    CXTransaction *transaction = [[CXTransaction alloc] init];
    [transaction addAction:startAction];
    [self.controller requestTransaction:transaction
                             completion:^(NSError *_Nullable error){
                             }];
    [self.provider reportOutgoingCallWithUUID:uuid startedConnectingAtDate:nil];
#endif
    //RCCallKit_Delete_end
}

- (void)reportOutgoingCallConnected {
//RCCallKit_Delete_Start
#if PUBLIC
#else
    [self.provider reportOutgoingCallWithUUID:self.currentUUID connectedAtDate:nil];
#endif
    //RCCallKit_Delete_end
}

- (void)reportIncomingCallWithCallId:(NSString *)callId
                             inviter:(NSString *)inviterId
                          userIdList:(NSArray<NSString *> *)userIdList
                             isVideo:(BOOL)isVideo {
//RCCallKit_Delete_Start
#if PUBLIC
#else
    if (self.currentUUID) {
        return;
    }
    NSUUID *uuid = [[NSUUID alloc] initWithUUIDString:callId];
    self.currentUUID = uuid;
    CXCallUpdate *update = [[CXCallUpdate alloc] init];
    update.supportsHolding = NO;
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
                                      completion:^(NSError *_Nullable error) {
                                          if (error == nil) {
                                          }
                                      }];
#endif
    //RCCallKit_Delete_end
}

- (void)answerCXCall {
//RCCallKit_Delete_Start
#if PUBLIC
    //RCCallKit_Delete_end
    self.currentUUID = nil;
//RCCallKit_Delete_Start
#else
    if (_currentUUID) {
        CXAnswerCallAction *action = [[CXAnswerCallAction alloc] initWithCallUUID:_currentUUID];
        CXTransaction *transaction = [[CXTransaction alloc] init];
        [transaction addAction:action];
        [self.controller requestTransaction:transaction
                                 completion:^(NSError *_Nullable error){
                                 }];
    }
#endif
    //RCCallKit_Delete_end
}

- (void)endCXCall {
//RCCallKit_Delete_Start
#if PUBLIC
    //RCCallKit_Delete_end
    self.currentUUID = nil;
//RCCallKit_Delete_Start
#else
    if (_currentUUID) {
        CXEndCallAction *endAction = [[CXEndCallAction alloc] initWithCallUUID:_currentUUID];
        CXTransaction *transaction = [[CXTransaction alloc] init];
        [transaction addAction:endAction];
        [self.controller requestTransaction:transaction
                                 completion:^(NSError *_Nullable error){
                                 }];
    }
#endif
    //RCCallKit_Delete_end
}

- (void)hangupIfNeedWithUUID:(NSString *)UUID {
    if (UUID.length == 0) {
        return;
    }
    if (![UUID isEqualToString:self.currentUUID.UUIDString]) {
        [[RCCall sharedRCCall].currentCallSession hangup];
    }
}

//RCCallKit_Delete_Start
#if PUBLIC
#else
#pragma mark - CXProviderDelegate
- (void)provider:(CXProvider *)provider performAnswerCallAction:(CXAnswerCallAction *)action {
    if ([self.currentUUID.UUIDString isEqualToString:action.callUUID.UUIDString]) {
        if ([RCCall sharedRCCall].currentCallSession) {
            [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayAndRecord error:nil];
            [[AVAudioSession sharedInstance] setMode:AVAudioSessionModeVoiceChat error:nil];
            self.acceptedFromCallKit = YES;
            [[RCCall sharedRCCall].currentCallSession accept:[RCCall sharedRCCall].currentCallSession.mediaType];
        } else {
            // wait a moment for a session creation;
            self.connecting = YES;
        }
        [action fulfill];
    } else {
        [action fail];
    }
}

- (void)didCreateNewSession:(NSNotification *)notification {
    RCCallSession *session = notification.object;
    if (self.connecting) {
        [[RCCall sharedRCCall].currentCallSession accept:[RCCall sharedRCCall].currentCallSession.mediaType];
    }
    self.connecting = NO;
}

- (void)provider:(CXProvider *)provider performEndCallAction:(CXEndCallAction *)action {
    if ([self.currentUUID.UUIDString isEqualToString:action.callUUID.UUIDString]) {
        [[RCCall sharedRCCall].currentCallSession hangup];
        _currentUUID = nil;
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

- (void)provider:(CXProvider *)provider performSetMutedCallAction:(CXSetMutedCallAction *)action {
    if ([self.currentUUID.UUIDString isEqualToString:action.callUUID.UUIDString]) {
        [[RCCall sharedRCCall].currentCallSession setMuted:action.muted];
    }
    [action fulfill];
}

- (void)provider:(CXProvider *)provider didActivateAudioSession:(AVAudioSession *)audioSession {
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

#pragma mark - Getter
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
//RCCallKit_Delete_end

@end
