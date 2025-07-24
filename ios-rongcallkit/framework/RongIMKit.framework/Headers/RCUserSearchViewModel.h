//
//  RCAddFriendViewModel.h
//  RongIMKit
//
//  Created by RobinCui on 2024/8/28.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseViewModel.h"
#import "RCListViewModelProtocol.h"
#import "RCNavigationItemsViewModel.h"
#import "RCCellViewModelProtocol.h"
#import "RCSearchUserProfileViewModel.h"
#import <RongIMLibCore/RongIMLibCore.h>

NS_ASSUME_NONNULL_BEGIN
@class RCUserSearchViewModel;
@protocol RCUserSearchViewModelDelegate <NSObject>
@optional
/// 配置自定义的导航按钮功能
/// - Parameter viewModel: viewModel
///   - Returns: 用户自定义的导航按钮功能
///
///   - Since:
- (RCNavigationItemsViewModel *_Nullable)willConfigureRightNavigationItemsForUserSearchViewModel:(RCUserSearchViewModel *)viewModel;

/// 配置自定义的搜索功能
/// - Parameter viewModel: viewModel
///   - Returns: 用户自定义的搜索功能
///
///   - Since:
- (RCSearchUserProfileViewModel *_Nullable)willConfigureSearchBarViewModelForUserSearchViewModel:(RCUserSearchViewModel *)viewModel;

/// 触发搜索用户事件
/// - Parameters:
///   - viewModel: viewModel
///   - text: 搜索关键字
///   - Returns: App是否处理[YES : SDK不再处理, NO: SDK处理]
///
///   - Since:
- (BOOL)userSearchViewModel:(RCUserSearchViewModel *)viewModel searchUserProfileWithText:(NSString *)text;

/// 显示用户详情
/// - Parameters:
///   - viewModel: viewModel
///   - profile: 用户信息
///   - Returns: App是否处理[YES : SDK不再处理, NO: SDK处理]
///
///   - Since:
- (BOOL)userSearchViewModel:(RCUserSearchViewModel *)viewModel showUserProfile:(RCUserProfile *)profile;
@end

/// 搜索用户 ViewModel
/// - Since: 5.12.0
@interface RCUserSearchViewModel : RCBaseViewModel

/// 代理
@property (nonatomic, weak) id<RCUserSearchViewModelDelegate> delegate;

/// 配置导航按钮
- (NSArray *)configureRightNaviItemsForViewController:(UIViewController *)viewController;

/// 配置searchBar
- (UISearchBar *)configureSearchBarForViewController:(UIViewController *)viewController;

/// 绑定响应器
- (void)bindResponder:(UIViewController <RCListViewModelResponder>*)responder;

/// 停止编辑
- (void)endEditingState;
@end

NS_ASSUME_NONNULL_END
