//
//  RCRTCDrawer.h
//  RongRTCLib
//
//  Created by RongCloud on 2021/11/24.
//  Copyright © 2021 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

@class RCRTCVideoFrame;

NS_ASSUME_NONNULL_BEGIN

@protocol RCRTCDrawer <NSObject>

/*!
 接收视频数据尺寸
 */
- (void)setSize:(CGSize)size;

/*!
 接收视频帧数据
 */
- (void)renderFrame:(nullable RCRTCVideoFrame *)frame;

@end

NS_ASSUME_NONNULL_END
