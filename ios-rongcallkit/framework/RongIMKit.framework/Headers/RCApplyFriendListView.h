//
//  RCFriendApplyListView.h
//  RongIMKit
//
//  Created by RobinCui on 2024/8/23.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseView.h"

NS_ASSUME_NONNULL_BEGIN
/// 申请好友列表
/// - Since:5.12.0
@interface RCApplyFriendListView : RCBaseView
/// tableView
@property (nonatomic, strong) UITableView *tableView;

/// 空视图
@property (nonatomic, strong) UILabel *labEmpty;

/// 添加刷新事件
- (void)addRefreshingTarget:(id)target withSelector:(SEL)selector;

/// 停止刷新
- (void)stopRefreshing;
@end

NS_ASSUME_NONNULL_END
