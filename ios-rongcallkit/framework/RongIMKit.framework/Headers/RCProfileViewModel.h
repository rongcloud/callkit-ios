//
//  RCUserProfileViewModel.h
//  RongUserProfile
//
//  Created by zgh on 2024/8/16.
//

#import "RCBaseViewModel.h"
#import <RongIMLibCore/RongIMLibCore.h>
#import "RCProfileCellViewModel.h"
#import "RCListViewModelProtocol.h"
#import "RCProfileFooterViewModel.h"

@class RCProfileViewModel;
NS_ASSUME_NONNULL_BEGIN

@protocol RCProfileViewModelDelegate <NSObject>

@optional

/// 即将加载 footer viewModel
/// - Parameters viewModel: viewModel
/// - Parameters  footerViewModel: footerViewModel
/// - Returns: App处理后的 footerViewModel
///
/// - Since: 5.12.0
- (RCProfileFooterViewModel *)profileViewModel:(RCProfileViewModel *)viewModel willLoadProfileFooterViewModel:(RCProfileFooterViewModel *)footerViewModel ;

/// 即将加载数据源
/// - Parameters viewModel: viewModel
/// - Parameters  profileList: 当前数据源
/// - Returns: App处理后的数据源
///
/// - Since: 5.12.0
- (NSArray <NSArray <RCProfileCellViewModel*> *> * )profileViewModel:(RCProfileViewModel *)viewModel
                                        willLoadProfileCellViewModel:(NSArray <NSArray <RCProfileCellViewModel*> *> *)profileList;

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
- (BOOL)profileViewModel:(RCProfileViewModel *)viewModel
          viewController:(UIViewController*)viewController
             tableView:(UITableView *)tableView
          didSelectRow:(NSIndexPath *)indexPath
           cellViewModel:(RCProfileCellViewModel *)cellViewModel;
@end

/// 资料页 viewModel
/// - Since: 5.12.0
@interface RCProfileViewModel : RCBaseViewModel<RCListViewModelProtocol>

/// 数据源
@property (nonatomic, strong, readonly) NSArray <NSArray <RCProfileCellViewModel*> *> *profileList;

/// 尾部视图 viewModel
@property (nonatomic, strong, readonly, nullable) RCProfileFooterViewModel *footerViewModel;

/// 代理
@property (nonatomic, weak) id<RCProfileViewModelDelegate> delegate;

/// view 响应器
@property (nonatomic, weak) id<RCListViewModelResponder> responder;

/// 更新 profile
- (void)updateProfile;

/// 加载 footerView
- (UIView *)loadFooterView;

@end

NS_ASSUME_NONNULL_END
