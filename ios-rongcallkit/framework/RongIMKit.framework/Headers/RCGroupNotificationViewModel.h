//
//  RCGroupNotificationViewModel.h
//  RongIMKit
//
//  Created by RobinCui on 2024/11/14.
//  Copyright © 2024 RongCloud. All rights reserved.
//
#import <UIKit/UIKit.h>
#import "RCListViewModelProtocol.h"
#import <RongIMLibCore/RongIMLibCore.h>
#import "RCBaseViewModel.h"
#import "RCNavigationItemsViewModel.h"
#import "RCBaseCellViewModel.h"

NS_ASSUME_NONNULL_BEGIN
@class RCGroupNotificationViewModel;

@protocol RCGroupNotificationViewModelDelegate <NSObject>
@optional
/// 交付当前数据源给app处理
/// - Parameters:
///   - viewModel: viewModel
///   - dataSource: 当前数据源
///   - Returns: App处理后的数据源
///
///   - Since: 5.12.2
- (NSArray *_Nullable)groupNotificationViewModel:(RCGroupNotificationViewModel *)viewModel
      willLoadItemsInDataSource:(NSArray *_Nullable)dataSource;

/// 配置自定义的导航按钮功能
/// - Parameter viewModel: viewModel
///   - Returns: 用户自定义的导航按钮功能
///
///   - Since: 5.12.2
- (RCNavigationItemsViewModel *_Nullable)willConfigureRightNavigationItemsForGroupNotificationViewModel:(RCGroupNotificationViewModel *)viewModel;

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
- (BOOL)groupNotificationViewModel:(RCGroupNotificationViewModel *)viewModel
                    viewController:(UIViewController*)viewController
                         tableView:(UITableView *)tableView
                      didSelectRow:(NSIndexPath *)indexPath
                     cellViewModel:(RCBaseCellViewModel *)cellViewModel;
@end


@interface RCGroupNotificationViewModel : RCBaseViewModel<RCListViewModelProtocol>

/// 代理
@property (nonatomic, weak) id<RCGroupNotificationViewModelDelegate> delegate;
/// 搜索条件[pageToken, 数量, 顺序]
@property (nonatomic, strong) RCPagingQueryOption *option;

/// 初始化
/// - Parameters:
///   - option: 搜索配置
///   - types: 请求的类型
///   - status: 请求的状态
- (instancetype)initWithOption:(nullable RCPagingQueryOption *)option
                         types:(nullable NSArray<NSNumber *> *)types
                        status:(nullable NSArray<NSNumber *> *)status;
/// 配置导航
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

/// 加载更多
- (void)loadMoreData;

/// 加载数据
/// - Parameters:
///   - option: 条件
///   - types: 类型
///   - status: 状态
- (void)fetchDataWithOption:(RCPagingQueryOption *)option
                      types:(nonnull NSArray<NSNumber *> *)types
                     status:(nonnull NSArray<NSNumber *> *)status;
@end

NS_ASSUME_NONNULL_END
