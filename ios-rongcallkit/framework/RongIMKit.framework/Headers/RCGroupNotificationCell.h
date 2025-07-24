//
//  RCGroupNotificationCell.h
//  RongIMKit
//
//  Created by RobinCui on 2024/11/14.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseTableViewCell.h"
#import "RCGroupNotificationCellViewModel.h"
@class RCloudImageView;
UIKIT_EXTERN NSString * _Nullable const RCGroupNotificationCellIdentifier;
UIKIT_EXTERN NSInteger const RCGroupNotificationCellHorizontalMargin;
UIKIT_EXTERN NSInteger const RCGroupNotificationCellPortraitWidth;
UIKIT_EXTERN NSInteger const RCGroupNotificationCellVerticalMargin;

NS_ASSUME_NONNULL_BEGIN

@interface RCGroupNotificationCell : RCBaseTableViewCell
/*!
消息发送者的用户头像
*/
@property (nonatomic, strong) RCloudImageView *portraitImageView;
@property (nonatomic, strong) UILabel *labName;
@property (nonatomic, strong) UILabel *labTips;
@property (nonatomic, strong) UILabel *labStatus;
@property (nonatomic, strong) RCGroupNotificationCellViewModel *viewModel;
/// 拒绝按钮
@property (nonatomic, strong) UIButton *btnReject;

/// 确认按钮
@property (nonatomic, strong) UIButton *btnApprove;


@property (nonatomic, strong) UIView *buttonsContainer;

/// 更新Cell 信息
/// - Parameter viewModel: vm
- (void)updateWithViewModel:(RCGroupNotificationCellViewModel *)viewModel;

/// 显示头像
/// - Parameter url: 头像地址
- (void)showPortrait:(NSString *)url;

@end

NS_ASSUME_NONNULL_END
