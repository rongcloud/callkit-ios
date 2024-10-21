//
//  RCLocalPreviewView.h
//  RongRTCLib
//
//  Created by RongCloud on 2018/12/17.
//  Copyright © 2018年 RongCloud. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import "RCRTCVideoPreviewView.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 ⚠️ RCRTCLocalVideoView 即将废弃 , 请使用RCRTCVideoView
 
 @discussion deprecated from 5.1.10
 */
__attribute__((deprecated("Class RCRTCLocalVideoView is deprecated , use Class RCRTCVideoView instead")))

@interface RCRTCLocalVideoView : RCRTCVideoPreviewView
/*!
 刷新渲染视图 View
 
 @discussion
 刷新渲染视图 View
 
 @remarks 视频配置
 */
- (void)flushVideoView DEPRECATED_MSG_ATTRIBUTE("Method flushVideoView is deprecated");

@end

NS_ASSUME_NONNULL_END
