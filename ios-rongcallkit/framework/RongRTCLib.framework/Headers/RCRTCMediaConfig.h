//
//  RCRTCMediaConfig.h
//  RongRTCLib
//
//  Created by RongCloud on 2020/2/13.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

@class RCRTCVideoConfig;
@class RCRTCAudioConfig;

NS_ASSUME_NONNULL_BEGIN

@interface RCRTCMediaConfig : NSObject

/*!
 视频配置
 */
@property (nonatomic, strong) RCRTCVideoConfig *videoConfig;

/*!
 音频配置
 */
@property (nonatomic, strong) RCRTCAudioConfig *audioConfig;

@end

NS_ASSUME_NONNULL_END
