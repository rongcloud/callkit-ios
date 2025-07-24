//
//  RCCommandMessage.h
//  RongIMLib
//
//  Created by 张改红 on 15/12/2.
//  Copyright © 2015 年 RongCloud. All rights reserved.
//
#import <RongIMLibCore/RCMessageContent.h>

/// 命令消息的类型名
#define RCCommandMessageIdentifier @"RC:CmdMsg"

NS_ASSUME_NONNULL_BEGIN

/// 命令消息类
///
/// 命令消息类，此消息不存储不计入未读消息数。
/// 与 RCCommandNotificationMessage 的区别是，此消息不存储，也不会在界面上显示。
///
/// - Remark: 通知类消息
@interface RCCommandMessage : RCMessageContent <NSCoding>

/// 命令的名称
@property (nonatomic, copy) NSString *name;

/// 命令的扩展数据
///
/// 命令的扩展数据，可以为任意字符串，如存放您定义的 json 数据。
@property (nonatomic, copy, nullable) NSString *data;

/// 初始化命令消息
///
/// - Parameter name: 命令的名称
/// - Parameter data: 命令的扩展数据
///
/// - Returns: 命令消息对象
+ (instancetype)messageWithName:(NSString *)name data:(nullable NSString *)data;

@end

NS_ASSUME_NONNULL_END
