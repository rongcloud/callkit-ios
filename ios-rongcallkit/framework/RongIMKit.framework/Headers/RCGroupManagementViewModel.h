//
//  RCGroupManagementViewModel.h
//  RongIMKit
//
//  Created by zgh on 2024/11/25.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseViewModel.h"
#import "RCListViewModelProtocol.h"
#import "RCBaseCellViewModel.h"
NS_ASSUME_NONNULL_BEGIN
@class RCGroupManagementViewModel;
@protocol RCGroupManagementViewModelDelegate <NSObject>

@optional

/// 即将加载数据源
/// - Parameters viewModel: viewModel
/// - Parameters  dataSource: 当前数据源
/// - Returns: App处理后的数据源
///
///   - Since: 5.12.2
- (NSArray <NSArray <RCBaseCellViewModel *> *> *)groupManagement:(RCGroupManagementViewModel *)viewModel
                                       willLoadItemsInDataSource:(NSArray <NSArray <RCBaseCellViewModel *> *> *)dataSource;

/// 用户点击Cell事件
/// - Parameters viewModel: viewModel
/// - Parameters viewController: 当前 VC
/// - Parameters tableView: tableView
/// - Parameters indexPath: indexPath
/// - Parameters cellViewModel: cellViewModel
/// - Returns: App是否处理[YES : SDK不再处理, NO: SDK处理]
///
/// - Since: 5.12.2
- (BOOL)groupManagement:(RCGroupManagementViewModel *)viewModel
         viewController:(UIViewController*)viewController
              tableView:(UITableView *)tableView
           didSelectRow:(NSIndexPath *)indexPath
          cellViewModel:(RCBaseCellViewModel *)cellViewModel;

@end
/// 群管理 ViewModel
/// - Since: 5.12.2
@interface RCGroupManagementViewModel : RCBaseViewModel<RCListViewModelProtocol>

/// 代理
@property (nonatomic, weak) id<RCGroupManagementViewModelDelegate> delegate;

/// 实例化 RCGroupManagementViewModel
///
/// - Parameters groupId: 群主 Id
+ (instancetype)viewModelWithGroupId:(NSString *)groupId;

/// 绑定响应器
- (void)bindResponder:(id<RCListViewModelResponder>)responder;

/// 获取数据源
- (void)fetchDataSources;
@end

NS_ASSUME_NONNULL_END
