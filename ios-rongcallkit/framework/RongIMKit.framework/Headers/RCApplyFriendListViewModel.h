//
//  RCApplyFriendListViewModel.h
//  RongIMKit
//
//  Created by RobinCui on 2024/8/23.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RCBaseViewModel.h"
#import "RCListViewModelProtocol.h"
#import "RCNavigationItemsViewModel.h"
#import "RCCellViewModelProtocol.h"
#import "RCApplyFriendCellViewModel.h"
#import "RCApplyFriendSectionItem.h"
#import <RongIMLibCore/RongIMLibCore.h>
NS_ASSUME_NONNULL_BEGIN

@class RCApplyFriendListViewModel;

@protocol RCApplyFriendListDelegate <NSObject>
@optional
/// 交付当前数据源给app处理
/// - Parameters:
///   - viewModel: viewModel
///   - dataSource: 当前数据源
///   - Returns: App处理后的数据源
///
///   - Since:

- (NSArray <RCApplyFriendCellViewModel *> *_Nullable)applyFriendListViewModel:(RCApplyFriendListViewModel *)viewModel
                                                    willLoadItemsInDataSource:(NSArray *_Nullable)dataSource;

/// 配置自定义的导航按钮功能
/// - Parameter viewModel: viewModel
///   - Returns: 用户自定义的导航按钮功能
///
///   - Since:
- (RCNavigationItemsViewModel *_Nullable)willConfigureRightNavigationItemsForApplyFriendListViewModel:(RCApplyFriendListViewModel *)viewModel;

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
- (BOOL)applyFriendListViewModel:(RCApplyFriendListViewModel *)viewModel
                  viewController:(UIViewController*)viewController
                       tableView:(UITableView *)tableView
                    didSelectRow:(NSIndexPath *)indexPath
                   cellViewModel:(RCApplyFriendCellViewModel *)cellViewModel;
@end

/// 好友申请列表
/// - Since:5.12.0
@interface RCApplyFriendListViewModel : RCBaseViewModel<RCListViewModelProtocol>

/// 代理
@property (nonatomic, weak) id<RCApplyFriendListDelegate> delegate;

/// 初始化
/// - Parameter items: 数据源
/// - Parameter option: 配置
/// - Parameter types: 类型列表
/// - Parameter status: 状态列表
- (instancetype)initWithSectionItems:(nullable NSArray <RCApplyFriendSectionItem *>*)items
                              option:(nullable RCPagingQueryOption *)option
                               types:(nullable NSArray<NSNumber *> *)types
                              status:(nullable NSArray<NSNumber *> *)status;

/// 配置导航
/// - Parameter viewController: viewController
- (NSArray *)configureRightNaviItemsForViewController:(UIViewController *)viewController;

/// 获取数据
- (void)fetchData;

/// 绑定响应器
- (void)bindResponder:(UIViewController <RCListViewModelResponder>*)responder;

/// cell 高度
/// - Parameters:
///   - tableView: tableView
///   - indexPath: indexPath
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath;

/// header 高度
/// - Parameters:
///   - tableView: tableView
///   - indexPath: indexPath
- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section;

/// 加载更多
- (void)loadMoreData;

/// header 高度
/// - Parameters:
///   - tableView: tableView
///   - indexPath: indexPath
///   - Returns: action 列表
- (NSArray<UITableViewRowAction *> *)tableView:(UITableView *)tableView
                  editActionsForRowAtIndexPath:(NSIndexPath *)indexPath;

@end

NS_ASSUME_NONNULL_END
