//
//  RCGroupManagersController.h
//  RongIMKit
//
//  Created by zgh on 2024/11/25.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseViewController.h"
#import "RCGroupManagerListViewModel.h"

NS_ASSUME_NONNULL_BEGIN
/// 群管理员页面
/// - Since: 5.12.2
@interface RCGroupManagerListController : RCBaseViewController
/// 实例化 RCGroupManagerListController
///
/// - Parameters viewModel: viewModel
- (instancetype)initWithViewModel:(RCGroupManagerListViewModel *)viewModel;

@end

NS_ASSUME_NONNULL_END
