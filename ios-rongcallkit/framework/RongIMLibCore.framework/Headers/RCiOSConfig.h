//
//  RCiOSConfig.h
//  RongIMLib
//
//  Created by 孙浩 on 2020/9/17.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// iOS 推送级别常量
/// "passive" 被动通知：即并不需要及时关注的通知，类似餐馆推荐通知
/// "active"   主动通知（默认的）：默认的通知，即人们可能想知道的，类似最喜欢的体育比赛的最新比分
/// "time-sensitive" 时效性通知：需要人们立刻注意的通知，类似账户安全问题或快递动态
/// "critical" 重要通知：关于个人健康或直接影响到设备拥有者的公共安全事件且需要立刻关注的，这类通知很少，一般是来自公共政府机构或健康 App
static NSString *const kInterruptionLevel_passive = @"passive";
static NSString *const kInterruptionLevel_active = @"active";
static NSString *const kInterruptionLevel_time_sensitive = @"time-sensitive";
static NSString *const kInterruptionLevel_critical = @"critical";

@interface RCiOSConfig : NSObject

/// iOS 平台通知栏分组 ID
///
/// 相同的 thread-id 推送分为一组
///
/// iOS10 开始支持
@property (nonatomic, copy, nullable) NSString *threadId;

/// iOS 标识推送的类型
///
/// 如果不设置后台默认取消息类型字符串，如 RC:TxtMsg
@property (nonatomic, copy, nullable) NSString *category;

/// iOS 平台通知覆盖 ID
///
/// apnsCollapseId 相同时，新收到的通知会覆盖老的通知，最大 64 字节
///
/// iOS10 开始支持
@property (nonatomic, copy, nullable) NSString *apnsCollapseId;

/// iOS 富文本推送内容
@property (nonatomic, copy, nullable) NSString *richMediaUri;

/// iOS 推送级别。默认值 "active"
/// "passive" 被动通知：即并不需要及时关注的通知，类似餐馆推荐通知
/// "active"   主动通知（默认的）：默认的通知，即人们可能想知道的，类似最喜欢的体育比赛的最新比分
/// "time-sensitive" 时效性通知：需要人们立刻注意的通知，类似账户安全问题或快递动态
/// "critical" 重要通知：关于个人健康或直接影响到设备拥有者的公共安全事件且需要立刻关注的，这类通知很少，一般是来自公共政府机构或健康 App。
@property (nonatomic, copy) NSString *interruptionLevel;

@end

NS_ASSUME_NONNULL_END
