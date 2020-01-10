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
#import "RCCXCall.h"
#import <AVFoundation/AVFoundation.h>
#import <CoreTelephony/CTCall.h>
#import <CoreTelephony/CTCallCenter.h>
#import "WhiteBoardWebView.h"
#import "KxCallMenu.h"

NSNotificationName const RCCallNewSessionCreationNotification = @"RCCallNewSessionCreation Notification";

@interface RCCallBaseViewController ()
{
    UIImage *signalImage0, *signalImage1, *signalImage2, *signalImage3, *signalImage4, *signalImage5;
    WhiteBoardWebView *whiteBoardWebView;
    dispatch_semaphore_t sem;
    dispatch_queue_t queue;
    BOOL hangupButtonClick;
}

@property(nonatomic, strong) NSTimer *activeTimer;
@property(nonatomic, strong) AVAudioPlayer *audioPlayer;
@property(nonatomic, assign) BOOL needPlayingAlertAfterForeground;
@property(nonatomic, assign) BOOL needPlayingRingAfterForeground;
@property(nonatomic, strong) CTCallCenter *callCenter;
@property(nonatomic, strong) UIView *topGradientView;
@property(nonatomic, strong) UIView *bottomGradientView;
@property(nonatomic, strong) UIAlertController *alertController;
@property(nonatomic, assign) BOOL backCamera;
@property(nonatomic, weak) NSTimer *vibrateTimer;

@end

@implementation RCCallBaseViewController
#pragma mark - init
- (instancetype)initWithIncomingCall:(RCCallSession *)callSession {
    self = [super init];
    if (self) {
        _callSession = callSession;
        _backCamera = NO;
        [[NSNotificationCenter defaultCenter] postNotificationName:RCCallNewSessionCreationNotification object:_callSession];
        sem = dispatch_semaphore_create(1);
        queue = dispatch_queue_create("AnswerQueue", DISPATCH_QUEUE_SERIAL);
        [self registerForegroundNotification];
        [_callSession addDelegate:self];
        [RCCallKitUtility setScreenForceOn];
        [_callSession setMinimized:NO];
        self.needPlayingRingAfterForeground = YES;
        hangupButtonClick = NO;
    }
    return self;
}

- (instancetype)initWithOutgoingCall:(RCConversationType)conversationType
                            targetId:(NSString *)targetId
                           mediaType:(RCCallMediaType)mediaType
                          userIdList:(NSArray *)userIdList {
    self = [super init];
    if (self) {
        [self willChangeValueForKey:@"callSession"];
        _callSession = [[RCCallClient sharedRCCallClient] startCall:conversationType
                                                           targetId:targetId
                                                                 to:userIdList
                                                          mediaType:mediaType
                                                    sessionDelegate:self
                                                              extra:nil];
        [[NSNotificationCenter defaultCenter] postNotificationName:RCCallNewSessionCreationNotification object:_callSession];
        [self didChangeValueForKey:@"callSession"];
        sem = dispatch_semaphore_create(1);
        queue = dispatch_queue_create("AnswerQueue", DISPATCH_QUEUE_SERIAL);
        if (mediaType == RCCallMediaAudio) {
            if (conversationType == ConversationType_PRIVATE) {
                [[RCCXCall sharedInstance] startCall:targetId];
            } else {
                NSString *str = @"";
                for (NSString *userId in userIdList) {
                    str = [str stringByAppendingFormat:@"%@:::", userId];
                }
                str = [str substringToIndex:str.length - 3];
                [[RCCXCall sharedInstance] startCall:[str copy]];
            }
        }
        [self registerForegroundNotification];
        [RCCallKitUtility setScreenForceOn];
        [_callSession setMinimized:NO];
        hangupButtonClick = NO;
        
    }
    return self;
}

- (instancetype)initWithActiveCall:(RCCallSession *)callSession {
    self = [super init];
    if (self) {
        _callSession = callSession;
        sem = dispatch_semaphore_create(1);
        queue = dispatch_queue_create("AnswerQueue", DISPATCH_QUEUE_SERIAL);
        [self registerForegroundNotification];
        [_callSession addDelegate:self];
        [_callSession setMinimized:YES];
        hangupButtonClick = NO;
    }
    return self;
}

- (void)registerForegroundNotification {
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(appDidBecomeActive)
                                                 name:UIApplicationDidBecomeActiveNotification
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleAudioRouteChange:) name:AVAudioSessionRouteChangeNotification object:nil];
}

- (void)dealloc {
    [self stopPlayRing];
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
        [self checkApplicationStateAndAlert];
    } else if (self.needPlayingRingAfterForeground) {
        [self shouldRingForIncomingCall];
    }
}

- (void)triggerVibrate {
    [self.vibrateTimer invalidate];
    self.vibrateTimer = nil;
    
    self.vibrateTimer = [NSTimer scheduledTimerWithTimeInterval:2.f target:self selector:@selector(triggerVibrateAction) userInfo:nil repeats:YES];
}

- (void)triggerVibrateAction
{
    NSInteger checker = [RCCallKitUtility compareVersion:[UIDevice currentDevice].systemVersion toVersion:@"9.0"];
    if (checker >= 0) {
        AudioServicesPlaySystemSoundWithCompletion(kSystemSoundID_Vibrate, ^{});
    }
    else{
        AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
    }
}

- (void)startPlayRing:(NSString *)ringPath {
    if (ringPath) {
        if (self.audioPlayer) {
            [self stopPlayRing];
        }
        AVAudioSession *audioSession = [AVAudioSession sharedInstance];
        if (self.callSession.callStatus == RCCallDialing) {
            [audioSession setCategory:AVAudioSessionCategoryPlayAndRecord withOptions:AVAudioSessionCategoryOptionAllowBluetooth | AVAudioSessionCategoryOptionAllowBluetoothA2DP error:nil];
        } else {
            //默认情况按静音或者锁屏键会静音
            [audioSession setCategory:AVAudioSessionCategorySoloAmbient error:nil];
            [self triggerVibrate];
        }
        
        [audioSession setActive:YES error:nil];

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
    if (self.vibrateTimer) {
        [self.vibrateTimer invalidate];
        self.vibrateTimer = nil;
    }
    
    if (self.audioPlayer) {
        [self.audioPlayer stop];
        self.audioPlayer = nil;
        //设置铃声停止后恢复其他app的声音
        [[AVAudioSession sharedInstance] setActive:YES withOptions:AVAudioSessionSetActiveOptionNotifyOthersOnDeactivation
                                             error:nil];
    }
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.backgroundView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, self.view.bounds.size.width, self.view.bounds.size.height)];
    self.backgroundView.backgroundColor = [UIColor colorWithRed:20/255.0 green:28/255.0 blue:36/255.0 alpha:1/1.0];
    [self.view addSubview:self.backgroundView];
    self.backgroundView.hidden = NO;

    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onOrientationChanged:)
                                                 name:UIApplicationDidChangeStatusBarOrientationNotification
                                               object:nil];

    [self registerTelephonyEvent];
    [self addProximityMonitoringObserver];

//    UIVisualEffect *blurEffect = [UIBlurEffect effectWithStyle:UIBlurEffectStyleDark];
//    self.blurView = [[UIVisualEffectView alloc] initWithEffect:blurEffect];
    self.blurView = [[UIView alloc] init];
    self.blurView.frame = self.view.frame;
 
    self.blurView.backgroundColor = [UIColor colorWithRed:20/255.0 green:28/255.0 blue:36/255.0 alpha:1/1.0];
    self.blurView.alpha = 0.9;
    
    [self.view addSubview:self.blurView];
    self.blurView.hidden = YES;
}

- (void)onOrientationChanged:(NSNotification *)notification {
    [self resetLayout:self.callSession.isMultiCall
            mediaType:self.callSession.mediaType
           callStatus:self.callSession.callStatus];
}

- (void)checkApplicationStateAndAlert {
    if (self.callSession.callStatus == RCCallDialing) {
        if ([UIApplication sharedApplication].applicationState == UIApplicationStateActive) {
            NSString *ringPath = [[[NSBundle mainBundle] pathForResource:@"RongCloud" ofType:@"bundle"]
                                  stringByAppendingPathComponent:@"voip/voip_calling_ring.mp3"];
            [self startPlayRing:ringPath];
            self.needPlayingAlertAfterForeground = NO;
        } else {
            self.needPlayingAlertAfterForeground = YES;
        }
    }
}
- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    //呼出后立刻振铃
    if (self.callSession.callStatus == RCCallDialing) {
        [self performSelector:@selector(checkApplicationStateAndAlert) withObject:nil afterDelay:1];
    }

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
        _minimizeButton.imageView.contentMode = UIViewContentModeScaleToFill;
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
        [_inviteUserButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/addmenu.png"]
                           forState:UIControlStateNormal];
        [_inviteUserButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/addmenu.png"]
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
        _timeLabel.layer.shadowOpacity = 0.8;
        _timeLabel.layer.shadowRadius = 3.0;
        _timeLabel.layer.shadowColor = [UIColor blackColor].CGColor;
        _timeLabel.layer.shadowOffset = CGSizeMake(0, 1);
        _timeLabel.font = [UIFont fontWithName:@"PingFangSC-Regular" size:13];
        _timeLabel.textAlignment = NSTextAlignmentCenter;

        [self.view addSubview:_timeLabel];
        _timeLabel.hidden = YES;
    }
    return _timeLabel;
}

- (void)startActiveTimer {
    [_activeTimer invalidate];
    _activeTimer = nil;
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
    if (hangupButtonClick) return;
    long sec = ([[NSDate date] timeIntervalSince1970] * 1000 - self.callSession.connectedTime) / 1000;
    self.timeLabel.text = [RCCallKitUtility getReadableStringForTime:sec];
    
    if (sec >= 3600 && self.timeLabel.frame.size.width != 80)
    {
        self.timeLabel.frame = CGRectMake(self.view.frame.size.width / 2 - 114.0 / 2, RCCallMiniButtonTopMargin + RCCallMiniLabelHeight + RCCallTimeTopMargin + RCCallStatusBarHeight,
                                          100.0, RCCallTimeLabelHeight);
        self.timeLabel.textAlignment = NSTextAlignmentRight;
        self.signalImageView.frame = CGRectMake(self.timeLabel.frame.origin.x + self.timeLabel.frame.size.width + 4.0f,  self.timeLabel.frame.origin.y,
                                                RCCallTopMargin - 5.0,  RCCallTimeLabelHeight);
    }
}

- (UILabel *)tipsLabel {
    if (!_tipsLabel) {
        _tipsLabel = [[UILabel alloc] init];
        _tipsLabel.backgroundColor = [UIColor clearColor];
        _tipsLabel.textColor = [UIColor whiteColor];
        _tipsLabel.font = [UIFont systemFontOfSize:18];
        _tipsLabel.textAlignment = NSTextAlignmentCenter;
        _tipsLabel.layer.shadowOpacity = 0.8;
        _tipsLabel.layer.shadowRadius = 3.0;
        _tipsLabel.layer.shadowColor = [UIColor blackColor].CGColor;
        _tipsLabel.layer.shadowOffset = CGSizeMake(0, 1);
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
        [_muteButton addTarget:self action:@selector(muteButtonClicked) forControlEvents:UIControlEventTouchUpInside];
        [_muteButton setSelected:self.callSession.isMuted];

        _muteButton.titleLabel.layer.shadowOpacity = 0.8;
        _muteButton.titleLabel.layer.shadowRadius = 3.0;
        _muteButton.titleLabel.layer.shadowColor = [UIColor blackColor].CGColor;
        _muteButton.titleLabel.layer.shadowOffset = CGSizeMake(0, 1);
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

- (UIButton *)addButton
{
    if (!_addButton) {
        _addButton = [[UIButton alloc] init];
        [_addButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/addmenu.png"] forState:UIControlStateNormal];
        [_addButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/addmenu.png"] forState:UIControlStateHighlighted];
        [_addButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/addmenu.png"] forState:UIControlStateSelected];
        //        [_addButton setTitle:NSLocalizedStringFromTable(@"VoIPCallMute", @"RongCloudKit", nil) forState:UIControlStateNormal];
        //        [_addButton setSelected:self.callSession.isMuted];
        [_addButton addTarget:self action:@selector(inviteUserButtonClicked) forControlEvents:UIControlEventTouchUpInside];
        
        [self.view addSubview:_addButton];
        _addButton.hidden = YES;
    }
    return _addButton;
}

- (void)addButtonClicked
{
    KxCallMenuItem *addMemberItem = [KxCallMenuItem menuItem:@"添加成员" image:[RCCallKitUtility imageFromVoIPBundle:@"voip/add.png"] target:self action:@selector(inviteUserButtonClicked)];
    KxCallMenuItem *whiteBoardItem = [KxCallMenuItem menuItem:@"白板" image:[RCCallKitUtility imageFromVoIPBundle:@"voip/whiteboard.png"] target:self action:@selector(whiteBoardButtonClicked)];
    KxCallMenuItem *handupItem = [KxCallMenuItem menuItem:@"举手发言" image:[RCCallKitUtility imageFromVoIPBundle:@"voip/handup.png"] target:self action:@selector(handUpButtonClicked)];
    
    NSMutableArray *menuItems = [NSMutableArray new];
    [menuItems addObject:addMemberItem];
    
    UIBarButtonItem *rightBarButton = self.navigationItem.rightBarButtonItems[1];
    CGRect targetFrame = rightBarButton.customView.frame;
    targetFrame.origin.y = targetFrame.origin.y + 15;
    [KxCallMenu setTintColor:[UIColor blackColor]];
    [KxCallMenu setTitleFont:[UIFont systemFontOfSize:16]];
    [KxCallMenu showMenuInView:_addButton.superview fromRect:CGRectMake([UIScreen mainScreen].bounds.size.width - 80, 48, 0, 0) menuItems:menuItems];
}

- (UIButton *)handUpButton
{
    if (!_handUpButton) {
        _handUpButton = [[UIButton alloc] init];
        [_handUpButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/handup.png"] forState:UIControlStateNormal];
        [_handUpButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/handup.png"] forState:UIControlStateHighlighted];
        [_handUpButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/handup.png"] forState:UIControlStateSelected];
//        [_handUpButton setTitle:NSLocalizedStringFromTable(@"VoIPCallMute", @"RongCloudKit", nil) forState:UIControlStateNormal];
//        [_handUpButton setSelected:self.callSession.isMuted];
        [_handUpButton addTarget:self action:@selector(handUpButtonClicked) forControlEvents:UIControlEventTouchUpInside];
        
        [self.view addSubview:_handUpButton];
        _handUpButton.hidden = YES;
    }
    return _handUpButton;
}

- (void)handUpButtonClicked
{
}

- (UIButton *)whiteBoardButton
{
    if (!_whiteBoardButton) {
        _whiteBoardButton = [[UIButton alloc] init];
        [_whiteBoardButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/whiteboard.png"] forState:UIControlStateNormal];
        [_whiteBoardButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/whiteboard.png"] forState:UIControlStateHighlighted];
        [_whiteBoardButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/whiteboard.png"] forState:UIControlStateSelected];
//        [_whiteBoardButton setTitle:NSLocalizedStringFromTable(@"VoIPCallMute", @"RongCloudKit", nil) forState:UIControlStateNormal];
        //        [_whiteBoardButton setSelected:self.callSession.isMuted];
        [_whiteBoardButton addTarget:self action:@selector(whiteBoardButtonClicked) forControlEvents:UIControlEventTouchUpInside];
        
        [self.view addSubview:_whiteBoardButton];
        _whiteBoardButton.hidden = YES;
    }
    return _whiteBoardButton;
}

- (void)whiteBoardButtonClicked
{
}

- (UIImageView *)signalImageView
{
    if (!_signalImageView) {
        _signalImageView = [[UIImageView alloc] init];
        _signalImageView.image = [RCCallKitUtility imageFromVoIPBundle:@"voip/signal5.png"];
        [self.view addSubview:_signalImageView];
        
        signalImage0 = [RCCallKitUtility imageFromVoIPBundle:@"voip/signal0.png"];
        signalImage1 = [RCCallKitUtility imageFromVoIPBundle:@"voip/signal1.png"];
        signalImage2 = [RCCallKitUtility imageFromVoIPBundle:@"voip/signal2.png"];
        signalImage3 = [RCCallKitUtility imageFromVoIPBundle:@"voip/signal3.png"];
        signalImage4 = [RCCallKitUtility imageFromVoIPBundle:@"voip/signal4.png"];
        signalImage5 = [RCCallKitUtility imageFromVoIPBundle:@"voip/signal5.png"];
    }
    return _signalImageView;
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

        [_speakerButton addTarget:self
                           action:@selector(speakerButtonClicked)
                 forControlEvents:UIControlEventTouchUpInside];
        _speakerButton.titleLabel.layer.shadowOpacity = 0.8;
        _speakerButton.titleLabel.layer.shadowRadius = 3.0;
        _speakerButton.titleLabel.layer.shadowColor = [UIColor blackColor].CGColor;
        _speakerButton.titleLabel.layer.shadowOffset = CGSizeMake(0, 1);
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
        _acceptButton.titleLabel.layer.shadowOpacity = 0.8;
        _acceptButton.titleLabel.layer.shadowRadius = 3.0;
        _acceptButton.titleLabel.layer.shadowColor = [UIColor blackColor].CGColor;
        _acceptButton.titleLabel.layer.shadowOffset = CGSizeMake(0, 1);
        
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
        _hangupButton.titleLabel.layer.shadowOpacity = 0.8;
        _hangupButton.titleLabel.layer.shadowRadius = 3.0;
        _hangupButton.titleLabel.layer.shadowColor = [UIColor blackColor].CGColor;
        _hangupButton.titleLabel.layer.shadowOffset = CGSizeMake(0, 1);
        [self.view addSubview:_hangupButton];
        _hangupButton.hidden = YES;
    }
    return _hangupButton;
}

- (void)hangupButtonClicked {
    hangupButtonClick = YES;
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
        _cameraCloseButton.titleLabel.layer.shadowOpacity = 0.8;
        _cameraCloseButton.titleLabel.layer.shadowRadius = 3.0;
        _cameraCloseButton.titleLabel.layer.shadowColor = [UIColor blackColor].CGColor;
        _cameraCloseButton.titleLabel.layer.shadowOffset = CGSizeMake(0, 1);
        
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
            [_cameraSwitchButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/switchcamera.png"]
                                 forState:UIControlStateNormal];
            [_cameraSwitchButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/switchcamera.png"]
                                 forState:UIControlStateHighlighted];
            [_cameraSwitchButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/switchcamera.png"]
                                 forState:UIControlStateSelected];
        }

        [_cameraSwitchButton addTarget:self
                                action:@selector(cameraSwitchButtonClicked)
                      forControlEvents:UIControlEventTouchUpInside];

        [self.view addSubview:_cameraSwitchButton];
        _cameraSwitchButton.hidden = YES;
        [_cameraSwitchButton setSelected:_backCamera];
    }
    return _cameraSwitchButton;
}

- (void)cameraSwitchButtonClicked {
    [self didTapCameraSwitchButton];
    
    if ([self.callSession switchCameraMode])
    {
        _backCamera = !_backCamera;
    }
    //[_cameraSwitchButton setSelected:_backCamera];
}

- (UIView *)topGradientView {
    if (!_topGradientView) {
        _topGradientView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, RCCallTopGGradientHeight)];
        _topGradientView.backgroundColor = [UIColor clearColor];
        [_topGradientView.layer insertSublayer:[self getGradientLayerWithFrame:CGRectMake(0, 0, self.view.frame.size.width, RCCallTopGGradientHeight) direction:YES] atIndex:0];
        
        [self.view insertSubview:_topGradientView aboveSubview:self.backgroundView];
        _topGradientView.hidden = YES;
    }
    return _topGradientView;
}

- (UIView *)bottomGradientView {
    if (!_bottomGradientView) {
        _bottomGradientView = [[UIView alloc] initWithFrame:CGRectMake(0, self.view.frame.size.height - RCCallBottomGradientHeight, self.view.frame.size.width, RCCallBottomGradientHeight)];
        _bottomGradientView.backgroundColor = [UIColor clearColor];
        _bottomGradientView.userInteractionEnabled = NO;
        [_bottomGradientView.layer insertSublayer:[self getGradientLayerWithFrame:CGRectMake(0, 0, self.view.frame.size.width, RCCallBottomGradientHeight) direction:NO] atIndex:0];
        
        [self.view insertSubview:_bottomGradientView aboveSubview:self.backgroundView];
        _bottomGradientView.hidden = YES;
    }
    return _bottomGradientView;
}

- (CAGradientLayer *)getGradientLayerWithFrame:(CGRect)frame direction:(BOOL)isUpToDown{
    
    //为透明度设置渐变效果
    UIColor *colorBegin = [UIColor colorWithRed:(0/255.0)  green:(0/255.0)  blue:(0/255.0)  alpha:0.3];
    UIColor *colorEnd = [UIColor colorWithRed:(0/255.0)  green:(0/255.0)  blue:(0/255.0)  alpha:0.0];
    NSArray *colors = [NSArray arrayWithObjects:(id)colorBegin.CGColor, (id)colorEnd.CGColor, nil];
    CAGradientLayer *gradient = [CAGradientLayer layer];
    //设置开始和结束位置(设置渐变的方向)
    if (isUpToDown) {
        gradient.startPoint = CGPointMake(0, 0);
        gradient.endPoint = CGPointMake(0, 1);
    }else {
        gradient.startPoint = CGPointMake(0, 1);
        gradient.endPoint = CGPointMake(0, 0);
    }
    gradient.colors = colors;
    gradient.frame = frame;
    return gradient;
}

#pragma mark - layout
- (void)resetLayout:(BOOL)isMultiCall mediaType:(RCCallMediaType)mediaType callStatus:(RCCallStatus)callStatus {
    if (mediaType == RCCallMediaAudio && !isMultiCall) {
        self.backgroundView.backgroundColor=[UIColor colorWithRed:20/255.0 green:28/255.0 blue:36/255.0 alpha:1/1.0];
        self.backgroundView.hidden = NO;
        self.topGradientView.hidden = YES;
        self.bottomGradientView.hidden = YES;

        self.blurView.hidden = NO;

        if (callStatus == RCCallDialing) {
            self.minimizeButton.frame = CGRectMake(RCCallHorizontalMargin, RCCallMiniButtonTopMargin + RCCallStatusBarHeight, RCCallMiniButtonLength, RCCallMiniButtonLength);
            self.minimizeButton.hidden = NO;
        }else if (callStatus == RCCallActive) {
            self.minimizeButton.frame = CGRectMake(RCCallHorizontalMargin, RCCallMiniButtonTopMargin + RCCallStatusBarHeight, RCCallMiniButtonLength, RCCallMiniButtonLength);
            self.minimizeButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.minimizeButton.hidden = YES;
        }

        self.inviteUserButton.hidden = YES;

        // header orgin y = RCCallVerticalMargin * 3
        if (callStatus == RCCallActive) {
            self.timeLabel.frame =
                CGRectMake(RCCallHorizontalMargin,
                           RCCallTopGGradientHeight + RCCallHeaderLength + RCCallTopMargin + RCCallLabelHeight + RCCallTimeTopMargin + RCCallStatusBarHeight,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallTimeLabelHeight);
            self.timeLabel.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.timeLabel.hidden = YES;
        }

        if (callStatus == RCCallHangup) {
            self.tipsLabel.frame =
                CGRectMake(RCCallHorizontalMargin,
                           self.view.frame.size.height - RCCallButtonBottomMargin * 5 - RCCallExtraSpace,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        } else if (callStatus == RCCallActive) {
            self.tipsLabel.frame = CGRectMake(
                RCCallHorizontalMargin,
                RCCallButtonLength - 3.0f + RCCallStatusBarHeight,
                self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        } else {
            self.tipsLabel.frame =
            CGRectMake(RCCallHorizontalMargin,
                       self.view.frame.size.height * 0.54,
                       self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        }
        self.tipsLabel.hidden = NO;
        
        if (callStatus == RCCallActive) {
            self.muteButton.frame = CGRectMake(RCCallHorizontalMiddleMargin,
                                               self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2) - RCCallCustomButtonLength - RCCallExtraSpace,
                                               RCCallCustomButtonLength, RCCallCustomButtonLength);
            [self layoutTextUnderImageButton:self.muteButton];
            self.muteButton.hidden = NO;
            self.muteButton.enabled = YES;
        } else if (callStatus == RCCallDialing) {
            self.muteButton.frame = CGRectMake(RCCallHorizontalMiddleMargin,
                                               self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2) - RCCallCustomButtonLength - RCCallExtraSpace,
                                               RCCallCustomButtonLength, RCCallCustomButtonLength);
            [self layoutTextUnderImageButton:self.muteButton];
            self.muteButton.hidden = NO;
            self.muteButton.enabled = NO;
        } else if (callStatus != RCCallHangup) {
            self.muteButton.hidden = YES;
        }

        if (callStatus == RCCallActive){
            self.speakerButton.frame =
            CGRectMake(self.view.frame.size.width - RCCallHorizontalMiddleMargin - RCCallCustomButtonLength,
                       self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2) - RCCallCustomButtonLength - RCCallExtraSpace, RCCallCustomButtonLength,
                       RCCallCustomButtonLength);
            [self layoutTextUnderImageButton:self.speakerButton];
            self.speakerButton.hidden = NO;
            [self.speakerButton setSelected:self.callSession.speakerEnabled];
            if ([self isHeadsetPluggedIn])
                [self reloadSpeakerRoute:NO];
        } else if (callStatus == RCCallDialing) {
            self.speakerButton.frame =
                CGRectMake(self.view.frame.size.width - RCCallHorizontalMiddleMargin - RCCallCustomButtonLength,
                           self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2) - RCCallCustomButtonLength - RCCallExtraSpace, RCCallCustomButtonLength,
                           RCCallCustomButtonLength);
            [self layoutTextUnderImageButton:self.speakerButton];
            self.speakerButton.hidden = NO;
            if ([self isHeadsetPluggedIn])
            [self reloadSpeakerRoute:NO];
        } else if (callStatus != RCCallHangup) {
            self.speakerButton.hidden = YES;
        }

        if (callStatus == RCCallDialing) {
            self.hangupButton.frame =
                CGRectMake((self.view.frame.size.width - RCCallButtonLength) / 2,
                           self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2 + RCCallCustomButtonLength / 2 + 1.25f) - RCCallButtonLength/2 - RCCallExtraSpace, RCCallButtonLength,
                           RCCallButtonLength);
            [self layoutTextUnderBigImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.hidden = YES;
        } else if (callStatus == RCCallIncoming || callStatus == RCCallRinging) {
            self.hangupButton.frame = CGRectMake(
                RCCallHorizontalBigMargin, self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2 + RCCallCustomButtonLength / 2 + 1.25f) - RCCallButtonLength/2 - RCCallExtraSpace,
                RCCallButtonLength, RCCallButtonLength);
            [self layoutTextUnderImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.frame =
                CGRectMake(self.view.frame.size.width - RCCallHorizontalBigMargin - RCCallButtonLength,
                           self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2 + RCCallCustomButtonLength / 2 + 1.25f) - RCCallButtonLength/2 - RCCallExtraSpace, RCCallButtonLength,
                           RCCallButtonLength);
            [self layoutTextUnderImageButton:self.acceptButton];
            self.acceptButton.hidden = NO;
        } else if (callStatus == RCCallActive) {
            self.hangupButton.frame =
                CGRectMake((self.view.frame.size.width - RCCallButtonLength) / 2,
                           self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2 + RCCallCustomButtonLength / 2 + 1.25f) - RCCallButtonLength/2 - RCCallExtraSpace, RCCallButtonLength,
                           RCCallButtonLength);
            [self layoutTextUnderBigImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.hidden = YES;
        }

        self.cameraCloseButton.hidden = YES;
        self.cameraSwitchButton.hidden = YES;

    } else if (mediaType == RCCallMediaVideo && !isMultiCall) {
        self.backgroundView.hidden = NO;

        if (callStatus == RCCallDialing || callStatus == RCCallIncoming || callStatus == RCCallRinging  || callStatus == RCCallHangup) {
            self.blurView.hidden = NO;
        }else{
            self.blurView.hidden = YES;
        }
        
        if (callStatus == RCCallDialing) {
            self.minimizeButton.frame = CGRectMake(RCCallHorizontalMargin, RCCallMiniButtonTopMargin + RCCallStatusBarHeight, RCCallMiniButtonLength, RCCallMiniButtonLength);
            self.minimizeButton.hidden = NO;
        }else if (callStatus == RCCallActive) {
            self.minimizeButton.frame = CGRectMake(RCCallHorizontalMargin, RCCallMiniButtonTopMargin + RCCallStatusBarHeight,
                                                   RCCallMiniButtonLength, RCCallMiniButtonLength);
            self.minimizeButton.hidden = NO;
            self.topGradientView.hidden = NO;
            self.bottomGradientView.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.minimizeButton.hidden = YES;
            self.topGradientView.hidden = YES;
            self.bottomGradientView.hidden = YES;
        }

        self.inviteUserButton.hidden = YES;

        if (callStatus == RCCallActive) {
            self.timeLabel.frame =
                CGRectMake(RCCallHorizontalMargin, RCCallMiniButtonTopMargin + RCCallMiniLabelHeight + RCCallTimeTopMargin + RCCallStatusBarHeight,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2,RCCallTimeLabelHeight);
            self.timeLabel.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.timeLabel.hidden = YES;
        }

        // header orgin y = RCCallVerticalMargin * 3
        if (callStatus == RCCallActive) {
            self.tipsLabel.frame =
                CGRectMake(RCCallHorizontalMargin,
                           self.view.frame.size.height - RCCallButtonBottomMargin * 3 - RCCallButtonLength -RCCallExtraSpace,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        } else if (callStatus == RCCallDialing) {
            self.tipsLabel.frame = CGRectMake(RCCallHorizontalMargin,
                                               self.view.frame.size.height * 0.54, self.view.frame.size.width - RCCallHorizontalMargin * 2 , RCCallLabelHeight);
            
        } else if (callStatus == RCCallIncoming || callStatus == RCCallRinging) {
            self.tipsLabel.frame =
            CGRectMake(RCCallHorizontalMargin,
                        self.view.frame.size.height * 0.54,
                       self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        } else if (callStatus == RCCallHangup) {
            self.tipsLabel.frame = CGRectMake(
                RCCallHorizontalMargin,
                self.view.frame.size.height - RCCallButtonBottomMargin * 3 - RCCallButtonLength -RCCallExtraSpace,
                self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        }
        self.tipsLabel.hidden = NO;

        if (callStatus == RCCallDialing) {
            self.muteButton.frame = CGRectMake(RCCallHorizontalMiddleMargin,
                                               self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2) - RCCallCustomButtonLength - RCCallExtraSpace,
                                               RCCallCustomButtonLength, RCCallCustomButtonLength);
            [self layoutTextUnderImageButton:self.muteButton];
            self.muteButton.hidden = NO;
            self.muteButton.enabled = NO;
        }else if (callStatus == RCCallActive) {
            self.muteButton.frame = CGRectMake(RCCallHorizontalMiddleMargin,
                                               self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2) - RCCallCustomButtonLength - RCCallExtraSpace,
                                               RCCallCustomButtonLength, RCCallCustomButtonLength);
            [self layoutTextUnderImageButton:self.muteButton];
            self.muteButton.hidden = NO;
            self.muteButton.enabled = YES;
        }else if (callStatus != RCCallHangup) {
            self.muteButton.hidden = YES;
            self.muteButton.enabled = NO;
        }

        if (callStatus == RCCallDialing) {
            self.speakerButton.frame = CGRectMake(self.view.frame.size.width -RCCallHorizontalMiddleMargin - RCCallCustomButtonLength,
                                               self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2) - RCCallCustomButtonLength - RCCallExtraSpace,
                                               RCCallCustomButtonLength, RCCallCustomButtonLength);
            [self layoutTextUnderImageButton:self.speakerButton];
            self.speakerButton.hidden = NO;
            [self setSpeakerEnable:NO];
            if ([self isHeadsetPluggedIn])
                [self reloadSpeakerRoute:NO];
        }else if (callStatus != RCCallHangup) {
            self.speakerButton.hidden = YES;
        }

        if (callStatus == RCCallDialing) {
            self.hangupButton.frame =
            CGRectMake((self.view.frame.size.width - RCCallButtonLength) / 2,
                       self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2 + RCCallCustomButtonLength / 2 + 1.25f) - RCCallButtonLength/2 - RCCallExtraSpace, RCCallButtonLength,
                       RCCallButtonLength);
            [self layoutTextUnderBigImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.hidden = YES;
        } else if (callStatus == RCCallIncoming || callStatus == RCCallRinging) {
            self.hangupButton.frame = CGRectMake(
                                                 RCCallHorizontalBigMargin, self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2 + RCCallCustomButtonLength / 2 + 1.25f) - RCCallButtonLength/2 - RCCallExtraSpace,
                                                 RCCallButtonLength, RCCallButtonLength);
            [self layoutTextUnderImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.frame =
            CGRectMake(
                       self.view.frame.size.width - RCCallHorizontalBigMargin - RCCallButtonLength, self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2 + RCCallCustomButtonLength / 2 + 1.25f) - RCCallButtonLength/2 - RCCallExtraSpace,
                       RCCallButtonLength, RCCallButtonLength);
            [self layoutTextUnderImageButton:self.acceptButton];
            self.acceptButton.hidden = NO;
        } else if (callStatus == RCCallActive) {
            self.hangupButton.frame =
            CGRectMake((self.view.frame.size.width - RCCallButtonLength) / 2,
                       self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2 + RCCallCustomButtonLength / 2 + 1.25f) - RCCallButtonLength/2 - RCCallExtraSpace, RCCallButtonLength,
                       RCCallButtonLength);
            [self layoutTextUnderBigImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.hidden = YES;
        }

        if (callStatus == RCCallActive) {
            self.cameraSwitchButton.frame = CGRectMake(self.view.frame.size.width -RCCallHorizontalMiddleMargin - RCCallCustomButtonLength,
                                                      self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2) - RCCallCustomButtonLength - RCCallExtraSpace,
                                                      RCCallCustomButtonLength, RCCallCustomButtonLength);
            [self layoutTextUnderImageButton:self.cameraSwitchButton];
            self.cameraSwitchButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.cameraSwitchButton.hidden = YES;
        }

        if (callStatus == RCCallActive) {
            self.cameraCloseButton.frame =
            CGRectMake(self.view.frame.size.width - RCCallHorizontalMiddleMargin - RCCallCustomButtonLength,
                       self.view.frame.size.height - RCCallButtonBottomMargin * 4 - RCCallCustomButtonLength * 2 - RCCallHorizontalMargin - RCCallExtraSpace, RCCallCustomButtonLength,
                       RCCallCustomButtonLength);
            [self layoutTextUnderImageButton:self.cameraCloseButton];
            self.cameraCloseButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.cameraCloseButton.hidden = YES;
        }
    } else if (mediaType == RCCallMediaAudio && isMultiCall) {
        self.backgroundView.backgroundColor = [UIColor colorWithRed:20/255.0 green:28/255.0 blue:36/255.0 alpha:1/1.0];
        self.backgroundView.hidden = NO;
        self.topGradientView.hidden = YES;
        self.bottomGradientView.hidden = YES;
        self.blurView.hidden = YES;

        if (callStatus == RCCallDialing) {
            self.minimizeButton.frame = CGRectMake(RCCallHorizontalMargin, RCCallMiniButtonTopMargin + RCCallStatusBarHeight, RCCallMiniButtonLength, RCCallMiniButtonLength);
            self.minimizeButton.hidden = NO;
        }else if (callStatus == RCCallActive) {
            self.minimizeButton.frame = CGRectMake(RCCallHorizontalMargin, RCCallMiniButtonTopMargin + RCCallStatusBarHeight, RCCallMiniButtonLength, RCCallMiniButtonLength);
            self.minimizeButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.minimizeButton.hidden = YES;
        }

        if (callStatus == RCCallActive) {
            self.inviteUserButton.frame =
                CGRectMake(self.view.frame.size.width - RCCallHorizontalMargin - RCCallMiniButtonLength,
                            RCCallMiniButtonTopMargin +  + RCCallStatusBarHeight, RCCallMiniButtonLength, RCCallMiniButtonLength);
            self.inviteUserButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.inviteUserButton.hidden = YES;
        }

        if (callStatus == RCCallActive) {
            self.timeLabel.frame =
                CGRectMake(RCCallHorizontalMargin,  RCCallMiniButtonTopMargin + RCCallMiniLabelHeight + RCCallTimeTopMargin + RCCallStatusBarHeight,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallTimeLabelHeight);
            self.timeLabel.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.timeLabel.hidden = YES;
        }

        // header orgin y = RCCallVerticalMargin * 2
        if (callStatus == RCCallIncoming || callStatus == RCCallRinging) {
            self.tipsLabel.frame =
                CGRectMake(RCCallHorizontalMargin,
                            self.view.frame.size.height * 0.54 ,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        } else if (callStatus == RCCallDialing) {
            self.tipsLabel.frame =
                CGRectMake(RCCallHorizontalMargin,  self.view.frame.size.height * 0.54,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        } else if (callStatus == RCCallHangup) {
            self.tipsLabel.frame =
            CGRectMake(RCCallHorizontalMargin,
                       self.view.frame.size.height - RCCallButtonBottomMargin * 3 - RCCallButtonLength -RCCallExtraSpace,
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
            self.muteButton.frame = CGRectMake(RCCallHorizontalMiddleMargin,
                                               self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2) - RCCallCustomButtonLength - RCCallExtraSpace,
                                               RCCallCustomButtonLength, RCCallCustomButtonLength);
            [self layoutTextUnderImageButton:self.muteButton];
            self.muteButton.hidden = NO;
            self.muteButton.enabled = YES;
        } else if (callStatus == RCCallDialing) {
            self.muteButton.frame = CGRectMake(RCCallHorizontalMiddleMargin,
                                               self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2) - RCCallCustomButtonLength - RCCallExtraSpace,
                                               RCCallCustomButtonLength, RCCallCustomButtonLength);
            [self layoutTextUnderImageButton:self.muteButton];
            self.muteButton.hidden = NO;
            self.muteButton.enabled = NO;
        } else if (callStatus != RCCallHangup) {
            self.muteButton.hidden = NO;
            self.muteButton.enabled = NO;
        }

        if (callStatus == RCCallActive || callStatus == RCCallDialing) {
            self.speakerButton.frame =
            CGRectMake(self.view.frame.size.width - RCCallHorizontalMiddleMargin - RCCallCustomButtonLength,
                       self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2) - RCCallCustomButtonLength - RCCallExtraSpace, RCCallCustomButtonLength,
                       RCCallCustomButtonLength);
            [self layoutTextUnderImageButton:self.speakerButton];
            self.speakerButton.hidden = NO;
            if ([self isHeadsetPluggedIn])
                [self reloadSpeakerRoute:NO];
        } else if (callStatus != RCCallHangup) {
            self.speakerButton.hidden = YES;
        }
        
        if (callStatus == RCCallActive) {
            [self.speakerButton setSelected:self.callSession.speakerEnabled];
            if ([self isHeadsetPluggedIn])
                [self reloadSpeakerRoute:NO];
        }

        if (callStatus == RCCallDialing) {
            self.hangupButton.frame =
            CGRectMake((self.view.frame.size.width - RCCallButtonLength) / 2,
                       self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2 + RCCallCustomButtonLength / 2 + 1.25f) - RCCallButtonLength/2 - RCCallExtraSpace, RCCallButtonLength,
                       RCCallButtonLength);
            [self layoutTextUnderBigImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.hidden = YES;
        } else if (callStatus == RCCallIncoming || callStatus == RCCallRinging) {
            self.hangupButton.frame = CGRectMake(
                                                 RCCallHorizontalBigMargin, self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2 + RCCallCustomButtonLength / 2 + 1.25f) - RCCallButtonLength/2 - RCCallExtraSpace,
                                                 RCCallButtonLength, RCCallButtonLength);
            [self layoutTextUnderImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.frame =
                CGRectMake(self.view.frame.size.width - RCCallHorizontalBigMargin - RCCallButtonLength,
                           self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2 + RCCallCustomButtonLength / 2 + 1.25f) - RCCallButtonLength/2 - RCCallExtraSpace, RCCallButtonLength,
                           RCCallButtonLength);
            [self layoutTextUnderImageButton:self.acceptButton];
            self.acceptButton.hidden = NO;
        } else if (callStatus == RCCallActive) {
            self.hangupButton.frame =
            CGRectMake((self.view.frame.size.width - RCCallButtonLength) / 2,
                       self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2 + RCCallCustomButtonLength / 2 + 1.25f) - RCCallButtonLength/2 - RCCallExtraSpace, RCCallButtonLength,
                       RCCallButtonLength);
            [self layoutTextUnderBigImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.hidden = YES;
        }

        self.cameraCloseButton.hidden = YES;
        self.cameraSwitchButton.hidden = YES;

    } else if (mediaType == RCCallMediaVideo && isMultiCall) {// 多人视频
        self.backgroundView.hidden = NO;

        if (callStatus == RCCallDialing || callStatus == RCCallIncoming || callStatus == RCCallRinging  || callStatus == RCCallHangup) {
            self.blurView.hidden = NO;
        }else{
            self.blurView.hidden = YES;
        }
        
        if (callStatus == RCCallActive) {
            self.muteButton.frame = CGRectMake(RCCallHorizontalMiddleMargin,
                                               self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2) - RCCallCustomButtonLength - RCCallExtraSpace,
                                               RCCallCustomButtonLength, RCCallCustomButtonLength);
            [self layoutTextUnderImageButton:self.muteButton];
            self.muteButton.hidden = NO;
            self.muteButton.enabled = YES;
        } else if (callStatus == RCCallDialing) {
            self.muteButton.frame = CGRectMake(RCCallHorizontalMiddleMargin,
                                               self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2) - RCCallCustomButtonLength - RCCallExtraSpace,
                                               RCCallCustomButtonLength, RCCallCustomButtonLength);
            [self layoutTextUnderImageButton:self.muteButton];
            self.muteButton.hidden = YES;
            self.muteButton.enabled = NO;
        } else if (callStatus != RCCallHangup) {
            self.muteButton.hidden = YES;
            self.muteButton.enabled = NO;
        }
        
        if (callStatus == RCCallDialing) {
            self.speakerButton.frame =
            CGRectMake(self.view.frame.size.width - RCCallHorizontalMiddleMargin - RCCallCustomButtonLength,
                       self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2) - RCCallCustomButtonLength - RCCallExtraSpace, RCCallCustomButtonLength,
                       RCCallCustomButtonLength);
            [self layoutTextUnderImageButton:self.speakerButton];
            self.speakerButton.hidden = YES;
            [self setSpeakerEnable:NO];
            if ([self isHeadsetPluggedIn])
                [self reloadSpeakerRoute:NO];
        } else if (callStatus != RCCallHangup) {
            self.speakerButton.hidden = YES;
        }
        
        
        if (callStatus == RCCallDialing) {
            self.minimizeButton.frame = CGRectMake(RCCallHorizontalMargin, RCCallMiniButtonTopMargin + RCCallStatusBarHeight, RCCallMiniButtonLength, RCCallMiniButtonLength);
            self.minimizeButton.hidden = NO;
        }else if (callStatus == RCCallActive) {
            self.minimizeButton.frame = CGRectMake(RCCallHorizontalMargin, RCCallMiniButtonTopMargin + RCCallStatusBarHeight, RCCallMiniButtonLength, RCCallMiniButtonLength);
            self.minimizeButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.minimizeButton.hidden = YES;
        }

        if (callStatus == RCCallActive) {
            self.cameraSwitchButton.frame = CGRectMake(
                                                       self.view.frame.size.width - RCCallHeaderLength,
                                                       RCCallMiniButtonLength + RCCallStatusBarHeight, RCCallMiniButtonLength, RCCallMiniButtonLength);
            self.cameraSwitchButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.cameraSwitchButton.hidden = YES;
        }
        
//        if (callStatus == RCCallActive) {
//            self.inviteUserButton.frame =
//            CGRectMake(self.view.frame.size.width - RCCallHorizontalMargin / 2 - RCCallButtonLength / 2,
//                       RCCallVerticalMargin, RCCallButtonLength / 2, RCCallButtonLength / 2);
//            self.inviteUserButton.hidden = NO;
//        } else if (callStatus != RCCallHangup) {
//            self.inviteUserButton.hidden = YES;
//        }
        
        if (callStatus == RCCallActive) {
            self.addButton.frame =
            CGRectMake(self.view.frame.size.width - RCCallHorizontalMargin - RCCallButtonLength / 2,
                       RCCallMiniButtonLength + RCCallStatusBarHeight, RCCallButtonLength / 2, RCCallButtonLength / 2);
            self.addButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.addButton.hidden = YES;
        }
        
        if (callStatus == RCCallActive) {
            self.timeLabel.frame =
            CGRectMake(self.view.frame.size.width / 2 - 49.0 / 2, RCCallMiniButtonTopMargin + RCCallMiniLabelHeight + RCCallTimeTopMargin + RCCallStatusBarHeight,
                       35.0, RCCallTimeLabelHeight);
            self.timeLabel.textAlignment = NSTextAlignmentLeft;
            self.timeLabel.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.timeLabel.hidden = YES;
        }
        
        if (callStatus == RCCallActive) {
            self.signalImageView.frame =
            CGRectMake(self.timeLabel.frame.origin.x + self.timeLabel.frame.size.width + 4.0f,  self.timeLabel.frame.origin.y,
                                                    RCCallTopMargin - 5.0,  RCCallTimeLabelHeight);
            self.signalImageView.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.signalImageView.hidden = YES;
        }
        
        if (callStatus == RCCallIncoming || callStatus == RCCallRinging) {
            self.tipsLabel.frame =
                CGRectMake(RCCallHorizontalMargin,
                            self.view.frame.size.height * 0.54,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        } else if (callStatus == RCCallDialing) {
            self.tipsLabel.frame =
            CGRectMake(RCCallHorizontalMargin, self.view.frame.size.height * 0.52,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        } else if (callStatus == RCCallHangup) {
            self.tipsLabel.frame =
            CGRectMake(RCCallHorizontalMargin,
                       self.view.frame.size.height - RCCallButtonLength - RCCallButtonBottomMargin * 2 - RCCallButtonInsideMargin - RCCallLabelHeight - RCCallExtraSpace,
                       self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        }  else {
            self.tipsLabel.frame =
                CGRectMake(RCCallHorizontalMargin,
                           self.view.frame.size.height - RCCallVerticalMargin - RCCallButtonLength * 3.5 -
                               RCCallInsideMargin * 5 - RCCallLabelHeight,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        }
        self.tipsLabel.hidden = NO;

  
        if (callStatus == RCCallDialing) {
            self.hangupButton.frame =
            CGRectMake((self.view.frame.size.width - RCCallButtonLength) / 2,
                       self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2 + RCCallCustomButtonLength / 2 + 1.25f) - RCCallButtonLength/2 - RCCallExtraSpace, RCCallButtonLength,
                       RCCallButtonLength);
            [self layoutTextUnderBigImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.hidden = YES;
        } else if (callStatus == RCCallIncoming || callStatus == RCCallRinging) {
            self.hangupButton.frame = CGRectMake(
                                                 RCCallHorizontalBigMargin, self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2 + RCCallCustomButtonLength / 2 + 1.25f) - RCCallButtonLength/2 - RCCallExtraSpace,
                                                 RCCallButtonLength, RCCallButtonLength);
            [self layoutTextUnderImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.frame =
                CGRectMake(self.view.frame.size.width - RCCallHorizontalBigMargin - RCCallButtonLength,
                           self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2 + RCCallCustomButtonLength / 2 + 1.25f) - RCCallButtonLength/2 - RCCallExtraSpace, RCCallButtonLength,
                           RCCallButtonLength);
            [self layoutTextUnderImageButton:self.acceptButton];
            self.acceptButton.hidden = NO;
        } else if (callStatus == RCCallActive) {
            self.hangupButton.frame =
                CGRectMake((self.view.frame.size.width - RCCallButtonLength) / 2,
                           self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2 + RCCallCustomButtonLength / 2 + 1.25f) - RCCallButtonLength/2 - RCCallExtraSpace, RCCallButtonLength,
                           RCCallButtonLength);
            [self layoutTextUnderBigImageButton:self.hangupButton];
            self.hangupButton.hidden = NO;

            self.acceptButton.hidden = YES;
        }

        if (callStatus == RCCallActive) {
            self.cameraCloseButton.frame =
            CGRectMake(self.view.frame.size.width - RCCallHorizontalMiddleMargin - (RCCallCustomButtonLength + RCCallInsideMargin),
                       self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - RCCallInsideMargin * 2) - RCCallCustomButtonLength - RCCallExtraSpace, RCCallCustomButtonLength + RCCallInsideMargin * 2,
                       RCCallCustomButtonLength);
            [self layoutTextUnderImageButton:self.cameraCloseButton];
            self.cameraCloseButton.hidden = NO;
        } else if (callStatus != RCCallHangup) {
            self.cameraCloseButton.hidden = YES;
        }
    }
}

- (void)layoutTextUnderImageButton:(UIButton *)button {
    [button.titleLabel setFont:[UIFont fontWithName:@"PingFangSC-Regular" size:13]];
    [button setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];

    button.titleEdgeInsets = UIEdgeInsetsMake(0, -button.imageView.frame.size.width,
                                              -button.imageView.frame.size.height - RCCallInsideMargin, 0);
    button.imageEdgeInsets = UIEdgeInsetsMake(-button.titleLabel.intrinsicContentSize.height - RCCallInsideMargin, 0, 0,
                                              -button.titleLabel.intrinsicContentSize.width);
}

- (void)layoutTextUnderBigImageButton:(UIButton *)button {
//    [button.titleLabel setFont:[UIFont systemFontOfSize:13]];
    [button.titleLabel setFont:[UIFont fontWithName:@"PingFangSC-Regular" size:13]];
    [button setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    
    button.titleEdgeInsets = UIEdgeInsetsMake(0, -button.imageView.frame.size.width,
                                              -button.imageView.frame.size.height - RCCallInsideMiniMargin , 0);
    button.imageEdgeInsets = UIEdgeInsetsMake(-button.titleLabel.intrinsicContentSize.height - RCCallInsideMiniMargin, 0, 0, -button.titleLabel.intrinsicContentSize.width);
}

- (void)layoutTextUnderLargeImageButton:(UIButton *)button {
    //    [button.titleLabel setFont:[UIFont systemFontOfSize:13]];
    [button.titleLabel setFont:[UIFont fontWithName:@"PingFangSC-Regular" size:13]];
    [button setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    
    button.titleEdgeInsets = UIEdgeInsetsMake(0, -button.imageView.frame.size.width,
                                              -button.imageView.frame.size.height - RCCallInsideMiniMargin , 0);
    button.imageEdgeInsets = UIEdgeInsetsMake(-button.titleLabel.intrinsicContentSize.height - 13.0, 0, 0, -button.titleLabel.intrinsicContentSize.width);
}

#pragma mark - RCCallSessionDelegate
/*!
 通话已接通
 */
- (void)callDidConnect {
    [self callWillConnect];
    
    if (self.callSession.mediaType == RCCallMediaAudio &&
        [self.callSession.caller isEqualToString:[RCIMClient sharedRCIMClient].currentUserInfo.userId]) {
        [[RCCXCall sharedInstance] reportOutgoingCallConnected];
    }

    self.tipsLabel.text = (self.callSession.mediaType == RCCallMediaVideo) ? NSLocalizedStringFromTable(@"Connecting...", @"RongCloudKit", nil) : @"";
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
    [[RCCXCall sharedInstance] endCXCall];
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
        [[RCCall sharedRCCall] stopReceiveCallVibrate];
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
    
    [[RCCXCall sharedInstance] setAVAudioSessionMode];
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
//    [self checkApplicationStateAndAlert];
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
    dispatch_async(dispatch_get_main_queue(), ^{
        switch (txQuality)
        {
            case RCCall_Quality_Unknown:
                self.signalImageView.image = self->signalImage0;
                break;
            case RCCall_Quality_Excellent:
                self.signalImageView.image = self->signalImage5;
                break;
            case RCCall_Quality_Good:
                self.signalImageView.image = self->signalImage4;
                break;
            case RCCall_Quality_Poor:
                self.signalImageView.image = self->signalImage3;
                break;
            case RCCall_Quality_Bad:
                self.signalImageView.image = self->signalImage2;
                break;
            case RCCall_Quality_VBad:
                self.signalImageView.image = self->signalImage1;
                break;
            case RCCall_Quality_Down:
                self.signalImageView.image = self->signalImage0;
                break;
            default:
                break;
        }
        
        if (self.callSession.callStatus == RCCallActive) {
            if (txQuality > RCCall_Quality_VBad || rxQuality > RCCall_Quality_VBad) {
                //[self playNetworkBadSounds];
                self.tipsLabel.frame =
                CGRectMake(RCCallHorizontalMargin,
                           self.view.frame.size.height - RCCallButtonBottomMargin * 5 - RCCallExtraSpace,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
                self.tipsLabel.text = NSLocalizedStringFromTable(@"voip_network_bad", @"RongCloudKit", nil);
            } else {
                self.tipsLabel.text = nil;
            }
        }
    });
}

- (void)playNetworkBadSounds {
    static time_t prePlayTime = 0;
    NSString *soundPath =
        [[[NSBundle mainBundle] pathForResource:@"RongCloud" ofType:@"bundle"]
            stringByAppendingPathComponent:@"voip/voip_network_error_sound.wav"];
    if (soundPath.length > 0) {
        NSURL* fileUrl = [NSURL fileURLWithPath:soundPath];
        SystemSoundID soundId = 0;
        OSStatus error =  AudioServicesCreateSystemSoundID((__bridge CFURLRef _Nonnull)(fileUrl), &soundId);
        if (error == kAudioServicesNoError && time(nil) - prePlayTime > 5) {
            prePlayTime = time(nil);
            AudioServicesPlayAlertSound(soundId);
        }
    }
}

- (void)receiveRemoteUserVideoFirstKeyFrame:(NSString *)userId
{
    self.tipsLabel.text = @"";
}

- (void)setSpeakerEnable:(BOOL)enable
{
    [self.callSession setSpeakerEnabled:enable];
    [self.speakerButton setSelected:enable];
}

#pragma mark - telephony
- (void)registerTelephonyEvent {
    self.callCenter = [[CTCallCenter alloc] init];
    self.callCenter.callEventHandler = ^(CTCall *call) {
        if ([call.callState isEqualToString:CTCallStateConnected]) {
            [[RCCXCall sharedInstance] hangupIfNeedWithUUID:call.callID];
        }
    };
}

#pragma mark - proximity
- (void)addProximityMonitoringObserver {
    if (self.callSession.mediaType == RCCallMediaAudio) {
        [UIDevice currentDevice].proximityMonitoringEnabled = YES;
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(proximityStatueChanged:)
                                                     name:UIDeviceProximityStateDidChangeNotification
                                                   object:nil];
    }
}

- (void)removeProximityMonitoringObserver {
    [UIDevice currentDevice].proximityMonitoringEnabled = NO;
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                     name:UIDeviceProximityStateDidChangeNotification
                                                   object:nil];
}

- (void)proximityStatueChanged:(NSNotificationCenter *)notification {
    
    switch (self.mediaType)
    {
        case RCCallMediaAudio:
        {
        }
            break;
        case RCCallMediaVideo:
        {
            if (self.callSession.callStatus == RCCallActive)
            {
                if ([UIDevice currentDevice].proximityState)
                    [self.callSession setSpeakerEnabled:NO];
                else
                    [self.callSession setSpeakerEnabled:YES];
            }
        }
            break;
        default:
            break;
    }
}

- (void)handleAudioRouteChange:(NSNotification*)notification
{
    NSInteger reason = [[[notification userInfo] objectForKey:AVAudioSessionRouteChangeReasonKey] integerValue];
    AVAudioSessionRouteDescription *route = [AVAudioSession sharedInstance].currentRoute;
    AVAudioSessionPortDescription *port = route.outputs.firstObject;
    switch (reason)
    {
        case AVAudioSessionRouteChangeReasonUnknown:
            break;
        case AVAudioSessionRouteChangeReasonNewDeviceAvailable : //1
            [self reloadSpeakerRoute:NO];
            break;
        case AVAudioSessionRouteChangeReasonOldDeviceUnavailable : //2
            [self reloadSpeakerRoute:YES];
            break;
        case AVAudioSessionRouteChangeReasonCategoryChange : //3
            break;
        case AVAudioSessionRouteChangeReasonOverride : //4
        {
            if ([port.portType isEqualToString:AVAudioSessionPortBuiltInReceiver] || [port.portType isEqualToString: AVAudioSessionPortBuiltInSpeaker]){
                [self reloadSpeakerRoute:YES];
            }
            else{
                [self reloadSpeakerRoute:NO];
            }
        }
            break;
        case AVAudioSessionRouteChangeReasonWakeFromSleep : //6
            break;
        case AVAudioSessionRouteChangeReasonNoSuitableRouteForCategory : //7
            break;
        case AVAudioSessionRouteChangeReasonRouteConfigurationChange : //8
            break;
        default:
            break;
    }
}

- (void)reloadSpeakerRoute:(BOOL)enable
{
    dispatch_async(dispatch_get_main_queue(), ^{
        self.speakerButton.enabled = enable;
    });
}

- (BOOL)isHeadsetPluggedIn
{
    AVAudioSessionRouteDescription *route = [[AVAudioSession sharedInstance] currentRoute];
    for (AVAudioSessionPortDescription* desc in [route outputs])
    {
        NSString *outputer = desc.portType;
        if ([outputer isEqualToString:AVAudioSessionPortHeadphones] || [outputer isEqualToString:AVAudioSessionPortBluetoothLE] || [outputer isEqualToString:AVAudioSessionPortBluetoothHFP] || [outputer isEqualToString:AVAudioSessionPortBluetoothA2DP])
            return YES;
    }
    return NO;
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
