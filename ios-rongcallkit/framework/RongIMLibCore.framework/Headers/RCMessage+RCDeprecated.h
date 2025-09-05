//
//  RCMessage+RCDeprecated.h
//  RongIMLibCore
//
//  Created by shuai shao on 2025/7/17.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <RongIMLibCore/RongIMLibCore.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCMessage (RCDeprecated)

/// 消息的接收状态 (针对接收的消息生效)
@property (nonatomic, assign) RCReceivedStatus receivedStatus __deprecated_msg("Use receivedStatusInfo instead");

/// RCMessage 初始化方法（已废弃，请不要使用该接口构造消息发送）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter messageDirection: 消息的方向
/// - Parameter messageId: 消息的 ID（如果是发送该消息初始值请设置为 -1）
/// - Parameter content: 消息的内容
- (instancetype)initWithType:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
                   direction:(RCMessageDirection)messageDirection
                   messageId:(long)messageId
                     content:(RCMessageContent *)content
    __deprecated_msg("Use initWithType:targetId:direction:content: instead");

@end

NS_ASSUME_NONNULL_END
