//
//  RCGetUnreadMentionMeConversationListParams.h
//  RongIMLibCore
//
//  Created by RongCloud on 2025/9/5.
//  Copyright © 2025 RongCloud. All rights reserved.
// 
/// - Since: 5.28.0
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCGetUnreadMentionMeConversationListParams : NSObject
/// 支持的会话类型的数组 (需要将 RCConversationType 转为 NSNumber 构建 NSArray)
/// 支持单聊、群聊、系统、超级群会话类型
/// 非上述类型或者空数组，查询返回错误码 34284
@property (nonatomic, copy)NSArray<NSNumber *> *conversationTypes;

/// 是否置顶优先，传 YES 表示置顶会话优先返回，否则结果只以会话时间排序
/// 默认值为 YES
@property (nonatomic, assign)BOOL topPriority;

/// 查询的开始时间, 传 0 表示查询最新时间的会话，后续查询可传入 conversations 的最后一个元素的 conversation time 单位：毫秒
/// 默认值为 0，小于 0 则查询返回错误码 34202
@property (nonatomic, assign)long long timestamp;

/// 获取的数量，有效值范围 [1, 100] 默认值为 0，超过范围则查询返回错误码 34232
@property (nonatomic, assign)NSUInteger count;
@end

NS_ASSUME_NONNULL_END
