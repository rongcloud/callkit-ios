//
//  RCCallSingleCallViewController.m
//  RongCallKit
//
//  Created by 岑裕 on 16/3/21.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCCallSingleCallViewController.h"
#import "RCCallFloatingBoard.h"
#import "RCCallKitUtility.h"
#import "RCUserInfoCacheManager.h"
#import "RCloudImageView.h"

@interface RCCallSingleCallViewController ()

@property(nonatomic, strong) RCUserInfo *remoteUserInfo;

@end

@implementation RCCallSingleCallViewController

// init
- (instancetype)initWithIncomingCall:(RCCallSession *)callSession {
    return [super initWithIncomingCall:callSession];
}

- (instancetype)initWithOutgoingCall:(NSString *)targetId mediaType:(RCCallMediaType)mediaType {
    return [super initWithOutgoingCall:ConversationType_PRIVATE
                              targetId:targetId
                             mediaType:mediaType
                            userIdList:@[ targetId ]];
}

- (instancetype)initWithActiveCall:(RCCallSession *)callSession {
    return [super initWithActiveCall:callSession];
}

- (void)viewDidLoad {
    [super viewDidLoad];

    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onUserInfoUpdate:)
                                                 name:RCKitDispatchUserInfoUpdateNotification
                                               object:nil];

    RCUserInfo *userInfo = [[RCUserInfoCacheManager sharedManager] getUserInfo:self.callSession.targetId];
    if (!userInfo) {
        userInfo = [[RCUserInfo alloc] initWithUserId:self.callSession.targetId name:nil portrait:nil];
    }
    self.remoteUserInfo = userInfo;
    [self.remoteNameLabel setText:userInfo.name];
    [self.remotePortraitView setImageURL:[NSURL URLWithString:userInfo.portraitUri]];
}

- (RCloudImageView *)remotePortraitView {
    if (!_remotePortraitView) {
        _remotePortraitView = [[RCloudImageView alloc] init];

        [self.view addSubview:_remotePortraitView];
        _remotePortraitView.hidden = YES;
        [_remotePortraitView setPlaceholderImage:[RCCallKitUtility getDefaultPortraitImage]];
        _remotePortraitView.layer.cornerRadius = 4;
        _remotePortraitView.layer.masksToBounds = YES;
    }
    return _remotePortraitView;
}

- (UILabel *)remoteNameLabel {
    if (!_remoteNameLabel) {
        _remoteNameLabel = [[UILabel alloc] init];
        _remoteNameLabel.backgroundColor = [UIColor clearColor];
        _remoteNameLabel.textColor = [UIColor whiteColor];
        _remoteNameLabel.layer.shadowOpacity = 0.8;
        _remoteNameLabel.layer.shadowRadius = 1.0;
        _remoteNameLabel.layer.shadowColor = [UIColor darkGrayColor].CGColor;
        _remoteNameLabel.layer.shadowOffset = CGSizeMake(0, 1);
        _remoteNameLabel.font = [UIFont systemFontOfSize:18];
        _remoteNameLabel.textAlignment = NSTextAlignmentCenter;

        [self.view addSubview:_remoteNameLabel];
        _remoteNameLabel.hidden = YES;
    }
    return _remoteNameLabel;
}

- (UIImageView *)statusView {
    if (!_statusView) {
        _statusView = [[RCloudImageView alloc] init];
        [self.view addSubview:_statusView];
        _statusView.hidden = YES;
        _statusView.image = [RCCallKitUtility imageFromVoIPBundle:@"voip/voip_connecting"];
    }
    return _statusView;
}

- (UIView *)mainVideoView {
    if (!_mainVideoView) {
        _mainVideoView = [[UIView alloc] initWithFrame:self.backgroundView.frame];
        _mainVideoView.backgroundColor = RongVoIPUIColorFromRGB(0x262e42);

        [self.backgroundView addSubview:_mainVideoView];
        _mainVideoView.hidden = YES;
    }
    return _mainVideoView;
}

- (UIView *)subVideoView {
    if (!_subVideoView) {
        _subVideoView = [[UIView alloc] init];
        _subVideoView.backgroundColor = [UIColor blackColor];
        _subVideoView.layer.borderWidth = 1;
        _subVideoView.layer.borderColor = [[UIColor whiteColor] CGColor];

        [self.view addSubview:_subVideoView];
        _subVideoView.hidden = YES;

        UITapGestureRecognizer *tap =
            [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(subVideoViewClicked)];
        [_subVideoView addGestureRecognizer:tap];
    }
    return _subVideoView;
}

- (void)subVideoViewClicked {
    if ([self.remoteUserInfo.userId isEqualToString:self.callSession.targetId]) {
        RCUserInfo *userInfo = [RCIMClient sharedRCIMClient].currentUserInfo;

        self.remoteUserInfo = userInfo;
        [self.remoteNameLabel setText:userInfo.name];
        [self.remotePortraitView setImageURL:[NSURL URLWithString:userInfo.portraitUri]];

        [self.callSession setVideoView:self.mainVideoView userId:self.remoteUserInfo.userId];
        [self.callSession setVideoView:self.subVideoView userId:self.callSession.targetId];
    } else {
        RCUserInfo *userInfo = [[RCUserInfoCacheManager sharedManager] getUserInfo:self.callSession.targetId];
        if (!userInfo) {
            userInfo = [[RCUserInfo alloc] initWithUserId:self.callSession.targetId name:nil portrait:nil];
        }
        self.remoteUserInfo = userInfo;
        [self.remoteNameLabel setText:userInfo.name];
        [self.remotePortraitView setImageURL:[NSURL URLWithString:userInfo.portraitUri]];

        [self.callSession setVideoView:self.subVideoView userId:[RCIMClient sharedRCIMClient].currentUserInfo.userId];
        [self.callSession setVideoView:self.mainVideoView userId:self.remoteUserInfo.userId];
    }
}

- (void)resetLayout:(BOOL)isMultiCall mediaType:(RCCallMediaType)mediaType callStatus:(RCCallStatus)callStatus {
    [super resetLayout:isMultiCall mediaType:mediaType callStatus:callStatus];

    UIImage *remoteHeaderImage = self.remotePortraitView.image;

    if (mediaType == RCCallMediaAudio) {
        self.remotePortraitView.frame = CGRectMake((self.view.frame.size.width - RCCallHeaderLength) / 2,
                                                   RCCallVerticalMargin * 3, RCCallHeaderLength, RCCallHeaderLength);
        self.remotePortraitView.image = remoteHeaderImage;
        self.remotePortraitView.hidden = NO;

        self.remoteNameLabel.frame =
            CGRectMake(RCCallHorizontalMargin, RCCallVerticalMargin * 3 + RCCallHeaderLength + RCCallInsideMargin,
                       self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        self.remoteNameLabel.hidden = NO;

        self.remoteNameLabel.textAlignment = NSTextAlignmentCenter;
        self.tipsLabel.textAlignment = NSTextAlignmentCenter;

        self.statusView.frame = CGRectMake((self.view.frame.size.width - 17) / 2,
                                           RCCallVerticalMargin * 3 + (RCCallHeaderLength - 4) / 2, 17, 4);

        if (callStatus == RCCallRinging || callStatus == RCCallDialing || callStatus == RCCallIncoming) {
            self.remotePortraitView.alpha = 0.5;
            self.statusView.hidden = NO;
        } else {
            self.statusView.hidden = YES;
            self.remotePortraitView.alpha = 1.0;
        }

        self.mainVideoView.hidden = YES;
        self.subVideoView.hidden = YES;
        [self resetRemoteUserInfoIfNeed];
    } else {
        if (callStatus == RCCallDialing) {
            self.mainVideoView.hidden = NO;
            [self.callSession setVideoView:self.mainVideoView
                                    userId:[RCIMClient sharedRCIMClient].currentUserInfo.userId];
            self.blurView.hidden = YES;
        } else if (callStatus == RCCallActive) {
            self.mainVideoView.hidden = NO;
            [self.callSession setVideoView:self.mainVideoView userId:self.callSession.targetId];
            self.blurView.hidden = YES;
        } else {
            self.mainVideoView.hidden = YES;
        }

        if (callStatus == RCCallActive) {
            self.remotePortraitView.hidden = YES;

            self.remoteNameLabel.frame =
                CGRectMake(RCCallHorizontalMargin, RCCallVerticalMargin,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
            self.remoteNameLabel.hidden = NO;
            self.remoteNameLabel.textAlignment = NSTextAlignmentCenter;
        } else if (callStatus == RCCallDialing) {
            self.remotePortraitView.frame =
                CGRectMake((self.view.frame.size.width - RCCallHeaderLength) / 2, RCCallVerticalMargin * 3,
                           RCCallHeaderLength, RCCallHeaderLength);
            self.remotePortraitView.image = remoteHeaderImage;
            self.remotePortraitView.hidden = NO;

            self.remoteNameLabel.frame =
                CGRectMake(RCCallHorizontalMargin, RCCallVerticalMargin * 3 + RCCallHeaderLength + RCCallInsideMargin,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
            self.remoteNameLabel.hidden = NO;
            self.remoteNameLabel.textAlignment = NSTextAlignmentCenter;
        } else if (callStatus == RCCallIncoming || callStatus == RCCallRinging) {
            self.remotePortraitView.frame =
                CGRectMake((self.view.frame.size.width - RCCallHeaderLength) / 2, RCCallVerticalMargin * 3,
                           RCCallHeaderLength, RCCallHeaderLength);
            self.remotePortraitView.image = remoteHeaderImage;
            self.remotePortraitView.hidden = NO;

            self.remoteNameLabel.frame =
                CGRectMake(RCCallHorizontalMargin, RCCallVerticalMargin * 3 + RCCallHeaderLength + RCCallInsideMargin,
                           self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
            self.remoteNameLabel.hidden = NO;
            self.remoteNameLabel.textAlignment = NSTextAlignmentCenter;
        }

        if (callStatus == RCCallActive) {
            if ([RCCallKitUtility isLandscape] && [self isSupportOrientation:(UIInterfaceOrientation)[UIDevice currentDevice].orientation]) {
                self.subVideoView.frame =
                    CGRectMake(self.view.frame.size.width - RCCallHeaderLength - RCCallHorizontalMargin / 2,
                               RCCallVerticalMargin, RCCallHeaderLength * 1.5, RCCallHeaderLength);
            } else {
                self.subVideoView.frame =
                    CGRectMake(self.view.frame.size.width - RCCallHeaderLength - RCCallHorizontalMargin / 2,
                               RCCallVerticalMargin, RCCallHeaderLength, RCCallHeaderLength * 1.5);
            }
            [self.callSession setVideoView:self.subVideoView
                                    userId:[RCIMClient sharedRCIMClient].currentUserInfo.userId];
            self.subVideoView.hidden = NO;
        } else {
            self.subVideoView.hidden = YES;
        }

        self.remoteNameLabel.textAlignment = NSTextAlignmentCenter;
        self.statusView.frame = CGRectMake((self.view.frame.size.width - 17) / 2,
                                           RCCallVerticalMargin * 3 + (RCCallHeaderLength - 4) / 2, 17, 4);

        if (callStatus == RCCallRinging || callStatus == RCCallDialing || callStatus == RCCallIncoming) {
            self.remotePortraitView.alpha = 0.5;
            self.statusView.hidden = NO;
        } else {
            self.statusView.hidden = YES;
            self.remotePortraitView.alpha = 1.0;
        }
    }
}

- (void)resetRemoteUserInfoIfNeed {
    if (![self.remoteUserInfo.userId isEqualToString:self.callSession.targetId]) {
        RCUserInfo *userInfo = [[RCUserInfoCacheManager sharedManager] getUserInfo:self.callSession.targetId];
        if (!userInfo) {
            userInfo = [[RCUserInfo alloc] initWithUserId:self.callSession.targetId name:nil portrait:nil];
        }
        self.remoteUserInfo = userInfo;
        [self.remoteNameLabel setText:userInfo.name];
        [self.remotePortraitView setImageURL:[NSURL URLWithString:userInfo.portraitUri]];
    }
}

- (BOOL)isSupportOrientation:(UIInterfaceOrientation)orientation {
    return [[UIApplication sharedApplication]
               supportedInterfaceOrientationsForWindow:[UIApplication sharedApplication].keyWindow] &
           (1 << orientation);
}

#pragma mark - UserInfo Update
- (void)onUserInfoUpdate:(NSNotification *)notification {
    NSDictionary *userInfoDic = notification.object;
    NSString *updateUserId = userInfoDic[@"userId"];
    RCUserInfo *updateUserInfo = userInfoDic[@"userInfo"];

    if ([updateUserId isEqualToString:self.remoteUserInfo.userId]) {
        __weak typeof(self) weakSelf = self;
        dispatch_async(dispatch_get_main_queue(), ^{
            weakSelf.remoteUserInfo = updateUserInfo;
            [weakSelf.remoteNameLabel setText:updateUserInfo.name];
            [weakSelf.remotePortraitView setImageURL:[NSURL URLWithString:updateUserInfo.portraitUri]];
        });
    }
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
