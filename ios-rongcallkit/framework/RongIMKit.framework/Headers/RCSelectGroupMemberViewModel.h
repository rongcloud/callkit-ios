//
//  RCSelectGroupMemberViewModel.h
//  RongIMKit
//
//  Created by zgh on 2024/11/15.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseViewModel.h"
#import "RCListViewModelProtocol.h"
#import "RCRemoveGroupMemberCellViewModel.h"
#import "RCSearchBarViewModel.h"
NS_ASSUME_NONNULL_BEGIN
@class RCSelectGroupMemberViewModel;
@protocol RCSelectGroupMemberViewModelDelegate <NSObject>

@optional

/// 即将加载搜索 ViewModel
///
/// - Parameter viewModel: viewModel
/// - Parameter searchViewModel: searchViewModel
/// - Returns: 用户自定义的搜索功能
///
/// - Since: 5.12.2
- (RCSearchBarViewModel *_Nullable)selectGroupMember:(RCSelectGroupMemberViewModel *)viewModel
                          willLoadSearchBarViewModel:(RCSearchBarViewModel *)searchViewModel;

/// 即将加载数据源
///
/// - Parameters viewModel: viewModel
/// - Parameters  dataSource: 当前数据源
/// - Returns: App处理后的数据源
///
///   - Since: 5.12.2
- (NSArray <RCRemoveGroupMemberCellViewModel *> *)selectGroupMember:(RCSelectGroupMemberViewModel *)viewModel
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
/// - Since: 5.12.2
- (BOOL)selectGroupMember:(RCSelectGroupMemberViewModel *)viewModel
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
/// - Since: 5.12.2
- (BOOL)selectGroupMemberDidSelectComplete:(RCSelectGroupMemberViewModel *)viewModel
                             selectUserIds:(NSMutableArray <NSString *>*)selectUserIds
                            viewController:(UIViewController*)viewController;

@end

/// 选择群成员 ViewModel
///  - Since: 5.12.2
@interface RCSelectGroupMemberViewModel : RCBaseViewModel<RCListViewModelProtocol>
/// 代理
@property (nonatomic, weak) id<RCSelectGroupMemberViewModelDelegate> delegate;

/// 选择完成 block
@property (nonatomic, copy) void (^selectionDidCompelteBlock)(NSArray <NSString *>*selectUserIds, UIViewController *selectVC);

/// 选择的用户列表
@property (nonatomic, strong, readonly) NSMutableArray <NSString *>*selectUserIds;

/// 当前数据源
@property (nonatomic, strong, readonly) NSArray <RCRemoveGroupMemberCellViewModel *>*memberList;

/// 群 Id
@property (nonatomic, copy, readonly) NSString *groupId;

/// 单次最多可选择数量
@property (nonatomic, assign, setter=setMaxSelectCount:) NSInteger maxSelectCount;

/// 超限提示信息
@property (nonatomic, copy) NSString *tip;

/// 隐藏的用户id
@property (nonatomic, strong) NSArray <NSString *> *hideUserIds;

/// 实例化 RCRemoveGroupMembersViewModel
///
/// - Parameters groupId: 群主 Id
/// - Parameters existingUserIds: 已经存在的用户 id 列表
+ (instancetype)viewModelWithGroupId:(NSString *)groupId
                     existingUserIds:(nullable NSArray *)existingUserIds;

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
