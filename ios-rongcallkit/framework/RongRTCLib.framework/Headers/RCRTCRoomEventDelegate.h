//
//  RCRTCRoomEventDelegate.h
//  RongRTCLib
//
//  Created by RongCloud on 2019/1/7.
//  Copyright © 2019 RongCloud. All rights reserved.
//

#ifndef RongRTCRoomDelegate_h
#define RongRTCRoomDelegate_h

#import <AVFoundation/AVFoundation.h>
#import <Foundation/Foundation.h>

@class RCRTCRemoteUser;
@class RCRTCAudioInputStream;
@class RCRTCVideoInputStream;
@class RCRTCRoom;
@class RCRTCCDNInputStream;
@class RCRTCASR;

NS_ASSUME_NONNULL_BEGIN

/*!
 音视频通话的房间代理, 实现这个代理之后房间成员变化以及资源的变化都会通过代理通知给您
 */
@protocol RCRTCRoomEventDelegate <NSObject>

@optional

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
 远端用户加入通知
 
 @param user 加入的用户信息
 @discussion
 有用户加入的回调, 此时 user 不包含任何资源, 只是标记有人加入, 此时无法订阅这个人的流
 
 @remarks 代理
 */
- (void)didJoinUser:(RCRTCRemoteUser *)user;

/*!
 远端用户离开通知
 
 @param user 离开的用户
 @discussion
 有用户离开时的回调, 当有用户离开的时候, SDK 会取消订阅这个 user,  APP 无需再次调用取消订阅的接口
 
 @remarks 代理
 */
- (void)didLeaveUser:(RCRTCRemoteUser *)user;

/*!
 远端用户切换身份通知
 
 @param user 切换身份的用户
 @param roleType 该用户当前的身份
 
 @discussion
 有切换身份时的回调，当有用户切换身份的时候，当前房间内其他主播会收到该消息。
 如果订阅了当前 user 的流，SDK 会主动取消订阅，不需要手动取消订阅。
 added from 5.1.9
 
 @remarks 代理
 */
- (void)didSwitchRoleWithUser:(RCRTCRemoteUser *)user roleType:(RCRTCLiveRoleType)roleType;


/*!
 远端用户掉线通知
 
 @param user 掉线的用户
 @discussion
 有用户掉线时的回调, 当有用户掉线的时候, SDK 会取消订阅这个 user,  APP 无需再次调用取消订阅的接口
 
 @remarks 代理
 */
- (void)didOfflineUser:(RCRTCRemoteUser *)user;

/*!
 第一个视频关键帧到达通知
 
 @param stream 开始接收数据的 stream
 @discussion
 数据流第一个关键帧到达
 
 @remarks 代理
 */
- (void)didReportFirstKeyframe:(RCRTCVideoInputStream *)stream
    DEPRECATED_MSG_ATTRIBUTE("use RCRTCRoomEventDelegate.h didReportFirstFrame:mediaType: instead");

/*!
 加入房间后, 第一个音频关键帧到达通知
 
 @param stream 开始接收数据的 stream
 @discussion
 数据流第一个关键帧到达
 
 @remarks 代理
 */
- (void)didReportFirstAudioFrame:(RCRTCAudioInputStream *)stream
    DEPRECATED_MSG_ATTRIBUTE("use RCRTCRoomEventDelegate.h didReportFirstFrame:mediaType: instead");

/*!
 订阅远端资源成功后, 音频或视频首帧到达通知
 
 @param stream 开始接收数据的 stream
 @param mediaType 数据流类型（如视频流、音频流）
 @discussion
 数据流第一个关键帧到达
 
 @remarks 代理
 */
- (void)didReportFirstFrame:(RCRTCInputStream *)stream mediaType:(RCRTCMediaType)mediaType;

/*!
 远端用户发布资源通知
 
 @param streams 用户发布的资源信息
 @discussion
 当有远端用户发布资源时, 通过此方法回调通知上报该用户发布的流, 其中流中有 userID（用户 ID）,  tag（标识符）,  type（流类型）,  state（是否禁用） 等关键信息, 可调用订阅接口, 订阅其中的流
 
 @remarks 代理
 */
- (void)didPublishStreams:(NSArray<RCRTCInputStream *> *)streams;

/*!
 远端用户取消发布资源通知

 @param streams 取消发布资源
 @discussion
 当有远端用户取消发布资源时, 通过此方法回调, SDK 默认会取消订阅这些流, 其中流中有 userID（用户 ID）,  tag（标识符）,  type（流类型）,  state（是否禁用） 等关键信息, APP 可根据这些关键信息自定义化, 无需再次调用取消订阅接口
 
 @remarks 代理
 */
- (void)didUnpublishStreams:(NSArray<RCRTCInputStream *> *)streams;

/*!
 远端直播合流发布资源通知

 @param streams 发布的直播资源
 @discussion
 当直播存在的时候(只要有一个主播存在),直播合流就存在,代理会通知到用户liveStreams已经发布
 用户可以使用RCRTCLocal.h 里面的 subscribeStream:tinyStreams:completion: api去订阅.
 Added from 5.1.0
 
 @remarks 代理
 */
- (void)didPublishLiveStreams:(NSArray<RCRTCInputStream *> *)streams;

/*!
 远端直播合流取消发布资源通知

 @param streams 取消发布的直播资源
 @discussion
 当房间内没有任何主播在发布资源的时候, 直播的合流就不存在了,
 代理会通知到用户liveStreams已经取消发布,sdk内部会主动取消订阅一次,用户也可以进行一次取消订阅合流.
 Added from 5.1.0
 
 @remarks 代理
 */
- (void)didUnpublishLiveStreams:(NSArray<RCRTCInputStream *> *)streams;

/*!
 远端CDN流发布资源通知

 @param stream 发布的CDN资源
 @discussion
 Added from 5.1.5
 
 @remarks 代理
 */
- (void)didPublishCDNStream:(RCRTCCDNInputStream *)stream;

/*!
 远端CDN流取消发布资源通知

 @param stream 取消发布的CDN资源
 @discussion
 Added from 5.1.5
 
 @remarks 代理
 */
- (void)didUnpublishCDNStream:(RCRTCCDNInputStream *)stream;

/*!
 接收到远端用户发送的 SEI 通知
 
 @param SEI sei 数据
 @param userId 用户id
 @discussion 监听远端用户发送的 SEI 内容，通过 userId 区分。
 Added from 5.2.5
 
 @remarks 代理
 */
- (void)didReceiveSEI:(NSString *)SEI userId:(NSString *)userId;

/*!
 观众接收到合流 SEI 通知
 
 @param SEI sei 数据
 @discussion 观众角色订阅 liveStreams 后，该回调会接收以下两种类型的数据。
 1.mcu server 会主动通过该接口回调主播合流布局的信息 {"mcuRoomState":"xxx"}
 2.如果远端主播有发送 SEI，可以通过此回调接收数据。
 Added from 5.2.5
 
 @remarks 代理
 */
- (void)didReceiveLiveStreamSEI:(NSString *)SEI;

/*!
 接收到其他人发送到 room 里的消息
 
 @param message 消息体, 参考 IMLib 中 RCMessage
 @discussion
 接收到其他人发送到 room 里的消息
 
 @remarks 代理
 */
- (void)didReceiveMessage:(RCMessage *)message;

/*!
 如果用户调用 RCRTCEngine 的 setReconnectEnable 关闭 SDK 断线重连, 1分钟没有链接上信令服务器, SDK 会关闭音视频连接, 释放资源,
 将用户踢出房间, 回调通知用户
 
 @param room 离开的房间
 @discussion
 如果用户调用 RCRTCEngine 的 setReconnectEnable 关闭 SDK 断线重连, 1分钟没有链接上信令服务器, SDK 会关闭音视频连接, 释放资源,
 将用户踢出房间, 回调通知用户
 @deprecated from 5.1.0
 
 @remarks 代理
 */
- (void)didKickedOutOfTheRoom:(RCRTCRoom *)room
    DEPRECATED_MSG_ATTRIBUTE("use RCRTCEngineEventDelegate.h didKicked instead");

/*!
 被服务端踢下线通知
 
 @param room 离开的房间
 @discussion
 如果用户在房间内, 此时收到服务器封禁的通知, SDK 会关闭音视频连接, 释放资源,
 将用户踢出房间, 回调通知用户
 @deprecated from 5.1.0
 
 @remarks 代理
 */
- (void)didKickedByServer:(RCRTCBaseRoom *)room
    DEPRECATED_MSG_ATTRIBUTE("use RCRTCEngineEventDelegate.h didKicked instead");

/*!
 远端用户音频静默改变通知
 
 @param stream 流信息
 @param mute 当前流是否可用
 @discussion
 音频状态改变
 
 @remarks 代理
 */
- (void)stream:(RCRTCInputStream *)stream didAudioMute:(BOOL)mute;

/*!
 远端用户视频静默改变通知
 
 @param stream 流信息
 @param enable 当前流是否可用
 @discussion
 视频状态改变
 
 @remarks 代理
 */
- (void)stream:(RCRTCInputStream *)stream didVideoEnable:(BOOL)enable;

#pragma mark - 邀请跨房间连麦
/*!
 其他房间邀请人调用 RCRTCLocalUser 类中 requestJoinOtherRoom:userId:autoMix:extra:completion: 方法,
 定向发起连麦邀请后, 被邀请人收到的回调, 其他非被邀请人不会收到此回调
 
 @param inviterRoomId 邀请人所在房间号
 @param inviterUserId 邀请人的用户Id
 @param extra 自定义扩展信息, 邀请人发起邀请时填写的自定义扩展信息
 @discussion
 其他房间邀请人定向发起连麦邀请后, 被邀请人收到的回调, 其他非被邀请人不会收到此回调
 
 @remarks 代理
 */
- (void)didRequestJoinOtherRoom:(NSString *)inviterRoomId
                  inviterUserId:(nullable NSString *)inviterUserId
                          extra:(nullable NSString *)extra;

/*!
 其他房间邀请人调用 RCRTCLocalUser 类中 cancelRequestJoinOtherRoom:userId:extra:completion: 方法,
 取消之前发起的连麦邀请后, 被邀请人收到的回调, 其他非被邀请人不会收到此回调
 
 @param inviterRoomId 邀请人所在房间号
 @param inviterUserId 邀请人的用户Id
 @param extra 自定义扩展信息, 邀请人取消邀请时填写的自定义扩展信息
 @discussion
 其他房间邀请人取消之前发起的连麦邀请后, 被邀请人收到的回调, 其他非被邀请人不会收到此回调
 
 @remarks 代理
 */
- (void)didCancelRequestOtherRoom:(NSString *)inviterRoomId
                    inviterUserId:(nullable NSString *)inviterUserId
                            extra:(nullable NSString *)extra;

/*!
 被邀请人调用 RCRTCLocalUser 类中 responseJoinOtherRoom:userId:agree:autoMix:extra:completion: 方法,
 被邀请人应答同意连麦邀请后, 邀请人及其房间中其他非观众用户收到的回调
 被邀请人应答拒绝连麦邀请后, 只有邀请人收到的回调, 其他用户不会收到此回调
 
 @param inviterRoomId 邀请人所在房间号
 @param inviterUserId 邀请人的用户Id
 @param inviteeRoomId 被邀请人所在房间号
 @param inviteeUserId 被邀请人的用户Id
 @param agree 被邀请人同意/拒绝
 @param extra 自定义扩展信息, 被邀请人应答时填写的自定义扩展信息
 @discussion
 被邀请人应答同意连麦邀请后, 邀请人及其房间中其他非观众用户收到的回调
 被邀请人应答拒绝连麦邀请后, 只有邀请人收到的回调, 其他用户不会收到此回调
 
 @remarks 代理
 */
- (void)didResponseJoinOtherRoom:(nullable NSString *)inviterRoomId
                   inviterUserId:(nullable NSString *)inviterUserId
                   inviteeRoomId:(nullable NSString *)inviteeRoomId
                   inviteeUserId:(nullable NSString *)inviteeUserId
                           agree:(BOOL)agree
                           extra:(nullable NSString *)extra;

/*!
 结束连麦用户在调用  RCRTCEngine 类中 leaveOtherRoom:notifyFinished:completion: 方法时,
 如果将 notifyFinished 对应的参数填写为 YES, 正在跨房间连麦的所有用户将会收到此回调, 否则不会收到此回调
 
 @param roomId 结束连麦用户所在房间号
 @param userId 结束连麦用户Id
 @discussion
 结束连麦用户在调用 leaveOtherRoom:notifyFinished:completion: 方法时,
 如果将 notifyFinished 对应的参数填写为 YES, 正在跨房间连麦的所有用户将会收到此回调, 否则不会收到此回调
 
 @remarks 代理
 */
- (void)didFinishOtherRoom:(NSString *)roomId userId:(NSString *)userId;


@end

NS_ASSUME_NONNULL_END

#endif /* RongRTCRoomDelegate_h */
