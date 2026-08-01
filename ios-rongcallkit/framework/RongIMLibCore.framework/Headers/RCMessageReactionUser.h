//
//  RCMessageReactionUser.h
//  RongIMLibCore
//
//  Created by RC on 2026/6/1.
//  Copyright © 2026 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 消息回应用户信息。
///
/// - Since: 5.42.0
@interface RCMessageReactionUser : NSObject <NSCopying, NSCoding>

/// 用户 ID。
@property (nonatomic, copy) NSString *userId;

/// 回应时间，Unix 时间戳，单位毫秒。
@property (nonatomic, assign) long long reactionTime;

@end

NS_ASSUME_NONNULL_END
