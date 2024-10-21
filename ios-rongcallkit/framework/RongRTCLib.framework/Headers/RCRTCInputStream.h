//
//  RongRTCInputStream.h
//  RongRTCLib
//
//  Created by RongCloud on 2019/1/7.
//  Copyright © 2019 RongCloud. All rights reserved.
//

#import <CoreVideo/CoreVideo.h>
#import <Foundation/Foundation.h>

#import "RCRTCLibDefine.h"
#import "RCRTCStream.h"

NS_ASSUME_NONNULL_BEGIN

@class RCRTCVideoView;
@class RCRTCVideoTextureView;
@class RCRTCInputStream;

/*!
 接收到的音视频流
 */
@interface RCRTCInputStream : RCRTCStream

/*!
 初始化
 
 @discussion
 初始化
 
 @warning
 请勿调用, 仅供 SDK 内部调用
 
 @remarks 资源管理
 @return RCRTCInputStream 实例对象
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
 初始化
 
 @discussion
 初始化
 
 @warning
 请勿调用, 仅供 SDK 内部调用
 
 @remarks 资源管理
 @return RCRTCInputStream 实例对象
 */
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
