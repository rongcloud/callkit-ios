//
//  RCMessageReactionManager.h
//  RongIMKit
//
//  Created by RC on 2026/6/2.
//  Copyright © 2026 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RCMessageReactionUsageInfo.h"

NS_ASSUME_NONNULL_BEGIN

/// 消息回应管理器。
///
/// - Since: 5.42.0
@interface RCMessageReactionManager : NSObject

/// 获取消息回应管理器单例。
+ (instancetype)sharedManager;

/// 初始化指定本地存储 Key 的管理器，供测试使用。
- (instancetype)initWithStorageKey:(NSString *)storageKey;

/// 记录一次回应使用。
///
/// - Parameter reactionId: 回应 ID。
- (void)recordReactionUsage:(NSString *)reactionId;

/// 获取常用回应列表。
///
/// - Parameter count: 查询数量，`count <= 0` 返回空数组，`count > 20` 按 20 截断。
- (NSArray<RCMessageReactionUsageInfo *> *)getFrequentlyUsedReactionsWithCount:(NSInteger)count;

/// 清空测试实例的统计数据。
- (void)clearReactionUsageForTesting;

@end

NS_ASSUME_NONNULL_END
