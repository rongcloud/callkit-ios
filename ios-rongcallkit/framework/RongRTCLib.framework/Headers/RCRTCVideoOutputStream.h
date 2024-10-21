//
//  RCRTCVideoOutputStream.h
//  RongRTCLib
//
//  Created by RongCloud on 2020/6/2.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import "RCRTCOutputStream.h"
#import "RCRTCVideoSourceInterface.h"
#import "RCRTCDrawer.h"
@class RCRTCVideoView;
@class RCRTCVideoTextureView;
@class RCRTCVideoOutputStream;
@class RCRTCVideoFrame;

NS_ASSUME_NONNULL_BEGIN

@class RCRTCVideoStreamConfig;

/*!
 接收到视频流事件的代理
 */
@protocol RCRTCVideoOutputStreamEventDelegate <NSObject>

@optional
/*!
 视频数据大小发生变化回调
 
 @param stream  流信息
 @param size    流变化后的宽和高

 @discussion
 回调给流size的数据变化
 
 @remarks 代理
 added from 5.1.14
 */
- (void)outputVideoStream:(RCRTCVideoOutputStream *)stream didChangedFrameSize:(CGSize)size;

/*!
 视频数据方向发生变化回调
 
 @param stream  流信息
 @param rotation   0、90、180、270

 @discussion
 回调给流方向的数据变化
 
 @remarks 代理
 added from 5.1.14
 */
- (void)outputVideoStream:(RCRTCVideoOutputStream *)stream didChangedRotation:(NSInteger)rotation;

/*!
 采集视频数据回调
 
 @param videoFrame 采集的视频数据，类型为 RCRTCVideoFrameFormatNV12
 @param stream 采集的视频帧数据所属接收到的流
 @discussion
 采集的视频数据，如果修改该视频帧，会影响本地渲染和编码发送的视频帧数据，不支持修改数据格式
 
 @remarks 代理
 added from 5.2.3
 */
- (void)outputVideoStream:(RCRTCVideoOutputStream *)stream captureVideoFrame:(nullable RCRTCVideoFrame *)videoFrame;

/*!
 即将渲染视频帧的数据回调
 
 @param videoFrame 即将渲染的视频帧数据，类型为 RCRTCVideoFrameFormatI420
 @param stream 即将渲染的视频帧数据所属接收到的流
 @discussion
 即将渲染视频帧数据，如果修改该视频帧，会影响本地视频渲染，不支持修改数据格式
 
 @remarks 代理
 added from 5.1.14
 */
- (void)outputVideoStream:(RCRTCVideoOutputStream *)stream willRenderVideoFrame:(nullable RCRTCVideoFrame *)videoFrame;

/*!
 即将编码发送的视频帧数据回调
 
 @param videoFrame 即将编码发送的视频帧数据，类型为 RCRTCVideoFrameFormatI420
 @param stream 即将编码发送的视频帧数据所属接收到的流
 @discussion
 即将编码发送的视频帧数据，如果修改该视频帧，会影响发送出去的视频帧，不支持修改数据格式
 
 @remarks 代理
 added from 5.2.1
 */
- (void)outputVideoStream:(RCRTCVideoOutputStream *)stream willEncodeVideoFrame:(nullable RCRTCVideoFrame *)videoFrame;

@end

/**
 视频数据写入接口
 */
@protocol RCRTCVideoObserverInterface <NSObject>

/*!
 写入媒体流
 
 @param videoFrame 媒体数据
 @param error 失败时返回的相关描述
 @discussion 写入媒体流, 该方法会直接将视频数据进行视频编码并发送至远端
 
 @remarks 资源管理
 */
- (void)writeVideoFrame:(RCRTCVideoFrame *)videoFrame error:(NSError **)error;

/*!
 写入媒体流
 
 @param videoFrame 媒体数据
 @param mirror 视频数据是否镜像发送
 @param error 失败时返回的相关描述
 @discussion 写入媒体流, 该方法会直接将视频数据进行视频编码并发送至远端
 
 @remarks 资源管理
 */
- (void)writeVideoFrame:(RCRTCVideoFrame *)videoFrame mirror:(BOOL)mirror error:(NSError **)error;


- (void)write:(CMSampleBufferRef)sample
        error:(NSError **)error DEPRECATED_MSG_ATTRIBUTE("use writeVideoFrame:error: instead");
- (void)write:(CMSampleBufferRef)sample
       mirror:(BOOL)mirror
        error:(NSError **)error DEPRECATED_MSG_ATTRIBUTE("use writeVideoFrame:mirror:error: instead");

@end

@interface RCRTCVideoOutputStream : RCRTCOutputStream <RCRTCVideoObserverInterface>

/**
 本地视频配置
 */
@property (nonatomic, copy, nullable) RCRTCVideoStreamConfig *videoConfig;

/**
 输出视频源
 */
@property (nonatomic, weak, nullable) id<RCRTCVideoSourceInterface> videoSource;

@property (atomic, copy, nullable) RCRTCVideoFrameCallback videoFrameSendCallback DEPRECATED_MSG_ATTRIBUTE("use RCRTCVideoOutputStream.h outputVideoStream:willEncodeVideoFrame: instead");

@property (atomic, copy, nullable) RCRTCVideoCMSampleBufferCallback videoSendBufferCallback DEPRECATED_MSG_ATTRIBUTE("use RCRTCVideoOutputStream.h outputVideoStream:willEncodeVideoFrame: instead");

/*!
 接收到视频流事件的代理
 */
@property (nonatomic, weak, nullable) id<RCRTCVideoOutputStreamEventDelegate> streamEventDelegate;

/*!
 初始化视频流数据并设置标签
 
 @param tag 用户自定标签，注：用户不能传特殊字符，只支持 ASCII
 @discussion
 初始化流数据的参数
 
 @remarks 资源管理
 @return 流对象
 */
- (instancetype)initVideoOutputStreamWithTag:(NSString *)tag;

/*!
 设置视频流的渲染视图
 
 @param view 渲染界面，传空则将原视图删除
 @discussion
 设置视频媒体数据的渲染界面
 
 @remarks 资源管理
 */
- (void)setVideoView:(nullable id<RCRTCDrawer>)view;

/*!
 设置视频媒体数据的渲染纹理界面
 
 @param view 渲染纹理界面，传空则将原视图删除
 @discussion
 设置视频媒体数据的渲染纹理界面
 
 @remarks 资源管理
 */
- (void)setVideoTextureView:(nullable RCRTCVideoTextureView *)view;

/*!
 设置视频源
 
 @param source 视频源
 @discussion
 设置视频源，如果使用者需要自定义视频流的话，需要实现 RCRTCVideoSourceInterface 协议，视频源中通过调用 RCRTCVideoOutputStream 的 write 方法写入视频数据
 
 @remarks 资源管理
 */
- (void)setVideoSource:(nullable id<RCRTCVideoSourceInterface>)source;

#pragma mark - 水印

/*!
 设置水印

 @param image 水印图片，如果该参数为 nil，则移除水印
 @param position 水印位置尺寸

 @return 水印是否设置成功

 @discussion Added from 5.1.15
 position 范围 0 ~ 1, 左上角为原点，
 x：水印的坐标，取值范围为0 ~ 1的浮点数。
 y：水印的坐标，取值范围为0 ~ 1的浮点数。
 width：水印的宽度，取值范围为0 ~ 1的浮点数。
 height：不用设置，内部会根据水印图片的宽高比自动计算一个合适的高度。
 
 例如：当前视频的编码分辨率是 640 × 480 ，且 position 设置为（0.1，0.1，0.2，0.0）
      那么水印的左上坐标点就是（480 × 0.1，640 × 0.1）即（48，64）
      水印的宽度是 480 × 0.2 = 96px，水印的高度会根据水印图片的宽高比由 SDK 自动算出。

 @remarks RCRTCEngine：媒体流操作
 */
- (BOOL)setWaterMark:(nullable UIImage *)image position:(CGRect)position;

@end

NS_ASSUME_NONNULL_END
