//
//  RCRTCVideoInputStream.h
//  RongRTCLib
//
//  Created by RongCloud on 2020/6/1.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import "RCRTCInputStream.h"
#import "RCRTCDrawer.h"

NS_ASSUME_NONNULL_BEGIN

@class RCRTCVideoInputStream;
/*!
 接收到视频流的代理
 */
DEPRECATED_MSG_ATTRIBUTE("please use RCRTCInputStream.h RCRTCVideoInputStreamEventDelegate instead")
@protocol RCRTCVideoInputStreamDelegate <NSObject>

/*!
 即将渲染视频帧的数据回调
 
 @param ref 即将渲染的视频帧数据
 @param stream 即将渲染的视频帧数据所属接收到的流
 @discussion
 即将渲染视频帧数据, 如果需要自定义视频显示的话需要修改该视频帧
 
 @remarks 代理
 */
- (void)willRenderCVPixelBufferRef:(CVPixelBufferRef)ref stream:(RCRTCInputStream *)stream;
@end


/*!
 接收到视频流事件的代理
 */
@protocol RCRTCVideoInputStreamEventDelegate <NSObject>

@optional
/*!
 视频数据大小发生变化回调
 
 @param stream  流信息
 @param size   流变化后的宽高

 @discussion
 回调给流size的数据变化
 
 @remarks 代理
 added from 5.1.14
 */
- (void)inputVideoStream:(RCRTCVideoInputStream *)stream didChangedFrameSize:(CGSize)size;

/*!
 视频数据方向发生变化回调
 
 @param stream  流信息
 @param rotation   0、90、180、270

 @discussion
 回调给流方向的数据变化
 
 @remarks 代理
 added from 5.1.14
 */
- (void)inputVideoStream:(RCRTCVideoInputStream *)stream didChangedRotation:(NSInteger)rotation;

/*!
 即将渲染视频帧的数据回调
 
 @param videoFrame 即将渲染的视频帧数据
 @param stream 即将渲染的视频帧数据所属接收到的流
 @discussion
 即将渲染视频帧数据，如果修改该视频帧，会影响本地渲染远端用户的视频帧，不支持修改数据格式
 
 @remarks 代理
 added from 5.1.14
 */
- (void)inputVideoStream:(RCRTCVideoInputStream *)stream willRenderVideoFrame:(nullable RCRTCVideoFrame *)videoFrame;

@end

/*!
 接收到的视频流
 */
@interface RCRTCVideoInputStream : RCRTCInputStream

/*!
 接收到视频流事件的代理
 */
@property (nonatomic, weak, nullable) id<RCRTCVideoInputStreamEventDelegate> streamEventDelegate;

/*!
 接收到的视频流代理
 */
@property (nonatomic, weak, nullable) id<RCRTCVideoInputStreamDelegate> delegate DEPRECATED_MSG_ATTRIBUTE(
    "please use RCRTCVideoInputStream.h streamEventDelegate instead");

/*!
 初始化
 
 @discussion
 初始化
 
 @warning
 请勿调用, 仅供 SDK 内部调用
 
 @remarks 资源管理
 @return RCRTCVideoInputStream 实例对象
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
 初始化
 
 @discussion
 初始化
 
 @warning
 请勿调用, 仅供 SDK 内部调用
 
 @remarks 资源管理
 @return RCRTCVideoInputStream 实例对象
 */
- (instancetype)new NS_UNAVAILABLE;

/*!
 设置视频流的渲染视图
 
 @param view 渲染视图 RCRTCVideoView 对象
 @discussion
 接受到远端用户的视频流，然后设置视频流的渲染视图，就可以渲染出远端视频
 
 @remarks 视频配置
 */
- (void)setVideoView:(nullable id<RCRTCDrawer>)view;

/*!
 设置视频流的渲染纹理视图
 
 @param view 渲染纹理视图
 @discussion
 接受到远端用户的视频流，然后设置视频流的渲染纹理视图，就可以渲染出远端视频
 
 @remarks 视频配置
 */
- (void)setVideoTextureView:(nullable RCRTCVideoTextureView *)view;

@end

NS_ASSUME_NONNULL_END
