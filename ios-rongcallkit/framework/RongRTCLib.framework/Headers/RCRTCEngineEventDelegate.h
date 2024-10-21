//
//  RCRTCEngineDelegate.h
//  RongRTCLib
//
//  Created by RongCloud on 2019/1/2.
//  Copyright © 2019 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RCRTCLibDefine.h"

@class RCRTCBaseRoom;

NS_ASSUME_NONNULL_BEGIN

/*!
 音视频引擎代理
 */
@protocol RCRTCEngineEventDelegate <NSObject>

@optional

/*!
 音频路由改变回调
 
 @remarks RCRTCEngineEventDelegate
 
 */
- (void)didAudioRouteChanged:(RCRTCAudioRouteType)audioRouteType;

/*!
 屏幕共享拓展 结束消息回调
 
 @remarks RCRTCEngineEventDelegate
 Added from 5.1.8
 */
- (void)screenShareExtentionFinished;

/*!
 屏幕共享拓展 开始消息回调
 
 @remarks RCRTCEngineEventDelegate
 @discussion
 需要先获取屏幕共享所需流 RCRTCEngine：RCRTCScreenShareOutputStream  get 接口
 Added from 5.2.0
 */
- (void)screenShareExtentionStarted;

/*!
 被 SDK 踢出房间通知
 
 @param roomId 离开的房间
 @param reason 被踢出房间原因
 @discussion
 如果用户在房间内, 此时由于某种原因被踢离开房间, SDK 会关闭音视频连接, 释放资源, 将用户踢出房间, 回调通知用户，
 如果用户不在房间内，roomId 为 nil，只释放资源，回调通知用户
 
 @remarks 代理
 */
- (void)didKicked:(nullable NSString *)roomId
           reason:(RCRTCKickedReason)reason;

/*!
 被 SDK 踢出房间通知
 
 @param roomId 离开的房间
 @param reason 被踢出房间原因
 @param extra Server API 自定义数据
 @discussion
 如果用户在房间内, 此时由于某种原因被踢离开房间, SDK 会关闭音视频连接, 释放资源, 将用户踢出房间, 回调通知用户，
 如果用户不在房间内，roomId 为 nil，只释放资源，回调通知用户
 
 @remarks 代理
 */
- (void)didKicked:(nullable NSString *)roomId
           reason:(RCRTCKickedReason)reason
            extra:(nullable NSDictionary *)extra;

- (void)didKicked:(nullable NSString *)roomId
           Reason:(RCRTCKickedReason)reason DEPRECATED_MSG_ATTRIBUTE("use didKicked:reason: instead");
/*!
 发生错误回调
 该回调方法表示 SDK 运行时出现了（网络或媒体相关的）错误。通常情况下，SDK 上报的错误意味着 SDK 无法自动恢复，需要 App 干预或提示用户。
 详细的错误代码，见 RCRTCCode。

 @param errorCode 具体返回数据参考 RCRTCCode 说明
 */
- (void)didOccurError:(RCRTCCode)errorCode;

/*!
 如果用户在房间内, RTC连接状态变化通知
 
 @param state 连接状态
 @discussion
 如果用户在房间内, RTC连接状态变化通知
 
 @remarks 代理
 */
- (void)didRTCConnectionStateChanged:(RCRTCConnectionState)state;
@end

NS_ASSUME_NONNULL_END
