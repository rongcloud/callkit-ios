//
//  RCCallSession.h
//  RongCallLib
//
//  Created by 岑裕 on 16/2/29.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCCallCommonDefine.h"
#import "RCCallUserProfile.h"
#import <Foundation/Foundation.h>
#import <RongIMLib/RongIMLib.h>
#import <CoreMedia/CoreMedia.h>

/*!
 通话状态变化的监听器
 */
@protocol RCCallSessionDelegate <NSObject>

@optional

/*!
 通话已接通
 */
- (void)callDidConnect;

/*!
 通话已结束
 */
- (void)callDidDisconnect;

/*!
 对端用户正在振铃

 @param userId 用户ID
 */
- (void)remoteUserDidRing:(NSString *)userId;

/*!
 有用户被邀请加入通话

 @param userId    被邀请的用户ID
 @param mediaType 希望被邀请者使用的媒体类型
 */
- (void)remoteUserDidInvite:(NSString *)userId mediaType:(RCCallMediaType)mediaType;

/*!
 对端用户加入了通话

 @param userId    用户ID
 @param mediaType 用户的媒体类型
 */
- (void)remoteUserDidJoin:(NSString *)userId mediaType:(RCCallMediaType)mediaType;

/*!
 对端用户切换了媒体类型

 @param userId    用户ID
 @param mediaType 切换至的媒体类型
 */
- (void)remoteUserDidChangeMediaType:(NSString *)userId mediaType:(RCCallMediaType)mediaType;

/*!
 对端用户开启或关闭了麦克风的状态
 
 @param disabled  是否关闭麦克风
 @param userId    用户ID
 */
- (void)remoteUserDidDisableMicrophone:(BOOL)disabled byUser:(NSString *)userId;

/*!
 对端用户开启或关闭了摄像头的状态

 @param disabled  是否关闭摄像头
 @param userId    用户ID
 */
- (void)remoteUserDidDisableCamera:(BOOL)disabled byUser:(NSString *)userId;

/*!
 对端用户挂断

 @param userId 用户ID
 @param reason 挂断的原因
 */
- (void)remoteUserDidLeft:(NSString *)userId reason:(RCCallDisconnectReason)reason;

/*!
 对端用户发布自定义媒体流

 @param streamId 自定义流ID
 @param tag 自定义流标签
 @param mediaType 媒体类型
*/
- (void)remoteUserDidPublishCustomMediaStream:(NSString *)streamId streamTag:(NSString *)tag mediaType:(RCCallMediaType)mediaType;

/*!
 对端用户取消发布自定义媒体流
 
 @param streamId 自定义流ID
*/
- (void)remoteUserDidCancelPublishCustomMediaStream:(NSString *)streamId;

/*!
 彩铃
 */
- (void)shouldAlertForWaitingRemoteResponse;

/*!
 来电铃声
 */
- (void)shouldRingForIncomingCall;

/*!
 停止播放铃声(通话接通或挂断)
 */
- (void)shouldStopAlertAndRing;

/*!
 通话过程中的错误回调

 @param error 错误码
 @warning 这个接口回调的错误码主要是为了提供必要的log以及提示用户，如果是不可恢复的错误，SDK会挂断电话并回调callDidDisconnect，App可以在callDidDisconnect中统一处理通话结束的逻辑。
 */
- (void)errorDidOccur:(RCCallErrorCode)error;

/*!
 当前通话网络状态的回调，该回调方法每秒触发一次

 @param txQuality   上行网络质量
 @param rxQuality   下行网络质量, 接收到的所有远端用户网络质量的平均值
 */
- (void)networkTxQuality:(RCCallQuality)txQuality rxQuality:(RCCallQuality)rxQuality;

/*!
 当前通话网络状态的回调，该回调方法每秒触发一次
 
 @param txQuality   上行网络质量
 @param rxQuality   下行网络质量, 接收到的某个远端用户的网络质量
 @param userID      远端用户
 */
- (void)networkTxQuality:(RCCallQuality)txQuality rxQuality:(RCCallQuality)rxQuality remoteUserID:(NSString *)userID;

/*!
 当前通话某用户声音音量回调，该回调方法每两秒触发一次

 @param leavel   声音级别: 0~9, 0为无声, 依次变大
 @param userID   用户ID, 本端用户ID(发送音量) 或 远端用户ID(接收音量)
*/
- (void)audioLevel:(NSInteger)leavel userID:(NSString *)userID;

/*!
 当前通话本地视频数据, 用于GPU滤镜处理, 同步返回处理后的同一 sampleBuffer 对象,
 需要本地视频数据时首先调用 RCCallClient.h 中 - (void)setEnableBeauty:(BOOL)enable方法设置为打开, 该方法默认为NO
 若设置setEnableBeauty为Yes, 但未实现 processVideoFrame: 则使用采集的原始视频显示和发送
 @param sampleBuffer   本地视频数据
 */
- (CMSampleBufferRef)processVideoFrame:(CMSampleBufferRef)sampleBuffer;

/*!
 当前通话视频通话时, 收到远端用户的第一个视频帧的回调.
 @param userId   远端用户ID
 */
- (void)receiveRemoteUserVideoFirstKeyFrame:(NSString *)userId;

@end


/*!
 通话实体
 */
@interface RCCallSession : NSObject

/*!
 通话的会话类型
 */
@property(nonatomic, assign, readonly) RCConversationType conversationType;

/*!
 通话ID
 */
@property(nonatomic, strong, readonly) NSString *callId;

/*!
 通话的目标会话ID
 */
@property(nonatomic, strong, readonly) NSString *targetId;

/*!
 是否是多方通话
 */
@property(nonatomic, assign, readonly, getter=isMultiCall) BOOL multiCall;

/*!
 通话的扩展信息
 */
@property(nonatomic, strong, readonly) NSString *extra;

/*!
 通话的当前状态
 */
@property(nonatomic, assign, readonly) RCCallStatus callStatus;

/*!
 通话的最初发起人
 */
@property(nonatomic, strong, readonly) NSString *caller;

/*!
 邀请当前用户加入通话的邀请者
 */
@property(nonatomic, strong, readonly) NSString *inviter;

/*!
 当前的用户列表
 */
@property(nonatomic, strong, readonly) NSArray *userProfileList;

/*!
 自己的状态
 */
@property(nonatomic, strong, readonly) RCCallUserProfile *myProfile;

/*!
 当前用户使用的媒体类型
 */
@property(nonatomic, assign, readonly) RCCallMediaType mediaType;

/*!
 通话开始的时间

 @discussion 如果是用户呼出的通话，则startTime为通话呼出时间；如果是呼入的通话，则startTime为通话呼入时间。
 */
@property(nonatomic, assign, readonly) long long startTime;

/*!
 通话接通时间
 */
@property(nonatomic, assign, readonly) long long connectedTime;

/*!
 通话挂断原因
 */
@property(nonatomic, assign) RCCallDisconnectReason disconnectReason;

/*!
 设置通话状态变化的监听器

 @param delegate 通话状态变化的监听器
 */
- (void)setDelegate:(id<RCCallSessionDelegate>)delegate DEPRECATED_MSG_ATTRIBUTE("please call method addDelegate:");

/**
 添加通话状态的监听器, 支持多代理

 @param delegate 通话状态变化的监听器
 */
- (void)addDelegate:(id<RCCallSessionDelegate>)delegate;

/**
 删除通话状态的监听器

 @param delegate 通话状态的监听器
 */
- (void)removeDelegate:(id<RCCallSessionDelegate>)delegate;

/**
 获取所有的监听器

 @return 返回监听器数组
 */
- (NSArray <id <RCCallSessionDelegate>> *)allDelegates;

/*!
 接听来电

 @param type 接听使用的媒体类型
 */
- (void)accept:(RCCallMediaType)type;

/*!
 挂断通话
 */
- (void)hangup;

/*!
 观察者身份用户, 发布自己的音视频资源
 */
- (void)publishMediaResource:(RCCallMediaType)mediaType complete:(void(^)(BOOL isSuccess, NSInteger code))block;

/*!
 正常身份用户, 取消发布自己的音视频资源
 */
- (void)unPublishMediaResource:(void(^)(BOOL isSuccess, NSInteger code))block;

/*!
 邀请用户加入通话

 @param userIdList 用户ID列表
 @param type       建议被邀请者使用的媒体类型
 */
- (void)inviteRemoteUsers:(NSArray *)userIdList mediaType:(RCCallMediaType)type;

/*!
 邀请用户加入通话
 
 @param userIdList 用户ID列表
 @param observerIdList 需要以观察者身份加入房间的用户ID列表
 @param type       建议被邀请者使用的媒体类型
 */
- (void)inviteRemoteUsers:(NSArray *)userIdList observerIdList:(NSArray *)observerIdList mediaType:(RCCallMediaType)type;

/*!
 设置用户所在的视频View

 @param userId 用户ID（自己或他人）
 @param view   视频的View
 */
- (void)setVideoView:(UIView *)view userId:(NSString *)userId;

/**
 设置用户所在的视频View

 @param view userId 用户ID（自己或他人)
 @param userId 视频的View
 @param renderMode 视频显示模式 (默认为RCCallRenderModelHidden)
 */
- (void)setVideoView:(UIView *)view userId:(NSString *)userId renderMode:(RCCallRenderModel)renderMode;

/*!
 更换自己使用的媒体类型

 @param type 媒体类型
 */
- (BOOL)changeMediaType:(RCCallMediaType)type;

/*!
 静音状态
 */
@property(nonatomic, readonly) BOOL isMuted;

/*!
 设置静音状态

 @param muted 是否静音
 @return 是否设置成功
 @discussion 默认值为NO。
 */
- (BOOL)setMuted:(BOOL)muted;

/*!
 是否有最小化窗口
 */
@property(nonatomic, readonly) BOOL minimized;

/*!
 设置是否有最小化窗口状态
 
 @param minimized 是否最小化
 */
- (void)setMinimized:(BOOL)minimized;

/*!
 扬声器状态，是否开启扬声器

 @discussion 音频通话的默认值为NO，视频通话的默认值为YES。
 */
@property(nonatomic, readonly) BOOL speakerEnabled;

/*!
 设置扬声器状态

 @param speakerEnabled  是否开启扬声器
 @return                是否设置成功
 */
- (BOOL)setSpeakerEnabled:(BOOL)speakerEnabled;

/*!
 摄像头状态，是否开启摄像头
 */
@property(nonatomic, readonly) BOOL cameraEnabled;

/*!
 设置摄像头状态

 @param cameraEnabled  是否开启摄像头
 @return               是否设置成功
 @discussion 音频通话的默认值为NO，视频通话的默认值为YES。
 */
- (BOOL)setCameraEnabled:(BOOL)cameraEnabled;

/*!
 切换前后摄像头

 @return 是否切换成功
 */
- (BOOL)switchCameraMode;

@end
