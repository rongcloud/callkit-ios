//
//  RCCallMultiCallUserCell.m
//  RongCallKit
//
//  Created by litao on 16/3/22.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCCallMultiCallUserCell.h"
#import "RCCallKitUtility.h"
#import "RCloudImageView.h"
#import "RongCallKitAdaptiveHeader.h"

@interface RCCallMultiCallUserCell ()

@property (nonatomic, strong) RCCallUserCallInfoModel *model;
@property (nonatomic, assign) RCCallStatus callStatus;
@property (nonatomic, strong) UIVisualEffectView *blurView;

@end

@implementation RCCallMultiCallUserCell

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        self.contentView.backgroundColor = [UIColor clearColor];
    
        self.headerImageView = [[RCloudImageView alloc] initWithFrame:CGRectZero];
        self.headerImageView.autoresizingMask = UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth;
        self.headerImageView.contentMode = UIViewContentModeScaleAspectFill;
        self.headerImageView.clipsToBounds = YES;
        self.headerImageView.layer.borderWidth = 1;
        self.headerImageView.layer.borderColor = [[UIColor whiteColor] CGColor];
        
        UIVisualEffect *blurEffect = [UIBlurEffect effectWithStyle:UIBlurEffectStyleDark];
        self.blurView = [[UIVisualEffectView alloc] initWithEffect:blurEffect];
        self.blurView.frame = self.headerImageView.frame;
        [self.headerImageView setPlaceholderImage:[RCCallKitUtility imageFromVoIPBundle:@"default_portrait_msg"]];
        self.headerImageView.hidden = YES;
        [self.contentView addSubview:self.headerImageView];

        self.nameLabel = [[UILabel alloc] initWithFrame:CGRectZero];
        self.nameLabel.textColor = [UIColor whiteColor];
        self.nameLabel.textAlignment = NSTextAlignmentCenter;
        self.nameLabel.backgroundColor = [UIColor clearColor];
        self.nameLabel.font = [UIFont fontWithName:@"PingFangSC-Regular" size:14];
        self.nameLabel.hidden = YES;
        [self.contentView addSubview:self.nameLabel];
        
        self.statusView = [[UIImageView alloc] initWithFrame:CGRectZero];
        [self.statusView setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/voip_connecting"]];
        self.statusView.hidden = YES;
        [self.contentView addSubview:self.statusView];

        _cellNameLabel = [[UILabel alloc] init];
        _cellNameLabel.backgroundColor = [UIColor clearColor];
        _cellNameLabel.textColor = [UIColor whiteColor];
        _cellNameLabel.layer.shadowOpacity = 0.8;
        _cellNameLabel.layer.shadowRadius = 3.0;
        _cellNameLabel.layer.shadowColor = [UIColor darkGrayColor].CGColor;
        _cellNameLabel.layer.shadowOffset = CGSizeMake(0, 1);
        _cellNameLabel.font = [UIFont systemFontOfSize:14];
        _cellNameLabel.textAlignment = NSTextAlignmentCenter;
        _cellNameLabel.frame =
            CGRectMake(0, self.frame.size.height - 16 - RCCallInsideMargin, self.frame.size.width, 16);
        [self.contentView addSubview:self.cellNameLabel];
    }
    return self;
}

- (void)setModel:(RCCallUserCallInfoModel *)model status:(RCCallStatus)callStatus {
    _model = model;
    self.callStatus = callStatus;

    CGFloat nameLabelHeight = 16;
    CGFloat insideMargin = 5;

    if ((callStatus == RCCallDialing || callStatus == RCCallActive) && model.profile.mediaType == RCCallMediaVideo) {
        
    } else {
        self.headerImageView.layer.borderWidth = 1;
        self.headerImageView.layer.borderColor = [UIColor whiteColor].CGColor;
        self.headerImageView.layer.masksToBounds = YES;
        if (RCKitConfigCenter.ui.globalConversationAvatarStyle == RC_USER_AVATAR_CYCLE &&
            RCKitConfigCenter.ui.globalMessageAvatarStyle == RC_USER_AVATAR_CYCLE) {
            self.headerImageView.layer.cornerRadius =
                MIN(self.bounds.size.width, self.bounds.size.height - nameLabelHeight - insideMargin) / 2;
        } else {
            self.headerImageView.layer.cornerRadius = 4.f;
        }
        self.headerImageView.backgroundColor = [[UIColor clearColor] colorWithAlphaComponent:1.0];
        self.headerImageView.layer.edgeAntialiasingMask =
            kCALayerLeftEdge | kCALayerRightEdge | kCALayerBottomEdge | kCALayerTopEdge;
    }

    if (callStatus == RCCallIncoming ||
        callStatus == RCCallRinging ||
        model.profile.mediaType == RCCallMediaVideo) {
        nameLabelHeight = 0;
        insideMargin = 0;
    }

    if (model.profile.mediaType == RCCallMediaAudio) {
        [self resetLayout:nameLabelHeight insideMargin:insideMargin];
    } else {
        [self resetLayoutWithVideo:nameLabelHeight insideMargin:insideMargin];
    }

    [self.headerImageView setImageURL:[NSURL URLWithString:model.userInfo.portraitUri]];
    [self.nameLabel setText:model.userInfo.name];
    self.headerImageView.hidden = NO;
    
    if (callStatus == RCCallDialing || callStatus == RCCallRinging || callStatus == RCCallIncoming) {
        self.headerImageView.alpha = 0.5;
    } else {
        self.headerImageView.alpha = 1.0;
    }
}

- (void)resetLayout:(CGFloat)nameLabelHeight insideMargin:(CGFloat)insideMargin {
    CGFloat minLength = MIN(self.bounds.size.width, self.bounds.size.height - nameLabelHeight - insideMargin);

    self.headerImageView.frame = CGRectMake((self.bounds.size.width - minLength) / 2, 0, minLength, minLength);
    self.headerImageView.hidden = NO;

    self.nameLabel.font = [UIFont fontWithName:@"PingFangSC-Regular" size:11];
    self.nameLabel.frame =
        CGRectMake(0, self.bounds.size.height - nameLabelHeight, self.bounds.size.width, nameLabelHeight);
    if (nameLabelHeight > 0) {
        self.nameLabel.hidden = NO;
    } else {
        self.nameLabel.hidden = YES;
    }

    self.statusView.frame =
        CGRectMake((self.bounds.size.width - 17) / 2, (self.headerImageView.frame.size.width - 4) / 2, 17, 4);
    //只有呼出状态需要 ... loading UI
    self.statusView.hidden = self.callStatus != RCCallDialing;
}

- (void)resetLayoutWithVideo:(CGFloat)nameLabelHeight insideMargin:(CGFloat)insideMargin {
    self.headerImageView.frame = self.bounds;
    self.headerImageView.hidden = NO;

    self.nameLabel.frame =
        CGRectMake(0, self.bounds.size.height - nameLabelHeight - 10, self.bounds.size.width, nameLabelHeight);
    if (nameLabelHeight > 0) {
        self.nameLabel.hidden = NO;
    } else {
        self.nameLabel.hidden = YES;
    }

    self.statusView.frame = CGRectMake((self.bounds.size.width - 20.0), 13.5, 17, 4);
    //    self.statusView.contentMode = UIViewContentModeScaleAspectFit;

    if (self.callStatus == RCCallIncoming || self.callStatus == RCCallRinging) {
        self.statusView.hidden = YES;
        self.nameLabel.hidden = YES;
    } else {
        self.nameLabel.hidden = NO;
        if (self.callStatus == RCCallIncoming ||
            self.callStatus == RCCallRinging ||
            self.callStatus == RCCallDialing) {
            self.statusView.hidden = NO;
        } else {
            self.statusView.hidden = YES;
        }
    }
}
@end
