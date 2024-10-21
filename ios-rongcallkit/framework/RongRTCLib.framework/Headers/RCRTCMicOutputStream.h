//
//  RCRTCMicOutputStream.h
//  RongRTCLib
//
//  Created by RongCloud on 2020/4/16.
//  Copyright © 2020年 RongCloud. All rights reserved.
//

#import "RCRTCAudioMixer.h"
#import "RCRTCAudioOutputStream.h"
#import "RCRTCLibDefine.h"
#import "RCRTCOutputStream.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 麦克风输出流，以麦克风为音频源的音频输出流
 */
@interface RCRTCMicOutputStream : RCRTCAudioOutputStream

/*!
 麦克风的音量，范围:0~200，默认值:100
 */
@property (nonatomic, assign) NSUInteger recordingVolume;

/*!
 音频码率
*/
@property (nonatomic, assign, readwrite) NSInteger bitrateValue;

/*!
 音频编解码方式
 默认: OPUS
 */
@property (nonatomic, assign, readwrite) RCRTCAudioCodecType audioCodecType;

/*!
 音频通话质量
 默认: 人声音质，RCRTCAudioQualitySpeech
 */
@property (nonatomic, assign, readonly) RCRTCAudioQuality audioQuality;

/*!
 音频通话模式
 默认: 普通通话模式，RCRTCAudioScenarioDefault
 */
@property (nonatomic, assign, readonly) RCRTCAudioScenario audioScenario;

/*!
 本地发送的音频数据（合流）回调
 */
@property (nonatomic, copy, nullable) RCRTCAudioDataCallback willSendAudioBufferCallback;

/*!
 麦克风的音频数据回调
 added from 5.1.6
 */
@property (nonatomic, copy, nullable) RCRTCAudioFrameCallback recordAudioDataCallback;

/*!
 初始化

 @discussion
 初始化

 @warning
 请勿调用, 仅供 SDK 内部调用，如要获取实例对象，请使用 [RCRTCEngine sharedInstance].defaultAudioStream 获取实例。

 @remarks 资源管理
 @return 失败
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
 初始化

 @discussion
 初始化

 @warning
 请勿调用, 仅供 SDK 内部调用，如要获取实例对象，请使用 [RCRTCEngine sharedInstance].defaultAudioStream 获取实例。

 @remarks 资源管理
 @return 失败
 */
- (instancetype)new NS_UNAVAILABLE;

/*!
 关闭/打开麦克风

 @param disable YES 关闭，NO 打开
 @discussion
 关闭/打开麦克风

 @remarks 音频配置
 */
- (void)setMicrophoneDisable:(BOOL)disable;

/*!
 设置音频通话质量和音频通话模式

 @param audioQuality 音频通话质量, audioScenario 音频通话模式
 @discussion
 设置音频通话质量和音频通话模式

 @remarks 音频流处理
 @return 设置是否成功
 */
- (BOOL)setAudioQuality:(RCRTCAudioQuality)audioQuality Scenario:(RCRTCAudioScenario)audioScenario;

@end

NS_ASSUME_NONNULL_END
