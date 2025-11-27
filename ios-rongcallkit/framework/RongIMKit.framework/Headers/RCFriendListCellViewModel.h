//
//  RCFriendListCellViewModel.h
//  RongIMKit
//
//  Created by RobinCui on 2024/8/20.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseCellViewModel.h"
#import "RCCellViewModelProtocol.h"
#import <RongIMLibCore/RongIMLibCore.h>
NS_ASSUME_NONNULL_BEGIN


/// 好友列表 CellViewModel
/// - Since: 5.12.0
@interface RCFriendListCellViewModel : RCBaseCellViewModel<RCCellViewModelProtocol>

/// 好友信息
@property (nonatomic, strong) RCFriendInfo *friendInfo;

/// 是否显示在线状态
@property (nonatomic, assign) BOOL displayOnlineStatus;

/// 在线状态
@property (nonatomic, strong) RCSubscribeUserOnlineStatus *onlineStatus;

/// 注册 cell
+ (void)registerCellForTableView:(UITableView *)tableView;

/// 初始化
- (instancetype)initWithFriend:(RCFriendInfo  * _Nullable )friendInfo;

/// 刷新好友
- (void)refreshWithFriend:(RCFriendInfo *)friendInfo;

/// 刷新在线状态
- (void)refreshOnlineStatus:(RCSubscribeUserOnlineStatus *)onlineStatus;

@end

NS_ASSUME_NONNULL_END
