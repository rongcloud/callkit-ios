/**
 * Copyright (c) 2014-2015, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */

//  RCTextMessage.h
//  Created by Heq.Shinoda on 14-6-13.

#import <RongIMLibCore/RCMessageContent.h>

/// 文本消息的类型名
#define RCTextMessageTypeIdentifier @"RC:TxtMsg"

NS_ASSUME_NONNULL_BEGIN
@class RCTranslateInfo;
/// 文本消息类
///
/// 文本消息类，此消息会进行存储并计入未读消息数。
///
/// - Remark: 内容类消息
@interface RCTextMessage : RCMessageContent <NSCoding>

/// 文本消息的内容
@property (nonatomic, copy) NSString *content;

/// 翻译信息。
///
/// - Since: 5.24.0
@property (nonatomic, strong) RCTranslateInfo *translateInfo;

/// 初始化文本消息
///
/// - Parameter content: 文本消息的内容
/// - Returns: 文本消息对象
+ (instancetype)messageWithContent:(NSString *)content;

@end

NS_ASSUME_NONNULL_END
