//
//  RCRTCStreamStat.h
//  RongRTCLib
//
//  Created by RongCloud on 2021/12/27.
//  Copyright © 2021 RongCloud. All rights reserved.
//

#import "RCRTCBaseStat.h"

NS_ASSUME_NONNULL_BEGIN

@interface RCRTCStreamStat : RCRTCBaseStat
/*!
 trackId
 */
@property (nonatomic, readonly) NSString *trackId DEPRECATED_MSG_ATTRIBUTE("use streamId property instead");

/*!
 流Id
 */
@property (nonatomic, readonly, nullable) NSString *streamId;

/*!
 用户Id
 */
@property (nonatomic, readonly, nullable) NSString *userId;

@end

NS_ASSUME_NONNULL_END
