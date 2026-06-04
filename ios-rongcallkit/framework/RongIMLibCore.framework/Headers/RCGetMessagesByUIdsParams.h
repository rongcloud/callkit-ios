//
//  RCGetMessagesByUIdsParams.h
//  RongIMLibCore
//
//  Created by Codex on 2026/5/8.
//  Copyright © 2026 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class RCConversationIdentifier;

/// 批量按消息 UID 查询消息参数。
///
/// - Since: 5.36.0
@interface RCGetMessagesByUIdsParams : NSObject

/// 会话标识。
@property (nonatomic, strong) RCConversationIdentifier *conversationIdentifier;

/// 消息唯一 ID 数组，最多 20 个。
@property (nonatomic, copy) NSArray<NSString *> *messageUIds;

@end

NS_ASSUME_NONNULL_END
