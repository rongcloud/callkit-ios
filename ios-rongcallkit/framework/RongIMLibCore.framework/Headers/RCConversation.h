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

#import "RCMessageContent.h"
#import <Foundation/Foundation.h>

@class RCReadReceiptInfo, RCGroupReadReceiptInfoV2, RCMessageConfig;
/*!
 会话类

 @discussion 会话类，包含会话的所有属性。
 */
@interface RCConversation : NSObject <NSCoding>

/*!
 会话类型
 */
@property (nonatomic, assign) RCConversationType conversationType;

/*!
 会话 ID
 */
@property (nonatomic, copy) NSString *targetId;

/*!
 该会话的业务标识，长度限制 20 字符
 */
@property (nonatomic, copy) NSString *channelId;

/*!
 会话的标题
 */
@property (nonatomic, copy) NSString *conversationTitle;

/*!
 会话中的未读消息数量
 */
@property (nonatomic, assign) int unreadMessageCount;

/*!
 是否置顶，默认值为 NO

 @discussion
 如果设置了置顶，在 IMKit 的 RCConversationListViewController 中会将此会话置顶显示。
 */
@property (nonatomic, assign) BOOL isTop;

/*!
 会话中最后一条消息的接收状态
 */
@property (nonatomic, assign) RCReceivedStatus receivedStatus;

/*!
 会话中最后一条消息的发送状态
 */
@property (nonatomic, assign) RCSentStatus sentStatus;

/*!
 会话中最后一条消息的接收时间（Unix时间戳、毫秒）
 */
@property (nonatomic, assign) long long receivedTime;

/*!
 会话中最后一条消息的发送时间（Unix时间戳、毫秒）
 */
@property (nonatomic, assign) long long sentTime;

/*!
 会话中存在的草稿
 */
@property (nonatomic, copy) NSString *draft;

/*!
 会话中最后一条消息的类型名
 */
@property (nonatomic, copy) NSString *objectName;

/*!
 会话中最后一条消息的发送者用户 ID
 */
@property (nonatomic, copy) NSString *senderUserId;

/*!
 会话中最后一条消息的消息 ID
 */
@property (nonatomic, assign) long lastestMessageId;

/*!
 会话中最后一条消息的内容
 */
@property (nonatomic, strong) RCMessageContent *lastestMessage;

/*!
 会话中最后一条消息的方向
 */
@property (nonatomic, assign) RCMessageDirection lastestMessageDirection;

/*!
 会话中最后一条消息的 json Dictionary

 @discussion 此字段存放最后一条消息内容中未编码的 json 数据。
 SDK 内置的消息，如果消息解码失败，默认会将消息的内容存放到此字段；如果编码和解码正常，此字段会置为 nil。
 */
@property (nonatomic, strong) NSDictionary *jsonDict;

/*!
 最后一条消息的全局唯一 ID

 @discussion 服务器消息唯一 ID（在同一个Appkey下全局唯一）
 */
@property (nonatomic, copy) NSString *lastestMessageUId;

/*!
 会话中是否存在被 @ 的消息

 @discussion 在清除会话未读数（clearMessagesUnreadStatus:targetId:）的时候，会将此状态置成 NO。
 */
@property (nonatomic, assign, readonly) BOOL hasUnreadMentioned;

/*!
会话中 @ 消息的个数

@discussion 在清除会话未读数（clearMessagesUnreadStatus:targetId:）的时候，会将此值置成 0。
*/
@property (nonatomic, assign) int mentionedCount;

/*!
会话是否是免打扰状态
*/
@property (nonatomic, assign) RCConversationNotificationStatus blockStatus;

/*!
 最后一条消息的阅读回执状态
 */
@property (nonatomic, strong) RCReadReceiptInfo *latestMessageReadReceiptInfo;

/*!
 最后一条消息的群阅读回执状态
 @discussion 如果是调用 RCGroupReadReceiptV2Manager 中方法实现群已读回执功能，此参数才有效，否则请使用 readReceiptInfo 属性获取阅读回执状态
 @discussion 如果使用 IMKit，请用 readReceiptInfo 属性
 */
@property (nonatomic, strong) RCGroupReadReceiptInfoV2 *latestMessageGroupReadReceiptInfoV2;

/*!
 最后一条消息的消息配置
 */
@property (nonatomic, strong) RCMessageConfig *latestMessageMessageConfig;

/*!
 最后一条消息是否可以包含扩展信息
 
 @discussion 该属性在消息发送时确定，发送之后不能再做修改
 @discussion 扩展信息只支持单聊和群组，其它会话类型不能设置扩展信息
*/
@property (nonatomic, assign) BOOL latestMessageCanIncludeExpansion;

/*!
 最后一条消息的扩展信息列表
 
 @discussion 扩展信息只支持单聊和群组，其它会话类型不能设置扩展信息
 @discussion 默认消息扩展字典 key 长度不超过 32 ，value 长度不超过 4096 ，单次设置扩展数量最大为 20，消息的扩展总数不能超过 300
*/
@property (nonatomic, strong) NSDictionary<NSString *, NSString *> *latestMessageExpansion;

/*!
 免打扰级别
 */
@property (nonatomic, assign) RCPushNotificationLevel notificationLevel;
@end
