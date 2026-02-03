//
//  RCCallClient.h
//  RongCallLib
//
//  Created by RongCloud on 16/2/28.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import <Foundation/Foundation.h>
#import <RongIMLibCore/RongIMLibCore.h>
#import <RongRTCLib/RongRTCLib.h>
#import "RCCallClientSignalServer.h"
#import "RCCallCommonDefine.h"
#import "RCCallSession.h"

NS_ASSUME_NONNULL_BEGIN

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
- (void)didReceiveCallRemoteNotification:(nullable NSString *)callId
                           inviterUserId:(nullable NSString *)inviterUserId
                               mediaType:(RCCallMediaType)mediaType
                              userIdList:(nullable NSArray<NSString *> *)userIdList
                                userDict:(nullable NSDictionary *)userDict
                              isVoIPPush:(BOOL)isVoIPPush
                              pushConfig:(nullable RCMessagePushConfig *)pushConfig;

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
- (void)didCancelCallRemoteNotification:(nullable NSString *)callId
                          inviterUserId:(nullable NSString *)inviterUserId
                              mediaType:(RCCallMediaType)mediaType
                             userIdList:(nullable NSArray<NSString *> *)userIdList
                             pushConfig:(nullable RCMessagePushConfig *)pushConfig
                         isRemoteCancel:(BOOL)isRemoteCancel;

@optional

/*!
 接收到通话漏接的回调
 
 @param callSession 呼入的通话实体
 @discussion
 接收到通话漏接的回调
 
 @remarks 代理
 */
- (void)didMissCall:(RCCallSession *)callSession;

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
                             userIdList:(NSArray *)userIdList
    DEPRECATED_MSG_ATTRIBUTE(
        "use didCancelCallRemoteNotification:inviterUserId:mediaType:userIdList:pushConfig:isRemoteCancel: instead");

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
                                userDict:(NSDictionary *)userDict
    DEPRECATED_MSG_ATTRIBUTE(
        "use didReceiveCallRemoteNotification:inviterUserId:mediaType:userIdList:userDict:isVoIPPush:pushConfig: "
        "instead");

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
                              isVoIPPush:(BOOL)isVoIPPush
    DEPRECATED_MSG_ATTRIBUTE(
        "use didReceiveCallRemoteNotification:inviterUserId:mediaType:userIdList:userDict:isVoIPPush:pushConfig: "
        "instead");

@end

/*!
 智能语音代理
 */
@protocol RCCallASRDelegate <NSObject>

@optional

/*!
 语音识别错误通知回调
 
 @remarks 代理
 */
- (void)didASRError:(NSInteger)code;

/*!
 语音识别服务开启通知回调
 
 @remarks 代理
 */
- (void)didReceiveStartASR;

/*!
 语音识别服务停止通知回调
 
 @remarks 代理
 */
- (void)didReceiveStopASR;

/*!
 语音识别信息回调
 
 @param asrContent 语音识别信息
 
 @remarks 代理
 */
- (void)didReceiveASRContent:(RCRTCASRContent *)asrContent;

/*!
 语音翻译内容回调
 
 @param content 语音翻译内容
 
 @remarks 代理
 */
- (void)didReceiveRealtimeTranslationContent:(RCRTCRealtimeTranslationContent *)content;

/*!
 智能总结开始通知回调
 
 @remarks 代理
 */
- (void)didReceiveStartSummarization:(NSString *)taskId;

/*!
 智能总结关闭通知回调
 
 @remarks 代理
 */
- (void)didReceiveStopSummarization:(NSString *)taskId;

@end

@class RCMessagePushConfig;

/*!
 融云CallLib核心类
 */
@interface RCCallClient : NSObject

/*!
 自定义push消息. 应在startCall之前调用
 */
@property (nonatomic, strong, nullable) RCMessagePushConfig *invitePushConfig;

/*!
 自定义push消息. 应在startCall之前调用
 */
@property (nonatomic, strong, nullable) RCMessagePushConfig *hangupPushConfig;

/*!
 呼叫或通话过程中, 当收到手机号系统来电时, 是否挂断当前呼叫或通话, 默认: Yes 挂断
*/
@property (nonatomic, assign) BOOL canHangupSystemPhonecall;

/*!
 在开启 IM 链接多端登录的前提下，同一 UserId 的不同端先后加入通话的处理行为 默认: RCCallJoinCallTypeKick 将先加入通话用户踢出通话
 */
@property (nonatomic, assign) RCCallJoinCallType joinCallType;

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
- (nullable RCCallSession *)startCall:(RCConversationType)conversationType
                             targetId:(NSString *)targetId
                                   to:(NSArray<NSString *> *)userIdList
                            mediaType:(RCCallMediaType)type
                      sessionDelegate:(id<RCCallSessionDelegate>)delegate
                                extra:(nullable NSString *)extra;

/*!
 发起一个跨应用通话
 
 @param conversationType 会话类型 (仅支持单聊)
 @param targetId         目标会话ID, 单人呼叫时targetId为被叫端UserId
 @param userIdList       被叫端的用户ID列表, 数组中仅填写被叫端UserId, 请不要填写主叫端UserId, 否则无法发起呼叫；（注意此处ID组成形式为Appkey+UserId, 格式为appkey_userid，注意下划线拼接）
 @param type             发起的通话媒体类型
 @param delegate         通话监听
 @param extra            附件信息
 @discussion
 发起一个通话
 
 @remarks 通话管理
 @return 呼出的通话实体
 */
- (RCCallSession *)startCrossCall:(RCConversationType)conversationType
                         targetId:(NSString *)targetId
                               to:(NSArray *)userIdList
                        mediaType:(RCCallMediaType)type
                  sessionDelegate:(id<RCCallSessionDelegate>)delegate
                            extra:(nullable NSString *)extra;

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
- (nullable RCCallSession *)startCall:(RCConversationType)conversationType
                             targetId:(NSString *)targetId
                                   to:(NSArray<NSString *> *)userIdList
                       observerIdList:(NSArray<NSString *> *)observerIdList
                            mediaType:(RCCallMediaType)type
                      sessionDelegate:(id<RCCallSessionDelegate>)delegate
                                extra:(nullable NSString *)extra;

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
@property (nonatomic, strong, readonly, nullable) RCCallSession *currentCallSession;

/*!
 @remarks 上次通话的通话会话静态实体
 
 @discussion
 5.8.0版本callLib修改
 currentCallSession有效生命周期由开始通话直到下次通话开始为止，变为了由开始通话直到这次通话结束为止
 为了弥补这个逻辑缺失，新增了lastCallSession，从这次通话回调结束以后生效，直到下次通话结束失效
 */
@property (nonatomic, strong, readonly, nullable) RCCallSessionSnapshot *lastCallSession;

/*!
 是否生成通话记录消息，默认为YES
 */
@property (nonatomic, assign) BOOL enableCallSummary;

/*!
 是否开启多平台模式，默认为NO
 */
@property (nonatomic, assign) BOOL enableMultiPlatformMode;

/*!
 设置是否使用苹果 PushKit 推送
 
 @param enable YES 使用, NO 不使用
 @discussion
 是否打开苹果 PushKit 推送, 该推送可以直接激活 App, 注: iOS 13 以后 PushKit 必须结合苹果 CallKit.framework 进行使用, 否则无法正常处理 VoIP 相关推送逻辑,
 如果设置为 NO 则使用普通 APNS 消息推送来处理音视频信令逻辑, 默认关闭. 打开之后 App 默认需要自行处理 VoIP 推送唤起 CallKit.framework 的逻辑.
 
 @remarks 通话设置
 */
- (void)setApplePushKitEnable:(BOOL)enable;

/*!
 设置是否使用音视频预热
 
@param preconnectEnabled YES 使用, NO 不使用
@discussion
默认情况下 SDK 内部会在发送通话信令或接听信令成功的时候，主动进行音视频的预热
 
@remarks 通话设置
 */
- (void)setPreconnectEnabled:(BOOL)preconnectEnabled;

/*!
 设置语音识别监听器
 
 @param delegate 语音识别监听器
 @discussion
 设置语音识别监听器
 
 @remarks 智能语音
 */
- (void)setASRDelegate:(id<RCCallASRDelegate>)delegate;

/*!
 设置语音识别源语言
 
 @param languageCode 语言代码
 @discussion
 设置语音识别源语言
 
 @remarks 智能语音
 */
- (void)setSrcLanguageCode:(NSString *)languageCode;

/*!
 设置语音识别中本地用户的昵称
 
 @param nickName 昵称，用于智能总结
 @discussion
 设置语音识别中本地用户的昵称
 
 @remarks 智能语音
 */
- (void)setNickName:(NSString *)nickName;

/*!
 开启语音识别服务
 
 @param completion 开启语音识别服务回调
 
 @discussion
 开启语音识别服务，如果房间内没有人发布流，则无法开启语音识别服务，SDK 会在有人发布流后补偿进行开启语音识别服务
 
 @remarks 智能语音
 */
- (void)startASR:(nullable void (^)(BOOL success, NSInteger code))completion;

/*!
 停止语音识别服务
 
 @param completion 停止语音识别服务回调
 
 @discussion
 停止语音识别服务
 
 @remarks 智能语音
 */
- (void)stopASR:(nullable void (^)(BOOL success, NSInteger code))completion;

/*!
 设置是否打开语音识别
 
@param enable YES 打开, NO 关闭
@return 返回值，0 代表成功
@discussion
1. 通话接通后，可以通过此接口打开或关闭语音识别功能；
2. 默认关闭语音识别功能，开启后会在通话过程中自动识别用户语音并转换为文字。
 
@remarks 智能语音
 */
- (int)setEnableASR:(BOOL)enable;

/*!
 开启语音翻译
 @param destLangCode 翻译目标语言码
 
 @discussion
 1. 语音翻译依赖语音识别服务，需要在收到 RCCallASRDelegate 的 didReceiveStartASR 回调后，调用开启语音翻译
 2. 开启语音翻译，会通过 RCCallASRDelegate 的 didReceiveRealtimeTranslationContent 回调返回语音翻译结果
 
 @remarks 智能语音
 */
- (void)startRealtimeTranslation:(NSString *)destLangCode copmletion:(nullable void (^)(BOOL success, NSInteger code))completion;

/*!
 关闭语音翻译
 
 @discussion
 关闭语音翻译
 
 @remarks 智能语音
 */
- (void)stopRealtimeTranslation:(nullable void (^)(BOOL success, NSInteger code))completion;

/*!
 开始智能总结任务
 
 @param completion 开启智能总结任务回调
 
 @discussion
 1. 智能总结任务依赖语音识别服务，需要在收到 RCCallASRDelegate 的 didReceiveStartASR 回调后，调用开启智能总结任务
 2. 开始智能总结任务为房间级别接口，房间内开始智能总结任务，会通过 RCCallASRDelegate 的 didReceiveStartSummarization 回调返回智能总结任务状态
 3. completion 中 taskId 为开始智能总结任务 ID
 
 @remarks 智能语音
 */
- (void)startSummarization:(nullable void(^)(BOOL isSuccess, RCRTCCode code, NSString *taskId))completion;

/*!
 关闭智能总结任务
 
 @param completion 关闭智能总结任务回调
 
 @discussion
 1. 关闭智能总结任务为房间级别接口，房间内关闭智能总结任务，会通过 RCCallASRDelegate 的 didReceiveStopSummarization 回调返回智能总结任务状态
 
 @remarks 智能语音
 */
- (void)stopSummarization:(nullable void(^)(BOOL isSuccess, RCRTCCode code))completion;

/*!
 生成智能总结
 
 @param roomId 生成智能总结的通话 ID
 @param taskId 智能总结任务 ID，通过 didReceiveStartSummarization 回调获取到
 @param startTime 本次需要总结的开始时间，UTC 时间戳，单位秒，传入 0，表示总结开始的时间
 @param endTime 本次需要总结的结束时间，UTC 时间戳，单位秒，传入 0，表示当前时间，如果总结已经停止，则表示总结结束的时间
 @param config 生成智能总结配置
 @param contentBlock 内容回调
 @param completion 结果回调
 
 @remarks 智能语音
 */
- (void)generateSummarization:(nonnull NSString *)callId
                       taskId:(nonnull NSString *)taskId
                    startTime:(NSTimeInterval)startTime
                      endTime:(NSTimeInterval)endTime
                       config:(nullable RCRTCGenerateSummarizationConfig *)config
                 contentBlock:(nullable void(^)(NSString *content))contentBlock
                   completion:(nullable void(^)(BOOL isSuccess, RCRTCCode code))completion;

/*!
 获取语音转文字
 
 @param roomId 获取语音转文字的通话 ID
 @param taskId 智能总结任务 ID，通过 didReceiveStartSummarization 回调获取到
 @param startTime 本次需要获取语音转文字的开始时间，UTC 时间戳，单位秒，传入 0，表示总结开始的时间
 @param endTime 本次需要获取语音转文字的结束时间，UTC 时间戳，单位秒，传入 0，表示当前时间，如果总结已经停止，则表示总结结束的时间
 @param destLang 目标语言代码，如果传入 nil，则使用默认语言
 @param contentBlock 内容回调，如果内容比较多，contentBlock 会回调多次
 @param completion 结果回调
 
 @remarks 智能语音
 */
- (void)getASRContent:(nonnull NSString *)callId
               taskId:(nonnull NSString *)taskId
            startTime:(NSTimeInterval)startTime
              endTime:(NSTimeInterval)endTime
             destLang:(nullable NSString *)destLang
         contentBlock:(nullable void(^)(NSString *content))contentBlock
           completion:(nullable void(^)(BOOL isSuccess, RCRTCCode code))completion;

/*!
 设置忙线处理策略
 
 @param busyCallPolicy 忙线处理策略
 @discussion
 默认值：RCCallBusyCallPolicyDefault 主叫响应拒绝，结束呼叫
 */
- (void)setBusyCallPolicy:(RCCallBusyCallPolicy)busyCallPolicy;

/*!
 获取 SDK 版本号

 @return 版本号

 @remarks 参数配置
 */
+ (NSString *)getVersion;

@end

NS_ASSUME_NONNULL_END
