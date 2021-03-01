//
//  RCReferenceMessage.h
//  RongIMLib
//
//  Created by 张改红 on 2020/2/26.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <RongIMLibCore/RongIMLibCore.h>
/*!
 引用消息的类型名
 */
#define RCReferenceMessageTypeIdentifier @"RC:ReferenceMsg"
/*!
引用消息类

@discussion 引用消息类，此消息会进行存储并计入未读消息数。
 
@remarks 内容类消息
*/
@interface RCReferenceMessage : RCMessageContent
/*!
 引用文本
 */
@property (nonatomic, strong) NSString *content;
/*!
 被引用消息的发送者 ID
 */
@property (nonatomic, strong) NSString *referMsgUserId;
/*!
 被引用消息体
 */
@property (nonatomic, strong) RCMessageContent *referMsg;
/*!
 扩展字段
 */
@property (nonatomic, strong) NSString *extra;
@end
