//
//  RCGroupRemoveMembersViewModel.h
//  RongIMKit
//
//  Created by zgh on 2024/8/27.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseViewModel.h"
#import "RCRemoveGroupMemberCellViewModel.h"
#import "RCListViewModelProtocol.h"
#import "RCSearchBarViewModel.h"

@class RCRemoveGroupMembersViewModel;
NS_ASSUME_NONNULL_BEGIN

@protocol RCGroupRemoveMembersViewModelDelelgate <NSObject>
@optional

/// 即将加载搜索 ViewModel
///
/// - Parameter viewModel: viewModel
/// - Parameter searchViewModel: searchViewModel
/// - Returns: 用户自定义的搜索功能
///
/// - Since: 5.12.0
- (RCSearchBarViewModel *_Nullable)groupRemoveMembers:(RCRemoveGroupMembersViewModel *)viewModel
                           willLoadSearchBarViewModel:(RCSearchBarViewModel *)searchViewModel;

/// 即将加载数据源
///
/// - Parameters viewModel: viewModel
/// - Parameters  dataSource: 当前数据源
/// - Returns: App处理后的数据源
///
///   - Since: 5.12.0
- (NSArray <RCRemoveGroupMemberCellViewModel *> *)groupRemoveMembers:(RCRemoveGroupMembersViewModel *)viewModel
                                           willLoadItemsInDataSource:(NSArray <RCRemoveGroupMemberCellViewModel *>*)dataSource;

/// 用户点击Cell事件
///
/// - Parameters viewModel: viewModel
/// - Parameters viewController: 当前 VC
/// - Parameters tableView: tableView
/// - Parameters indexPath: indexPath
/// - Parameters cellViewModel: cellViewModel
/// - Returns: App是否处理[YES : SDK不再处理, NO: SDK处理]
///
/// - Since: 5.12.0
- (BOOL)groupRemoveMembers:(RCRemoveGroupMembersViewModel *)viewModel
            viewController:(UIViewController*)viewController
                 tableView:(UITableView *)tableView
              didSelectRow:(NSIndexPath *)indexPath
             cellViewModel:(RCRemoveGroupMemberCellViewModel *)cellViewModel;

/// 选择完成回调
///
/// - Parameters viewModel: viewModel
/// - Parameters selectUserIds: 选择用户列表
/// - Parameters viewController: 当前 VC
/// - Returns: App是否处理[YES : SDK不再处理, NO: SDK处理]
///
/// - Since: 5.12.0
- (BOOL)groupRemoveMembersDidSelectComplete:(RCRemoveGroupMembersViewModel *)viewModel
                              selectUserIds:(NSMutableArray <NSString *>*)selectUserIds
                             viewController:(UIViewController*)viewController;
@end

/// 移除群成员 ViewModel
/// - Since: 5.12.0
@interface RCRemoveGroupMembersViewModel : RCBaseViewModel<RCListViewModelProtocol>

/// 代理
@property (nonatomic, weak) id<RCGroupRemoveMembersViewModelDelelgate> delegate;

/// 选择的用户列表
@property (nonatomic, strong, readonly) NSMutableArray <NSString *>*selectUserIds;

/// 当前数据源
@property (nonatomic, strong, readonly) NSArray <RCRemoveGroupMemberCellViewModel *>*memberList;

/// 群 Id
@property (nonatomic, copy, readonly) NSString *groupId;

/// 单次最多可选择数量，默认 30, 0 < maxSelectCount <= 100
@property (nonatomic, assign, setter=setMaxSelectCount:) NSInteger maxSelectCount;

/// 实例化 RCRemoveGroupMembersViewModel
+ (instancetype)viewModelWithGroupId:(NSString *)groupId;

/// 绑定响应器
- (void)bindResponder:(id<RCListViewModelResponder>)responder;

/// 分页加载数据源
- (void)fetchGroupMembersByPage;

/// 配置当前 VC
- (UISearchBar *)configureSearchBar;

/// 停止编辑
- (void)endEditingState;

/// 选择完成
- (void)selectionDidDone;

@end

NS_ASSUME_NONNULL_END
