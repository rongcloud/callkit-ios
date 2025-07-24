//
//  RCSelectUserViewModel.h
//  RongIMKit
//
//  Created by zgh on 2024/8/26.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseViewModel.h"
#import "RCSearchBarViewModel.h"
#import "RCListViewModelProtocol.h"
#import "RCSelectUserCellViewModel.h"

@class RCSelectUserViewModel;
typedef NS_ENUM(NSUInteger, RCSelectUserType) {
    RCSelectUserTypeCreateGroup,
    RCSelectUserTypeInviteJoinGroup,
};

NS_ASSUME_NONNULL_BEGIN
/// 选择联系人代理
/// - Since: 5.12.0
@protocol RCSelectUserViewModelDelegate <NSObject>
@optional

/// 即将加载搜索 ViewModel
///
/// - Parameter viewModel: viewModel
/// - Parameter searchViewModel: searchViewModel
/// - Returns: 用户自定义的搜索功能
///
/// - Since: 5.12.0
- (RCSearchBarViewModel *_Nullable)selectUserViewModel:(RCSelectUserViewModel *)viewModel
                            willLoadSearchBarViewModel:(RCSearchBarViewModel *)searchViewModel;

/// 即将加载数据源
///
/// - Parameters viewModel: viewModel
/// - Parameters  dataSource: 当前数据源
/// - Returns: App处理后的数据源
///
///   - Since: 5.12.0
- (NSArray <RCSelectUserCellViewModel *>* _Nullable)selectUserViewModel:(RCSelectUserViewModel *)viewModel
                                     willLoadItemsInDataSource:(NSArray <RCSelectUserCellViewModel *>*)dataSource;

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
- (BOOL)selectUserViewModel:(RCSelectUserViewModel *)viewModel
             viewController:(UIViewController*)viewController
                  tableView:(UITableView *)tableView
               didSelectRow:(NSIndexPath *)indexPath
              cellViewModel:(RCSelectUserCellViewModel *)cellViewModel;

/// 选择完成回调
///
/// - Parameters viewModel: viewModel
/// - Parameters selectUserIds: 选择用户列表
/// - Parameters viewController: 当前 VC
/// - Returns: App是否处理[YES : SDK不再处理, NO: SDK处理]
///
/// - Since: 5.12.0
- (BOOL)selectUserDidSelectComplete:(RCSelectUserViewModel *)viewModel
                      selectUserIds:(NSMutableArray <NSString *>*)selectUserIds
                     viewController:(UIViewController*)viewController;


@end

/// 选择联系人 ViewModel
/// - Since: 5.12.0
@interface RCSelectUserViewModel : RCBaseViewModel<RCListViewModelProtocol>

/// 实例化 RCSelectUserViewModel
///
/// - Parameters type: 选择联系人类型
/// - Parameters groupId: 群 Id
///
/// - Returns: 实例
///
/// - Since: 5.12.0
+ (instancetype)viewModelWithType:(RCSelectUserType)type
                          groupId:(NSString *_Nullable)groupId;

/// 代理
@property (nonatomic, weak) id<RCSelectUserViewModelDelegate> delegate;

/// 选择的用户列表
@property (nonatomic, strong, readonly) NSMutableArray <NSString *>*selectUserIds;

/// 单次最多可选择数量，默认 30, 0 < maxSelectCount <= 100
@property (nonatomic, assign, setter=setMaxSelectCount:) NSInteger maxSelectCount;

@property (nonatomic, copy) void (^selectionDidCompelteBlock)(NSArray <NSString *>*selectUserIds, UIViewController *selectVC);

/// 配置 searchBar
- (UISearchBar *)configureSearchBarForViewController:(UIViewController *)viewController;

/// 分区名称
- (NSArray *)sectionIndexTitles;

/// 获取数据
- (void)fetchData;

/// 绑定响应器
- (void)bindResponder:(id<RCListViewModelResponder>)responder;

/// 停止编辑
- (void)endEditingState;

/// 选择完成
- (void)selectionDidDone;

/// 获取空视图提示信息
- (NSString *)emptyTip;

@end

NS_ASSUME_NONNULL_END
