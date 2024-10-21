//
//  RCRTCStream.h
//  RongRTCLib
//
//  Created by RongCloud on 2020/5/18.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "RCRTCLibDefine.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 音视频流
 */
@interface RCRTCStream : NSObject

/*!
 媒体流 ID
 */
@property (nonatomic, copy, readonly, nullable) NSString *streamId;

/*!
 媒体流类型
 */
@property (nonatomic, assign, readonly) RCRTCMediaStreamType mediaStreamType;

/*!
 媒体类型
 */
@property (nonatomic, assign, readonly) RCRTCMediaType mediaType;

/*!
 媒体流扩展标识符
 */
@property (nonatomic, copy, readonly, nullable) NSString *tag;

/*!
 媒体流所属的用户 ID
 */
@property (nonatomic, copy, readonly, nullable) NSString *userId;

/*!
 媒体流资源状态
 */
@property (nonatomic, assign, readonly) RCRTCResourceState resourceState;

/*!
 媒体流禁用状态
 注：
 1. 对于远端流（输入流），只是不解码视频与音频，但是音视频数据是正常接收的，如果不想接收数据可以进行取消订阅远端流
 2. 对于本地流（输出流），不编码和发送音视频数据，不影响采集。
 */
@property (nonatomic, assign, readwrite) BOOL isMute;

/*!
 初始化
 
 @discussion
 初始化
 
 @warning
 请勿调用, 仅供 SDK 内部调用
 
 @remarks 资源管理
 @return RCRTCStream 实例对象
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
 初始化
 
 @discussion
 初始化
 
 @warning
 请勿调用, 仅供 SDK 内部调用
 
 @remarks 资源管理
 @return RCRTCStream 实例对象
 */
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
