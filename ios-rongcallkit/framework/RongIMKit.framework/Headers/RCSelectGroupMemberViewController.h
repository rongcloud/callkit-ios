//
//  RCSelectGroupMemberViewController.h
//  RongIMKit
//
//  Created by zgh on 2024/11/15.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseViewController.h"
#import "RCSelectGroupMemberViewModel.h"
NS_ASSUME_NONNULL_BEGIN
/// 选择群成员页面
/// - Since: 5.12.2
@interface RCSelectGroupMemberViewController : RCBaseViewController
/// 实例化 RCSelectGroupMemberViewController
///
/// - Parameters viewModel: viewModel
- (instancetype)initWithViewModel:(RCSelectGroupMemberViewModel *)viewModel;

@end

NS_ASSUME_NONNULL_END
