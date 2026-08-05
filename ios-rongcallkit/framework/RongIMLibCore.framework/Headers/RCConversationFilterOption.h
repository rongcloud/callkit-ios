//
//  RCConversationFilterOption.h
//  RongIMLibCore
//
//  Created by chinaspx on 2025/3/25.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <RongIMLibCore/RCStatusDefine.h>

NS_ASSUME_NONNULL_BEGIN

/// 会话类型过滤。
///
/// - Since: 5.20.0
@interface RCConversationTypeFilter : NSObject

/// 会话类型
@property (nonatomic, assign, readonly) RCConversationType type;

/// 频道 ID，有效值：包含 @"" 或有效字符串，无效值：nil 不包含 channelId 的条件查询
/// 单群聊未启用 channelId 传 nil，启用则传真实有效值
@property (nonatomic, copy, nullable) NSString *channelId;

/// 构造方法。
/// - Parameter type: 会话类型。
- (instancetype)initWithType:(RCConversationType)type;

@end

/// 会话列表参数配置。
///
/// - Since: 5.20.0
@interface RCConversationListOption : NSObject

/// 获取的数量，默认为 20。
/// 当实际取回的会话数量小于 count 值时，表明已取完数据。
@property (nonatomic, assign) NSInteger count;

/// 会话的时间戳，单位：毫秒。获取这个时间戳之前的会话列表，0 表示从最新开始获取。
@property (nonatomic, assign) long long startTime;

/// 查询结果的排序方式，是否置顶优先，传 YES 表示置顶会话优先返回，否则结果只以会话时间排序。
/// 默认为 YES。
@property (nonatomic, assign) BOOL topPriority;

@end

NS_ASSUME_NONNULL_END
