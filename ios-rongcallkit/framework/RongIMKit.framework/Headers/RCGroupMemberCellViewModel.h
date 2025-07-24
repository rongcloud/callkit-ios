//
//  RCGroupMemberCellViewModel.h
//  RongIMKit
//
//  Created by zgh on 2024/8/26.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseCellViewModel.h"
#import <RongIMLibCore/RongIMLibCore.h>
NS_ASSUME_NONNULL_BEGIN

/// 群成员 cellViewModel
/// - Since: 5.12.0
@interface RCGroupMemberCellViewModel : RCBaseCellViewModel<RCCellViewModelProtocol>

/// 群成员
@property (nonatomic, strong, readonly) RCGroupMemberInfo *memberInfo;

/// 备注（好友设置了备注才有）
@property (nonatomic, strong, nullable) NSString *remark;

/// 隐藏箭头
@property (nonatomic, assign) BOOL hiddenArrow;

/// 注册 cell
+ (void)registerCellForTableView:(UITableView *)tableView;

/// 实例化 RCGroupMemberCellViewModel
- (instancetype)initWithMember:(RCGroupMemberInfo *)memberInfo;

@end

NS_ASSUME_NONNULL_END
