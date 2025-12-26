//
//  RCGroupNotificationView.h
//  RongIMKit
//
//  Created by RobinCui on 2024/11/14.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCSearchBarListView.h"

NS_ASSUME_NONNULL_BEGIN

@interface RCGroupNotificationView : RCSearchBarListView
/// 添加刷新事件
- (void)addRefreshingTarget:(id)target withSelector:(SEL)selector;

/// 停止刷新
- (void)stopRefreshing;
@end

NS_ASSUME_NONNULL_END
