//
//  RCSearchMessageParams.h
//  RongIMLibCore
//
//  Created by shuai shao on 2025/6/10.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCStatusDefine.h>

NS_ASSUME_NONNULL_BEGIN

/// 时间范围。
///
/// - Since: 5.22.0
@interface RCTimeRange : NSObject

/// 查询的开始时间戳，单位毫秒，默认为 0，范围为 [0, endTime)。
@property (nonatomic, assign) NSInteger startTime;

/// 查询的结束时间戳，单位毫秒，范围为 (startTime, Now()]。
/// 如果未赋值，或者赋值为 0，使用当前时间。
@property (nonatomic, assign) NSInteger endTime;

/// 初始化接口。
/// - Parameters:
///   - startTime: 开始时间。
///   - endTime: 结束时间。
- (instancetype)initWithStartTime:(NSInteger)startTime endTime:(NSInteger)endTime;

@end

/// 会话过滤。
///
/// - Since: 5.22.0
@interface RCConversationFilter : NSObject

/// 会话类型列表，过滤会话的类型。
@property (nonatomic, copy, nullable) NSArray<NSNumber *> *conversationTypes;

/// 会话 ID 列表，过滤会话的 ID。
@property (nonatomic, copy, nullable) NSArray<NSString *> *targetIds;

/// 频道 ID 列表，过滤频道的 ID。
@property (nonatomic, copy, nullable) NSArray<NSString *> *channelIds;

/// 初始化方法。
/// - Parameters:
///   - conversationTypes: 会话类型数组。
///   - targetIds: 会话 ID 数组。
///   - channelIds: 频道 ID 数组。
- (instancetype)initWithConversationTypes:(nullable NSArray<NSNumber *> *)conversationTypes
                                targetIds:(nullable NSArray<NSString *> *)targetIds
                               channelIds:(nullable NSArray<NSString *> *)channelIds;

@end

/// 消息过滤。
///
/// - Since: 5.22.0
@interface RCMessageFilter : NSObject

/// 消息发送者 ID 列表，过滤发送者 ID。
@property (nonatomic, copy, nullable) NSArray<NSString *> *senderIds;

/// 消息类型列表，过滤消息类型。
@property (nonatomic, copy, nullable) NSArray<NSString *> *objectNames;

/// 初始化方法。
/// - Parameters:
///   - conversationTypes: 会话类型数组。
///   - senderIds: 消息发送者 ID 数组。
///   - objectNames: 消息类型名字数组。
- (instancetype)initWithSenderIds:(nullable NSArray<NSString *> *)senderIds
                      objectNames:(nullable NSArray<NSString *> *)objectNames;

@end

/// 本地消息搜索参数。
///
/// ```
/// 查询时间轴：
/// 0--------startTime--------------------endTime---------Now()
/// 正序（order == RCOrderAscending）查询：
/// 0--------startTime|---->--------------endTime---------Now()
/// 倒序（order == RCOrderDescending）查询个数：
/// 0--------startTime--------------<----|endTime---------Now()
/// 倒序有位移 (offset) 查询：
/// 0--------startTime----------<----|----endTime---------Now()
/// ```
///
/// - Since: 5.22.0
@interface RCSearchMessageParams : NSObject

/// 搜索关键词。
@property (nonatomic, copy, nullable) NSString *keyword;

/// 查询个数，范围为 (0, 100]。
@property (nonatomic, assign) NSInteger limit;

/// 查询位移，默认为 0。
@property (nonatomic, assign) NSInteger offset;

/// 排序方式，默认为 `RCOrderDescending`。
@property (nonatomic, assign) RCOrder order;

/// 查询的时间范围。
@property (nonatomic, strong, nullable) RCTimeRange *timeRange;

/// 查询的会话条件。
@property (nonatomic, strong, nullable) RCConversationFilter *conversationFilter;

/// 查询的消息条件。
@property (nonatomic, strong, nullable) RCMessageFilter *messageFilter;

@end

NS_ASSUME_NONNULL_END
