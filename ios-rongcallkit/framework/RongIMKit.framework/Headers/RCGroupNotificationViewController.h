//
//  RCGroupNotificationViewController.h
//  RongIMKit
//
//  Created by RobinCui on 2024/11/14.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseViewController.h"
#import "RCGroupNotificationViewModel.h"
NS_ASSUME_NONNULL_BEGIN

@interface RCGroupNotificationViewController : RCBaseViewController
/// 实例化 RCGroupNotificationViewController
- (instancetype)initWithViewModel:(RCGroupNotificationViewModel *)viewModel;

@end

NS_ASSUME_NONNULL_END
