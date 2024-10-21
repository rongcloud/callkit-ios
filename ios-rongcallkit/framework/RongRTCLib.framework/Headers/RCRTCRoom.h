//
//  RCRTCRoom.h
//  RongRTCLib
//
//  Created by RongCloud on 2019/1/7.
//  Copyright © 2019 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RCRTCBaseRoom.h"
#import "RCRTCRoomEventDelegate.h"

NS_ASSUME_NONNULL_BEGIN

@class RCRTCLocalUser;
@class RCRTCCDNInputStream;

/*!
 音视频通话的房间
 */
@interface RCRTCRoom : RCRTCBaseRoom

/*!
 房间事件代理
 */
@property (nonatomic, weak, nullable) id<RCRTCRoomEventDelegate> delegate;

/*!
 当前用户
 */
@property (nonatomic, strong, readonly, nullable) RCRTCLocalUser *localUser;

/*!
 主房间中主播已经加入的副房间Id列表
 */
@property (nonatomic, strong, readonly) NSArray<NSString *> *otherRoomIdArray;

/*!
 远端音频数据（合流）回调
 */
@property (nonatomic, copy, nullable) RCRTCAudioDataCallback receivedAudioBufferCallback;

/*!
 设置所有远端用户是否静音
 
 @param mute 是否静音所有远端用户, YES 禁止  NO 允许
 @discussion
 将所有远端用户静音, 注: 该功能只是不播放接收到的音频数据
 
 @remarks 音频流处理
 */
- (void)muteAllRemoteAudio:(BOOL)mute;

/*!
 获取直播合流数组
 
 @discussion
 只要有主播就会存在, 房间内没有主播则为 空数组
 Added from 5.1.0
 
 @remarks 资源管理
 */
- (NSArray<RCRTCInputStream *> *)getLiveStreams;

/*!
 获取CDN流
 
 @discussion
 只要有房间有cdn流发布
 
 @remarks 资源管理
 */
- (nullable RCRTCCDNInputStream *)getCDNStream;

@end

NS_ASSUME_NONNULL_END
