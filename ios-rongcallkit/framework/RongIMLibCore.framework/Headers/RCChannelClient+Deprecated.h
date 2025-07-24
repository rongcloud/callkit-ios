//
//  RCChannelClient+Deprecated.h
//  RongIMLibCore
//
//  Created by shuai shao on 2023/1/29.
//  Copyright © 2023 RongCloud. All rights reserved.
//

#import <RongIMLibCore/RongIMLibCore.h>

NS_ASSUME_NONNULL_BEGIN

/// - Since: 5.4.1
/// - Warning: 本文件的方法已经过期，请您根据提示使用替代方法。
@interface RCChannelClient (Deprecated)

#pragma mark - 消息发送 -
/// 异步发送消息
///
/// - Parameter conversationType: 发送消息的会话类型
/// - Parameter targetId: 发送消息的会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter content: 消息的内容
/// - Parameter pushContent: 接收方离线时需要显示的远程推送内容
/// - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
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
           attached:(nullable void (^)(RCMessage *_Nullable message))attachedBlock
            success:(nullable void (^)(long messageId))successBlock
              error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock
    __deprecated_msg(
        "Use [RCChannelClient "
        "sendMessage:targetId:channelId:content:pushContent:pushData:option:attached:success:error:] instead");
;

/// 发送消息
///
/// - Parameter conversationType: 发送消息的会话类型
/// - Parameter targetId: 发送消息的会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter content: 消息的内容
/// - Parameter pushContent: 接收方离线时需要显示的远程推送内容
/// - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter successBlock: 消息发送成功的回调 [messageId: 消息的 ID]
/// - Parameter errorBlock: 消息发送失败的回调 [nErrorCode: 发送失败的错误码，
/// messageId:消息的 ID]
/// - Returns: 发送的消息实体
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
/// - Since: 5.1.1
- (nullable RCMessage *)sendMessage:(RCConversationType)conversationType
                           targetId:(NSString *)targetId
                          channelId:(nullable NSString *)channelId
                            content:(RCMessageContent *)content
                        pushContent:(nullable NSString *)pushContent
                           pushData:(nullable NSString *)pushData
                            success:(nullable void (^)(long messageId))successBlock
                              error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock
    __deprecated_msg(
        "Use [RCChannelClient "
        "sendMessage:targetId:channelId:content:pushContent:pushData:option:attached:success:error:] instead");

/// 发送消息
///
/// - Parameter conversationType: 发送消息的会话类型
/// - Parameter targetId: 发送消息的会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter content: 消息的内容
/// - Parameter pushContent: 接收方离线时需要显示的远程推送内容
/// - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter option: 消息的相关配置
/// - Parameter successBlock: 消息发送成功的回调 [messageId: 消息的 ID]
/// - Parameter errorBlock: 消息发送失败的回调 [nErrorCode: 发送失败的错误码，
/// messageId: 消息的 ID]
/// - Returns: 发送的消息实体
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
/// - Since: 5.1.1
- (nullable RCMessage *)sendMessage:(RCConversationType)conversationType
                           targetId:(NSString *)targetId
                          channelId:(nullable NSString *)channelId
                            content:(RCMessageContent *)content
                        pushContent:(nullable NSString *)pushContent
                           pushData:(nullable NSString *)pushData
                             option:(RCSendMessageOption *)option
                            success:(nullable void (^)(long messageId))successBlock
                              error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock
    __deprecated_msg(
        "Use [RCChannelClient "
        "sendMessage:targetId:channelId:content:pushContent:pushData:option:attached:success:error:] instead");

/// 发送媒体消息（图片、文件、视频等消息）
///
/// - Parameter conversationType: 发送消息的会话类型
/// - Parameter targetId: 发送消息的会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter content: 消息的内容
/// - Parameter pushContent: 接收方离线时需要显示的远程推送内容
/// - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter progressBlock: 消息发送进度更新的回调 [progress:当前的发送进度，0
/// <= progress <= 100, messageId:消息的 ID]
/// - Parameter successBlock: 消息发送成功的回调 [messageId:消息的 ID]
/// - Parameter errorBlock: 消息发送失败的回调 [errorCode:发送失败的错误码，
/// messageId:消息的 ID]
/// - Parameter cancelBlock: 用户取消了消息发送的回调 [messageId:消息的 ID]
/// - Returns: 发送的消息实体
///
/// 当接收方离线并允许远程推送时，会收到远程推送。
/// 远程推送中包含两部分内容，一是 pushContent，用于显示；二是 pushData，用于携带不显示的数据。
///
/// SDK 内置的消息类型，如果您将 pushContent 和 pushData 置为 nil，会使用默认的推送格式进行远程推送。
/// 自定义类型的消息，需要您自己设置 pushContent 来定义推送内容，否则将不会进行远程推送。
///
/// 如果您上传媒体文件的文件到自己服务器，需要构建一个媒体消息对象（如图片消息对象 RCImageMessage），并将媒体消息对象的 remoteUrl 字段设置为上传成功的 URL 地址，然后使用 [RCChannelClient sendMessage:targetId:channelId:content:pushContent:pushData:option:attached:success:error:] 方法发送。
///
/// - Warning: 使用此方法发送消息，不会自动更新 UI。
///
/// - Remark: 消息操作
/// - Since: 5.1.1
- (nullable RCMessage *)sendMediaMessage:(RCConversationType)conversationType
                                targetId:(NSString *)targetId
                               channelId:(nullable NSString *)channelId
                                 content:(RCMessageContent *)content
                             pushContent:(nullable NSString *)pushContent
                                pushData:(nullable NSString *)pushData
                                progress:(nullable void (^)(int progress, long messageId))progressBlock
                                 success:(nullable void (^)(long messageId))successBlock
                                   error:(nullable void (^)(RCErrorCode errorCode, long messageId))errorBlock
                                  cancel:(nullable void (^)(long messageId))cancelBlock
    __deprecated_msg("Use [RCChannelClient "
                     "sendMediaMessage:targetId:channelId:content:pushContent:pushData:attached:progress:success:error:"
                     "cancel:] instead");

/// 发送媒体消息 (上传图片或文件等媒体信息到指定的服务器)
///
/// - Parameter conversationType: 发送消息的会话类型
/// - Parameter targetId: 发送消息的会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter content: 消息的内容
/// - Parameter pushContent: 接收方离线时需要显示的远程推送内容
/// - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter uploadPrepareBlock: 媒体文件上传进度更新的监听 [uploadListener:当前的发送进度监听]
/// - Parameter progressBlock: 消息发送进度更新的回调 [progress:当前的发送进度，0
/// <= progress <= 100, messageId:消息的 ID]
/// - Parameter successBlock: 消息发送成功的回调 [messageId:消息的 ID]
/// - Parameter errorBlock: 消息发送失败的回调 [errorCode:发送失败的错误码，
/// messageId:消息的 ID]
/// - Parameter cancelBlock: 用户取消了消息发送的回调 [messageId:消息的 ID]
/// - Returns: 发送的消息实体
///
/// @discussion
/// 如果您使用 IMLibCore 上传媒体文件的文件到自己服务器，需要构建一个媒体消息对象（如图片消息对象 RCImageMessage），并将媒体消息对象的 remoteUrl 字段设置为上传成功的 URL 地址，然后使用 [RCChannelClient sendMessage:targetId:channelId:content:pushContent:pushData:option:attached:success:error:] 方法发送。
///
/// - Remark: 消息操作
/// - Since: 5.1.1
- (nullable RCMessage *)sendMediaMessage:(RCConversationType)conversationType
                                targetId:(NSString *)targetId
                               channelId:(nullable NSString *)channelId
                                 content:(RCMessageContent *)content
                             pushContent:(nullable NSString *)pushContent
                                pushData:(nullable NSString *)pushData
                           uploadPrepare:
                               (nullable void (^)(RCUploadMediaStatusListener *uploadListener))uploadPrepareBlock
                                progress:(nullable void (^)(int progress, long messageId))progressBlock
                                 success:(nullable void (^)(long messageId))successBlock
                                   error:(nullable void (^)(RCErrorCode errorCode, long messageId))errorBlock
                                  cancel:(nullable void (^)(long messageId))cancelBlock
    __deprecated_msg("Use [RCChannelClient "
                     "sendMediaMessage:targetId:channelId:content:pushContent:pushData:attached:uploadPrepare:progress:"
                     "success:error:cancel:] instead");


/// 插入向外发送的、指定时间的消息（此方法如果 sentTime 有问题会影响消息排序，慎用！！）
/// （该消息只插入本地数据库，实际不会发送给服务器和对方）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter sentStatus: 发送状态
/// - Parameter content: 消息的内容
/// - Parameter sentTime: 消息发送的 Unix 时间戳，单位为毫秒（传 0 会按照本地时间插入）
/// - Returns: 插入的消息实体
///
/// 此方法不支持聊天室的会话类型。如果 sentTime<=0，则被忽略，会以插入时的时间为准。
///
/// - Remark: 消息操作
/// - Since: 5.1.1
- (nullable RCMessage *)insertOutgoingMessage:(RCConversationType)conversationType
                                     targetId:(NSString *)targetId
                                    channelId:(nullable NSString *)channelId
                                   sentStatus:(RCSentStatus)sentStatus
                                      content:(RCMessageContent *)content
                                     sentTime:(long long)sentTime
    __deprecated_msg("Use [RCChannelClient "
                     "insertOutgoingMessage:targetId:channelId:canIncludeExpansion:sentStatus:content:sentTime:"
                     "completion:] instead");

/// 异步插入向外发送的、指定时间的消息（此方法如果 sentTime 有问题会影响消息排序，慎用！！）
/// （该消息只插入本地数据库，实际不会发送给服务器和对方）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter sentStatus: 发送状态
/// - Parameter content: 消息的内容
/// - Parameter sentTime: 消息发送的 Unix 时间戳，单位为毫秒（传 0 会按照本地时间插入）
/// - Parameter completion: 异步回调 [发送的消息实体]
///
/// 此方法不支持聊天室的会话类型。如果 sentTime<=0，则被忽略，会以插入时的时间为准。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)insertOutgoingMessage:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                    channelId:(nullable NSString *)channelId
                   sentStatus:(RCSentStatus)sentStatus
                      content:(RCMessageContent *)content
                     sentTime:(long long)sentTime
                   completion:(nullable void (^)(RCMessage *_Nullable message))completion
    __deprecated_msg("Use [RCChannelClient "
                     "insertOutgoingMessage:targetId:channelId:canIncludeExpansion:sentStatus:content:sentTime:"
                     "completion:] instead");

/// 插入接收的消息（此方法如果 sentTime
/// 有问题会影响消息排序，慎用！！）（该消息只插入本地数据库，实际不会发送给服务器和对方）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter senderUserId: 发送者 ID
/// - Parameter receivedStatus: 接收状态
/// - Parameter content: 消息的内容
/// - Parameter sentTime: 消息发送的 Unix 时间戳，单位为毫秒（传 0 会按照本地时间插入）
/// - Returns: 插入的消息实体
///
/// 此方法不支持聊天室的会话类型。
///
/// - Remark: 消息操作
/// - Since: 5.1.1
- (nullable RCMessage *)insertIncomingMessage:(RCConversationType)conversationType
                                     targetId:(NSString *)targetId
                                    channelId:(nullable NSString *)channelId
                                 senderUserId:(NSString *)senderUserId
                               receivedStatus:(RCReceivedStatus)receivedStatus
                                      content:(RCMessageContent *)content
                                     sentTime:(long long)sentTime
    __deprecated_msg("Use [RCChannelClient "
                     "insertIncomingMessage:targetId:channelId:senderUserId:receivedStatusInfo:content:sentTime:"
                     "completion:] instead");

/// 异步插入接收的消息（此方法如果 sentTime
/// 有问题会影响消息排序，慎用！！）（该消息只插入本地数据库，实际不会发送给服务器和对方）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter senderUserId: 发送者 ID
/// - Parameter receivedStatus: 接收状态
/// - Parameter content: 消息的内容
/// - Parameter sentTime: 消息发送的 Unix 时间戳，单位：毫秒（传 0 会按照本地时间插入）
/// - Parameter completion: 异步回调 [插入的消息实体]
///
/// 此方法不支持聊天室的会话类型。如果 sentTime <= 0，则被忽略，会以插入时的时间为准。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)insertIncomingMessage:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                    channelId:(nullable NSString *)channelId
                 senderUserId:(NSString *)senderUserId
               receivedStatus:(RCReceivedStatus)receivedStatus
                      content:(RCMessageContent *)content
                     sentTime:(long long)sentTime
                   completion:(nullable void (^)(RCMessage *_Nullable message))completion
    __deprecated_msg("Use [RCChannelClient "
                     "insertIncomingMessage:targetId:channelId:senderUserId:receivedStatusInfo:content:sentTime:"
                     "completion:] instead");

/// 发送定向消息
///
/// - Parameter conversationType: 发送消息的会话类型
/// - Parameter targetId: 发送消息的会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter userIdList: 接收消息的用户 ID 列表
/// - Parameter content: 消息的内容
/// - Parameter pushContent: 接收方离线时需要显示的远程推送内容
/// - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter successBlock: 消息发送成功的回调 [messageId:消息的 ID]
/// - Parameter errorBlock: 消息发送失败的回调 [errorCode:发送失败的错误码，messageId:消息的 ID]
///
/// - Returns: 发送的消息实体
///
/// 此方法用于在群组和讨论组中发送消息给其中的部分用户，其它用户不会收到这条消息。
/// userIdLis t 里 ID 个数不能超过 300，超过会被截断。
///
/// - Warning: 此方法目前仅支持普通群组和讨论组。
///
/// - Remark: 消息操作
/// - Since: 5.1.1
- (nullable RCMessage *)sendDirectionalMessage:(RCConversationType)conversationType
                                      targetId:(NSString *)targetId
                                     channelId:(nullable NSString *)channelId
                                  toUserIdList:(NSArray<NSString *> *)userIdList
                                       content:(RCMessageContent *)content
                                   pushContent:(nullable NSString *)pushContent
                                      pushData:(nullable NSString *)pushData
                                       success:(nullable void (^)(long messageId))successBlock
                                         error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock
    __deprecated_msg("Use [RCChannelClient "
                     "sendDirectionalMessage:targetId:channelId:toUserIdList:content:pushContent:pushData:option:"
                     "attached:success:error:] instead");

/// 发送定向消息
///
/// - Parameter conversationType: 发送消息的会话类型
/// - Parameter targetId: 发送消息的会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter userIdList: 接收消息的用户 ID 列表
/// - Parameter content: 消息的内容
/// - Parameter pushContent: 接收方离线时需要显示的远程推送内容
/// - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter option: 消息的相关配置
/// - Parameter successBlock: 消息发送成功的回调 [messageId:消息的 ID]
/// - Parameter errorBlock: 消息发送失败的回调 [errorCode:发送失败的错误码，
/// messageId:消息的 ID]
///
/// - Returns: 发送的消息实体
///
/// 此方法用于在群组和讨论组中发送消息给其中的部分用户，其它用户不会收到这条消息。
/// userIdList 里 ID 个数不能超过 300，超过会被截断。
///
/// - Warning: 此方法目前仅支持普通群组和讨论组。
///
/// - Remark: 消息操作
/// - Since: 5.1.2
- (nullable RCMessage *)sendDirectionalMessage:(RCConversationType)conversationType
                                      targetId:(NSString *)targetId
                                     channelId:(nullable NSString *)channelId
                                  toUserIdList:(NSArray<NSString *> *)userIdList
                                       content:(RCMessageContent *)content
                                   pushContent:(nullable NSString *)pushContent
                                      pushData:(nullable NSString *)pushData
                                        option:(RCSendMessageOption *)option
                                       success:(nullable void (^)(long messageId))successBlock
                                         error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock
    __deprecated_msg("Use [RCChannelClient "
                     "sendDirectionalMessage:targetId:channelId:toUserIdList:content:pushContent:pushData:option:"
                     "attached:success:error:] instead");

/// 异步发送定向消息
///
/// - Parameter conversationType: 发送消息的会话类型
/// - Parameter targetId: 发送消息的会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter userIdList: 接收消息的用户 ID 列表
/// - Parameter content: 消息的内容
/// - Parameter pushContent: 接收方离线时需要显示的远程推送内容
/// - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter attachedBlock: 入库回调 [message: 已存数据库的消息体]
/// - Parameter successBlock: 消息发送成功的回调 [messageId:消息的 ID]
/// - Parameter errorBlock: 消息发送失败的回调 [errorCode:发送失败的错误码，
/// messageId:消息的 ID]
///
/// 此方法用于在群组和讨论组中发送消息给其中的部分用户，其它用户不会收到这条消息。
/// userIdLis t 里 ID 个数不能超过 300，超过会被截断。
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
                      attached:(nullable void (^)(RCMessage *_Nullable message))attachedBlock
                       success:(nullable void (^)(long messageId))successBlock
                         error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock
    __deprecated_msg("Use [RCChannelClient "
                     "sendDirectionalMessage:targetId:channelId:toUserIdList:content:pushContent:pushData:option:"
                     "attached:success:error:] instead");

#pragma mark - 消息操作 -

/// 获取某个会话中指定数量的最新消息实体（按照时间从新到旧排列）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter count: 需要获取的消息数量
/// - Returns: 消息实体 RCMessage 对象列表
///
/// - Remark: 消息操作
/// - Since: 5.1.1
- (nullable NSArray<RCMessage *> *)getLatestMessages:(RCConversationType)conversationType
                                            targetId:(NSString *)targetId
                                           channelId:(nullable NSString *)channelId
                                               count:(int)count
    __deprecated_msg("Use [RCChannelClient getLatestMessages:targetId:channelId:count:completion:] instead");

/// 获取会话中，从指定消息之前、指定数量的最新消息实体（按照时间从新到旧排列）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter oldestMessageId: 截止的消息 ID [0 或 -1 代表从最近的发送时间查起]
/// - Parameter count: 需要获取的消息数量
/// - Returns: 消息实体 RCMessage 对象列表
///
/// 返回的消息中不包含 oldestMessageId 对应那条消息。
/// 如：oldestMessageId 为 10，count 为 2，会返回 messageId 为 9 和 8 的 RCMessage 对象列表。
///
/// 此方法不支持超级群的会话类型。
///
/// - Remark: 消息操作
/// - Since: 5.1.1
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                             targetId:(NSString *)targetId
                                            channelId:(nullable NSString *)channelId
                                      oldestMessageId:(long)oldestMessageId
                                                count:(int)count
    __deprecated_msg(
        "Use [RCChannelClient getHistoryMessages:targetId:channelId:oldestMessageId:count:completion:] instead");

/// 获取会话中，从指定消息之前、指定数量的、指定消息类型的最新消息实体（按照时间从新到旧排列）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter objectName: 消息内容的类型名，如果想取全部类型的消息请传 nil
/// - Parameter oldestMessageId: 截止的消息 ID [0 或 -1 代表从最近的发送时间查起]
/// - Parameter count: 需要获取的消息数量
/// - Returns: 消息实体 RCMessage 对象列表
///
/// 返回的消息中不包含 oldestMessageId 对应的那条消息。
/// 如：oldestMessageId 为 10，count 为 2，会返回 messageId 为 9 和 8 的 RCMessage 对象列表。
///
/// 此方法不支持超级群的会话类型。
///
/// - Remark: 消息操作
/// - Since: 5.1.1
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                             targetId:(NSString *)targetId
                                            channelId:(nullable NSString *)channelId
                                           objectName:(nullable NSString *)objectName
                                      oldestMessageId:(long)oldestMessageId
                                                count:(int)count
    __deprecated_msg("Use [RCChannelClient "
                     "getHistoryMessages:targetId:channelId:objectName:oldestMessageId:count:completion:] instead");

/// 获取会话中，指定消息、指定数量、指定消息类型、向前或向后查找的消息实体列表（按照时间从新到旧排列）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter objectName: 消息内容的类型名，如果想取全部类型的消息请传 nil
/// - Parameter baseMessageId: 当前的消息 ID [0 或 -1 代表从最近的发送时间查起]
/// - Parameter isForward: 查询方向 true 为向前，false 为向后
/// - Parameter count: 需要获取的消息数量
/// - Returns: 消息实体 RCMessage 对象列表
///
/// 返回的消息中不包含 baseMessageId 对应的那条消息。
///
/// 超级群不会接收离线消息，超级群调用该接口会出现消息断档的情况，请使用断档消息接口获取超级群消息。
///
/// - Remark: 消息操作
/// - Since: 5.1.1
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                             targetId:(NSString *)targetId
                                            channelId:(nullable NSString *)channelId
                                           objectName:(nullable NSString *)objectName
                                        baseMessageId:(long)baseMessageId
                                            isForward:(BOOL)isForward
                                                count:(int)count
    __deprecated_msg(
        "Use [RCChannelClient "
        "getHistoryMessages:targetId:channelId:objectName:baseMessageId:isForward:count:completion:] instead");

/// 获取会话中，指定时间、指定数量、指定消息类型（多个）、向前或向后查找的消息实体列表（按照时间从新到旧排列）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter objectNames: 消息内容的类型名称列表
/// - Parameter sentTime: 当前的消息时间戳
/// - Parameter isForward: 查询方向 true 为向前，false 为向后
/// - Parameter count: 需要获取的消息数量
/// - Returns: 消息实体 RCMessage 对象列表
///
/// 返回的消息中不包含 sentTime 对应的那条消息。
/// 超级群不会接收离线消息，超级群调用该接口会出现消息断档的情况，请使用断档消息接口获取超级群消息。
///
/// - Remark: 消息操作
/// - Since: 5.1.1
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                             targetId:(NSString *)targetId
                                            channelId:(nullable NSString *)channelId
                                          objectNames:(NSArray<NSString *> *)objectNames
                                             sentTime:(long long)sentTime
                                            isForward:(BOOL)isForward
                                                count:(int)count
    __deprecated_msg("Use [RCChannelClient "
                     "getHistoryMessages:targetId:channelId:objectName:sentTime:isForward:count:completion:] instead");

/// 在会话中搜索指定消息的前 beforeCount 数量和后 afterCount 数量的消息。返回的消息列表中会包含指定的消息（按照时间从新到旧排列）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter sentTime: 消息的发送时间
/// - Parameter beforeCount: 指定消息的前部分消息数量
/// - Parameter afterCount: 指定消息的后部分消息数量
/// - Returns: 消息实体 RCMessage 对象列表
///
/// 此方法不支持超级群的会话类型。
///
/// - Remark: 消息操作
/// - Since: 5.1.1
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                             targetId:(NSString *)targetId
                                            channelId:(nullable NSString *)channelId
                                             sentTime:(long long)sentTime
                                          beforeCount:(int)beforeCount
                                           afterCount:(int)afterCount
    __deprecated_msg("Use [RCChannelClient "
                     "getHistoryMessages:targetId:channelId:sentTime:beforeCount:afterCount:completion:] instead");
;

/// 从服务器端获取之前的历史消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter recordTime: 截止的消息发送时间戳，毫秒
/// - Parameter count: 需要获取的消息数量，1 < count <= 100
/// - Parameter successBlock: 获取成功的回调 [messages:获取到的历史消息数组，isRemaining 是否还有剩余消息 YES
/// 表示还有剩余，NO 表示无剩余]
/// - Parameter errorBlock: 获取失败的回调 [status:获取失败的错误码]
///
/// @discussion
/// 此方法从服务器端获取之前的历史消息，但是必须先开通历史消息云存储功能。
///
/// 本地数据库可以查到的消息，该接口不会再返回，所以建议先用 getHistoryMessages
/// 相关接口取本地历史消息，本地消息取完之后再通过该接口获取远端历史消息
///
/// - Remark: 消息操作
/// - Since: 5.1.1
- (void)getRemoteHistoryMessages:(RCConversationType)conversationType
                        targetId:(NSString *)targetId
                       channelId:(nullable NSString *)channelId
                      recordTime:(long long)recordTime
                           count:(int)count
                         success:(nullable void (^)(NSArray<RCMessage *> *messages, BOOL isRemaining))successBlock
                           error:(nullable void (^)(RCErrorCode status))errorBlock
    __deprecated_msg("Use [RCChannelClient getRemoteHistoryMessages:targetId:channelId:option:success:error:] instead");

/// 获取历史消息（仅支持单群聊）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter option: 可配置的参数
/// - Parameter complete: 获取成功的回调 [messages：获取到的历史消息数组；code : 获取是否成功，0 表示成功，非 0 表示失败，此时 messages 数组可能存在断档]
///
/// 必须开通历史消息云存储功能。
/// 此方法先从本地获取历史消息，本地有缺失的情况下会从服务端同步缺失的部分。当本地没有更多消息的时候，会从服务器拉取
/// 从服务端同步失败的时候会返回非 0 的 errorCode，同时把本地能取到的消息回调上去。
///
/// - Remark: 消息操作
/// - Since: 5.1.2
- (void)getMessages:(RCConversationType)conversationType
           targetId:(NSString *)targetId
          channelId:(nullable NSString *)channelId
             option:(RCHistoryMessageOption *)option
           complete:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages, RCErrorCode code))complete;

/// 获取会话中 @ 提醒自己的消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
///
/// 最多返回 10 条@提醒的消息
/// - Warning: 使用 IMKit 注意在进入会话页面前调用，否则在进入会话会调用清除未读数的接口 clearMessagesUnreadStatus: targetId:
/// 以及设置消息接收状态接口 setMessageReceivedStatus:receivedStatus: 会同步清除 @ 提醒信息状态。
///
/// - Remark: 高级功能
/// - Since: 5.1.1
- (nullable NSArray<RCMessage *> *)getUnreadMentionedMessages:(RCConversationType)conversationType
                                                     targetId:(NSString *)targetId
                                                    channelId:(nullable NSString *)channelId
    __deprecated_msg("Use [RCChannelClient getUnreadMentionedMessages:targetId:channelId:completion:] instead");

/// 获取本地指定会话的未读条数的 @ 消息列表，仅支持群组
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter count: 未读的 @ 消息，取值范围 [1,100]
/// - Parameter desc: 是否是降序查
/// 假如有 1000 条未读的 @ 消息，取 100 条未读
/// desc 为 true 时获取后 100 条消息，messageList 的顺序是 901 到 1000
/// desc 为 false 是获取前 100 条消息，messageList 的顺序是 1 到 100
///
/// - Warning: 使用 IMKit 注意在进入会话页面前调用，否则在进入会话会调用清除未读数的接口 clearMessagesUnreadStatus: targetId:
/// 以及设置消息接收状态接口 setMessageReceivedStatus:receivedStatus: 会同步清除 @ 提醒信息状态。
/// 5.1.9 stable 单独添加该接口
/// - Since: 5.2.5

- (nullable NSArray<RCMessage *> *)getUnreadMentionedMessages:(RCConversationType)conversationType
                                                     targetId:(NSString *)targetId
                                                    channelId:(nullable NSString *)channelId
                                                        count:(int)count
                                                         desc:(BOOL)desc
    __deprecated_msg(
        "Use [RCChannelClient getUnreadMentionedMessages:targetId:channelId:count:desc:completion:] instead");

/// 根据会话 id 获取所有子频道的 @ 未读消息总数
///
/// - Parameter targetId: 会话 ID
/// - Returns: 该会话内的未读消息数
///
/// - Remark: 超级群消息操作
/// - Since: 5.2.0
- (int)getUltraGroupUnreadMentionedCount:(NSString *)targetId
    __deprecated_msg("Use [RCChannelClient getUltraGroupUnreadMentionedCount:completion:] instead");

/// 撤回消息
///
/// - Parameter message: 需要撤回的消息
/// - Parameter successBlock: 撤回成功的回调 [messageId:撤回的消息 ID，该消息已经变更为新的消息 `RCRecallNotificationMessage`]
/// - Parameter errorBlock: 撤回失败的回调 [errorCode:撤回失败错误码]
/// - Remark: 高级功能
/// - Since: 5.2.0
- (void)recallUltraGroupMessage:(RCMessage *)message
                        success:(nullable void (^)(long messageId))successBlock
                          error:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 获取会话里第一条未读消息。
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Returns: 第一条未读消息的实体。
///
/// 前提：超级群会话不接收离线消息。
/// 用户在线接收的超级群未读消息已经保存到本地数据库，可以通过此接口获取到
/// 用户离线的超级群未读消息，用户在线之后不收离线未读消息，通过此接口获取第一条未读消息为空
/// - Remark: 消息操作
/// - Since: 5.1.1
- (nullable RCMessage *)getFirstUnreadMessage:(RCConversationType)conversationType
                                     targetId:(NSString *)targetId
                                    channelId:(nullable NSString *)channelId
    __deprecated_msg("Use [RCChannelClient getFirstUnreadMessage:targetId:channelId:completion:] instead");

/// 删除本地所有 channel 特定时间之前的消息
///
/// - Parameter targetId: 会话 ID
/// - Parameter timestamp: 会话的时间戳，单位：毫秒
/// - Returns: 是否删除成功
///
/// - Remark: 消息操作
/// - Since: 5.2.0
- (BOOL)deleteUltraGroupMessagesForAllChannel:(NSString *)targetId
                                    timestamp:(long long)timestamp
    __deprecated_msg("Use [RCChannelClient deleteUltraGroupMessagesForAllChannel:timestamp:completion:] instead");

/// 删除本地特定 channel 特点时间之前的消息
///
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 频道 ID
/// - Parameter timestamp: 会话的时间戳，单位：毫秒
/// - Returns: 是否删除成功
///
/// - Remark: 消息操作
/// - Since: 5.2.0
- (BOOL)deleteUltraGroupMessages:(NSString *)targetId
                       channelId:(nullable NSString *)channelId
                       timestamp:(long long)timestamp
    __deprecated_msg("Use [RCChannelClient deleteUltraGroupMessages:channelId:timestamp:completion:] instead");

/// 删除某个会话中的所有消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Returns: 是否删除成功
///
/// - Remark: 消息操作
/// - Since: 5.1.1
- (BOOL)clearMessages:(RCConversationType)conversationType
             targetId:(NSString *)targetId
            channelId:(nullable NSString *)channelId
    __deprecated_msg("Use [RCChannelClient clearMessages:targetId:channelId:completion:] instead");

#pragma mark - 会话列表操作 -

/// 获取本地会话列表（按照时间从新到旧排列，如果有置顶的会话，则置顶的会话会排列在前面）
///
/// - Parameter conversationTypeList: 会话类型的数组 (需要将 RCConversationType 转为 NSNumber 构建 NSArray)
/// - Parameter channelId: 所属会话的业务标识
/// - Returns: 会话 RCConversation 的列表
///
/// 当您的会话较多且没有清理机制的时候，强烈建议您使用 getConversationList: count: startTime:
/// 分页拉取会话列表，否则有可能造成内存过大。
///
/// - Remark: 会话列表
/// - Since: 5.1.1
- (nullable NSArray<RCConversation *> *)getConversationList:(NSArray<NSNumber *> *)conversationTypeList
                                                  channelId:(nullable NSString *)channelId
    __deprecated_msg("Use [RCChannelClient getConversationList:channelId:completion:] instead");

/// 分页获取本地会话列表（按照时间从新到旧排列，如果有置顶的会话，则置顶的会话会排列在前面）
///
/// - Parameter conversationTypeList: 会话类型的数组 (需要将 RCConversationType 转为 NSNumber 构建 NSArray)
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter count: 获取的数量（当实际取回的会话数量小于 count 值时，表明已取完数据）
/// - Parameter startTime: 会话的时间戳（获取这个时间戳之前的会话列表，0 表示从最新开始获取）
/// - Returns: 会话 RCConversation 的列表
///
/// - Remark: 会话列表
/// - Since: 5.1.1
- (nullable NSArray<RCConversation *> *)getConversationList:(NSArray<NSNumber *> *)conversationTypeList
                                                  channelId:(nullable NSString *)channelId
                                                      count:(int)count
                                                  startTime:(long long)startTime
    __deprecated_msg("Use [RCChannelClient getConversationList:channelId:count:startTime:completion:] instead");

/// 获取本地特定会话下所有频道的会话列表（按照时间从新到旧排列，如果有置顶的会话，则置顶的会话会排列在前面）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Returns: 会话 RCConversation 的列表
///
/// - Remark: 会话列表
/// - Since: 5.2.0
- (nullable NSArray<RCConversation *> *)getConversationListForAllChannel:(RCConversationType)conversationType
                                                                targetId:(NSString *)targetId
    __deprecated_msg("Use [RCChannelClient getConversationListForAllChannel:targetId:completion:] instead");

/// 分页获取本地特定会话类型下所有 channel 的会话列表（按照时间从新到旧排列，如果有置顶的会话，则置顶的会话会排列在前面）
/// - Parameter conversationTypeList: 会话类型数组
/// - Parameter count: 会话个数
/// - Parameter startTime: 开始时间，首次可传入 0
/// - Returns: 会话 RCConversation 的列表
///
/// - Since: 5.2.3
- (nullable NSArray<RCConversation *> *)getConversationListForAllChannel:(NSArray<NSNumber *> *)conversationTypeList
                                                                   count:(int)count
                                                               startTime:(long long)startTime
    __deprecated_msg("Use [RCChannelClient getConversationListForAllChannel:count:startTime:completion:] instead");

/// 获取本地所有含 ChannelId 会话列表（按照时间从新到旧排列，如果有置顶的会话，则置顶的会话会排列在前面）
///
/// - Parameter conversationTypeList: 会话类型的数组 (需要将 RCConversationType 转为 NSNumber 构建 NSArray)
/// - Returns: 会话 RCConversation 的列表
///
/// - Warning: 当会话数量多的时候，会有性能问题，所以建议在非主线程调用该接口
/// - Remark: 会话列表
/// - Since: 5.2.3
- (nullable NSArray<RCConversation *> *)getConversationListForAllChannel:(NSArray<NSNumber *> *)conversationTypeList
    __deprecated_msg("Use [RCChannelClient getConversationListForAllChannel:completion:] instead");

/// 获取本地单个会话数据
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Returns: 会话的对象
///
/// - Remark: 会话
/// - Since: 5.1.1
- (nullable RCConversation *)getConversation:(RCConversationType)conversationType
                                    targetId:(NSString *)targetId
                                   channelId:(nullable NSString *)channelId
    __deprecated_msg("Use [RCChannelClient getConversation:targetId:channelId:completion:] instead");

/// 获取会话中的消息数量
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
///
/// - Remark: 会话
/// - Since: 5.1.1
- (int)getMessageCount:(RCConversationType)conversationType
              targetId:(NSString *)targetId
             channelId:(nullable NSString *)channelId
    __deprecated_msg("Use [RCChannelClient getMessageCount:targetId:channelId:completion:] instead");

/// 删除本地指定类型的会话
///
/// - Parameter conversationTypeList: 会话类型的数组 (需要将 RCConversationType 转为 NSNumber 构建 NSArray)
/// - Parameter channelId: 所属会话的业务标识
/// - Returns: 是否删除成功
///
/// 此方法会从本地存储中删除该会话，同时删除会话中的消息。
/// 此方法不支持超级群的会话类型，包含超级群时可能会造成数据异常。
///
/// - Remark: 会话
/// - Since: 5.1.1
- (BOOL)clearConversations:(NSArray<NSNumber *> *)conversationTypeList
                 channelId:(nullable NSString *)channelId
    __deprecated_msg("Use [RCChannelClient clearConversations:channelId:completion:] instead");

/// 删除本地和服务的会话
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Returns: 本地会话是否删除成功
///
/// 此方法会同时删除本地和服务的会话，但是不会删除会话中的消息。如果此会话中有新的消息，该会话将重新在会话列表中显示，并显示最近的历史消息。
/// - Warning: 如果服务的会话删除失败，本地的会话依然会被删除。SDK 在未连接的情况下，删除服务会话会失败
///
/// - Remark: 会话
/// - Since: 5.1.1
- (BOOL)removeConversation:(RCConversationType)conversationType
                  targetId:(NSString *)targetId
                 channelId:(nullable NSString *)channelId
    __deprecated_msg("Use [RCChannelClient removeConversation:targetId:channelId:completion:] instead");

/// 设置会话的置顶状态
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter isTop: 是否置顶
/// - Returns: 设置是否成功
///
/// 会话不存在时设置置顶，会在会话列表生成会话。
///
/// - Remark: 会话
/// - Since: 5.1.1
- (BOOL)setConversationToTop:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
                   channelId:(nullable NSString *)channelId
                       isTop:(BOOL)isTop
    __deprecated_msg("Use [RCChannelClient setConversationToTop:targetId:channelId:isTop:completion:] instead");

/// 获取本地会话的置顶状态
///
/// - Parameter conversationIdentifier: 会话信息
/// - Parameter channelId: 所属会话的业务标识
///
/// - Remark: 会话
/// - Since: 5.1.5
- (BOOL)getConversationTopStatus:(RCConversationIdentifier *)conversationIdentifier
                       channelId:(nullable NSString *)channelId
    __deprecated_msg("Use [RCChannelClient getConversationTopStatus:channelId:completion:] instead");

/// 获取本地置顶的会话列表
///
/// - Parameter conversationTypeList: 会话类型的数组 (需要将 RCConversationType 转为 NSNumber 构建 NSArray)
/// - Returns: 置顶的会话 RCConversation 的列表
///
/// - Remark: 会话列表
/// - Since: 5.1.1
- (nullable NSArray<RCConversation *> *)getTopConversationList:(NSArray<NSNumber *> *)conversationTypeList
                                                     channelId:(nullable NSString *)channelId
    __deprecated_msg("Use [RCChannelClient getTopConversationList:channelId:completion:] instead");

#pragma mark - 会话中的草稿操作 -

/// 获取会话中的草稿信息（用户输入但未发送的暂存消息）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话目标 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Returns: 该会话中的草稿
///
/// - Remark: 会话
/// - Since: 5.1.1
- (nullable NSString *)getTextMessageDraft:(RCConversationType)conversationType
                                  targetId:(NSString *)targetId
                                 channelId:(nullable NSString *)channelId
    __deprecated_msg("Use [RCChannelClient getTextMessageDraft:targetId:channelId:completion:] instead");

/// 保存草稿信息（用户输入但未发送的暂存消息）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话目标 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter content: 草稿信息
/// - Returns: 是否保存成功
///
/// - Remark: 会话
/// - Since: 5.1.1
- (BOOL)saveTextMessageDraft:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
                   channelId:(nullable NSString *)channelId
                     content:(NSString *)content
    __deprecated_msg("Use [RCChannelClient saveTextMessageDraft:targetId:channelId:content:completion:] instead");

/// 删除会话中的草稿信息（用户输入但未发送的暂存消息）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话目标 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Returns: 是否删除成功
///
/// - Remark: 会话
/// - Since: 5.1.1
- (BOOL)clearTextMessageDraft:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                    channelId:(nullable NSString *)channelId
    __deprecated_msg("Use [RCChannelClient clearTextMessageDraft:targetId:channelId:completion:] instead");

#pragma mark - 未读消息数 -

/// 获取所有的未读消息数（聊天室会话除外）
///
/// - Parameter channelId: 所属会话的业务标识
///
/// - Returns: 所有的未读消息数（含免打扰会话未读数）
///
/// - Remark: 会话
/// - Since: 5.1.1
- (int)getTotalUnreadCountWithChannelId:(nullable NSString *)channelId
    __deprecated_msg("Use [RCChannelClient getTotalUnreadCountWithChannelId:completion:] instead");

/// 获取所有的未读消息数（聊天室会话除外）
///
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter isContain: 是否包含免打扰会话的未读数，YES 包含免打扰会话未读数
///
/// - Returns: 所有的未读消息数
///
/// - Remark: 会话
/// - Since: 5.2.3
- (int)getTotalUnreadCountWithChannelId:(nullable NSString *)channelId
                         containBlocked:(BOOL)isContain
    __deprecated_msg("Use [RCChannelClient getTotalUnreadCountWithChannelId:containBlocked:completion:] instead");

/// 获取某个会话内的未读消息数（聊天室会话除外）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话目标 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Returns: 该会话内的未读消息数
///
/// - Remark: 会话
/// - Since: 5.1.1
- (int)getUnreadCount:(RCConversationType)conversationType
             targetId:(NSString *)targetId
            channelId:(nullable NSString *)channelId
    __deprecated_msg("Use [RCChannelClient getUnreadCount:targetId:channelId:completion:] instead");

/// 获取某个会话内的未读消息数
///
/// - Parameter conversationIdentifier: 会话信息
/// - Parameter messageClassList: 消息类型数组
/// - Parameter channelId: 所属会话的业务标识
/// - Returns: 该会话内的未读消息数
///
/// 此方法不支持聊天室和超级群的会话类型。
///
/// - Remark: 会话
/// - Since: 5.1.5
- (int)getUnreadCount:(RCConversationIdentifier *)conversationIdentifier
     messageClassList:(NSArray<Class> *)messageClassList
            channelId:(nullable NSString *)channelId
    __deprecated_msg("Use [RCChannelClient getUnreadCount:messageClassList:channelId:completion:] instead");


/// 获取某些类型的会话中所有的未读消息数（聊天室会话除外）
///
/// - Parameter conversationTypes: 会话类型的数组
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter isContain: 是否包含免打扰消息的未读数
/// - Returns: 该类型的会话中所有的未读消息数
///
/// - Remark: 会话
/// - Since: 5.1.1
- (int)getUnreadCount:(NSArray<NSNumber *> *)conversationTypes
            channelId:(nullable NSString *)channelId
       containBlocked:(bool)isContain
    __deprecated_msg("Use [RCChannelClient getUnreadCount:channelId:containBlocked:completion:] instead");

/// 获取某个类型的会话中所有未读的被 @ 的消息数
///
/// - Parameter conversationTypes: 会话类型的数组
/// - Parameter channelId: 所属会话的业务标识
/// - Returns: 该类型的会话中所有未读的被 @ 的消息数
///
/// - Remark: 会话
/// - Since: 5.1.1
- (int)getUnreadMentionedCount:(NSArray<NSNumber *> *)conversationTypes
                     channelId:(nullable NSString *)channelId
    __deprecated_msg("Use [RCChannelClient getUnreadMentionedCount:channelId:completion:] instead");

/// 清除某个会话中的未读消息数
///
/// - Parameter conversationType: 会话类型，不支持聊天室
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Returns: 是否清除成功
///
/// - Remark: 会话
/// - Since: 5.1.1
- (BOOL)clearMessagesUnreadStatus:(RCConversationType)conversationType
                         targetId:(NSString *)targetId
                        channelId:(nullable NSString *)channelId
    __deprecated_msg("Use [RCChannelClient clearMessagesUnreadStatus:targetId:channelId:completion:] instead");

/// 清除某个会话中的未读消息数（该会话在时间戳 timestamp 之前的消息将被置成已读。）
///
/// - Parameter conversationType: 会话类型，不支持聊天室
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter timestamp: 该会话已阅读的最后一条消息的发送时间戳
/// - Returns: 是否清除成功
///
/// - Remark: 会话
/// - Since: 5.1.1
- (BOOL)clearMessagesUnreadStatus:(RCConversationType)conversationType
                         targetId:(NSString *)targetId
                        channelId:(nullable NSString *)channelId
                             time:(long long)timestamp
    __deprecated_msg("Use [RCChannelClient clearMessagesUnreadStatus:targetId:channelId:time:completion:] instead");

#pragma mark - 会话的消息提醒 -

/// 设置会话的消息提醒状态
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter isBlocked: 是否屏蔽消息提醒
/// - Parameter successBlock: 设置成功的回调 [nStatus:会话设置的消息提醒状态]
/// - Parameter errorBlock: 设置失败的回调 [status:设置失败的错误码]
///
/// 如果您使用 IMLibCore，此方法会屏蔽该会话的远程推送；
/// 如果您使用 IMKit，此方法会屏蔽该会话的所有提醒（远程推送、本地通知、前台提示音）,该接口不支持聊天室。
///
/// - Remark: 会话
/// - Since: 5.1.1
- (void)setConversationNotificationStatus:(RCConversationType)conversationType
                                 targetId:(NSString *)targetId
                                channelId:(nullable NSString *)channelId
                                isBlocked:(BOOL)isBlocked
                                  success:(nullable void (^)(RCConversationNotificationStatus nStatus))successBlock
                                    error:(nullable void (^)(RCErrorCode status))errorBlock
    __deprecated_msg("Use [RCChannelClient "
                     "setConversationChannelNotificationLevel:targetId:channelId:level:success:error:] instead");

/// 获取本地消息免打扰会话列表
/// - Parameter conversationTypeList: 会话类型的数组 (需要将 RCConversationType 转为 NSNumber 构建 NSArray)
/// - Parameter channelId: 所属会话的业务标识
/// - Returns: 消息免打扰会话 RCConversation 的列表
///
/// - Remark: 会话列表
/// - Since: 5.1.1
- (nullable NSArray<RCConversation *> *)getBlockedConversationList:(NSArray<NSNumber *> *)conversationTypeList
                                                         channelId:(nullable NSString *)channelId
    __deprecated_msg("Use [RCChannelClient getBlockedConversationList:channelId:completion:] instead");

#pragma mark - 搜索 -

/// 根据关键字搜索指定会话中的消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter keyword: 关键字
/// - Parameter count: 最大的查询数量
/// - Parameter startTime: 查询 startTime 之前的消息，单位：毫秒（传 0 表示不限时间）
///
/// - Returns: 匹配的消息列表
///
/// 此方法不支持超级群的会话类型。
///
/// - Remark: 消息操作
/// - Since: 5.1.1
- (nullable NSArray<RCMessage *> *)searchMessages:(RCConversationType)conversationType
                                         targetId:(NSString *)targetId
                                        channelId:(nullable NSString *)channelId
                                          keyword:(NSString *)keyword
                                            count:(int)count
                                        startTime:(long long)startTime
    __deprecated_msg(
        "Use [RCChannelClient searchMessages:targetId:channelId:keyword:count:startTime:completion:] instead");

/// 根据时间，偏移量和个数搜索指定会话中的消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter keyword: 关键字，传空默认为是查全部符合条件的消息
/// - Parameter startTime: 查询 startTime 之后的消息，startTime >= 0，单位：毫秒
/// - Parameter endTime: 查询 endTime 之前的消息，endTime > startTime，单位：毫秒
/// - Parameter offset: 查询的消息的偏移量，offset >= 0
/// - Parameter limit: 最大的查询数量，limit 需大于 0，最大值为 100，如果大于 100，会默认成 100。
///
/// - Returns: 匹配的消息列表
///
/// 只支持搜索已存储到本地的消息。
///
/// - Remark: 消息操作
/// - Since: 5.1.2
- (nullable NSArray<RCMessage *> *)searchMessages:(RCConversationType)conversationType
                                         targetId:(NSString *)targetId
                                        channelId:(nullable NSString *)channelId
                                          keyword:(nullable NSString *)keyword
                                        startTime:(long long)startTime
                                          endTime:(long long)endTime
                                           offset:(int)offset
                                            limit:(int)limit
    __deprecated_msg("Use [RCChannelClient "
                     "searchMessages:targetId:channelId:keyword:startTime:endTime:offset:limit:completion:] instead");

/// 按用户 ID 搜索指定会话中的消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter userId: 搜索用户 ID
/// - Parameter count: 最大的查询数量
/// - Parameter startTime: 查询 startTime 之前的消息，单位：毫秒（传 0 表示不限时间）
///
/// - Returns: 匹配的消息列表
///
/// 只支持搜索已存储到本地的消息。
///
/// - Remark: 消息操作
/// - Since: 5.1.1
- (nullable NSArray<RCMessage *> *)searchMessages:(RCConversationType)conversationType
                                         targetId:(NSString *)targetId
                                        channelId:(nullable NSString *)channelId
                                           userId:(NSString *)userId
                                            count:(int)count
                                        startTime:(long long)startTime
    __deprecated_msg(
        "Use [RCChannelClient searchMessages:targetId:channelId:userId:count:startTime:completion:] instead");

/// 搜索指定会话中所有 channelId 的消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter keyword: 关键字，非空
/// - Parameter count: 最大的查询数量
/// - Parameter startTime: 查询 startTime 之前的消息，单位：毫秒（传 0 表示不限时间）
///
/// - Returns: 匹配的消息列表
///
/// 只支持搜索已存储到本地的消息。
///
/// - Remark: 消息操作
/// - Since: 5.2.3
- (nullable NSArray<RCMessage *> *)searchMessagesForAllChannel:(RCConversationType)conversationType
                                                      targetId:(NSString *)targetId
                                                       keyword:(NSString *)keyword
                                                         count:(int)count
                                                     startTime:(long long)startTime
    __deprecated_msg(
        "Use [RCChannelClient searchMessagesForAllChannel:targetId:keyword:count:startTime:completion:] instead");

/// 分页搜索指定会话中所有 channelId 在指定时间范围内的消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter keyword: 关键字，非空
/// - Parameter startTime: 开始时间，单位：毫秒（传 0 表示不限时间）
/// - Parameter endTime: 结束时间，可传入当前 unix 时间，单位：毫秒
/// - Parameter offset: 偏移量，默认填 0
/// - Parameter limit: 最大的查询数量
///
/// - Returns: 匹配的消息列表
///
/// 只支持搜索已存储到本地的消息。
///
/// - Remark: 消息操作
/// - Since: 5.2.3
- (nullable NSArray<RCMessage *> *)searchMessagesForAllChannel:(RCConversationType)conversationType
                                                      targetId:(NSString *)targetId
                                                       keyword:(NSString *)keyword
                                                     startTime:(long long)startTime
                                                       endTime:(long long)endTime
                                                        offset:(int)offset
                                                         limit:(int)limit
    __deprecated_msg(
        "Use [RCChannelClient searchMessagesForAllChannel:targetId:keyword:startTime:endTime:offset:limit:completion:] "
        "instead");

/// 根据关键字搜索会话
///
/// - Parameter conversationTypeList: 需要搜索的会话类型列表
/// - Parameter channelId: 所属会话的业务标识
/// - Parameter objectNameList: 需要搜索的消息类型名列表 (即每个消息类方法 getObjectName 的返回值)
/// - Parameter keyword: 关键字
///
/// - Returns: 匹配的会话搜索结果列表
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
/// - Since: 5.2.3
- (nullable NSArray<RCSearchConversationResult *> *)searchConversations:(NSArray<NSNumber *> *)conversationTypeList
                                                              channelId:(nullable NSString *)channelId
                                                            messageType:(NSArray<NSString *> *)objectNameList
                                                                keyword:(NSString *)keyword
    __deprecated_msg("Use [RCChannelClient searchConversations:targetId:messageType:keyword:completion:] instead");

/// 根据关键字搜索特定会话类型下所有 channelId 的会话
///
/// - Parameter conversationTypeList: 需要搜索的会话类型列表
/// - Parameter objectNameList: 需要搜索的消息类型名列表 (即每个消息类方法 getObjectName 的返回值)，不能为 nil
/// - Parameter keyword: 关键字，非空
///
/// - Returns: 匹配的会话搜索结果列表
///
/// 目前，SDK 内置的文本消息、文件消息、图文消息支持搜索。
/// 自定义的消息必须要实现 RCMessageContent 的 getSearchableWords 接口才能进行搜索。
///
/// conversationTypeList 包含超级群会话类型时，超级群会话只搜索已存储到本地的消息记录。
/// conversationTypeList 中类型个数不能超过 300，超过会被截断。
/// objectNameList 中类型名个数不能超过 300，超过会被截断。
///
/// conversationTypeList 传值时：
/// OC 需转成 NSNumber 传入（例如 @[ @(ConversationType_PRIVATE) ]），
/// Swift 需获取到 rawValue 强转成 NSNumber 传入
/// （例如 let privateType = NSNumber(value: RCConversationType.ConversationType_PRIVATE.rawValue)
/// [privateType]  ）
///
/// - Remark: 消息操作
/// - Since: 5.2.3
- (nullable NSArray<RCSearchConversationResult *> *)
    searchConversationsForAllChannel:(NSArray<NSNumber *> *)conversationTypeList
                         messageType:(NSArray<NSString *> *)objectNameList
                             keyword:(NSString *)keyword
    __deprecated_msg("Use [RCChannelClient searchConversationsForAllChannel:messageType:keyword:completion:] instead");

@end

NS_ASSUME_NONNULL_END
