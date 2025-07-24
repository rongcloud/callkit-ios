//
//  RCGroupNotificationNaviItemsViewModel.h
//  RongIMKit
//
//  Created by RobinCui on 2024/11/14.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCNavigationItemsViewModel.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, RCGroupNotificationCategory) {
    RCGroupNotificationCategoryAll, // 全部
    RCGroupNotificationCategoryToBeConfirmed, // 待确认
    RCGroupNotificationCategoryDealt, // 已完成
    RCGroupNotificationCategoryExpired // 已过期
};

@protocol RCGroupNotificationNaviItemsViewModelDelegate <NSObject>

/// 用户选择展示类别
- (void)userDidSelectCategory:(RCGroupNotificationCategory)category;

@end

@interface RCGroupNotificationNaviItemsViewModel : RCNavigationItemsViewModel
/// 代理
@property (nonatomic, weak) id<RCGroupNotificationNaviItemsViewModelDelegate> delegate;
@end

NS_ASSUME_NONNULL_END
