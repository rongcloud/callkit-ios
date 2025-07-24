/**
 * Copyright (c) 2014-2015, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */

//  RCProfileNotificationMessage.h
//  Created by xugang on 14/11/28.

#import <RongIMLibCore/RCMessageContent.h>

/// 公众服务账号信息变更消息的类型名
#define RCProfileNotificationMessageIdentifier @"RC:ProfileNtf"

NS_ASSUME_NONNULL_BEGIN

/// 公众服务账号信息变更消息类
///
/// 公众服务账号信息变更消息类，此消息会进行存储，但不计入未读消息数。
/// - Remark: 通知类消息
@interface RCProfileNotificationMessage : RCMessageContent <NSCoding>

/// 公众服务账号信息变更的操作名
@property (nonatomic, copy) NSString *operation;

/// 信息变更的数据，可以为任意格式，如 json 数据。
@property (nonatomic, copy, nullable) NSString *data;

/// 初始化公众服务账号信息变更消息
///
/// - Parameter operation: 信息变更的操作名
/// - Parameter data: 信息变更的数据
/// - Parameter extra: 信息变更的附加信息
/// - Returns: 公众服务账号信息变更消息的对象
+ (instancetype)notificationWithOperation:(NSString *)operation
                                     data:(nullable NSString *)data
                                    extra:(nullable NSString *)extra;

@end

NS_ASSUME_NONNULL_END
