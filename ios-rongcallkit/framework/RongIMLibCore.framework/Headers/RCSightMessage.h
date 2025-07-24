//
//  RCSightMessage.h
//  RongIMLib
//
//  Created by LiFei on 2016/12/1.
//  Copyright © 2016 年 RongCloud. All rights reserved.
//

#import <RongIMLibCore/RongIMLibCore.h>
#import <UIKit/UIKit.h>

/// 小视频消息的类型名
#define RCSightMessageTypeIdentifier @"RC:SightMsg"

NS_ASSUME_NONNULL_BEGIN

@class AVAsset;

/// 小视频消息类
///
/// 小视频消息类，此消息会进行存储并计入未读消息数。
///
/// - Remark: 内容类消息
///
@interface RCSightMessage : RCMediaMessageContent <NSCoding>

/// 网络 URL 地址
@property (nonatomic, readonly, nullable) NSString *sightUrl;

/// 视频时长，以秒为单位
@property (nonatomic, assign, readonly) NSUInteger duration;

/// 文件大小
@property (nonatomic, assign, readonly) long long size;

/// 缩略图
@property (nonatomic, strong, readonly, nullable) UIImage *thumbnailImage;


/// 创建小视频消息的便利构造方法
///
/// - Parameter path: 视频文件本地路径
/// - Parameter image: 视频首帧缩略图
/// - Parameter duration: 视频时长，以秒为单位
/// - Returns: 视频消息实例变量
///
+ (instancetype)messageWithLocalPath:(NSString *)path thumbnail:(UIImage *)image duration:(NSUInteger)duration;

@end

NS_ASSUME_NONNULL_END
