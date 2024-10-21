//
//  RCRTCOutputStream.h
//  RongRTCLib
//
//  Created by RongCloud on 2019/1/8.
//  Copyright © 2019年 RongCloud. All rights reserved.
//

#import <CoreMedia/CoreMedia.h>
#import <Foundation/Foundation.h>

#import "RCRTCStream.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 本地输出音视频流
 */
@interface RCRTCOutputStream : RCRTCStream

/*!
 初始化
 
 @discussion
 初始化
 
 @warning
 请勿调用, 仅供 SDK 内部调用
 
 @remarks 资源管理
 @return RCRTCOutputStream 实例对象
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
 初始化
 
 @discussion
 初始化
 
 @warning
 请勿调用, 仅供 SDK 内部调用
 
 @remarks 资源管理
 @return RCRTCOutputStream 实例对象
 */
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
