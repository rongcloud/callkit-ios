//
//  RCSearchGroupsViewController.h
//  RongIMKit
//
//  Created by RobinCui on 2024/11/21.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseViewController.h"
#import "RCSearchGroupsViewModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface RCSearchGroupsViewController : RCBaseViewController
/// 实例化 RCSearchGroupsViewController
- (instancetype)initWithViewModel:(RCSearchGroupsViewModel *)viewModel;
@end

NS_ASSUME_NONNULL_END
