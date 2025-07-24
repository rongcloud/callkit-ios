/**
 * Copyright (c) 2014-2015, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */

//  RCCommandNotificationMessage.h
//  Created by xugang on 14/11/28.

#import <RongIMLibCore/RCMessageContent.h>

/// 命令提醒消息的类型名
#define RCCommandNotificationMessageIdentifier @"RC:CmdNtf"

NS_ASSUME_NONNULL_BEGIN

/// 命令提醒消息类
///
/// 此消息会进行存储，但不计入未读消息数。
/// 与 RCCommandMessage 的区别是，此消息会进行存储并在界面上显示。
///
/// - Remark: 通知类消息
@interface RCCommandNotificationMessage : RCMessageContent <NSCoding>

/// 命令提醒的名称
@property (nonatomic, copy) NSString *name;

/// 命令提醒消息的扩展数据
///
/// 命令提醒消息的扩展数据，可以为任意字符串，如存放您定义的 json 数据。
@property (nonatomic, copy, nullable) NSString *data;

/// 初始化命令提醒消息
///
/// - Parameter name: 命令的名称
/// - Parameter data: 命令的扩展数据
///
/// - Returns: 命令提醒消息对象
+ (instancetype)notificationWithName:(NSString *)name data:(nullable NSString *)data;

@end

NS_ASSUME_NONNULL_END
