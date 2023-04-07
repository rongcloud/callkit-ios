//
//  RCCallSelectingMemberCell.m
//  RongCallKit
//
//  Created by RongCloud on 16/3/15.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCCallSelectingMemberCell.h"
#import "RCCallKitUtility.h"

@implementation RCCallSelectingMemberCell

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        self.selectedImageView = [[UIImageView alloc] init];
        self.selectedImageView.translatesAutoresizingMaskIntoConstraints = NO;
        [self.contentView addSubview:self.selectedImageView];

        NSLayoutConstraint *selectedImageViewLeadingConstraint = [self.selectedImageView.leadingAnchor constraintEqualToAnchor:self.contentView.leadingAnchor constant:10];
        NSLayoutConstraint *selectedImageViewTopConstraint = [self.selectedImageView.topAnchor constraintEqualToAnchor:self.contentView.topAnchor constant:17.5];
        NSLayoutConstraint *selectedImageViewWidthConstraint = [self.selectedImageView.widthAnchor constraintEqualToConstant:20];
        NSLayoutConstraint *selectedImageViewHeightConstraint = [self.selectedImageView.heightAnchor constraintEqualToConstant:20];

        [self.contentView addConstraints:@[selectedImageViewLeadingConstraint, selectedImageViewTopConstraint, selectedImageViewWidthConstraint, selectedImageViewHeightConstraint]];


        self.headerImageView = [[RCloudImageView alloc] init];
        self.headerImageView.layer.masksToBounds = YES;
        if (RCKitConfigCenter.ui.globalConversationAvatarStyle == RC_USER_AVATAR_CYCLE &&
            RCKitConfigCenter.ui.globalMessageAvatarStyle == RC_USER_AVATAR_CYCLE) {
            self.headerImageView.layer.cornerRadius = 45 / 2;
        } else {
            self.headerImageView.layer.cornerRadius = 5.f;
        }
        self.headerImageView.translatesAutoresizingMaskIntoConstraints = NO;

        [self.contentView addSubview:self.headerImageView];
        
        NSLayoutConstraint *headerImageViewLeadingConstraint = [self.headerImageView.leadingAnchor constraintEqualToAnchor:self.contentView.leadingAnchor constant:40];
        NSLayoutConstraint *headerImageViewTopConstraint = [self.headerImageView.topAnchor constraintEqualToAnchor:self.contentView.topAnchor constant:5];
        NSLayoutConstraint *headerImageViewWidthConstraint = [self.headerImageView.widthAnchor constraintEqualToConstant:45];
        NSLayoutConstraint *headerImageViewHeightConstraint = [self.headerImageView.heightAnchor constraintEqualToConstant:45];

        [self.contentView addConstraints:@[headerImageViewLeadingConstraint, headerImageViewTopConstraint, headerImageViewWidthConstraint, headerImageViewHeightConstraint]];
        [self.headerImageView setPlaceholderImage:[RCCallKitUtility imageFromVoIPBundle:@"default_portrait_msg"]];

        self.nameLabel = [[UILabel alloc] init];
        self.nameLabel.frame = CGRectMake(110, 5, self.bounds.size.width - 150, 45);
        [self.contentView addSubview:self.nameLabel];
        self.backgroundColor = [RCKitUtility generateDynamicColor:hex_rgb(0xffffff)
                                                        darkColor:[hex_rgb(0x1c1c1e) colorWithAlphaComponent:0.4]];
    }
    return self;
}

- (void)layoutSubviews {
    [super layoutSubviews];
}

- (void)awakeFromNib {
    // Initialization code
    [super awakeFromNib];
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];
}

@end
