//
//  RCCall.mm
//  RongCallKit
//
//  Created by RongCloud on 16/3/11.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCCall.h"
#import <AVFoundation/AVFoundation.h>
#import "RCCXCall.h"
#import "RCCallAudioMultiCallViewController.h"
#import "RCCallBaseViewController.h"
#import "RCCallDetailMessageCell.h"
#import "RCCallKitUtility.h"
#import "RCCallSelectMemberViewController.h"
#import "RCCallSingleCallViewController.h"
#import "RCCallTipMessageCell.h"
#import "RCCallVideoMultiCallViewController.h"
#import "RCUserInfoCacheManager.h"
#import "RongCallKitAdaptiveHeader.h"

#if __IPHONE_10_0
#import <UserNotifications/UserNotifications.h>
#endif

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#define AlertWithoutConfirm 1000
#define AlertWithConfirm 1001

#define kActivityWindowTag 1002

#ifndef dispatch_main_async_safe
#define dispatch_main_async_safe(block)                           \
    if (dispatch_queue_get_label(DISPATCH_CURRENT_QUEUE_LABEL) == \
        dispatch_queue_get_label(dispatch_get_main_queue())) {    \
        block();                                                  \
    } else {                                                      \
        dispatch_async(dispatch_get_main_queue(), block);         \
    }
#endif

static NSString *const __RongCallKit__Version = @"5.1.11";
static NSString *const __RongCallKit__Commit = @"51138f72";
static NSString *const __RongCallKit__Time = @"202111011809";

@interface RCCall () <RCCallReceiveDelegate>

@property (nonatomic, strong) NSMutableDictionary *alertInfoDic;
@property (nonatomic, strong) AVAudioPlayer *audioPlayer;
@property (nonatomic, strong) NSMutableArray *callWindows;
@property (nonatomic, strong) NSTimer *timer;
@property (nonatomic, strong) NSMutableDictionary *locationNotificationMap;

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
//RCCallKit_Delete_Start
#if PUBLIC
#else
            [[RCCallClient sharedRCCallClient] setApplePushKitEnable:YES];
#endif
            //RCCallKit_Delete_end
            NSLog(@"callkitVersion:%@, commitId:%@, time:%@", __RongCallKit__Version, __RongCallKit__Commit,
                  __RongCallKit__Time);
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
        UINavigationController *rootVC =
            [[UINavigationController alloc] initWithRootViewController:voipCallSelectViewController];
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
                                UIViewController *avCallVC = nil;
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
                    [self loadErrorAlertWithConfirm:RCCallKitLocalizedString(@"AccessRightTitle")
                                            message:RCCallKitLocalizedString(@"speakerAccessRight")];
                }
            });
        }];
    }
}

- (void)checkCapturePermission:(void (^)(BOOL granted))complete {
    AVAuthorizationStatus authStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];

    if (authStatus == AVAuthorizationStatusDenied || authStatus == AVAuthorizationStatusRestricted) {
        [self loadErrorAlertWithConfirm:RCCallKitLocalizedString(@"AccessRightTitle")
                                message:RCCallKitLocalizedString(@"cameraAccessRight")];
        complete(NO);
    } else if (authStatus == AVAuthorizationStatusNotDetermined) {
        [AVCaptureDevice requestAccessForMediaType:AVMediaTypeVideo
                                 completionHandler:^(BOOL granted) {
                                     if (!granted) {
                                         [self
                                             loadErrorAlertWithConfirm:RCCallKitLocalizedString(@"AccessRightTitle")
                                                               message:RCCallKitLocalizedString(@"cameraAccessRight")];
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
        [self loadErrorAlertWithoutConfirm:RCCallKitLocalizedString(@"VoIPAudioCallExistedWarning")];
        return NO;
    } else if (currentCallSession && currentCallSession.mediaType == RCCallMediaVideo) {
        [self loadErrorAlertWithoutConfirm:RCCallKitLocalizedString(@"VoIPVideoCallExistedWarning")];
        return NO;
    } else {
        return YES;
    }
}

- (void)presentCallViewController:(UIViewController *)viewController {
    [[[UIApplication sharedApplication] keyWindow] endEditing:YES];
    UIWindow *activityWindow = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    activityWindow.windowLevel = [UIApplication sharedApplication].keyWindow.windowLevel + 1;
    activityWindow.rootViewController = viewController;
    activityWindow.tag = kActivityWindowTag;
    [self.callWindows addObject:activityWindow];

    [self showActivityWindowIfNeedDelay];
}

- (void)showActivityWindowIfNeedDelay {
    NSArray *windows = [self.callWindows
        filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"tag == %ld", kActivityWindowTag]];
    if (!windows || windows.count == 0) {
        return;
    }
    UIWindow *window = windows.firstObject;
    if (@available(iOS 13.0, *)) {
        if ([UIApplication sharedApplication].keyWindow.windowScene) {
            [window setWindowScene:[UIApplication sharedApplication].keyWindow.windowScene];
            [self showActivityWindow:window];
        } else {
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.2 * NSEC_PER_SEC)), dispatch_get_main_queue(),
                           ^{
                               [self showActivityWindowIfNeedDelay];
                           });
        }
    } else {
        [self showActivityWindow:window];
    }
}

- (void)showActivityWindow:(UIWindow *)window {
    dispatch_main_async_safe(^{
        [window makeKeyAndVisible];
        CATransition *animation = [CATransition animation];
        [animation setDuration:0.3];
        animation.type = kCATransitionMoveIn;      //可更改为其他方式
        animation.subtype = kCATransitionFromTop;  //可更改为其他方式
        [[window layer] addAnimation:animation forKey:nil];
    });
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

- (void)didCancelCallRemoteNotification:(NSString *)callId
                          inviterUserId:(NSString *)inviterUserId
                              mediaType:(RCCallMediaType)mediaType
                             userIdList:(NSArray *)userIdList
                             pushConfig:(RCMessagePushConfig *)pushConfig
                         isRemoteCancel:(BOOL)isRemoteCancel {
    [self stopReceiveCallVibrate];

    [[RCCXCall sharedInstance] endCXCall];

    if (pushConfig && isRemoteCancel) {
        [self postLocalNotification:pushConfig userInfo:nil hasSound:NO isCancelCall:YES];
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
//RCCallKit_Delete_Start
#if PUBLIC
#else
    if (isVoIPPush) {
        NSInteger checker = [RCCallKitUtility compareVersion:[UIDevice currentDevice].systemVersion toVersion:@"10.0"];
        if (checker >= 0) {
            if (mediaType == RCCallMediaAudio) {
                [[RCCXCall sharedInstance] reportIncomingCallWithCallId:callId
                                                                inviter:inviterUserId
                                                             userIdList:userIdList
                                                                isVideo:NO];
                return;
            } else {
                [[RCCXCall sharedInstance] reportIncomingCallWithCallId:callId
                                                                inviter:inviterUserId
                                                             userIdList:userIdList
                                                                isVideo:YES];
                return;
            }
        }
    }
#endif
    //RCCallKit_Delete_end

    [self startReceiveCallVibrate];

    [self postLocalNotification:pushConfig userInfo:userDict hasSound:YES isCancelCall:NO];
}

- (void)postLocalNotification:(RCMessagePushConfig *)pushConfig
                     userInfo:(NSDictionary *)userInfo
                     hasSound:(BOOL)hasSound
                 isCancelCall:(BOOL)isCancelCall {
    NSLog(@"postLocalNotification hasSound:%@,isCancelCall:%@", hasSound ? @"YES" : @"NO",
          isCancelCall ? @"YES" : @"NO");
    NSString *pushContent = @"";
    NSString *title = @"";
    NSString *soundName = @"RongCallKit.bundle/voip/voip_call.caf";

    if ([RCIMClient sharedRCIMClient].pushProfile.isShowPushContent ||
        (pushConfig && pushConfig.forceShowDetailContent)) {
        if (pushConfig && pushConfig.pushTitle && pushConfig.pushTitle.length != 0) {
            title = pushConfig.pushTitle;
        } else {
            RCUserInfo *userInfo = [[RCUserInfoCacheManager sharedManager] getUserInfo:self.currentCallSession.inviter];
            if (self.currentCallSession.conversationType == ConversationType_PRIVATE) {
                if (userInfo) {
                    title = userInfo.name;
                }
            } else {
                RCGroup *groupInfo =
                    [[RCUserInfoCacheManager sharedManager] getGroupInfo:self.currentCallSession.targetId];
                if (groupInfo) {
                    title = groupInfo.groupName;
                }
            }
        }
        if (pushConfig && pushConfig.pushContent && pushConfig.pushContent.length != 0 &&
            ![pushConfig.pushContent isEqualToString:@"voip"]) {
            pushContent = pushConfig.pushContent;
        } else {
            if (isCancelCall) {
                pushContent = RCCallKitLocalizedString(@"VoIPCall_hangup_PushContent");
            } else {
                RCUserInfo *userInfo =
                    [[RCUserInfoCacheManager sharedManager] getUserInfo:self.currentCallSession.inviter];
                if (userInfo) {
                    pushContent =
                        [NSString stringWithFormat:self.currentCallSession.mediaType == RCCallMediaAudio ?
                                                       RCCallKitLocalizedString(@"VoIPCall_invite_audio_push_Content") :
                                                       RCCallKitLocalizedString(@"VoIPCall_invite_video_push_Content"),
                                                   userInfo.name];
                } else {
                    pushContent = self.currentCallSession.mediaType == RCCallMediaVideo ?
                        RCCallKitLocalizedString(@"VoIPVideoCallIncomingWithoutUserName") :
                        RCCallKitLocalizedString(@"VoIPAudioCallIncomingWithoutUserName");
                }
            }
        }
    } else {
        pushContent = RCCallKitLocalizedString(@"receive_new_message");
    }
    NSString *requestWithIdentifier = [NSUUID UUID].UUIDString;
    if (pushConfig && pushConfig.iOSConfig && pushConfig.iOSConfig.apnsCollapseId &&
        pushConfig.iOSConfig.apnsCollapseId.length > 0) {
        requestWithIdentifier = pushConfig.iOSConfig.apnsCollapseId;
    }

    if (@available(iOS 10.0, *)) {
        UNMutableNotificationContent *content = [[UNMutableNotificationContent alloc] init];
        if (pushConfig && !pushConfig.disablePushTitle) {
            content.title = title;
        }
        content.body = pushContent;
        content.userInfo = userInfo;
        if (hasSound) {
            content.sound = [UNNotificationSound soundNamed:soundName];
        } else {
            content.sound = [UNNotificationSound defaultSound];
        }
        if (pushConfig && pushConfig.iOSConfig && pushConfig.iOSConfig.threadId) {
            content.threadIdentifier = pushConfig.iOSConfig.threadId;
        }
        NSLog(@"postLocalNotification id:%@", requestWithIdentifier);
        [[UNUserNotificationCenter currentNotificationCenter]
            removeDeliveredNotificationsWithIdentifiers:@[requestWithIdentifier]];
        UNNotificationRequest *request = [UNNotificationRequest requestWithIdentifier:requestWithIdentifier
                                                                              content:content
                                                                              trigger:nil];
        [[UNUserNotificationCenter currentNotificationCenter] addNotificationRequest:request
                                                               withCompletionHandler:^(NSError *_Nullable error){
                                                               }];

    } else {
        UILocalNotification *callNotification = [[UILocalNotification alloc] init];
        callNotification.alertAction = RCCallKitLocalizedString(@"LocalNotificationShow");

        if (@available(iOS 8.2, *)) {
            if (pushConfig && !pushConfig.disablePushTitle) {
                callNotification.alertTitle = title;
            }
        }
        callNotification.alertBody = pushContent;
        callNotification.userInfo = userInfo;
        if (hasSound) {
            [callNotification setSoundName:soundName];
        } else {
            [callNotification setSoundName:UILocalNotificationDefaultSoundName];
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
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:title
                                                    message:nil
                                                   delegate:nil
                                          cancelButtonTitle:nil
                                          otherButtonTitles:nil];
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
                                              cancelButtonTitle:RCCallKitLocalizedString(@"OK")
                                              otherButtonTitles:nil];
        alert.tag = AlertWithConfirm;
        [alert show];
    });
}

- (void)startReceiveCallVibrate {
    [self triggerVibrateRCCall];
}

- (void)stopReceiveCallVibrate {
    if (self.timer) {
        [self.timer invalidate];
        self.timer = nil;
    }
}

- (void)triggerVibrateRCCall {
    self.timer = [NSTimer scheduledTimerWithTimeInterval:2.f
                                                  target:self
                                                selector:@selector(triggerVibrateRCCallAction)
                                                userInfo:nil
                                                 repeats:YES];
}

- (void)triggerVibrateRCCallAction {
    NSInteger checker = [RCCallKitUtility compareVersion:[UIDevice currentDevice].systemVersion toVersion:@"9.0"];
    if (checker >= 0) {
        AudioServicesPlaySystemSoundWithCompletion(kSystemSoundID_Vibrate,
                                                   ^{
                                                   });
    } else {
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

+ (NSString *)getVersion {
    return __RongCallKit__Version;
}

+ (void)load {
    Class clazz = NSClassFromString(@"RCUtilities");
    if (clazz && [clazz respondsToSelector:@selector(setModuleName:version:)]) {
        [clazz performSelector:@selector(setModuleName:version:)
                    withObject:@"callkit"
                    withObject:__RongCallKit__Version];
    }
}

@end
