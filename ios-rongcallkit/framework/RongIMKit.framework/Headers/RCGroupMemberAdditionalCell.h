//
//  RCGroupMemberAddtionalCell.h
//  RongIMKit
//
//  Created by RobinCui on 2025/11/11.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import "RCStackTableViewCell.h"
UIKIT_EXTERN NSString * _Nullable const RCGroupMemberAdditionalCellIdentifier;

NS_ASSUME_NONNULL_BEGIN

@interface RCGroupMemberAdditionalCell : RCStackTableViewCell
@property (nonatomic, strong) UIImageView *portraitImageView;
@property (nonatomic, strong) UILabel *labName;
- (void)showPortraitByImage:(UIImage *)image;
@end

NS_ASSUME_NONNULL_END
