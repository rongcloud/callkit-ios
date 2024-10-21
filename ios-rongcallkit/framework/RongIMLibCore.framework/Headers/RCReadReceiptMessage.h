/**
 * Copyright (c) 2014-2015, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */

//  RCHasReadNotificationMessage.h
//  Created by Heq.Shinoda on 14-6-13.

#import <RongIMLibCore/RCMessageContent.h>

#define RCHasReadNotificationMessageTypeIdentifier @"RC:ReadNtf"

/*!
 已读通知消息类

 已读通知消息类，此消息会进行不存储不计入未读消息数。

 - Remark: 信令类消息
*/
@interface RCReadReceiptMessage : RCMessageContent <NSCoding>

/**
 *  最后一条消息的发送时间
 */
@property (nonatomic, assign) long long lastMessageSendTime;

/**
 *  最后一条消息的id（融云全局唯一Id）
 */
@property (nonatomic, copy) NSString *messageUId;

/**
 *  已读消息类型，目前传1 按照会话来更新未读消息状态
 */
@property (nonatomic, assign) RCReadReceiptMessageType type;

+ (instancetype)notificationWithLastMessageSendTime:(long long)lastMessageSendTime;

@end
