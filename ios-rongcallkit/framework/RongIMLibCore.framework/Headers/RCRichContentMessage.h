/**
 * Copyright (c) 2014-2015, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */

//  RCRichContentMessage.h
//  Created by Gang Li on 10/17/14.

#import "RCMessageContent.h"
#import <UIKit/UIKit.h>

/*!
 图文消息的类型名
 */
#define RCRichContentMessageTypeIdentifier @"RC:ImgTextMsg"

NS_ASSUME_NONNULL_BEGIN

/*!
 图文消息类

 图文消息类，此消息会进行存储并计入未读消息数。
 
 - Remark: 内容类消息
 */
@interface RCRichContentMessage : RCMessageContent <NSCoding>

/*!
 图文消息的标题
 */
@property (nonatomic, copy) NSString *title;

/*!
 图文消息的内容摘要
 */
@property (nonatomic, copy) NSString *digest;

/*!
 图文消息图片 URL
 */
@property (nonatomic, copy) NSString *imageURL;

/*!
 图文消息中包含的需要跳转到的URL
 */
@property (nonatomic, copy, nullable) NSString *url;

/*!
 初始化图文消息

 - Parameter title: 图文消息的标题
 - Parameter digest: 图文消息的内容摘要
 - Parameter imageURL: 图文消息的图片URL
 - Parameter extra: 图文消息的扩展信息
 - Returns: 图文消息对象
 */
+ (instancetype)messageWithTitle:(NSString *)title
                          digest:(NSString *)digest
                        imageURL:(NSString *)imageURL
                           extra:(nullable NSString *)extra;

/*!
 初始化图文消息

 - Parameter title: 图文消息的标题
 - Parameter digest: 图文消息的内容摘要
 - Parameter imageURL: 图文消息的图片URL
 - Parameter url: 图文消息中包含的需要跳转到的URL
 - Parameter extra: 图文消息的扩展信息
 - Returns: 图文消息对象
 */
+ (instancetype)messageWithTitle:(NSString *)title
                          digest:(NSString *)digest
                        imageURL:(NSString *)imageURL
                             url:(nullable NSString *)url
                           extra:(nullable NSString *)extra;

@end

NS_ASSUME_NONNULL_END
