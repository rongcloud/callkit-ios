//
//  RCMyGroupsView.h
//  RongIMKit
//
//  Created by RobinCui on 2024/11/20.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCSearchBarListView.h"

NS_ASSUME_NONNULL_BEGIN

@interface RCMyGroupsView : RCSearchBarListView

/// 添加刷新事件
- (void)addRefreshingTarget:(id)target withSelector:(SEL)selector;

/// 停止刷新
- (void)stopRefreshing;
@end

NS_ASSUME_NONNULL_END
