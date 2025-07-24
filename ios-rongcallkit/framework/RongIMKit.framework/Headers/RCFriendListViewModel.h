//
//  RCFriendListViewModel.h
//  RongUserProfile
//
//  Created by RobinCui on 2024/8/16.
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
@class RCFriendListViewModel;
@protocol RCFriendListViewModelDelegate <NSObject>
@optional
/// 交付当前数据源给app处理
/// - Parameters:
///   - viewModel: viewModel
///   - dataSource: 当前数据源
///   - Returns: App处理后的数据源
///
///   - Since: 5.12.0
- (NSArray *_Nullable)friendListViewModel:(RCFriendListViewModel *)viewModel
      willLoadItemsInDataSource:(NSArray *_Nullable)dataSource;

/// 配置自定义的导航按钮功能
/// - Parameter viewModel: viewModel
///   - Returns: 用户自定义的导航按钮功能
///
///   - Since: 5.12.0
- (RCNavigationItemsViewModel *_Nullable)willConfigureRightNavigationItemsForFriendListViewModel:(RCFriendListViewModel *)viewModel;


/// 配置自定义的搜索功能
/// - Parameter viewModel: viewModel
///   - Returns: 用户自定义的搜索功能
///
///   - Since: 5.12.0
- (RCSearchBarViewModel *_Nullable)willConfigureSearchBarViewModelForFriendListViewModel:(RCFriendListViewModel *)viewModel;

/// 添加常驻Cell的viewModel
/// - Parameter viewModel: viewModel
///   - Returns: 需要在第一个 section 显示的ViewModel
///
///   - Since: 5.12.0
- (NSArray <RCFriendListPermanentCellViewModel *>*_Nullable)appendPermanentCellViewModelsForFriendListViewModel:(RCFriendListViewModel *)viewModel;

/// 用户点击Cell事件
/// - Parameters:
///   - viewModel: viewModel
///   - viewController: viewController
///   - tableView: tableView
///   - indexPath: indexPath
///   - viewModel: CellViewModel
///   - Returns: App是否处理[YES : SDK不再处理, NO: SDK处理]
///
///   - Since: 5.12.0
- (BOOL)friendListViewModel:(RCFriendListViewModel *)viewModel
             viewController:(UIViewController*)viewController
                  tableView:(UITableView *)tableView
               didSelectRow:(NSIndexPath *)indexPath
              cellViewModel:(RCBaseCellViewModel *)cellViewModel;
@end

/// 好友列表 viewModel
/// - Since: 5.12.0
@interface RCFriendListViewModel : RCBaseViewModel<RCListViewModelProtocol>

/// 代理
@property (nonatomic, weak) id<RCFriendListViewModelDelegate> delegate;

/// 配置导航
- (NSArray *)configureRightNaviItemsForViewController:(UIViewController *)viewController;

/// 配置 searchBar
- (UISearchBar *)configureSearchBarForViewController:(UIViewController *)viewController;

/// 分区标题
- (NSArray *)sectionIndexTitles;

/// 获取数据
- (void)fetchData;

/// 绑定响应器
- (void)bindResponder:(UIViewController <RCListViewModelResponder>*)responder;

@end

NS_ASSUME_NONNULL_END
