//
//  RCCallSelectingMemberCell.m
//  RongCallKit
//
//  Created by 岑裕 on 16/3/15.
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
        [self.headerImageView
            setPlaceholderImage:[RCKitUtility imageNamed:@"default_portrait_msg" ofBundle:@"RongCloud.bundle"]];
        self.headerImageView.frame = CGRectMake(40, 5, 60, 60);

        self.headerImageView.layer.cornerRadius = 5;
        self.headerImageView.layer.masksToBounds = YES;

        [self.contentView addSubview:self.headerImageView];

        self.nameLabel = [[UILabel alloc] init];
        self.nameLabel.frame = CGRectMake(110, 5, self.bounds.size.width - 110, 60);
        self.nameLabel.textColor = [UIColor whiteColor];
        [self.contentView addSubview:self.nameLabel];

        self.contentView.backgroundColor = RongVoIPUIColorFromRGB(0x262e42);
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
