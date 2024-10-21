//
//  RCRTCLiveAudioStatus.h
//  RongRTCLib
//
//  Created by RongCloud on 2021/10/18.
//  Copyright © 2019 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCRTCLiveAudioStatus : NSObject

/*!
 用户Id
 */
@property (nonatomic, readonly, nullable) NSString *userId;

/*!
 流Id
 */
@property (nonatomic, readonly, nullable) NSString *streamId;

/*!
 音量大小, 0 - 9表示音量高低
 */
@property (nonatomic, readonly) NSInteger audioLevel;

@end

NS_ASSUME_NONNULL_END
