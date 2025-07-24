//
//  RCFriendApplyCell.h
//  RongIMKit
//
//  Created by RobinCui on 2024/8/23.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RCBaseTableViewCell.h"
#import "RCApplyFriendCellViewModel.h"

UIKIT_EXTERN NSString * _Nullable const RCFriendApplyCellIdentifier;
UIKIT_EXTERN NSInteger const RCFriendApplyCellMargin;

@class RCloudImageView;

NS_ASSUME_NONNULL_BEGIN

/// 好友申请操作 cell
/// - Since:5.12.0
@interface RCApplyFriendCell : RCBaseTableViewCell
/*!
消息发送者的用户头像
*/
@property (nonatomic, strong) RCloudImageView *portraitImageView;
@property (nonatomic, strong) UILabel *labName;
@property (nonatomic, strong) UILabel *labRemark;
@property (nonatomic, strong) UIButton *btnExpand;
@property (nonatomic, strong) UIView *buttonsContainer;
@property (nonatomic, strong) UILabel *labStatus;
@property (nonatomic, strong) RCApplyFriendCellViewModel *viewModel;

- (void)updateWithViewModel:(RCApplyFriendCellViewModel *)viewModel;
@end
NS_ASSUME_NONNULL_END
