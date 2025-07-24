//
//  RCSearchFriendsViewModel.h
//  RongIMKit
//
//  Created by RobinCui on 2024/9/4.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RCBaseViewModel.h"
#import "RCListViewModelProtocol.h"
#import "RCNavigationItemsViewModel.h"
#import "RCSearchBarViewModel.h"

#import "RCCellViewModelProtocol.h"
#import "RCFriendListCellViewModel.h"
#import "RCFriendListPermanentCellViewModel.h"
NS_ASSUME_NONNULL_BEGIN
@class RCSearchFriendsViewModel;

@protocol RCSearchFriendsViewModelModelDelegate <NSObject>

@optional

/// 交付当前数据源给app处理
/// - Parameters:
///   - viewModel: viewModel
///   - dataSource: 当前数据源
///   - Returns: App处理后的数据源
///
///   - Since:
- (NSArray *_Nullable)searchFriendsViewModel:(RCSearchFriendsViewModel *_Nonnull)viewModel
                   willLoadItemsInDataSource:(NSArray *_Nullable)dataSource;

/// 配置自定义的导航按钮功能
/// - Parameter viewModel: viewModel
///   - Returns: 用户自定义的导航按钮功能
///
///   - Since:
- (RCNavigationItemsViewModel *_Nullable)willConfigureRightNavigationItemsForSearchFriendsViewModel:(RCSearchFriendsViewModel *_Nonnull)viewModel;


/// 配置自定义的搜索功能
/// - Parameter viewModel: viewModel
///   - Returns: 用户自定义的搜索功能
///
///   - Since:
- (RCSearchBarViewModel *_Nullable)willConfigureSearchBarViewModelForSearchFriendsViewModel:(RCSearchFriendsViewModel *_Nonnull)viewModel;

/// 用户点击Cell事件
/// - Parameters:
///   - viewModel: viewModel
///   - viewController: viewController
///   - tableView: tableView
///   - indexPath: indexPath
///   - viewModel: CellViewModel
///   - Returns: App是否处理[YES : SDK不再处理, NO: SDK处理]
///
///   - Since:
- (BOOL)searchFriendsViewModel:(RCSearchFriendsViewModel *_Nonnull)viewModel
                viewController:(UIViewController*_Nonnull)viewController
                     tableView:(UITableView *_Nonnull)tableView
                  didSelectRow:(NSIndexPath *_Nonnull)indexPath
                 cellViewModel:(RCBaseCellViewModel *_Nonnull)cellViewModel;
@end

@interface RCSearchFriendsViewModel : RCBaseViewModel<RCListViewModelProtocol>
@property (nonatomic, weak) id<RCSearchFriendsViewModelModelDelegate> _Nullable delegate;

- (NSArray *_Nonnull)configureRightNaviItemsForViewController:(UIViewController *_Nonnull)viewController;
- (UISearchBar *_Nonnull)configureSearchBarForViewController:(UIViewController *_Nonnull)viewController;
- (NSArray *_Nonnull)sectionIndexTitles;
- (void)bindResponder:(id<RCListViewModelResponder>_Nonnull)responder;
- (void)endEditingState;
@end
NS_ASSUME_NONNULL_END
