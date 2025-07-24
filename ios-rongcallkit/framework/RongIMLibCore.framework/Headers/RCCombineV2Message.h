//
//  RCCombineV2Message.h
//  GlobalIMUIKit
//
//  Created by zgh on 2023/11/6.
//

#import <RongIMLibCore/RongIMLibCore.h>

NS_ASSUME_NONNULL_BEGIN

/// 合并转发消息的类型名
#define RCCombineV2MessageTypeIdentifier @"RC:CombineV2Msg"

@interface RCCombineV2Message : RCMediaMessageContent

/// 转发的消息会话类型（目前仅支持单聊和群聊）。
@property (nonatomic, assign, readonly) RCConversationType conversationType;

/// 转发的消息展示的缩略内容列表 (格式是发送者：缩略内容)。
@property (nonatomic, readonly) NSArray<NSString *> *summaryList;

/// 转发的全部消息的发送者名称列表（单聊是经过排重的，群聊是群组名称）。
@property (nonatomic, readonly) NSArray<NSString *> *nameList;

/// 被转发的消息条数。
@property (nonatomic, assign, readonly) NSUInteger msgNum;

/// 消息列表。当被转发的消息长度之和小于等于 12K 时才会有此字段，此时不会有 JsonMsgKey 字段。
/// [
///   {
///     "fromUserId":"uid_A",
///     "targetId":"group1",
///     "timestamp":1693382006578,
///     "objectName":"RC:TxtMsg",
///     "content":{
///       "content":"大家觉得这个怎么样？"
///     }
///   }
/// ]
@property (nonatomic, readonly, nullable) NSArray<NSDictionary<NSString *, id<NSCoding>> *> *msgList;

/// 合并转发的消息列表 Key。当被转发的消息长度之和大于 12K 时才会有此字段，此时不会有 msgList 字段。
@property (nonatomic, readonly, nullable) NSString *jsonMsgKey;


/// 初始化 RCCombineV2Message 消息
///
/// - Parameter summaryList: 转发的消息展示的缩略内容列表
/// - Parameter nameList: 转发的全部消息的发送者名称列表（单聊是经过排重的，群聊是群组名称）
/// - Parameter conversationType: 转发的消息会话类型
/// - Parameter msgList: 转发的消息体列表
///
/// - Returns: 消息实例对象
+ (instancetype)messageWithSummaryList:(NSArray<NSString *> *)summaryList
                              nameList:(NSArray<NSString *> *)nameList
                      conversationType:(RCConversationType)conversationType
                              messages:(NSArray<RCMessage *> *)messages;

@end

NS_ASSUME_NONNULL_END
