//
//  RCUFriendListViewController.h
//  RongUserProfile
//
//  Created by RobinCui on 2024/8/16.
//

#import "RCBaseViewController.h"
#import "RCFriendListViewModel.h"

NS_ASSUME_NONNULL_BEGIN
/// 好友列表
/// - Since: 5.12.0
@interface RCFriendListViewController : RCBaseViewController

/// 实例化 RCFriendListViewController
- (instancetype)initWithViewModel:(RCFriendListViewModel *)viewModel;

@end

NS_ASSUME_NONNULL_END
