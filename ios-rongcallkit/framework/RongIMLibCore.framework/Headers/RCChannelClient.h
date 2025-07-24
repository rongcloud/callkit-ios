//
//  RCChannelClient.h
//  RongIMLibCore
//
//  Created by 张改红 on 2021/1/29.
//  Copyright © 2021 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCConversation.h>
#import <RongIMLibCore/RCMessage.h>
#import <RongIMLibCore/RCSearchConversationResult.h>
#import <RongIMLibCore/RCStatusDefine.h>
#import <RongIMLibCore/RCUploadMediaStatusListener.h>
#import <RongIMLibCore/RCUserInfo.h>
#import <RongIMLibCore/RCSendMessageOption.h>
#import <RongIMLibCore/RCRemoteHistoryMsgOption.h>
#import <RongIMLibCore/RCConversationChannelProtocol.h>
#import <RongIMLibCore/RCHistoryMessageOption.h>
#import <RongIMLibCore/RCConversationIdentifier.h>
#import <RongIMLibCore/RCIMClientProtocol.h>
#import <RongIMLibCore/RCMessageDigestInfo.h>
#import <RongIMLibCore/RCUserGroupStatusDelegate.h>
#import <RongIMLibCore/RCGroupMessageReaderV2.h>
#import <RongIMLibCore/RCConversationFilterOption.h>

NS_ASSUME_NONNULL_BEGIN

@class RCConversationUnreadInfo, RCClearMessageOption;
@class RCNotificationQuietHoursSetting;

/// 融云 ConversationChannel 核心类
///
/// 您需要通过 sharedChannelManager 方法，获取单例对象。
@interface RCChannelClient : NSObject

/// 获取核心类单例
///
/// - Returns: 核心单例类
/// - Since: 5.1.1
+ (instancetype)sharedChannelManager;

#pragma mark 代理

/// 设置消息已读回执监听器
///
/// - Parameter delegate: RCChannelClient 消息已读回执监听器
///
/// - Remark: 功能设置
/// - Since: 5.1.1
- (void)setChannelMessageReceiptDelegate:(nullable id<RCConversationChannelMessageReceiptDelegate>)delegate;


/// 设置输入状态的监听器
///
/// - Parameter delegate: RCChannelClient 输入状态的的监听器
///
/// - Warning: 目前仅支持单聊。
///
/// - Remark: 功能设置
/// - Since: 5.1.1
- (void)setRCConversationChannelTypingStatusDelegate:(nullable id<RCConversationChannelTypingStatusDelegate>)delegate;

/// 设置超级群输入状态的监听器
///
/// - Parameter delegate: RCChannelClient 输入状态的的监听器
///
/// 此方法只支持超级群的会话类型。
/// - Remark: 超级群
/// - Since: 5.2.0
- (void)setRCUltraGroupTypingStatusDelegate:(nullable id<RCUltraGroupTypingStatusDelegate>)delegate;

/// 设置超级群已读时间回调监听器
///
/// - Parameter delegate: 超级群已读时间回调监听器
///
/// 此方法只支持超级群的会话类型。
/// - Remark: 超级群
/// - Since: 5.2.0
- (void)setRCUltraGroupReadTimeDelegate:(nullable id<RCUltraGroupReadTimeDelegate>)delegate;

/// 设置超级群消息处理监听器
///
/// - Parameter delegate: 超级群消息处理回调监听器
///
/// 此方法只支持超级群的会话类型。
/// - Remark: 超级群
/// - Since: 5.2.0
- (void)setRCUltraGroupMessageChangeDelegate:(nullable id<RCUltraGroupMessageChangeDelegate>)delegate;

#pragma mark 消息发送

/// 异步发送消息
///
/// - Parameter conversationType: 发送消息的会话类型
/// - Parameter targetId: 发送消息的会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter content: 消息的内容
/// - Parameter pushContent: 接收方离线时需要显示的远程推送内容
/// - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter option: 消息的相关配置
/// - Parameter attachedBlock: 入库回调 [message: 已存数据库的消息体]
/// - Parameter successBlock: 消息发送成功的回调 [messageId: 消息的 ID]
/// - Parameter errorBlock: 消息发送失败的回调 [nErrorCode: 发送失败的错误码，
/// messageId: 消息的 ID]
///
/// 当接收方离线并允许远程推送时，会收到远程推送。
/// 远程推送中包含两部分内容，一是 pushContent，用于显示；二是 pushData，用于携带不显示的数据。
///
/// SDK 内置的消息类型，如果您将 pushContent 和 pushData 置为 nil，会使用默认的推送格式进行远程推送。
/// 自定义类型的消息，需要您自己设置 pushContent 来定义推送内容，否则将不会进行远程推送。
///
/// 如果您使用此方法发送媒体类型消息（如图片消息），需要您自己实现媒体文件的上传，构建一个媒体消息对象（如图片消息对象 RCImageMessage），并将媒体消息对象的 remoteUrl 字段设置为上传成功的 URL 地址，然后使用此方法发送。
///
/// - Warning: 使用此方法发送消息，不会自动更新 UI。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)sendMessage:(RCConversationType)conversationType
           targetId:(NSString *)targetId
          channelId:(nullable NSString *)channelId
            content:(RCMessageContent *)content
        pushContent:(nullable NSString *)pushContent
           pushData:(nullable NSString *)pushData
             option:(nullable RCSendMessageOption *)option
           attached:(nullable void (^)(RCMessage *_Nullable message))attachedBlock
            success:(nullable void (^)(long messageId))successBlock
              error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock;

/// 异步发送媒体消息（图片消息或文件消息）
///
/// - Parameter conversationType: 发送消息的会话类型
/// - Parameter targetId: 发送消息的会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter content: 消息的内容
/// - Parameter pushContent: 接收方离线时需要显示的远程推送内容
/// - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter attachedBlock: 入库回调 [message: 已存数据库的消息体]
/// - Parameter progressBlock: 消息发送进度更新的回调 [progress:当前的发送进度，0
/// <= progress <= 100, messageId:消息的 ID]
/// - Parameter successBlock: 消息发送成功的回调 [messageId:消息的 ID]
/// - Parameter errorBlock: 消息发送失败的回调 [errorCode:发送失败的错误码，
/// messageId:消息的 ID]
/// - Parameter cancelBlock: 用户取消了消息发送的回调 [messageId:消息的 ID]
///
/// 当接收方离线并允许远程推送时，会收到远程推送。
/// 远程推送中包含两部分内容，一是 pushContent，用于显示；二是 pushData，用于携带不显示的数据。
///
/// SDK 内置的消息类型，如果您将 pushContent 和 pushData 置为 nil，会使用默认的推送格式进行远程推送。
/// 自定义类型的消息，需要您自己设置 pushContent 来定义推送内容，否则将不会进行远程推送。
///
/// 如果您使用 IMLibCore 上传媒体文件的文件到自己服务器，需要构建一个媒体消息对象（如图片消息对象 RCImageMessage），并将媒体消息对象的 remoteUrl 字段设置为上传成功的 URL 地址，然后使用 [RCChannelClient sendMessage:targetId:channelId:content:pushContent:pushData:option:attached:success:error:] 方法发送。
///
/// - Warning: 使用此方法发送媒体消息，不会自动更新 UI。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)sendMediaMessage:(RCConversationType)conversationType
                targetId:(NSString *)targetId
               channelId:(nullable NSString *)channelId
                 content:(RCMessageContent *)content
             pushContent:(nullable NSString *)pushContent
                pushData:(nullable NSString *)pushData
                attached:(nullable void (^)(RCMessage *_Nullable message))attachedBlock
                progress:(nullable void (^)(int progress, long messageId))progressBlock
                 success:(nullable void (^)(long messageId))successBlock
                   error:(nullable void (^)(RCErrorCode errorCode, long messageId))errorBlock
                  cancel:(nullable void (^)(long messageId))cancelBlock;

/// 异步发送媒体消息 (上传图片或文件等媒体信息到指定的服务器)
///
/// - Parameter conversationType: 发送消息的会话类型
/// - Parameter targetId: 发送消息的会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter content: 消息的内容
/// - Parameter pushContent: 接收方离线时需要显示的远程推送内容
/// - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter attachedBlock: 入库回调 [message: 已存数据库的消息体]
/// - Parameter uploadPrepareBlock: 媒体文件上传进度更新的监听 [uploadListener:当前的发送进度监听]
/// - Parameter progressBlock: 消息发送进度更新的回调 [progress:当前的发送进度，0
/// <= progress <= 100, messageId:消息的 ID]
/// - Parameter successBlock: 消息发送成功的回调 [messageId:消息的 ID]
/// - Parameter errorBlock: 消息发送失败的回调 [errorCode:发送失败的错误码，
/// messageId:消息的 ID]
/// - Parameter cancelBlock: 用户取消了消息发送的回调 [messageId:消息的 ID]
///
/// 当接收方离线并允许远程推送时，会收到远程推送。
/// 远程推送中包含两部分内容，一是 pushContent，用于显示；二是 pushData，用于携带不显示的数据。
///
/// SDK 内置的消息类型，如果您将 pushContent 和 pushData 置为 nil，会使用默认的推送格式进行远程推送。
/// 自定义类型的消息，需要您自己设置 pushContent 来定义推送内容，否则将不会进行远程推送。
///
/// 如果您使用 IMLibCore 上传媒体文件的文件到自己服务器，需要构建一个媒体消息对象（如图片消息对象 RCImageMessage），并将媒体消息对象的 remoteUrl 字段设置为上传成功的 URL 地址，然后使用 [RCChannelClient sendMessage:targetId:channelId:content:pushContent:pushData:option:attached:success:error:] 方法发送。
///
/// - Warning: 使用此方法发送媒体消息，不会自动更新 UI。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)sendMediaMessage:(RCConversationType)conversationType
                targetId:(NSString *)targetId
               channelId:(nullable NSString *)channelId
                 content:(RCMessageContent *)content
             pushContent:(nullable NSString *)pushContent
                pushData:(nullable NSString *)pushData
                attached:(nullable void (^)(RCMessage *_Nullable message))attachedBlock
           uploadPrepare:(nullable void (^)(RCUploadMediaStatusListener *uploadListener))uploadPrepareBlock
                progress:(nullable void (^)(int progress, long messageId))progressBlock
                 success:(nullable void (^)(long messageId))successBlock
                   error:(nullable void (^)(RCErrorCode errorCode, long messageId))errorBlock
                  cancel:(nullable void (^)(long messageId))cancelBlock;

/// 异步插入向外发送的、指定时间的消息（此方法如果 sentTime 有问题会影响消息排序，慎用！！）
/// （该消息只插入本地数据库，实际不会发送给服务器和对方）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter canIncludeExpansion: 是否支持扩展
/// - Parameter sentStatus: 发送状态
/// - Parameter content: 消息的内容
/// - Parameter sentTime: 消息发送的 Unix 时间戳，单位：毫秒（传 0 会按照本地时间插入）
/// - Parameter completion: 异步回调 [发送的消息实体]
///
/// - Note: 如果 sentTime <= 0，则被忽略，会以插入时的时间为准。
/// - Remark: 消息操作
/// - Since: 5.3.1
- (void)insertOutgoingMessage:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                    channelId:(nullable NSString *)channelId
          canIncludeExpansion:(BOOL)canIncludeExpansion
                   sentStatus:(RCSentStatus)sentStatus
                      content:(RCMessageContent *)content
                     sentTime:(long long)sentTime
                   completion:(nullable void (^)(RCMessage *_Nullable message))completion;

/// 异步插入接收的消息（此方法如果 sentTime
/// 有问题会影响消息排序，慎用！！）（该消息只插入本地数据库，实际不会发送给服务器和对方）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter senderUserId: 发送者 ID
/// - Parameter receivedStatusInfo: 消息接收状态的 RCReceivedStatusInfo 对象
/// - Parameter content: 消息的内容
/// - Parameter sentTime: 消息发送的 Unix 时间戳，单位：毫秒（传 0 会按照本地时间插入）
/// - Parameter completion: 异步回调 [插入的消息实体]
///
/// - Note: 如果 sentTime <= 0，则被忽略，会以插入时的时间为准。
/// - Note: 新接口使用 RCReceivedStatusInfo 类来记录已读、已下载、已听等状态，通过按位计算的方式，支持多种状态并存；可以通过 RCReceivedStatusInfo 对外接口直接获取是否已读/已下载/已听等
/// - Warning: 新、旧接口原则上不混用，否则接收状态可能出现偏差
/// - Remark: 消息操作
/// - Since: 5.6.8
- (void)insertIncomingMessage:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                    channelId:(nullable NSString *)channelId
                 senderUserId:(NSString *)senderUserId
           receivedStatusInfo:(RCReceivedStatusInfo *)receivedStatusInfo
                      content:(RCMessageContent *)content
                     sentTime:(long long)sentTime
                   completion:(nullable void (^)(RCMessage *_Nullable message))completion;

/// 异步发送定向消息
///
/// - Parameter conversationType: 发送消息的会话类型
/// - Parameter targetId: 发送消息的会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter userIdList: 接收消息的用户 ID 列表 [个数不能超过 300，超过会被截断]
/// - Parameter content: 消息的内容
/// - Parameter pushContent: 接收方离线时需要显示的远程推送内容
/// - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter option: 消息的相关配置
/// - Parameter attachedBlock: 入库回调 [message: 已存数据库的消息体]
/// - Parameter successBlock: 消息发送成功的回调 [messageId:消息的 ID]
/// - Parameter errorBlock: 消息发送失败的回调 [errorCode:发送失败的错误码，
/// messageId:消息的 ID]
///
/// 此方法用于在群组和讨论组中发送消息给其中的部分用户，其它用户不会收到这条消息。
/// 使用此方法发送定向消息，不会自动更新 UI。
///
/// - Warning: 此方法目前仅支持普通群组和讨论组。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)sendDirectionalMessage:(RCConversationType)conversationType
                      targetId:(NSString *)targetId
                     channelId:(nullable NSString *)channelId
                  toUserIdList:(NSArray<NSString *> *)userIdList
                       content:(RCMessageContent *)content
                   pushContent:(nullable NSString *)pushContent
                      pushData:(nullable NSString *)pushData
                        option:(nullable RCSendMessageOption *)option
                      attached:(nullable void (^)(RCMessage *_Nullable message))attachedBlock
                       success:(nullable void (^)(long messageId))successBlock
                         error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock;

#pragma mark - 消息阅读回执 -

/// 发送某个会话中消息阅读的回执
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter timestamp: 该会话中已阅读的最后一条消息的发送时间戳，单位：毫秒
/// - Parameter successBlock: 发送成功的回调
/// - Parameter errorBlock: 发送失败的回调 [nErrorCode: 失败的错误码]
///
/// 此接口只支持单聊，如果使用 IMLibCore 可以注册监听
/// RCLibDispatchReadReceiptNotification 通知，使用 IMKit 直接设置 RCIM.h
/// 中的 enabledReadReceiptConversationTypeList。
///
/// - Warning: 目前仅支持单聊。
///
/// - Remark: 高级功能
/// - Since: 5.1.1
- (void)sendReadReceiptMessage:(RCConversationType)conversationType
                      targetId:(NSString *)targetId
                     channelId:(nullable NSString *)channelId
                          time:(long long)timestamp
                       success:(nullable void (^)(void))successBlock
                         error:(nullable void (^)(RCErrorCode nErrorCode))errorBlock;

/// 发送阅读回执
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter messageList: 已经阅读了的消息列表
/// - Parameter successBlock: 发送成功的回调
/// - Parameter errorBlock: 发送失败的回调 [nErrorCode: 失败的错误码]
///
/// 当用户阅读了需要阅读回执的消息，可以通过此接口发送阅读回执，消息的发送方即可直接知道哪些人已经阅读。
///
/// - Remark: 高级功能
/// - Since: 5.1.1
- (void)sendReadReceiptResponse:(RCConversationType)conversationType
                       targetId:(NSString *)targetId
                      channelId:(nullable NSString *)channelId
                    messageList:(NSArray<RCMessage *> *)messageList
                        success:(nullable void (^)(void))successBlock
                          error:(nullable void (^)(RCErrorCode nErrorCode))errorBlock;

/// 同步会话阅读状态（把指定会话里所有发送时间早于 timestamp 的消息置为已读）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter timestamp: 已经阅读的最后一条消息的 Unix 时间戳，单位：毫秒
/// - Parameter successBlock: 同步成功的回调
/// - Parameter errorBlock: 同步失败的回调 [nErrorCode: 失败的错误码]
///
/// 此方法不支持超级群的会话类型。
///
/// - Remark: 高级功能
/// - Since: 5.1.1
- (void)syncConversationReadStatus:(RCConversationType)conversationType
                          targetId:(NSString *)targetId
                         channelId:(nullable NSString *)channelId
                              time:(long long)timestamp
                           success:(nullable void (^)(void))successBlock
                             error:(nullable void (^)(RCErrorCode nErrorCode))errorBlock;

/// 上报超级群的已读时间
///
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter timestamp: 已读时间，传入最后一条消息的 sentTime，单位：毫秒
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// 此方法只支持超级群的会话类型。
/// - Remark: 超级群
/// - Since: 5.2.0
- (void)syncUltraGroupReadStatus:(NSString *)targetId
                       channelId:(nullable NSString *)channelId
                            time:(long long)timestamp
                         success:(nullable void (^)(void))successBlock
                           error:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 同步服务端会话阅读状态（把指定会话里所有发送时间早于 timestamp 的消息置为已读）
///
/// - Parameter conversationIdentifier: 会话信息
/// - Parameter timestamp: 已经阅读的最后一条消息的 Unix 时间戳 (毫秒)
/// - Parameter successBlock: 同步成功的回调
/// - Parameter errorBlock: 同步失败的回调 [nErrorCode: 失败的错误码]
///
/// - Remark: 高级功能
/// - Since: 5.12.3
- (void)setReadTimestamp:(RCConversationIdentifier *)conversationIdentifier
               timestamp:(long long)timestamp
                 success:(nullable void (^)(void))successBlock
                   error:(nullable void (^)(RCErrorCode errorcode))errorBlock;
#pragma mark - 消息操作

/// 异步获取某个会话中指定数量的最新消息实体（按照时间从新到旧排列）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter count: 需要获取的消息数量
/// - Parameter completion: 异步回调 [消息实体 RCMessage 对象列表]
///
/// 此方法不支持超级群的会话类型。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)getLatestMessages:(RCConversationType)conversationType
                 targetId:(NSString *)targetId
                channelId:(nullable NSString *)channelId
                    count:(int)count
               completion:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages))completion;

/// 异步获取会话中，从指定消息之前、指定数量的最新消息实体（按照时间从新到旧排列）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter oldestMessageId: 截止的消息 ID [0 或 -1 代表从最近的发送时间查起]
/// - Parameter count: 需要获取的消息数量
/// - Parameter completion: 异步回调 [消息实体 RCMessage 对象列表]
///
/// 返回的消息中不包含 oldestMessageId 对应那条消息。
///
/// 该方法仅获取本地数据库中的消息
/// 超级群不会接收离线消息，超级群调用该接口会出现消息断档的情况，请使用断档消息接口获取超级群消息。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)getHistoryMessages:(RCConversationType)conversationType
                  targetId:(NSString *)targetId
                 channelId:(nullable NSString *)channelId
           oldestMessageId:(long)oldestMessageId
                     count:(int)count
                completion:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages))completion;

/// 异步获取会话中，从指定消息之前、指定数量的、指定消息类型的最新消息实体（按照时间从新到旧排列）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter objectName: 消息内容的类型名，如果想取全部类型的消息请传 nil
/// - Parameter oldestMessageId: 截止的消息 ID [0 或 -1 代表从最近的发送时间查起]
/// - Parameter count: 需要获取的消息数量
/// - Parameter completion: 异步回调 [消息实体 RCMessage 对象列表]
///
/// 返回的消息中不包含 oldestMessageId 对应的那条消息。
///
/// 该方法仅获取本地数据库中的消息
/// 超级群不会接收离线消息，超级群调用该接口会出现消息断档的情况，请使用断档消息接口获取超级群消息。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)getHistoryMessages:(RCConversationType)conversationType
                  targetId:(NSString *)targetId
                 channelId:(nullable NSString *)channelId
                objectName:(nullable NSString *)objectName
           oldestMessageId:(long)oldestMessageId
                     count:(int)count
                completion:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages))completion;

/// 异步获取会话中，指定消息、指定数量、指定消息类型、向前或向后查找的消息实体列表（按照时间从新到旧排列）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter objectName: 消息内容的类型名，如果想取全部类型的消息请传 nil
/// - Parameter baseMessageId: 当前的消息 ID [0 或 -1 代表从最近的发送时间查起]
/// - Parameter isForward: 查询方向 true 为向前，false 为向后
/// - Parameter count: 需要获取的消息数量
/// - Parameter completion: 异步回调 [消息实体 RCMessage 对象列表]
///
/// 返回的消息中不包含 baseMessageId 对应的那条消息。
///
/// 该方法仅获取本地数据库中的消息
/// 超级群不会接收离线消息，超级群调用该接口会出现消息断档的情况，请使用断档消息接口获取超级群消息。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)getHistoryMessages:(RCConversationType)conversationType
                  targetId:(NSString *)targetId
                 channelId:(nullable NSString *)channelId
                objectName:(nullable NSString *)objectName
             baseMessageId:(long)baseMessageId
                 isForward:(BOOL)isForward
                     count:(int)count
                completion:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages))completion;

/// 异步获取会话中，指定时间、指定数量、指定消息类型（多个）、向前或向后查找的消息实体列表（按照时间从新到旧排列）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter objectNames: 消息内容的类型名称列表
/// - Parameter sentTime: 当前的消息时间戳，单位：毫秒
/// - Parameter isForward: 查询方向 true 为向前，false 为向后
/// - Parameter count: 需要获取的消息数量
/// - Parameter completion: 异步回调 [消息实体 RCMessage 对象列表]
///
/// 返回的消息中不包含 sentTime 对应的那条消息。
///
/// 该方法仅获取本地数据库中的消息
/// 超级群不会接收离线消息，超级群调用该接口会出现消息断档的情况，请使用断档消息接口获取超级群消息。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)getHistoryMessages:(RCConversationType)conversationType
                  targetId:(NSString *)targetId
                 channelId:(nullable NSString *)channelId
               objectNames:(NSArray<NSString *> *)objectNames
                  sentTime:(long long)sentTime
                 isForward:(BOOL)isForward
                     count:(int)count
                completion:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages))completion;

/// 在会话中异步搜索指定消息的前 beforeCount 数量和后 afterCount 数量的消息（按照时间从新到旧排列）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter sentTime: 消息的发送时间，单位：毫秒
/// - Parameter beforeCount: 指定消息的前部分消息数量
/// - Parameter afterCount: 指定消息的后部分消息数量
/// - Parameter completion: 异步回调 [消息实体 RCMessage 对象列表]
///
/// 该方法仅获取本地数据库中的消息
/// 超级群不会接收离线消息，超级群调用该接口会出现消息断档的情况，请使用断档消息接口获取超级群消息。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)getHistoryMessages:(RCConversationType)conversationType
                  targetId:(NSString *)targetId
                 channelId:(nullable NSString *)channelId
                  sentTime:(long long)sentTime
               beforeCount:(int)beforeCount
                afterCount:(int)afterCount
                completion:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages))completion;
/// 从服务器端清除历史消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter recordTime: 清除消息时间戳，单位：毫秒【0 <= recordTime <= 当前会话最后一条消息的 sentTime, 0 清除所有消息，其他值清除小于等于 recordTime 的消息】
/// - Parameter successBlock: 获取成功的回调
/// - Parameter errorBlock: 获取失败的回调 [status:清除失败的错误码]
///
/// 此方法从服务器端清除历史消息，但是必须先开通历史消息云存储功能。
/// 例如，您不想从服务器上获取更多的历史消息，通过指定 recordTime 清除成功后只能获取该时间戳之后的历史消息。
///
/// - Remark: 消息操作
/// - Since: 5.1.1
- (void)clearRemoteHistoryMessages:(RCConversationType)conversationType
                          targetId:(NSString *)targetId
                         channelId:(nullable NSString *)channelId
                        recordTime:(long long)recordTime
                           success:(nullable void (^)(void))successBlock
                             error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 清除历史消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter recordTime: 清除消息时间戳，单位：毫秒【0 <= recordTime <= 当前会话最后一条消息的 sentTime,0
/// 清除所有消息，其他值清除小于等于 recordTime 的消息】
/// - Parameter clearRemote: 是否同时删除服务端消息
/// - Parameter successBlock: 获取成功的回调
/// - Parameter errorBlock: 获取失败的回调 [ status:清除失败的错误码]
///
/// 此方法可以清除服务器端历史消息和本地消息，如果清除服务器端消息必须先开通历史消息云存储功能。
/// 例如，您不想从服务器上获取更多的历史消息，通过指定 recordTime 并设置 clearRemote 为 YES
/// 清除消息，成功后只能获取该时间戳之后的历史消息。如果 clearRemote 传 NO，
/// 只会清除本地消息。
///
/// - Remark: 消息操作
/// - Since: 5.1.1
- (void)clearHistoryMessages:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
                   channelId:(nullable NSString *)channelId
                  recordTime:(long long)recordTime
                 clearRemote:(BOOL)clearRemote
                     success:(nullable void (^)(void))successBlock
                       error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 从服务器端获取之前的历史消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter option: 可配置的参数
/// - Parameter successBlock: 获取成功的回调 [messages:获取到的历史消息数组，isRemaining 是否还有剩余消息 YES
/// 表示还有剩余，NO 表示无剩余]
/// - Parameter errorBlock: 获取失败的回调 [status:获取失败的错误码]
///
/// 此方法从服务器端获取之前的历史消息，但是必须先开通历史消息云存储功能。
///
/// - Remark: 消息操作
/// - Since: 5.1.1
- (void)getRemoteHistoryMessages:(RCConversationType)conversationType
                        targetId:(NSString *)targetId
                       channelId:(nullable NSString *)channelId
                          option:(RCRemoteHistoryMsgOption *)option
                         success:(nullable void (^)(NSArray<RCMessage *> *messages, BOOL isRemaining))successBlock
                           error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 获取历史消息
/// 获取指定会话的连续消息，会先从本地数据库获取指定数量消息，然后根据这些消息所在会话的连续
/// 置信区间来判断，这些消息中间是否有断档遗漏（即本地存储消息与服务端存储不同步）如果本地数据库的消息有断档，
/// 会触发一次从服务端获取断档处的消息，然后跟本地消息合并再返回给调用者。
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter option: 可配置的参数
/// - Parameter complete: 获取成功的回调 [messages：获取到的历史消息数组；code : 获取是否成功，0 表示成功，非 0 表示失败，此时 messages 数组可能存在断档]
/// - Parameter errorBlock: 获取失败的回调 [status:获取失败的错误码]，参数合法性检查不通过会直接回调 errorBlock
///
/// - Note: 以下为单群聊场景下的详细说明：
///
///  产生消息断档的典型情况有：
///  1. 超过消息离线存储最长时间未登录。例如默认离线消息的最长存储时间是 7 天，若用户连续 10 天未登录，当再次登录时，
///  服务器只会推送最近 7 天的离线消息，那么更早的 3 天内的消息本地就没有，这段期间称为断档。
///  2. 客户启用了群组离线消息存储条数配置。例如配置群组离线消息存储条数为 100 条，若用户离线期间，
///  该群离线消息超过 100 条，当再次登录时，服务器只会推送最后的 100 条消息，那么更早的消息本地也没有，这段期间称为断档。
///
///  本地存储消息是否断档的判断逻辑：
///  当连接成功后，服务器主动下发消息分为两种情况，一种是单条直发，一种是通知拉取（一般是会话消息量较大的情况）。还有一种
///  是客户端主动拉取消息。对于通知拉取和主动拉取，服务端返回结果中都带有连续置信区间的起始和终止时间戳，客户端会将这段时
///  间记录在本地数据库中，视为该会话的连续置信区间。如果用户一直在线情况下，收到单条直发消息，也会将当前消息的时间戳与本
///  地存储的该会话置信区间做拼接，视为连续置信区间。当用户调用此接口时，会根据用户传入的获取消息条数 count 来从本地数据库
///  中获取，如果获取的所有消息时间戳都在连续置信区间内，就视为无断档，可直接返回给用户。否则会以断档处时间戳为起点，向服
///  务端拉取历史消息，拉回来消息的同时，会更新该会话的连续置信区间，并将入库类型消息与本地数据库的消息合并，再返回给用户。
///
///  结果回调中，messages 为本次拉取到的消息列表，timestamp 为下次拉取的起始时间戳，isRemaining 为服务器是否还有未拉取的消息。
///  分为以下几种情况：
///  1. messages 数量等于 count。代表本次的调用已拉取到 count 条消息，且消息是连续的。用户可根据 isRemaining
///  结果决定是否要继续拉取。
///  2. messages 数量小于 count（包括 0 的情况），且 isRemaining 为 false。
///  代表本次调用已拉取到所有连续消息，且服务端也无更多消息可供拉取。
///  3. messages 数量小于 count（包括 0 的情况），且 isRemaining 为 true。
///  代表本次调用只拉取到这么多连续消息，虽然尝试从服务端拉取断档处消息，但拉回来的都是不存储类型的消息。
///  同时服务端还有更多消息可供拉取，需要用户使用返回的 timestamp 继续拉取。
///
///  以下情况需要注意：
///  1. 调用此接口返回的消息，会在本地标记为连续消息。如果后面调用了删除消息相关接口从本地数据库删除了已连续的消息，
///  会认为此处仍然连续无断档。下次再调用此接口时，不会从服务端拉取此处已删除的消息。
///  2. 当用户一直在线时，如果服务端通过 ServerAPI 将当前用户踢出某群，过一段时间再加回来。
///  如果服务端执行以上操作的同时什么都不做，客户端是无感知的。用户在被踢出群的这段时间内，此群消息接收不到，
///  等加回来后又可以收之后的消息，但 SDK 会认为此间消息一直连续无断档，下次调用此接口时，不会从服务端拉取退群期间的消息。
///  如果想补偿这段时间消息，需要调用拉取该时段的远端消息接口。为避免执行上述操作时，客户端无感知，
///  建议在服务端执行踢人操作前，同时发送一条小灰条消息通知被踢人，避免用户误解。
///
/// - Warning:
/// 必须开通历史消息云存储功能。
/// 此方法先从本地获取历史消息，本地有缺失的情况下会从服务端同步缺失的部分。当本地没有更多消息的时候，会从服务器拉取
/// 从服务端同步失败的时候会返回非 0 的 errorCode，同时把本地能取到的消息回调上去。
/// 在获取远端消息的时候，可能会拉到信令消息，信令消息会被 SDK 排除掉，导致 messages.count 小于 option.count，此时只要 isRemaining 为 YES，那么下次拉取消息的时候，请用 timestamp 当做 option.recordTime 再去拉取；如果 isRemaining 为 NO，则代表远端不再有消息了
///
/// - Remark: 消息操作
/// - Since: 5.2.0
- (void)getMessages:(RCConversationType)conversationType
           targetId:(NSString *)targetId
          channelId:(nullable NSString *)channelId
             option:(RCHistoryMessageOption *)option
           complete:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages, long long timestamp, BOOL isRemaining,
                                       RCErrorCode code))complete
              error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 异步获取会话中 @ 提醒自己的消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter completion: 异步回调 [消息实体 RCMessage 对象列表]
///
/// 最多返回 10 条@提醒的消息
/// - Warning: 使用 IMKit 注意在进入会话页面前调用，否则在进入会话会调用清除未读数的接口 clearMessagesUnreadStatus: targetId:
/// 以及设置消息接收状态接口 setMessageReceivedStatus:receivedStatus: 会同步清除 @ 提醒信息状态。
///
/// - Remark: 高级功能
/// - Since: 5.3.0
- (void)getUnreadMentionedMessages:(RCConversationType)conversationType
                          targetId:(NSString *)targetId
                         channelId:(nullable NSString *)channelId
                        completion:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages))completion;

/// 异步获取本地指定会话的未读条数的 @ 消息列表，仅支持群组
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter count: 未读的 @ 消息，取值范围 [1,100]
/// - Parameter desc: 是否是降序查
/// - Parameter completion: 异步回调 [消息实体 RCMessage 对象列表]
///
/// 假如有 1000 条未读的 @ 消息，取 100 条未读
/// desc 为 true 时获取后 100 条消息，messageList 的顺序是 901 到 1000
/// desc 为 false 是获取前 100 条消息，messageList 的顺序是 1 到 100
///
/// - Warning: 使用 IMKit 注意在进入会话页面前调用，否则在进入会话会调用清除未读数的接口 clearMessagesUnreadStatus: targetId:
/// 以及设置消息接收状态接口 setMessageReceivedStatus:receivedStatus: 会同步清除 @ 提醒信息状态。
/// - Since: 5.3.0

- (void)getUnreadMentionedMessages:(RCConversationType)conversationType
                          targetId:(NSString *)targetId
                         channelId:(nullable NSString *)channelId
                             count:(int)count
                              desc:(BOOL)desc
                        completion:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages))completion;

/// 异步根据会话 id 获取所有子频道的 @ 未读消息总数
///
/// - Parameter targetId: 会话 ID
/// - Parameter completion: 回调会话内的未读消息数
///
/// - Remark: 超级群消息操作
/// - Since: 5.3.0
- (void)getUltraGroupUnreadMentionedCount:(NSString *)targetId completion:(nullable void (^)(int num))completion;

/// 消息修改
///
/// - Parameter messageUId: 将被修改的消息 id
/// - Parameter newContent: 将被修改的消息内容
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// 此方法只能修改相同频道的同类型消息，仅能修改自己发送的消息
///
/// - Remark: 消息操作
/// - Since: 5.2.0
- (void)modifyUltraGroupMessage:(NSString *)messageUId
                 messageContent:(RCMessageContent *)newContent
                        success:(nullable void (^)(void))successBlock
                          error:(nullable void (^)(RCErrorCode status))errorBlock;


/// 更新超级群消息扩展信息
///
/// - Parameter messageUId: 消息 messageUId
/// - Parameter expansionDic: 要更新的消息扩展信息键值对
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// - Remark: 高级功能
/// - Since: 5.2.0
- (void)updateUltraGroupMessageExpansion:(NSString *)messageUId
                            expansionDic:(NSDictionary<NSString *, NSString *> *)expansionDic
                                 success:(nullable void (^)(void))successBlock
                                   error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 删除超级群消息扩展信息中特定的键值对
///
/// - Parameter messageUId: 消息 messageUId
/// - Parameter keyArray: 消息扩展信息中待删除的 key 的列表
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// - Remark: 高级功能
/// - Since: 5.2.0
- (void)removeUltraGroupMessageExpansion:(NSString *)messageUId
                                keyArray:(NSArray<NSString *> *)keyArray
                                 success:(nullable void (^)(void))successBlock
                                   error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 撤回超级群消息
///
/// - Parameter message: 需要撤回的消息
/// - Parameter isDelete: 是否移除远端消息记录
/// - Parameter successBlock: 撤回成功的回调 [messageId:撤回的消息 ID。isDelete:NO 时，该消息已经变更为新的消息 `RCRecallNotificationMessage`; isDelete:YES 时，该消息已经被删除]
/// - Parameter errorBlock: 撤回失败的回调 [errorCode:撤回失败错误码]
/// - Remark: 高级功能
/// - Since: 5.2.3
- (void)recallUltraGroupMessage:(RCMessage *)message
                       isDelete:(BOOL)isDelete
                        success:(nullable void (^)(long messageId))successBlock
                          error:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 获取同一个超级群下的批量服务消息（含所有频道）
/// 获取成功后强制更新本地消息
/// - Parameter messages: 消息列表 [最多 20 条，每个消息对象需包含 ConversationType,targetId,channelId, messageUid,sentTime]
/// - Parameter successBlock: 成功的回调 [matchedMsgList:成功的消息列表，notMatchMsgList:失败的消息列表]
/// - Parameter errorBlock: 失败的回调 [errorCode:错误码]
/// - Remark: 高级功能
/// - Since: 5.2.0
- (void)getBatchRemoteUltraGroupMessages:(NSArray<RCMessage *> *)messages
                                 success:(nullable void (^)(NSArray<RCMessage *> *matchedMsgList,
                                                            NSArray<RCMessage *> *notMatchMsgList))successBlock
                                   error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 批量获取本地消息，支持单聊、群聊、超级群、聊天室会话类型
/// - Parameter conversationType: 会话类型 [非法报错:INVALID_PARAMETER_CONVERSATIONTYPE]
/// - Parameter targetId: 会话 ID[非法报错:INVALID_PARAMETER_TARGETID]
/// - Parameter channelId: 频道 ID(非超级群时传 nil)[非法报错:INVALID_PARAMETER_CHANNELID]
/// - Parameter messageUIDs: 消息 UID 列表 (最多 20 条)[数量大于 20 或为 0，类型不对:INVALID_PARAMETER_MESSAGELIST]
/// - Parameter successBlock: 成功的回调 [messages:成功的消息列表，mismatch:失败的消息 UID 列表]
/// - Parameter errorBlock: 失败的回调 [errorCode:错误码]
///
/// mismatch 不为空，则代表本地没有对应的 message:
/// 1. messageUid 可能不是标准的 UID 字符串，本地无法匹配
/// 2. 超级群默认只同步会话最后一条消息，可能本地找不到本地对应消息，可以先调用 getBatchRemoteUltraGroupMessages 从远端拉去一下
/// 3. 聊天室退出之后，本地消息会被清空，调用该接口无法拿到本地消息
/// - Remark: 高级功能
/// - Since: 5.3.0
- (void)getBatchLocalMessages:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                    channelId:(nullable NSString *)channelId
                  messageUIDs:(NSArray<NSString *> *)messageUIDs
                      success:(nullable void (^)(NSArray<RCMessage *> *messages,
                                                 NSArray<NSString *> *mismatch))successBlock
                        error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 异步获取会话里第一条未读消息。
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter completion: 异步回调 [第一条未读消息的实体]
///
/// - Remark: 消息操作
/// 前提：超级群会话不接收离线消息。
///  用户在线接收的超级群未读消息已经保存到本地数据库，可以通过此接口获取到
///  用户离线的超级群未读消息，用户在线之后不收离线未读消息，通过此接口获取第一条未读消息为空
/// - Since: 5.3.0
- (void)getFirstUnreadMessage:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                    channelId:(nullable NSString *)channelId
                   completion:(nullable void (^)(RCMessage *_Nullable message))completion;

/// 删除某个会话中的所有消息
///
/// - Parameter conversationType: 会话类型，不支持聊天室
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// 此方法删除数据库中该会话的消息记录，同时会整理压缩数据库，减少占用空间
///
/// - Remark: 消息操作
/// - Since: 5.1.1
- (void)deleteMessages:(RCConversationType)conversationType
              targetId:(NSString *)targetId
             channelId:(nullable NSString *)channelId
               success:(nullable void (^)(void))successBlock
                 error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 批量删除某个会话中的指定远端消息（同时删除对应的本地消息）
///
/// - Parameter conversationType: 会话类型，不支持聊天室
/// - Parameter targetId: 目标会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter messages: 将被删除的消息列表
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// 一次批量操作仅支持删除属于同一个会话的消息，请确保消息列表中的所有消息来自同一会话
/// 一次最多删除 100 条消息。
///
/// - Remark: 消息操作
/// - Since: 5.1.1
- (void)deleteRemoteMessage:(RCConversationType)conversationType
                   targetId:(NSString *)targetId
                  channelId:(nullable NSString *)channelId
                   messages:(NSArray<RCMessage *> *)messages
                    success:(nullable void (^)(void))successBlock
                      error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 异步删除指定超级群、所有 channel、指定时间之前的本地消息
///
/// - Parameter targetId: 会话 ID
/// - Parameter timestamp: 会话的时间戳，单位：毫秒
/// - Parameter completion: 异步回调 [是否删除成功]
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)deleteUltraGroupMessagesForAllChannel:(NSString *)targetId
                                    timestamp:(long long)timestamp
                                   completion:(nullable void (^)(BOOL result))completion;

/// 异步删除指定超级群、指定 channel、指定时间之前的本地消息
///
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 频道 ID
/// - Parameter timestamp: 会话的时间戳，单位：毫秒
/// - Parameter completion: 异步回调 [是否删除成功]
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)deleteUltraGroupMessages:(NSString *)targetId
                       channelId:(nullable NSString *)channelId
                       timestamp:(long long)timestamp
                      completion:(nullable void (^)(BOOL result))completion;
/// 删除指定 channel、指定时间之前的服务端消息
///
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 频道 ID
/// - Parameter timestamp: 会话的时间戳，单位：毫秒
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// - Remark: 消息操作
/// - Since: 5.2.0
- (void)deleteRemoteUltraGroupMessages:(NSString *)targetId
                             channelId:(nullable NSString *)channelId
                             timestamp:(long long)timestamp
                               success:(nullable void (^)(void))successBlock
                                 error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 异步删除某个会话中的所有消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter completion: 异步回调 [是否删除成功]
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)clearMessages:(RCConversationType)conversationType
             targetId:(NSString *)targetId
            channelId:(nullable NSString *)channelId
           completion:(nullable void (^)(BOOL result))completion;

/// 异步批量删除指定会话早于（含）发送时间的所有本地数据库消息
///
/// - Parameter clearMessageOptions: [RCClearMessageOption], 最大数量为 20
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调 [status: 失败的错误码]
///
/// 此方法删除数据库中会话早于（含）发送时间的消息记录，时间戳传 0 清除所有消息
/// 支持的会话类型：单聊，群聊，聊天室，系统消息
///
/// - Remark: 会话
/// - Since: 5.6.7
- (void)clearMessages:(NSArray<RCClearMessageOption *> *)clearMessageOptions
              success:(nullable void (^)(void))successBlock
                error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 异步批量删除服务端指定会话早于（含）发送时间的所有远端消息（可以删除对应的本地消息）
///
/// - Parameter clearMessageOptions: [RCClearMessageOption], 最大数量为 20
/// - Parameter isDeleteLocal: 是否删除对应的本地消息
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调 [status: 失败的错误码]
///
/// 时间戳传 0 清除所有消息
/// 支持的会话类型：单聊，群聊，聊天室，系统消息
///
/// - Remark: 会话
/// - Since: 5.6.7
- (void)clearRemoteMessages:(NSArray<RCClearMessageOption *> *)clearMessageOptions
              isDeleteLocal:(BOOL)isDeleteLocal
                    success:(nullable void (^)(void))successBlock
                      error:(nullable void (^)(RCErrorCode status))errorBlock;


#pragma mark - 会话列表操作

/// 异步获取本地会话列表（按照时间从新到旧排列，如果有置顶的会话，则置顶的会话会排列在前面）
///
/// - Parameter conversationTypeList: 会话类型的数组 (需要将 RCConversationType 转为 NSNumber 构建 NSArray)
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter completion: 异步回调 [会话 RCConversation 的列表]
///
/// 当您的会话较多且没有清理机制的时候，强烈建议您使用 getConversationList: count: startTime:
/// 分页拉取会话列表，否则有可能造成内存过大。
///
/// - Remark: 会话列表
/// - Since: 5.3.0
- (void)getConversationList:(NSArray<NSNumber *> *)conversationTypeList
                  channelId:(nullable NSString *)channelId
                 completion:(nullable void (^)(NSArray<RCConversation *> *_Nullable conversationList))completion;

/// 异步分页获取本地会话列表（按照时间从新到旧排列，如果有置顶的会话，则置顶的会话会排列在前面）
///
/// - Parameter conversationTypeList: 会话类型的数组 (需要将 RCConversationType 转为 NSNumber 构建 NSArray)
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter count: 获取的数量（当实际取回的会话数量小于 count 值时，表明已取完数据）
/// - Parameter startTime: 会话的时间戳，单位：毫秒（获取这个时间戳之前的会话列表，0 表示从最新开始获取）
/// - Parameter completion: 异步回调 [会话 RCConversation 的列表]
///
/// - Remark: 会话列表
/// - Since: 5.3.0
- (void)getConversationList:(NSArray<NSNumber *> *)conversationTypeList
                  channelId:(nullable NSString *)channelId
                      count:(int)count
                  startTime:(long long)startTime
                 completion:(nullable void (^)(NSArray<RCConversation *> *_Nullable conversationList))completion;

/// 异步分页获取本地会话列表（按照时间从新到旧排列，如果有置顶的会话，则置顶的会话会排列在前面）
///
/// - Parameter conversationTypeList: 会话类型的数组 (需要将 RCConversationType 转为 NSNumber 构建 NSArray)
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter count: 获取的数量（当实际取回的会话数量小于 count 值时，表明已取完数据）
/// - Parameter startTime: 会话的时间戳，单位：毫秒（获取这个时间戳之前的会话列表，0 表示从最新开始获取）
/// - Parameter topPriority: 查询结果的排序方式，是否置顶优先，传 true 表示置顶会话优先返回，否则结果只以会话时间排序
/// - Parameter completion: 异步回调 [会话 RCConversation 的列表]
///
/// - Remark: 会话列表
/// - Since: 5.6.6
- (void)getConversationList:(NSArray<NSNumber *> *)conversationTypeList
                  channelId:(nullable NSString *)channelId
                      count:(int)count
                  startTime:(long long)startTime
                topPriority:(BOOL)topPriority
                 completion:(nullable void (^)(NSArray<RCConversation *> *_Nullable conversationList))completion;

/// 异步获取会话列表。
/// - Parameters:
///   - filters: 会话过滤参数。
///   - option: 参数配置。
///   - completion: 结果回调。
///
/// - Since: 5.20.0
- (void)getConversationListByFilters:(NSArray<RCConversationTypeFilter *> *)filters
                              option:(nullable RCConversationListOption *)option
                          completion:(RCConversationListCompletion)completion;

/// 异步获取本地特定会话下所有频道的会话列表（按照时间从新到旧排列，如果有置顶的会话，则置顶的会话会排列在前面）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter completion: 异步回调 [会话 RCConversation 的列表]
///
/// - Remark: 会话列表
/// - Since: 5.3.0
- (void)getConversationListForAllChannel:(RCConversationType)conversationType
                                targetId:(NSString *)targetId
                              completion:
                                  (nullable void (^)(NSArray<RCConversation *> *_Nullable conversationList))completion;

/// 分页异步获取本地特定会话类型下所有 channel 的会话列表（按照时间从新到旧排列，如果有置顶的会话，则置顶的会话会排列在前面）
/// - Parameter conversationTypeList: 会话类型数组
/// - Parameter count: 会话个数
/// - Parameter startTime: 开始时间，首次可传入 0，单位：毫秒
/// - Parameter completion: 异步回调 [会话 RCConversation 的列表]
///
/// 此方法会从本地数据库中，读取会话列表。
/// - Since: 5.3.0
- (void)getConversationListForAllChannel:(NSArray<NSNumber *> *)conversationTypeList
                                   count:(int)count
                               startTime:(long long)startTime
                              completion:
                                  (nullable void (^)(NSArray<RCConversation *> *_Nullable conversationList))completion;

/// 异步获取本地所有含 ChannelId 会话列表（按照时间从新到旧排列，如果有置顶的会话，则置顶的会话会排列在前面）
///
/// - Parameter conversationTypeList: 会话类型的数组 (需要将 RCConversationType 转为 NSNumber 构建 NSArray)
/// - Parameter completion: 异步回调 [会话 RCConversation 的列表]
///
/// - Warning: 当会话数量多的时候，会有性能问题，所以建议在非主线程调用该接口
/// - Remark: 会话列表
/// - Since: 5.3.0
- (void)getConversationListForAllChannel:(NSArray<NSNumber *> *)conversationTypeList
                              completion:
                                  (nullable void (^)(NSArray<RCConversation *> *_Nullable conversationList))completion;

/// 异步获取本地单个会话数据
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter completion: 异步回调 [会话的对象]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)getConversation:(RCConversationType)conversationType
               targetId:(NSString *)targetId
              channelId:(nullable NSString *)channelId
             completion:(nullable void (^)(RCConversation *_Nullable conversation))completion;

/// 异步获取本地会话中的消息数量
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter completion: 异步回调 [会话中的消息数量，-1 表示获取消息数量出错]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)getMessageCount:(RCConversationType)conversationType
               targetId:(NSString *)targetId
              channelId:(nullable NSString *)channelId
             completion:(nullable void (^)(int num))completion;

/// 异步删除本地指定类型的会话
///
/// - Parameter conversationTypeList: 会话类型的数组 (需要将 RCConversationType 转为 NSNumber 构建 NSArray)
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter completion: 异步回调 [是否删除成功]
///
/// 此方法会从本地存储中删除该会话，同时删除会话中的消息。
/// 此方法不支持超级群的会话类型，包含超级群时可能会造成数据异常。
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)clearConversations:(NSArray<NSNumber *> *)conversationTypeList
                 channelId:(nullable NSString *)channelId
                completion:(nullable void (^)(BOOL result))completion;

/// 异步删除本地和服务的会话
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter completion: 异步回调 [是否删除成功]
///
/// 此方法会同时删除本地和服务的会话，但是不会删除会话中的消息。如果此会话中有新的消息，该会话将重新在会话列表中显示，并显示最近的历史消息。
/// - Warning: 如果服务的会话删除失败，本地的会话依然会被删除。SDK 在未连接的情况下，删除服务会话会失败
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)removeConversation:(RCConversationType)conversationType
                  targetId:(NSString *)targetId
                 channelId:(nullable NSString *)channelId
                completion:(nullable void (^)(BOOL result))completion
    NS_SWIFT_NAME(removeConversation(_:targetId:channelId:completion:));

/// 异步批量删除会话列表
///
/// - Parameter conversationIdentifiers: [RCConversationIdentifier], 最大数量为 20
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调 [status: 失败的错误码]
///
/// 不删除会话内的消息，如果会话中有新的消息，该会话将重新在会话列表中显示，并显示最近的历史消息。
/// 支持的会话类型：单聊，群聊，系统消息
///
/// - Remark: 会话
/// - Since: 5.6.7
- (void)removeConversations:(NSArray<RCConversationIdentifier *> *)conversationIdentifiers
                    success:(nullable void (^)(void))successBlock
                      error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 删除远端会话

/// - Parameter conversationIdentifiers    [RCConversationIdentifier], 最大数量为 20
/// - Parameter successBlock        删除成功的回调
/// - Parameter errorBlock          删除失败的回调 [status:删除失败的错误码]
///
/// - Remark: 会话
/// - Since:5.12.3
- (void)removeRemoteConversations:(NSArray<RCConversationIdentifier *> *)conversationIdentifiers
                          success:(nullable void (^)(void))successBlock
                            error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 异步设置会话的置顶状态
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter isTop: 是否置顶
/// - Parameter completion: 异步回调 [设置是否成功]
///
/// 会话不存在时设置置顶，会在会话列表生成会话。
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)setConversationToTop:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
                   channelId:(nullable NSString *)channelId
                       isTop:(BOOL)isTop
                  completion:(nullable void (^)(BOOL result))completion;

/// 异步批量设置会话的置顶状态
///
/// - Parameter conversationIdentifiers: [RCConversationIdentifier], 最大数量为 20
/// - Parameter isTop: 是否置顶（置顶：YES，取消置顶：NO）
/// - Parameter needCreate: 在没有会话时，是否创建会话
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调 [status: 失败的错误码]
///
/// - Remark: 会话
/// - Since: 5.6.7
- (void)setConversationsToTop:(NSArray<RCConversationIdentifier *> *)conversationIdentifiers
                        isTop:(BOOL)isTop
                   needCreate:(BOOL)needCreate
                      success:(nullable void (^)(void))successBlock
                        error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 异步设置会话的置顶状态
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter isTop: 是否置顶
/// - Parameter needUpdateTime: 是否更新时间
/// - Parameter completion: 异步回调 [设置是否成功]
///
/// 会话不存在时设置置顶，会在会话列表生成会话。
///
/// - Remark: 会话
- (void)setConversationToTop:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
                   channelId:(nullable NSString *)channelId
                       isTop:(BOOL)isTop
              needUpdateTime:(BOOL)needUpdateTime
                  completion:(nullable void (^)(BOOL result))completion;

/// 异步获取本地会话的置顶状态
///
/// - Parameter conversationIdentifier: 会话信息
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter completion: 异步回调 [是否置顶]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)getConversationTopStatus:(RCConversationIdentifier *)conversationIdentifier
                       channelId:(nullable NSString *)channelId
                      completion:(nullable void (^)(BOOL result))completion;

/// 异步获取本地置顶的会话列表
///
/// - Parameter conversationTypeList: 会话类型的数组 (需要将 RCConversationType 转为 NSNumber 构建 NSArray)
/// - Parameter completion: 异步回调 [置顶的会话 RCConversation 的列表]
///
/// - Remark: 会话列表
/// - Since: 5.3.0
- (void)getTopConversationList:(NSArray<NSNumber *> *)conversationTypeList
                     channelId:(nullable NSString *)channelId
                    completion:(nullable void (^)(NSArray<RCConversation *> *_Nullable conversationList))completion;
#pragma mark 会话中的草稿操作

/// 异步获取会话中的草稿信息（用户输入但未发送的暂存消息）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话目标 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter completion: 异步回调 [该会话中的草稿]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)getTextMessageDraft:(RCConversationType)conversationType
                   targetId:(NSString *)targetId
                  channelId:(nullable NSString *)channelId
                 completion:(nullable void (^)(NSString *_Nullable content))completion;

/// 异步保存草稿信息（用户输入但未发送的暂存消息）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话目标 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter content: 草稿信息
/// - Parameter completion: 异步回调 [是否保存成功]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)saveTextMessageDraft:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
                   channelId:(nullable NSString *)channelId
                     content:(NSString *)content
                  completion:(nullable void (^)(BOOL result))completion;

/// 异步删除会话中的草稿信息（用户输入但未发送的暂存消息）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话目标 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter completion: 异步回调 [是否删除成功]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)clearTextMessageDraft:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                    channelId:(nullable NSString *)channelId
                   completion:(nullable void (^)(BOOL result))completion;

#pragma mark 未读消息数

/// 异步获取所有的未读消息数（聊天室会话除外）
///
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter completion: 异步回调 [所有的未读消息数（含免打扰会话未读数）]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)getTotalUnreadCountWithChannelId:(nullable NSString *)channelId
                              completion:(nullable void (^)(int num))completion;

/// 异步获取所有的未读消息数（聊天室会话除外）
///
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter isContain: 是否包含免打扰会话的未读数，YES 包含免打扰会话未读数
/// - Parameter completion: 异步回调 [所有的未读消息数]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)getTotalUnreadCountWithChannelId:(nullable NSString *)channelId
                          containBlocked:(BOOL)isContain
                              completion:(nullable void (^)(int num))completion;

/// 异步获取某个会话内的未读消息数（聊天室会话除外）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话目标 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter completion: 异步回调 [该会话内的未读消息数]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)getUnreadCount:(RCConversationType)conversationType
              targetId:(NSString *)targetId
             channelId:(nullable NSString *)channelId
            completion:(nullable void (^)(int num))completion;

/// 异步获取某个会话内的未读消息数
///
/// - Parameter conversationIdentifier: 会话信息
/// - Parameter messageClassList: 消息类型数组
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter completion: 异步回调 [该会话内的未读消息数]
///
/// 此方法不支持聊天室和超级群的会话类型。
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)getUnreadCount:(RCConversationIdentifier *)conversationIdentifier
      messageClassList:(NSArray<Class> *)messageClassList
             channelId:(nullable NSString *)channelId
            completion:(nullable void (^)(int num))completion;

/// 异步获取某些类型的会话中所有的未读消息数（聊天室会话除外）
///
/// - Parameter conversationTypes: 会话类型的数组
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter isContain: 是否包含免打扰消息的未读数
/// - Parameter completion: 异步回调 [该类型的会话中所有的未读消息数]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)getUnreadCount:(NSArray<NSNumber *> *)conversationTypes
             channelId:(nullable NSString *)channelId
        containBlocked:(bool)isContain
            completion:(nullable void (^)(int num))completion;

/// 异步获取某个类型的会话中所有未读的被 @ 的消息数
///
/// - Parameter conversationTypes: 会话类型的数组
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter completion: 异步回调 [该类型的会话中所有未读的被 @ 的消息数]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)getUnreadMentionedCount:(NSArray<NSNumber *> *)conversationTypes
                      channelId:(nullable NSString *)channelId
                     completion:(nullable void (^)(int num))completion;

/// 异步清除某个会话中的未读消息数
///
/// - Parameter conversationType: 会话类型，不支持聊天室
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter completion: 异步回调 [是否清除成功]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)clearMessagesUnreadStatus:(RCConversationType)conversationType
                         targetId:(NSString *)targetId
                        channelId:(nullable NSString *)channelId
                       completion:(nullable void (^)(BOOL result))completion;

/// 异步清除某个会话中的未读消息数（该会话在时间戳 timestamp 之前的消息将被置成已读。）
///
/// - Parameter conversationType: 会话类型，不支持聊天室
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter timestamp: 该会话已阅读的最后一条消息的发送时间戳，单位：毫秒
/// - Parameter completion: 异步回调 [是否清除成功]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)clearMessagesUnreadStatus:(RCConversationType)conversationType
                         targetId:(NSString *)targetId
                        channelId:(nullable NSString *)channelId
                             time:(long long)timestamp
                       completion:(nullable void (^)(BOOL result))completion;

#pragma mark - 会话的消息提醒

/// 设置会话的消息提醒状态
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter level: 消息通知级别
/// - Parameter successBlock: 设置成功的回调
/// - Parameter errorBlock: 设置失败的回调 [status:设置失败的错误码]
///
/// 如果您需要移除消息通知，level 参数传入 RCPushNotificationLevelDefault 即可
/// 注：超级群通过该接口对具体频道进行免打扰设置
///
/// - Remark: 会话
/// - Since: 5.2.2
- (void)setConversationChannelNotificationLevel:(RCConversationType)conversationType
                                       targetId:(NSString *)targetId
                                      channelId:(nullable NSString *)channelId
                                          level:(RCPushNotificationLevel)level
                                        success:(nullable void (^)(void))successBlock
                                          error:(nullable void (^)(RCErrorCode status))errorBlock;


/// 查询会话的消息提醒状态
///
/// - Parameter conversationType: 会话类型（不支持聊天室，聊天室是不接受会话消息提醒的）
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter successBlock: 查询成功的回调 [nStatus:会话设置的消息提醒状态]
/// - Parameter errorBlock: 查询失败的回调 [status:设置失败的错误码]
///
/// - Remark: 会话
/// - Since: 5.1.1
- (void)getConversationNotificationStatus:(RCConversationType)conversationType
                                 targetId:(NSString *)targetId
                                channelId:(nullable NSString *)channelId
                                  success:(nullable void (^)(RCConversationNotificationStatus nStatus))successBlock
                                    error:(nullable void (^)(RCErrorCode status))errorBlock;
/// 查询消息通知级别
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter successBlock: 设置成功的回调 [level:消息通知级别]
/// - Parameter errorBlock: 查询失败的回调 [status:设置失败的错误码]
///
/// - Remark: 会话
/// - Since: 5.2.2
- (void)getConversationChannelNotificationLevel:(RCConversationType)conversationType
                                       targetId:(NSString *)targetId
                                      channelId:(nullable NSString *)channelId
                                        success:(nullable void (^)(RCPushNotificationLevel level))successBlock
                                          error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 异步获取本地消息免打扰会话列表
/// - Parameter conversationTypeList: 会话类型的数组 (需要将 RCConversationType 转为 NSNumber 构建 NSArray)
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter completion: 异步回调 [消息免打扰会话 RCConversation 的列表]
///
/// - Remark: 会话列表
/// - Since: 5.3.0
- (void)getBlockedConversationList:(NSArray<NSNumber *> *)conversationTypeList
                         channelId:(nullable NSString *)channelId
                        completion:(nullable void (^)(NSArray<RCConversation *> *_Nullable conversationList))completion;
/// 设置超级群的默认消息状态
///
/// 一般由管理员设置的接口，针对超级群的所有群成员生效，针对超级群下所有频道生效，优先级较低。
/// 如果群成员自己超级群的免打扰级别，那么以群成员自己设置的为准。
///
/// - Parameter targetId: 会话 ID
/// - Parameter level: 等级
/// - Parameter successBlock: 设置成功的回调
/// - Parameter errorBlock: 设置失败的回调 [status:设置失败的错误码]
///
/// - Since: 5.2.2
- (void)setUltraGroupConversationDefaultNotificationLevel:(NSString *)targetId
                                                    level:(RCPushNotificationLevel)level
                                                  success:(nullable void (^)(void))successBlock
                                                    error:(nullable void (^)(RCErrorCode status))errorBlock;
/// 获取超级群的默认消息状态
///
/// - Parameter targetId: 会话 ID
/// - Parameter successBlock: 设置成功的回调 [level:消息通知级别]
/// - Parameter errorBlock: 设置失败的回调 [status:设置失败的错误码]
///
/// - Remark: 会话
/// - Since: 5.2.2
- (void)getUltraGroupConversationDefaultNotificationLevel:(NSString *)targetId
                                                  success:(nullable void (^)(RCPushNotificationLevel level))successBlock
                                                    error:(nullable void (^)(RCErrorCode status))errorBlock;


#pragma mark - 输入状态提醒

/// 向会话中发送正在输入的状态
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话目标  ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter objectName: 正在输入的消息的类型名
///
/// contentType 为用户当前正在编辑的消息类型名，即 RCMessageContent 中 getObjectName 的返回值。
/// 如文本消息，应该传类型名"RC:TxtMsg"。
///
/// - Warning: 目前仅支持单聊。
///
/// - Remark: 高级功能
/// - Since: 5.1.1
- (void)sendTypingStatus:(RCConversationType)conversationType
                targetId:(NSString *)targetId
               channelId:(nullable NSString *)channelId
             contentType:(NSString *)objectName;

/// 向超级群会话中发送正在输入的状态
///
/// - Parameter targetId: 会话目标  ID
/// - Parameter channelId: 所属会话的频道 id
/// - Parameter status: 输入状态类型
///
/// - Remark: 高级功能
/// - Since: 5.2.0
- (void)sendUltraGroupTypingStatus:(NSString *)targetId
                         channelId:(nullable NSString *)channelId
                      typingStatus:(RCUltraGroupTypingStatus)status
                           success:(nullable void (^)(void))successBlock
                             error:(nullable void (^)(RCErrorCode status))errorBlock;
#pragma mark - 搜索

/// 根据关键字异步搜索指定会话中的消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter keyword: 关键字
/// - Parameter count: 最大的查询数量
/// - Parameter startTime: 查询 startTime 之前的消息，单位：毫秒（传 0 表示不限时间）
/// - Parameter completion: 异步回调 [匹配的消息列表]
///
/// 只支持搜索已存储到本地的消息。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)searchMessages:(RCConversationType)conversationType
              targetId:(NSString *)targetId
             channelId:(nullable NSString *)channelId
               keyword:(NSString *)keyword
                 count:(int)count
             startTime:(long long)startTime
            completion:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages))completion;

/// 根据时间，偏移量和个数异步搜索指定会话中的消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter keyword: 关键字，传空默认为是查全部符合条件的消息
/// - Parameter startTime: 查询 startTime 之后的消息，startTime >= 0，单位：毫秒
/// - Parameter endTime: 查询 endTime 之前的消息，endTime > startTime，单位：毫秒
/// - Parameter offset: 查询的消息的偏移量，offset >= 0
/// - Parameter limit: 最大的查询数量，limit 需大于 0，最大值为 100，如果大于 100，会默认成 100。
/// - Parameter completion: 异步回调 [匹配的消息列表]
///
/// 只支持搜索已存储到本地的消息。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)searchMessages:(RCConversationType)conversationType
              targetId:(NSString *)targetId
             channelId:(nullable NSString *)channelId
               keyword:(nullable NSString *)keyword
             startTime:(long long)startTime
               endTime:(long long)endTime
                offset:(int)offset
                 limit:(int)limit
            completion:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages))completion;

/// 按用户 ID 异步搜索指定会话中的消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter userId: 搜索用户 ID
/// - Parameter count: 最大的查询数量
/// - Parameter startTime: 查询 startTime 之前的消息，单位：毫秒（传 0 表示不限时间）
/// - Parameter completion: 异步回调 [匹配的消息列表]
///
///
/// 只支持搜索已存储到本地的消息。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)searchMessages:(RCConversationType)conversationType
              targetId:(NSString *)targetId
             channelId:(nullable NSString *)channelId
                userId:(NSString *)userId
                 count:(int)count
             startTime:(long long)startTime
            completion:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages))completion;

/// 异步搜索指定会话中所有 channelId 的消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter keyword: 关键字，非空
/// - Parameter count: 最大的查询数量
/// - Parameter startTime: 查询 startTime 之前的消息，单位：毫秒（传 0 表示不限时间）
/// - Parameter completion: 异步回调 [匹配的消息列表]
///
/// 只支持搜索已存储到本地的消息。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)searchMessagesForAllChannel:(RCConversationType)conversationType
                           targetId:(NSString *)targetId
                            keyword:(NSString *)keyword
                              count:(int)count
                          startTime:(long long)startTime
                         completion:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages))completion;

/// 分页异步搜索指定会话中所有 channelId 在指定时间范围内的消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter keyword: 关键字，非空
/// - Parameter startTime: 开始时间，单位：毫秒（传 0 表示不限时间）
/// - Parameter endTime: 结束时间，可传入当前 unix 时间，，单位：毫秒
/// - Parameter offset: 偏移量，默认填 0
/// - Parameter limit: 最大的查询数量
/// - Parameter completion: 异步回调 [匹配的消息列表]
///
/// 只支持搜索已存储到本地的消息。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)searchMessagesForAllChannel:(RCConversationType)conversationType
                           targetId:(NSString *)targetId
                            keyword:(NSString *)keyword
                          startTime:(long long)startTime
                            endTime:(long long)endTime
                             offset:(int)offset
                              limit:(int)limit
                         completion:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages))completion;

/// 根据关键字搜索指定超级群下多个频道的本地历史消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 id
/// - Parameter channelIds: 频道列表，支持一次查询多个频道，必须满足 `0 < 频道个数 <= 50`
/// SDK 会过滤掉数组中的空字符串，如果 channelId 不合法（非字符串类型或长度超过  20 为不合法）
/// 或 频道个数不满足条件，errorBlock 会返回错误码 `INVALID_PARAMETER_CHANNELID`
/// - Parameter keyword: 查询内容关键字
/// - Parameter startTime: 查询 startTime 之前的消息（传 0 表示从最新消息开始搜索）
/// - Parameter limit: 最大的查询数量，limit 需大于 0，最大值为 100，如果大于 100，会默认成 100。
/// - Parameter successBlock: [messages] 满足条件的消息列表，按时间倒序排序
/// - Parameter errorBlock: [errorCode] 错误码
///
/// - Remark: 消息操作
/// - Since: 5.6.2
- (void)searchMessagesForChannels:(RCConversationType)conversationType
                         targetId:(NSString *)targetId
                       channelIds:(NSArray<NSString *> *)channelIds
                          keyword:(NSString *)keyword
                        startTime:(long long)startTime
                            limit:(int)limit
                          success:(nullable void (^)(NSArray<RCMessage *> *messages))successBlock
                            error:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 根据发送者用户 ID 搜索指定超级群下多个频道的本地历史消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 id
/// - Parameter channelIds: 频道列表，支持一次查询多个频道，必须满足 `0 < 频道个数 <= 50`
/// SDK 会过滤掉数组中的空字符串，如果 channelId 不合法（非字符串类型或长度超过  20 为不合法）
/// 或 频道个数不满足条件，errorBlock 会返回错误码 `INVALID_PARAMETER_CHANNELID`
/// - Parameter userId: 消息发送者用户 ID
/// - Parameter startTime: 查询 startTime 之前的消息（传 0 表示从最新消息开始搜索）
/// - Parameter limit: 最大的查询数量，limit 需大于 0，最大值为 100，如果大于 100，会默认成 100。
/// - Parameter successBlock: [messages] 满足条件的消息列表，按时间倒序排序
/// - Parameter errorBlock: [errorCode] 错误码
///
/// - Remark: 消息操作
/// - Since: 5.6.2
- (void)searchMessagesByUserForChannels:(RCConversationType)conversationType
                               targetId:(NSString *)targetId
                             channelIds:(NSArray<NSString *> *)channelIds
                                 userId:(NSString *)userId
                              startTime:(long long)startTime
                                  limit:(int)limit
                                success:(nullable void (^)(NSArray<RCMessage *> *messages))successBlock
                                  error:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 根据发送者用户 ID 搜索指定超级群下所有频道的本地历史消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 id
/// - Parameter userId: 消息发送者用户 ID
/// - Parameter startTime: 查询 startTime 之前的消息（传 0 表示从最新消息开始搜索）
/// - Parameter limit: 最大的查询数量，limit 需大于 0，最大值为 100，如果大于 100，会默认成 100。
/// - Parameter successBlock: [messages] 满足条件的消息列表，按时间倒序排序
/// - Parameter errorBlock: [errorCode] 错误码
///
/// - Remark: 消息操作
/// - Since: 5.6.2
- (void)searchMessagesByUserForAllChannel:(RCConversationType)conversationType
                                 targetId:(NSString *)targetId
                                   userId:(NSString *)userId
                                startTime:(long long)startTime
                                    limit:(int)limit
                                  success:(nullable void (^)(NSArray<RCMessage *> *messages))successBlock
                                    error:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 根据关键字异步搜索会话
///
/// - Parameter conversationTypeList: 需要搜索的会话类型列表
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter objectNameList: 需要搜索的消息类型名列表 (即每个消息类方法 getObjectName 的返回值)
/// - Parameter keyword: 关键字
/// - Parameter completion: 异步回调 [匹配的会话搜索结果列表]
///
///
/// 目前，SDK 内置的文本消息、文件消息、图文消息支持搜索。
/// 自定义的消息必须要实现 RCMessageContent 的 getSearchableWords 接口才能进行搜索。
///
/// conversationTypeList 包含超级群会话类型时，超级群会话只搜索已存储到本地的消息记录。
/// objectNameList 中类型名个数不能超过 300，超过会被截断。
///
/// conversationTypeList 传值时：
/// OC 需转成 NSNumber 传入（例如 @[ @(ConversationType_PRIVATE) ]），
/// Swift 需获取到 rawValue 强转成 NSNumber 传入
/// （例如 let privateType = NSNumber(value: RCConversationType.ConversationType_PRIVATE.rawValue)
/// [privateType]  ）
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)searchConversations:(NSArray<NSNumber *> *)conversationTypeList
                  channelId:(nullable NSString *)channelId
                messageType:(NSArray<NSString *> *)objectNameList
                    keyword:(NSString *)keyword
                 completion:(nullable void (^)(NSArray<RCSearchConversationResult *> *_Nullable results))completion;

/// 根据关键字异步搜索特定会话类型下所有 channelId 的会话
///
/// - Parameter conversationTypeList: 需要搜索的会话类型列表
/// - Parameter objectNameList: 需要搜索的消息类型名列表 (即每个消息类方法 getObjectName 的返回值)，不能为 nil
/// - Parameter keyword: 关键字，非空
/// - Parameter completion: 异步回调 [匹配的会话搜索结果列表]
///
/// 目前，SDK 内置的文本消息、文件消息、图文消息支持搜索。
/// 自定义的消息必须要实现 RCMessageContent 的 getSearchableWords 接口才能进行搜索。
///
/// conversationTypeList 包含超级群会话类型时，超级群会话只搜索已存储到本地的消息记录。
/// objectNameList 中类型名个数不能超过 300，超过会被截断。
///
/// conversationTypeList 传值时：
/// OC 需转成 NSNumber 传入（例如 @[ @(ConversationType_PRIVATE) ]），
/// Swift 需获取到 rawValue 强转成 NSNumber 传入
/// （例如 let privateType = NSNumber(value: RCConversationType.ConversationType_PRIVATE.rawValue)
/// [privateType]  ）
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)searchConversationsForAllChannel:(NSArray<NSNumber *> *)conversationTypeList
                             messageType:(NSArray<NSString *> *)objectNameList
                                 keyword:(NSString *)keyword
                              completion:(nullable void (^)(NSArray<RCSearchConversationResult *> *_Nullable results))
                                             completion;

#pragma mark - 消息状态


/// 设置超级群频道的默认消息状态
/// 一般由管理员设置的的接口，针对超级群的所有群成员生效，仅针对设置的频道生效，优先级较低。如果群成员自己设置超级群的免打扰级别，那么以群成员自己设置的为准。
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 频道 ID
/// - Parameter level: 消息通知级别
/// - Parameter successBlock: 设置成功的回调
/// - Parameter errorBlock: 设置失败的回调 [status:设置失败的错误码]
///
/// - Remark: 会话
/// - Since: 5.2.2
- (void)setUltraGroupConversationChannelDefaultNotificationLevel:(NSString *)targetId
                                                       channelId:(nullable NSString *)channelId
                                                           level:(RCPushNotificationLevel)level
                                                         success:(nullable void (^)(void))successBlock
                                                           error:(nullable void (^)(RCErrorCode status))errorBlock;


/// 获取超级群频道的默认消息状态
///
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 频道 ID
/// - Parameter successBlock: 设置成功的回调 [level:消息通知级别]
/// - Parameter errorBlock: 设置失败的回调 [status:设置失败的错误码]
///
/// - Remark: 会话
/// - Since: 5.2.2
- (void)getUltraGroupConversationChannelDefaultNotificationLevel:(NSString *)targetId
                                                       channelId:(nullable NSString *)channelId
                                                         success:(nullable void (^)(RCPushNotificationLevel level))
                                                                     successBlock
                                                           error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 屏蔽某个时间段的消息提醒
///
/// - Parameter startTime: 开始消息免打扰时间，格式为 HH:MM:SS
/// - Parameter spanMins: 需要消息免打扰分钟数，0 < spanMins < 1440
/// （比如，您设置的起始时间是 00:00，结束时间为 01:00，则 spanMins 为 60 分钟。设置为 1439 代表全天免打扰（23 * 60 + 59 = 1439））
/// - Parameter level: 消息通知级别
/// - Parameter successBlock: 屏蔽成功的回调
/// - Parameter errorBlock: 屏蔽失败的回调 [status:屏蔽失败的错误码]
///
/// 此方法设置的屏蔽时间会在每天该时间段时生效。
///
/// - Remark: 会话
/// - Since: 5.2.2
- (void)setNotificationQuietHoursLevel:(NSString *)startTime
                              spanMins:(int)spanMins
                                 level:(RCPushNotificationQuietHoursLevel)level
                               success:(nullable void (^)(void))successBlock
                                 error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 屏蔽某个时间段的消息提醒
///
/// - Parameter setting: 消息免打扰配置
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调 [status:屏蔽失败的错误码]
///
/// 此方法设置的屏蔽时间会在每天该时间段时生效。
///
/// - Remark: 会话
/// - Since: 5.14.0
- (void)setNotificationQuietHoursWithSetting:(RCNotificationQuietHoursSetting *)setting
                                     success:(nullable void (^)(void))successBlock
                                       error:(nullable void (^)(RCErrorCode status))errorBlock;


/// 查询已设置的时间段消息提醒屏蔽
///
/// - Parameter successBlock: 屏蔽成功的回调 [startTime:已设置的屏蔽开始时间，
/// spanMins:已设置的屏蔽时间分钟数，0 < spanMins < 1440]，level:消息通知级别
/// - Parameter errorBlock: 查询失败的回调 [status:查询失败的错误码]
///
/// - Remark: 会话
/// - Since: 5.2.2
- (void)getNotificationQuietHoursLevel:(nullable void (^)(NSString *startTime, int spanMins,
                                                          RCPushNotificationQuietHoursLevel level))successBlock
                                 error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 查询已设置的消息提醒屏蔽信息
///
/// - Parameter successBlock: 查询成功的回调。
/// - Parameter errorBlock: 查询失败的回调。
///
/// - Remark: 会话
/// - Since: 5.14.0
- (void)getNotificationQuietHoursSetting:(nullable void (^)(RCNotificationQuietHoursSetting *setting))successBlock
                                   error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 设置会话的消息提醒状态
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter level: 消息通知级别
/// - Parameter successBlock: 设置成功的回调
/// - Parameter errorBlock: 设置失败的回调 [status:设置失败的错误码]
///
/// 如要移除消息提醒状态，设置 level 为 RCPushNotificationLevelDefault
/// 注：超级群调用该接口，相当于设置了 channelId 为 空 的频道的免打扰，不会屏蔽整个超级群会话下所有频道的免打扰
///
/// - Remark: 会话
/// - Since: 5.2.2
- (void)setConversationNotificationLevel:(RCConversationType)conversationType
                                targetId:(NSString *)targetId
                                   level:(RCPushNotificationLevel)level
                                 success:(nullable void (^)(void))successBlock
                                   error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 异步批量设置会话的消息提醒状态
///
/// - Parameter conversationIdentifiers: [RCConversationIdentifier], 最大数量为 20
/// - Parameter level: RCPushNotificationLevel
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调 [status: 失败的错误码]
///
/// 如要移除消息提醒状态，设置 level 为 RCPushNotificationLevelDefault
/// 不支持聊天室
///
/// - Remark: 会话
/// - Since: 5.6.7
- (void)setConversationsNotificationLevel:(NSArray<RCConversationIdentifier *> *)conversationIdentifiers
                                    level:(RCPushNotificationLevel)level
                                  success:(nullable void (^)(void))successBlock
                                    error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 获取会话的消息提醒状态
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter successBlock: 设置成功的回调 [level:消息通知级别]
/// - Parameter errorBlock: 设置失败的回调 [status:设置失败的错误码]
///
/// - Remark: 会话
/// - Since: 5.2.2
- (void)getConversationNotificationLevel:(RCConversationType)conversationType
                                targetId:(NSString *)targetId
                                 success:(nullable void (^)(RCPushNotificationLevel level))successBlock
                                   error:(nullable void (^)(RCErrorCode status))errorBlock;


/// 设置会话类型的消息提醒状态
///
/// - Parameter conversationType: 会话类型
/// - Parameter level: 消息通知级别
/// - Parameter successBlock: 设置成功的回调
/// - Parameter errorBlock: 设置失败的回调 [status:设置失败的错误码]
///
/// 如要移除消息提醒状态，设置 level 为 RCPushNotificationLevelDefault
///
/// - Remark: 会话
/// - Since: 5.2.3

- (void)setConversationTypeNotificationLevel:(RCConversationType)conversationType
                                       level:(RCPushNotificationLevel)level
                                     success:(nullable void (^)(void))successBlock
                                       error:(nullable void (^)(RCErrorCode status))errorBlock;


/// 获取会话类型的消息提醒状态
///
/// - Parameter conversationType: 会话类型
/// - Parameter successBlock: 设置成功的回调 [level:消息通知级别]
/// - Parameter errorBlock: 设置失败的回调 [status:设置失败的错误码]
///
/// - Remark: 会话
/// - Since: 5.2.3

- (void)getConversationTypeNotificationLevel:(RCConversationType)conversationType
                                     success:(nullable void (^)(RCPushNotificationLevel level))successBlock
                                       error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 删除已设置的全局时间段消息提醒屏蔽
///
/// - Parameter successBlock: 删除屏蔽成功的回调
/// - Parameter errorBlock: 删除屏蔽失败的回调 [status:失败的错误码]
///
/// - Remark: 会话
/// - Since: 5.2.2
- (void)removeNotificationQuietHours:(nullable void (^)(void))successBlock
                               error:(nullable void (^)(RCErrorCode status))errorBlock;

#pragma mark-- 超级群

/// 拉取超级群列表后回调功能
///
/// - Parameter delegate: 代理
///
/// 超级群会话同步状态监听，要在初始化之后，连接之前设置代理
/// - Remark: 超级群消息操作
/// - Since: 5.2.2

- (void)setUltraGroupConversationDelegate:(id<RCUltraGroupConversationDelegate>)delegate;

/// 超级群频道信息回调功能
///
/// - Parameter delegate: 代理
///
/// - Remark: 超级群频道操作
/// - Since: 5.2.4

- (void)setUltraGroupChannelDelegate:(id<RCUltraGroupChannelDelegate>)delegate;


/// 获取指定超级群下所有频道的未读消息总数 (子线程回调，如有 UI 操作，请切回主线程)
///
/// - Parameter targetId: 会话 ID
/// - Parameter successBlock: 获取成功的回调 [消息数量]
/// - Parameter errorBlock: 获取失败的回调 [status:清除失败的错误码]
/// - Remark: 超级群消息操作
/// - Since: 5.2.2
- (void)getUltraGroupUnreadCount:(NSString *)targetId
                         success:(nullable void (^)(NSInteger count))successBlock
                           error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 获取超级群会话类型的所有未读消息数 (子线程回调，如有 UI 操作，请切回主线程)
///
/// - Parameter successBlock: 获取成功的回调 [消息数量]
/// - Parameter errorBlock: 获取失败的回调 [status:清除失败的错误码]
/// - Remark: 超级群消息操作
/// - Since: 5.2.2
- (void)getUltraGroupAllUnreadCount:(nullable void (^)(NSInteger count))successBlock
                              error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 获取超级群会话类型的 @ 消息未读数接口 (子线程回调，如有 UI 操作，请切回主线程)
///
/// - Parameter successBlock: 获取成功的回调 [消息数量]
/// - Parameter errorBlock: 获取失败的回调 [status:清除失败的错误码]
/// - Remark: 超级群消息操作
/// - Since: 5.2.2
- (void)getUltraGroupAllUnreadMentionedCount:(nullable void (^)(NSInteger count))successBlock
                                       error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 异步获取某个超级群指定 channel 列表，某段时间范围内的消息数量 (子线程回调，如有 UI 操作，请切回主线程)
///
/// - Parameter targetId: 会话 ID
/// - Parameter channelIds: 频道列表，支持一次查询多个频道，如果为空，则返回全部 channel id 的消息数量
/// - Parameter startTime      查询 startTime 之后的消息，startTime >= 0
/// - Parameter endTime           查询 endTime 之前的消息，endTime > startTime
/// - Parameter success           异步回调 [会话中的消息数量]
/// - Parameter error               错误回调 [错误码]
///
/// - Remark: 超级群消息操作
/// - Since: 5.6.4
- (void)getUltraGroupMessageCountByTimeRange:(NSString *)targetId
                                  channelIds:(NSArray<NSString *> *)channelIds
                                   startTime:(long long)startTime
                                     endTime:(long long)endTime
                                     success:(nullable void (^)(NSInteger count))successBlock
                                       error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 可以获取本地指定超级群下公有频道或者私有频道的列表
/// - Parameter targetId: 会话 ID
/// - Parameter channelType: 频道类型
/// - Parameter successBlock: 获取成功的回调 [会话列表]
/// - Parameter errorBlock: 获取失败的回调 [status:清除失败的错误码]
/// - Remark: 超级群消息操作
/// - Since: 5.2.4
- (void)getUltraGroupChannelList:(NSString *)targetId
                     channelType:(RCUltraGroupChannelType)channelType
                         success:(nullable void (^)(NSArray<RCConversation *> *list))successBlock
                           error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 根据超级群会话 id 数组获取对应的会话对象数组
///
/// - Parameter targetIds: 会话 id 数组，最多 20 个
/// - Parameter successBlock: 成功回调 [会话未读信息数组]
/// - Parameter errorBlock: 失败回调 [失败错误码]
///
/// - Remark: 超级群会话
/// - Since: 5.4.6
- (void)getUltraGroupConversationUnreadInfoList:(nonnull NSArray<NSString *> *)targetIds
                                        success:
                                            (nonnull void (^)(NSArray<RCConversationUnreadInfo *> *list))successBlock
                                          error:(nonnull void (^)(RCErrorCode status))errorBlock;

#pragma mark - 未读数

/// 获取会话未读消息数 (子线程回调，如有 UI 操作，请切回主线程)
/// - Parameter conversationTypes: 会话类型数组：[单聊、群聊、超级群、系统会话]
/// - Parameter levels: 免打扰类型数组 [RCPushNotificationLevel]
/// - Parameter successBlock: 获取成功的回调 [消息数量]
/// - Parameter errorBlock: 获取失败的回调 [status:失败的错误码]
/// - Remark: 单聊、群聊、超级群消息操作
/// - Since: 5.2.5
- (void)getUnreadCount:(nonnull NSArray<NSNumber *> *)conversationTypes
                levels:(nonnull NSArray<NSNumber *> *)levels
               success:(nullable void (^)(NSInteger count))successBlock
                 error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 获取会话未读 @消息数 (子线程回调，如有 UI 操作，请切回主线程)
/// - Parameter conversationTypes: 会话类型数组：[群聊、超级群]
/// - Parameter levels: 免打扰类型数组 [RCPushNotificationLevel]
/// - Parameter successBlock: 获取成功的回调 [消息数量]
/// - Parameter errorBlock: 获取失败的回调 [status:失败的错误码]
/// - Remark: 群聊、超级群消息操作
/// - Since: 5.2.5
- (void)getUnreadMentionedCount:(nonnull NSArray<NSNumber *> *)conversationTypes
                         levels:(nonnull NSArray<NSNumber *> *)levels
                        success:(nullable void (^)(NSInteger count))successBlock
                          error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 获取指定超级群会话的未读消息数（包括所有频道) (子线程回调，如有 UI 操作，请切回主线程)
/// - Parameter targetId: 超级群会话 ID
/// - Parameter levels: 免打扰类型数组 [RCPushNotificationLevel]
/// - Parameter successBlock: 获取成功的回调 [消息数量]
/// - Parameter errorBlock: 获取失败的回调 [status:失败的错误码]
/// - Remark: 超级群消息操作
/// - Since: 5.2.5
- (void)getUltraGroupUnreadCount:(nonnull NSString *)targetId
                          levels:(nonnull NSArray<NSNumber *> *)levels
                         success:(nullable void (^)(NSInteger count))successBlock
                           error:(nullable void (^)(RCErrorCode status))errorBlock;


/// 获取指定超级群会话的未读@消息数（包括所有频道） (子线程回调，如有 UI 操作，请切回主线程)
/// - Parameter targetId: 超级群会话 ID
/// - Parameter levels: 免打扰类型数组 [RCPushNotificationLevel]
/// - Parameter successBlock: 获取成功的回调 [消息数量]
/// - Parameter errorBlock: 获取失败的回调 [status:失败的错误码]
/// - Remark: 超级群消息操作
/// - Since: 5.2.5
- (void)getUltraGroupUnreadMentionedCount:(nonnull NSString *)targetId
                                   levels:(nonnull NSArray<NSNumber *> *)levels
                                  success:(nullable void (^)(NSInteger count))successBlock
                                    error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 获取超级群会话类型未读的 @ 消息摘要列表接口 (子线程回调，如有 UI 操作，请切回主线程)
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter sendTime: 消息发送的时间 [毫秒，0 代表从第一条开始查询]
/// - Parameter count: 查询数量 [1 - 50], 超过范围上报 INVALID_PARAMETER_COUNT 错误码
/// - Parameter successBlock: 获取成功的回调 [消息摘要列表]
/// - Parameter errorBlock: 获取失败的回调 [status:失败的错误码]
/// - Remark: 超级群消息操作
/// - Since: 5.2.5
- (void)getUltraGroupUnreadMentionedDigests:(nonnull NSString *)targetId
                                  channelId:(nullable NSString *)channelId
                                   sendTime:(long long)sendTime
                                      count:(NSInteger)count
                                    success:(nullable void (^)(NSArray<RCMessageDigestInfo *> *digests))successBlock
                                      error:(nullable void (^)(RCErrorCode status))errorBlock;

#pragma mark - 用户组

/// 设置用户组信息回调代理
///
/// - Parameter delegate: 代理
///
/// - Remark: 用户组信息操作
///
/// - Since: 5.4.0
- (void)setUserGroupStatusDelegate:(nullable id<RCUserGroupStatusDelegate>)delegate;


#pragma mark - 已读回执V4


/// 获取某条消息的已读回执信息
/// - Parameters:
/// - targetId: 会话 ID
/// - channelId: 业务 ID
/// - messageUID: 消息 uid
/// - successBlock: 成功回调
/// - errorBlock: 失败回调
/// - Since: 5.6.7

- (void)getMessageReadReceiptV4:(nonnull NSString *)targetId
                      channelId:(nullable NSString *)channelId
                     messageUID:(nonnull NSString *)messageUID
                   successBlock:(nullable void (^)(NSInteger readCount, NSInteger totalCount,
                                                   NSArray<RCGroupMessageReaderV2 *> *list))successBlock
                     errorBlock:(nullable void (^)(RCErrorCode status))errorBlock;


/// 发送消息的已读回执，会将区间内的消息在服务端全部添加已读状态，本地不进行处理。需要 lib 自己调用清除未读等相关接口处理其他业务。
/// - Parameters:
/// - conversationType: 会话类型
/// - targetId: 会话 ID
/// - channelId: 业务 ID
/// - startMessageUID: 开始的消息 UID
/// - endMessageUID: 结束的消息 UID
/// - successBlock: 成功回调
/// - errorBlock: 失败回调
/// - Since: 5.6.7
- (void)sendReadReceiptMessageV4:(RCConversationType)conversationType
                        targetId:(nonnull NSString *)targetId
                       channelId:(nullable NSString *)channelId
                 startMessageUID:(nullable NSString *)startMessageUID
                   endMessageUID:(nonnull NSString *)endMessageUID
                    successBlock:(nullable void (^)(void))successBlock
                      errorBlock:(nullable void (^)(RCErrorCode status))errorBlock;
@end

NS_ASSUME_NONNULL_END
