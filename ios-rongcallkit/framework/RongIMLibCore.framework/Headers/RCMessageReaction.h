//
//  RCMessageReaction.h
//  RongIMLibCore
//
//  Created by RC on 2026/6/1.
//  Copyright © 2026 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class RCMessageReactionUser;

/// 消息回应摘要数据。
///
/// - Since: 5.42.0
@interface RCMessageReaction : NSObject <NSCopying, NSCoding>

/// 消息唯一 ID。
@property (nonatomic, copy) NSString *messageUId;

/// 回应 ID。
@property (nonatomic, copy) NSString *reactionId;

/// 当前用户是否已回应。
@property (nonatomic, assign) BOOL hasCurrentUserReacted;

/// 回应该消息的部分用户列表。
@property (nonatomic, strong) NSArray<RCMessageReactionUser *> *users;

/// 回应总数。
@property (nonatomic, assign) NSInteger totalCount;

/// 回应时间，Unix 时间戳，单位毫秒。
@property (nonatomic, assign) long long reactionTime;

@end

NS_ASSUME_NONNULL_END
