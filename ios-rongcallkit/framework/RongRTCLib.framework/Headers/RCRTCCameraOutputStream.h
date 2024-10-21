//
//  RCRTCCameraOutputStream.h
//  RongRTCLib
//
//  Created by RongCloud on 2019/1/8.
//  Copyright © 2019年 RongCloud. All rights reserved.
//

#import <CoreMedia/CoreMedia.h>
#import <UIKit/UIKit.h>

#import "RCRTCLibDefine.h"
#import "RCRTCVideoView.h"
#import "RCRTCVideoOutputStream.h"
#import "RCRTCVideoStreamConfig.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 摄像头输出流，以摄像头为视频源的视频输出流
 */
@interface RCRTCCameraOutputStream : RCRTCVideoOutputStream

/*!
 当前开启摄像头位置
 */
@property (nonatomic, assign) RCRTCDeviceCamera cameraPosition;

/*!
 摄像头采集角度
 默认以 AVCaptureVideoOrientationPortrait 角度进行采集
 */
@property (nonatomic, assign) AVCaptureVideoOrientation videoOrientation;

/*!
 本地摄像头采集是否镜像
 
 前置摄像头默认: YES，后置摄像头默认: NO
 */
@property (nonatomic, assign) BOOL isCaptureMirror;

/*!
 本地摄像头采集是否镜像
 
 前置摄像头默认: YES，后置摄像头默认: NO
 */
@property (nonatomic, assign) BOOL isPreviewMirror DEPRECATED_MSG_ATTRIBUTE("use RCRTCCameraOutputStream.h isCaptureMirror instead");;

/*!
 本地摄像头发送数据是否镜像
 
 默认: NO, 不镜像
 */
@property (nonatomic, assign) BOOL isEncoderMirror;

/*!
 是否启用视频小流

 摄像头视频流，默认开启。自定义视频流，默认关闭
 */
@property (nonatomic, assign) BOOL enableTinyStream;

@property (atomic, copy, nullable) RCRTCVideoCMSampleBufferCallback videoDisplayBufferCallback DEPRECATED_MSG_ATTRIBUTE("please use RCRTCVideoOutputStream.h outputVideoStream:willRenderVideoFrame: instead");

/*!
 初始化
 
 @discussion
 初始化
 
 @warning
 请勿调用, 仅供 SDK 内部调用，如要获取实例对象，请使用 [RCRTCEngine sharedInstance].defaultVideoStream 获取实例。
 
 @remarks 资源管理
 @return RCRTCCameraOutputStream 实例对象
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
 初始化
 
 @discussion
 初始化
 
 @warning
 请勿调用, 仅供 SDK 内部调用，如要获取实例对象，请使用 [RCRTCEngine sharedInstance].defaultVideoStream 获取实例。
 
 @remarks 资源管理
 @return RCRTCCameraOutputStream 实例对象
 */
- (instancetype)new NS_UNAVAILABLE;

/*!
 写入视频流数据
 
 @param sample 媒体数据
 @param error 失败时返回的相关描述
 @discussion
 写入视频流数据
 
 @warning
 请勿调用，摄像头输出流内部已经实现摄像头数据采集，调用者无需自己写入视频流数据
 
 @remarks 资源管理
 */
- (void)write:(CMSampleBufferRef)sample error:(NSError **)error NS_UNAVAILABLE;

/*!
 设置视频源
 
 @param videoSource 视频源
 @discussion
 请勿调用，摄像头输出流的视频源已经封装在 SDK 内，调用者无需设置视频源，如果要自定义视频流，请使用 RCRTCVideoOutputStream
 
 @remarks 资源管理
 */
- (void)setVideoSource:(id<RCRTCVideoSourceInterface>)videoSource NS_UNAVAILABLE;

/*!
 设置视频流的渲染视图
 
 @param view 渲染视图
 @discussion
 设置本地摄像头采集的视频流渲染视图
 
 @remarks 视频配置
 */
- (void)setVideoView:(nullable id<RCRTCDrawer>)view;

/*!
 设置视频数的渲染纹理视图
 
 @param view 渲染纹理视图
 @discussion
 设置本地摄像头采集的视频流渲染纹理视图
 
 @remarks 视频配置
 */
- (void)setVideoTextureView:(nullable RCRTCVideoTextureView *)view;

/*!
 开启摄像头数据采集
 
 @discussion
 开启摄像头采集数据
 
 @remarks 资源管理
 */
- (void)startCapture;

/*!
 停止摄像头数据采集
 
 @discussion
 关闭摄像头采集数据
 
 @remarks 资源管理
 */
- (void)stopCapture;

/*!
 切换前后摄像头
 
 @discussion
 切换前后摄像头
 
 @remarks 视频配置
 */
- (void)switchCamera;

/*!
 摄像头是否支持区域对焦
 
 @discussion
 摄像头是否支持手动对焦功能
 
 @remarks 摄像头配置
 */
- (BOOL)isCameraFocusSupported;

/*!
 设置预览视图中的对焦点
 
 @param point 对焦点，(x，y)是在预览视图中归一化的坐标，即对焦点相对预览视图的位置与预览视图宽高的比值，取值范围为[0, 1]，左上角是(0, 0)

 @discussion
 改变对焦位置
 
 @remarks 摄像头配置
 */
- (BOOL)setCameraFocusPositionInPreview:(CGPoint)point;

/*!
 摄像头是否支持区域测光
 
 @discussion
 摄像头是否支持手动曝光功能
 
 @remarks 摄像头配置
 */
- (BOOL)isCameraExposurePositionSupported;

/*!
 设置预览视图中的曝光点
 
 @param point 曝光点，(x，y)是在预览视图中归一化的坐标，即曝光点相对预览视图的位置与预览视图宽高的比值，取值范围为[0, 1]，左上角是(0, 0)

 @discussion
 改变对焦位置
 
 @remarks 摄像头配置
 */
- (BOOL)setCameraExposurePositionInPreview:(CGPoint)point;

/*!
 摄像头是否支持闪光灯
 
 @discussion
 摄像头是否支持闪光灯
 
 @remarks 摄像头配置
 */
- (BOOL)isCameraTorchSupported;

/*!
 设置是否打开摄像头闪光灯
 
 @param enable YES 为打开，NO 为关闭摄像头闪光灯
 @discussion
 设置是否打开摄像头闪光灯
 
 @remarks 摄像头配置
 */
- (BOOL)enableCameraTorch:(BOOL)enable;

/*!
 摄像头是否支持缩放
 
 @discussion
 摄像头是否支持缩放
 
 @remarks 摄像头配置
 */
- (BOOL)isCameraZoomSupported;

/*!
 设置摄像头缩放比例
 
 @param zoomFactor 摄像头缩放比例，有效范围从 1.0 到最大缩放
 @discussion
 设置摄像头缩放比例
 
 @remarks 摄像头配置
 */
- (BOOL)setCameraZoomFactor:(float)zoomFactor;

/*!
 获取摄像头最大缩放比例
 
 @discussion
 获取摄像头最大缩放比例
 
 @remarks 摄像头配置
 */
- (float)getCameraMaxZoomFactor;

/*!
 设置小流视频配置
 
 @param config 视频配置
 @discussion
 设置小流视频配置
 
 @remarks 视频配置
 */
- (BOOL)setTinyVideoConfig:(RCRTCVideoStreamConfig *)config;

/*!
 获取小流视频配置
 
 @discussion
 获取小流视频配置
 
 @remarks 视频配置
 */
- (nullable RCRTCVideoStreamConfig *)getTinyVideoConfig;

@end

NS_ASSUME_NONNULL_END
