//
//  RCSyncReadStatusMessage.h
//  RongIMLib
//
//  Created by 杜立召 on 16/8/22.
//  Copyright © 2016 年 RongCloud. All rights reserved.
//

#import "RCMessageContent.h"

/*!
 消息已读状态同步消息类

 消息已读状态同步消息类，此消息会进行不存储不计入未读消息数。

 - Remark: 信令类消息
*/
@interface RCSyncReadStatusMessage : RCMessageContent <NSCoding>
#define RCSyncReadStatusMessageTypeIdentifier @"RC:SRSMsg"

/// 最后一条消息的发送时间
@property (nonatomic, assign) long long lastMessageSendTime;

+ (instancetype)notificationWithLastMessageSendTime:(long long)lastMessageSendTime;

@end
