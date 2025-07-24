//
//  RCConversationChannelProtocol.h
//  RongIMLibCore
//
//  Created by Sin on 2021/3/5.
//  Copyright © 2021 RongCloud. All rights reserved.
//

#ifndef RCConversationChannelProtocol_h
#define RCConversationChannelProtocol_h

#import <RongIMLibCore/RCUltraGroupChannelChangeInfo.h>

NS_ASSUME_NONNULL_BEGIN

@class RCUserTypingStatus;
@protocol RCConversationChannelMessageReceiptDelegate <NSObject>
@optional
/*!
 请求消息已读回执（收到需要阅读时发送回执的请求，收到此请求后在会话页面已经展示该 messageUId 对应的消息或者调用
 getHistoryMessages 获取消息的时候，包含此 messageUId 的消息，需要调用 sendMessageReadReceiptResponse
 接口发送消息阅读回执）

 - Parameter messageUId: 请求已读回执的消息ID
 - Parameter conversationType: conversationType
 - Parameter targetId: targetId
 - Parameter channelId: 所属会话的业务标识
 */
- (void)onMessageReceiptRequest:(RCConversationType)conversationType
                       targetId:(NSString *)targetId
                      channelId:(nullable NSString *)channelId
                     messageUId:(NSString *)messageUId;

/*!
 消息已读回执响应（收到阅读回执响应，可以按照 messageUId 更新消息的阅读数）
 - Parameter messageUId: 请求已读回执的消息ID
 - Parameter conversationType: conversationType
 - Parameter targetId: targetId
 - Parameter channelId: 所属会话的业务标识
 - Parameter userIdList: 已读userId列表
 */
- (void)onMessageReceiptResponse:(RCConversationType)conversationType
                        targetId:(NSString *)targetId
                       channelId:(nullable NSString *)channelId
                      messageUId:(NSString *)messageUId
                      readerList:(NSMutableDictionary *)userIdList;

@end

@protocol RCConversationChannelTypingStatusDelegate <NSObject>
/*!
 用户输入状态变化的回调

 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话目标ID
 - Parameter channelId: 所属会话的业务标识
 - Parameter userTypingStatusList: 正在输入的RCUserTypingStatus列表（nil表示当前没有用户正在输入）
 
 当客户端收到用户输入状态的变化时，会回调此接口，通知发生变化的会话以及当前正在输入的RCUserTypingStatus列表。
 */
- (void)onTypingStatusChanged:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                    channelId:(nullable NSString *)channelId
                       status:(nullable NSArray<RCUserTypingStatus *> *)userTypingStatusList;
@end

#pragma mark - 超级群会话代理

@protocol RCUltraGroupConversationDelegate <NSObject>

//超级群会话列表与会话最后一条消息同步完成
- (void)ultraGroupConversationListDidSync;
@end

@protocol RCUltraGroupChannelDelegate <NSObject>

/*!
 超级群类型变更通知
 1. 公有频道变私有频道时，公有频道所有用户会收到该通知
   a. 在私有频道白名单内的用户，收到的变更类型是 PublicToPrivate(公有频道变私有频道前，可以提前将用户加入私有频道白名单)
   b. 不在私有频道白名单的其他用户，变更类型为 PublicToPrivateUserNotIn

 2. 私有频道变公有频道时，私有频道白名单中的用户收到通知，变更类型为 PrivateToPublic

 - Parameter infoList: 频道变更信息
 
 当客户端收到频道变更时，会回调此接口，通知发生变化的会话频道列表。
 该功能仅支持超级群。
 */
- (void)ultraGroupChannelTypeDidChanged:(NSArray<RCUltraGroupChannelChangeTypeInfo *> *)infoList;

/*!
 频道白名单用户被移除通知(当前仅支持私有频道)
 1. 公有频道时，将用户从私有频道白名单移除时，不通知
 2. 私有频道时，将用户从白名单移除时，仅通知私有频道所有用户，含被踢的用户
 3. 清理本地数据
   a. 当被踢用户为当前用户时：用户本地会话删除，本地会话的消息保留
   b. 当被踢用户为其他人时：不做任何处理

 - Parameter infoList: 频道变更信息
 
 当客户端收到用户被移除频道时，会回调此接口，通知发生变化的会话频道列表。
 该功能仅支持超级群。
 */
- (void)ultraGroupChannelUserDidKicked:(NSArray<RCUltraGroupChannelUserKickedInfo *> *)infoList;


/*!
 删除频道通知，可以认为是频道解散。
 1. 公有频道时，删除频道通知频道中所有人
 2. 私有频道时，删除频道通知白名单中所有人
 3. 清理本地数据：用户本地会话删除，本地会话的消息保留

 - Parameter infoList: 频道变更信息
 
 当客户端收到频道解散时，会回调此接口，通知发生变化的会话频道列表。
 该功能仅支持超级群。
 */
- (void)ultraGroupChannelDidDisbanded:(NSArray<RCUltraGroupChannelDisbandedInfo *> *)infoList;


@end

NS_ASSUME_NONNULL_END

#endif /* RCConversationChannelProtocol_h */
