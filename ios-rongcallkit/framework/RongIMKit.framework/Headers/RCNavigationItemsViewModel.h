//
//  RCUFriendListNaviItemsViewModel.h
//  RongUserProfile
//
//  Created by RobinCui on 2024/8/16.
//

#import <UIKit/UIKit.h>
#import "RCBaseViewModel.h"

NS_ASSUME_NONNULL_BEGIN
/// 导航 viewModel
@interface RCNavigationItemsViewModel : RCBaseViewModel

/// 响应器
@property (nonatomic, weak) UIViewController *responder;

/// 初始化
- (instancetype)initWithResponder:(UIViewController *)responder;

/// 导航右按钮
- (NSArray *)rightNavigationBarItems;
@end

NS_ASSUME_NONNULL_END
