//
//  RCRTCAudioConfig.h
//  RongRTCLib
//
//  Created by RongCloud on 2020/2/13.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCRTCAudioConfig : NSObject

/*!
 本地音频码率
 */
@property (nonatomic, assign) NSUInteger bitrate;

@end

NS_ASSUME_NONNULL_END
