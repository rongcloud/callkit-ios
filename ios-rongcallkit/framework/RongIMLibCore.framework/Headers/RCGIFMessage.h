//
//  RCGIFMessage.h
//  RongIMLib
//
//  Created by liyan on 2018/12/20.
//  Copyright © 2018 年 RongCloud. All rights reserved.
//

#import <RongIMLibCore/RongIMLibCore.h>

NS_ASSUME_NONNULL_BEGIN

/// GIF 消息的类型名
///
/// 仅支持 gif 类型的图片；jpg、png 等其他格式的图片请使用 RCImageMessage
#define RCGIFMessageTypeIdentifier @"RC:GIFMsg"

/// GIF 消息
///
/// GIF 消息类，此消息会进行存储并计入未读消息数。
///
/// - Remark: 内容类消息
@interface RCGIFMessage : RCMediaMessageContent

/// GIF 图的大小，单位字节
@property (nonatomic, assign) long long gifDataSize;

/// GIF 图的宽
@property (nonatomic, assign) long width;

/// GIF 图的高
@property (nonatomic, assign) long height;

/// 初始化 GIF 消息
///
/// - Parameter gifImageData: GIF 图的数据
/// - Parameter width: GIF 的宽
/// - Parameter height: GIF 的高
///
/// - Returns: GIF 消息对象
+ (instancetype)messageWithGIFImageData:(NSData *)gifImageData width:(long)width height:(long)height;

/// 初始化 GIF 消息
///
/// - Parameter gifURI: GIF 的本地路径
/// - Parameter width: GIF 的宽
/// - Parameter height: GIF 的高
///
/// - Returns: GIF 消息对象
+ (instancetype)messageWithGIFURI:(NSString *)gifURI width:(long)width height:(long)height;

@end

NS_ASSUME_NONNULL_END
