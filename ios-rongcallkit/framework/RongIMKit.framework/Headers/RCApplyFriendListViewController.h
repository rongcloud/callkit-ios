//
//  RCFriendApplyListViewController.h
//  RongIMKit
//
//  Created by RobinCui on 2024/8/23.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RongIMKit/RCApplyFriendListViewModel.h>
#import <RongIMKit/RCBaseViewController.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCApplyFriendListViewController : RCBaseViewController
- (instancetype)initWithViewModel:(RCApplyFriendListViewModel *)viewModel;
@end

NS_ASSUME_NONNULL_END
