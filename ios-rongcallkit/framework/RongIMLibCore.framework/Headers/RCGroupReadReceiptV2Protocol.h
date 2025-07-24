//
//  RCGroupReadReceiptV2Protocol.h
//  RongIMLibCore
//
//  Created by 张改红 on 2021/3/9.
//  Copyright © 2021 RongCloud. All rights reserved.
//

#ifndef RCGroupReadReceiptV2Protocol_h
#define RCGroupReadReceiptV2Protocol_h

#import <RongIMLibCore/RCStatusDefine.h>

NS_ASSUME_NONNULL_BEGIN

@class RCMessage;

@protocol RCGroupReadReceiptV2Delegate <NSObject>

/*!
 消息已读回执响应（收到阅读回执响应，可以按照 messageUId 更新消息的阅读数）
 - Parameter conversationType: conversationType
 - Parameter targetId: targetId
 - Parameter channelId: 所属会话的业务标识
 - Parameter messageUId: 请求已读回执的消息ID
 - Parameter readCount: 已读用户数
 - Parameter totalCount: 群内总用户数
  */
- (void)onMessageReceiptResponse:(RCConversationType)conversationType
                        targetId:(NSString *)targetId
                       channelId:(nullable NSString *)channelId
                      messageUId:(NSString *)messageUId
                       readCount:(int)readCount
                      totalCount:(int)totalCount;

@end

@protocol RCReadReceiptV4Delegate <NSObject>

/// 私聊已读回执
/// - Parameters:
///   - conversationType: conversationType
///   - targetId: targetId
///   - channelId: 所属会话的业务标识
///   - readTime: 阅读时间
- (void)onPrivateMessageReceiptResponse:(RCConversationType)conversationType
                               targetId:(NSString *)targetId
                              channelId:(nullable NSString *)channelId
                               readTime:(long long)readTime;

/*!
 群组中消息发送方，当收到server的已读回执响应时，会回调此方法
 - Parameter conversationType: conversationType
 - Parameter targetId: targetId
 - Parameter channelId: 所属会话的业务标识
 - Parameter messageUId: 请求已读回执的消息ID
 - Parameter readCount: 已读用户数
 - Parameter totalCount: 群内总用户数
  */
- (void)onGroupMessageReceiptResponse:(RCConversationType)conversationType
                             targetId:(NSString *)targetId
                            channelId:(nullable NSString *)channelId
                           messageUId:(NSString *)messageUId
                            readCount:(int)readCount
                           totalCount:(int)totalCount;
@end

@protocol RCConversationChannelSyncConversationReadStatusDelegate <NSObject>


/// 同步会话已读状态代理:(与 RCLibDispatchReadReceiptNotification 通知等同)
/// - Parameters:
///   - message: 消息
///   - offline: 是否离线
- (void)onSyncConversationReadStatus:(RCMessage *)message offline:(BOOL)offline;


/// V4 同步已读状态
/// - Parameters:
///   - conversationType: 会话类型
///   - targetId: targetId
///   - channelId: channelId
///   - readTime: readTime
- (void)onSyncConversationReadTime:(RCConversationType)conversationType
                          targetId:(NSString *)targetId
                         channelId:(nullable NSString *)channelId
                          readTime:(long long)readTime;

@end

@class RCReadReceiptResponseV5;

/// 已读回执 V5 事件代理。
@protocol RCReadReceiptV5Delegate <NSObject>

@optional

/// 已读回执变更通知。
///
/// - Parameter responses: 消息已读回执信息。
///
/// - Since: 5.20.0
- (void)didReceiveMessageReadReceiptResponses:(NSArray<RCReadReceiptResponseV5 *> *)responses;

@end

NS_ASSUME_NONNULL_END

#endif /* RCGroupReadReceiptV2Protocol_h */
