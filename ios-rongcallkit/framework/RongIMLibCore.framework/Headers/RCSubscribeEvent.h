//
//  RCSubscribeEvent.h
//  RongIMLibCore
//
//  Created by chinaspx on 2024/2/22.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCStatusDefine.h>

NS_ASSUME_NONNULL_BEGIN

/// 订阅类型枚举
typedef NS_ENUM(NSInteger, RCSubscribeType) {
    /// 订阅在线状态
    RCSubscribeTypeOnlineStatus = 1,
    /// 订阅用户信息变更
    ///
    /// - Since: 5.10.0
    RCSubscribeTypeUserProfile = 2,

    /// 好友在线状态（好友无需主动订阅）
    /// - Since:
    RCSubscribeTypeFriendOnlineStatus = 3,

    /// 好友用户信息变更（好友无需主动订阅）
    /// - Since:
    RCSubscribeTypeFriendUserProfile = 4,

    /// 无效枚举值，业务上不用
    RCSubscribeTypeInvalid
};

typedef NS_ENUM(NSInteger, RCSubscribeOperationType) {
    // 订阅
    RCSubscribeOperationTypeSubscribe = 0,
    // 取消订阅
    RCSubscribeOperationTypeUnSubscribe = 1
};

/// 订阅的事件
@interface RCSubscribeEvent : NSObject
/// 订阅用户 ID
@property (nonatomic, copy) NSString *userId;
/// 订阅类型
@property (nonatomic, assign) RCSubscribeType subscribeType;
/// 订阅操作类型
@property (nonatomic, assign) RCSubscribeOperationType operationType;
/// 订阅时间，unix 毫秒
@property (nonatomic, assign) long long subscribeTime;
/// 订阅有效时长，单位秒 [60s ~ 30 天]
@property (nonatomic, assign) NSInteger expiry;

@end

NS_ASSUME_NONNULL_END
