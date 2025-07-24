//
//  RCApplyNaviItemsViewModel.h
//  RongIMKit
//
//  Created by RobinCui on 2024/8/27.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCNavigationItemsViewModel.h"

typedef NS_ENUM(NSInteger ,RCApplicationCategory) {
    RCApplicationCategoryBoth,
    RCApplicationCategoryReceived,
    RCApplicationCategorySent
};
NS_ASSUME_NONNULL_BEGIN

@protocol RCApplyNaviItemsViewModelDelegate <NSObject>

/// 用户选择展示类别
- (void)userDidSelectCategory:(RCApplicationCategory)category;

@end

/// 申请页导航 ViewModel
/// - Since:5.12.0
@interface RCApplyNaviItemsViewModel : RCNavigationItemsViewModel

/// 代理
@property (nonatomic, weak) id<RCApplyNaviItemsViewModelDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
