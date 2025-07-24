//
//  RCMyGroupsViewController.h
//  RongIMKit
//
//  Created by RobinCui on 2024/11/20.
//  Copyright © 2024 RongCloud. All rights reserved.
//
#import <UIKit/UIKit.h>
#import "RCBaseViewController.h"
#import "RCMyGroupsViewModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface RCMyGroupsViewController : RCBaseViewController
/// 实例化 RCMyGroupsViewController
- (instancetype)initWithViewModel:(RCMyGroupsViewModel *)viewModel;

@end

NS_ASSUME_NONNULL_END
