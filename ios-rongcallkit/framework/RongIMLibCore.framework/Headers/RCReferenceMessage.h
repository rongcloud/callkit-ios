//
//  RCReferenceMessage.h
//  RongIMLib
//
//  Created by 张改红 on 2020/2/26.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <RongIMLibCore/RongIMLibCore.h>
/// 引用消息的类型名
#define RCReferenceMessageTypeIdentifier @"RC:ReferenceMsg"

NS_ASSUME_NONNULL_BEGIN

/// 被引用消息的状态。
///
/// - Since: 5.26.0
typedef NS_ENUM(NSInteger, RCReferenceMessageStatus) {
    /// 默认状态。
    RCReferenceMessageStatusDefault = 0,
    /// 引用的消息被修改。
    RCReferenceMessageStatusModified = 1,
    /// 引用的消息被撤回。
    RCReferenceMessageStatusRecalled = 2,
    /// 引用的消息被删除。
    RCReferenceMessageStatusDeleted = 3,
};

/*!
引用消息类

引用消息类，此消息会进行存储并计入未读消息数。
 
- Remark: 内容类消息
*/
@interface RCReferenceMessage : RCMessageContent
/// 引用文本
@property (nonatomic, strong) NSString *content;
/// 被引用消息的发送者 ID
@property (nonatomic, strong) NSString *referMsgUserId;

/// 被引用消息体
@property (nonatomic, strong, nullable) RCMessageContent *referMsg;

/// 被引用消息的 messageUId。服务器消息唯一 ID（在同一个 AppKey 下全局唯一）
@property (nonatomic, strong) NSString *referMsgUid;

/// 被引用消息的状态。
///
/// - Since: 5.26.0
@property (nonatomic, assign) RCReferenceMessageStatus referMsgStatus;

@end

NS_ASSUME_NONNULL_END
