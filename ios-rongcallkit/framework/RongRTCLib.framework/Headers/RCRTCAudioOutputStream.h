//
//  RCRTCAudioOutputStream.h
//  RongRTCLib
//
//  Created by RongCloud on 2020/6/2.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import "RCRTCOutputStream.h"

NS_ASSUME_NONNULL_BEGIN

@interface RCRTCAudioOutputStream : RCRTCOutputStream

/*!
 初始化
 
 @discussion
 初始化
 
 @warning
 请勿调用, 仅供 SDK 内部调用
 
 @remarks 资源管理
 @return RCRTCAudioOutputStream 实例对象
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
 初始化
 
 @discussion
 初始化
 
 @warning
 请勿调用, 仅供 SDK 内部调用
 
 @remarks 资源管理
 @return RCRTCAudioOutputStream 实例对象
 */
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
