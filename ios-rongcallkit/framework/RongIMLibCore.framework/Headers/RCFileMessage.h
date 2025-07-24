//
//  RCFileMessage.h
//  RongIMLib
//
//  Created by 珏王 on 16/5/23.
//  Copyright © 2016 年 RongCloud. All rights reserved.
//

#import <RongIMLibCore/RongIMLibCore.h>

/// 文件消息的类型名
#define RCFileMessageTypeIdentifier @"RC:FileMsg"

NS_ASSUME_NONNULL_BEGIN

/// 文件消息类
///
/// 文件消息类，此消息会进行存储并计入未读消息数。
///
/// - Remark: 内容类消息
@interface RCFileMessage : RCMediaMessageContent <NSCoding>

/// 文件大小，单位为 Byte
@property (nonatomic, assign) long long size;

/// 文件类型
@property (nonatomic, copy, nullable) NSString *type;

/// 文件的网络地址
@property (nonatomic, copy, nullable) NSString *fileUrl;

/// 初始化文件消息
///
/// - Parameter localPath: 文件的本地路径
/// - Returns: 文件消息对象
+ (instancetype)messageWithFile:(NSString *)localPath;

@end

NS_ASSUME_NONNULL_END
