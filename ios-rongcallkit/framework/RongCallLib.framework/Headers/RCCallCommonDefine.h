//
//  RCCallCommonDefine.h
//  RongCallLib
//
//  Created by RongCloud on 16/2/28.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#ifndef RCCallCommonDefine_h
#define RCCallCommonDefine_h

/*!
 引擎类型
 */
typedef NS_ENUM(NSInteger, RCCallEngineType) {
    /*!
     无
     */
    RCCallEngineNone = 0,
    /*!
     声网
     */
    RCCallEngineAgora = 1,
    /*!
     融云
     */
    RCCallEngineRong = 2,
    /*!
     Blink
     */
    RCCallEngineBlink = 3,
    /*!
     RTC3.0
     */
    RCCallEngineRongRTC = 4
};

/*!
 媒体类型
 */
typedef NS_ENUM(NSInteger, RCCallMediaType) {
    /*!
     音频
     */
    RCCallMediaAudio = 1,
    /*!
     视频
     */
    RCCallMediaVideo = 2
};

/*!
 通话质量
 */
typedef NS_ENUM(NSUInteger, RCCallQuality) {
    /*!
     未知
     */
    RCCall_Quality_Unknown = 0,
    /*!
     Excellent
     */
    RCCall_Quality_Excellent = 1,
    /*!
     Good
     */
    RCCall_Quality_Good = 2,
    /*!
     Poor
     */
    RCCall_Quality_Poor = 3,
    /*!
     Bad
     */
    RCCall_Quality_Bad = 4,
    /*!
     VBad
     */
    RCCall_Quality_VBad = 5,
    /*!
     Down
     */
    RCCall_Quality_Down = 6
};

/**
 视频显示模式
 */
typedef NS_ENUM(NSInteger, RCCallRenderModel) {
    /*!
     默认: 如果视频尺寸与显示视窗尺寸不一致，则视频流会按照显示视窗的比例进行周边裁剪或图像拉伸后填满视窗。
     */
    RCCallRenderModelHidden = 1,
    
    /*!
     RenderFit: 如果视频尺寸与显示视窗尺寸不一致，在保持长宽比的前提下，将视频进行缩放后填满视窗。
     */
    RCCallRenderModelFit = 2,
    
    /*!
     RenderAdaptive: 如果自己和对方都是竖屏，或者如果自己和对方都是横屏，使用
     RCCallRenderModelHidden；如果对方和自己一个竖屏一个横屏，则使用RCCallRenderModelFit。
     */
    RCCallRenderModelAdaptive = 3
};

#pragma mark - Call

/*!
 错误码
 */
typedef NS_ENUM(NSInteger, RCCallErrorCode) {
    /*!
     成功
     */
    RCCallSuccess = 0,
    /*!
     网络不可用
     */
    RCCallNetworkUnavailable = 1,
    /*!
     已经处于通话中了
     */
    RCCallOneCallExisted = 2,
    /*!
     无效操作
     */
    RCCallOperationUnavailable = 3,
    /*!
     参数错误
     */
    RCCallInvalidParam = 4,
    /*!
     网络不稳定
     */
    RCCallNetworkUnstable = 5,
    /*!
     媒体服务请求失败
     */
    RCCallMediaRequestFailed = 6,
    /*!
     媒体服务初始化失败
     */
    RCCallMediaServerNotReady = 7,
    /*!
     媒体服务未初始化
     */
    RCCallMediaServerNotInitialized = 8,
    /*!
     媒体服务请求超时
     */
    RCCallMediaRequestTimeout = 9,
    /*!
     未知的媒体服务错误
     */
    RCCallMediaUnkownError = 10,
    /*!
     已被禁止通话
     */
    RCCallMediaKickedByServerError = 11,
    /*!
     音视频服务已关闭
     */
    RCCallMediaServerClosedError = 12,
    /*!
     音视频发布资源失败
     */
    RCCallMediaServerPublishError = 13,
    /*!
     音视频订阅资源失败
     */
    RCCallMediaServerSubscribeError = 14,
    /*!
     其他端已在通话中
     */
    RCCallMediaJoinRoomRefuseError = 15,
    /*!
     己方其他端已加入其他房间
     */
    RCCallMediaOtherClientJoinedRoom = 16
};

/*!
 通话结束原因
 */
typedef NS_ENUM(NSInteger, RCCallDisconnectReason) {
    /*!
     己方取消已发出的通话请求
     */
    RCCallDisconnectReasonCancel = 1,
    /*!
     己方拒绝收到的通话请求
     */
    RCCallDisconnectReasonReject = 2,
    /*!
     己方挂断
     */
    RCCallDisconnectReasonHangup = 3,
    /*!
     己方忙碌
     */
    RCCallDisconnectReasonBusyLine = 4,
    /*!
     己方未接听
     */
    RCCallDisconnectReasonNoResponse = 5,
    /*!
     己方不支持当前引擎
     */
    RCCallDisconnectReasonEngineUnsupported = 6,
    /*!
     己方网络出错
     */
    RCCallDisconnectReasonNetworkError = 7,
    /*!
     己方获取媒体资源失败
     */
    RCCallDisconnectReasonResourceError = 8,
    /*!
     己方发布资源失败
     */
    RCCallDisconnectReasonPublishError = 9,
    /*!
     己方订阅资源失败
     */
    RCCallDisconnectReasonSubscribeError = 10,
    /*!
     对方取消已发出的通话请求
     */
    RCCallDisconnectReasonRemoteCancel = 11,
    /*!
     对方拒绝收到的通话请求
     */
    RCCallDisconnectReasonRemoteReject = 12,
    /*!
     通话过程对方挂断
     */
    RCCallDisconnectReasonRemoteHangup = 13,
    /*!
     对方忙碌
     */
    RCCallDisconnectReasonRemoteBusyLine = 14,
    /*!
     对方未接听
     */
    RCCallDisconnectReasonRemoteNoResponse = 15,
    /*!
     对方不支持当前引擎
     */
    RCCallDisconnectReasonRemoteEngineUnsupported = 16,
    /*!
     对方网络错误
     */
    RCCallDisconnectReasonRemoteNetworkError = 17,
    /*!
     对方获取媒体资源失败
     */
    RCCallDisconnectReasonRemoteResourceError = 18,
    /*!
     对方发布资源失败
     */
    RCCallDisconnectReasonRemotePublishError = 19,
    /*!
     对方订阅资源失败
     */
    RCCallDisconnectReasonRemoteSubscribeError = 20,
    /*!
     己方其他端已加入新通话
     */
    RCCallDisconnectReasonKickedByOtherCall = 21,
    /*!
     己方其他端已在通话中
     */
    RCCallDisconnectReasonInOtherCall = 22,
    /*!
     己方已被禁止通话
     */
    RCCallDisconnectReasonKickedByServer = 23,
    /*!
     己方已接听系统来电
     */
    RCCallDisconnectReasonAcceptSystemCall = 24,
    /*!
     对方其他端已加入新通话
     */
    RCCallDisconnectReasonRemoteKickedByOtherCall = 31,
    /*!
     对方其他端已在通话中
     */
    RCCallDisconnectReasonRemoteInOtherCall = 32,
    /*!
     对方已被禁止通话
     */
    RCCallDisconnectReasonRemoteKickedByServer = 33,
    /*!
     对方已接听系统来电
     */
    RCCallDisconnectReasonRemoteAcceptSystemCall = 34,
    /*!
     己方其他端已接听
     */
    RCCallDisconnectReasonAcceptByOtherClient = 101,
    /*!
     己方其他端已挂断
     */
    RCCallDisconnectReasonHangupByOtherClient = 102,
    /*!
     己方被对方加入黑名单
    */
    RCCallDisconnectReasonAddToBlackList = 103,
    /*!
     音视频服务已关闭
     */
    RCCallDisconnectReasonMediaServerClosed = 104,
    /*!
     己方被降级为观察者
     */
    RCCallDisconnectReasonDegrade = 301
};

/*!
 通话视频参数
 */
typedef NS_ENUM(NSInteger, RCVideoProfile) {
    /*!
     176x132, 10fps, 150kbps
     */
    RC_VIDEO_PROFILE_132P = 10,
    /*!
     256x144, 15fps, 350kbps
     */
    RC_VIDEO_PROFILE_144P_1 = 11,
    /*!
     240x240, 15fps, 400kbps
     */
    RC_VIDEO_PROFILE_240P = 20,
    /*!
     320x240, 15fps, 500kbps
     */
    RC_VIDEO_PROFILE_240P_1 = 21,
    /*!
     480x360, 15fps, 650kbps
     */
    RC_VIDEO_PROFILE_360P = 30,
    /*!
     640x360, 15fps, 800kbps
     */
    RC_VIDEO_PROFILE_360P_1 = 40,
    /*!
     640x480, 15fps, 1000kbps
     */
    RC_VIDEO_PROFILE_480P = 50,
    /*!
     720x480, 15fps, 1200kbps
     */
    RC_VIDEO_PROFILE_480P_1 = 60,
    /*!
     1280x720, 15fps, 2500kbps
     */
    RC_VIDEO_PROFILE_720P = 70,
    /*!
     默认的视频参数
     */
    RC_VIDEO_PROFILE_DEFAULT = RC_VIDEO_PROFILE_480P
};

/*!
 视频编码方式
 */
typedef NS_ENUM(NSInteger, RCVideoCodecType) {
    /*!
     H264
     */
    RC_VIDEO_CODEC_H264
};

/*!
 通话状态
 */
typedef NS_ENUM(NSInteger, RCCallStatus) {
    /*!
     初始状态
     */
    //RCCallIdle = 0,
    /*!
     正在呼出
     */
    RCCallDialing = 1,
    /*!
     正在呼入
     */
    RCCallIncoming = 2,
    /*!
     收到一个通话呼入后，正在振铃
     */
    RCCallRinging = 3,
    /*!
     正在通话
     */
    RCCallActive = 4,
    /*!
     已经挂断
     */
    RCCallHangup = 5
};

/*!
 用户类型
 */
typedef NS_ENUM(NSInteger, RCCallUserType) {
    /*!
     正常用户
     */
    RCCallUserNormal = 1,
    /*!
     观察者
     */
    RCCallUserObserver = 2
};

/*!
 同UserId两端同时加入通话类型
 */
typedef NS_ENUM(NSUInteger, RCCallJoinCallType) {
    /*!
     将先加入通话用户踢出通话
     */
    RCCallJoinCallTypeKick,
    /*!
     拒绝当前用户加入通话
     */
    RCCallJoinCallTypeRefuse,
    /*!
     两端共存, 可同时都在通话中
     */
    RCCallJoinCallTypeCoexist
};

#endif /* RCCallCommonDefine_h */
