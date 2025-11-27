//
//  RCChatRoomClient.h
//  RongIMLib
//
//  Created by 张改红 on 2020/7/28.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RongIMLibCore.h>
#import "RCChatRoomProtocol.h"
#import "RCChatRoomInfo.h"

NS_ASSUME_NONNULL_BEGIN

@class RCJoinChatRoomResponse;
@interface RCChatRoomClient : NSObject

+ (instancetype)sharedChatRoomClient;

#pragma mark - 聊天室操作

/*!
  加入聊天室（如果聊天室不存在则会创建）

 - Parameter targetId:        聊天室 ID，最大长度为 64 个字符
 - Parameter messageCount:    进入聊天室时获取历史消息的数量，-1 <= messageCount <= 50
 - Parameter extra:           附加信息，默认最大长度为 128 个字符，服务可配置
 - Parameter successBlock:    加入聊天室成功的回调
 - Parameter errorBlock:      加入聊天室失败的回调 [status: 加入聊天室失败的错误码]
 
 - Remark: 聊天室
 - Since: 5.10.2
 */
- (void)joinChatRoom:(NSString *)targetId
        messageCount:(int)messageCount
               extra:(nullable NSString *)extra
        successBlock:(nullable void (^)(RCJoinChatRoomResponse *response))successBlock
          errorBlock:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 加入已经存在的聊天室（如果聊天室不存在返回错误 23410，人数超限返回错误 23411）

 - Parameter targetId:        聊天室 ID，最大长度为 64 个字符
 - Parameter messageCount:    进入聊天室时获取历史消息的数量，-1 <= messageCount <= 50
 - Parameter successBlock:    加入聊天室成功的回调
 - Parameter errorBlock:      加入聊天室失败的回调 [status: 加入聊天室失败的错误码]
 
 - Remark: 聊天室
 - Since: 5.6.3
 */
- (void)joinExistChatRoom:(NSString *)targetId
             messageCount:(int)messageCount
             successBlock:(nullable void (^)(RCJoinChatRoomResponse *response))successBlock
               errorBlock:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 加入已经存在的聊天室（如果聊天室不存在返回错误 23410，人数超限返回错误 23411）

 - Parameter targetId:        聊天室 ID，最大长度为 64 个字符
 - Parameter messageCount:    进入聊天室时获取历史消息的数量，-1 <= messageCount <= 50
 - Parameter extra:           附加信息，最大长度为超过 128 个字符
 - Parameter successBlock:    加入聊天室成功的回调
 - Parameter errorBlock:      加入聊天室失败的回调 [status: 加入聊天室失败的错误码]
 
 - Remark: 聊天室
 - Since: 5.10.2
 */
- (void)joinExistChatRoom:(NSString *)targetId
             messageCount:(int)messageCount
                    extra:(nullable NSString *)extra
             successBlock:(nullable void (^)(RCJoinChatRoomResponse *response))successBlock
               errorBlock:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 退出聊天室

 - Parameter targetId:                聊天室 ID，最大长度为 64 个字符
 - Parameter successBlock:            退出聊天室成功的回调
 - Parameter errorBlock:              退出聊天室失败的回调 [status:退出聊天室失败的错误码]

 - Remark: 聊天室
 */
- (void)quitChatRoom:(NSString *)targetId
             success:(nullable void (^)(void))successBlock
               error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 退出聊天室

 - Parameter targetId:                聊天室 ID，最大长度为 64 个字符
 - Parameter extra:                   附加信息，默认最大长度为 128 个字符，服务可配置
 - Parameter successBlock:            退出聊天室成功的回调
 - Parameter errorBlock:              退出聊天室失败的回调 [status:退出聊天室失败的错误码]

 - Remark: 聊天室
 */
- (void)quitChatRoom:(NSString *)targetId
               extra:(nullable NSString *)extra
             success:(nullable void (^)(void))successBlock
               error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 获取聊天室的信息（包含部分成员信息和当前聊天室中的成员总数）

 - Parameter targetId:     聊天室 ID，最大长度为 64 个字符
 - Parameter count: 需要获取的成员信息的数量（目前获取到的聊天室信息中仅包含不多于 20 人的成员信息，即 0 <= count <=
 20，传入 0 获取到的聊天室信息将或仅包含成员总数，不包含具体的成员列表）
 - Parameter order:        需要获取的成员列表的顺序（最早加入或是最晚加入的部分成员）
 - Parameter successBlock: 获取成功的回调 [chatRoomInfo:聊天室信息]
 - Parameter errorBlock:   获取失败的回调 [status:获取失败的错误码]

  因为聊天室一般成员数量巨大，权衡效率和用户体验，目前返回的聊天室信息仅包含不多于 20 人的成员信息和当前成员总数。
 如果您使用 RC_ChatRoom_Member_Asc 升序方式查询，将返回最早加入的成员信息列表；
 如果您使用 RC_ChatRoom_Member_Desc 降序方式查询，将返回最晚加入的成员信息列表。
 上述两种方式查询，返回的成员列表都是按加入时间从旧到新。

 - Remark: 聊天室
 */
- (void)getChatRoomInfo:(NSString *)targetId
                  count:(int)count
                  order:(RCChatRoomMemberOrder)order
                success:(nullable void (^)(RCChatRoomInfo *chatRoomInfo))successBlock
                  error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 添加 IMLib 的聊天室状态监听器

 - Parameter delegate: IMLib 聊天室状态监听器
 */
- (void)addChatRoomStatusDelegate:(id<RCChatRoomStatusDelegate>)delegate NS_SWIFT_NAME(addChatRoomStatusDelegate(_:));

/*!
 移除 IMLib 的聊天室状态监听器

 - Parameter delegate: IMLib 聊天室状态监听器
 */
- (void)removeChatRoomStatusDelegate:(id<RCChatRoomStatusDelegate>)delegate
    NS_SWIFT_NAME(removeChatRoomStatusDelegate(_:));

/*!
 获取 IMLib 的聊天室状态监听器
 
 - Returns: 所有 IMLib 聊天室状态监听器
 */
- (NSArray<id<RCChatRoomStatusDelegate>> *)allChatRoomStatusDelegates;

/*!
 从服务器端获取聊天室的历史消息
 - Parameter targetId:            聊天室ID，最大长度为 64 个字符
 - Parameter recordTime:          起始的消息发送时间戳，毫秒
 - Parameter count:               需要获取的消息数量， 0 < count <= 200
 - Parameter order:               拉取顺序，RC_Timestamp_Desc:倒序，RC_Timestamp_ASC:正序
 - Parameter successBlock:        获取成功的回调 [messages:获取到的历史消息数组, syncTime:下次拉取消息的时间戳]
 - Parameter errorBlock:          获取失败的回调 [status:获取失败的错误码]

  此方法从服务器端获取聊天室的历史消息，但是必须先开通聊天室消息云存储功能。
 指定开始时间,比如2016年9月1日10点(1472695200000),
 默认是0(正序:从存储的第一条消息开始拉取,倒序:从存储的最后一条消息开始拉取)
 */
- (void)getRemoteChatroomHistoryMessages:(NSString *)targetId
                              recordTime:(long long)recordTime
                                   count:(int)count
                                   order:(RCTimestampOrder)order
                                 success:(nullable void (^)(NSArray<RCMessage *> *messages,
                                                            long long syncTime))successBlock
                                   error:(nullable void (^)(RCErrorCode status))errorBlock;

#pragma mark - 聊天室状态存储 (使用前必须先联系商务开通)

/*!
 添加聊天室 KV 状态变化监听

 - Parameter delegate: 代理
 */
- (void)addChatRoomKVStatusChangeDelegate:(id<RCChatRoomKVStatusChangeDelegate>)delegate
    NS_SWIFT_NAME(addChatRoomKVStatusChangeDelegate(_:));

/*!
 移除聊天室 KV 状态变化监听

 - Parameter delegate: 代理
 */
- (void)removeChatRoomKVStatusChangeDelegate:(id<RCChatRoomKVStatusChangeDelegate>)delegate
    NS_SWIFT_NAME(removeChatRoomKVStatusChangeDelegate(_:));

/*!
 获取聊天室 KV 状态变化监听
 
 - Returns: 所有聊天室 KV 状态变化的监听器
 */
- (NSArray<id<RCChatRoomKVStatusChangeDelegate>> *)allChatRoomKVStatusChangeDelegates;


/**
 设置聊天室自定义属性

 - Parameter chatroomId:   聊天室 ID，最大长度为 64 个字符
 - Parameter key: 聊天室属性名称，Key 支持大小写英文字母、数字、部分特殊符号 + = - _ 的组合方式，最大长度 128 个字符
 - Parameter value: 聊天室属性对应的值，最大长度 4096 个字符
 - Parameter sendNotification:   是否需要发送通知，如果发送通知，聊天室中的其他用户会接收到 RCChatroomKVNotificationMessage
 通知消息，消息内容中包含操作类型(type)、属性名称(key)、属性名称对应的值(value)和自定义字段(extra)
 - Parameter autoDelete:   用户掉线或退出时，是否自动删除该 Key、Value 值；自动删除时不会发送通知
 - Parameter notificationExtra:   通知的自定义字段，RC:chrmKVNotiMsg 通知消息中会包含此字段，最大长度 2 kb
 - Parameter successBlock: 成功回调
 - Parameter errorBlock:   失败回调

 必须先开通聊天室状态存储功能
 设置聊天室自定义属性，当 key 不存在时，代表增加属性； 当 key 已经存在时，代表更新属性的值，且只有 key
 的创建者可以更新属性的值。

 - Remark: 聊天室
 */
- (void)setChatRoomEntry:(NSString *)chatroomId
                     key:(NSString *)key
                   value:(NSString *)value
        sendNotification:(BOOL)sendNotification
              autoDelete:(BOOL)autoDelete
       notificationExtra:(nullable NSString *)notificationExtra
                 success:(nullable void (^)(void))successBlock
                   error:(nullable void (^)(RCErrorCode nErrorCode))errorBlock;

/**
 强制设置聊天室自定义属性

 - Parameter chatroomId:   聊天室 ID，最大长度为 64 个字符
 - Parameter key: 聊天室属性名称，Key 支持大小写英文字母、数字、部分特殊符号 + = - _ 的组合方式，最大长度 128 个字符
 - Parameter value: 聊天室属性对应的值，最大长度 4096 个字符
 - Parameter sendNotification:   是否需要发送通知，如果发送通知，聊天室中的其他用户会接收到 RCChatroomKVNotificationMessage
 通知消息，消息内容中包含操作类型(type)、属性名称(key)、属性名称对应的值(value)和自定义字段(extra)
 - Parameter autoDelete:   用户掉线或退出时，是否自动删除该 Key、Value 值；自动删除时不会发送通知
 - Parameter notificationExtra:   通知的自定义字段，RCChatroomKVNotificationMessage 通知消息中会包含此字段，最大长度 2 kb
 - Parameter successBlock: 成功回调
 - Parameter errorBlock:   失败回调

 必须先开通聊天室状态存储功能
 强制设置聊天室自定义属性，当 key 不存在时，代表增加属性； 当 key 已经存在时，代表更新属性的值。

 - Remark: 聊天室
 */
- (void)forceSetChatRoomEntry:(NSString *)chatroomId
                          key:(NSString *)key
                        value:(NSString *)value
             sendNotification:(BOOL)sendNotification
                   autoDelete:(BOOL)autoDelete
            notificationExtra:(nullable NSString *)notificationExtra
                      success:(nullable void (^)(void))successBlock
                        error:(nullable void (^)(RCErrorCode nErrorCode))errorBlock;

/**
 批量设置聊天室自定义属性

 - Parameter chatroomId:   聊天室 ID，最大长度为 64 个字符
 - Parameter entries:   聊天室属性，key 支持大小写英文字母、数字、部分特殊符号 + = - _ 的组合方式，最大长度 128 个字符，value 聊天室属性对应的值，最大长度 4096 个字符，最多一次设置 10 条
 - Parameter isForce:   是否强制覆盖
 - Parameter autoDelete:   用户掉线或退出时，是否自动删除该 Key、Value 值
 - Parameter successBlock: 成功回调
 - Parameter errorBlock:   失败回调，当 nErrorCode 为 RC_KV_STORE_NOT_ALL_SUCCESS（23428）的时候，entries 才会有值（key 为设置失败的 key，value 为该 key 对应的错误码）

 必须先开通聊天室状态存储功能
 
 - Remark: 聊天室
 */
- (void)setChatRoomEntries:(NSString *)chatroomId
                   entries:(NSDictionary<NSString *, NSString *> *)entries
                   isForce:(BOOL)isForce
                autoDelete:(BOOL)autoDelete
                   success:(nullable void (^)(void))successBlock
                     error:(nullable void (^)(RCErrorCode nErrorCode,
                                              NSDictionary<NSString *, NSNumber *> *failureEntries))errorBlock;

/**
 获取聊天室单个属性

 - Parameter chatroomId: 聊天室 ID，最大长度为 64 个字符
 - Parameter key: 聊天室属性名称
 - Parameter successBlock: 成功回调
 - Parameter errorBlock: 失败回调

 必须先开通聊天室状态存储功能

 - Remark: 聊天室
 */
- (void)getChatRoomEntry:(NSString *)chatroomId
                     key:(NSString *)key
                 success:(nullable void (^)(NSDictionary<NSString *, NSString *> *entry))successBlock
                   error:(nullable void (^)(RCErrorCode nErrorCode))errorBlock;

/**
 获取聊天室所有自定义属性

 - Parameter chatroomId: 聊天室 ID，最大长度为 64 个字符
 - Parameter successBlock: 成功回调
 - Parameter errorBlock: 失败回调

 必须先开通聊天室状态存储功能

 - Remark: 聊天室
 */
- (void)getAllChatRoomEntries:(NSString *)chatroomId
                      success:(nullable void (^)(NSDictionary<NSString *, NSString *> *entry))successBlock
                        error:(nullable void (^)(RCErrorCode nErrorCode))errorBlock;

/**
 删除聊天室自定义属性

 - Parameter chatroomId: 聊天室 ID，最大长度为 64 个字符
 - Parameter key: 聊天室属性名称
 - Parameter sendNotification:   是否需要发送通知，如果发送通知，聊天室中的其他用户会接收到 RCChatroomKVNotificationMessage
 通知消息，消息内容中包含操作类型(type)、属性名称(key)、属性名称对应的值(value)和自定义字段(extra)
 - Parameter notificationExtra:   通知的自定义字段，RCChatroomKVNotificationMessage 通知消息中会包含此字段，最大长度 2 kb
 - Parameter successBlock: 成功回调
 - Parameter errorBlock:   失败回调

 必须先开通聊天室状态存储功能
 删除聊天室自定义属性，只有自己设置的属性可以被删除。

 - Remark: 聊天室
 */
- (void)removeChatRoomEntry:(NSString *)chatroomId
                        key:(NSString *)key
           sendNotification:(BOOL)sendNotification
          notificationExtra:(nullable NSString *)notificationExtra
                    success:(nullable void (^)(void))successBlock
                      error:(nullable void (^)(RCErrorCode nErrorCode))errorBlock;

/**
 强制删除聊天室自定义属性

 - Parameter chatroomId: 聊天室 ID，最大长度为 64 个字符
 - Parameter key: 聊天室属性名称
 - Parameter sendNotification:   是否需要发送通知，如果发送通知，聊天室中的其他用户会接收到 RCChatroomKVNotificationMessage
 通知消息，消息内容中包含操作类型(type)、属性名称(key)、属性名称对应的值(value)和自定义字段(extra)
 - Parameter notificationExtra:   通知的自定义字段，RCChatroomKVNotificationMessage 通知消息中会包含此字段，最大长度 2 kb
 - Parameter successBlock: 成功回调
 - Parameter errorBlock:   失败回调

 必须先开通聊天室状态存储功能
 强制删除聊天室自定义属性。

 - Remark: 聊天室
 */
- (void)forceRemoveChatRoomEntry:(NSString *)chatroomId
                             key:(NSString *)key
                sendNotification:(BOOL)sendNotification
               notificationExtra:(nullable NSString *)notificationExtra
                         success:(nullable void (^)(void))successBlock
                           error:(nullable void (^)(RCErrorCode nErrorCode))errorBlock;

/**
 批量删除聊天室自定义属性

 - Parameter chatroomId:   聊天室 ID，最大长度为 64 个字符
 - Parameter keys:   聊天室属性名称，最多一次删除 10 条
 - Parameter isForce:   是否强制覆盖
 - Parameter successBlock: 成功回调
 - Parameter errorBlock:   失败回调，当 nErrorCode 为 RC_KV_STORE_NOT_ALL_SUCCESS（23428）的时候，entries 才会有值（key 为设置失败的 key，value 为该 key 对应的错误码）

 必须先开通聊天室状态存储功能
 
 - Remark: 聊天室
 */
- (void)removeChatRoomEntries:(NSString *)chatroomId
                         keys:(NSArray<NSString *> *)keys
                      isForce:(BOOL)isForce
                      success:(nullable void (^)(void))successBlock
                        error:(nullable void (^)(RCErrorCode nErrorCode,
                                                 NSDictionary<NSString *, NSNumber *> *failureEntries))errorBlock;

#pragma mark - 聊天室成员变化监听器

/*!
 设置聊天室成员变化的监听器

 可以设置并实现此拦截器来监听聊天室成员的加入或退出

 - Remark: 功能设置
 */
@property (nonatomic, weak, nullable) id<RCChatRoomMemberDelegate> memberDelegate;


/// 绑定聊天室 ID 和 RTCRoomID
/// - Parameter chatRoomId: 聊天室 ID，最大长度为 64 个字符
/// - Parameter rtcRoomId: rtc room ID
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
- (void)bindChatRoom:(NSString *)chatRoomId
         withRTCRoom:(NSString *)rtcRoomId
             success:(nullable void (^)(void))successBlock
               error:(nullable void (^)(RCErrorCode nErrorCode))errorBlock;

#pragma mark - 聊天室事件通知监听器

/**
 添加 IMLib 的聊天室事件通知监听器

 聊天室事件通知
 封禁、解封、禁言、解除禁言、多端同步相关事件等
 - Parameter delegate: IMLib 聊天室事件通知监听器
 
 - Since: 5.4.5
 */
- (void)addChatRoomNotifyEventDelegate:(id<RCChatRoomNotifyEventDelegate>)delegate
    NS_SWIFT_NAME(addChatRoomNotifyEventDelegate(_:));

/**
 移除 IMLib 的聊天室事件通知监听器

 - Parameter delegate: IMLib 聊天室事件通知监听器
 - Since: 5.4.5
 */
- (void)removeChatRoomNotifyEventDelegate:(id<RCChatRoomNotifyEventDelegate>)delegate
    NS_SWIFT_NAME(removeChatRoomNotifyEventDelegate(_:));

/**
 返回 IMLib 的聊天室事件通知监听器

 - Since: 5.4.5
 */
- (NSArray<id<RCChatRoomNotifyEventDelegate>> *)allChatRoomNotifyEventDelegates;


/// 是否允许聊天室消息排重，默认值为 YES
///
/// 排重的场景如下
/// 发送方弱网情况下发送消息，消息到达服务但发送方没有收到服务 ack，导致发送方认为消息发送失败
/// 此种情况下，服务端和接收方都会收到第一条消息
/// 此时发送方重发该消息，再次达到服务，那么此时服务端会有两条消息（消息内容相同，messageUid 不同）
/// 接收方会收到两条内容相同但 messageUid 不同的消息，SDK 此时会把第二条相同内容消息排重掉
/// 以此来保证重发的相同内容消息，发送方只有一条消息，接收方也只有一条消息
///
/// 当消息量少时，消息排重影响不大；但是本地存在大量消息时，排重会出现性能问题
/// 当 APP 本地存在大量消息，且发生收消息卡顿时，建议将排重关闭
/// 在初始化接口之后连接之前调用
///
/// - Parameter enableCheck: 是否允许聊天室消息排重
///
/// - Since: 5.8.2
- (void)setCheckChatRoomDuplicateMessage:(BOOL)enableCheck;

@end

NS_ASSUME_NONNULL_END
