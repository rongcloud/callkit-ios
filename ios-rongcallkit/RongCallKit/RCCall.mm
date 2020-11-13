//
//  RCCall.mm
//  RongCallKit
//
//  Created by 岑裕 on 16/3/11.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCCall.h"
#import "RCCallAudioMultiCallViewController.h"
#import "RCCallBaseViewController.h"
#import "RCCallDetailMessageCell.h"
#import "RCCallKitUtility.h"
#import "RCCallSelectMemberViewController.h"
#import "RCCallSingleCallViewController.h"
#import "RCCallTipMessageCell.h"
#import "RCCallVideoMultiCallViewController.h"
#import "RCUserInfoCacheManager.h"
#import "RCCXCall.h"
#import <RongIMKit/RongIMKit.h>
#import <AVFoundation/AVFoundation.h>

#if __IPHONE_10_0
#import <UserNotifications/UserNotifications.h>
#endif

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#define AlertWithoutConfirm 1000
#define AlertWithConfirm 1001

@interface RCCall () <RCCallReceiveDelegate>

@property(nonatomic, strong) NSMutableDictionary *alertInfoDic;
@property(nonatomic, strong) AVAudioPlayer *audioPlayer;
@property(nonatomic, strong) NSMutableArray *callWindows;
@property(nonatomic, strong) NSTimer *timer;
@property(nonatomic, strong) NSMutableDictionary *locationNotificationMap;

@end

@implementation RCCall

+ (instancetype)sharedRCCall {
    static RCCall *pRongVoIP;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        if (pRongVoIP == nil) {
            pRongVoIP = [[RCCall alloc] init];
            [[RCCallClient sharedRCCallClient] setDelegate:pRongVoIP];
            pRongVoIP.maxMultiAudioCallUserNumber = 20;
            pRongVoIP.maxMultiVideoCallUserNumber = 7;
            pRongVoIP.canIncomingCall = YES;
            pRongVoIP.callWindows = [[NSMutableArray alloc] init];
            pRongVoIP.locationNotificationMap = [[NSMutableDictionary alloc] init];
            [pRongVoIP registerNotification];
        }
    });
    return pRongVoIP;
}

- (void)registerNotification {
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(appDidBecomeActive)
                                                 name:UIApplicationDidBecomeActiveNotification
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(appDidResignActive)
                                                 name:UIApplicationWillResignActiveNotification
                                               object:nil];
}

- (void)appDidBecomeActive {
    [self stopReceiveCallVibrate];
}

- (void)appDidResignActive {
    [self stopReceiveCallVibrate];
}

- (BOOL)isAudioCallEnabled:(RCConversationType)conversationType {
    return [[RCCallClient sharedRCCallClient] isAudioCallEnabled:conversationType];
}

- (BOOL)isVideoCallEnabled:(RCConversationType)conversationType {
    return [[RCCallClient sharedRCCallClient] isVideoCallEnabled:conversationType];
}

- (void)startSingleCall:(NSString *)targetId mediaType:(RCCallMediaType)mediaType {
    if ([self preCheckForStartCall:mediaType]) {
        [self checkSystemPermission:mediaType
                            success:^{
                                [self startSingleCallViewController:targetId mediaType:mediaType];
                            }];
    }
}

- (void)startSingleCallViewController:(NSString *)targetId mediaType:(RCCallMediaType)mediaType {
    RCCallSingleCallViewController *singleCallViewController =
        [[RCCallSingleCallViewController alloc] initWithOutgoingCall:targetId mediaType:mediaType];

    [self presentCallViewController:singleCallViewController];
}

- (void)startMultiCall:(RCConversationType)conversationType
              targetId:(NSString *)targetId
             mediaType:(RCCallMediaType)mediaType {
    if ([self preCheckForStartCall:mediaType]) {
        [self checkSystemPermission:mediaType
                            success:^{
                                [self startSelectMemberViewContoller:conversationType
                                                            targetId:targetId
                                                           mediaType:mediaType];
                            }];
    }
}

- (void)startSelectMemberViewContoller:(RCConversationType)conversationType
                              targetId:(NSString *)targetId
                             mediaType:(RCCallMediaType)mediaType {
    if (conversationType == ConversationType_DISCUSSION || conversationType == ConversationType_GROUP) {
        __weak typeof(self) weakSelf = self;
        RCCallSelectMemberViewController *voipCallSelectViewController = [[RCCallSelectMemberViewController alloc]
            initWithConversationType:conversationType
                            targetId:targetId
                           mediaType:mediaType
                               exist:@[[RCIMClient sharedRCIMClient].currentUserInfo.userId]
                             success:^(NSArray *addUserIdList) {
                                 [weakSelf startMultiCallViewController:conversationType
                                                               targetId:targetId
                                                              mediaType:mediaType
                                                             userIdList:addUserIdList];
                             }];
        UINavigationController *rootVC = [[UINavigationController alloc] initWithRootViewController:voipCallSelectViewController];
        rootVC.modalPresentationStyle = UIModalPresentationFullScreen;
        [self presentCallViewController:rootVC];
    }
}

- (void)startMultiCallViewController:(RCConversationType)conversationType
                            targetId:(NSString *)targetId
                           mediaType:(RCCallMediaType)mediaType
                          userIdList:(NSArray *)userIdList {
    
    if ([self preCheckForStartCall:mediaType]) {
        [self checkSystemPermission:mediaType
                            success:^{
                                UIViewController* avCallVC = nil;
                                if (mediaType == RCCallMediaAudio) {
                                    avCallVC = [[RCCallAudioMultiCallViewController alloc]
                                                    initWithOutgoingCall:conversationType
                                                                targetId:targetId
                                                              userIdList:userIdList];
                                    
                                } else {
                                    avCallVC = [[RCCallVideoMultiCallViewController alloc]
                                                    initWithOutgoingCall:conversationType
                                                                targetId:targetId
                                                               mediaType:mediaType
                                                              userIdList:userIdList];
                                    
                                }
                                [self presentCallViewController:avCallVC];
                            }];
    }
}

- (void)checkSystemPermission:(RCCallMediaType)mediaType success:(void (^)(void))successBlock {
    if (mediaType == RCCallMediaVideo) {
        [self checkCapturePermission:^(BOOL granted) {
            if (granted) {
                [self checkRecordPermission:^() {
                    successBlock();
                }];
            }
        }];

    } else if (mediaType == RCCallMediaAudio) {
        [self checkRecordPermission:^() {
            successBlock();
        }];
    }
}

- (void)checkRecordPermission:(void (^)(void))successBlock {
    if ([[AVAudioSession sharedInstance] respondsToSelector:@selector(requestRecordPermission:)]) {
        [[AVAudioSession sharedInstance] requestRecordPermission:^(BOOL granted) {
            dispatch_async(dispatch_get_main_queue(), ^{
                if (granted) {
                    successBlock();
                } else {
                    [self
                        loadErrorAlertWithConfirm:NSLocalizedStringFromTable(@"AccessRightTitle", @"RongCloudKit", nil)
                                          message:NSLocalizedStringFromTable(@"speakerAccessRight", @"RongCloudKit",
                                                                             nil)];
                }
            });
        }];
    }
}

- (void)checkCapturePermission:(void (^)(BOOL granted))complete {
    AVAuthorizationStatus authStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];

    if (authStatus == AVAuthorizationStatusDenied || authStatus == AVAuthorizationStatusRestricted) {
        [self loadErrorAlertWithConfirm:NSLocalizedStringFromTable(@"AccessRightTitle", @"RongCloudKit", nil)
                                message:NSLocalizedStringFromTable(@"cameraAccessRight", @"RongCloudKit", nil)];
        complete(NO);
    } else if (authStatus == AVAuthorizationStatusNotDetermined) {
        [AVCaptureDevice
            requestAccessForMediaType:AVMediaTypeVideo
                    completionHandler:^(BOOL granted) {
                        if (!granted) {
                            [self loadErrorAlertWithConfirm:NSLocalizedStringFromTable(@"AccessRightTitle",
                                                                                       @"RongCloudKit", nil)
                                                    message:NSLocalizedStringFromTable(@"cameraAccessRight",
                                                                                       @"RongCloudKit", nil)];
                        }
                        complete(granted);
                    }];
    } else {
        complete(YES);
    }
}

- (BOOL)preCheckForStartCall:(RCCallMediaType)mediaType {
    RCCallSession *currentCallSession = [RCCall sharedRCCall].currentCallSession;
    if (currentCallSession && currentCallSession.mediaType == RCCallMediaAudio) {
        [self loadErrorAlertWithoutConfirm:NSLocalizedStringFromTable(@"VoIPAudioCallExistedWarning", @"RongCloudKit",
                                                                      nil)];
        return NO;
    } else if (currentCallSession && currentCallSession.mediaType == RCCallMediaVideo) {
        [self loadErrorAlertWithoutConfirm:NSLocalizedStringFromTable(@"VoIPVideoCallExistedWarning", @"RongCloudKit",
                                                                      nil)];
        return NO;
    } else {
        return YES;
    }
}

- (void)presentCallViewController:(UIViewController *)viewController {
    [[[UIApplication sharedApplication] keyWindow] endEditing:YES];
    UIWindow *activityWindow = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    activityWindow.windowLevel = UIWindowLevelNormal;
    activityWindow.rootViewController = viewController;
    
    NSInteger checker = [RCCallKitUtility compareVersion:[UIDevice currentDevice].systemVersion toVersion:@"13.0"];
    if (checker >= 0) {
#ifdef __IPHONE_13_0
        [activityWindow setWindowScene:[UIApplication sharedApplication].keyWindow.windowScene];
#endif
    }
    
    [activityWindow makeKeyAndVisible];
    CATransition *animation = [CATransition animation];
    [animation setDuration:0.3];
    animation.type = kCATransitionMoveIn;     //可更改为其他方式
    animation.subtype = kCATransitionFromTop; //可更改为其他方式
    [[activityWindow layer] addAnimation:animation forKey:nil];
    [self.callWindows addObject:activityWindow];
}

- (void)dismissCallViewController:(UIViewController *)viewController {

    [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleDefault];
    if ([viewController isKindOfClass:[RCCallBaseViewController class]]) {
        UIViewController *rootVC = viewController;
        while (rootVC.parentViewController) {
            rootVC = rootVC.parentViewController;
        }
        viewController = rootVC;
    }

    for (UIWindow *window in self.callWindows) {
        if (window.rootViewController == viewController) {
            [window resignKeyWindow];
            window.hidden = YES;
            [[UIApplication sharedApplication].delegate.window makeKeyWindow];
            [self.callWindows removeObject:window];
            break;
        }
    }
    [viewController dismissViewControllerAnimated:YES completion:nil];
}

- (RCCallSession *)currentCallSession {
    return [RCCallClient sharedRCCallClient].currentCallSession;
}

#pragma mark - receive call
- (void)didReceiveCall:(RCCallSession *)callSession {
    if (!self.canIncomingCall) {
        [callSession hangup];
        return;
    }
    
    if (!callSession.isMultiCall) {
        RCCallSingleCallViewController *singleCallViewController =
        [[RCCallSingleCallViewController alloc] initWithIncomingCall:callSession];
        
        [self presentCallViewController:singleCallViewController];
    } else {
        if (callSession.mediaType == RCCallMediaAudio) {
            RCCallAudioMultiCallViewController *multiCallViewController =
            [[RCCallAudioMultiCallViewController alloc] initWithIncomingCall:callSession];
            
            [self presentCallViewController:multiCallViewController];
        } else {
            RCCallVideoMultiCallViewController *multiCallViewController =
            [[RCCallVideoMultiCallViewController alloc] initWithIncomingCall:callSession];
            
            [self presentCallViewController:multiCallViewController];
        }
    }
}

-(void)didCancelCallRemoteNotification:(NSString *)callId
                         inviterUserId:(NSString *)inviterUserId
                             mediaType:(RCCallMediaType)mediaType
                            userIdList:(NSArray *)userIdList
                            pushConfig:(RCMessagePushConfig*) pushConfig
                        isRemoteCancel:(BOOL)isRemoteCancel {
    [self stopReceiveCallVibrate];
    
    [[RCCXCall sharedInstance] endCXCall];
    
    if (pushConfig && isRemoteCancel) {
        [self postLocalNotification:pushConfig userInfo:nil hasSound:NO ];
    }
}

- (void)didReceiveCallRemoteNotification:(NSString *)callId
                           inviterUserId:(NSString *)inviterUserId
                               mediaType:(RCCallMediaType)mediaType
                              userIdList:(NSArray *)userIdList
                                userDict:(NSDictionary *)userDict
                              isVoIPPush:(BOOL)isVoIPPush
                                 pushConfig:(RCMessagePushConfig *)pushConfig {
    if (!self.canIncomingCall) {
        return;
    }

    [self startReceiveCallVibrate];

    [self postLocalNotification:pushConfig userInfo:userDict hasSound:YES];
}

- (void)postLocalNotification:(RCMessagePushConfig *)pushConfig userInfo:(NSDictionary*)userInfo hasSound:(BOOL)hasSound{
    NSString* pushContent = NSLocalizedStringFromTable(@"receive_new_message", @"RongCloudKit", nil);
    NSString *title = @"";
    NSString* soundName = @"RongCloud.bundle/voip/voip_call.caf";
    
    if ([RCIMClient sharedRCIMClient].pushProfile.isShowPushContent || (pushConfig && pushConfig.forceShowDetailContent)) {
        if (pushConfig && pushConfig.pushTitle && pushConfig.pushTitle.length != 0) {
            title = pushConfig.pushTitle;
        }
        if (pushConfig && pushConfig.pushContent && pushConfig.pushContent.length != 0) {
            pushContent = pushConfig.pushContent;
        }
    }
    NSString *requestWithIdentifier = [NSUUID UUID].UUIDString;
    if (pushConfig && pushConfig.iOSConfig && pushConfig.iOSConfig.apnsCollapseId && pushConfig.iOSConfig.apnsCollapseId.length > 0) {
        requestWithIdentifier = pushConfig.iOSConfig.apnsCollapseId;
    }
    
    if(@available(iOS 10.0, *)){
        UNMutableNotificationContent *content = [[UNMutableNotificationContent alloc] init];
        content.title = title;
        content.body = pushContent;
        content.userInfo = userInfo;
        if(hasSound){
            content.sound = [UNNotificationSound soundNamed:soundName];
        }
        if (pushConfig && pushConfig.iOSConfig && pushConfig.iOSConfig.threadId) {
            content.threadIdentifier = pushConfig.iOSConfig.threadId;
        }
        [[UNUserNotificationCenter currentNotificationCenter] removeDeliveredNotificationsWithIdentifiers:@[requestWithIdentifier]];
        UNNotificationRequest *request = [UNNotificationRequest requestWithIdentifier:requestWithIdentifier content:content trigger:nil];
        [[UNUserNotificationCenter currentNotificationCenter] addNotificationRequest:request withCompletionHandler:^(NSError * _Nullable error) {}];
        
    }else{
        UILocalNotification *callNotification = [[UILocalNotification alloc] init];
        callNotification.alertAction = NSLocalizedStringFromTable(@"LocalNotificationShow", @"RongCloudKit", nil);
        
        if (@available(iOS 8.2, *)) {
            callNotification.alertTitle = title;
        }
        callNotification.alertBody = pushContent;
        callNotification.userInfo = userInfo;
        if (hasSound) {
            [callNotification setSoundName:soundName];
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            UILocalNotification *notification = [self.locationNotificationMap objectForKey:requestWithIdentifier];
            if (notification) {
                [[UIApplication sharedApplication] cancelLocalNotification:notification];
            }
            [self.locationNotificationMap setObject:callNotification forKey:requestWithIdentifier];
            [[UIApplication sharedApplication] presentLocalNotificationNow:callNotification];
        });

    }
}

#pragma mark - alert
- (void)loadErrorAlertWithoutConfirm:(NSString *)title {
    UIAlertView *alert =
        [[UIAlertView alloc] initWithTitle:title message:nil delegate:nil cancelButtonTitle:nil otherButtonTitles:nil];
    alert.tag = AlertWithoutConfirm;
    [NSTimer scheduledTimerWithTimeInterval:1.0f
                                     target:self
                                   selector:@selector(cancelAlert:)
                                   userInfo:alert
                                    repeats:NO];
    [alert show];
}

- (void)cancelAlert:(NSTimer *)scheduledTimer {
    UIAlertView *alert = (UIAlertView *)(scheduledTimer.userInfo);
    if (alert.tag == AlertWithoutConfirm) {
        [alert dismissWithClickedButtonIndex:0 animated:NO];
    }
    [[UIApplication sharedApplication].delegate.window makeKeyAndVisible];
}

- (void)loadErrorAlertWithConfirm:(NSString *)title message:(NSString *)message {
    dispatch_async(dispatch_get_main_queue(), ^{
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:title
                                                        message:message
                                                       delegate:nil
                                              cancelButtonTitle:NSLocalizedStringFromTable(@"OK", @"RongCloudKit", nil)
                                              otherButtonTitles:nil];
        alert.tag = AlertWithConfirm;
        [alert show];
    });
}

- (void)startReceiveCallVibrate
{
    //默认情况按静音或者锁屏键会静音
    AVAudioSession *audioSession = [AVAudioSession sharedInstance];
    [audioSession setCategory:AVAudioSessionCategorySoloAmbient error:nil];
    [self triggerVibrateRCCall];
}

- (void)stopReceiveCallVibrate
{
    if (self.timer) {
        [self.timer invalidate];
        self.timer = nil;
    }
    
    if (self.currentCallSession.callStatus == RCCallIncoming || self.currentCallSession.callStatus == RCCallRinging) {
        [[AVAudioSession sharedInstance] setActive:NO withOptions:AVAudioSessionSetActiveOptionNotifyOthersOnDeactivation error:nil];
    }
}

- (void)triggerVibrateRCCall {
    self.timer = [NSTimer scheduledTimerWithTimeInterval:2.f target:self selector:@selector(triggerVibrateRCCallAction) userInfo:nil repeats:YES];
}

- (void)triggerVibrateRCCallAction
{
    NSInteger checker = [RCCallKitUtility compareVersion:[UIDevice currentDevice].systemVersion toVersion:@"9.0"];
    if (checker >= 0) {
        AudioServicesPlaySystemSoundWithCompletion(kSystemSoundID_Vibrate, ^{});
    }
    else{
        AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
    }
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

//接口向后兼容 [[++
- (id<RCCallGroupMemberDataSource>)groupMemberDataSource {
    return [RCIM sharedRCIM].groupMemberDataSource;
}

- (void)setGroupMemberDataSource:(id<RCCallGroupMemberDataSource>)groupMemberDataSource {
    [RCIM sharedRCIM].groupMemberDataSource = groupMemberDataSource;
}
//接口向后兼容 --]]

@end
