//
//  RCRTCCDNStream.h
//  RongRTCLib
//
//  Created by RongCloud on 2021/5/18.
//  Copyright © 2021 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RCRTCInputStream.h"
#import "RCRTCLibDefine.h"
#import "RCRTCDrawer.h"
NS_ASSUME_NONNULL_BEGIN

typedef void (^RCRTCConfigCallback)(BOOL isSuccess, RCRTCCode code);

@class RCRTCCDNInputStream;

@protocol RCRTCCDNInputStreamDelegate <NSObject>
/*!
 SEI 数据监听回调
 
 @param cdnStream 当前 cdn 流对象
 @param data SEI 数据
 @discussion
 订阅 cdn 流成功后，通过 receiver 回调 cdn 流中包含 SEI 信息
 回调的频次取决于 cdn 流的 SEI 帧数据间隔
 */
- (void)cdnStream:(RCRTCCDNInputStream *)cdnStream handleSEIData:(NSString *)data;

@end

@interface RCRTCCDNInputStream : RCRTCInputStream

/*!
 设置 cdn 流监听代理
 */
@property (nonatomic, weak) id<RCRTCCDNInputStreamDelegate> delegate;

/*!
 获取订阅 CDN 流前设置的分辨率
 */
- (RCRTCVideoSizePreset)getVideoResolution;

/*!
 获取订阅 CDN 流前设置的帧率
 */
- (RCRTCVideoFPS)getVideoFps;

/*!
 当前订阅成功的 CDN 流最高支持的分辨率
 */
- (RCRTCVideoSizePreset)getHighestResolution;

/*!
 当前订阅成功的 CDN 流最高支持的帧率
 */
- (RCRTCVideoFPS)getHighestFPS;

/*!
  设置分辨率和帧率
  @param videoSizePreset 分辨率
  @param fps 帧率
 */
- (void)setVideoConfig:(RCRTCVideoSizePreset)videoSizePreset
              fpsValue:(RCRTCVideoFPS)fps
            completion:(nullable RCRTCConfigCallback)completion;

/*!
 设置视频流的渲染视图
 
 @param render 渲染视图
 @discussion
 接受到远端用户的视频流，然后设置视频流的渲染视图，就可以渲染出远端视频
 
 @remarks 视频配置
 */
- (void)setVideoView:(nullable id<RCRTCDrawer>)render;

@end

NS_ASSUME_NONNULL_END
