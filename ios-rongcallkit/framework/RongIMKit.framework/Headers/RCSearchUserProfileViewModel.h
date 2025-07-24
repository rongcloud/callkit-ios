//
//  RCSearchUserProfileViewModel.h
//  RongIMKit
//
//  Created by RobinCui on 2024/8/28.
//  Copyright © 2024 RongCloud. All rights reserved.
//
#import <UIKit/UIKit.h>
#import "RCBaseViewModel.h"

NS_ASSUME_NONNULL_BEGIN
@protocol RCSearchUserProfileViewModelDelegate <NSObject>
@optional
/// 输入框输入内容变化
///
/// - Parameters searchBar: searchBar
/// - Parameters searchText: searchText
/// - Returns: App处理后的数据源
///
///   - Since: 5.12.0
- (void)searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText;

/// 搜索用户资料
///
/// - Parameters text: 文本
///
/// - Since: 5.12.0
- (void)searchUserProfileWithText:(NSString *)text;

@end

/// 搜索用户
/// - Since: 5.12.0
@interface RCSearchUserProfileViewModel : RCBaseViewModel

/// 代理
@property (nonatomic, weak) id<RCSearchUserProfileViewModelDelegate> delegate;

/// searchBar
@property (nonatomic, strong) UISearchBar *searchBar;

/// 初始化
///
/// - Parameters placeholder: 占位文本
- (instancetype)initWithPlaceholder:(NSString *)placeholder;

/// 停止编辑
- (void)endEditingState;
@end

NS_ASSUME_NONNULL_END
