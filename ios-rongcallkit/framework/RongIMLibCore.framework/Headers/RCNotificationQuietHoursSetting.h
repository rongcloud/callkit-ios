//
//  RCNotificationQuietHoursSetting.h
//  RongIMLibCore
//
//  Created by shuai shao on 2025/2/7.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

enum RCPushNotificationQuietHoursLevel : NSInteger;

/// 消息提醒屏蔽信息
/// - Since: 5.14.0
@interface RCNotificationQuietHoursSetting : NSObject

/// 开始时间。
@property (nonatomic, copy) NSString *startTime;
/// 分钟数，范围为 (0 , 1440)。
/// （比如，您设置的起始时间是 00:00，结束时间为 01:00，则 spanMins 为 60 分钟。设置为 1439 代表全天免打扰（23 * 60 + 59 = 1439））
@property (nonatomic, assign) int spanMins;
/// 消息通知级别。
@property (nonatomic, assign) enum RCPushNotificationQuietHoursLevel level;
/// 时区。
/// 国内数据中心默认  Asia/Shanghai，海外默认 UTC。
@property (nonatomic, copy, nullable) NSString *timezone;

@end

NS_ASSUME_NONNULL_END
