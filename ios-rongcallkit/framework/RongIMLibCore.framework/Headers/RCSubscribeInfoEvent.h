//
//  RCSubscribeInfoEvent.h
//  RongIMLibCore
//
//  Created by chinaspx on 2024/4/8.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <RongIMLibCore/RCSubscribeEvent.h>

NS_ASSUME_NONNULL_BEGIN

@class RCSubscribeEventDetail;
@class RCUserProfile;

/// 订阅的状态信息事件（含状态信息）
@interface RCSubscribeInfoEvent : NSObject
/// 订阅用户 ID
@property (nonatomic, copy) NSString *userId;
/// 订阅类型
@property (nonatomic, assign) RCSubscribeType subscribeType;
/// 订阅时间，unix 毫秒
@property (nonatomic, assign) long long subscribeTime;
/// 订阅有效时长，单位秒 [60s ~ 30 天]
@property (nonatomic, assign) NSInteger expiry;
/// 订阅用户的状态信息
@property (nonatomic, strong, nullable) NSArray<RCSubscribeEventDetail *> *details;

/// 订阅用户的用户信息
///
/// - Since: 5.10.0
@property (nonatomic, strong, nullable) RCUserProfile *userProfile;

@end


@interface RCSubscribeEventDetail : NSObject
/// 订阅事件状态值 (0：离线，1：在线)
@property (nonatomic, assign) NSInteger eventValue;

/// 状态修改时间，unix 毫秒
@property (nonatomic, assign) long long changeTime;

/// 设备平台
@property (nonatomic, assign) RCPlatform platform;

@end
NS_ASSUME_NONNULL_END
