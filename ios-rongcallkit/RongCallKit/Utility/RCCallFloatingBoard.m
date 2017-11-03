//
//  RCCallFloatingBoard.m
//  RongCallKit
//
//  Created by litao on 16/3/15.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCCallFloatingBoard.h"
#import "RCCallKitUtility.h"
#import <CoreTelephony/CTCall.h>
#import <CoreTelephony/CTCallCenter.h>
#import <UIKit/UIKit.h>

@interface RCCallFloatingBoard () <RCCallSessionDelegate>

@property(nonatomic, strong) NSTimer *activeTimer;
@property(nonatomic, copy) void (^touchedBlock)(RCCallSession *callSession);
@property(nonatomic, strong) CTCallCenter *callCenter;

@end

static RCCallFloatingBoard *staticBoard = nil;

static NSString *RCVoipFloatingBoardPosX = @"RCVoipFloatingBoardPosX";
static NSString *RCVoipFloatingBoardPosY = @"RCVoipFloatingBoardPosY";

@implementation RCCallFloatingBoard

+ (void)startCallFloatingBoard:(RCCallSession *)callSession
              withTouchedBlock:(void (^)(RCCallSession *callSession))touchedBlock {
    staticBoard = [[RCCallFloatingBoard alloc] init];
    staticBoard.callSession = callSession;
    [staticBoard.callSession setDelegate:staticBoard];
    staticBoard.touchedBlock = touchedBlock;
    [staticBoard initBoard];
}

+ (void)stopCallFloatingBoard {
    [staticBoard hideCallFloatingBoard];
    [staticBoard clearCallFloatingBoard];
    staticBoard = nil;
}

- (void)initBoard {
    if (self.callSession.callStatus == RCCallHangup) {
        [self performSelector:@selector(clearCallFloatingBoard) withObject:nil afterDelay:2];
    }
    [self updateActiveTimer];
    [self startActiveTimer];
    [self updateBoard];
    [self registerTelephonyEvent];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onOrientationChanged:)
                                                 name:UIApplicationDidChangeStatusBarOrientationNotification
                                               object:nil];
    [self addProximityMonitoringObserver];
}

- (void)registerTelephonyEvent {
    self.callCenter = [[CTCallCenter alloc] init];
    __weak __typeof(self) weakSelf = self;
    self.callCenter.callEventHandler = ^(CTCall *call) {
        if ([call.callState isEqualToString:CTCallStateConnected]) {
            [weakSelf.callSession hangup];
        }
    };
}

- (void)onOrientationChanged:(NSNotification *)notification {
    [self updateBoard];
}

- (void)startActiveTimer {
    self.activeTimer = [NSTimer scheduledTimerWithTimeInterval:1
                                                        target:self
                                                      selector:@selector(updateActiveTimer)
                                                      userInfo:nil
                                                       repeats:YES];
    [self.activeTimer fire];
}

- (void)stopActiveTimer {
    if (self.activeTimer) {
        [self.activeTimer invalidate];
        self.activeTimer = nil;
    }
}

- (void)updateActiveTimer {
    long sec = [[NSDate date] timeIntervalSince1970] - self.callSession.connectedTime / 1000;
    if (self.callSession.callStatus == RCCallActive && ![self isVideoViewEnabledSession]) {
        [self.floatingButton setTitle:[RCCallKitUtility getReadableStringForTime:sec] forState:UIControlStateNormal];
        [self layoutTextUnderImageButton:self.floatingButton];
    }
}

- (void)updateBoard {
    CGFloat posX = [[[NSUserDefaults standardUserDefaults] objectForKey:RCVoipFloatingBoardPosX] floatValue];
    CGFloat posY = [[[NSUserDefaults standardUserDefaults] objectForKey:RCVoipFloatingBoardPosY] floatValue];
    posX = posX ? posX : 30;
    posY = posY ? posY : 30;
    CGRect screenBounds = [UIScreen mainScreen].bounds;
    posX = (posX + 30) > screenBounds.size.width ? (screenBounds.size.width - 30) : posX;
    posY = (posY + 48) > screenBounds.size.height ? (screenBounds.size.height - 48) : posY;

    if ([UIDevice currentDevice].orientation == UIDeviceOrientationLandscapeLeft &&
        [self isSupportOrientation:UIInterfaceOrientationLandscapeLeft]) {
        self.window.transform = CGAffineTransformMakeRotation(M_PI / 2);
        self.window.frame = CGRectMake(posX, posY, 64, 96);
        self.floatingButton.frame = CGRectMake(0, 0, 96, 64);
        if ([self isVideoViewEnabledSession]) {
            self.videoView.frame = CGRectMake(0, 0, 96, 64);
        }
    } else if ([UIDevice currentDevice].orientation == UIDeviceOrientationLandscapeRight &&
               [self isSupportOrientation:UIInterfaceOrientationLandscapeRight]) {
        self.window.transform = CGAffineTransformMakeRotation(-M_PI / 2);
        self.window.frame = CGRectMake(posX, posY, 64, 96);
        self.floatingButton.frame = CGRectMake(0, 0, 96, 64);
        if ([self isVideoViewEnabledSession]) {
            self.videoView.frame = CGRectMake(0, 0, 96, 64);
        }
    } else {
        if ([UIDevice currentDevice].orientation == UIDeviceOrientationPortraitUpsideDown &&
            [self isSupportOrientation:UIInterfaceOrientationPortraitUpsideDown]) {
            self.window.transform = CGAffineTransformMakeRotation(M_PI);
        } else {
            self.window.transform = CGAffineTransformMakeRotation(0);
        }

        self.window.frame = CGRectMake(posX, posY, 64, 96);
        self.floatingButton.frame = CGRectMake(0, 0, 64, 96);
        if ([self isVideoViewEnabledSession]) {
            self.videoView.frame = CGRectMake(0, 0, 64, 96);
        }
    }

    if ([self isVideoViewEnabledSession]) {
        if (self.callSession.callStatus == RCCallActive) {
            [self.callSession setVideoView:self.videoView userId:self.callSession.targetId];
            [self.callSession setVideoView:nil userId:[RCIMClient sharedRCIMClient].currentUserInfo.userId];
        } else if (self.callSession.callStatus == RCCallHangup) {
            UILabel *videoStopTips =
                [[UILabel alloc] initWithFrame:CGRectMake(0, self.videoView.frame.size.height / 2 - 10,
                                                          self.videoView.frame.size.width, 20)];
            videoStopTips.textAlignment = NSTextAlignmentCenter;
            videoStopTips.text = NSLocalizedStringFromTable(@"VoIPCallHasEnd", @"RongCloudKit", nil);
            videoStopTips.textColor = RongVoIPUIColorFromRGB(0x0195ff);
            [self.videoView addSubview:videoStopTips];
        }
    } else {
        if (self.callSession.callStatus == RCCallActive) {
            [self.floatingButton setBackgroundColor:[UIColor clearColor]];
        } else if (self.callSession.callStatus == RCCallHangup) {
            [self.floatingButton setTitle:NSLocalizedStringFromTable(@"VoIPCallHasEnd", @"RongCloudKit", nil)
                                 forState:UIControlStateNormal];
        }
    }
}

- (UIWindow *)window {
    if (!_window) {
        CGFloat posX = [[[NSUserDefaults standardUserDefaults] objectForKey:RCVoipFloatingBoardPosX] floatValue];
        CGFloat posY = [[[NSUserDefaults standardUserDefaults] objectForKey:RCVoipFloatingBoardPosY] floatValue];
        posX = (posX - 30) ? posX : 30;
        posY = (posY - 48) ? posY : 48;
        CGRect screenBounds = [UIScreen mainScreen].bounds;
        posX = (posX + 30) > screenBounds.size.width ? (screenBounds.size.width - 30) : posX;
        posY = (posY + 48) > screenBounds.size.height ? (screenBounds.size.height - 48) : posY;
        _window = [[UIWindow alloc] initWithFrame:CGRectMake(posX, posY, 64, 96)];
        _window.backgroundColor = [UIColor whiteColor];
        _window.windowLevel = UIWindowLevelAlert + 1;
        _window.layer.cornerRadius = 4;
        _window.layer.masksToBounds = YES;
        _window.layer.borderWidth = 1;
        _window.layer.borderColor = [RongVoIPUIColorFromRGB(0x0195ff) CGColor];
        [_window makeKeyAndVisible]; //关键语句,显示window

        UIPanGestureRecognizer *panGestureRecognizer =
            [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(handlePanGestures:)];
        panGestureRecognizer.minimumNumberOfTouches = 1;
        panGestureRecognizer.maximumNumberOfTouches = 1;
        [_window addGestureRecognizer:panGestureRecognizer];
    }
    return _window;
}

- (UIView *)videoView {
    if (!_videoView) {
        _videoView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 64, 96)];
        _videoView.backgroundColor = [UIColor blackColor];
        CGRect windowFrame = self.window.frame;
        windowFrame.size.width = _videoView.frame.size.width;
        windowFrame.size.height = _videoView.frame.size.height;
        self.window.frame = windowFrame;
        [self.window addSubview:_videoView];

        UITapGestureRecognizer *tap =
            [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(touchedBoard:)];
        [_videoView addGestureRecognizer:tap];
    }
    return _videoView;
}

- (UIButton *)floatingButton {
    if (!_floatingButton) {
        _floatingButton = [UIButton buttonWithType:UIButtonTypeCustom];
        if (self.callSession.mediaType == RCCallMediaAudio) {
            [_floatingButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/audio_min.png"]
                             forState:UIControlStateNormal];
        } else {
            [_floatingButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/video_min.png"]
                             forState:UIControlStateNormal];
        }
        [_floatingButton setTitle:@"" forState:UIControlStateNormal];
        _floatingButton.backgroundColor = [UIColor clearColor];
        _floatingButton.frame = CGRectMake(0, 0, 64, 96);
        CGRect windowFrame = self.window.frame;
        windowFrame.size.width = _floatingButton.frame.size.width;
        windowFrame.size.height = _floatingButton.frame.size.height;
        self.window.frame = windowFrame;

        [_floatingButton addTarget:self action:@selector(touchedBoard:) forControlEvents:UIControlEventTouchUpInside];

        [self.window addSubview:_floatingButton];
    }
    return _floatingButton;
}

- (BOOL)isSupportOrientation:(UIInterfaceOrientation)orientation {
    UIInterfaceOrientationMask mask =
        [[UIApplication sharedApplication] supportedInterfaceOrientationsForWindow:self.window];
    return mask & (1 << orientation);
}

- (void)handlePanGestures:(UIPanGestureRecognizer *)paramSender {
    if (paramSender.state != UIGestureRecognizerStateEnded && paramSender.state != UIGestureRecognizerStateFailed) {
        CGPoint location = [paramSender locationInView:[UIApplication sharedApplication].windows[0]];

        if ([UIDevice currentDevice].orientation == UIDeviceOrientationLandscapeLeft &&
            [self isSupportOrientation:UIInterfaceOrientationLandscapeLeft]) {
            CGFloat tmp = location.x;
            location.x = [UIScreen mainScreen].bounds.size.height - location.y;
            location.y = tmp;
        } else if ([UIDevice currentDevice].orientation == UIDeviceOrientationLandscapeRight &&
                   [self isSupportOrientation:UIInterfaceOrientationLandscapeRight]) {
            CGFloat tmp = location.x;
            location.x = location.y;
            location.y = [UIScreen mainScreen].bounds.size.width - tmp;
        } else if ([UIDevice currentDevice].orientation == UIDeviceOrientationPortraitUpsideDown &&
                   [self isSupportOrientation:UIInterfaceOrientationPortraitUpsideDown]) {
            CGFloat tmp = location.x;
            location.x = [UIScreen mainScreen].bounds.size.height - location.y;
            location.y = [UIScreen mainScreen].bounds.size.width - tmp;
        }

        CGRect frame = self.window.frame;
        frame.origin.x = location.x - frame.size.width / 2;
        frame.origin.y = location.y - frame.size.height / 2;

        if (frame.origin.x < 0) {
            frame.origin.x = 2;
        }
        if (frame.origin.y < 0) {
            frame.origin.y = 2;
        }

        if ([RCCallKitUtility isLandscape] && [self isSupportOrientation:(UIInterfaceOrientation)[UIDevice currentDevice].orientation]) {
            if (frame.origin.y + frame.size.height > [UIScreen mainScreen].bounds.size.width) {
                frame.origin.y = [UIScreen mainScreen].bounds.size.width - 2 - frame.size.height;
            }

            if (frame.origin.x + frame.size.width > [UIScreen mainScreen].bounds.size.height) {
                frame.origin.x = [UIScreen mainScreen].bounds.size.height - 2 - frame.size.width;
            }
        } else {
            if (frame.origin.x + frame.size.width > [UIScreen mainScreen].bounds.size.width) {
                frame.origin.x = [UIScreen mainScreen].bounds.size.width - 2 - frame.size.width;
            }

            if (frame.origin.y + frame.size.height > [UIScreen mainScreen].bounds.size.height) {
                frame.origin.y = [UIScreen mainScreen].bounds.size.height - 2 - frame.size.height;
            }
        }
        self.window.frame = frame;
    } else if (paramSender.state == UIGestureRecognizerStateEnded) {
        CGRect frame = self.window.frame;
        [[NSUserDefaults standardUserDefaults] setObject:@(frame.origin.x) forKey:RCVoipFloatingBoardPosX];
        [[NSUserDefaults standardUserDefaults] setObject:@(frame.origin.y) forKey:RCVoipFloatingBoardPosY];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
}

- (void)touchedBoard:(id)sender {
    [self hideCallFloatingBoard];
    if (self.touchedBlock) {
        self.touchedBlock(self.callSession);
    }
    [self clearCallFloatingBoard];
}

- (void)hideCallFloatingBoard {
    [self stopActiveTimer];

    if (_videoView) {
        [_videoView removeFromSuperview];
        _videoView = nil;
    }
    if (_floatingButton) {
        [_floatingButton removeFromSuperview];
        _floatingButton = nil;
    }
    [_window setHidden:YES];
}

- (void)clearCallFloatingBoard {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    _activeTimer = nil;
    _callSession = nil;
    _touchedBlock = nil;
    _floatingButton = nil;
    _videoView = nil;
    _window = nil;
    staticBoard = nil;
}

- (void)layoutTextUnderImageButton:(UIButton *)button {
    [button.titleLabel setFont:[UIFont systemFontOfSize:16]];
    [button setTitleColor:RongVoIPUIColorFromRGB(0x0195ff) forState:UIControlStateNormal];

    button.titleEdgeInsets = UIEdgeInsetsMake(0, -button.imageView.frame.size.width,
                                              -button.imageView.frame.size.height - RCCallInsideMargin / 2, 0);
    // button.imageEdgeInsets =
    // UIEdgeInsetsMake(-button.titleLabel.frame.size.height-offset/2, 0, 0,
    // -button.titleLabel.frame.size.width);
    // 由于iOS8中titleLabel的size为0，用上面这样设置有问题，修改一下即可
    button.imageEdgeInsets = UIEdgeInsetsMake(-button.titleLabel.intrinsicContentSize.height - RCCallInsideMargin / 2,
                                              0, 0, -button.titleLabel.intrinsicContentSize.width);
}

- (BOOL)isVideoViewEnabledSession {
    if (self.callSession.mediaType == RCCallMediaVideo && !self.callSession.isMultiCall) {
        return YES;
    } else {
        return NO;
    }
}

/*!
 通话已接通
 */
- (void)callDidConnect {
    [self updateBoard];
}

/*!
 通话已结束
 */
- (void)callDidDisconnect {
    [self updateBoard];
    [self performSelector:@selector(clearCallFloatingBoard) withObject:nil afterDelay:2];
    [RCCallKitUtility clearScreenForceOnStatus];
    [self removeProximityMonitoringObserver];
}

/*!
 对端正在振铃

 @param userId 对端的用户ID
 */
- (void)remoteUserDidRing:(NSString *)userId {
}

/*!
 有用户被邀请加入通话

 @param userId    被邀请的用户ID
 @param mediaType 希望被邀请者选择的媒体类型
 */
- (void)remoteUserDidInvite:(NSString *)userId mediaType:(RCCallMediaType)mediaType {
}

/*!
 有用户加入了通话

 @param userId    用户ID
 @param mediaType 用户的媒体类型
 */
- (void)remoteUserDidJoin:(NSString *)userId mediaType:(RCCallMediaType)mediaType {
}

/*!
 有用户切换了媒体类型

 @param userId    用户ID
 @param mediaType 切换至的媒体类型
 */
- (void)remoteUserDidChangeMediaType:(NSString *)userId mediaType:(RCCallMediaType)mediaType {
    dispatch_async(dispatch_get_main_queue(), ^{
        if (!self.callSession.isMultiCall) {
            if (mediaType == RCCallMediaAudio && self.callSession.mediaType != RCCallMediaAudio) {
                if ([self.callSession changeMediaType:RCCallMediaAudio]) {
                    [self.videoView removeFromSuperview];
                    [self initBoard];
                }
            }
        }
    });
}

/*!
 对端用户关闭/打开了摄像头

 @param userId    用户ID
 @param muted     是否关闭camera
 */
- (void)remoteUserDidDisableCamera:(BOOL)muted byUser:(NSString *)userId {
}

/*!
 有用户挂断

 @param userId 用户ID
 @param reason 挂断的原因
 */
- (void)remoteUserDidLeft:(NSString *)userId reason:(RCCallDisconnectReason)reason {
}

/*!
 对方正在振铃，可以播放对应的彩铃
 */
- (void)shouldAlertForWaitingRemoteResponse {
}

/*!
 收到电话，可以播放铃声
 */
- (void)shouldRingForIncomingCall {
}

/*!
 停止播放铃声(通话接通或挂断)
 */
- (void)shouldStopAlertAndRing {
}

/*!
 通话过程中的错误回调

 @param error 错误码

 @warning 如果是不可恢复的错误，SDK会挂断电话并回调callDidDisconnect。
 */
- (void)errorDidOccur:(RCCallErrorCode)error {
}

- (void)addProximityMonitoringObserver {
    [UIDevice currentDevice].proximityMonitoringEnabled = YES;

    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(proximityStatueChanged:)
                                                 name:UIDeviceProximityStateDidChangeNotification
                                               object:nil];
}

- (void)removeProximityMonitoringObserver {
    [UIDevice currentDevice].proximityMonitoringEnabled = NO;

    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:UIDeviceProximityStateDidChangeNotification
                                                  object:nil];
}

- (void)proximityStatueChanged:(NSNotificationCenter *)notification {
    //    if ([UIDevice currentDevice].proximityState) {
    //        [[AVAudioSession sharedInstance]
    //        setCategory:AVAudioSessionCategoryPlayAndRecord error:nil];
    //    } else {
    //        [[AVAudioSession sharedInstance]
    //        setCategory:AVAudioSessionCategoryPlayback error:nil];
    //    }
}
@end
