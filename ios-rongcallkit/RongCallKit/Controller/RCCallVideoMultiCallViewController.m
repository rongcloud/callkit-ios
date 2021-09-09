//
//  RCCallVideoMultiCallViewController.m
//  RongCallKit
//
//  Created by litao on 16/3/18.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCCallVideoMultiCallViewController.h"
#import "RCAudioMultiCallUserCollectionLayout.h"
#import "RCCXCall.h"
#import "RCCall.h"
#import "RCCallFloatingBoard.h"
#import "RCCallKitUtility.h"
#import "RCCallMultiCallUserCell.h"
#import "RCCallSelectMemberViewController.h"
#import "RCCallUserCallInfoModel.h"
#import "RCUserInfoCacheManager.h"
#import "RCVideoMultiCallUserCollectionLayout.h"
#import "RCloudImageView.h"
#import "UICollectionView+BackgroundView.h"

#define currentUserId ([RCIMClient sharedRCIMClient].currentUserInfo.userId)
#define RongVoIPMultiVideoCellReuseID @"RongVoIPMultiVideoCellReuseID"

@interface RCCallVideoMultiCallViewController () <UICollectionViewDataSource, UICollectionViewDelegate>

@property (nonatomic, strong) RCCallUserCallInfoModel *mainModel;
@property (nonatomic, assign) BOOL isFullScreen;
@property (nonatomic, strong) NSMutableDictionary *cellLabelDic;

@end

@implementation RCCallVideoMultiCallViewController

- (instancetype)initWithIncomingCall:(RCCallSession *)callSession {
    return [super initWithIncomingCall:callSession];
}

- (instancetype)initWithOutgoingCall:(RCConversationType)conversationType
                            targetId:(NSString *)targetId
                          userIdList:(NSArray *)userIdList {
    return [super initWithOutgoingCall:conversationType
                              targetId:targetId
                             mediaType:RCCallMediaAudio
                            userIdList:userIdList];
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

    [self initAllUserModel];
    if (self.callSession.callStatus == RCCallHangup) {
        [[RCCall sharedRCCall] dismissCallViewController:self];
        return;
    }

    self.backgroundView.userInteractionEnabled = YES;
    [self.backgroundView
        addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self
                                                                     action:@selector(backgroundViewClicked)]];
    [self.acceptButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/answervideo.png"]
                       forState:UIControlStateNormal];
    [self.acceptButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/answervideo_hover.png"]
                       forState:UIControlStateHighlighted];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    self.isFullScreen = NO;
    self.cellLabelDic = [NSMutableDictionary dictionary];
    [RCCallKitUtility checkSystemPermission:self.callSession.mediaType
        success:^{

        }
        error:^{
            [self hangupButtonClicked];
        }];
}

- (void)initAllUserModel {
    if (self.callSession.callStatus == RCCallIncoming || self.callSession.callStatus == RCCallRinging) {
        if ([self inviterHasHangup]) {
            RCCallUserProfile *firstUserProfile = self.callSession.userProfileList[0];
            self.mainModel = [self generateUserModel:firstUserProfile.userId];
            [self.callSession setVideoView:self.backgroundView userId:self.mainModel.userId];

            self.subUserModelList = [[NSMutableArray alloc] init];
            for (RCCallUserProfile *userProfile in self.callSession.userProfileList) {
                if (![userProfile.userId isEqualToString:firstUserProfile.userId] && userProfile.userType != 2) {
                    RCCallUserCallInfoModel *userModel = [self generateUserModel:userProfile.userId];
                    [self.subUserModelList addObject:userModel];
                }
            }
            RCCallUserCallInfoModel *userModel = [self generateUserModel:currentUserId];
            if (userModel.profile.userType != 2) [self.subUserModelList addObject:userModel];
        } else {
            self.mainModel = [self generateUserModel:self.callSession.inviter];
            [self.callSession setVideoView:self.backgroundView userId:self.mainModel.userId];

            self.subUserModelList = [[NSMutableArray alloc] init];
            BOOL isContaitSelf = NO;
            for (RCCallUserProfile *userProfile in self.callSession.userProfileList) {
                if (![userProfile.userId isEqualToString:self.callSession.inviter] && userProfile.userType != 2) {
                    RCCallUserCallInfoModel *userModel = [self generateUserModel:userProfile.userId];
                    [self.subUserModelList addObject:userModel];
                }
                if ([userProfile.userId isEqualToString:currentUserId]) {
                    isContaitSelf = YES;
                }
            }

            if (!isContaitSelf) {
                RCCallUserCallInfoModel *userModel = [self generateUserModel:currentUserId];
                if (userModel.profile.userType != 2) [self.subUserModelList addObject:userModel];
            }
        }
    } else if (self.callSession.callStatus == RCCallDialing) {
        self.mainModel = [self generateUserModel:currentUserId];
        [self.callSession setVideoView:self.backgroundView userId:self.mainModel.userId];

        self.subUserModelList = [[NSMutableArray alloc] init];
        for (RCCallUserProfile *userProfile in self.callSession.userProfileList) {
            if (userProfile.userType != 2) {
                RCCallUserCallInfoModel *userModel = [self generateUserModel:userProfile.userId];
                [self.subUserModelList addObject:userModel];
            }
        }
    } else if (self.callSession.callStatus == RCCallActive) {
        if ([self.callSession.inviter isEqualToString:currentUserId] || [self inviterHasHangup]) {
            self.mainModel = [self generateUserModel:currentUserId];
            [self.callSession setVideoView:self.backgroundView userId:self.mainModel.userId];

            self.subUserModelList = [[NSMutableArray alloc] init];
            for (RCCallUserProfile *userProfile in self.callSession.userProfileList) {
                if (userProfile.userType != 2) {
                    RCCallUserCallInfoModel *userModel = [self generateUserModel:userProfile.userId];
                    [self.subUserModelList addObject:userModel];
                }
            }
        } else {
            self.mainModel = [self generateUserModel:self.callSession.inviter];
            [self.callSession setVideoView:self.backgroundView userId:self.mainModel.userId];

            self.subUserModelList = [[NSMutableArray alloc] init];
            for (RCCallUserProfile *userProfile in self.callSession.userProfileList) {
                if (![userProfile.userId isEqualToString:self.callSession.inviter] && userProfile.userType != 2) {
                    RCCallUserCallInfoModel *userModel = [self generateUserModel:userProfile.userId];
                    [self.subUserModelList addObject:userModel];
                }
            }
            RCCallUserCallInfoModel *userModel = [self generateUserModel:currentUserId];
            if (userModel.profile.userType != 2) [self.subUserModelList addObject:userModel];
        }
    }
}

- (RCCallUserCallInfoModel *)generateUserModel:(NSString *)userId {
    RCCallUserCallInfoModel *userModel = [[RCCallUserCallInfoModel alloc] init];
    userModel.userId = userId;
    userModel.userInfo = [[RCUserInfoCacheManager sharedManager] getUserInfo:userId];

    if ([userId isEqualToString:currentUserId]) {
        userModel.profile = self.callSession.myProfile;
    } else {
        for (RCCallUserProfile *userProfile in self.callSession.userProfileList) {
            if ([userProfile.userId isEqualToString:userId]) {
                userModel.profile = userProfile;
                break;
            }
        }
    }

    return userModel;
}

- (NSArray *)getAllUserIdInSubUserModel {
    NSMutableArray *userIdList = [[NSMutableArray alloc] init];
    for (RCCallUserCallInfoModel *userModel in self.subUserModelList) {
        [userIdList addObject:userModel.userId];
    }
    if (userIdList.count > 0) {
        return userIdList;
    } else {
        return nil;
    }
}

- (BOOL)inviterHasHangup {
    if ([self.callSession.inviter isEqualToString:currentUserId]) {
        if (self.callSession.callStatus == RCCallHangup) {
            return YES;
        } else {
            return NO;
        }
    } else {
        for (RCCallUserProfile *userProfile in self.callSession.userProfileList) {
            if ([userProfile.userId isEqualToString:self.callSession.inviter] &&
                userProfile.callStatus != RCCallHangup) {
                return NO;
            }
        }
        return YES;
    }
}

- (RCCallUserCallInfoModel *)getModelInSubUserModelList:(NSString *)userId {
    for (RCCallUserCallInfoModel *model in self.subUserModelList) {
        if ([model.userId isEqualToString:userId]) {
            return model;
        }
    }
    return nil;
}

- (void)updateSubUserLayout:(RCCallUserCallInfoModel *)model {
    if (model) {
        NSInteger index = [self.subUserModelList indexOfObject:model];
        if (index != NSNotFound && [self.userCollectionView numberOfItemsInSection:0] > index) {
            NSIndexPath *indexPath = [NSIndexPath indexPathForItem:index inSection:0];
            [UIView performWithoutAnimation:^{
                [self.userCollectionView reloadItemsAtIndexPaths:@[ indexPath ]];
            }];
        }
    }
}

- (void)updateAllSubUserLayout {
    [self.userCollectionView reloadData];
}

- (void)addSubUserModel:(RCCallUserCallInfoModel *)model {
    if (model.userId && ![[self getAllUserIdInSubUserModel] containsObject:model.userId]) {
        NSInteger index = self.subUserModelList.count;
        NSIndexPath *indexPath = [NSIndexPath indexPathForItem:index inSection:0];
        if (model.profile.userType != 2) {
            [self.subUserModelList addObject:model];
            [self.userCollectionView insertItemsAtIndexPaths:[NSArray arrayWithObject:indexPath]];
        }
    }
}

- (void)removeSubUserModel:(RCCallUserCallInfoModel *)model {
    if (model) {
        NSInteger index = [self.subUserModelList indexOfObject:model];
        if (index != NSNotFound) {
            NSIndexPath *indexPath = [NSIndexPath indexPathForItem:index inSection:0];
            [self.subUserModelList removeObject:model];
            if ([self.userCollectionView numberOfItemsInSection:0] > index) {
                [self.userCollectionView deleteItemsAtIndexPaths:[NSArray arrayWithObject:indexPath]];
            }
        }
    }
}

- (void)backgroundViewClicked {
    if (self.callSession.callStatus == RCCallActive) {
        self.isFullScreen = !self.isFullScreen;
        [[UIApplication sharedApplication] setStatusBarHidden:self.isFullScreen];
        [self resetLayout:self.callSession.isMultiCall
                mediaType:self.callSession.mediaType
               callStatus:self.callSession.callStatus];
    }
}

- (RCloudImageView *)inviterPortraitView {
    if (!_inviterPortraitView) {
        _inviterPortraitView = [[RCloudImageView alloc] init];

        [self.view addSubview:_inviterPortraitView];
        _inviterPortraitView.hidden = YES;
        [_inviterPortraitView setPlaceholderImage:[RCCallKitUtility getDefaultPortraitImage]];
        _inviterPortraitView.layer.cornerRadius = 4;
        _inviterPortraitView.layer.masksToBounds = YES;
    }
    return _inviterPortraitView;
}

- (RCloudImageView *)inviterPortraitBgView {
    if (!_inviterPortraitBgView) {
        _inviterPortraitBgView = [[RCloudImageView alloc] init];

        [self.view addSubview:_inviterPortraitBgView];
        [self.view insertSubview:_inviterPortraitBgView aboveSubview:self.backgroundView];
        _inviterPortraitBgView.hidden = YES;
        [_inviterPortraitBgView setPlaceholderImage:[RCCallKitUtility getDefaultPortraitImage]];
        _inviterPortraitBgView.layer.masksToBounds = YES;
        _inviterPortraitBgView.contentMode = UIViewContentModeScaleAspectFill;
    }
    return _inviterPortraitBgView;
}

- (UILabel *)inviterNameLabel {
    if (!_inviterNameLabel) {
        _inviterNameLabel = [[UILabel alloc] init];
        _inviterNameLabel.backgroundColor = [UIColor clearColor];
        _inviterNameLabel.textColor = [UIColor whiteColor];
        _inviterNameLabel.font = [UIFont systemFontOfSize:18];
        _inviterNameLabel.textAlignment = NSTextAlignmentCenter;
        _inviterNameLabel.text = self.mainModel.userInfo.name;
        _inviterNameLabel.layer.shadowOpacity = 0.8;
        _inviterNameLabel.layer.shadowRadius = 3.0;
        _inviterNameLabel.layer.shadowColor = [UIColor darkGrayColor].CGColor;
        _inviterNameLabel.layer.shadowOffset = CGSizeMake(0, 1);
        [self.view addSubview:_inviterNameLabel];
        _inviterNameLabel.hidden = YES;
    }
    return _inviterNameLabel;
}

- (UILabel *)mainNameLabel {
    if (!_mainNameLabel) {
        _mainNameLabel = [[UILabel alloc] init];
        _mainNameLabel.backgroundColor = [UIColor clearColor];
        _mainNameLabel.textColor = [UIColor whiteColor];
        _mainNameLabel.layer.shadowOpacity = 0.8;
        _mainNameLabel.layer.shadowRadius = 3.0;
        _mainNameLabel.layer.shadowColor = [UIColor darkGrayColor].CGColor;
        _mainNameLabel.layer.shadowOffset = CGSizeMake(0, 1);
        _mainNameLabel.font = [UIFont fontWithName:@"PingFangSC-Regular" size:18];
        _mainNameLabel.textAlignment = NSTextAlignmentLeft;
        _mainNameLabel.text = self.mainModel.userInfo.name;
        _mainNameLabel.textAlignment = NSTextAlignmentCenter;
        [self.view addSubview:_mainNameLabel];
        _mainNameLabel.hidden = YES;
    }
    return _mainNameLabel;
}

- (UILabel *)userCollectionTitleLabel {
    if (!_userCollectionTitleLabel) {
        _userCollectionTitleLabel = [[UILabel alloc] init];
        _userCollectionTitleLabel.backgroundColor = [UIColor clearColor];
        _userCollectionTitleLabel.textColor = [UIColor whiteColor];
        _userCollectionTitleLabel.font = [UIFont fontWithName:@"PingFangSC-Regular" size:16.0];
        _userCollectionTitleLabel.textAlignment = NSTextAlignmentCenter;
        _userCollectionTitleLabel.text = RCCallKitLocalizedString(@"VoIPMultiCallUserCollectionTitle");
        _userCollectionTitleLabel.layer.shadowOpacity = 0.8;
        _userCollectionTitleLabel.layer.shadowRadius = 3.0;
        _userCollectionTitleLabel.layer.shadowColor = [UIColor darkGrayColor].CGColor;
        _userCollectionTitleLabel.layer.shadowOffset = CGSizeMake(0, 1);
        [self.view addSubview:_userCollectionTitleLabel];
        _userCollectionTitleLabel.hidden = YES;
    }
    return _userCollectionTitleLabel;
}

- (UICollectionView *)userCollectionView {
    if (!_userCollectionView) {
        if (self.userCollectionViewLayout) {
            _userCollectionView = [[UICollectionView alloc] initWithFrame:CGRectZero
                                                     collectionViewLayout:self.userCollectionViewLayout];
        } else {
            RCVideoMultiCallUserCollectionLayout *userCollectionViewLayout =
                [[RCVideoMultiCallUserCollectionLayout alloc] initWithItemMargin:5];
            _userCollectionView = [[UICollectionView alloc] initWithFrame:CGRectZero
                                                     collectionViewLayout:userCollectionViewLayout];
        }
        _userCollectionView.backgroundColor = [UIColor clearColor];
        _userCollectionView.tag = 202872;
        [_userCollectionView setCallVideoMultiCallViewController:self];

        [self.view addSubview:_userCollectionView];
        _userCollectionView.hidden = YES;
        _userCollectionView.dataSource = self;
        _userCollectionView.delegate = self;
        [_userCollectionView registerClass:[RCCallMultiCallUserCell class]
                forCellWithReuseIdentifier:RongVoIPMultiVideoCellReuseID];
    }
    return _userCollectionView;
}

- (void)inviteUserButtonClicked {
    [self didTapInviteUserButton];

    if (self.callSession.isMultiCall) {
        [self inviteNewUser];
    } else {
        RCLogI(@"not support add user for conversation type %zd", self.callSession.conversationType);
    }
}

- (void)inviteNewUser {
    NSMutableArray *existUserIdList = [[NSMutableArray alloc] init];
    for (RCCallUserProfile *userProfile in self.callSession.userProfileList) {
        [existUserIdList addObject:userProfile.userId];
    }
    [existUserIdList addObject:currentUserId];

    __weak typeof(self) weakSelf = self;
    if ([RCCall sharedRCCall].callInviteNewUserDelegate &&
        [[RCCall sharedRCCall].callInviteNewUserDelegate
            respondsToSelector:@selector(inviteNewUser:targetId:mediaType:baseOn:selectResult:)]) {
        [[RCCall sharedRCCall].callInviteNewUserDelegate
            inviteNewUser:existUserIdList
                 targetId:self.targetId
                mediaType:self.mediaType
                   baseOn:self
             selectResult:^(NSArray<NSString *> *userIdList) {
                 [weakSelf.callSession inviteRemoteUsers:userIdList mediaType:weakSelf.mediaType];
             }];
    } else {
        RCCallSelectMemberViewController *selectViewController = [[RCCallSelectMemberViewController alloc]
            initWithConversationType:self.conversationType
                            targetId:self.targetId
                           mediaType:self.mediaType
                               exist:[existUserIdList copy]
                             success:^(NSArray *addUserIdList) {
                                 [weakSelf.callSession inviteRemoteUsers:addUserIdList mediaType:weakSelf.mediaType];
                             }];
        UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:selectViewController];
        nav.modalPresentationStyle = UIModalPresentationFullScreen;
        dispatch_async(dispatch_get_main_queue(), ^{
            [weakSelf presentViewController:nav animated:YES completion:nil];
        });
    }
}

- (void)inviteNewUserWithClickEvent {
    NSMutableArray *existUserIdList = [[NSMutableArray alloc] init];
    for (RCCallUserProfile *userProfile in self.callSession.userProfileList) {
        [existUserIdList addObject:userProfile.userId];
    }
    [existUserIdList addObject:currentUserId];

    __weak typeof(self) weakSelf = self;
    RCCallSelectMemberViewController *selectViewController = [[RCCallSelectMemberViewController alloc]
        initWithConversationType:self.conversationType
                        targetId:self.targetId
                       mediaType:self.mediaType
                           exist:existUserIdList
                         success:^(NSArray *addUserIdList) {
                             [weakSelf.callSession inviteRemoteUsers:addUserIdList mediaType:weakSelf.mediaType];
                         }];
    UINavigationController *rootVC = [[UINavigationController alloc] initWithRootViewController:selectViewController];
    rootVC.modalPresentationStyle = UIModalPresentationFullScreen;
    dispatch_async(dispatch_get_main_queue(), ^{
        [weakSelf presentViewController:rootVC animated:YES completion:nil];
    });
}

- (void)resetLayout:(BOOL)isMultiCall mediaType:(RCCallMediaType)mediaType callStatus:(RCCallStatus)sessionCallStatus {
    [super resetLayout:isMultiCall mediaType:mediaType callStatus:sessionCallStatus];

    RCCallStatus callStatus = sessionCallStatus;
    if ((callStatus == RCCallIncoming || callStatus == RCCallRinging) &&
        [RCCXCall sharedInstance].acceptedFromCallKit) {
        callStatus = RCCallActive;
        [RCCXCall sharedInstance].acceptedFromCallKit = NO;
    }

    self.blurView.hidden = YES;

    if (callStatus == RCCallIncoming || callStatus == RCCallRinging) {
        [self.inviterPortraitView setImageURL:[NSURL URLWithString:self.mainModel.userInfo.portraitUri]];
        self.inviterPortraitView.frame =
            CGRectMake((self.view.frame.size.width - RCCallHeaderLength) / 2,
                       RCCallTopGGradientHeight + RCCallStatusBarHeight, RCCallHeaderLength, RCCallHeaderLength);
        self.inviterPortraitView.hidden = NO;

        [self.inviterPortraitBgView setImageURL:[NSURL URLWithString:self.mainModel.userInfo.portraitUri]];
        self.inviterPortraitBgView.frame = CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height);
        self.inviterNameLabel.text = self.mainModel.userInfo.name;
        self.inviterNameLabel.frame =
            CGRectMake((self.view.frame.size.width - RCCallNameLabelWidth) / 2,
                       RCCallTopGGradientHeight + RCCallHeaderLength + RCCallTopMargin + RCCallStatusBarHeight,
                       RCCallNameLabelWidth, RCCallLabelHeight);
        self.inviterNameLabel.hidden = NO;
    } else {
        self.inviterNameLabel.hidden = YES;
        self.inviterPortraitView.hidden = YES;
    }

    if (callStatus == RCCallDialing) {
        [self.inviterPortraitBgView setImageURL:[NSURL URLWithString:self.mainModel.userInfo.portraitUri]];
        self.inviterPortraitBgView.frame = CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height);

        self.mainNameLabel.frame =
            CGRectMake((self.view.frame.size.width - RCCallNameLabelWidth) / 2,
                       RCCallMiniButtonTopMargin + RCCallStatusBarHeight, RCCallNameLabelWidth, RCCallLabelHeight);
        self.mainNameLabel.hidden = NO;
    } else if (callStatus == RCCallActive) {
        self.mainNameLabel.frame =
            CGRectMake((self.view.frame.size.width - RCCallNameLabelWidth) / 2,
                       RCCallMiniButtonTopMargin + RCCallStatusBarHeight, RCCallNameLabelWidth, RCCallLabelHeight);
        self.mainNameLabel.hidden = NO;
        self.inviterPortraitBgView.hidden = YES;

    } else {
        self.mainNameLabel.hidden = YES;
    }

    CGFloat titleY = MAX(RCCallVerticalMargin * 2 + RCCallHeaderLength + RCCallInsideMargin * 3 + RCCallLabelHeight * 2,
                         (self.view.frame.size.height - RCCallLabelHeight) / 2);
    CGFloat tipsLabelY = MIN(self.view.frame.size.height * 0.54,
                             self.view.frame.size.height - (RCCallButtonBottomMargin * 2 + RCCallButtonLength) - 95.0 -
                                 23 - 16.0 - 40.0 - RCCallExtraSpace);
    if (callStatus == RCCallIncoming || callStatus == RCCallRinging) {
        CGRect newFrame = self.tipsLabel.frame;
        newFrame.origin.y = tipsLabelY;
        self.tipsLabel.frame = newFrame;

        self.userCollectionTitleLabel.frame =
            CGRectMake(RCCallHorizontalMargin,
                       self.view.frame.size.height - (RCCallButtonBottomMargin * 2 + RCCallButtonLength) - 95.0 - 23 -
                           16.0 - RCCallExtraSpace,
                       self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
        self.userCollectionTitleLabel.hidden = NO;
        self.userCollectionTitleLabel.alpha = 0.4;
    } else {
        self.userCollectionTitleLabel.alpha = 1.0;
        self.userCollectionTitleLabel.hidden = YES;
        self.userCollectionTitleLabel.frame = CGRectMake(
            RCCallHorizontalMargin,
            self.view.frame.size.height - RCCallButtonBottomMargin - RCCallCustomButtonLength * 4.5 - RCCallExtraSpace,
            self.view.frame.size.width - RCCallHorizontalMargin * 2, RCCallLabelHeight);
    }

    if (callStatus == RCCallIncoming || callStatus == RCCallRinging) {
        self.userCollectionView.frame = CGRectMake(
            RCCallHorizontalMargin,
            self.view.frame.size.height - (RCCallButtonBottomMargin * 2 + RCCallButtonLength) - 95.0 - RCCallExtraSpace,
            self.view.frame.size.width - RCCallHorizontalMargin * 2, 55.0);
        self.userCollectionView.contentInset = UIEdgeInsetsMake(0, 20.0, 0, 20.0);

        if (self.userCollectionViewLayout) {
            self.userCollectionView.collectionViewLayout = self.userCollectionViewLayout;
        } else {
            UICollectionViewFlowLayout *userCollectionViewLayout = [[UICollectionViewFlowLayout alloc] init];
            userCollectionViewLayout.itemSize = CGSizeMake(55, 55);
            userCollectionViewLayout.scrollDirection = UICollectionViewScrollDirectionHorizontal;
            userCollectionViewLayout.minimumLineSpacing = 10.0;
            [self.userCollectionView setCollectionViewLayout:userCollectionViewLayout animated:YES];
            self.userCollectionView.showsHorizontalScrollIndicator = NO;
        }
        self.userCollectionView.hidden = NO;
    } else if (callStatus == RCCallDialing || (callStatus == RCCallActive && !self.isFullScreen)) {
        CGFloat width = (UIScreen.mainScreen.bounds.size.width - 40.0 - 20.0) / 4.5;

        self.userCollectionView.frame =
            CGRectMake(0,
                       self.view.frame.size.height - (RCCallButtonBottomMargin * 2 - 2.5 + RCCallButtonLength) -
                           width * 4 / 3 - 40.0 - RCCallExtraSpace,
                       self.view.frame.size.width, width * 4 / 3);
        self.userCollectionView.contentInset = UIEdgeInsetsMake(0, 20.0, 0, 20.0);

        if (self.userCollectionViewLayout) {
            self.userCollectionView.collectionViewLayout = self.userCollectionViewLayout;
        } else {
            UICollectionViewFlowLayout *userCollectionViewLayout = [[UICollectionViewFlowLayout alloc] init];
            userCollectionViewLayout.itemSize = CGSizeMake(width, width * 4 / 3);
            userCollectionViewLayout.scrollDirection = UICollectionViewScrollDirectionHorizontal;
            userCollectionViewLayout.minimumLineSpacing = 10.0;
            userCollectionViewLayout.scrollDirection = UICollectionViewScrollDirectionHorizontal;
            [self.userCollectionView setCollectionViewLayout:userCollectionViewLayout animated:YES];
            self.userCollectionView.showsHorizontalScrollIndicator = NO;
            self.userCollectionViewLayout = userCollectionViewLayout;
        }
        self.userCollectionView.showsHorizontalScrollIndicator = NO;
        self.userCollectionView.hidden = NO;
    } else if (callStatus == RCCallActive && self.isFullScreen) {
        self.userCollectionView.frame = CGRectMake(
            0, self.view.frame.size.height - RCCallButtonBottomMargin * 1 - RCCallButtonLength * 2.1 - RCCallExtraSpace,
            self.view.frame.size.width, RCCallButtonLength * 2.5);
        self.userCollectionView.hidden = NO;
        self.userCollectionView.showsHorizontalScrollIndicator = NO;
    }

    if (callStatus == RCCallActive) {
        self.minimizeButton.hidden = self.isFullScreen;
        self.handUpButton.hidden = self.isFullScreen;
        self.whiteBoardButton.hidden = self.isFullScreen;
        self.cameraSwitchButton.hidden = self.isFullScreen;
        self.addButton.hidden = self.isFullScreen;
        self.muteButton.hidden = self.isFullScreen;
        self.hangupButton.hidden = self.isFullScreen;
        self.cameraCloseButton.hidden = self.isFullScreen;
        self.mainNameLabel.hidden = self.isFullScreen;
        self.timeLabel.hidden = self.isFullScreen;
        self.signalImageView.hidden = self.isFullScreen;
    }
}

#pragma mark - RCCallSessionDelegate

/*!
 通话已接通
 */
- (void)callDidConnect {
    [self.userCollectionView removeFromSuperview];
    _userCollectionView = nil;
    [self userCollectionView];
    [self updateAllSubUserLayout];
    [self.callSession setVideoView:self.backgroundView userId:self.mainModel.userId];
    [super callDidConnect];
}

/*!
 对端正在振铃

 @param userId 对端的用户ID
 */
- (void)remoteUserDidRing:(NSString *)userId {
    RCCallUserCallInfoModel *model = [self getModelInSubUserModelList:userId];
    [self updateSubUserLayout:model];
}

/*!
 有用户被邀请加入通话

 @param userId    被邀请的用户ID
 @param mediaType 希望被邀请者选择的媒体类型
 */
- (void)remoteUserDidInvite:(NSString *)userId mediaType:(RCCallMediaType)mediaType {
    RCCallUserCallInfoModel *model = [self generateUserModel:userId];
    [self addSubUserModel:model];

    NSString *userName = [[RCUserInfoCacheManager sharedManager] getUserInfo:userId].name;
    if (userName) {
        NSString *inviteTips =
            [NSString stringWithFormat:RCCallKitLocalizedString(@"VoIPCallRemoteDidInvite"), userName];
        self.tipsLabel.text = inviteTips;

        __weak typeof(self) weakSelf = self;
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            if ([weakSelf.tipsLabel.text isEqualToString:inviteTips]) {
                weakSelf.tipsLabel.text = @"";
            }
        });
    }
}

/*!
 有用户加入了通话

 @param userId    用户ID
 @param mediaType 用户的媒体类型
 */
- (void)remoteUserDidJoin:(NSString *)userId mediaType:(RCCallMediaType)mediaType {
    if (![userId isEqualToString:self.mainModel.userId]) {
        RCCallUserCallInfoModel *model = [self getModelInSubUserModelList:userId];
        if (!model) {
            [self addSubUserModel:[self generateUserModel:userId]];
        } else {
            [self updateSubUserLayout:model];
        }
    }
}

/*!
 对端用户关闭/打开了摄像头

 @param userId    用户ID
 @param muted     是否关闭camera
 */
- (void)remoteUserDidDisableCamera:(BOOL)muted byUser:(NSString *)userId {
    if ([userId isEqualToString:self.mainModel.userId] && muted) {
        self.backgroundView.backgroundColor = RongVoIPUIColorFromRGB(0x262e42);
    } else {
        [self updateSubUserLayout:[self getModelInSubUserModelList:userId]];
    }
}

/*!
 有用户挂断

 @param userId 用户ID
 @param reason 挂断的原因
 */
- (void)remoteUserDidLeft:(NSString *)userId reason:(RCCallDisconnectReason)reason {
    if ([userId isEqualToString:self.mainModel.userId]) {
        if (self.callSession.callStatus == RCCallIncoming || self.callSession.callStatus == RCCallRinging ||
            self.callSession.callStatus == RCCallActive) {
            for (RCCallUserCallInfoModel *userModel in self.subUserModelList) {
                if ([userModel.userId isEqualToString:currentUserId]) {
                    [self removeSubUserModel:userModel];
                    break;
                }
            }

            self.mainModel = [self generateUserModel:currentUserId];
            [self.callSession setVideoView:self.backgroundView userId:self.mainModel.userId];
            self.mainNameLabel.text = self.mainModel.userInfo.name;
            if (self.callSession.callStatus == RCCallIncoming || self.callSession.callStatus == RCCallRinging) {
                self.inviterNameLabel.text = self.mainModel.userInfo.name;
            }

            [self updateAllSubUserLayout];
        }
    } else {
        for (RCCallUserCallInfoModel *userModel in self.subUserModelList) {
            if ([userId isEqualToString:userModel.userId]) {
                [self removeSubUserModel:userModel];
                break;
            }
        }
    }
}

#pragma mark - UICollectionViewDataSource
- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return self.subUserModelList.count;
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView
                  cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    RCCallMultiCallUserCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:RongVoIPMultiVideoCellReuseID
                                                                              forIndexPath:indexPath];
    RCCallUserCallInfoModel *userModel = self.subUserModelList[indexPath.row];
    [cell setModel:userModel status:self.callSession.callStatus];
    [self.callSession setVideoView:(UIView *)cell.headerImageView userId:userModel.userId];

    if (self.callSession.callStatus == RCCallIncoming || self.callSession.callStatus == RCCallRinging) {
    } else {
        cell.cellNameLabel.text = userModel.userInfo.name;
    }

    if (self.callSession.callStatus == RCCallActive && userModel.profile.callStatus == RCCallActive) {
        cell.headerImageView.image = nil;
    }
    return cell;
}

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath {
    if (self.callSession.callStatus == RCCallActive) {
        RCCallUserCallInfoModel *tempModel = self.mainModel;
        RCCallUserCallInfoModel *selectedModel = self.subUserModelList[indexPath.row];

        if (selectedModel.profile.callStatus != RCCallActive) {
            return;
        }

        self.mainModel = selectedModel;
        [self.callSession setVideoView:self.backgroundView userId:self.mainModel.userId];
        self.mainNameLabel.text = selectedModel.userInfo.name;
        [self.subUserModelList removeObject:selectedModel];
        [self.subUserModelList insertObject:tempModel atIndex:indexPath.row];

        [self updateSubUserLayout:tempModel];
    }
}

#pragma mark - UserInfo Update
- (void)onUserInfoUpdate:(NSNotification *)notification {
    NSDictionary *userInfoDic = notification.object;
    NSString *updateUserId = userInfoDic[@"userId"];
    RCUserInfo *updateUserInfo = userInfoDic[@"userInfo"];

    __weak typeof(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if ([updateUserId isEqualToString:weakSelf.mainModel.userId]) {
            weakSelf.mainModel.userInfo = updateUserInfo;
            weakSelf.mainNameLabel.text = updateUserInfo.name;
            weakSelf.inviterNameLabel.text = updateUserInfo.name;
            [weakSelf.inviterPortraitView setImageURL:[NSURL URLWithString:updateUserInfo.portraitUri]];
        } else {
            RCCallUserCallInfoModel *model = [weakSelf getModelInSubUserModelList:updateUserInfo.userId];
            if (model) {
                model.userInfo = updateUserInfo;
                [weakSelf updateSubUserLayout:model];
            }
        }
    });
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
