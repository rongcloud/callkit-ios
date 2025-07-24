//
//  RCGroupMembersViewModel.h
//  RongIMKit
//
//  Created by zgh on 2024/8/26.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseViewModel.h"
#import "RCGroupMemberCellViewModel.h"
#import "RCSearchBarViewModel.h"
#import "RCListViewModelProtocol.h"

NS_ASSUME_NONNULL_BEGIN
@class RCGroupTransferViewModel;
/// 群成员列表代理
/// - Since: 5.12.2
@protocol RCGroupTransferViewModelDelegate <NSObject>
@optional
/// 即将加载搜索 ViewModel
///
/// - Parameter viewModel: viewModel
/// - Parameter searchViewModel: searchViewModel
/// - Returns: 用户自定义的搜索功能
///
/// - Since: 5.12.2
- (RCSearchBarViewModel *_Nullable)groupMemberList:(RCGroupTransferViewModel *)viewModel
                        willLoadSearchBarViewModel:(RCSearchBarViewModel *)searchViewModel;

/// 即将加载数据源
/// - Parameters viewModel: viewModel
/// - Parameters  dataSource: 当前数据源
/// - Returns: App处理后的数据源
///
///   - Since: 5.12.2
- (NSArray <RCGroupMemberCellViewModel *> * )groupMemberList:(RCGroupTransferViewModel *)viewModel
                                   willLoadItemsInDataSource:(NSArray <RCGroupMemberCellViewModel *> * )dataSource;

/// 用户点击Cell事件
/// - Parameters viewModel: viewModel
/// - Parameters viewController: 当前 VC
/// - Parameters tableView: tableView
/// - Parameters indexPath: indexPath
/// - Parameters cellViewModel: cellViewModel
/// - Returns: App是否处理[YES : SDK不再处理, NO: SDK处理]
///
/// - Since: 5.12.2
- (BOOL)groupMemberList:(RCGroupTransferViewModel *)viewModel
         viewController:(UIViewController*)viewController
              tableView:(UITableView *)tableView
           didSelectRow:(NSIndexPath *)indexPath
          cellViewModel:(RCGroupMemberCellViewModel *)cellViewModel;

/// 群主已经转让成功
/// - Parameters groupId: 群 id
/// - Parameters newOwnerId: 新群主 id
/// - Parameters viewController: 当前 VC
/// - Returns: App是否处理[YES : SDK不再处理, NO: SDK处理]
///
/// - Since: 5.12.2
- (BOOL)groupOwnerDidTransfer:(NSString *)groupId
                   newOwnerId:(NSString *)newOwnerId
               viewController:(UIViewController*)viewController;
@end

/// 群成员列表 ViewModel
/// - Since: 5.12.2
@interface RCGroupTransferViewModel : RCBaseViewModel<RCListViewModelProtocol>

/// 代理
@property (nonatomic, weak) id<RCGroupTransferViewModelDelegate> delegate;

/// 数据源
@property (nonatomic, strong, readonly) NSArray <RCGroupMemberCellViewModel *>*memberList;

/// 每页加载成员数, 默认 50，0 < pageCount <= 100
@property (nonatomic, assign, setter=setPageCount:) NSInteger pageCount;

/// 群 Id
@property (nonatomic, copy, readonly) NSString *groupId;

/// 实例化 RCGroupTransferOwnerViewModel
+ (instancetype)viewModelWithGroupId:(NSString *)groupId;

/// 绑定响应器
- (void)bindResponder:(id<RCListViewModelResponder>)responder;

/// 分页加载群成员
- (void)fetchGroupMembersByPage;

/// 配置 searchBar
///
/// - Returns searchBar: searchBar
- (UISearchBar *)configureSearchBar;

/// 停止编辑
- (void)endEditingState;
@end

NS_ASSUME_NONNULL_END
