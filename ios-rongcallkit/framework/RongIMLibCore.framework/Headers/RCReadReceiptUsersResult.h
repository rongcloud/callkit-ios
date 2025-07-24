//
//  RCReadReceiptUsersResult.h
//  RongIMLibCore
//
//  Created by shuai shao on 2025/4/25.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class RCReadReceiptUser;

/// 获取消息已读用户结果。
///
/// - Since: 5.20.0
@interface RCReadReceiptUsersResult : NSObject

/// 用户数据。
@property (nonatomic, copy, readonly) NSArray<RCReadReceiptUser *> *users;

/// 分页 Token，如果为空，则没有更多数据。
@property (nonatomic, copy, readonly, nullable) NSString *pageToken;

/// 总数。
@property (nonatomic, assign, readonly) NSInteger totalCount;

@end

NS_ASSUME_NONNULL_END
