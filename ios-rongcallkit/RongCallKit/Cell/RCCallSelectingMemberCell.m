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
        self.selectedImageView.frame = CGRectMake(10, 25, 20, 20);
        [self.contentView addSubview:self.selectedImageView];

        self.headerImageView = [[RCloudImageView alloc] init];
        self.headerImageView.contentMode = UIViewContentModeScaleAspectFill;
        [self.headerImageView setPlaceholderImage:[RCCallKitUtility imageFromVoIPBundle:@"default_portrait_msg"]];

        self.headerImageView.frame = CGRectMake(40, 5, 45, 45);
        self.headerImageView.layer.masksToBounds = YES;
        if (RCKitConfigCenter.ui.globalConversationAvatarStyle == RC_USER_AVATAR_CYCLE &&
            RCKitConfigCenter.ui.globalMessageAvatarStyle == RC_USER_AVATAR_CYCLE) {
            self.headerImageView.layer.cornerRadius = self.headerImageView.frame.size.width / 2;
        } else {
            self.headerImageView.layer.cornerRadius = 5.f;
        }

        [self.contentView addSubview:self.headerImageView];

        self.nameLabel = [[UILabel alloc] init];
        self.nameLabel.frame = CGRectMake(110, 5, self.bounds.size.width - 110, 45);
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
