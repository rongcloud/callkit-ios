//
//  RCFriendApplyOperationCell.h
//  RongIMKit
//
//  Created by RobinCui on 2024/8/23.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCApplyFriendCell.h"

UIKIT_EXTERN NSString * _Nullable const RCFriendApplyOperationCellIdentifier;

NS_ASSUME_NONNULL_BEGIN
/// 好友申请操作 cell
/// - Since:5.12.0
@interface RCApplyFriendOperationCell : RCApplyFriendCell

/// 拒绝按钮
@property (nonatomic, strong) UIButton *btnReject;

/// 接受按钮
@property (nonatomic, strong) UIButton *btnApprove;

@end

NS_ASSUME_NONNULL_END
