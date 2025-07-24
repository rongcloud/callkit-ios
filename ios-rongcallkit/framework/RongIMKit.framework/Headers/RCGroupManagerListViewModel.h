//
//  RCGroupManagersViewModel.h
//  RongIMKit
//
//  Created by zgh on 2024/11/25.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseViewModel.h"
#import "RCListViewModelProtocol.h"
#import "RCBaseCellViewModel.h"
NS_ASSUME_NONNULL_BEGIN
@class RCGroupManagerListViewModel;
@protocol RCGroupManagerListViewModelDelegate <NSObject>

@optional
/// 用户点击Cell事件
/// - Parameters viewModel: viewModel
/// - Parameters viewController: 当前 VC
/// - Parameters tableView: tableView
/// - Parameters indexPath: indexPath
/// - Parameters cellViewModel: cellViewModel
/// - Returns: App是否处理[YES : SDK不再处理, NO: SDK处理]
///
/// - Since: 5.12.0
- (BOOL)  groupManagers:(RCGroupManagerListViewModel *)viewModel
         viewController:(UIViewController*)viewController
              tableView:(UITableView *)tableView
           didSelectRow:(NSIndexPath *)indexPath
          cellViewModel:(RCBaseCellViewModel *)cellViewModel;

/// 已经添加管理员
/// - Parameters groupId: 群 id
/// - Parameters addUserIds: 添加的管理员id列表
/// - Parameters viewController: 当前 VC
/// - Returns: App是否处理[YES : SDK不再处理, NO: SDK处理]
///
/// - Since: 5.12.0
- (BOOL)groupManagersDidAdd:(NSString *)groupId
                 addUserIds:(NSArray <NSString *>*)addUserIds
             viewController:(UIViewController*)viewController;

/// 将要移除管理员
/// - Parameters groupId: 群 id
/// - Parameters removeUserIds: 移除的管理员id列表
/// - Parameters viewController: 当前 VC
/// - Returns: App是否处理[YES : SDK不再处理, NO: SDK处理]
///
/// - Since: 5.12.0
- (BOOL)groupManagersWillRemove:(NSString *)groupId
                  removeUserIds:(NSArray <NSString *>*)removeUserIds
                 viewController:(UIViewController*)viewController;

/// 已经移除管理员
/// - Parameters groupId: 群 id
/// - Parameters removeUserIds: 移除的管理员id列表
/// - Parameters viewController: 当前 VC
/// - Returns: App是否处理[YES : SDK不再处理, NO: SDK处理]
///
/// - Since: 5.12.0
- (BOOL)groupManagersDidRemove:(NSString *)groupId
                 removeUserIds:(NSArray <NSString *>*)removeUserIds
                viewController:(UIViewController*)viewController;
@end

/// 管理员列表 ViewModel
/// - Since: 5.12.2
@interface RCGroupManagerListViewModel : RCBaseViewModel<RCListViewModelProtocol>
///代理
@property (nonatomic, weak) id<RCGroupManagerListViewModelDelegate> delegate;

/// 实例化 RCGroupManagerListViewModel
///
/// - Parameters groupId: 群主 Id
+ (instancetype)viewModelWithGroupId:(NSString *)groupId;

/// 绑定响应器
- (void)bindResponder:(id<RCListViewModelResponder>)responder;

/// 获取管理员列表
- (void)fetchGroupManagers;
@end

NS_ASSUME_NONNULL_END
