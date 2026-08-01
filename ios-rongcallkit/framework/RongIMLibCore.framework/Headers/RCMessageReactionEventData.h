//
//  RCMessageReactionEventData.h
//  RongIMLibCore
//
//  Created by RC on 2026/6/16.
//  Copyright © 2026 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class RCConversationIdentifier;
@class RCMessageReactionUser;

/// 消息回应变更类型。
///
/// - Since: 5.42.0
typedef NS_ENUM(NSInteger, RCMessageReactionOperationType) {
    /// 添加消息回应。
    RCMessageReactionOperationTypeAdded = 1,
    /// 移除消息回应。
    RCMessageReactionOperationTypeRemoved = 2,
    /// 清空该消息的全部回应。
    ///
    /// 当操作类型为此值时，`reactionId` 为空字符串，`users` 为空数组。
    RCMessageReactionOperationTypeCleared = 3,
};

/// 消息回应变更数据。
///
/// - Since: 5.42.0
@interface RCMessageReactionEventData : NSObject <NSCopying, NSCoding>

/// 会话标识。
@property (nonatomic, strong, nullable) RCConversationIdentifier *conversationIdentifier;

/// 消息唯一 ID。
@property (nonatomic, copy) NSString *messageUId;

/// 回应 ID。
///
/// 当 `operationType` 为 `RCMessageReactionOperationTypeCleared` 时，该值为空字符串。
@property (nonatomic, copy) NSString *reactionId;

/// 消息回应操作类型。
@property (nonatomic, assign) RCMessageReactionOperationType operationType;

/// 回应该消息的部分用户列表。
///
/// 当 `operationType` 为 `RCMessageReactionOperationTypeCleared` 时，该值为空数组。
@property (nonatomic, strong) NSArray<RCMessageReactionUser *> *users;

/// 回应总数。
@property (nonatomic, assign) NSInteger totalCount;

@end

NS_ASSUME_NONNULL_END
