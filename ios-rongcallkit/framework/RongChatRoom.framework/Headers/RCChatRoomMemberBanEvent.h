//
//  RCChatRoomMemberBanEvent.h
//  RongChatRoom
//
//  Created by chinaspx on 2023/5/6.
//  Copyright © 2023 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RCChatRoomEnumDefine.h"

NS_ASSUME_NONNULL_BEGIN

@interface RCChatRoomMemberBanEvent : NSObject
/// 聊天室 ID
@property (nonatomic, copy) NSString *chatroomId;

/**
 禁言操作类型，详见枚举值
 禁言/解除禁言操作类型：
 0：解除指定聊天室中用户禁言；
 1：禁言指定聊天室中用户；
 2：解除聊天室全体禁言；
 3：聊天室全体禁言
 4: 移出禁言用户白名单
 5: 添加禁言用户白名单
 6: 解除用户聊天室全局禁言
 7：用户聊天室全局禁言
 */
@property (nonatomic, assign) RCChatRoomMemberBanType banType;

/// 禁言的总时间（禁言的操作有此字段）(毫秒) ，最大值为 43200 分钟（1 个月）, 最小值 1 分钟
@property (nonatomic, assign) NSInteger durationTime;

/// 操作时间 (毫秒时间戳)
@property (nonatomic, assign) long long operateTime;

/// 禁言/解禁言用户 ID 列表
@property (nonatomic, copy) NSArray<NSString *> *userIdList;

/// 附加信息
@property (nonatomic, copy, nullable) NSString *extra;

@end

NS_ASSUME_NONNULL_END
