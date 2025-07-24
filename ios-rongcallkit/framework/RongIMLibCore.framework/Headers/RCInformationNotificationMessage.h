/**
 * Copyright (c) 2014-2015, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */

//  RCInformationNotificationMessage.h
//  Created by xugang on 14/12/4.

#import <RongIMLibCore/RCMessageContent.h>

/// 通知消息的类型名
#define RCInformationNotificationMessageIdentifier @"RC:InfoNtf"

NS_ASSUME_NONNULL_BEGIN

/// 通知消息类
///
/// 通知消息类，此消息会进行存储，但不计入未读消息数。
///
/// - Remark: 通知类消息
@interface RCInformationNotificationMessage : RCMessageContent <NSCoding>

/// 通知的内容
@property (nonatomic, copy) NSString *message;

/// 初始化通知消息
///
/// - Parameter message: 通知的内容
/// - Parameter extra: 通知的附加信息
///
/// - Returns: 通知消息对象
+ (instancetype)notificationWithMessage:(NSString *)message extra:(nullable NSString *)extra;

@end

NS_ASSUME_NONNULL_END
