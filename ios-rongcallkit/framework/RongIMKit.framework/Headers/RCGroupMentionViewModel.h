//
//  RCGroupMentionViewModel.h
//  RongIMKit
//
//  Created by RobinCui on 2025/11/19.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import "RCBaseViewModel.h"
#import "RCGroupMemberCellViewModel.h"
#import "RCSearchBarViewModel.h"
#import "RCListViewModelProtocol.h"
// @all userId
extern NSString  * _Nonnull const RCMentionAllUsersID;
NS_ASSUME_NONNULL_BEGIN

@interface RCGroupMentionViewModel : RCBaseViewModel<RCListViewModelProtocol>

/// 数据源
@property (nonatomic, strong, readonly) NSArray <RCGroupMemberCellViewModel *>*memberList;

/// 每页加载成员数, 默认 50，0 < pageCount <= 100
@property (nonatomic, assign, setter=setPageCount:) NSInteger pageCount;

/// 群 Id
@property (nonatomic, copy, readonly) NSString *groupId;


/// 实例化 RCGroupMentionViewModel
+ (instancetype)viewModelWithGroupId:(NSString *)groupId
                       selectedBlock:(void (^)(RCUserInfo *selectedUserInfo))selectedBlock
                              cancel:(void (^)(void))cancelBlock;

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

- (void)selectionCanceled;

@end

NS_ASSUME_NONNULL_END
