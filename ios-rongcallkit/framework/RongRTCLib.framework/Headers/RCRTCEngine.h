//
//  RCRTCEngine.h
//  RongRTCLib
//
//  Created by RongCloud on 2019/1/2.
//  Copyright © 2019 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "RCRTCAudioEffectManager.h"
#import "RCRTCCodeDefine.h"
#import "RCRTCConfig.h"
#import "RCRTCCryptoDelegate.h"
#import "RCRTCLibDefine.h"
#import "RCRTCRoomConfig.h"
#import "RCRTCJoinedRoomInfo.h"

NS_ASSUME_NONNULL_BEGIN

@class RCRTCRoom;
@class RCRTCOtherRoom;
@class RCRTCVideoPreviewView;
@class RCRTCVideoStreamConfig;
@class RCRTCOutputStream;
@class RCRTCMicOutputStream;
@class RCRTCCameraOutputStream;
@class RCRTCFileVideoOutputStream;
@class RCRTCScreenShareOutputStream;
@protocol RCRTCStatusReportDelegate;
@protocol RCRTCEngineEventDelegate;
@protocol RCRTCProbeTestDelegate;

/*!
 音视频引擎类
 */
@interface RCRTCEngine : NSObject

/*!
 音视频引擎单例

 @remarks RCRTCEngine
 */
+ (RCRTCEngine *)sharedInstance;

/*!
 请使用 sharedInstance 初始化方法
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
 请使用 sharedInstance 初始化方法
 */
- (instancetype)new NS_UNAVAILABLE;

/*!
 音视频引擎参数设置
 
 @param config Engine 配置
 @return 错误码，参考 RCRTCCode

 @remarks RCRTCEngine：参数配置
 */
- (int)initWithConfig:(RCRTCConfig *)config;

/*!
 音视频引擎销毁资源, 会有主动离开房间操作

 @remarks RCRTCEngine
 */
- (void)unInit;

/*!
 音效管理器，管理播放、暂停等

 @remarks RCRTCEngine：参数配置
 */
@property (nonatomic, strong, readonly) RCRTCAudioEffectManager *audioEffectManager;

/*!
 全局音视频配置信息

 @remarks RCRTCEngine：参数配置
 */
@property (nonatomic, strong, readonly, nullable) RCRTCConfig *config;

/*!
 当前已加入的房间，已废弃

 @deprecated 4.0.5
 @remarks RCRTCEngine：房间接口
 */
@property (nonatomic, strong, readonly, nullable) RCRTCRoom *currentRoom DEPRECATED_MSG_ATTRIBUTE("use room property instead");

/*!
 当前已加入的房间

 @remarks RCRTCEngine：房间接口
 */
@property (nonatomic, strong, readonly, nullable) RCRTCRoom *room;

/*!
 本地默认音频流

 @remarks RCRTCEngine：媒体流操作
 */
@property (nonatomic, strong, readonly) RCRTCMicOutputStream *defaultAudioStream;

/*!
 本地默认视频流

 @remarks RCRTCEngine：媒体流操作
 */
@property (nonatomic, strong, readonly) RCRTCCameraOutputStream *defaultVideoStream;

/*!
 房间状态报告监听

 @remarks RCRTCEngine：统计接口
 */
@property (nonatomic, weak, nullable) id<RCRTCStatusReportDelegate> statusReportDelegate;

/*!
 Engine 代理

 @remarks RCRTCEngine：Engine 通知接口
 */
@property (nonatomic, weak, nullable) id<RCRTCEngineEventDelegate> delegate;

/*!
 整体播放音量，范围:0~100，默认值:100

 @remarks RCRTCEngine：媒体流操作
 */
@property (nonatomic, assign) NSUInteger playingVolume;

/*!
 所有远端流音量，范围:0~200，默认值:100

 @remarks RCRTCEngine：媒体流操作
 */
@property (nonatomic, assign) NSUInteger remotePlaybackVolume;

#pragma mark - 设备检测
/*!
 设备检测
 @param interval   麦克风录制统计时间[2 10] 单位 s,大于10秒默认为10s 小于2秒按2秒计算
 
 @remarks RCRTCEngine：设备检测开启接口
 added from 5.1.9
 */
- (void)startEchoTest:(NSTimeInterval)interval;

/*!
 设备检测
 
 @remarks RCRTCEngine：设备检测关闭接口
 added from 5.1.9
 */
- (void)stopEchoTest;

#pragma mark - 创建自定义文件视频流
/*!
 创建自定义文件视频流
     
 @param path      文件路径
 @param replace   文件中音频是否替换麦克风数据，YES 替换麦克风数据，NO 与麦克风数据混音
 @param playback  文件中的音频是否在本端播放
 @param tag       自定义视频文件流标识
 @param config    自定视频文件流的配置信息
 
 @return 自定义视频文件流
 
 @discussion Added from 5.1.9
 
 @remarks RCRTCEngine：媒体流操作
 */
- (nullable RCRTCFileVideoOutputStream *)createFileVideoOutputStream:(NSString *)path
                                                        replaceAudio:(BOOL)replace
                                                            playback:(BOOL)playback
                                                                 tag:(NSString *)tag
                                                              config:(RCRTCVideoStreamConfig *)config;

#pragma mark - 获取屏幕共享流
/*!
 获取屏幕共享所需流
 
 @param groupId   groupId 苹果开发者账号后台申请
 
 @remarks RCRTCEngine：RCRTCScreenShareOutputStream  get 接口
 added from 5.1.8
 */
- (RCRTCScreenShareOutputStream *)getScreenShareVideoStreamWithGroupId:(NSString *)groupId;

#pragma mark - 设置媒体服务器地址
/*!
 设置媒体服务器地址

 @remarks RCRTCEngine：参数配置

 @param url 媒体服务器地址
 设置媒体服务器地址，特别注意如果设置了会覆盖导航下载下来的 media server url
 @return 设置是否成功
 */
- (BOOL)setMediaServerUrl:(NSString *)url;

#pragma mark - 听筒/扬声器切换
/*!
 启用扬声器

 @param useSpeaker YES 启用扬声器；NO 关闭扬声器
 @discussion
 暂态设置启用或关闭扬声器

 @deprecated 4.0.5
 @remarks RCRTCEngine：媒体流操作
 @return 调用成功返回 YES
 */
- (BOOL)useSpeaker:(BOOL)useSpeaker DEPRECATED_MSG_ATTRIBUTE("use enableSpeaker: API instead");

/*!
 启用扬声器

 @param enable 默认值为 YES；YES 启用扬声器；NO 关闭扬声器
 @discussion
 暂态设置启用或关闭扬声器，任何用户行为或者音频相关 API 的调用都有可能改变暂态设置

 @remarks RCRTCEngine：媒体流操作
 @return 调用成功返回 YES
 */
- (BOOL)enableSpeaker:(BOOL)enable;

/*!
 设置默认音频路由

 @param defaultToSpeaker 默认为 NO，不使用扬声器作为默认音频路由；YES 使用扬声器作为默认音频路由
 @discussion
 设置默认的音频路由，就是在没有外接设备的前提下，设置系统使用听筒还是扬声器播放音频。

 @remarks RCRTCEngine：媒体流操作
 @return 调用成功返回 YES
 */
- (BOOL)setDefaultAudioRouteToSpeaker:(BOOL)defaultToSpeaker;

#pragma mark - 自定义加密
/*!
 设置音频输出流自定义加密回调

 @param audioEncryptorDelegate 加密代理，接口传入 RCRTCCustomizedEncryptorDelegate 的非空实现对象表示开启自定义加密；
 如果传入 nil 代表关闭自定义加密。

 @discussion
 该接口设置为全局设置，对所有发送音频进行加密，开启时机为加入房间前或者观众订阅流前，关闭时机为离开房间或者观众取消订阅流后，
 其它时机调用可能会不生效或者其它负面效果。

 @remarks RCRTCEngine：加密接口
 */
- (void)setAudioCustomizedEncryptorDelegate:(nullable id<RCRTCCustomizedEncryptorDelegate>)audioEncryptorDelegate;

/*!
 设置音频输入流自定义解密回调

 @param audioDecryptorDelegate 加密代理，接口传入 RCRTCDecryptorDelegate 的非空实现对象表示开启自定义解密；
 如果传入 nil 代表关闭自定义解密。

 @discussion
 该接口设置为全局设置，对所有接收音频进行解密，开启时机为加入房间前或者观众订阅流前，关闭时机为离开房间或者观众取消订阅流后，
 其它时机调用可能会不生效或者其它负面效果。

 @remarks RCRTCEngine：加密接口

 */
- (void)setAudioCustomizedDecryptorDelegate:(nullable id<RCRTCCustomizedDecryptorDelegate>)audioDecryptorDelegate;

/*!
 设置视频输出流自定义加密回调

 @param videoEncryptorDelegate 加密代理，接口传入 RCRTCCustomizedEncryptorDelegate 的非空实现对象表示开启自定义加密；
 如果传入 nil 代表关闭自定义加密。

 @discussion
 该接口设置为全局设置，对所有发送视频进行加密，开启时机为加入房间前或者观众订阅流前，关闭时机为离开房间或者观众取消订阅流后，
 其它时机调用可能会不生效或者其它负面效果。

 @remarks RCRTCEngine：加密接口

 */
- (void)setVideoCustomizedEncryptorDelegate:(nullable id<RCRTCCustomizedEncryptorDelegate>)videoEncryptorDelegate;

/*!
 设置视频输入流自定义解密回调

 @param videoDecryptorDelegate 加密代理，接口传入 RCRTCDecryptorDelegate 的非空实现对象表示开启自定义解密；
 如果传入 nil 代表关闭自定义解密。

 @discussion
 该接口设置为全局设置，对所有接收视频进行解密，开启时机为加入房间前或者观众订阅流前，关闭时机为离开房间或者观众取消订阅流后，
 其它时机调用可能会不生效或者其它负面效果。

 @remarks RCRTCEngine：加密接口
 */
- (void)setVideoCustomizedDecryptorDelegate:(nullable id<RCRTCCustomizedDecryptorDelegate>)videoDecryptorDelegate;

#pragma mark - 加入房间
/*!
 加入房间

 @param roomId 房间 Id, 支持大小写英文字母、数字、部分特殊符号 + = - _ 的组合方式 最长 64 个字符
 @param completion 加入房间回调,其中, room 对象中的 remoteUsers, 存储当前房间中的所有人, 包括发布资源和没有发布资源的人

 @remarks RCRTCEngine：房间接口
 */
- (void)joinRoom:(NSString *)roomId
      completion:(nullable void (^)(RCRTCRoom *_Nullable room, RCRTCCode code))completion;

/*!
 加入指定类型房间

 @param roomId 房间 Id, 支持大小写英文字母、数字、部分特殊符号 + = - _ 的组合方式 最长 64 个字符
 @param config 加入房间的配置, 主要用于配置直播场景。
 @param completion 加入房间回调, 其中 room 对象中的 remoteUsers, 存储当前房间中的所有人, 包括发布资源和没有发布资源的人
 @discussion
 加入房间

 @remarks RCRTCEngine：房间接口
 */
- (void)joinRoom:(NSString *)roomId
          config:(RCRTCRoomConfig *)config
      completion:(nullable void (^)(RCRTCRoom *_Nullable room, RCRTCCode code))completion;

#pragma mark - 离开房间
/*!
 离开房间，已废弃

 @param roomId 房间 Id
 @param completion 离开房间回调

 @deprecated 4.0.5
 @remarks RCRTCEngine：房间接口
 */
- (void)leaveRoom:(NSString *)roomId
       completion:(nullable void (^)(BOOL isSuccess, RCRTCCode code))completion
    DEPRECATED_MSG_ATTRIBUTE("use leaveRoom: API instead");

/*!
 离开房间

 @param completion 离开房间回调
 @discussion
 离开房间时不需要调用取消资源发布, SDK 内部会做好取消发布资源逻辑

 @remarks RCRTCEngine：房间接口
 */
- (void)leaveRoom:(nullable RCRTCOperationCallback)completion;

#pragma mark - 加入副房间
/*!
 连麦邀请后加入副房间

 @param roomId 副房间 Id, 支持大小写英文字母、数字、部分特殊符号 + = - _ 的组合方式 最长 64 个字符
 @param completion 加入副房间回调
 @discussion
 此方法仅供连麦加入副房间使用

 @remarks RCRTCEngine：房间接口
 */
- (void)joinOtherRoom:(NSString *)roomId
           completion:(nullable void (^)(RCRTCOtherRoom *_Nullable room, RCRTCCode code))completion;

#pragma mark - 离开副房间
/*!
 离开副房间

 @param roomId 副房间 Id
 @param isNotify 是否通知所有连麦用户结束, YES:通知  NO:不通知；
                如果想在退出副房间的同时结束 PK，请调用 RCRTCLocalUser.h 的 quitRoomPK 接口。
 @param completion 离开房间回调
 @discussion
 此方法仅供连麦离开副房间使用

 @remarks RCRTCEngine：房间接口
 */
- (void)leaveOtherRoom:(NSString *)roomId
        notifyFinished:(BOOL)isNotify
            completion:(nullable RCRTCOperationCallback)completion DEPRECATED_MSG_ATTRIBUTE("use leaveOtherRoom:completion: API instead");

/*!
 离开副房间

 @param roomId 副房间 Id
 @param completion 离开房间回调
 @discussion
 此方法仅供连麦离开副房间使用

 @remarks RCRTCEngine：房间接口
 */
- (void)leaveOtherRoom:(NSString *)roomId
            completion:(nullable RCRTCOperationCallback)completion;

#pragma mark - 观众订阅，取消订阅
/*!
 观众订阅主播资源，已废弃

 @param url 主播直播的 url
 @param streamType 需要具体订阅的媒体类型
 @param completion  动作的回调, 会依次回调主播的 RCRTCInputStream, 根据 streamType 区分是音频流还是视频流, 如主播发布了音视频流, 此回调会回调两次, 分别为音频的 RCRTCInputStream,  和视频的 RCRTCInputStream 。
 @discussion
 仅直播模式可用,  作为观众, 直接观看主播的直播, 无需加入房间, 通过传入主播的 url, 仅观众端可用，此接口可具体订阅音频流或视频流或大小流
 
 @deprecated from 5.1.0
 @remarks RCRTCEngine：媒体流操作
 */
- (void)subscribeLiveStream:(NSString *)url
                 streamType:(RCRTCAVStreamType)streamType
                 completion:(nullable RCRTCLiveCallback)completion
    DEPRECATED_MSG_ATTRIBUTE("use RCRTCLocalUser.h subscribeStream:tinyStreams:completion: API instead");

/*!
 观众取消订阅主播资源，已废弃

 @param url 主播直播的 url
 @param completion 动作的回调
 @discussion
 仅直播模式可用, 作为观众, 退出观看主播的直播, 仅观众端使用
 
 @deprecated from 5.1.0
 @remarks RCRTCEngine：媒体流操作
 */
- (void)unsubscribeLiveStream:(NSString *)url
                   completion:(nullable void (^)(BOOL isSuccess, RCRTCCode code))completion
    DEPRECATED_MSG_ATTRIBUTE("use RCRTCLocalUser.h unsubscribeStreams:completion: API instead");

/*!
 查询当前用户已经加入的房间
 
 @discussion
 查询当前用户已经加入的房间
 
 @remarks 房间管理
 */
- (void)queryRTCRoomJoinedInfo:(nullable void(^)(BOOL isSuccess, RCRTCCode code, NSArray <RCRTCJoinedRoomInfo *> * _Nullable infoArray))completion;

/*!
 加房间前探测回调
 
 @discussion Add from 5.1.17
 
 @remarks RCRTCEngine：统计接口
 */
@property (nonatomic, weak, nullable) id<RCRTCProbeTestDelegate> probeTestDelegate;

/*!
 加房间前探测
 
 @param callback 开始探测操作的回调
 @discussion
 与当前的 media server 建立连接，可以从 RCRTCProbeTestDelegate 拿到探测的上下行报表数据，探测持续 30s 自动结束。
 Add from 5.1.17
 
 @remarks RCRTCEngine：探测接口
 */
- (void)startRTCProbeTest:(nullable RCRTCOperationCallback)callback;

/*!
 主动结束探测
 
 @param callback 开始探测操作的回调
 @discussion
 探测自动结束前,可以手动调用该接口停止探测。
 Add from 5.1.17
 
 @remarks RCRTCEngine：探测接口
 */
- (void)stopRTCProbeTest:(nullable RCRTCOperationCallback)callback;

#pragma mark - 智能语音
/*!
 生成智能总结
 
 @param roomId 生成智能总结的房间 ID
 @param taskId 智能总结任务 ID，通过 didReceiveStartSummarization 回调获取到
 @param startTime 本次需要总结的开始时间，UTC 时间戳，单位秒，传入 0，表示总结开始的时间
 @param endTime 本次需要总结的结束时间，UTC 时间戳，单位秒，传入 0，表示当前时间，如果总结已经停止，则表示总结结束的时间
 @param config 生成智能总结配置
 @param contentBlock 内容回调
 @param completion 结果回调
 
 @remarks 智能语音
 */
- (void)generateSummarization:(nonnull NSString *)roomId
                       taskId:(nonnull NSString *)taskId
                    startTime:(NSTimeInterval)startTime
                      endTime:(NSTimeInterval)endTime
                       config:(nullable RCRTCGenerateSummarizationConfig *)config
                 contentBlock:(nullable void(^)(NSString *content))contentBlock
                   completion:(nullable void(^)(BOOL isSuccess, RCRTCCode code))completion;

/*!
 获取语音转文字
 
 @param roomId 获取语音转文字的房间 ID
 @param taskId 智能总结任务 ID，通过 didReceiveStartSummarization 回调获取到
 @param startTime 本次需要获取语音转文字的开始时间，UTC 时间戳，单位秒，传入 0，表示总结开始的时间
 @param endTime 本次需要获取语音转文字的结束时间，UTC 时间戳，单位秒，传入 0，表示当前时间，如果总结已经停止，则表示总结结束的时间
 @param destLang 目标语言代码，如果传入 nil，则使用默认语言
 @param contentBlock 内容回调，如果内容比较多，contentBlock 会回调多次
 @param completion 结果回调
 
 @remarks 智能语音
 */
- (void)getASRContent:(nonnull NSString *)roomId
               taskId:(nonnull NSString *)taskId
            startTime:(NSTimeInterval)startTime
              endTime:(NSTimeInterval)endTime
             destLang:(nullable NSString *)destLang
         contentBlock:(nullable void(^)(NSString *content))contentBlock
           completion:(nullable void(^)(BOOL isSuccess, RCRTCCode code))completion;

#pragma mark - SDK 版本号
/*!
 获取 SDK 版本号，已废弃

 @return 版本号

 @deprecated 4.0.5
 @remarks RCRTCEngine：参数配置
 */
- (NSString *)getRTCLibVersion DEPRECATED_MSG_ATTRIBUTE("use getVersion API instead");

/*!
 获取 SDK 版本号

 @return 版本号

 @remarks RCRTCEngine：参数配置
 */
+ (NSString *)getVersion;

/*!
 获取 SDK 是否为私有云版本

 @return SDK 是否为私有云版本

 @remarks RCRTCEngine：参数配置
 */

+ (BOOL)isPrivateSDK;

@end

NS_ASSUME_NONNULL_END
