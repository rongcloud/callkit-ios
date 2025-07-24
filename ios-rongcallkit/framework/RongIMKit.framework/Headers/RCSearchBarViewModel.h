//
//  RCUFriendListSearchBarViewModel.h
//  RongUserProfile
//
//  Created by RobinCui on 2024/8/16.
//

#import <UIKit/UIKit.h>
#import "RCBaseViewModel.h"

NS_ASSUME_NONNULL_BEGIN

@protocol RCSearchBarViewModelDelegate <NSObject>
@optional
/// 输入框输入内容变化
///
/// - Parameters searchBar: searchBar
/// - Parameters searchText: searchText
/// - Returns: App处理后的数据源
///
///   - Since: 5.12.0
- (void)searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText;

/// 输入框输入状态变化
///
/// - Parameters searchBar: searchBar
/// - Parameters inSearching: 是否在搜索
/// - Returns: App处理后的数据源
///
///   - Since: 5.12.0
- (void)searchBar:(UISearchBar *)searchBar editingStateChanged:(BOOL)inSearching;

/// 输入框将要开始编辑
///
/// - Parameters searchBar: searchBar
/// - Returns: YES 开始编辑， NO 不开始编辑
///
///   - Since: 5.12.0
- (BOOL)searchBarShouldBeginEditing:(UISearchBar *)searchBar;
@end

/// 搜索 ViewModel
/// - Since: 5.12.0
@interface RCSearchBarViewModel : RCBaseViewModel

/// 代理
@property (nonatomic, weak) id<RCSearchBarViewModelDelegate> delegate;

/// 搜索 View
@property (nonatomic, strong) UISearchBar *searchBar;

/// 初始化
- (instancetype)initWithResponder:(UIViewController *)responder;

/// 是否是第一响应者
- (BOOL)isCurrentFirstResponder;

/// 停止编辑
- (void)endEditingState;
@end

NS_ASSUME_NONNULL_END
