//
//  RCGroupTransferOwnerViewController.h
//  RongIMKit
//
//  Created by zgh on 2024/8/26.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseViewController.h"
#import "RCGroupTransferViewModel.h"
NS_ASSUME_NONNULL_BEGIN
/// 群主转让页面
/// - Since: 5.12.2
@interface RCGroupTransferViewController : RCBaseViewController
/// 实例化 RCGroupTransferViewController
///
/// - Parameters viewModel: viewModel
- (instancetype)initWithViewModel:(RCGroupTransferViewModel *)viewModel;

@end

NS_ASSUME_NONNULL_END
