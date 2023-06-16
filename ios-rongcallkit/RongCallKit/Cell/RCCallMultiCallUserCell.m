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
@end

@implementation RCCallMultiCallUserCell

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        self.contentView.backgroundColor = [UIColor clearColor];
        [self.contentView addSubview:self.headerImageView];
        [self.contentView addSubview:self.nameLabel];
        [self.contentView addSubview:self.statusLabel];
        [self.contentView addSubview:self.cellNameLabel];
    }
    return self;
}

- (void)setModel:(RCCallUserCallInfoModel *)model status:(RCCallStatus)callStatus {
    _model = model;
    self.callStatus = callStatus;

    CGFloat nameLabelHeight = 16;
    CGFloat insideMargin = 5;
    
    if (callStatus == RCCallIncoming || callStatus == RCCallRinging || model.profile.mediaType == RCCallMediaVideo) {
        nameLabelHeight = 0;
        insideMargin = 0;
    }

    if ((callStatus == RCCallDialing || callStatus == RCCallActive) && model.profile.mediaType == RCCallMediaVideo) {
        
    } else {
        self.headerImageView.backgroundColor = [[UIColor clearColor] colorWithAlphaComponent:1.0];
        self.headerImageView.layer.edgeAntialiasingMask =
            kCALayerLeftEdge | kCALayerRightEdge | kCALayerBottomEdge | kCALayerTopEdge;
    }

    if (model.profile.mediaType == RCCallMediaAudio) {
        [self resetLayout:nameLabelHeight insideMargin:insideMargin];
    } else {
        [self resetLayoutWithVideo:nameLabelHeight insideMargin:insideMargin];
    }

    [self.headerImageView setImageURL:[NSURL URLWithString:model.userInfo.portraitUri]];
    [self.nameLabel setText:model.userInfo.name];
    self.headerImageView.hidden = NO;

}

- (void)resetLayout:(CGFloat)nameLabelHeight insideMargin:(CGFloat)insideMargin {
    CGFloat minLength = MIN(self.bounds.size.width, self.bounds.size.height - nameLabelHeight - insideMargin);

    self.headerImageView.frame = CGRectMake((self.bounds.size.width - minLength) / 2, 0, minLength, minLength);
    self.headerImageView.hidden = NO;
    
    if (RCKitConfigCenter.ui.globalConversationAvatarStyle == RC_USER_AVATAR_CYCLE &&
        RCKitConfigCenter.ui.globalMessageAvatarStyle == RC_USER_AVATAR_CYCLE) {
        self.headerImageView.layer.cornerRadius = minLength/2;
    }
    
    self.nameLabel.font = [UIFont fontWithName:@"PingFangSC-Regular" size:11];
    self.nameLabel.frame =
        CGRectMake(0, self.bounds.size.height - nameLabelHeight, self.bounds.size.width, nameLabelHeight);
    if (nameLabelHeight > 0) {
        self.nameLabel.hidden = NO;
    } else {
        self.nameLabel.hidden = YES;
    }

    self.statusLabel.frame =
        CGRectMake((self.bounds.size.width - self.headerImageView.frame.size.width) / 2,0,self.headerImageView.frame.size.width, self.headerImageView.frame.size.width);
    if (self.callStatus == RCCallIncoming || self.callStatus == RCCallRinging){
        self.headerImageView.alpha = 1;
        self.statusLabel.hidden = YES;
    }
    else if (self.callStatus == RCCallActive) {
        if (_model.profile.callStatus == RCCallIncoming || _model.profile.callStatus == RCCallRinging) {
            self.statusLabel.hidden = NO;
            self.headerImageView.alpha = 0.5;
        } else {
            self.statusLabel.hidden = YES;
            self.headerImageView.alpha = 1;
        }
    }
    else {
        self.statusLabel.hidden = NO;
        self.headerImageView.alpha = 0.5;
    }
}

- (void)resetLayoutWithVideo:(CGFloat)nameLabelHeight insideMargin:(CGFloat)insideMargin {
    self.headerImageView.frame = self.bounds;
    self.headerImageView.hidden = NO;

    self.nameLabel.frame =
        CGRectMake(0, self.bounds.size.height - nameLabelHeight - 5, self.bounds.size.width, nameLabelHeight);
    if (nameLabelHeight > 0) {
        self.nameLabel.hidden = NO;
    } else {
        self.nameLabel.hidden = YES;
    }

    self.statusLabel.frame = CGRectMake((self.bounds.size.width - self.headerImageView.frame.size.width) / 2,(self.bounds.size.height - self.headerImageView.frame.size.height) / 2,self.headerImageView.frame.size.width, self.headerImageView.frame.size.height);

    if (_model.profile.callStatus == RCCallIncoming ||
        _model.profile.callStatus == RCCallRinging ||
        _model.profile.callStatus == RCCallDialing) {
        
        if (self.callStatus == RCCallIncoming ||
            self.callStatus == RCCallRinging) {
            self.statusLabel.hidden = YES;
            self.headerImageView.alpha = 1;
        } else {
            self.statusLabel.hidden = NO;
            self.headerImageView.alpha = 0.5;
        }
    } else {
        self.statusLabel.hidden = YES;
        self.headerImageView.alpha = 1;
    }
}

- (RCloudImageView *)headerImageView {
    if (!_headerImageView) {
        _headerImageView = [[RCloudImageView alloc] initWithFrame:CGRectZero];
        _headerImageView.autoresizingMask = UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth;
        _headerImageView.contentMode = UIViewContentModeScaleAspectFill;
        _headerImageView.layer.masksToBounds = YES;
        _headerImageView.layer.borderWidth = 1;
        _headerImageView.layer.borderColor = [[UIColor whiteColor] CGColor];
        [_headerImageView setPlaceholderImage:[RCCallKitUtility imageFromVoIPBundle:@"default_portrait_msg"]];
        _headerImageView.hidden = YES;
    }
    return _headerImageView;
}

- (UILabel *)nameLabel {
    if (!_nameLabel) {
        _nameLabel = [[UILabel alloc] initWithFrame:CGRectZero];
        _nameLabel.textColor = [UIColor whiteColor];
        _nameLabel.textAlignment = NSTextAlignmentCenter;
        _nameLabel.backgroundColor = [UIColor clearColor];
        _nameLabel.font = [UIFont fontWithName:@"PingFangSC-Regular" size:14];
        _nameLabel.hidden = YES;
    }
    return _nameLabel;
}

- (UILabel *)statusLabel {
    if (!_statusLabel) {
        _statusLabel = [[UILabel alloc] initWithFrame:CGRectZero];
        _statusLabel.text = @"连接中";
        _statusLabel.font = [UIFont fontWithName:@"PingFangSC-Regular" size:13];
        _statusLabel.textAlignment = NSTextAlignmentCenter;
        _statusLabel.textColor = [UIColor whiteColor];
        _statusLabel.hidden = YES;
    }
    return _statusLabel;
    
}

- (UILabel *)cellNameLabel {
    if (!_cellNameLabel) {
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
            CGRectMake(0, self.bounds.size.height - 16 - RCCallInsideMargin, self.bounds.size.width, 16);
    }
    return _cellNameLabel;
}

@end
