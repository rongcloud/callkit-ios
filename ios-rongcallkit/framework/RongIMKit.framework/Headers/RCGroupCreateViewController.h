//
//  RCGroupCreateViewController.h
//  RongIMKit
//
//  Created by zgh on 2024/8/22.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseViewController.h"
#import "RCGroupCreateViewModel.h"

NS_ASSUME_NONNULL_BEGIN
/// 创建群组
/// - Since: 5.12.0
@interface RCGroupCreateViewController : RCBaseViewController

/// 实例化 RCGroupCreateViewController
- (instancetype)initWithViewModel:(RCGroupCreateViewModel *)viewModel;

@end

NS_ASSUME_NONNULL_END
