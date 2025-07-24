//
//  RCGroupManagementViewController.h
//  RongIMKit
//
//  Created by zgh on 2024/11/25.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseViewController.h"
#import "RCGroupManagementViewModel.h"

NS_ASSUME_NONNULL_BEGIN
/// 群管理页面
/// - Since: 5.12.2
@interface RCGroupManagementViewController : RCBaseViewController
/// 实例化 RCGroupManagementViewController
///
/// - Parameters viewModel: viewModel
- (instancetype)initWithViewModel:(RCGroupManagementViewModel *)viewModel;

@end

NS_ASSUME_NONNULL_END
