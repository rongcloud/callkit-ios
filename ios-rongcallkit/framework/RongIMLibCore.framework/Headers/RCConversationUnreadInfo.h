//
//  RCConversationUnreadInfo.h
//  RongIMLibCore
//
//  Created by shuai shao on 2023/6/2.
//  Copyright © 2023 RongCloud. All rights reserved.
//

#import <RongIMLibCore/RongIMLibCore.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCConversationUnreadInfo : NSObject

/// 会话类型
@property (nonatomic, assign) RCConversationType conversationType;

/// 会话 ID
@property (nonatomic, copy) NSString *targetId;

/// 该会话的业务标识，长度限制 20 字符
@property (nonatomic, copy, nullable) NSString *channelId;

/// 会话中的未读消息数量
@property (nonatomic, assign) int unreadMessageCount;

/// 会话中 @ 消息的总个数（包含 @ 我的个数和 @ 所有人的个数）
@property (nonatomic, assign) int mentionedCount;

/// 超级群会话中 @ 我的消息的个数
/// 只有超级群获取频道列表时有效
@property (nonatomic, assign) int mentionedMeCount;

/// 免打扰级别
@property (nonatomic, assign) RCPushNotificationLevel notificationLevel;

/// 初始化
- (instancetype)initWithConversation:(RCConversation *)conversation;

@end

NS_ASSUME_NONNULL_END
