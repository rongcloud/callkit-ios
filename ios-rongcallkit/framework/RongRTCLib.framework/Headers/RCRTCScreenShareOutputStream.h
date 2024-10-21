//
//  RCRTCScreenShareOutputStream.h
//  RongRTCLib
//
//  Created by RongCloud on 2021/8/24.
//  Copyright © 2021 RongCloud. All rights reserved.
//

#import <RongRTCLib/RongRTCLib.h>

NS_ASSUME_NONNULL_BEGIN
/*
 Added from 5.1.8
 */
@interface RCRTCScreenShareOutputStream : RCRTCVideoOutputStream

/*!
 音频数据回调
 */
@property (nonatomic, copy, nullable) RCRTCAudioFrameCallback audioDataCallback;

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)new NS_UNAVAILABLE;

- (instancetype)initVideoOutputStreamWithTag:(NSString *)tag NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
