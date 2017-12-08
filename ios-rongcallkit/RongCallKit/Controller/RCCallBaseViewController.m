//
//  RCCallBaseViewController.m
//  RongCallKit
//
//  Created by 岑裕 on 16/3/17.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCCallBaseViewController.h"
#import "RCCall.h"
#import "RCCallFloatingBoard.h"
#import "RCCallKitUtility.h"
#import "RCloudImageView.h"
#import <AVFoundation/AVFoundation.h>
#import <CoreTelephony/CTCall.h>
#import <CoreTelephony/CTCallCenter.h>

@interface RCCallBaseViewController ()

@property(nonatomic, strong) NSTimer *activeTimer;
@property(nonatomic, strong) AVAudioPlayer *audioPlayer;
@property(nonatomic, assign) BOOL needPlayingAlertAfterForeground;
@property(nonatomic, assign) BOOL needPlayingRingAfterForeground;
@property(nonatomic, strong) CTCallCenter *callCenter;

@end

@implementation RCCallBaseViewController
#pragma mark - init
- (instancetype)initWithIncomingCall:(RCCallSession *)callSession {
    self = [super init];
    if (self) {
        _callSession = callSession;
        [self registerForegroundNotification];
        [_callSession setDelegate:self];
        [RCCallKitUtility setScreenForceOn];
    }
    return self;
}

- (instancetype)initWithOutgoingCall:(RCConversationType)conversationType
                            targetId:(NSString *)targetId
                           mediaType:(RCCallMediaType)mediaType
                          userIdList:(NSArray *)userIdList {
    self = [super init];
    if (self) {
        _callSession = [[RCCallClient sharedRCCallClient] startCall:conversationType
                                                           targetId:targetId
                                                                 to:userIdList
                                                          mediaType:mediaType
                                                    sessionDelegate:self
                                                              extra:nil];
        [self registerForegroundNotification];
        [RCCallKitUtility setScreenForceOn];
    }
    return self;
}

- (instancetype)initWithActiveCall:(RCCallSession *)callSession {
    self = [super init];
    if (self) {
        _callSession = callSession;
        [self registerForegroundNotification];
        [_callSession setDelegate:self];
    }
    return self;
}

- (void)registerForegroundNotification {
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(appDidBecomeActive)
                                                 name:UIApplicationDidBecomeActiveNotification
                                               object:nil];
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

#pragma mark - getter
- (RCConversationType)conversationType {
    return self.callSession.conversationType;
}

- (NSString *)targetId {
    return self.callSession.targetId;
}

- (RCCallMediaType)mediaType {
    return self.callSession.mediaType;
}

- (void)appDidBecomeActive {
    if (self.needPlayingAlertAfterForeground) {
        [self shouldAlertForWaitingRemoteResponse];
    } else if (self.needPlayingRingAfterForeground) {
        [self shouldRingForIncomingCall];
    }
}

- (void)startPlayRing:(NSString *)ringPath {
    if (ringPath) {
        AVAudioSession *audioSession = [AVAudioSession sharedInstance];
        //默认情况按静音或者锁屏键会静音
        [audioSession setCategory:AVAudioSessionCategorySoloAmbient error:nil];
        [audioSession setActive:YES error:nil];

        if (self.audioPlayer) {
            [self stopPlayRing];
        }

        NSURL *url = [NSURL URLWithString:ringPath];
        NSError *error = nil;
        self.audioPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:&error];
        if (!error) {
            self.audioPlayer.numberOfLoops = -1;
            self.audioPlayer.volume = 1.0;
            [self.audioPlayer prepareToPlay];
            [self.audioPlayer play];
        }
    }
}

- (void)stopPlayRing {
    if (self.audioPlayer) {
        [self.audioPlayer stop];
        self.audioPlayer = nil;
        //设置铃声停止后恢复其他app的声音
        [[AVAudioSession sharedInstance] setActive:NO withOptions:AVAudioSessionSetActiveOptionNotifyOthersOnDeactivation
                                             error:nil];
    }
}

- (void)viewDidLoad {
    [super viewDidLoad];

    self.backgroundView = [[UIView alloc] initWithFrame:self.view.bounds];
    self.backgroundView.backgroundColor = RongVoIPUIColorFromRGB(0x262e42);
    [self.view addSubview:self.backgroundView];
    self.backgroundView.hidden = NO;

    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onOrientationChanged:)
                                                 name:UIApplicationDidChangeStatusBarOrientationNotification
                                               object:nil];

    [self registerTelephonyEvent];
    [self addProximityMonitoringObserver];
    //    UIVisualEffect *blurEffect = [UIBlurEffect
    //    effectWithStyle:UIBlurEffectStyleDark];
    //    self.blurView = [[UIVisualEffectView alloc] initWithEffect:blurEffect];
    //    self.blurView.frame = self.view.frame;
    //    [self.view addSubview:self.blurView];
    //    self.blurView.hidden = NO;
}

- (void)onOrientationChanged:(NSNotification *)notification {
    [self resetLayout:self.callSession.isMultiCall
            mediaType:self.callSession.mediaType
           callStatus:self.callSession.callStatus];
}
- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];

    if (self.callSession.callStatus == RCCallActive) {
        [self updateActiveTimer];
        [self startActiveTimer];
    } else if (self.callSession.callStatus == RCCallDialing) {
        self.tipsLabel.text = NSLocalizedStringFromTable(@"VoIPCallWaitingForRemoteAccept", @"RongCloudKit", nil);
    } else if (self.callSession.callStatus == RCCallIncoming || self.callSession.callStatus == RCCallRinging) {
        if (self.needPlayingRingAfterForeground) {
            [self shouldRingForIncomingCall];
        }
        if (self.callSession.mediaType == RCCallMediaAudio) {
            self.tipsLabel.text = NSLocalizedStringFromTable(@"VoIPAudioCallIncoming", @"RongCloudKit", nil);
        } else {
            self.tipsLabel.text = NSLocalizedStringFromTable(@"VoIPVideoCallIncoming", @"RongCloudKit", nil);
        }
    } else if (self.callSession.callStatus == RCCallHangup) {
        [self callDidDisconnect];
    }

    [self resetLayout:self.callSession.isMultiCall
            mediaType:self.callSession.mediaType
           callStatus:self.callSession.callStatus];
}

#pragma mark - Button&&Label&View
- (UIButton *)minimizeButton {
    if (!_minimizeButton) {
        _minimizeButton =
            [[UIButton alloc] initWithFrame:CGRectMake(RCCallHorizontalMargin / 2, RCCallVerticalMargin / 2,
                                                       RCCallButtonLength, RCCallButtonLength)];
        [_minimizeButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/minimize.png"]
                         forState:UIControlStateNormal];
        [_minimizeButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/minimize.png"]
                         forState:UIControlStateHighlighted];

        [_minimizeButton addTarget:self
                            action:@selector(minimizeButtonClicked)
                  forControlEvents:UIControlEventTouchUpInside];

        [self.view addSubview:_minimizeButton];
        _minimizeButton.hidden = YES;
    }
    return _minimizeButton;
}

- (void)minimizeButtonClicked {
    [self didTapMinimizeButton];

    Class selfClass = [self class];
    [RCCallFloatingBoard
        startCallFloatingBoard:self.callSession
              withTouchedBlock:^(RCCallSession *callSession) {
                  [[RCCall sharedRCCall] presentCallViewController:[[selfClass alloc] initWithActiveCall:callSession]];
              }];
    [self stopActiveTimer];
    [[RCCall sharedRCCall] dismissCallViewController:self];
}

- (UIButton *)inviteUserButton {
    if (!_inviteUserButton) {
        _inviteUserButton =
            [[UIButton alloc] initWithFrame:CGRectMake(RCCallHorizontalMargin / 2, RCCallVerticalMargin / 2,
                                                       RCCallButtonLength, RCCallButtonLength)];
        [_inviteUserButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/add.png"]
                           forState:UIControlStateNormal];
        [_inviteUserButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/add.png"]
                           forState:UIControlStateHighlighted];

        [_inviteUserButton addTarget:self
                              action:@selector(inviteUserButtonClicked)
                    forControlEvents:UIControlEventTouchUpInside];

        [self.view addSubview:_inviteUserButton];
        _inviteUserButton.hidden = YES;
    }
    return _inviteUserButton;
}

- (void)inviteUserButtonClicked {
    [self didTapInviteUserButton];
}

- (UILabel *)timeLabel {
    if (!_timeLabel) {
        _timeLabel = [[UILabel alloc] init];
        _timeLabel.backgroundColor = [UIColor clearColor];
        _timeLabel.textColor = [UIColor whiteColor];
        _timeLabel.font = [UIFont systemFontOfSize:18];
        _timeLabel.textAlignment = NSTextAlignmentCenter;

        [self.view addSubview:_timeLabel];
        _timeLabel.hidden = YES;
    }
    return _timeLabel;
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
    self.timeLabel.text = [RCCallKitUtility getReadableStringForTime:sec];
}

- (UILabel *)tipsLabel {
    if (!_tipsLabel) {
        _tipsLabel = [[UILabel alloc] init];
        _tipsLabel.backgroundColor = [UIColor clearColor];
        _tipsLabel.textColor = [UIColor whiteColor];
        _tipsLabel.font = [UIFont systemFontOfSize:18];
        _tipsLabel.textAlignment = NSTextAlignmentCenter;

        [self.view addSubview:_tipsLabel];
        _tipsLabel.hidden = YES;
    }
    return _tipsLabel;
}

- (UIButton *)muteButton {
    if (!_muteButton) {
        _muteButton = [[UIButton alloc] init];
        [_muteButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/mute.png"] forState:UIControlStateNormal];
        [_muteButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/mute_hover.png"]
                     forState:UIControlStateHighlighted];
        [_muteButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/mute_hover.png"]
                     forState:UIControlStateSelected];
        [_muteButton setTitle:NSLocalizedStringFromTable(@"VoIPCallMute", @"RongCloudKit", nil)
                     forState:UIControlStateNormal];
        [_muteButton setSelected:self.callSession.isMuted];
        [_muteButton addTarget:self action:@selector(muteButtonClicked) forControlEvents:UIControlEventTouchUpInside];

        [self.view addSubview:_muteButton];
        _muteButton.hidden = YES;
    }
    return _muteButton;
}

- (void)muteButtonClicked {
    [self didTapMuteButton];

    [self.callSession setMuted:!self.callSession.isMuted];
    [self.muteButton setSelected:self.callSession.isMuted];
}

- (UIButton *)speakerButton {
    if (!_speakerButton) {
        _speakerButton = [[UIButton alloc] init];
        [_speakerButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/handfree.png"]
                        forState:UIControlStateNormal];
        [_speakerButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/handfree_hover.png"]
                        forState:UIControlStateHighlighted];
        [_speakerButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/handfree_hover.png"]
                        forState:UIControlStateSelected];
        [_speakerButton setTitle:NSLocalizedStringFromTable(@"VoIPCallSpeaker", @"RongCloudKit", nil)
                        forState:UIControlStateNormal];
        [_speakerButton setSelected:self.callSession.speakerEnabled];

        [_speakerButton addTarget:self
                           action:@selector(speakerButtonClicked)
                 forControlEvents:UIControlEventTouchUpInside];

        [self.view addSubview:_speakerButton];
        _speakerButton.hidden = YES;
    }
    return _speakerButton;
}

- (void)speakerButtonClicked {
    [self didTapSpeakerButton];

    [self.callSession setSpeakerEnabled:!self.callSession.speakerEnabled];
    [self.speakerButton setSelected:self.callSession.speakerEnabled];
}

- (UIButton *)acceptButton {
    if (!_acceptButton) {
        _acceptButton = [[UIButton alloc] init];
        [_acceptButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/answer.png"]
                       forState:UIControlStateNormal];
        [_acceptButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/answer_hover.png"]
                       forState:UIControlStateHighlighted];
        [_acceptButton setTitle:NSLocalizedStringFromTable(@"VoIPCallAccept", @"RongCloudKit", nil)
                       forState:UIControlStateNormal];

        [_acceptButton addTarget:self
                          action:@selector(acceptButtonClicked)
                forControlEvents:UIControlEventTouchUpInside];

        [self.view addSubview:_acceptButton];
        _acceptButton.hidden = YES;
    }
    return _acceptButton;
}

- (void)acceptButtonClicked {
    [self didTapAcceptButton];

    if (!self.callSession) {
        [self callDidDisconnect];
    } else {
        [self.callSession accept:self.callSession.mediaType];
    }
}

- (UIButton *)hangupButton {
    if (!_hangupButton) {
        _hangupButton = [[UIButton alloc] init];
        [_hangupButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/hang_up.png"]
                       forState:UIControlStateNormal];
        [_hangupButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/hang_up_hover.png"]
                       forState:UIControlStateHighlighted];
        [_hangupButton setTitle:NSLocalizedStringFromTable(@"VoIPCallHangup", @"RongCloudKit", nil)
                       forState:UIControlStateNormal];

        [_hangupButton addTarget:self
                          action:@selector(hangupButtonClicked)
                forControlEvents:UIControlEventTouchUpInside];

        [self.view addSubview:_hangupButton];
        _hangupButton.hidden = YES;
    }
    return _hangupButton;
}

- (void)hangupButtonClicked {
    [self didTapHangupButton];

    if (!self.callSession) {
        [self callDidDisconnect];
    } else {
        [self.callSession hangup];
    }
}

- (UIButton *)cameraCloseButton {
    if (!_cameraCloseButton) {
        _cameraCloseButton = [[UIButton alloc] init];

        if (!self.callSession.isMultiCall) {
            [_cameraCloseButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/audio.png"]
                                forState:UIControlStateNormal];
            [_cameraCloseButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/audio.png"]
                                forState:UIControlStateHighlighted];
            [_cameraCloseButton
                setTitle:NSLocalizedStringFromTable(@"VoIPVideoCallTurnToAudioCall", @"RongCloudKit", nil)
                forState:UIControlStateNormal];
        } else {
            [_cameraCloseButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/video.png"]
                                forState:UIControlStateNormal];
            [_cameraCloseButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/video.png"]
                                forState:UIControlStateHighlighted];
            [_cameraCloseButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/video_hover.png"]
                                forState:UIControlStateSelected];
            [_cameraCloseButton setTitle:NSLocalizedStringFromTable(@"VoIPVideoCallCloseCamera", @"RongCloudKit", nil)
                                forState:UIControlStateNormal];
            [_cameraCloseButton setTitle:NSLocalizedStringFromTable(@"VoIPVideoCallOpenCamera", @"RongCloudKit", nil)
                                forState:UIControlStateSelected];
        }

        [_cameraCloseButton setSelected:!self.callSession.cameraEnabled];
        [_cameraCloseButton addTarget:self
                               action:@selector(cameraCloseButtonClicked)
                     forControlEvents:UIControlEventTouchUpInside];

        [self.view addSubview:_cameraCloseButton];
        _cameraCloseButton.hidden = YES;
    }
    return _cameraCloseButton;
}

- (void)cameraCloseButtonClicked {
    [self didTapCameraCloseButton];

    if (!self.callSession.isMultiCall) {
        [self.callSession setVideoView:nil userId:[RCIMClient sharedRCIMClient].currentUserInfo.userId];
        [self.callSession setVideoView:nil userId:self.callSession.targetId];

        if (self.callSession.callStatus == RCCallIncoming || self.callSession.callStatus == RCCallRinging) {
            [self.callSession accept:RCCallMediaAudio];
        }

        if ([self.callSession changeMediaType:RCCallMediaAudio]) {
            [self resetLayout:self.callSession.isMultiCall
                    mediaType:RCCallMediaAudio
                   callStatus:self.callSession.callStatus];
        }
    } else {
        [self.callSession setCameraEnabled:!self.callSession.cameraEnabled];
        [self.cameraCloseButton setSelected:!self.callSession.cameraEnabled];
    }
}

- (UIButton *)cameraSwitchButton {
    if (!_cameraSwitchButton) {
        _cameraSwitchButton = [[UIButton alloc] init];

        if (!self.callSession.isMultiCall) {
            [_cameraSwitchButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/camera.png"]
                                 forState:UIControlStateNormal];
            [_cameraSwitchButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/camera_hover.png"]
                                 forState:UIControlStateHighlighted];
            [_cameraSwitchButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/camera_hover.png"]
                                 forState:UIControlStateSelected];
            [_cameraSwitchButton setTitle:NSLocalizedStringFromTable(@"VoIPAudioCallCamera", @"RongCloudKit", nil)
                                 forState:UIControlStateNormal];
            [_cameraSwitchButton setTitle:NSLocalizedStringFromTable(@"VoIPAudioCallCamera", @"RongCloudKit", nil)
                                 forState:UIControlStateSelected];
        } else {
            [_cameraSwitchButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/change.png"]
                                 forState:UIControlStateNormal];
            [_cameraSwitchButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/change.png"]
                                 forState:UIControlStateHighlighted];
            [_cameraSwitchButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/change.png"]
                                 forState:UIControlStateSelected];
        }

        [_cameraSwitchButton addTarget:self
                                action:@selector(cameraSwitchButtonClicked)
                      forControlEvents:UIControlEventTouchUpInside];

        [self.view addSubview:_cameraSwitchButton];
        _cameraSwitchButton.hidden = YES;
    }
    return _cameraSwitchButton;
}

- (void)cameraSwitchButtonClicked {
    [self didTapCameraSwitchButton];

    [self.callSession switchCameraMode];
}

#pragma mark - layout
- (void)resetLayout:(BOOL)isMultiCall mediaType:(RCCallMediaType)mediaType callStatus:(RCCallStatus)callStatus {
    if (mediaType == RCCallMediaAudio && !isMultiCall) {
        self.backgroundView.backgroundColor = RongVoIPUIColorFromRGB(0x262e42);
        self.backgroundView.hidden = NO;

        self.blurView.hidden = NO;

        if (callStatus == RCCallActive) {
            self.minimizeButton.frame = CGRectMake(RCCallHorizontalMargin / 2, RCCallVerticalMargin,
                                                   RCCallButtonLength / 2, RCCallButtonLength / 2);
            self.minimizeButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.minimizeButton.hidden = YES;
        }

        self.inviteUserButton.hidden = YES;

        // header orgin y = RCCallVerticalMargin * 3
        if (callStatus == RCCallActive) {
            self.timeLabel.frame =
                CGRectMake(RCCallHorizontalMargin,
                           RCCallVerticalMargin * 3 + RCCallHeaderLength + RCCallInsideMargin * 2 + RCCallLabelHeight,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
            self.timeLabel.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.timeLabel.hidden = YES;
        }

        if (callStatus == RCCallHangup) {
            self.tipsLabel.frame =
                CGRectMake(RCCallHorizontalMargin,
                           self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength -
                               RCCallInsideMargin * 3 - RCCallLabelHeight,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        } else if (callStatus == RCCallActive) {
            self.tipsLabel.frame = CGRectMake(
                RCCallHorizontalMargin,
                MAX((self.view.frame.size.height - RCCallLabelHeight) / 2,
                    RCCallVerticalMargin * 3 + RCCallHeaderLength + RCCallInsideMargin * 3 + RCCallLabelHeight * 2),
                self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        } else {
            self.tipsLabel.frame =
                CGRectMake(RCCallHorizontalMargin,
                           RCCallVerticalMargin * 3 + RCCallHeaderLength + RCCallInsideMargin * 2 + RCCallLabelHeight,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        }
        self.tipsLabel.hidden = NO;

        if (callStatus == RCCallActive) {
            self.muteButton.frame = CGRectMake(RCCallHorizontalMargin,
                                               self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength,
                                               RCCallButtonLength, RCCallButtonLength);
            [self layoutTextUnderImageButton:self.muteButton];
            self.muteButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.muteButton.hidden = YES;
        }

        if (callStatus == RCCallActive) {
            self.speakerButton.frame =
                CGRectMake(self.view.frame.size.width - RCCallHorizontalMargin - RCCallButtonLength,
                           self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength, RCCallButtonLength,
                           RCCallButtonLength);
            [self layoutTextUnderImageButton:self.speakerButton];
            self.speakerButton.hidden = NO;
            [self.speakerButton setSelected:self.callSession.speakerEnabled];
        } else if (callStatus != RCCallHangup) {
            self.speakerButton.hidden = YES;
        }

        if (callStatus == RCCallDialing) {
            self.hangupButton.frame =
                CGRectMake((self.view.frame.size.width - RCCallButtonLength) / 2,
                           self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength, RCCallButtonLength,
                           RCCallButtonLength);
            [self layoutTextUnderImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.hidden = YES;
        } else if (callStatus == RCCallIncoming || callStatus == RCCallRinging) {
            self.hangupButton.frame = CGRectMake(
                RCCallHorizontalMargin, self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength,
                RCCallButtonLength, RCCallButtonLength);
            [self layoutTextUnderImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.frame =
                CGRectMake(self.view.frame.size.width - RCCallHorizontalMargin - RCCallButtonLength,
                           self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength, RCCallButtonLength,
                           RCCallButtonLength);
            [self layoutTextUnderImageButton:self.acceptButton];
            self.acceptButton.hidden = NO;
        } else if (callStatus == RCCallActive) {
            self.hangupButton.frame =
                CGRectMake((self.view.frame.size.width - RCCallButtonLength) / 2,
                           self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength, RCCallButtonLength,
                           RCCallButtonLength);
            [self layoutTextUnderImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.hidden = YES;
        }

        self.cameraCloseButton.hidden = YES;
        self.cameraSwitchButton.hidden = YES;

    } else if (mediaType == RCCallMediaVideo && !isMultiCall) {
        self.backgroundView.hidden = NO;

        self.blurView.hidden = YES;

        if (callStatus == RCCallActive) {
            self.minimizeButton.frame = CGRectMake(RCCallHorizontalMargin / 2, RCCallVerticalMargin,
                                                   RCCallButtonLength / 2, RCCallButtonLength / 2);
            self.minimizeButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.minimizeButton.hidden = YES;
        }

        self.inviteUserButton.hidden = YES;

        if (callStatus == RCCallActive) {
            self.timeLabel.frame =
                CGRectMake(RCCallHorizontalMargin, RCCallVerticalMargin + RCCallInsideMargin + RCCallLabelHeight,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
            self.timeLabel.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.timeLabel.hidden = YES;
        }

        // header orgin y = RCCallVerticalMargin * 3
        if (callStatus == RCCallActive) {
            self.tipsLabel.frame =
                CGRectMake(RCCallHorizontalMargin,
                           MAX((self.view.frame.size.height - RCCallLabelHeight) / 2,
                               RCCallVerticalMargin + RCCallHeaderLength * 1.5 + RCCallInsideMargin * 3),
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        } else if (callStatus == RCCallDialing) {
            self.tipsLabel.frame =
                CGRectMake(RCCallHorizontalMargin,
                           RCCallVerticalMargin * 3 + RCCallHeaderLength + RCCallInsideMargin * 2 + RCCallLabelHeight,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        } else if (callStatus == RCCallIncoming || callStatus == RCCallRinging) {
            self.tipsLabel.frame =
                CGRectMake(RCCallHorizontalMargin,
                           RCCallVerticalMargin * 3 + RCCallHeaderLength + RCCallInsideMargin * 2 + RCCallLabelHeight,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        } else if (callStatus == RCCallHangup) {
            self.tipsLabel.frame = CGRectMake(
                RCCallHorizontalMargin,
                self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength * 2 - RCCallInsideMargin * 8,
                self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        }
        self.tipsLabel.hidden = NO;

        if (callStatus == RCCallActive) {
            self.muteButton.frame = CGRectMake(RCCallHorizontalMargin,
                                               self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength,
                                               RCCallButtonLength, RCCallButtonLength);
            [self layoutTextUnderImageButton:self.muteButton];
            self.muteButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.muteButton.hidden = YES;
        }

        self.speakerButton.hidden = YES;

        if (callStatus == RCCallDialing) {
            self.hangupButton.frame =
                CGRectMake((self.view.frame.size.width - RCCallButtonLength) / 2,
                           self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength, RCCallButtonLength,
                           RCCallButtonLength);
            [self layoutTextUnderImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.hidden = YES;
        } else if (callStatus == RCCallIncoming || callStatus == RCCallRinging) {
            self.hangupButton.frame = CGRectMake(
                RCCallHorizontalMargin, self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength,
                RCCallButtonLength, RCCallButtonLength);
            [self layoutTextUnderImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.frame =
                CGRectMake(self.view.frame.size.width - RCCallHorizontalMargin - RCCallButtonLength,
                           self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength, RCCallButtonLength,
                           RCCallButtonLength);
            [self layoutTextUnderImageButton:self.acceptButton];
            self.acceptButton.hidden = NO;
        } else if (callStatus == RCCallActive) {
            self.hangupButton.frame =
                CGRectMake((self.view.frame.size.width - RCCallButtonLength) / 2,
                           self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength, RCCallButtonLength,
                           RCCallButtonLength);
            [self layoutTextUnderImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.hidden = YES;
        }

        if (callStatus == RCCallActive) {
            self.cameraSwitchButton.frame =
                CGRectMake(self.view.frame.size.width - RCCallHorizontalMargin - RCCallButtonLength,
                           self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength, RCCallButtonLength,
                           RCCallButtonLength);
            [self layoutTextUnderImageButton:self.cameraSwitchButton];
            self.cameraSwitchButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.cameraSwitchButton.hidden = YES;
        }

        if (callStatus == RCCallActive) {
            self.cameraCloseButton.frame = CGRectMake(
                self.view.frame.size.width - RCCallHorizontalMargin - RCCallButtonLength,
                self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength * 2 - RCCallInsideMargin * 5,
                RCCallButtonLength, RCCallButtonLength);
            [self layoutTextUnderImageButton:self.cameraCloseButton];
            self.cameraCloseButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.cameraCloseButton.hidden = YES;
        }

    } else if (mediaType == RCCallMediaAudio && isMultiCall) {
        self.backgroundView.backgroundColor = RongVoIPUIColorFromRGB(0x262e42);
        self.backgroundView.hidden = NO;

        self.blurView.hidden = NO;

        if (callStatus == RCCallActive) {
            self.minimizeButton.frame = CGRectMake(RCCallHorizontalMargin / 2, RCCallVerticalMargin,
                                                   RCCallButtonLength / 2, RCCallButtonLength / 2);
            self.minimizeButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.minimizeButton.hidden = YES;
        }

        if (callStatus == RCCallActive) {
            self.inviteUserButton.frame =
                CGRectMake(self.view.frame.size.width - RCCallHorizontalMargin / 2 - RCCallButtonLength / 2,
                           RCCallVerticalMargin, RCCallButtonLength / 2, RCCallButtonLength / 2);
            self.inviteUserButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.inviteUserButton.hidden = YES;
        }

        if (callStatus == RCCallActive) {
            self.timeLabel.frame =
                CGRectMake(RCCallHorizontalMargin, RCCallVerticalMargin,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
            self.timeLabel.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.timeLabel.hidden = YES;
        }

        // header orgin y = RCCallVerticalMargin * 2
        if (callStatus == RCCallIncoming || callStatus == RCCallRinging) {
            self.tipsLabel.frame =
                CGRectMake(RCCallHorizontalMargin,
                           RCCallVerticalMargin * 2 + RCCallHeaderLength + RCCallInsideMargin * 2 + RCCallLabelHeight,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        } else if (callStatus == RCCallDialing) {
            self.tipsLabel.frame =
                CGRectMake(RCCallHorizontalMargin, RCCallVerticalMargin,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        } else {
            self.tipsLabel.frame =
                CGRectMake(RCCallHorizontalMargin,
                           self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength -
                               RCCallInsideMargin * 3 - RCCallLabelHeight,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        }
        self.tipsLabel.hidden = NO;

        if (callStatus == RCCallActive) {
            self.muteButton.frame = CGRectMake(RCCallHorizontalMargin,
                                               self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength,
                                               RCCallButtonLength, RCCallButtonLength);
            [self layoutTextUnderImageButton:self.muteButton];
            self.muteButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.muteButton.hidden = YES;
        }

        if (callStatus == RCCallActive) {
            self.speakerButton.frame =
                CGRectMake(self.view.frame.size.width - RCCallHorizontalMargin - RCCallButtonLength,
                           self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength, RCCallButtonLength,
                           RCCallButtonLength);
            [self layoutTextUnderImageButton:self.speakerButton];
            self.speakerButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.speakerButton.hidden = YES;
        }

        if (callStatus == RCCallDialing) {
            self.hangupButton.frame =
                CGRectMake((self.view.frame.size.width - RCCallButtonLength) / 2,
                           self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength, RCCallButtonLength,
                           RCCallButtonLength);
            [self layoutTextUnderImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.hidden = YES;
        } else if (callStatus == RCCallIncoming || callStatus == RCCallRinging) {
            self.hangupButton.frame = CGRectMake(
                RCCallHorizontalMargin, self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength,
                RCCallButtonLength, RCCallButtonLength);
            [self layoutTextUnderImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.frame =
                CGRectMake(self.view.frame.size.width - RCCallHorizontalMargin - RCCallButtonLength,
                           self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength, RCCallButtonLength,
                           RCCallButtonLength);
            [self layoutTextUnderImageButton:self.acceptButton];
            self.acceptButton.hidden = NO;
        } else if (callStatus == RCCallActive) {
            self.hangupButton.frame =
                CGRectMake((self.view.frame.size.width - RCCallButtonLength) / 2,
                           self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength, RCCallButtonLength,
                           RCCallButtonLength);
            [self layoutTextUnderImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.hidden = YES;
        }

        self.cameraCloseButton.hidden = YES;
        self.cameraSwitchButton.hidden = YES;

    } else if (mediaType == RCCallMediaVideo && isMultiCall) {
        self.backgroundView.hidden = NO;

        self.blurView.hidden = YES;

        if (callStatus == RCCallActive) {
            self.minimizeButton.frame = CGRectMake(RCCallHorizontalMargin / 2, RCCallVerticalMargin,
                                                   RCCallButtonLength / 2, RCCallButtonLength / 2);
            self.minimizeButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.minimizeButton.hidden = YES;
        }

        if (callStatus == RCCallActive) {
            self.cameraSwitchButton.frame = CGRectMake(
                self.view.frame.size.width - RCCallHorizontalMargin / 2 - RCCallButtonLength - RCCallInsideMargin,
                RCCallVerticalMargin, RCCallButtonLength / 2, RCCallButtonLength / 2);
            self.cameraSwitchButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.cameraSwitchButton.hidden = YES;
        }

        if (callStatus == RCCallActive) {
            self.inviteUserButton.frame =
                CGRectMake(self.view.frame.size.width - RCCallHorizontalMargin / 2 - RCCallButtonLength / 2,
                           RCCallVerticalMargin, RCCallButtonLength / 2, RCCallButtonLength / 2);
            self.inviteUserButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.inviteUserButton.hidden = YES;
        }

        if (callStatus == RCCallActive) {
            self.timeLabel.frame =
                CGRectMake(RCCallHorizontalMargin, RCCallVerticalMargin + RCCallInsideMargin + RCCallLabelHeight,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
            self.timeLabel.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.timeLabel.hidden = YES;
        }

        if (callStatus == RCCallIncoming || callStatus == RCCallRinging) {
            self.tipsLabel.frame =
                CGRectMake(RCCallHorizontalMargin,
                           RCCallVerticalMargin * 2 + RCCallHeaderLength + RCCallInsideMargin * 2 + RCCallLabelHeight,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        } else if (callStatus == RCCallDialing) {
            self.tipsLabel.frame =
                CGRectMake(RCCallHorizontalMargin, RCCallVerticalMargin,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        } else {
            self.tipsLabel.frame =
                CGRectMake(RCCallHorizontalMargin,
                           self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength * 3.5 -
                               RCCallInsideMargin * 5 - RCCallLabelHeight,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        }
        self.tipsLabel.hidden = NO;

        if (callStatus == RCCallActive) {
            self.muteButton.frame = CGRectMake(RCCallHorizontalMargin,
                                               self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength,
                                               RCCallButtonLength, RCCallButtonLength);
            [self layoutTextUnderImageButton:self.muteButton];
            self.muteButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.muteButton.hidden = YES;
        }

        self.speakerButton.hidden = YES;

        if (callStatus == RCCallDialing) {
            self.hangupButton.frame =
                CGRectMake((self.view.frame.size.width - RCCallButtonLength) / 2,
                           self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength, RCCallButtonLength,
                           RCCallButtonLength);
            [self layoutTextUnderImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.hidden = YES;
        } else if (callStatus == RCCallIncoming || callStatus == RCCallRinging) {
            self.hangupButton.frame = CGRectMake(
                RCCallHorizontalMargin, self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength,
                RCCallButtonLength, RCCallButtonLength);
            [self layoutTextUnderImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.frame =
                CGRectMake(self.view.frame.size.width - RCCallHorizontalMargin - RCCallButtonLength,
                           self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength, RCCallButtonLength,
                           RCCallButtonLength);
            [self layoutTextUnderImageButton:self.acceptButton];
            self.acceptButton.hidden = NO;
        } else if (callStatus == RCCallActive) {
            self.hangupButton.frame =
                CGRectMake((self.view.frame.size.width - RCCallButtonLength) / 2,
                           self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength, RCCallButtonLength,
                           RCCallButtonLength);
            [self layoutTextUnderImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.hidden = YES;
        }

        if (callStatus == RCCallActive) {
            self.cameraCloseButton.frame =
                CGRectMake(self.view.frame.size.width - RCCallHorizontalMargin - RCCallButtonLength,
                           self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength, RCCallButtonLength,
                           RCCallButtonLength);
            [self layoutTextUnderImageButton:self.cameraCloseButton];
            self.cameraCloseButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.cameraCloseButton.hidden = YES;
        }
    }
}

- (void)layoutTextUnderImageButton:(UIButton *)button {
    [button.titleLabel setFont:[UIFont systemFontOfSize:12]];
    [button setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];

    button.titleEdgeInsets = UIEdgeInsetsMake(0, -button.imageView.frame.size.width,
                                              -button.imageView.frame.size.height - RCCallInsideMargin, 0);
    button.imageEdgeInsets = UIEdgeInsetsMake(-button.titleLabel.intrinsicContentSize.height - RCCallInsideMargin, 0, 0,
                                              -button.titleLabel.intrinsicContentSize.width);
}

#pragma mark - RCCallSessionDelegate
/*!
 通话已接通
 */
- (void)callDidConnect {
    [self callWillConnect];

    self.tipsLabel.text = @"";
    [self startActiveTimer];
    [self resetLayout:self.callSession.isMultiCall
            mediaType:self.callSession.mediaType
           callStatus:self.callSession.callStatus];
}

/*!
 通话已结束
 */
- (void)callDidDisconnect {
    [self callWillDisconnect];
    [RCCallKitUtility clearScreenForceOnStatus];

    if (self.callSession.connectedTime > 0) {
        self.tipsLabel.text = NSLocalizedStringFromTable(@"VoIPCallEnd", @"RongCloudKit", nil);
    } else {
        self.tipsLabel.text =
            [RCCallKitUtility getReadableStringForCallViewController:self.callSession.disconnectReason];
    }
    self.tipsLabel.textColor = [UIColor whiteColor];

    [self stopActiveTimer];
    [self resetLayout:self.callSession.isMultiCall
            mediaType:self.callSession.mediaType
           callStatus:self.callSession.callStatus];

    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [[RCCall sharedRCCall] dismissCallViewController:self];
    });
    [self removeProximityMonitoringObserver];
}

/*!
 对端正在振铃

 @param userId 对端的用户ID
 */
- (void)remoteUserDidRing:(NSString *)userId {
    [self resetLayout:self.callSession.isMultiCall
            mediaType:self.callSession.mediaType
           callStatus:self.callSession.callStatus];
}

/*!
 有用户被邀请加入通话

 @param userId    被邀请的用户ID
 @param mediaType 希望被邀请者选择的媒体类型
 */
- (void)remoteUserDidInvite:(NSString *)userId mediaType:(RCCallMediaType)mediaType {
    [self resetLayout:self.callSession.isMultiCall
            mediaType:self.callSession.mediaType
           callStatus:self.callSession.callStatus];
}

/*!
 有用户加入了通话

 @param userId    用户ID
 @param mediaType 用户的媒体类型
 */
- (void)remoteUserDidJoin:(NSString *)userId mediaType:(RCCallMediaType)mediaType {
    [self resetLayout:self.callSession.isMultiCall
            mediaType:self.callSession.mediaType
           callStatus:self.callSession.callStatus];
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
                    [self.callSession setVideoView:nil userId:[RCIMClient sharedRCIMClient].currentUserInfo.userId];
                    [self.callSession setVideoView:nil userId:self.callSession.targetId];
                    [self resetLayout:self.callSession.isMultiCall
                            mediaType:RCCallMediaAudio
                           callStatus:self.callSession.callStatus];
                }
            }
        } else if (self.callSession.mediaType == mediaType && mediaType == RCCallMediaVideo) {
            [self remoteUserDidDisableCamera:NO byUser:userId];
        }
    });
}

/*!
 对端用户关闭/打开了摄像头

 @param userId    用户ID
 @param muted     是否关闭camera
 */
- (void)remoteUserDidDisableCamera:(BOOL)muted byUser:(NSString *)userId {
    [self resetLayout:self.callSession.isMultiCall
            mediaType:self.callSession.mediaType
           callStatus:self.callSession.callStatus];
}

/*!
 有用户挂断

 @param userId 用户ID
 @param reason 挂断的原因
 */
- (void)remoteUserDidLeft:(NSString *)userId reason:(RCCallDisconnectReason)reason {
    [self resetLayout:self.callSession.isMultiCall
            mediaType:self.callSession.mediaType
           callStatus:self.callSession.callStatus];
}

/*!
 对方正在振铃，可以播放对应的彩铃
 */
- (void)shouldAlertForWaitingRemoteResponse {
    if ([UIApplication sharedApplication].applicationState == UIApplicationStateActive) {
        NSString *ringPath = [[[NSBundle mainBundle] pathForResource:@"RongCloud" ofType:@"bundle"]
            stringByAppendingPathComponent:@"voip/voip_calling_ring.mp3"];
        [self startPlayRing:ringPath];
        self.needPlayingAlertAfterForeground = NO;
    } else {
        self.needPlayingAlertAfterForeground = YES;
    }
}

/*!
 收到电话，可以播放铃声
 */
- (void)shouldRingForIncomingCall {
    if ([UIApplication sharedApplication].applicationState == UIApplicationStateActive) {
        NSString *ringPath = [[[NSBundle mainBundle] pathForResource:@"RongCloud" ofType:@"bundle"]
            stringByAppendingPathComponent:@"voip/voip_call.mp3"];
        [self startPlayRing:ringPath];
        self.needPlayingRingAfterForeground = NO;
    } else {
        self.needPlayingRingAfterForeground = YES;
    }
}

/*!
 停止播放铃声(通话接通或挂断)
 */
- (void)shouldStopAlertAndRing {
    self.needPlayingRingAfterForeground = NO;
    self.needPlayingAlertAfterForeground = NO;
    [self stopPlayRing];
}

/*!
 通话过程中的错误回调

 @param error 错误码

 @warning 如果是不可恢复的错误，SDK会挂断电话并回调callDidDisconnect。
 */
- (void)errorDidOccur:(RCCallErrorCode)error {
    if ([self respondsToSelector:@selector(tipsWillShow:)]) {
        if (![self tipsWillShow:error]) {
            return;
        }
    }
    //    self.tipsLabel.text = [NSString stringWithFormat:@"错误码：%ld",
    //    (long)error];
}

/*!
 当前通话网络状态的回调，该回调方法每两秒触发一次

 @param txQuality   上行网络质量
 @param rxQuality   下行网络质量
 */
- (void)networkTxQuality:(RCCallQuality)txQuality rxQuality:(RCCallQuality)rxQuality {
    //  NSLog(@"networkTxQuality, %d, %d", txQuality, rxQuality);
}

#pragma mark - telephony
- (void)registerTelephonyEvent {
    self.callCenter = [[CTCallCenter alloc] init];
    __weak __typeof(self) weakSelf = self;
    self.callCenter.callEventHandler = ^(CTCall *call) {
        if ([call.callState isEqualToString:CTCallStateConnected]) {
            [weakSelf.callSession hangup];
        }
    };
}

#pragma mark - proximity
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

#pragma mark - outside callback
- (void)callWillConnect {
}

- (void)callWillDisconnect {
}

- (BOOL)tipsWillShow:(RCCallErrorCode)warning {
    return YES;
}

- (void)didTapAcceptButton {
}

- (void)didTapHangupButton {
}

- (void)didTapMuteButton {
}

- (void)didTapCameraCloseButton {
}

- (void)didTapCameraSwitchButton {
}

- (void)didTapSpeakerButton {
}

- (void)didTapMinimizeButton {
}

- (void)didTapInviteUserButton {
}

@end
