//
//  RCRTCVideoViewEventDelegate.h
//  RongRTCLib
//
//  Created by RongCloud on 2021/11/9.
//  Copyright © 2021 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class RCRTCVideoStream;

/*!
 视频 view 代理
 @discussion
 added from 5.1.10
 */
@protocol RCRTCVideoViewEventDelegate <NSObject>

@optional

/*!
 首帧通知
 
 @param stream  视频流
 
 @discussion
 视频数据渲染第一帧的回调
 added from 5.1.11
 
 @remarks 代理
 */
- (void)didFirstFrameRendered:(RCRTCStream *)stream;

/*!
 远端视频尺寸大小改变通知
 
 @param size 视频尺寸
 @discussion
 当远端视频尺寸大小改变时，会进行回调通知
 @deprecated from 5.1.11
 
 @remarks 代理
 */
- (void)didVideoSizeChanged:(CGSize)size DEPRECATED_MSG_ATTRIBUTE("use RCRTCVideoInputStream.h RCRTCVideoInputStreamEventDelegate didFrameSizeChanged:width:height: API instead");

@end

NS_ASSUME_NONNULL_END
