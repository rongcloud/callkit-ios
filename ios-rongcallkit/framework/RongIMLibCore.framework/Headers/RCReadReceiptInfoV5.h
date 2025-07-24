//
//  RCReadReceiptInfoV5.h
//  RongIMLibCore
//
//  Created by shuai shao on 2025/4/15.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class RCConversationIdentifier;

/// 消息的阅读回执信息。
///
/// - Since: 5.20.0
@interface RCReadReceiptInfoV5 : NSObject

/// 会话标识。
@property (nonatomic, strong, readonly) RCConversationIdentifier *identifier;

/// 消息唯一 ID。
@property (nonatomic, copy, readonly) NSString *messageUId;

/// 未读人数。
@property (nonatomic, assign, readonly) NSInteger unreadCount;

/// 已读人数。
@property (nonatomic, assign, readonly) NSInteger readCount;

/// 总人数。
@property (nonatomic, assign, readonly) NSInteger totalCount;

@end

NS_ASSUME_NONNULL_END
