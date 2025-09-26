//
//  RCPlatformOnlineStatus.h
//  RongIMLibCore
//
//  Created by huan xu on 2025/9/10.
//  Copyright © 2025 RongCloud. All rights reserved.

/// - Since: 5.28.0

#import <Foundation/Foundation.h>
#import "RCStatusDefine.h"

NS_ASSUME_NONNULL_BEGIN

@interface RCPlatformOnlineStatus : NSObject
/// 平台
@property (nonatomic, assign) RCPlatform platform;
/// 是否在线
@property (nonatomic, assign) BOOL isOnline;
/// 更新时间(毫秒时间戳)
@property (nonatomic, assign) long long updateTime;

@end

NS_ASSUME_NONNULL_END
