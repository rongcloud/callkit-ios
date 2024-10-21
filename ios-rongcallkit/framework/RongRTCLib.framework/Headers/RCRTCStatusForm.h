//
//  RCRTCStatusForm.h
//  RongRTCLib
//
//  Created by RongCloud on 2019/5/30.
//  Copyright © 2019 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RCRTCGlobals.h"
#import "RCRTCLibDefine.h"
#import "RCRTCStreamStat.h"

NS_ASSUME_NONNULL_BEGIN

RONGRTCLIB_EXTERN NSString *const RongRTCMediaTypeVideo;
RONGRTCLIB_EXTERN NSString *const RongRTCMediaTypeAudio;

typedef NS_ENUM(NSInteger, RongRTCStreamState) { Equivocal = -1, Disabled = 0, Enabled = 1 };

/*!
 sdk 状态统计表
 */
@interface RCRTCStatusForm : NSObject

/*!
 cpu 使用率
 */
@property (nonatomic, readonly) float cpuUsage;

/*!
 上行码率
 */
@property (nonatomic, readonly) float totalSendBitRate;

/*!
 下行码率
 */
@property (nonatomic, readonly) float totalRecvBitRate;

/*!
 系统 cpu 使用率
 */
@property (nonatomic, readonly) float cpuUsageOfOS;

/*!
 网络类型，wlan 4g
 */
@property (nonatomic, readonly, nullable) NSString *networkType;

/*!
 往返时间
 */
@property (nonatomic, readonly) NSInteger rtt;

/*!
 ip 地址
 */
@property (nonatomic, readonly, nullable) NSString *ipAddress;

/*!
 可接收带宽
 */
@property (nonatomic, readonly) NSInteger availableReceiveBandwidth;

/*!
 可发送带宽
 */
@property (nonatomic, readonly) NSInteger availableSendBandwidth;

/*!
 发送端丢包数
 */
@property (nonatomic, readonly) NSInteger packetsDiscardedOnSend;

/*!
 上行 媒体流状态统计 数组
 */
@property (nonatomic, readonly) NSArray<RCRTCStreamStat *> *sendStats;

/*!
 下行 媒体流状态统计 数组
 */
@property (nonatomic, readonly) NSArray<RCRTCStreamStat *> *recvStats;

/*!
 通过 trackId 查找到此 Track 所属的 UserId
 */
+ (NSString *)fetchUserIdFromTrackId:(NSString *)trackId
    DEPRECATED_MSG_ATTRIBUTE("use RCRTCStreamStat userId property instead");

@end

NS_ASSUME_NONNULL_END
