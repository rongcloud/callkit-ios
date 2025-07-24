//
//  RCReadReceiptUser.h
//  RongIMLibCore
//
//  Created by shuai shao on 2025/4/15.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCUserInfo.h>

NS_ASSUME_NONNULL_BEGIN

/// 消息已读回执用户信息。
///
/// - Since: 5.20.0
@interface RCReadReceiptUser : NSObject

/// 用户 ID。
@property (nonatomic, copy, readonly) NSString *userId;

/// 该用户的阅读时间。0 表示用户没有发送已读回执。
@property (nonatomic, assign, readonly) long timestamp;

/// 是否被提醒的用户。
@property (nonatomic, assign, readonly) BOOL isMentioned;

@end

NS_ASSUME_NONNULL_END
