//
//  RCRTCVideoFrame.h
//  RongRTCLib
//
//  Created by RongCloud on 2021/11/22.
//  Copyright © 2021 RongCloud. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import "RCRTCLibDefine.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 视频帧数据
 */
@interface RCRTCVideoFrame : NSObject

/*!
 视频帧格式
 */
@property (nonatomic, readonly) RCRTCVideoFrameFormat format;

/*!
 视频宽度，单位为像素
 */
@property (nonatomic, readonly) NSInteger width;

/*!
 视频高度，单位为像素
 */
@property (nonatomic, readonly) NSInteger height;

/*!
 储存视频 buffer 对象
 */
@property (nonatomic, readonly, nullable) CVPixelBufferRef pixelBuffer;

/*!
 视频原始数据
 */
@property (nonatomic, readonly, nullable) NSData *data;

/*!
 旋转角度，0,90,180,270 顺时针
 */
@property (nonatomic, readonly) int rotation;

/*!
 显示时间戳，单位为纳秒
 */
@property (nonatomic, readonly) int64_t timeStampNs;

/*!
 初始化视频帧数据
     
 @param pixelBuffer  储存视频 buffer 对象, 只支持 NV12(420f) 或者 BGRA 格式视频
 @param timeStampNs  显示时间戳，单位为纳秒
 @param rotation 旋转角度，0,90,180,270
 
 @return 视频帧数据
 @discussion SDK 内部会持有 pixelBuffer，所以使用者生成的 pixelBuffer 需要 CVBufferRelease()
 */
- (nullable instancetype)initWithPixelBuffer:(CVPixelBufferRef)pixelBuffer
                        timeStampNs:(int64_t)timeStampNs
                           rotation:(int)rotation;

/*!
 初始化视频帧数据
     
 @param sampleBuffer  储存视频 buffer 对象, 只支持 NV12(420f) 或者 BGRA 格式视频
 @param rotation 旋转角度，0,90,180,270
 
 @return 视频帧数据
 @discussion SDK 内部会持有 sampleBuffer，所以使用者生成的 sampleBuffer 需要 CFRelease()
 */
- (nullable instancetype)initWithSampleBuffer:(CMSampleBufferRef)sampleBuffer
                            rotation:(int)rotation;

/*!
 转码视频数据
     
 @param pixelBuffer 转码后保存视频数据的buffer
 
 @discussion
 注意：
 1.需要确保传入 CVPixelBufferRef 的宽高和 RCRTCVideoFrame 的宽高一致，否则会放弃转码。
 2.请传入一个 NV12 或者 BGRA 格式的 CVPixelBufferRef, 否则会放弃转码。
 
 added from 5.1.15
 */
- (void)convertToPixelBuffer:(CVPixelBufferRef)pixelBuffer;

@end

NS_ASSUME_NONNULL_END
