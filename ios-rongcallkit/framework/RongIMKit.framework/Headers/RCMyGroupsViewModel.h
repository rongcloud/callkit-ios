//
//  RCMyGroupsViewModel.h
//  RongIMKit
//
//  Created by RobinCui on 2024/11/20.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseViewModel.h"
#import "RCListViewModelProtocol.h"
#import "RCNavigationItemsViewModel.h"
#import "RCCellViewModelProtocol.h"
#import "RCGroupInfoCellViewModel.h"
#import "RCSearchBarViewModel.h"
#import <RongIMLibCore/RongIMLibCore.h>

NS_ASSUME_NONNULL_BEGIN
@class RCMyGroupsViewModel;

@protocol RCMyGroupsViewModelDelegate <NSObject>
@optional
/// 交付当前数据源给app处理
/// - Parameters:
///   - viewModel: viewModel
///   - dataSource: 当前数据源
///   - Returns: App处理后的数据源
///
///   - Since: 5.12.2
- (NSArray *_Nullable)myGroupsViewModel:(RCMyGroupsViewModel *)viewModel
              willLoadItemsInDataSource:(NSArray *_Nullable)dataSource;

/// 配置自定义的导航按钮功能
/// - Parameter viewModel: viewModel
///   - Returns: 用户自定义的导航按钮功能
///
///   - Since: 5.12.2
- (RCNavigationItemsViewModel *_Nullable)willConfigureRightNavigationItemsForMyGroupsViewModel:(RCMyGroupsViewModel *)viewModel;


/// 配置自定义的搜索功能
/// - Parameter viewModel: viewModel
///   - Returns: 用户自定义的搜索功能
///
///   - Since: 5.12.2
- (RCSearchBarViewModel *_Nullable)willConfigureSearchBarViewModelForMyGroupsViewModel:(RCMyGroupsViewModel *)viewModel;

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
- (BOOL)myGroupsViewModel:(RCMyGroupsViewModel *)viewModel
           viewController:(UIViewController*)viewController
                tableView:(UITableView *)tableView
             didSelectRow:(NSIndexPath *)indexPath
            cellViewModel:(RCBaseCellViewModel *)cellViewModel;
@end

/// 群组列表 viewModel
/// - Since: 5.12.2
@interface RCMyGroupsViewModel : RCBaseViewModel<RCListViewModelProtocol>

/// 代理
@property (nonatomic, weak) id<RCMyGroupsViewModelDelegate> delegate;

/// 初始化
/// - Parameter option: 查询参数
- (instancetype)initWithOption:(nullable RCPagingQueryOption *)option;

/// 配置导航
- (NSArray *)configureRightNaviItemsForViewController:(UIViewController *)viewController;

/// 配置 searchBar
- (UISearchBar *)configureSearchBarForViewController:(UIViewController *)viewController;

/// 获取数据
- (void)fetchData;

/// 绑定响应器
- (void)bindResponder:(UIViewController <RCListViewModelResponder>*)responder;

/// 加载更多
- (void)loadMoreData;
@end

NS_ASSUME_NONNULL_END
