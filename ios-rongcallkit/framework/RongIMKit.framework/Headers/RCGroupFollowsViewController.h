//
//  RCGroupFollowsViewController.h
//  RongIMKit
//
//  Created by zgh on 2024/11/20.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseViewController.h"
#import "RCGroupFollowsViewModel.h"

NS_ASSUME_NONNULL_BEGIN
/// 群特别关注页面
/// - Since: 5.12.2
@interface RCGroupFollowsViewController : RCBaseViewController
/// 实例化 RCGroupFollowsViewController
///
/// - Parameters viewModel: viewModel
- (instancetype)initWithViewModel:(RCGroupFollowsViewModel *)viewModel;

@end

NS_ASSUME_NONNULL_END
