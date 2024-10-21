//
//  RCRTCFileVideoOutputStream.h
//  RongRTCLib
//
//  Created by RongCloud on 2021/8/30.
//  Copyright © 2021 RongCloud. All rights reserved.
//

#import <RongRTCLib/RongRTCLib.h>

NS_ASSUME_NONNULL_BEGIN

@protocol RCRTCFileVideoOutputStreamDelegate;

/*!
 自定义文件流
 
 @discussion Added from 5.1.9
 */
@interface RCRTCFileVideoOutputStream : RCRTCVideoOutputStream
/*!
 文件路径
 */
@property (nonatomic, readonly, nullable) NSString *filePath;

/*!
 文件中音频是否替换麦克风数据，YES 替换麦克风数据，NO 与麦克风数据混音
 */
@property (nonatomic, readonly) BOOL replace;

/*!
 文件中的音频是否在本端播放
 */
@property (nonatomic, readonly) BOOL playback;

/*!
 文件视频流代理
 */
@property (nonatomic, weak, nullable) id<RCRTCFileVideoOutputStreamDelegate> delegate;

/*!
 音频数据回调
 */
@property (nonatomic, copy, nullable) RCRTCAudioFrameCallback audioDataCallback;

/*!
 停止
 
 @return 是否调用成功
 
 @discussion 调用此方法会停止解码文件视频流并释放文件资源
 */
- (BOOL)stop;

/*!
 初始化

 @return 失败
 
 @warning
 请勿调用，仅供 SDK 内部调用，如要获取实例对象，请使用 [RCRTCEngine sharedInstance] 的
 createFileVideoOutputStream:replaceAudio:playback:tag:config: 方法获取实例。
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
 初始化

 @return 失败
 
 @warning
 请勿调用，仅供 SDK 内部调用，如要获取实例对象，请使用 [RCRTCEngine sharedInstance] 的
 createFileVideoOutputStream:replaceAudio:playback:tag:config: 方法获取实例。
 */
- (instancetype)new NS_UNAVAILABLE;

/*!
 初始化
 
 @return 失败
 
 @warning
 请勿调用，仅供 SDK 内部调用，如要获取实例对象，请使用 [RCRTCEngine sharedInstance] 的
 createFileVideoOutputStream:replaceAudio:playback:tag:config: 方法获取实例。
 */
- (instancetype)initVideoOutputStreamWithTag:(NSString *)tag NS_UNAVAILABLE;

@end

@protocol RCRTCFileVideoOutputStreamDelegate <NSObject>

/*!
 开始解码文件视频流
 */
- (void)fileVideoOutputStreamDidStartRead:(RCRTCFileVideoOutputStream *)stream;

/*!
 完成解码文件视频流
 */
- (void)fileVideoOutputStreamDidReadCompleted:(RCRTCFileVideoOutputStream *)stream;

/*!
 解码文件视频流失败
 */
- (void)fileVideoOutputStreamDidFailed:(RCRTCFileVideoOutputStream *)stream;

@end

NS_ASSUME_NONNULL_END
