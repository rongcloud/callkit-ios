/**
 * Copyright (c) 2014-2015, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */

//  RCImageMessage.h
//  Created by Heq.Shinoda on 14-6-13.

#import <RongIMLibCore/RCMediaMessageContent.h>
#import <UIKit/UIKit.h>

/// 图片消息的类型名
#define RCImageMessageTypeIdentifier @"RC:ImgMsg"

NS_ASSUME_NONNULL_BEGIN

/// 图片消息类
///
/// 图片消息类，此消息会进行存储并计入未读消息数。
///
/// 如果想发送原图，请设置属性 full 为 YES。
///
/// - Remark: 内容类消息
@interface RCImageMessage : RCMediaMessageContent <NSCoding>

/// 图片消息的 URL 地址
///
/// 发送方此字段为图片的本地路径，接收方此字段为网络 URL 地址。
///
/// - Note: 不再允许外部赋值，为只读属性。本地地址使用 localPath，远端地址使用 remoteUrl
@property (nonatomic, copy, readonly, nullable) NSString *imageUrl;

/// 图片消息的缩略图
@property (nonatomic, strong, nullable) UIImage *thumbnailImage;

/// 缩略图的 Base64 字符串。
@property (nonatomic, copy, readonly, nullable) NSString *thumbnailBase64String;

/// 缩略图的宽度。
@property (nonatomic, assign, readonly) NSInteger thumWidth;

/// 缩略图的高度。
@property (nonatomic, assign, readonly) NSInteger thumHeight;

/// 是否发送原图
///
/// 在发送图片的时候，是否发送原图，默认值为 NO。
@property (nonatomic, getter=isFull) BOOL full;

/// 图片消息的原始图片信息
@property (nonatomic, strong, nullable) UIImage *originalImage;

/// 图片消息的原始图片信息
///
/// 发送成功之前该字段是可用的
/// 发送成功之后基于减少内存的考虑，该字段不再保存原始数据
/// 发送成功之后请优先使用 localPath 与 remoteUrl 进行展示
@property (nonatomic, strong, readonly, nullable) NSData *originalImageData;

/// 初始化图片消息
///
/// 如果想发送原图，请设置属性 full 为 YES。
///
/// - Parameter image: 原始图片
///
/// - Returns: 图片消息对象
+ (instancetype)messageWithImage:(UIImage *)image;

/// 初始化图片消息
///
/// 如果想发送原图，请设置属性 full 为 YES。
///
/// - Parameter imageURI: 图片的本地路径
/// - Warning: imageURI  必须为本地路径，否则构造失败
///
/// - Returns: 图片消息对象
+ (instancetype)messageWithImageURI:(NSString *)imageURI;

/// 初始化图片消息
///
/// 如果想发送原图，请设置属性 full 为 YES。
///
/// - Parameter imageData: 图片的原始数据
///
/// - Returns: 图片消息对象
+ (instancetype)messageWithImageData:(NSData *)imageData;

@end

NS_ASSUME_NONNULL_END
