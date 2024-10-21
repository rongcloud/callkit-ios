//
//  RCRTCVideoUnityView.h
//  RongRTCLib
//
//  Copyright © 2021 RongCloud. All rights reserved.
//

#import "RCRTCLibDefine.h"
#import "RCRTCDrawer.h"

NS_ASSUME_NONNULL_BEGIN

@interface RTCUnityVideoFrame : NSObject

@property (nonatomic, readonly) int width;
@property (nonatomic, readonly) int height;
@property (nonatomic, readonly, nullable) const uint8_t *dataY;
@property (nonatomic, readonly, nullable) const uint8_t *dataU;
@property (nonatomic, readonly, nullable) const uint8_t *dataV;
@property (nonatomic, readonly) int strideY;
@property (nonatomic, readonly) int strideU;
@property (nonatomic, readonly) int strideV;

- (void)clear;

@end

@interface RCRTCVideoUnityView : NSObject <RCRTCDrawer>

- (nullable RTCUnityVideoFrame *)getCurrentFrame;

- (NSInteger)getBufferLength;

@end

NS_ASSUME_NONNULL_END
