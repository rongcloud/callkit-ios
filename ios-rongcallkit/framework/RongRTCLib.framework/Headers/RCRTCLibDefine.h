//
//  RCRTCLibDefine.h
//  RongRTCLib
//
//  Created by RongCloud on 2019/1/3.
//  Copyright © 2019 RongCloud. All rights reserved.
//

#ifndef RCRTCLibDefine_h
#define RCRTCLibDefine_h

#import <AVFoundation/AVFoundation.h>
#import <Foundation/Foundation.h>
#import "RCRTCCodeDefine.h"

@class RongRTCMember;
@class RCRTCRoom;
@class RCRTCStream;
@class RCRTCLiveInfo;
@class RCRTCInputStream;
@class RCRTCVideoFrame;

/*!
 某些操作的回调
 
 @param isSuccess 操作是否成功
 @param code 成功或者失败描述的错误码
 @discussion
 某些操作的回调
 
 @remarks 资源管理
 */
typedef void (^RCRTCOperationCallback)(BOOL isSuccess, RCRTCCode code);

/*!
 直播操作的回调
 
 @param isSuccess 操作是否成功
 @param code 成功或者失败描述的错误码
 @param liveInfo 当前直播主持人的数据模型
 @discussion
 直播操作的回调
 
 @remarks 资源管理
 */
typedef void (^RCRTCLiveOperationCallback)(BOOL isSuccess, RCRTCCode code, RCRTCLiveInfo *_Nullable liveInfo);

/*!
 观众观看直播的回调
 
 @param code 成功或者失败描述的错误码
 @param inputStream 当前直播流
 @discussion
 观众观看直播的回调
 
 @remarks 资源管理
 */
typedef void (^RCRTCLiveCallback)(RCRTCCode code, RCRTCInputStream *_Nullable inputStream);

/*!
 观众观看直播的回调
 
 @param code 成功或者失败描述的错误码
 @param inputStreams 当前直播流
 @discussion
 观众观看直播的回调
 
 @remarks 资源管理
 */
typedef void (^RCRTCLiveUrlCallback)(RCRTCCode code, NSArray<RCRTCInputStream *> *_Nullable inputStreams);

/*!
 获取用户属性操作回调
 
 @param isSuccess 操作是否成功
 @param code 成功或者失败的描述 错误码
 @param attr 获取结果
 @discussion
 获取用户属性操作回调
 
 @remarks 资源管理
 */
typedef void (^RCRTCAttributeOperationCallback)(BOOL isSuccess, RCRTCCode code, NSDictionary *_Nullable attr);

/*!
 订阅操作的回调
 
 @param isSuccess 操作是否成功
 @param code 成功或者失败描述的错误码
 @param subscribeErrorList 服务器返回的订阅失败列表
 @discussion
 订阅操作的回调
 
 @remarks 资源管理
 */
typedef void (^RCRTCSubscribeOperationCallback)(BOOL isSuccess, RCRTCCode code, NSArray<RCRTCInputStream *> *_Nullable subscribeErrorList);

/*!
 当前流状态
 */
typedef NS_ENUM(NSUInteger, RCRTCResourceState) {
    /*!
     流处于禁用状态
     */
    ResourceStateDisabled = 0,
    /*!
     流处于正常状态
     */
    ResourceStateNormal
};

/*!
 资源类型
 deprecated from 5.1.8
 */
typedef NS_ENUM(NSUInteger, RTCMediaType) {
    /*!
     只有声音
     */
    RTCMediaTypeAudio,
    /*!
     声音视频
     */
    RTCMediaTypeVideo,
    /*!
     数据（暂不支持）
     */
    RTCMediaTypeData,
    /*!
     空数据
     */
    RTCMediaTypeNothing
};

/*!
 媒体类型
 added from 5.1.8
 */
typedef NS_ENUM(NSUInteger, RCRTCMediaType) {
    /*!
     音频
     */
    RCRTCMediaTypeAudio,
    /*!
     音视频
     */
    RCRTCMediaTypeVideo,
    /*!
     数据（暂不支持）
     */
    RCRTCMediaTypeData,
    /*!
     空数据
     */
    RCRTCMediaTypeNothing
};

/*!
 媒体流类型
 added from 5.1.8
 */
typedef NS_ENUM(NSUInteger, RCRTCMediaStreamType) {
    /*!
     默认
     */
    RCRTCMediaStreamTypeDefault,
    /*!
     自定义
     */
    RCRTCMediaStreamTypeCustomized,
    /*!
     直播合流
     */
    RCRTCMediaStreamTypeMCULive,
    /*!
     CDN
     */
    RCRTCMediaStreamTypeCDN,
    /*!
     屏幕共享
     */
    RCRTCMediaStreamTypeScreenShare
};

/*!
 视频分辨率类型
 */
typedef NS_ENUM(NSInteger, RCRTCVideoSizePreset) {
    /*!
     无效参数
     */
    RCRTCVideoSizePresetInvalid = -1,
    /*!
     分辨率 176X144
     */
    RCRTCVideoSizePreset176x144,
    /*!
     分辨率 180X180
     */
    RCRTCVideoSizePreset180x180,
    /*!
     分辨率 256X144
     */
    RCRTCVideoSizePreset256x144,
    /*!
     分辨率 240X180
     */
    RCRTCVideoSizePreset240x180,
    /*!
     分辨率 320X180
     */
    RCRTCVideoSizePreset320x180,
    /*!
     分辨率 240X240
     */
    RCRTCVideoSizePreset240x240,
    /*!
     分辨率 320X240
     */
    RCRTCVideoSizePreset320x240,
    /*!
     分辨率 360X360
     */
    RCRTCVideoSizePreset360x360,
    /*!
     分辨率 480X360
     */
    RCRTCVideoSizePreset480x360,
    /*!
     分辨率 640X360
     */
    RCRTCVideoSizePreset640x360,
    /*!
     分辨率 480X480
     */
    RCRTCVideoSizePreset480x480,
    /*!
     分辨率 640X480
     */
    RCRTCVideoSizePreset640x480,
    /*!
     分辨率 720X480
     */
    RCRTCVideoSizePreset720x480,
    /*!
     分辨率 848X480
     */
    RCRTCVideoSizePreset848x480,
    /*!
     分辨率 960X720
     */
    RCRTCVideoSizePreset960x720,
    /*!
     分辨率 1280X720
     */
    RCRTCVideoSizePreset1280x720,
    /*!
     分辨率 1920X1080
     */
    RCRTCVideoSizePreset1920x1080
};

/*!
 视频方向
 */
typedef NS_ENUM(NSUInteger, RCRTCVideoOrientation) {
    /*!
     竖立, home 键在下部
     */
    RCRTCVideoOrientationPortrait = 1,
    /*!
     竖立, home 键在上部
     */
    RCRTCVideoOrientationPortraitUpsideDown,
    /*!
     横屏, home 键在左侧
     */
    RCRTCVideoOrientationLandscapeRight,
    /*!
     竖立, home 键在右侧
     */
    RCRTCVideoOrientationLandscapeLeft
};

/*!
 视频填充模式
 */
typedef NS_ENUM(NSInteger, RCRTCVideoFillMode) {
    /*!
     完整显示, 填充黑边
     等比例填充，直到一个维度到达区域边界
     */
    RCRTCVideoFillModeAspectFit,
    RCRTCVideoFillModeAspect
    __attribute__((deprecated("RCRTCVideoFillModeAspect即将废弃 请更换为RCRTCVideoFillModeAspectFit"))) =
        RCRTCVideoFillModeAspectFit,
    /*!
     满屏显示
     等比例填充，直到填充满整个视图区域，其中一个维度的部分区域会被裁剪
     */
    RCRTCVideoFillModeAspectFill,
    /*!
     非均匀模式。两个维度完全填充至整个视图区域
     */
    RCRTCVideoFillModeResize
};

/*!
 帧率
 */
typedef NS_ENUM(NSInteger, RCRTCVideoFPS) {
    /*!
     无效参数
     */
    RCRTCVideoFPSInvalid = -1,
    /*!
     每秒 10 帧
     */
    RCRTCVideoFPS10,
    /*!
     每秒 15 帧
     */
    RCRTCVideoFPS15,
    /*!
     每秒 24 帧
     */
    RCRTCVideoFPS24,
    /*!
     每秒 30 帧
     */
    RCRTCVideoFPS30
};

/*!
 视频编解码
 */
typedef NS_ENUM(NSUInteger, RCRTCCodecType) {
    /*!
     H264 编码
     */
    RCRTCCodecH264
};

/*!
 音频编解码
 */
typedef NS_ENUM(NSUInteger, RCRTCAudioCodecType) {
    /*!
     PCMU
     */
    RCRTCAudioCodecPCMU = 0,
    /*!
     OPUS
     */
    RCRTCAudioCodecOPUS = 111
};

/*!
 摄像头
 */
typedef NS_ENUM(NSUInteger, RCRTCDeviceCamera) {
    /*!
     未指明
     */
    RCRTCCaptureDeviceUnspecified = AVCaptureDevicePositionUnspecified,
    /*!
     后置摄像头
     */
    RCRTCCaptureDeviceBack = AVCaptureDevicePositionBack,
    /*!
     前置摄像头
     */
    RCRTCCaptureDeviceFront = AVCaptureDevicePositionFront
};

/*!
 设置加入房间时音视频使用模式
 */
typedef NS_ENUM(NSUInteger, RCRTCRoomType) {
    /*!
     普通音视频类型
     */
    RCRTCRoomTypeNormal = 0,
    /*!
     直播类型
     */
    RCRTCRoomTypeLive = 2,
    /*!
     跨应用多人房间
     */
    RCRTCRoomTypeCrossMuti = 7
};

/*!
 直播类型
 */
typedef NS_ENUM(NSUInteger, RCRTCLiveType) {
    /*!
     当前直播为音视频直播
     */
    RCRTCLiveTypeAudioVideo = 0,

    /*!
     当前直播为仅音频直播
     */
    RCRTCLiveTypeAudio = 1
};

/*!
 同一 UserID 多端加入房间处理类型
 */
typedef NS_ENUM(NSUInteger, RCRTCJoinRoomType) {
    /*!
     将之前加入房间的端踢出房间
     */
    RCRTCJoinRoomTypeKick = 0,
    /*!
     拒绝当前端加入房间
     */
    RCRTCJoinRoomTypeRefuse = 1
};

/*!
 直播类型下的角色区分
 */
typedef NS_ENUM(NSUInteger, RCRTCLiveRoleType) {
    /*!
     当前直播角色为主播
     */
    RCRTCLiveRoleTypeBroadcaster = 0,

    /*!
     当前直播角色为观众
     */
    RCRTCLiveRoleTypeAudience = 1
};

/*!
 观众订阅直播类型直播类型
 */
typedef NS_ENUM(NSUInteger, RCRTCAVStreamType) {
    /*!
     仅订阅音频
     */
    RCRTCAVStreamTypeAudio = 0,

    /*!
     仅订阅视频(大流)
     */
    RCRTCAVStreamTypeVideo = 1,

    /*!
    订阅音频+视频（大流）
    */
    RCRTCAVStreamTypeAudioVideo = 2,

    /*!
    仅订阅视频（小流）
    */
    RCRTCAVStreamTypeVideo_tiny = 3,

    /*!
    订阅音频+视频（小流）
    */
    RCRTCAVStreamTypeAudioVideo_tiny = 4
};

/*!
 设置音频通话质量, 默认为普通通话模式 RCRTCAudioQualitySpeech
 */
typedef NS_ENUM(NSUInteger, RCRTCAudioQuality) {
    /*!
     人声音质，编码码率最大值为32Kbps
     */
    RCRTCAudioQualitySpeech,
    /*!
     标清音乐音质，编码码率最大值为64Kbps
     */
    RCRTCAudioQualityMusic,
    /*!
     高清音乐音质，编码码率最大值为128Kbps
     */
    RCRTCAudioQualityMusicHigh,
};

/*!
 设置音频通话模式, 默认为普通通话模式 RCRTCAudioScenarioDefault
 */
typedef NS_ENUM(NSUInteger, RCRTCAudioScenario) {
    /*!
     普通通话模式(普通音质模式), 满足正常音视频场景
     */
    RCRTCAudioScenarioDefault,
    /*!
     音乐聊天室模式, 提升声音质量, 适用对音乐演唱要求较高的场景
     */
    RCRTCAudioScenarioMusicChatRoom,
    /*!
     音乐教室模式, 提升声音质量, 适用对乐器演奏音质要求较高的场景
     */
    RCRTCAudioScenarioMusicClassRoom
};

/*!
 被踢原因
 */
typedef NS_ENUM(NSInteger, RCRTCKickedReason) {
    /*!
     被服务端踢下线
     */
    RCRTCKickedReasonForServer = 1,
    /*!
     被同一UserId加入其他房间踢出当前房间
     */
    RCRTCKickedReasonForOtherJoinedRoom,
    /*!
     关闭 SDK 断线重连，SDK 将用户踢出房间
     */
    RCRTCKickedReasonForSDKDisconnect,
    /*!
     IMLib 退出登录，SDK 将用户踢出房间
     */
    RCRTCKickedReasonForIMLogout,
    /*!
     被其它端登录挤下线
     */
    RCRTCKickedReasonForOtherClientLogin,
    /*!
     服务器销毁房间，被迫离开房间
     */
    RCRTCKickedReasonForSeverDestory
};

/*!
 RTC连接状态
 */
typedef NS_ENUM(NSInteger, RCRTCConnectionState) {
    /*!
     连接中
     */
    RCRTCConnectionStateConnecting,
    /*!
     已连接
     */
    RCRTCConnectionStateConnected
};

/*!
 代理协议类型
 */
typedef NS_OPTIONS(NSUInteger, RCRTCProxyOptions) {
    RCRTCProxyOptionsNone = 0,
    RCRTCProxyOptionsHTTP = 1 << 0,
    RCRTCProxyOptionsUDP = 1 << 1,
    RCRTCProxyOptionsAll = RCRTCProxyOptionsHTTP | RCRTCProxyOptionsUDP
};

/*!
 视频帧格式
 */
typedef NS_ENUM(NSInteger, RCRTCVideoFrameFormat) {
    /*!
     NV12
     */
    RCRTCVideoFrameFormatNV12,
    /*!
     BGRA
     */
    RCRTCVideoFrameFormatBGRA,
    /*!
     I420
     */
    RCRTCVideoFrameFormatI420
};

/*!
 音频路由类型
 */
typedef NS_ENUM(NSInteger, RCRTCAudioRouteType) {
    /*!
     扬声器
     */
    RCRTCAudioRouteTypeSpeaker,
    /*!
     听筒
     */
    RCRTCAudioRouteTypeReceiver,
    /*!
     耳机
     */
    RCRTCAudioRouteTypeHeadphone,
    /*!
     蓝牙设备
     */
    RCRTCAudioRouteTypeBluetooth
};

NS_ASSUME_NONNULL_BEGIN

/*!
 原始音频数据
 */
@interface RCRTCAudioFrame : NSObject

/*!
 音频数据
 */
@property (assign, nonatomic) uint8_t * bytes;
/*!
 音频数据长度（字节数）
 */
@property (assign, nonatomic) int32_t length;
/*!
 声道数
 */
@property (assign, nonatomic) int32_t channels;
/*!
 采样率
 */
@property (assign, nonatomic) int32_t sampleRate;
/*!
 位深
 */
@property (assign, nonatomic) int32_t bytesPerSample;
/*!
 帧数
 */
@property (assign, nonatomic) int32_t samples;
/*!
 时间戳
 */
@property (assign, nonatomic) uint64_t renderTimeMs;

@end

NS_ASSUME_NONNULL_END

/*!
 视频帧回调
 
 @param valid 该视频帧是否有效
 @param videoFrame 视频帧内容
 @discussion
 视频帧回调
 
 @remarks 视频流处理
 @return 用户自定义视频帧
 */
typedef RCRTCVideoFrame *_Nullable (^RCRTCVideoFrameCallback)(BOOL valid, RCRTCVideoFrame *_Nullable videoFrame);

/*!
 视频帧回调
 
 @param valid 该视频帧是否有效
 @param sampleBuffer 视频帧内容
 @discussion
 视频帧回调
 
 @remarks 视频流处理
 @return 用户自定义视频帧
 */
typedef CMSampleBufferRef _Nullable (^RCRTCVideoCMSampleBufferCallback)(BOOL valid,
                                                                        CMSampleBufferRef _Nullable sampleBuffer);

/*!
 音频输入输出的回调
 
 @param inNumberFrames 帧个数
 @param ioData 音频 pcm 数据
 @param inTimeStamp 音频时间戳
 @param asbd 音频数据格式
 @discussion
 音频输入输出的回调
 
 @remarks 音频流处理
 */
typedef void (^RCRTCAudioDataCallback)(UInt32 inNumberFrames,
                                       AudioBufferList *_Nonnull ioData,
                                       const AudioTimeStamp *_Nonnull inTimeStamp,
                                       const AudioStreamBasicDescription asbd);

/*!
 音频数据的回调
 
 @param frame 音频数据
 @discussion
 音频输入输出的回调
 
 @remarks 音频流处理
 */
typedef void (^RCRTCAudioFrameCallback)(RCRTCAudioFrame *_Nonnull frame);

#endif /* RCRTCLibDefine_h */
