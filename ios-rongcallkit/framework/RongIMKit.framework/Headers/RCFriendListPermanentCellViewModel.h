//
//  RCFriendListPermanentCellViewModel.h
//  RongIMKit
//
//  Created by RobinCui on 2024/8/20.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseCellViewModel.h"
#import "RCCellViewModelProtocol.h"
NS_ASSUME_NONNULL_BEGIN

/// 好友列表常驻 cell
/// - Since: 5.12.0
@interface RCFriendListPermanentCellViewModel : RCBaseCellViewModel<RCCellViewModelProtocol>

/// 初始化
- (instancetype)initWithTitle:(NSString *)title
                     portrait:(UIImage *)portrait
                   touchBlock:(RCPermanentCellViewModelBlock)touchBlock;

/// 注册 cell
+ (void)registerCellForTableView:(UITableView *)tableView;
@end

NS_ASSUME_NONNULL_END
