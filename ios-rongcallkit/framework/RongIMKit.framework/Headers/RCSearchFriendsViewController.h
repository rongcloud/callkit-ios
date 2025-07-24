//
//  RCSearchFriendsViewController.h
//  RongIMKit
//
//  Created by RobinCui on 2024/9/4.
//  Copyright © 2024 RongCloud. All rights reserved.
//
#import "RCBaseViewController.h"
#import "RCSearchFriendsViewModel.h"

NS_ASSUME_NONNULL_BEGIN
/// 搜索好友列表
/// - Since: 5.12.0
@interface RCSearchFriendsViewController : RCBaseViewController

/// 实例化 RCSearchFriendsViewController
- (instancetype)initWithViewModel:(RCSearchFriendsViewModel *)viewModel;

@end

NS_ASSUME_NONNULL_END
