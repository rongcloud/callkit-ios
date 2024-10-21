//
//  RCRTCCustomMixAudio.h
//  RongRTCLib
//
//  Created by RongCloud on 2020/2/13.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

@class RCRTCStream;

NS_ASSUME_NONNULL_BEGIN

@interface RCRTCCustomMixAudio : NSObject

/*!
 要进行混音的流，必须为音频流
 */
@property (nonatomic, strong, nullable) RCRTCStream *audioStream;

@end

NS_ASSUME_NONNULL_END
