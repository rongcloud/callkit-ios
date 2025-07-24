//
//  RCSelectGroupMemberCellViewModel.h
//  RongIMKit
//
//  Created by zgh on 2024/8/27.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseCellViewModel.h"
#import "RCUserProfileDefine.h"
#import <RongIMLibCore/RongIMLibCore.h>

NS_ASSUME_NONNULL_BEGIN
/// 选择群成员cell
/// - Since: 5.12.0
@interface RCRemoveGroupMemberCellViewModel : RCBaseCellViewModel<RCCellViewModelProtocol>

/// 群成员
@property (nonatomic, strong, readonly) RCGroupMemberInfo *member;

/// 备注（好友设置了备注才有）
@property (nonatomic, strong, nullable) NSString *remark;

/// cell 当前选择状态
@property (nonatomic, assign, readonly) RCSelectState selectState;

/// 隐藏角色显示
@property (nonatomic, assign) BOOL hiddenRole;

/// 注册 cell
+ (void)registerCellForTableView:(UITableView *)tableView;

/// 实例化 RCRemoveGroupMemberCellViewModel
- (instancetype)initWithMember:(RCGroupMemberInfo *)member;

/// 更新cell
- (void)updateCell:(UITableViewCell *)cell state:(RCSelectState)state;

@end

NS_ASSUME_NONNULL_END
