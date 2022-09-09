//
//  RCFileMessage.h
//  RongIMLib
//
//  Created by 珏王 on 16/5/23.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import <RongIMLibCore/RongIMLibCore.h>

/*!
 文件消息的类型名
 */
#define RCFileMessageTypeIdentifier @"RC:FileMsg"

NS_ASSUME_NONNULL_BEGIN
/*!
 文件消息类
 
 @discussion 文件消息类，此消息会进行存储并计入未读消息数。
 
 @remarks 内容类消息
 */
@interface RCFileMessage : RCMediaMessageContent <NSCoding>

/*!
 文件名
 */
@property (nonatomic, copy, nullable) NSString *name;

/*!
 文件大小，单位为 Byte
 */
@property (nonatomic, assign) long long size;

/*!
 文件类型
 */
@property (nonatomic, copy, nullable) NSString *type;

/*!
 文件的网络地址
 */
@property (nonatomic, copy, nullable) NSString *fileUrl;

/*!
 文件的本地路径
 */
@property (nonatomic, copy, nullable) NSString *localPath;

/*!
 初始化文件消息

 @param localPath 文件的本地路径
 @return          文件消息对象
 */
+ (instancetype)messageWithFile:(NSString *)localPath;

@end

NS_ASSUME_NONNULL_END
