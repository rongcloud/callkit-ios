//
//  RCSelectUserCellViewModel.h
//  RongIMKit
//
//  Created by zgh on 2024/8/26.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseCellViewModel.h"
#import <RongIMLibCore/RongIMLibCore.h>
#import "RCUserProfileDefine.h"

NS_ASSUME_NONNULL_BEGIN
/// 选择联系人 cellViewModel
/// - Since: 5.12.0
@interface RCSelectUserCellViewModel : RCBaseCellViewModel<RCCellViewModelProtocol>

/// 好友信息
@property (nonatomic, strong, readonly) RCFriendInfo *friendInfo;

/// 当前显示选择状态
@property (nonatomic, assign) RCSelectState selectState;

/// 注册当前cell
+ (void)registerCellForTableView:(UITableView *)tableView;

/// 实例化 RCSelectUserCellViewModel
- (instancetype)initWithFriend:(RCFriendInfo *)friendInfo groupId:(NSString *)groupId;

/// 更新 cell
- (void)updateCell:(UITableViewCell *)cell state:(RCSelectState)state;
@end

NS_ASSUME_NONNULL_END
