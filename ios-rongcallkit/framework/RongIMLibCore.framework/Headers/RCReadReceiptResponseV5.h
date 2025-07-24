//
//  RCReadReceiptResponseV5.h
//  RongIMLibCore
//
//  Created by shuai shao on 2025/4/25.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class RCReadReceiptUser;
@class RCConversationIdentifier;

/// 消息已读回执响应信息。
///
/// - Since: 5.20.0
@interface RCReadReceiptResponseV5 : NSObject

/// 会话信息。
@property (nonatomic, strong, readonly) RCConversationIdentifier *identifier;

/// 消息唯一 ID。
@property (nonatomic, copy, readonly) NSString *messageUId;

/// 已读回执的用户。
@property (nonatomic, copy, readonly) NSArray<RCReadReceiptUser *> *users;

/// 已读人数。
@property (nonatomic, assign, readonly) NSInteger readCount;

/// 未读总数。
@property (nonatomic, assign, readonly) NSInteger unreadCount;

/// 总人数。
@property (nonatomic, assign, readonly) NSInteger totalCount;

@end

NS_ASSUME_NONNULL_END
