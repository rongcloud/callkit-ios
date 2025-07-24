//
//  RCLocalConfiguration.h
//  RongIMLibCore
//
//  Created by litao on 15/10/19.
//  Copyright © 2015 年 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RCLocalConfiguration : NSObject

+ (instancetype)sharedInstance;

/// 原图最大宽度，默认值：1080
@property (nonatomic, assign) NSUInteger imageWidth;
/// 原图最大高度，默认值：1080
@property (nonatomic, assign) NSUInteger imageHeight;
/// 原图质量压缩比例，默认值：0.85
@property (nonatomic, assign) float imageQuality;
/// 原图大小限制，默认值：200（单位：KB）配置发送图片时，如果图片大小不超过则发送原图
@property (nonatomic, assign) NSUInteger maxOriginalImageSize;


/// 缩略图最大边的长度，默认值：240
@property (nonatomic, assign) NSUInteger thumbnailMaxSize;
/// 缩略图最小边的长度，默认值：100
@property (nonatomic, assign) NSUInteger thumbnailMinSize;
/// 缩略图质量压缩比例，默认值：0.3
@property (nonatomic, assign) float thumbnailQuality;


/// 位置消息缩略图的最大宽度，默认值：480
@property (nonatomic, assign) float locationImageWidth;
/// 位置消息缩略图的最大高度，默认值：240
@property (nonatomic, assign) float locationImageHeight;
/// 位置消息缩略图压缩比例，默认值：0.7
@property (nonatomic, assign) float locationImageQuality;


/// 小视频压缩宽度，建议使用 16 的倍数，默认值：540
@property (nonatomic, assign) NSUInteger sightCompressWidth;
/// 小视频压缩高度，建议使用 16 的倍数，默认值：960
@property (nonatomic, assign) NSUInteger sightCompressHeight;


/// 文件下载的保存路径，默认值：Documents/MyFile
@property (nonatomic, copy) NSString *fileMessageRelativePath;

// 分片下载大小限制，超限才会去分片下载，单位为字节，默认 20971520（20MB）
@property (nonatomic, assign) long downloadSliceSize;

// 后台是否保活，默认值：NO
@property (nonatomic, assign) BOOL forceKeepAlive;

// 心跳间隔，默认值：15（单位：秒）
@property (nonatomic, assign) NSInteger heartBeatInterval;
@end
