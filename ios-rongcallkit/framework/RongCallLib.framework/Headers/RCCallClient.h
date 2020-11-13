//
//  RCCallClient.h
//  RongCallLib
//
//  Created by RongCloud on 16/2/28.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCCallCommonDefine.h"
#import "RCCallSession.h"
#import "RCCallClientSignalServer.h"
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <RongIMLib/RongIMLib.h>

#define kRongCallLibVersion @"V4.0.4_20201112193748_release_aae5735"

/*!
 CallLib全局通话呼入的监听器
 */
@protocol RCCallReceiveDelegate <NSObject>

@required
/*!
 接收到通话呼入的回调
 
 @param callSession 呼入的通话实体
 @discussion
 接收到通话呼入的回调
 
 @remarks 代理
 */
- (void)didReceiveCall:(RCCallSession *)callSession;

/*!

接收到通话呼入的远程通知的回调
 @param callId        呼入通话的唯一值
 @param inviterUserId 通话邀请者的UserId
 @param mediaType     通话的媒体类型
 @param userIdList    被邀请者的UserId列表
 @param userDict      远程推送包含的其他扩展信息
 @param isVoIPPush    是否 VoIP 推送
 @param pushConfig    推送配置

 @discussion
 接收到通话呼入的远程通知的回调
 
 @remarks 代理
 */
- (void)didReceiveCallRemoteNotification:(NSString *)callId
                           inviterUserId:(NSString *)inviterUserId
                               mediaType:(RCCallMediaType)mediaType
                              userIdList:(NSArray *)userIdList
                                userDict:(NSDictionary *)userDict
                              isVoIPPush:(BOOL)isVoIPPush
                              pushConfig:(RCMessagePushConfig*) pushConfig;

/*!
 接收到取消通话的远程通知的回调
 
 @param callId        呼入通话的唯一值
 @param inviterUserId 通话邀请者的UserId
 @param mediaType     通话的媒体类型
 @param userIdList    被邀请者的UserId列表
 @param pushConfig    推送配置
 @param isRemoteCancel  是否为远端取消呼叫
 @discussion
 接收到取消通话的远程通知的回调
 
 @remarks 代理
 */
-(void)didCancelCallRemoteNotification:(NSString *)callId
                         inviterUserId:(NSString *)inviterUserId
                             mediaType:(RCCallMediaType)mediaType
                            userIdList:(NSArray *)userIdList
                            pushConfig:(RCMessagePushConfig*) pushConfig
                        isRemoteCancel:(BOOL)isRemoteCancel;

@optional
/*!
 接收到取消通话的远程通知的回调
 
 @param callId        呼入通话的唯一值
 @param inviterUserId 通话邀请者的UserId
 @param mediaType     通话的媒体类型
 @param userIdList    被邀请者的UserId列表
 @discussion
 接收到取消通话的远程通知的回调
 
 @remarks 代理
 */
- (void)didCancelCallRemoteNotification:(NSString *)callId
                          inviterUserId:(NSString *)inviterUserId
                              mediaType:(RCCallMediaType)mediaType
                             userIdList:(NSArray *)userIdList API_DEPRECATED_WITH_REPLACEMENT("didCancelCallRemoteNotification: inviterUserId:mediaType:userIdList:message:isRemoteCancel:", ios(8.0, 13.0));

/*!
 接收到通话呼入的远程通知的回调
 
 @param callId        呼入通话的唯一值
 @param inviterUserId 通话邀请者的UserId
 @param mediaType     通话的媒体类型
 @param userIdList    被邀请者的UserId列表
 @param userDict      远程推送包含的其他扩展信息
 @discussion
 接收到通话呼入的远程通知的回调
 
 @remarks 代理
 */
- (void)didReceiveCallRemoteNotification:(NSString *)callId
                           inviterUserId:(NSString *)inviterUserId
                               mediaType:(RCCallMediaType)mediaType
                              userIdList:(NSArray *)userIdList
                                userDict:(NSDictionary *)userDict API_DEPRECATED_WITH_REPLACEMENT("didReceiveCallRemoteNotification:inviterUserId:mediaType:userIdList:userDict:isVoIPPush:message:", ios(8.0, 13.0));

/*!
 接收到通话呼入的远程通知的回调
 
 @param callId        呼入通话的唯一值
 @param inviterUserId 通话邀请者的UserId
 @param mediaType     通话的媒体类型
 @param userIdList    被邀请者的UserId列表
 @param userDict      远程推送包含的其他扩展信息
 @param isVoIPPush    是否 VoIP 推送
 @discussion
 接收到通话呼入的远程通知的回调
 
 @remarks 代理
 */
- (void)didReceiveCallRemoteNotification:(NSString *)callId
                           inviterUserId:(NSString *)inviterUserId
                               mediaType:(RCCallMediaType)mediaType
                              userIdList:(NSArray *)userIdList
                                userDict:(NSDictionary *)userDict
                              isVoIPPush:(BOOL)isVoIPPush  API_DEPRECATED_WITH_REPLACEMENT("didReceiveCallRemoteNotification:inviterUserId:mediaType:userIdList:userDict:isVoIPPush:message:", ios(8.0, 13.0));

@end

@class RCMessagePushConfig;

/*!
 融云CallLib核心类
 */
@interface RCCallClient : NSObject

/// 自定义push消息. 应在startCall之前调用
@property(nonatomic, strong)RCMessagePushConfig *invitePushConfig;

/// 自定义push消息. 应在startCall之前调用
@property(nonatomic, strong)RCMessagePushConfig *hangupPushConfig;

/*!
 获取融云通话能力库 RCCallClient 的核心类单例
 
 @discussion
 您可以通过此方法, 获取 RCCallClient 的单例，访问对象中的属性和方法
 
 @remarks 通话设置
 @return 融云通话能力库 RCCallClient 的核心类单例
 */
+ (instancetype)sharedRCCallClient;

/*!
 设置全局通话呼入的监听器
 
 @param delegate CallLib全局通话呼入的监听器
 @discussion
 设置全局通话呼入的监听器
 
 @remarks 通话设置
 */
- (void)setDelegate:(id<RCCallReceiveDelegate>)delegate;

/*!
 发起一个通话
 
 @param conversationType 会话类型
 @param targetId         目标会话ID, 单人呼叫时targetId为被叫端UserId, 多人呼叫时targetId为群组Id, 请不要填写主叫端UserId, 否则无法发起呼叫
 @param userIdList       被叫端的用户ID列表, 数组中仅填写被叫端UserId, 请不要填写主叫端UserId, 否则无法发起呼叫
 @param type             发起的通话媒体类型
 @param delegate         通话监听
 @param extra            附件信息
 @discussion
 发起一个通话
 
 @remarks 通话管理
 @return 呼出的通话实体
 */
- (RCCallSession *)startCall:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
                          to:(NSArray *)userIdList
                   mediaType:(RCCallMediaType)type
             sessionDelegate:(id<RCCallSessionDelegate>)delegate
                       extra:(NSString *)extra;

/*!
 发起一个通话
 
 @param conversationType 会话类型
 @param targetId         目标会话ID, 单人呼叫时targetId为被叫端UserId, 多人呼叫时targetId为群组Id
 @param userIdList       被叫端的用户ID列表, 数组中仅填写被叫端UserId, 请不要填写主叫端UserId, 否则无法发起呼叫
 @param observerIdList   主叫端指定需要以观察者身份加入房间的用户ID列表, 如果主叫端需要以观察者身份加入房间也需要填写主叫端UserId
 @param type             发起的通话媒体类型
 @param delegate         通话监听
 @param extra            附件信息
 @discussion
 发起一个通话
 
 @remarks 通话管理
 @return 呼出的通话实体
 */
- (RCCallSession *)startCall:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
                          to:(NSArray *)userIdList
              observerIdList:(NSArray *)observerIdList
                   mediaType:(RCCallMediaType)type
             sessionDelegate:(id<RCCallSessionDelegate>)delegate
                       extra:(NSString *)extra;


/*!
 当前会话类型是否支持音频通话
 
 @param conversationType 会话类型
 @discussion
 当前会话类型是否支持音频通话
 
 @remarks 通话设置
 @return 是否支持音频通话
 */
- (BOOL)isAudioCallEnabled:(RCConversationType)conversationType;

/*!
 当前会话类型是否支持视频通话
 
 @param conversationType 会话类型
 @discussion
 当前会话类型是否支持视频通话
 
 @remarks 通话设置
 @return 是否支持视频通话
 */
- (BOOL)isVideoCallEnabled:(RCConversationType)conversationType;

/*!
 设置本地视频分辨率
 
 @param profile 通话视频分辨率
 @discussion
 设置本地视频分辨率
 
 @remarks 视频设置
 */
- (void)setVideoProfile:(RCVideoProfile)profile;

/*!
 设置本地视频属性, 可用此接口设置本地视频方向
 
 @param orientation 视频方向, 默认: AVCaptureVideoOrientationPortrait
 @discussion
 设置本地视频属性, 可用此接口设置本地视频方向
 
 @remarks 视频设置
 */
- (void)setVideoOrientation:(AVCaptureVideoOrientation)orientation;

/*!
 设置码率
 
 @param rate 码率 单位 kbps
 @discussion
 设置码率
 
 @remarks 视频设置
 */
- (void)setBitRate:(NSUInteger)rate;

/*!
 设置外部信令服务器代理
 
 @param signalServerDelegate 外部信令服务器代理
 @discussion
 默认情况下 app 使用融云消息作为信令即可, 不需要设置此代理, 此时有个限制就是所有的通话必须在某一个会话中进行, 比如群组.
 如果您需要摆脱会话的限制, 请使用 server api 服务实现本代理, 然后 startCall 时 conversationType 传 0, targetId 传 nil, calllib 会调用您设置的代理来发送消息.
 请务必使用一个全局代理, 确保在拨打和接听 VoIP 的时候代理对象都存活, 这样才能确保正常通话.
 
 @remarks 通话设置
 */
- (void)setSignalServerDelegate:(id<RCCallSignalServerDelegate>)signalServerDelegate;

/*!
 当前的通话会话实体
 */
@property (nonatomic, strong, readonly) RCCallSession *currentCallSession;

/*!
 是否生成通话记录消息，默认为YES
 */
@property (nonatomic, assign) BOOL enableCallSummary;

/*!
 设置是否使用苹果 PushKit 推送
 
 @param enable YES 使用, NO 不使用
 @discussion
 是否打开苹果 PushKit 推送, 该推送可以直接激活 App, 注: iOS 13 以后 PushKit 必须结合苹果 CallKit.framework 进行使用, 否则无法正常处理 VoIP 相关推送逻辑,
 如果设置为 NO 则使用普通 APNS 消息推送来处理音视频信令逻辑, 默认关闭. 打开之后 App 默认需要自行处理 VoIP 推送唤起 CallKit.framework 的逻辑.
 
 @remarks 通话设置
 */
- (void)setApplePushKitEnable:(BOOL)enable;

@end
