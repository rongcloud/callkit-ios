//
//  RCMessageIdentifier.h
//  RongIMLibCore
//
//  Created by RC-MINI on 2025/6/11.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class RCConversationIdentifier;

/// 消息标识。
///
/// - Since: 5.20.2
@interface RCMessageIdentifier : NSObject

/// 消息所属会话。
@property (nonatomic, strong) RCConversationIdentifier *identifier;

/// 消息唯一 ID。
@property (nonatomic, copy) NSString *messageUId;

/// 初始化方法。
///
/// - Parameters:
///   - identifier: 会话标识。
///   - messageUId: 消息 UId。
- (instancetype)initWithConversationIdentifier:(RCConversationIdentifier *)identifier messageUId:(NSString *)messageUId;

@end

NS_ASSUME_NONNULL_END
