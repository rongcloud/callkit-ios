/**
 * Copyright (c) 2014-2015, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */

//  RCConversation.h
//  Created by Heq.Shinoda on 14-6-13.

#import <Foundation/Foundation.h>

#import <RongIMLibCore/RCMessageContent.h>

NS_ASSUME_NONNULL_BEGIN

@class RCReadReceiptInfo, RCGroupReadReceiptInfoV2, RCMessageConfig;
@class RCReceivedStatusInfo, RCMessage;
@class RCEditedMessageDraft;

/// 会话类，包含会话的所有属性。
@interface RCConversation : NSObject <NSCoding>

/// 会话类型
@property (nonatomic, assign) RCConversationType conversationType;

/// 会话 ID
@property (nonatomic, copy) NSString *targetId;

/// 该会话的业务标识，长度限制 20 字符
@property (nonatomic, copy, nullable) NSString *channelId;

/// 会话的标题
@property (nonatomic, copy, nullable) NSString *conversationTitle;

/// 会话中的未读消息数量
@property (nonatomic, assign) int unreadMessageCount;

/// 是否置顶，默认值为 NO
/// 如果设置了置顶，在 IMKit 的 RCConversationListViewController 中会将此会话置顶显示。
@property (nonatomic, assign) BOOL isTop;

/// 当前会话在此 tag 下的置顶状态。
/// 仅在通过 tag 获取会话时 getConversationsFromTagByPage，此字段有效。
@property (nonatomic, assign) BOOL isTopForTag;

/// 会话中最后一条消息的接收状态
@property (nonatomic, assign) RCReceivedStatus receivedStatus __deprecated_msg("Use receivedStatusInfo instead");

/// 会话中最后一条消息的接收状态类 (针对接收的消息生效)
/// - Since: 5.6.8
@property (nonatomic, strong, nullable) RCReceivedStatusInfo *receivedStatusInfo;

/// 会话中最后一条消息的发送状态
@property (nonatomic, assign) RCSentStatus sentStatus;

/// 会话中最后一条消息的接收时间（Unix 时间戳、毫秒）
@property (nonatomic, assign) long long receivedTime;

/// 会话中最后一条消息的发送时间（Unix 时间戳、毫秒）
@property (nonatomic, assign) long long sentTime;

/// 会话的操作时间（Unix 时间戳、毫秒），用于分页获取会话列表时传入的时间戳
/// 初始值与 sentTime 相同，置顶等操作会更新此时间戳
/// - Since: 5.6.7
@property (nonatomic, assign) long long operationTime;

/// 会话中存在的草稿
@property (nonatomic, copy, nullable) NSString *draft;

/// 会话中最后一条消息的类型名
@property (nonatomic, copy, nullable) NSString *objectName;

/// 会话中最后一条消息的发送者用户 ID
@property (nonatomic, copy, nullable) NSString *senderUserId;

/// 会话中最后一条消息的消息 ID
@property (nonatomic, assign) long latestMessageId;

/// 会话中最后一条消息的内容
@property (nonatomic, strong, nullable) RCMessageContent *latestMessage;

/// 会话中最后一条的完整消息体
@property (nonatomic, strong, readonly, nullable) RCMessage *latestRCMessage;

/// 会话中最后一条消息的方向
@property (nonatomic, assign) RCMessageDirection latestMessageDirection;

/// 会话中最后一条消息的 json Dictionary
///
/// 此字段存放最后一条消息内容中未编码的 json 数据。
/// SDK 内置的消息，如果消息解码失败，默认会将消息的内容存放到此字段；如果编码和解码正常，此字段会置为 nil。
@property (nonatomic, strong, nullable) NSDictionary *jsonDict;

/// 最后一条消息的全局唯一 ID
///
/// 服务器消息唯一 ID（在同一个 AppKey 下全局唯一）
@property (nonatomic, copy, nullable) NSString *latestMessageUId;

/// 会话中是否存在被 @ 的消息
///
/// 在清除会话未读数（clearMessagesUnreadStatus:targetId:）的时候，会将此状态置成 NO。
@property (nonatomic, assign, readonly) BOOL hasUnreadMentioned;

/// 会话中 @ 消息的总个数（包含 @ 我的个数和 @ 所有人的个数）
///
/// 在清除会话未读数（clearMessagesUnreadStatus:targetId:）的时候，会将此值置成 0。
@property (nonatomic, assign) int mentionedCount;

/// 超级群会话中 @ 我的消息的个数
///
/// 只有超级群获取频道列表时有效
/// 在清除会话未读数（clearMessagesUnreadStatus:targetId:）的时候，会将此值置成 0。
@property (nonatomic, assign) int mentionedMeCount;

/// 会话是否是免打扰状态
@property (nonatomic, assign) RCConversationNotificationStatus blockStatus;

/// 最后一条消息的阅读回执状态
@property (nonatomic, strong, nullable) RCReadReceiptInfo *latestMessageReadReceiptInfo;

/// 最后一条消息的群阅读回执状态
///
/// 如果是调用 RCGroupReadReceiptV2Manager 中方法实现群已读回执功能，此参数才有效，否则请使用 readReceiptInfo 属性获取阅读回执状态
/// 如果使用 IMKit，请用 readReceiptInfo 属性
@property (nonatomic, strong, nullable) RCGroupReadReceiptInfoV2 *latestMessageGroupReadReceiptInfoV2;

/// 最后一条消息的消息配置
@property (nonatomic, strong, nullable) RCMessageConfig *latestMessageMessageConfig;

/// 最后一条消息是否可以包含扩展信息
///
/// 该属性在消息发送时确定，发送之后不能再做修改
/// 扩展信息只支持单聊和群组，其它会话类型不能设置扩展信息
@property (nonatomic, assign) BOOL latestMessageCanIncludeExpansion;

/// 最后一条消息的扩展信息列表
///
/// 扩展信息只支持单聊和群组，其它会话类型不能设置扩展信息
/// 默认消息扩展字典 key 长度不超过 32，value 长度不超过 4096，单次设置扩展数量最大为 20，消息的扩展总数不能超过 300
@property (nonatomic, strong, nullable) NSDictionary<NSString *, NSString *> *latestMessageExpansion;

/// 免打扰级别
@property (nonatomic, assign) RCPushNotificationLevel notificationLevel;

/// 超级群频道类型，只有 ConversationType 为超级群时该字段有效，非超级群时为 0
@property (nonatomic, assign) RCUltraGroupChannelType channelType;

/// 会话中第一条未读消息时间戳（Unix 时间戳、毫秒）
///
/// 仅支持 超级群会话
/// - Since: 5.2.5
@property (nonatomic, assign) long long firstUnreadMsgSendTime;

/// 文本消息翻译方式。
///
/// - Since: 5.24.0
@property (nonatomic, assign) RCTranslateStrategy translateStrategy;

/// 是否包含机器人
///
/// - Since: 5.28.0
@property (nonatomic, assign) BOOL includeRobot;

/// 修改消息草稿
///
/// - Since:5.28.0
@property (nonatomic, strong) RCEditedMessageDraft *editedMessageDraft;

@end

@interface RCConversation (deprecated)

/// 会话中最后一条消息的消息 ID
@property (nonatomic, assign) long lastestMessageId __deprecated_msg("Use latestMessageId instead");

/// 会话中最后一条消息的内容
@property (nonatomic, strong, nullable) RCMessageContent *lastestMessage __deprecated_msg("Use latestMessage instead");

/// 会话中最后一条消息的方向
@property (nonatomic, assign)
    RCMessageDirection lastestMessageDirection __deprecated_msg("Use latestMessageDirection instead");

/// 最后一条消息的全局唯一 ID
///
/// 服务器消息唯一 ID（在同一个 AppKey 下全局唯一）
@property (nonatomic, copy, nullable) NSString *lastestMessageUId __deprecated_msg("Use latestMessageUId instead");


@end

NS_ASSUME_NONNULL_END
