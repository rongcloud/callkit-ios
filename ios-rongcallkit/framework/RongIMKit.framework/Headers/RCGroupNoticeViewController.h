//
//  RCGroupNoticeViewController.h
//  RongIMKit
//
//  Created by zgh on 2024/8/28.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseViewController.h"
#import "RCGroupNoticeViewModel.h"
NS_ASSUME_NONNULL_BEGIN
/// 群公告页面
/// - Since: 5.12.0
@interface RCGroupNoticeViewController : RCBaseViewController

/// 实例化 RCGroupNoticeViewController
///
/// - Parameters viewModel: viewModel
- (instancetype)initWithViewModel:(RCGroupNoticeViewModel *)viewModel;

@end

NS_ASSUME_NONNULL_END
