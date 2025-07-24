//
//  RCPublicServiceCommandMessage.h
//  RongIMLib
//
//  Created by litao on 15/6/23.
//  Copyright (c) 2015 年 RongCloud. All rights reserved.
//

#import <RongIMLibCore/RongIMLibCore.h>
#import "RCPublicServiceMenuItem.h"

/*!
 公众服务请求消息的类型名
 */
#define RCPublicServiceCommandMessageTypeIdentifier @"RC:PSCmd"

/*!
 公众服务请求消息类

 - Note: 公众服务请求消息类，此消息不存储，也不计入未读消息数。
 此消息仅用于客户端公共服务账号中的菜单，向服务器发送请求。

 - Remark: 通知类消息
 */
@interface RCPublicServiceCommandMessage : RCMessageContent <NSCoding>

/*!
 请求的名称
 */
@property (nonatomic, copy) NSString *command;

/*!
 请求的内容
 */
@property (nonatomic, copy) NSString *data;

/*!
 初始化公众服务请求消息

 - Parameter item: 公众服务菜单项
 - Returns: 公众服务请求消息对象
 */
+ (instancetype)messageFromMenuItem:(RCPublicServiceMenuItem *)item;

/*!
 初始化公众服务请求消息

 - Parameter command: 请求的名称
 - Parameter data: 请求的内容
 - Returns: 公众服务请求消息对象
 */
+ (instancetype)messageWithCommand:(NSString *)command data:(NSString *)data;

@end
