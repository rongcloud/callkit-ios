//
//  RCAddFriendView.h
//  RongIMKit
//
//  Created by RobinCui on 2024/8/28.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseView.h"

NS_ASSUME_NONNULL_BEGIN
/// 搜索视图
/// - Since:5.12.0
@interface RCUserSearchView : RCBaseView

/// searchBar
@property (nonatomic, strong) UIView *searchBar;

/// 空视图
@property (nonatomic, strong) UILabel *labEmpty;

/// 在 view 上配置 searchBar
- (void)configureSearchBar:(UIView *)bar;
@end

NS_ASSUME_NONNULL_END
