//
//  RCSubscribeUserOnlineStatus.h
//  RongIMLibCore
//
//  Created by huan xu on 2025/9/10.
//  Copyright © 2025 RongCloud. All rights reserved.

/// - Since: 5.28.0

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
@class RCPlatformOnlineStatus;
@interface RCSubscribeUserOnlineStatus : NSObject
/// 用户id
@property (nonatomic, copy) NSString *userId;
/// 平台信息
@property (nonatomic, copy) NSArray<RCPlatformOnlineStatus *> *details;
/// 是否在线，只要有一个 details 里面只要有一个平台在线，当前 isOnline = YES
@property (nonatomic, assign) BOOL isOnline;

@end

NS_ASSUME_NONNULL_END
