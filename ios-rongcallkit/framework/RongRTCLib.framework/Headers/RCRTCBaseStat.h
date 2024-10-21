//
//  RCRTCBaseStat.h
//  RongRTCLib
//
//  Created by RongCloud on 2021/12/27.
//  Copyright © 2021 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RCRTCLibDefine.h"

NS_ASSUME_NONNULL_BEGIN

@interface RCRTCBaseStat : NSObject

/*!
 媒体类型
 */
@property (nonatomic, readonly) NSString *mediaType;

/*!
 媒体流类型
 */
@property (nonatomic, readonly) RCRTCMediaStreamType mediaStreamType;

/*!
 音量大小, 0 - 9表示音量高低
 */
@property (nonatomic, readonly) NSInteger audioLevel;

/*!
 码率
 */
@property (nonatomic, readonly) float bitRate;

/*!
 丢包率
 */
@property (nonatomic, readonly) float packetLoss;

/*!
 视频帧宽度
 */
@property (nonatomic, readonly) NSInteger frameWidth;

/*!
 视频帧高度
 */
@property (nonatomic, readonly) NSInteger frameHeight;

/*!
 往返时间
 */
@property (nonatomic, readonly) NSInteger rtt;

/*!
 帧率
 */
@property (nonatomic, readonly) NSInteger frameRate;

/*!
 抖动
 */
@property (nonatomic, readonly) NSInteger jitterReceived;

/*!
 编码名称
 */
@property (nonatomic, readonly, nullable) NSString *codecName;

/*!
 渲染延时
 */
@property (nonatomic, readonly) NSInteger renderDelayMs;

/*!
 编解码器名称
 */
@property (nonatomic, readonly, nullable) NSString *codecImplementationName;

/*!
 nacks 数量
 */
@property (nonatomic, readonly) NSInteger googNacksReceived;

/*!
 统计格式化字符串
 */
@property (nonatomic, readonly) NSString *formString;

@end

NS_ASSUME_NONNULL_END
