//
//  RCRTCAudioMixer.h
//  RTCLib
//
//  Created by RongCloud on 2019/5/7.
//  Copyright © 2019 RongCloud. All rights reserved.
//

#import <CoreAudio/CoreAudioTypes.h>
#import <Foundation/Foundation.h>
#import "RCRTCGlobals.h"

/*!
 无限期循环
 */
RONGRTCLIB_EXTERN const UInt32 RCRTCLoopsIndefinitely;

/*!
 混音引擎状态
 deprecated from 5.1.3
 */
typedef NS_ENUM(NSUInteger, RTCMixEngineStatus) {
    /*!
     正常
     */
    RTCMixEngineStatusNormal,
    /*!
     准备中
     */
    RTCMixEngineStatusPrepare,
    /*!
     播放中（或混音中）
     */
    RTCMixEngineStatusPlaying,
    /*!
     暂停中
     */
    RTCMixEngineStatusPause,
    /*!
     停止
     */
    RTCMixEngineStatusStop
};

/*!
 播放（或混音）状态
 added from 5.1.3
 */
typedef NS_ENUM(NSUInteger, RCRTCAudioMixingState) {
    /*!
     播放中（或混音中）
     */
    RCRTCMixingStatePlaying,
    /*!
     暂停中
     */
    RCRTCMixingStatePause,
    /*!
     停止
     */
    RCRTCMixingStateStop,
    /*!
     播放失败
     */
    RCRTCMixingStateFailed
};

/*!
 播放（或混音）状态改变的原因
 added from 5.1.3
 */
typedef NS_ENUM(NSUInteger, RCRTCAudioMixingReason) {
    /*!
     成功调用 startMixingWithURL:playback:mixerMode:loopCount:;
     */
    RCRTCMixingReasonStartedByUser,
    /*!
     混音文件加载完成
     */
    RCRTCMixingReasonFileLoaded,
    /*!
     混音文件完成一次循环播放（或混音）
     */
    RCRTCMixingReasonOneLoopCompleted,
    /*!
     混音文件开始新的一次循环播放（或混音）
     */
    RCRTCMixingReasonStartNewLoop,
    /*!
     混音文件完成所有循环播放（或混音）
     */
    RCRTCMixingReasonAllLoopsCompleted,
    /*!
     成功调用 stop 停止播放（或混音）
     */
    RCRTCMixingReasonStoppedByUser,
    /*!
     成功调用 pause 停止播放（或混音）
     */
    RCRTCMixingReasonPausedByUser,
    /*!
     成功调用 resume 停止播放（或混音）
     */
    RCRTCMixingReasonResumedByUser,
    /*!
     混音文件加载失败（文件不存在或者文件格式不支持等原因导致加载失败）
     */
    RCRTCMixingReasonCanNotOpen,
};

/*!
 混音模式
 */
typedef NS_ENUM(NSInteger, RCRTCMixerMode) {
    /*!
     对端只能听见麦克风采集的声音
     */
    RCRTCMixerModeNone,
    /*!
     对端能够听到麦克风采集的声音和音频文件的声音
     */
    RCRTCMixerModeMixing,
    /*!
     对端只能听到音频文件的声音
     */
    RCRTCMixerModeReplace
};

/**
 本地音频左右声道混音
 @discussion Add from 5.1.13
 */
typedef NS_ENUM(NSInteger, RCRTCAudioDualMonoMode) {
    /*!
     当前音频立体声混音
     */
    RCRTCAudioDualMonoStereo = 0,
    /*!
     当前音频左声道混音
     */
    RCRTCAudioDualMonoLeft   = 1,
    /*!
     当前音频右声道混音
     */
    RCRTCAudioDualMonoRight  = 2
};

NS_ASSUME_NONNULL_BEGIN

/*!
 AudioMixer 的播放代理
 */
@protocol RCRTCAudioMixerAudioPlayDelegate <NSObject>

/*!
 当前播放进度

 @param progress 播放进度 range [0,1]
 @discussion
 当前播放进度

 @remarks 代理
 */
- (void)didReportPlayingProgress:(float)progress;

/*!
 混音状态

 @param mixingState 混音状态
 @param mixingReason 混音状态改变的原因
 @discussion
 当前混音状态
 Add from 5.1.3
 
 @remarks 代理
 */
- (void)didAudioMixingStateChanged:(RCRTCAudioMixingState)mixingState reason:(RCRTCAudioMixingReason)mixingReason;

@optional
/*!
 播放结束，如果循环播放多次，多次循环后调用

 @discussion
 播放结束，如果循环播放多次，多次循环后调用
 @deprecated from 5.1.3
 
 @remarks 代理
 */
- (void)didPlayToEnd DEPRECATED_MSG_ATTRIBUTE("use didAudioMixingStateChanged:reason: instead");

@end

/*!
 混音引擎
 */
@interface RCRTCAudioMixer : NSObject

/*!
 获取混音引擎单例
 */
+ (RCRTCAudioMixer *)sharedInstance;

/*!
 AudioMixer 的代理
 */
@property (nonatomic, weak, nullable) id<RCRTCAudioMixerAudioPlayDelegate> delegate;

/*!
 音频文件混音时的输入音量, 取值范围 [0,100], 默认值 100
 */
@property (nonatomic, assign) NSUInteger mixingVolume;

/*!
 音频文件本地播放音量, 取值范围 [0,100], 默认值 100
 */
@property (nonatomic, assign) NSUInteger playingVolume;

/*!
 混音文件的播放音调相对原始音调的偏移值，取值范围 [-12,12]，默认值 0，其中 0 表示原始音调，1 表示升高一个半音，-1 降低一个半音，以此类推。
 暂不支持处理在线音频
 */
@property (nonatomic, assign) double pitch;

/*!
 混音文件的播放速度，取值范围 [50,400]，默认值 100，其中 100 表示原始速度，50 表示 0.5 倍速，400 表示 4 倍速，以此类推。
 暂不支持处理在线音频
 */
@property (nonatomic, assign) double playbackSpeed;

/*!
 当前混音状态
 */
@property (nonatomic, assign, readonly)
    RTCMixEngineStatus status DEPRECATED_MSG_ATTRIBUTE("use didAudioMixingStateChanged:reason: instead");

/*!
 方法 writeAudioBufferList:frames:sampleTime:playback:  写入 AudioBufferList 的格式
 */
@property (nonatomic, readonly, class) AudioStreamBasicDescription writeAsbd;

/*!
 当前混音文件时长
 */
@property (nonatomic, assign, readonly) NSTimeInterval duration;

/*!
 获取指定音频文件的时长

 @param url  音频文件的 File URL
 @discussion
 获取指定音频文件的时长，只支持本地音频文件

 @remarks 音频配置
 @return 音频文件的时长
 */
+ (Float64)durationOfAudioFile:(NSURL *)url;

/*!
 设置播放进度
 @param progress 设置播放进度 取值范围 [0,1]
 @discussion
 设置播放进度

 @remarks 音频配置
 */
- (void)setPlayProgress:(float)progress;

/*!
 设置混音文件的播放音调
 @param pitch 相对原始音调的偏移值，默认值为 0，取值范围 [-12,12]，其中 0 表示原始音调，1 表示升高一个半音，-1 降低一个半音，以此类推。
 @discussion
 设置混音文件的播放音调，暂不支持处理在线音频
 Added from 5.2.0

 @remarks 音频配置
 */
- (void)setPitch:(double)pitch;

/*!
 设置混音文件的播放速度
 @param playbackSpeed 播放速度，默认值为 100，取值范围 [50,400]，其中 100 表示原始速度，50 表示 0.5 倍速，400 表示 4 倍速，以此类推。
 @discussion
 设置混音文件的播放速度，暂不支持处理在线音频
 Added from 5.2.0

 @remarks 音频配置
 */
- (void)setPlaybackSpeed:(double)playbackSpeed;

/*!
 开始混音, 开始新混音之前需要先调用 stop 结束混音, 重复调用会忽略操作
 @param fileURL  资源 URL 
 @param isPlay   是否播放
 @param mode 混音行为模式
 @param count 循环混音或者播放次数

 @discussion
 混音功能

 @remarks 音频配置
 @return 开始是否成功
 */
- (BOOL)startMixingWithURL:(NSURL *)fileURL
                  playback:(BOOL)isPlay
                 mixerMode:(RCRTCMixerMode)mode
                 loopCount:(NSUInteger)count;

/*!
 设置混音声道模式
 @param mode 声道模式 0 立体声混音, 1 左声道混音, 2 右声道混音
 @discussion
 只针对本地文件资源产生效果, 不支持网络资源的 url
 Add from 5.1.13

 @remarks 音频配置
 @return  设置是否成功
 */
- (BOOL)setAudioDualMonoMode:(RCRTCAudioDualMonoMode)mode;

/*!
 写入自定义音频数据
 @param abl 音频数据，格式为 PCM
 @param frames 音频帧个数
 @param sampleTime 音频帧时间戳
 @param isPlay 是否在本地播放

 @discussion
 写入自定义音频数据

 @remarks 音频流处理
 */
- (void)writeAudioBufferList:(const AudioBufferList *)abl
                      frames:(UInt32)frames
                  sampleTime:(SInt64)sampleTime
                    playback:(BOOL)isPlay;

/*!
 写入自定义音频数据
 @param abl 音频数据，格式为 PCM
 @param frames 音频帧个数
 @param sampleTime 音频帧时间戳
 @param asbd 音频格式描述
 @param isPlay 是否在本地播放

 @discussion
 写入自定义音频数据

 @remarks 音频流处理
 */
- (void)writeAudioBufferList:(const AudioBufferList *)abl
                      frames:(UInt32)frames
                  sampleTime:(SInt64)sampleTime
                        asbd:(AudioStreamBasicDescription)asbd
                    playback:(BOOL)isPlay;

/*!
 暂停

 @remarks 音频配置
 @return 暂停是否成功
 */
- (BOOL)pause;

/*!
 恢复

 @remarks 音频配置
 @return 恢复是否成功
 */
- (BOOL)resume;

/*!
 结束

 @remarks 音频配置
 @return 结束是否成功
 */
- (BOOL)stop;

@end

NS_ASSUME_NONNULL_END
