//
//  RCMessageReactionParams.h
//  RongIMLibCore
//
//  Created by RC on 2026/6/1.
//  Copyright © 2026 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class RCMessagePushConfig;

/// 添加或移除消息回应参数。
///
/// - Since: 5.42.0
@interface RCUpdateMessageReactionParam : NSObject

/// 消息唯一 ID。
@property (nonatomic, copy) NSString *messageUId;

/// 回应 ID。
@property (nonatomic, copy) NSString *reactionId;

/// 推送配置。
@property (nonatomic, strong, nullable) RCMessagePushConfig *pushConfig;

@end

/// 分页查询消息回应列表参数。
///
/// - Since: 5.42.0
@interface RCGetMessageReactionsParam : NSObject

/// 消息唯一 ID。
@property (nonatomic, copy) NSString *messageUId;

/// 查询数量，有效值范围 [1, 50]。
@property (nonatomic, assign) NSInteger count;

/// 分页标记。
@property (nonatomic, copy, nullable) NSString *pageToken;

@end

/// 分页查询回应用户列表参数。
///
/// - Since: 5.42.0
@interface RCGetMessageReactionUsersParam : NSObject

/// 消息唯一 ID。
@property (nonatomic, copy) NSString *messageUId;

/// 回应 ID。
@property (nonatomic, copy) NSString *reactionId;

/// 查询数量，有效值范围 [1, 50]。
@property (nonatomic, assign) NSInteger count;

/// 分页标记。
@property (nonatomic, copy, nullable) NSString *pageToken;

@end

NS_ASSUME_NONNULL_END
