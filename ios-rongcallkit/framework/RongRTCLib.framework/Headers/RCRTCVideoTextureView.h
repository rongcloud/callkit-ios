//
//  RCRTCVideoTextureView.h
//  RongRTCLib
//
//  Created by RongCloud on 2020/10/21.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import "RCRTCLibDefine.h"
#import "RCRTCDrawer.h"
NS_ASSUME_NONNULL_BEGIN

@protocol RCRTCVideoTextureViewDelegate <NSObject>

- (void)changeSize:(int)width height:(int)height;

- (void)changeRotation:(int)rotation;

- (void)firstFrameRendered;

- (void)frameRendered;

@end

@interface RCRTCVideoTextureView : NSObject <RCRTCDrawer>

@property (nonatomic, weak, nullable) id<RCRTCVideoTextureViewDelegate> textureViewDelegate;

- (CVPixelBufferRef)pixelBufferRef;

@end

NS_ASSUME_NONNULL_END
