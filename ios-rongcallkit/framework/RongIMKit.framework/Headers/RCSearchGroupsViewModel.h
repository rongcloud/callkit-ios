//
//  RCSearchGroupsViewModel.h
//  RongIMKit
//
//  Created by RobinCui on 2024/11/21.
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
@class RCSearchGroupsViewModel;

@protocol RCSearchGroupsViewModelDelegate <NSObject>

@optional

/// 交付当前数据源给app处理
/// - Parameters:
///   - viewModel: viewModel
///   - dataSource: 当前数据源
///   - Returns: App处理后的数据源
///
///   - Since: 5.12.2
- (NSArray *_Nullable)searchGroupsViewModel:(RCSearchGroupsViewModel *_Nonnull)viewModel
                   willLoadItemsInDataSource:(NSArray *_Nullable)dataSource;

/// 配置自定义的导航按钮功能
/// - Parameter viewModel: viewModel
///   - Returns: 用户自定义的导航按钮功能
///
///   - Since: 5.12.2
- (RCNavigationItemsViewModel *_Nullable)willConfigureRightNavigationItemsForSearchGroupsViewModel:(RCSearchGroupsViewModel *_Nonnull)viewModel;


/// 配置自定义的搜索功能
/// - Parameter viewModel: viewModel
///   - Returns: 用户自定义的搜索功能
///
///   - Since: 5.12.2
- (RCSearchBarViewModel *_Nullable)willConfigureSearchBarViewModelForSearchGroupsViewModel:(RCSearchGroupsViewModel *_Nonnull)viewModel;

/// 用户点击Cell事件
/// - Parameters:
///   - viewModel: viewModel
///   - viewController: viewController
///   - tableView: tableView
///   - indexPath: indexPath
///   - viewModel: CellViewModel
///   - Returns: App是否处理[YES : SDK不再处理, NO: SDK处理]
///
///   - Since: 5.12.2
- (BOOL)searchGroupsViewModel:(RCSearchGroupsViewModel *_Nonnull)viewModel
               viewController:(UIViewController*_Nonnull)viewController
                    tableView:(UITableView *_Nonnull)tableView
                 didSelectRow:(NSIndexPath *_Nonnull)indexPath
                cellViewModel:(RCBaseCellViewModel *_Nonnull)cellViewModel;
@end

@interface RCSearchGroupsViewModel : RCBaseViewModel<RCListViewModelProtocol>
@property (nonatomic, weak) id<RCSearchGroupsViewModelDelegate> _Nullable delegate;

/// 初始化
/// - Parameter option: 查询参数
- (instancetype)initWithOption:(nullable RCPagingQueryOption *)option;


/// 配置导航按钮
/// - Parameter viewController: VC
- (NSArray *_Nonnull)configureRightNaviItemsForViewController:(UIViewController *_Nonnull)viewController;


/// 配置搜索模块
/// - Parameter viewController: VC
- (UISearchBar *_Nonnull)configureSearchBarForViewController:(UIViewController *_Nonnull)viewController;

/// 绑定事件响应者
/// - Parameter responder: 响应者
- (void)bindResponder:(UIViewController <RCListViewModelResponder>* _Nonnull)responder;

/// 结束搜索框编辑状态
- (void)endEditingState;

/// 加载更多
- (void)loadMoreData;
@end
NS_ASSUME_NONNULL_END
