//
//  RCStreamMessage.h
//  RongIMLibCore
//
//  Created by shuai shao on 2025/2/19.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <RongIMLibCore/RongIMLibCore.h>

NS_ASSUME_NONNULL_BEGIN

/// 流式消息的类型名。
#define RCStreamMessageTypeIdentifier @"RC:StreamMsg"

/// 流式消息扩展中的摘要 Key。
#define RCStreamMessageExpansionSummeryKey @"RC_Ext_StreamMsgSummary"

@interface RCReferenceInfo : NSObject

/// 被引用消息的发送者 ID。
@property (nonatomic, strong, readonly) NSString *senderId;

/// 被引用消息的 messageUId。服务器消息唯一 ID（在同一个 AppKey 下全局唯一）
@property (nonatomic, strong, readonly) NSString *messageUId;

/// 被引用消息的消息体。
@property (nonatomic, strong, readonly, nullable) RCMessageContent *content;

@end

@interface RCStreamMessage : RCMessageContent

/// 流式消息内容。
@property (nonatomic, copy, readonly) NSString *content;

/// 流式消息的文本格式。
@property (nonatomic, copy, readonly) NSString *type;

/// 流式消息内容是否结束生成。
@property (nonatomic, assign, readonly) BOOL isComplete;

/// 流式消息内容是异常结束的原因，为业务服务器下发。
@property (nonatomic, assign, readonly) NSInteger completeReason;

/// 流式消息内容是异常结束的原因，为融云服务器下发，0 为正常结束。
@property (nonatomic, assign, readonly) NSInteger stopReason;

/// 客户端是否完成流拉取标识。
@property (nonatomic, assign, readonly) BOOL isSync;

/// 流式消息引用的消息信息。
@property (nonatomic, strong, readonly, nullable) RCReferenceInfo *referMsg;

@end

NS_ASSUME_NONNULL_END
