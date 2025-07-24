//
//  RCGroupMembersViewController.h
//  RongIMKit
//
//  Created by zgh on 2024/8/26.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseViewController.h"
#import "RCGroupMemberListViewModel.h"
NS_ASSUME_NONNULL_BEGIN

@interface RCGroupMemberListViewController : RCBaseViewController

- (instancetype)initWithViewModel:(RCGroupMemberListViewModel *)viewModel;

@end

NS_ASSUME_NONNULL_END
