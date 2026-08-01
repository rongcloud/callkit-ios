//
//  RCMessageReactionUsageInfo.h
//  RongIMKit
//
//  Created by RC on 2026/6/2.
//  Copyright © 2026 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 常用消息回应统计信息。
///
/// - Since: 5.42.0
@interface RCMessageReactionUsageInfo : NSObject <NSCopying, NSSecureCoding>

/// 回应 ID。
@property (nonatomic, copy) NSString *reactionId;

/// 使用次数。
@property (nonatomic, assign) NSInteger useCount;

/// 最近使用时间，Unix 时间戳，单位毫秒。
@property (nonatomic, assign) long long lastUsedTime;

@end

NS_ASSUME_NONNULL_END
