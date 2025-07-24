//
//  RCSelectUserViewController.h
//  RongIMKit
//
//  Created by zgh on 2024/8/26.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseViewController.h"
#import "RCSelectUserViewModel.h"
NS_ASSUME_NONNULL_BEGIN
/// 选择联系人
/// - Since: 5.12.0
@interface RCSelectUserViewController : RCBaseViewController

/// 实例化 RCSelectUserViewController
- (instancetype)initWithViewModel:(RCSelectUserViewModel *)viewModel;

@end

NS_ASSUME_NONNULL_END
