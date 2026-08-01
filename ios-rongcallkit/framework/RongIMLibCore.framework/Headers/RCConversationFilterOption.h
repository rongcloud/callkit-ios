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

/// 会话列表未读数筛选条件。
///
/// 该筛选条件为单选，不支持组合；仅影响未读数筛选，不影响其他查询及排序条件。
typedef NS_ENUM(NSInteger, RCConversationUnreadCountFilter) {
    /// 不按未读状态筛选，返回符合其他查询条件的全部会话。
    RCConversationUnreadCountFilterAll = 0,

    /// 仅返回未读消息数大于 0 的会话，即 `unreadMessageCount > 0`。
    RCConversationUnreadCountFilterUnreadOnly = 1,

    /// 仅返回存在未读 @ 消息的会话，即 `mentionedCount > 0`。
    /// `mentionedCount` 包含 @ 我的消息和 @ 所有人的消息。
    RCConversationUnreadCountFilterMentionOnly = 2,

    /// 仅返回未读消息数等于 0 的会话，即 `unreadMessageCount == 0`。
    RCConversationUnreadCountFilterNoUnread = 3,
};

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

/// 未读数筛选条件，默认为 `RCConversationUnreadCountFilterAll`。
@property (nonatomic, assign) RCConversationUnreadCountFilter unreadCountFilter;

@end

NS_ASSUME_NONNULL_END
