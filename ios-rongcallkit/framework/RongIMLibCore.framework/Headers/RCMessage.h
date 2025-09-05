/**
 * Copyright (c) 2014-2015, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */

//  RCMessage.h
//  Created by Heq.Shinoda on 14-6-13.

#ifndef __RCMessage
#define __RCMessage

#import <Foundation/Foundation.h>

#import <RongIMLibCore/RCMessageContent.h>
#import <RongIMLibCore/RCReadReceiptInfo.h>
#import <RongIMLibCore/RCStatusDefine.h>
#import <RongIMLibCore/RCMessageConfig.h>
#import <RongIMLibCore/RCMessagePushConfig.h>
#import <RongIMLibCore/RCGroupReadReceiptInfoV2.h>

NS_ASSUME_NONNULL_BEGIN

@class RCReceivedStatusInfo;
@class RCMessageModifyInfo;

/// 消息实体类
///
/// 包含消息的所有属性。
@interface RCMessage : NSObject <NSCopying, NSCoding>

/// 会话类型
@property (nonatomic, assign) RCConversationType conversationType;

/// 会话 ID
@property (nonatomic, copy) NSString *targetId;

/// 所属会话的业务标识，长度限制 20 字符
@property (nonatomic, copy, nullable) NSString *channelId;

/// 消息的 ID
///
/// 本地存储的消息的唯一值（数据库索引唯一值）
@property (nonatomic, assign) long messageId;

/// 消息的方向
@property (nonatomic, assign) RCMessageDirection messageDirection;

/// 消息的发送者 ID
@property (nonatomic, copy, nullable) NSString *senderUserId;

/// 消息的接收状态类 (针对接收的消息生效)
/// - Since: 5.6.8
@property (nonatomic, strong) RCReceivedStatusInfo *receivedStatusInfo;

/// 消息的发送状态 (针对发送的消息生效)
@property (nonatomic, assign) RCSentStatus sentStatus;

/// 消息的接收时间（Unix 时间戳、毫秒）
@property (nonatomic, assign) long long receivedTime;

/// 消息的发送时间（Unix 时间戳、毫秒）
@property (nonatomic, assign) long long sentTime;

/// 消息的类型名
@property (nonatomic, copy, nullable) NSString *objectName;

/// 消息的内容
@property (nonatomic, strong, nullable) RCMessageContent *content;

/// 消息的附加字段
@property (nonatomic, copy, nullable) NSString *extra;

/// 全局唯一 ID
///
/// 服务器消息唯一 ID（在同一个 AppKey 下全局唯一）
@property (nonatomic, copy, nullable) NSString *messageUId;

/// 阅读回执状态
@property (nonatomic, strong, nullable) RCReadReceiptInfo *readReceiptInfo;

/// 群阅读回执状态
///
/// 如果是调用 RCGroupReadReceiptV2Manager 中方法实现群已读回执功能，此参数才有效，否则请使用 readReceiptInfo 属性获取阅读回执状态
/// 如果使用 IMKit，请用 readReceiptInfo 属性
@property (nonatomic, strong, nullable) RCGroupReadReceiptInfoV2 *groupReadReceiptInfoV2;

/// 群阅读回执状态
///
/// 如果开启了已读回执 V4 功能，此参数才有效，否则请使用 readReceiptInfo 属性获取阅读回执状态
/// 如果使用 IMKit，请用 readReceiptInfo 属性
@property (nonatomic, strong, nullable, readonly) RCReadReceiptInfoV4 *readReceiptInfoV4;


/// 消息配置
@property (nonatomic, strong) RCMessageConfig *messageConfig;

/// 消息推送配置
@property (nonatomic, strong) RCMessagePushConfig *messagePushConfig;

/// 是否是离线消息，只在接收消息的回调方法中有效，如果消息为离线消息，则为 YES，其他情况均为 NO
@property (nonatomic, assign) BOOL isOffLine;


/// 消息是否可以包含扩展信息
///
/// 该属性在消息发送时确定，发送之后不能再做修改
/// 扩展信息只支持单聊、群聊、超级群，其它会话类型不能设置扩展信息
@property (nonatomic, assign) BOOL canIncludeExpansion;

/// 消息扩展信息列表
///
/// 扩展信息只支持单聊、群聊、超级群，其它会话类型不能设置扩展信息
/// 默认消息扩展字典 key 长度不超过 32，value 长度不超过 4096，单次设置扩展数量最大为 20，消息的扩展总数不能超过 300
@property (nonatomic, strong, nullable) NSDictionary<NSString *, NSString *> *expansionDic;

/// 消息是否被修改
///
/// - Note: 从 5.26.0 开始，支持全部类型的消息变更状态。
@property (nonatomic, assign) BOOL hasChanged;

/// 消息修改信息。
///
/// @since 5.26.0
@property (nonatomic, readonly, strong) RCMessageModifyInfo *modifyInfo;

/// 消息已读回执操作标识。
///
/// - Since: 5.20.0
@property (nonatomic, assign) BOOL needReceipt;

/// 已读回执是否已发送。
///
/// - Since: 5.20.0
@property (nonatomic, assign) BOOL sentReceipt;

/// 接收定向消息的用户数组
///
/// @since 5.8.0
@property (nonatomic, copy, nullable) NSArray<NSString *> *directedUserIds;

/// 禁止更新到会话最新一条消息，默认 NO: 更新，YES: 不更新
///
/// @since 5.12.2
@property (nonatomic, assign) BOOL disableUpdateLastMessage;

/// RCMessage 初始化方法
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter messageDirection: 消息的方向
/// - Parameter content: 消息的内容
- (instancetype)initWithType:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
                   direction:(RCMessageDirection)messageDirection
                     content:(RCMessageContent *)content;

/// RCMessage 初始化方法，供超级群消息使用
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 频道 ID
/// - Parameter messageDirection: 消息的方向
/// - Parameter content: 消息的内容
- (instancetype)initWithType:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
                   channelId:(nullable NSString *)channelId
                   direction:(RCMessageDirection)messageDirection
                     content:(RCMessageContent *)content;

@end

@class RCMessageIdentifier;

@interface RCMessage (RCIdentifier)

/// 消息标识。
///
/// - Since: 5.22.0
- (RCMessageIdentifier *)messageIdentifier;

@end

NS_ASSUME_NONNULL_END

#endif
