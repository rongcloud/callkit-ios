//
//  RCUAddFriendViewController.h
//  RongUserProfile
//
//  Created by RobinCui on 2024/8/16.
//

#import "RCBaseViewController.h"
#import "RCUserSearchViewModel.h"

NS_ASSUME_NONNULL_BEGIN

/// 搜索用户 VC
/// 
/// - Since: 5.12.0
@interface RCUserSearchViewController : RCBaseViewController

/// 初始化 RCUserSearchViewController
///
/// - Parameters viewModel: viewModel
- (instancetype)initWithViewModel:(RCUserSearchViewModel *)viewModel;
@end

NS_ASSUME_NONNULL_END
