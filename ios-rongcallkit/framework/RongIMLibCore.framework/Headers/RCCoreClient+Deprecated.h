//
//  RCCoreClient+Deprecated.h
//  RongIMLibCore
//
//  Created by shuai shao on 2023/1/29.
//  Copyright © 2023 RongCloud. All rights reserved.
//

#import <RongIMLibCore/RongIMLibCore.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @since 5.4.1
 @warning 本文件的方法已经过期，请您替换 RCCoreClient 中的方法。
 */
@interface RCCoreClient (Deprecated)

/**
 语音消息采样率，默认 8KHz

 @discussion
 2.9.12 之前的版本只支持 8KHz。如果设置为 16KHz，老版本将无法播放 16KHz 的语音消息。
 客服会话只支持 8KHz。

 @remarks 功能设置
 @since 5.0.0
 */
@property (nonatomic, assign) RCSampleRate sampleRate __attribute__((deprecated));

#pragma mark - Apple Watch 状态监听

/*!
 用于 Apple Watch 的 IMLibCore 事务监听器

 @remarks 功能设置
 */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
@property (nonatomic, weak, nullable) id<RCWatchKitStatusDelegate> watchKitStatusDelegate __attribute__((deprecated));
#pragma clang diagnostic pop

#pragma mark - 消息发送 -

/*!
 发送消息
 
 @param conversationType    发送消息的会话类型
 @param targetId            发送消息的会话 ID
 @param content             消息的内容
 @param pushContent         接收方离线时需要显示的远程推送内容
 @param pushData            接收方离线时需要在远程推送中携带的非显示数据
 @param successBlock        消息发送成功的回调 [messageId: 消息的 ID]
 @param errorBlock          消息发送失败的回调 [nErrorCode: 发送失败的错误码,
 messageId:消息的ID]
 @return                    发送的消息实体
 
 @discussion 当接收方离线并允许远程推送时，会收到远程推送。
 远程推送中包含两部分内容，一是 pushContent ，用于显示；二是 pushData ，用于携带不显示的数据。
 
 SDK 内置的消息类型，如果您将 pushContent 和 pushData 置为 nil ，会使用默认的推送格式进行远程推送。
 自定义类型的消息，需要您自己设置 pushContent 和 pushData 来定义推送内容，否则将不会进行远程推送。
 
 如果您使用此方法发送图片消息，需要您自己实现图片的上传，构建一个 RCImageMessage 对象，
 并将 RCImageMessage 中的 imageUrl 字段设置为上传成功的 URL 地址，然后使用此方法发送。
 
 如果您使用此方法发送文件消息，需要您自己实现文件的上传，构建一个 RCFileMessage 对象，
 并将 RCFileMessage 中的 fileUrl 字段设置为上传成功的 URL 地址，然后使用此方法发送。
 
 @warning 如果您使用 IMLibCore，可以使用此方法发送消息；
 如果您使用 IMKit，请使用 RCIM 中的同名方法发送消息，否则不会自动更新 UI。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (nullable RCMessage *)sendMessage:(RCConversationType)conversationType
                           targetId:(NSString *)targetId
                            content:(RCMessageContent *)content
                        pushContent:(nullable NSString *)pushContent
                           pushData:(nullable NSString *)pushData
                            success:(nullable void (^)(long messageId))successBlock
                              error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock __deprecated_msg("Use [RCCoreClient sendMessage:targetId:content:pushContent:pushData:attached:success:error:] instead");

/*!
 发送消息
 
 @param conversationType    发送消息的会话类型
 @param targetId            发送消息的会话 ID
 @param content             消息的内容
 @param pushContent         接收方离线时需要显示的远程推送内容
 @param pushData            接收方离线时需要在远程推送中携带的非显示数据
 @param option              消息的相关配置
 @param successBlock        消息发送成功的回调 [messageId: 消息的 ID]
 @param errorBlock          消息发送失败的回调 [nErrorCode: 发送失败的错误码,
 messageId: 消息的 ID]
 @return                    发送的消息实体
 
 @discussion 当接收方离线并允许远程推送时，会收到远程推送。
 远程推送中包含两部分内容，一是 pushContent，用于显示；二是 pushData，用于携带不显示的数据。
 
 SDK 内置的消息类型，如果您将 pushContent 和 pushData 置为 nil，会使用默认的推送格式进行远程推送。
 自定义类型的消息，需要您自己设置 pushContent 和 pushData 来定义推送内容，否则将不会进行远程推送。
 
 如果您使用此方法发送图片消息，需要您自己实现图片的上传，构建一个 RCImageMessage 对象，
 并将 RCImageMessage 中的 imageUrl 字段设置为上传成功的 URL 地址，然后使用此方法发送。
 
 如果您使用此方法发送文件消息，需要您自己实现文件的上传，构建一个 RCFileMessage 对象，
 并将 RCFileMessage 中的 fileUrl 字段设置为上传成功的 URL 地址，然后使用此方法发送。
 
 @warning 如果您使用 IMLibCore，可以使用此方法发送消息；
 如果您使用 IMKit，请使用 RCIM 中的同名方法发送消息，否则不会自动更新 UI。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (nullable RCMessage *)sendMessage:(RCConversationType)conversationType
                           targetId:(NSString *)targetId
                            content:(RCMessageContent *)content
                        pushContent:(nullable NSString *)pushContent
                           pushData:(nullable NSString *)pushData
                             option:(RCSendMessageOption *)option
                            success:(nullable void (^)(long messageId))successBlock
                              error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock  __deprecated_msg("Use [RCCoreClient sendMessage:targetId:content:pushContent:pushData:option:attached:success:error:] instead");

/*!
 发送媒体消息（图片消息或文件消息）
 
 @param conversationType    发送消息的会话类型
 @param targetId            发送消息的会话 ID
 @param content             消息的内容
 @param pushContent         接收方离线时需要显示的远程推送内容
 @param pushData            接收方离线时需要在远程推送中携带的非显示数据
 @param progressBlock       消息发送进度更新的回调 [progress:当前的发送进度, 0
 <= progress <= 100, messageId:消息的 ID]
 @param successBlock        消息发送成功的回调 [messageId:消息的 ID]
 @param errorBlock          消息发送失败的回调 [errorCode:发送失败的错误码,
 messageId:消息的 ID]
 @param cancelBlock         用户取消了消息发送的回调 [messageId:消息的 ID]
 @return                    发送的消息实体
 
 @discussion 当接收方离线并允许远程推送时，会收到远程推送。
 远程推送中包含两部分内容，一是 pushContent，用于显示；二是 pushData，用于携带不显示的数据。
 
 SDK 内置的消息类型，如果您将 pushContent 和 pushData 置为 nil，会使用默认的推送格式进行远程推送。
 自定义类型的消息，需要您自己设置 pushContent 和 pushData 来定义推送内容，否则将不会进行远程推送。
 
 如果您需要上传图片到自己的服务器，需要构建一个 RCImageMessage 对象，
 并将 RCImageMessage 中的 imageUrl 字段设置为上传成功的 URL 地址，然后使用 RCCoreClient 的
 sendMessage:targetId:content:pushContent:pushData:success:error:方法
 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。
 
 如果您需要上传文件到自己的服务器，构建一个 RCFileMessage 对象，
 并将 RCFileMessage 中的 fileUrl 字段设置为上传成功的 URL 地址，然后使用 RCCoreClient 的
 sendMessage:targetId:content:pushContent:pushData:success:error:方法
 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。
 
 @warning 如果您使用 IMLibCore，可以使用此方法发送媒体消息；
 如果您使用 IMKit，请使用 RCIM 中的同名方法发送媒体消息，否则不会自动更新 UI。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (nullable RCMessage *)sendMediaMessage:(RCConversationType)conversationType
                                targetId:(NSString *)targetId
                                 content:(RCMessageContent *)content
                             pushContent:(nullable NSString *)pushContent
                                pushData:(nullable NSString *)pushData
                                progress:(nullable void (^)(int progress, long messageId))progressBlock
                                 success:(nullable void (^)(long messageId))successBlock
                                   error:(nullable void (^)(RCErrorCode errorCode, long messageId))errorBlock
                                  cancel:(nullable void (^)(long messageId))cancelBlock __deprecated_msg("Use [RCCoreClient sendMediaMessage:targetId:content:pushContent:pushData:attached:progress:success:error:cancel:] instead");

/*!
 发送媒体消息(上传图片或文件等媒体信息到指定的服务器)
 
 @param conversationType    发送消息的会话类型
 @param targetId            发送消息的会话 ID
 @param content             消息的内容
 @param pushContent         接收方离线时需要显示的远程推送内容
 @param pushData            接收方离线时需要在远程推送中携带的非显示数据
 @param uploadPrepareBlock  媒体文件上传进度更新的监听
 [uploadListener:当前的发送进度监听]
 @param progressBlock       消息发送进度更新的回调 [progress:当前的发送进度, 0
 <= progress <= 100, messageId:消息的ID]
 @param successBlock        消息发送成功的回调 [messageId:消息的 ID]
 @param errorBlock          消息发送失败的回调 [errorCode:发送失败的错误码,
 messageId:消息的 ID]
 @param cancelBlock         用户取消了消息发送的回调 [messageId:消息的 ID]
 @return                    发送的消息实体
 
 @discussion
 如果您需要上传图片到自己的服务器并使用 IMLibCore，构建一个 RCImageMessage 对象，
 并将 RCImageMessage 中的 imageUrl 字段设置为上传成功的 URL 地址，然后使用 RCCoreClient 的
 sendMessage:targetId:content:pushContent:pushData:success:error:方法
 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。
 
 如果您需要上传文件到自己的服务器并使用 IMLibCore，构建一个 RCFileMessage 对象，
 并将 RCFileMessage 中的 fileUrl 字段设置为上传成功的 URL 地址，然后使用 RCCoreClient 的
 sendMessage:targetId:content:pushContent:pushData:success:error:方法
 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (nullable RCMessage *)sendMediaMessage:(RCConversationType)conversationType
                                targetId:(NSString *)targetId
                                 content:(RCMessageContent *)content
                             pushContent:(nullable NSString *)pushContent
                                pushData:(nullable NSString *)pushData
                           uploadPrepare:(nullable void (^)(RCUploadMediaStatusListener *uploadListener))uploadPrepareBlock
                                progress:(nullable void (^)(int progress, long messageId))progressBlock
                                 success:(nullable void (^)(long messageId))successBlock
                                   error:(nullable void (^)(RCErrorCode errorCode, long messageId))errorBlock
                                  cancel:(nullable void (^)(long messageId))cancelBlock __deprecated_msg("Use [RCCoreClient sendMediaMessage:targetId:content:pushContent:pushData:attached:uploadPrepare:progress:success:error:cancel:] instead");

/*!
 发送消息
 
 @param message             将要发送的消息实体（需要保证 message 中的 conversationType，targetId，messageContent 是有效值)
 @param pushContent         接收方离线时需要显示的远程推送内容
 @param pushData            接收方离线时需要在远程推送中携带的非显示数据
 @param successBlock        消息发送成功的回调 [successMessage: 消息实体]
 @param errorBlock          消息发送失败的回调 [nErrorCode: 发送失败的错误码, errorMessage:消息实体]
 @return                    发送的消息实体
 
 @discussion 当接收方离线并允许远程推送时，会收到远程推送。
 远程推送中包含两部分内容，一是 pushContent ，用于显示；二是 pushData ，用于携带不显示的数据。
 
 SDK 内置的消息类型，如果您将 pushContent 和 pushData 置为 nil ，会使用默认的推送格式进行远程推送。
 自定义类型的消息，需要您自己设置 pushContent 和 pushData 来定义推送内容，否则将不会进行远程推送。
 
 如果您使用此方法发送图片消息，需要您自己实现图片的上传，构建一个 RCImageMessage 对象，
 并将 RCImageMessage 中的 imageUrl 字段设置为上传成功的 URL 地址，然后使用此方法发送。
 
 如果您使用此方法发送文件消息，需要您自己实现文件的上传，构建一个 RCFileMessage 对象，
 并将 RCFileMessage 中的 fileUrl 字段设置为上传成功的 URL 地址，然后使用此方法发送。
 
 @warning 如果您使用 IMLibCore，可以使用此方法发送消息；
 如果您使用 IMKit，请使用 RCIM 中的同名方法发送消息，否则不会自动更新 UI。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (nullable RCMessage *)sendMessage:(RCMessage *)message
                        pushContent:(nullable NSString *)pushContent
                           pushData:(nullable NSString *)pushData
                       successBlock:(nullable void (^)(RCMessage *successMessage))successBlock
                         errorBlock:(nullable void (^)(RCErrorCode nErrorCode, RCMessage *errorMessage))errorBlock __deprecated_msg("Use [RCCoreClient sendMessage: pushContent:pushData:attached:successBlock:errorBlock:] instead");

/*!
 发送媒体消息(上传图片或文件等媒体信息到指定的服务器)
 
 @param message             将要发送的消息实体（需要保证 message 中的 conversationType，targetId，messageContent 是有效值)
 @param pushContent         接收方离线时需要显示的远程推送内容
 @param pushData            接收方离线时需要在远程推送中携带的非显示数据
 @param uploadPrepareBlock  媒体文件上传进度更新的监听
 [uploadListener:当前的发送进度监听]
 @param progressBlock       消息发送进度更新的回调 [progress:当前的发送进度, 0
 <= progress <= 100, messageId:消息的ID]
 @param successBlock        消息发送成功的回调 [messageId:消息的 ID]
 @param errorBlock          消息发送失败的回调 [errorCode:发送失败的错误码,
 messageId:消息的 ID]
 @param cancelBlock         用户取消了消息发送的回调 [messageId:消息的 ID]
 @return                    发送的消息实体
 
 @discussion
 如果您需要上传图片到自己的服务器并使用 IMLibCore，构建一个 RCImageMessage 对象，
 并将 RCImageMessage 中的 imageUrl 字段设置为上传成功的 URL 地址，然后使用 RCCoreClient 的
 sendMessage:targetId:content:pushContent:pushData:success:error:方法
 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。
 
 如果您需要上传文件到自己的服务器并使用 IMLibCore，构建一个 RCFileMessage 对象，
 并将 RCFileMessage 中的 fileUrl 字段设置为上传成功的 URL 地址，然后使用 RCCoreClient 的
 sendMessage:targetId:content:pushContent:pushData:success:error:方法
 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。
 
 @remarks 消息操作
 @since 5.2.1
 */
- (nullable RCMessage *)sendMediaMessage:(RCMessage *)message
                             pushContent:(nullable NSString *)pushContent
                                pushData:(nullable NSString *)pushData
                           uploadPrepare:(nullable void (^)(RCUploadMediaStatusListener *uploadListener))uploadPrepareBlock
                                progress:(nullable void (^)(int progress, long messageId))progressBlock
                                 success:(nullable void (^)(long messageId))successBlock
                                   error:(nullable void (^)(RCErrorCode errorCode, long messageId))errorBlock
                                  cancel:(nullable void (^)(long messageId))cancelBlock __deprecated_msg("Use [RCCoreClient sendMediaMessage:pushContent:pushData:attached:uploadPrepare:progress:success:error:cancel:] instead");

/*!
 发送媒体消息（图片消息或文件消息）
 
 @param message             将要发送的消息实体（需要保证 message 中的 conversationType，targetId，messageContent 是有效值)
 @param pushContent         接收方离线时需要显示的远程推送内容
 @param pushData            接收方离线时需要在远程推送中携带的非显示数据
 @param progressBlock       消息发送进度更新的回调 [progress:当前的发送进度, 0 <= progress <= 100, progressMessage:消息实体]
 @param successBlock        消息发送成功的回调 [successMessage:消息实体]
 @param errorBlock          消息发送失败的回调 [nErrorCode:发送失败的错误码, errorMessage:消息实体]
 @param cancelBlock         用户取消了消息发送的回调 [cancelMessage:消息实体]
 @return                    发送的消息实体
 
 @discussion 当接收方离线并允许远程推送时，会收到远程推送。
 远程推送中包含两部分内容，一是 pushContent，用于显示；二是 pushData，用于携带不显示的数据。
 
 SDK 内置的消息类型，如果您将 pushContent 和 pushData 置为 nil，会使用默认的推送格式进行远程推送。
 自定义类型的消息，需要您自己设置 pushContent 和 pushData 来定义推送内容，否则将不会进行远程推送。
 
 如果您需要上传图片到自己的服务器，需要构建一个 RCImageMessage 对象，
 并将 RCImageMessage 中的 imageUrl 字段设置为上传成功的 URL 地址，然后使用 RCCoreClient 的
 sendMessage:targetId:content:pushContent:pushData:success:error:方法
 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。
 
 如果您需要上传文件到自己的服务器，构建一个 RCFileMessage 对象，
 并将 RCFileMessage 中的 fileUrl 字段设置为上传成功的 URL 地址，然后使用 RCCoreClient 的
 sendMessage:targetId:content:pushContent:pushData:success:error:方法
 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。
 
 @warning 如果您使用 IMLibCore，可以使用此方法发送媒体消息；
 如果您使用 IMKit，请使用 RCIM 中的同名方法发送媒体消息，否则不会自动更新 UI。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (nullable RCMessage *)sendMediaMessage:(RCMessage *)message
                             pushContent:(nullable NSString *)pushContent
                                pushData:(nullable NSString *)pushData
                                progress:(nullable void (^)(int progress, RCMessage *progressMessage))progressBlock
                            successBlock:(nullable void (^)(RCMessage *successMessage))successBlock
                              errorBlock:(nullable void (^)(RCErrorCode nErrorCode, RCMessage *errorMessage))errorBlock
                                  cancel:(nullable void (^)(RCMessage *cancelMessage))cancelBlock __deprecated_msg("Use [RCCoreClient sendMediaMessage:pushContent:pushData:attached:progress:successBlock:errorBlock:cancel:] instead");

#pragma mark - 插入消息 -

/*!
 插入向外发送的消息（该消息只插入本地数据库，实际不会发送给服务器和对方）
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param sentStatus          发送状态
 @param content             消息的内容
 @return             插入的消息实体
 
 @discussion 此方法不支持聊天室的会话类型。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (nullable RCMessage *)insertOutgoingMessage:(RCConversationType)conversationType
                                     targetId:(NSString *)targetId
                                   sentStatus:(RCSentStatus)sentStatus
                                      content:(RCMessageContent *)content __deprecated_msg("Use [RCCoreClient insertOutgoingMessage:targetId:sentStatus:content:completion:] instead");

/*!
 插入向外发送的、指定时间的消息（此方法如果 sentTime 有问题会影响消息排序，慎用！！）
 （该消息只插入本地数据库，实际不会发送给服务器和对方）
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param sentStatus          发送状态
 @param content             消息的内容
 @param sentTime            消息发送的 Unix 时间戳，单位为毫秒（传 0 会按照本地时间插入）
 @return                    插入的消息实体
 
 @discussion 此方法不支持聊天室的会话类型。如果 sentTime<=0，则被忽略，会以插入时的时间为准。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (nullable RCMessage *)insertOutgoingMessage:(RCConversationType)conversationType
                                     targetId:(NSString *)targetId
                                   sentStatus:(RCSentStatus)sentStatus
                                      content:(RCMessageContent *)content
                                     sentTime:(long long)sentTime __deprecated_msg("Use [RCCoreClient insertOutgoingMessage:targetId:sentStatus:content:sentTime:completion:] instead");

/*!
 插入接收的消息（该消息只插入本地数据库，实际不会发送给服务器和对方）
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param senderUserId        发送者 ID
 @param receivedStatus      接收状态
 @param content             消息的内容
 @return                    插入的消息实体
 
 @discussion 此方法不支持聊天室的会话类型。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (nullable RCMessage *)insertIncomingMessage:(RCConversationType)conversationType
                                     targetId:(NSString *)targetId
                                 senderUserId:(NSString *)senderUserId
                               receivedStatus:(RCReceivedStatus)receivedStatus
                                      content:(RCMessageContent *)content __deprecated_msg("Use [RCCoreClient insertIncomingMessage:targetId:senderUserId:receivedStatus:content:completion:] instead");

/*!
 插入接收的消息（此方法如果 sentTime
 有问题会影响消息排序，慎用！！）（该消息只插入本地数据库，实际不会发送给服务器和对方）
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param senderUserId        发送者 ID
 @param receivedStatus      接收状态
 @param content             消息的内容
 @param sentTime            消息发送的 Unix 时间戳，单位为毫秒 （传 0 会按照本地时间插入）
 @return                    插入的消息实体
 
 @discussion 此方法不支持聊天室的会话类型。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (nullable RCMessage *)insertIncomingMessage:(RCConversationType)conversationType
                                     targetId:(NSString *)targetId
                                 senderUserId:(NSString *)senderUserId
                               receivedStatus:(RCReceivedStatus)receivedStatus
                                      content:(RCMessageContent *)content
                                     sentTime:(long long)sentTime __deprecated_msg("Use [RCCoreClient insertIncomingMessage:targetId:senderUserId:receivedStatus:content:sentTime:completion:] instead");

/*!
 批量插入接收的消息（该消息只插入本地数据库，实际不会发送给服务器和对方）
 RCMessage 下列属性会被入库，其余属性会被抛弃
 conversationType    会话类型
 targetId            会话 ID
 messageUId          消息唯一 ID,  此属性入库 5.3.5 开始支持
 messageDirection    消息方向
 senderUserId        发送者 ID
 receivedStatus      接收状态；消息方向为接收方，并且 receivedStatus 为 ReceivedStatus_UNREAD 时，该条消息未读
 sentStatus          发送状态
 content             消息的内容
 sentTime            消息发送的 Unix 时间戳，单位为毫秒 ，会影响消息排序
 extra            RCMessage 的额外字段
 
 @discussion 此方法不支持聊天室的会话类型。每批最多处理  500 条消息，超过 500 条返回 NO
 @discussion 消息的未读会累加到会话的未读数上

 @remarks 消息操作
 @since 5.1.1
 */
- (BOOL)batchInsertMessage:(NSArray<RCMessage *> *)msgs __deprecated_msg("Use [RCCoreClient batchInsertMessage:completion:] instead");

#pragma mark - 定向消息 -

/*!
 发送定向消息
 
 @param conversationType 发送消息的会话类型
 @param targetId         发送消息的会话 ID
 @param userIdList       接收消息的用户 ID 列表
 @param content          消息的内容
 @param pushContent      接收方离线时需要显示的远程推送内容
 @param pushData         接收方离线时需要在远程推送中携带的非显示数据
 @param successBlock     消息发送成功的回调 [messageId:消息的 ID]
 @param errorBlock       消息发送失败的回调 [errorCode:发送失败的错误码,
 messageId:消息的 ID]
 
 @return 发送的消息实体
 
 @discussion 此方法用于在群组和讨论组中发送消息给其中的部分用户，其它用户不会收到这条消息。
 如果您使用 IMLibCore，可以使用此方法发送定向消息；
 如果您使用 IMKit，请使用 RCIM 中的同名方法发送定向消息，否则不会自动更新 UI。
 @discussion userIdList里ID个数不能超过300，超过会被截断。
 
 @warning 此方法目前仅支持普通群组和讨论组。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (nullable RCMessage *)sendDirectionalMessage:(RCConversationType)conversationType
                                      targetId:(NSString *)targetId
                                  toUserIdList:(NSArray<NSString *> *)userIdList
                                       content:(RCMessageContent *)content
                                   pushContent:(nullable NSString *)pushContent
                                      pushData:(nullable NSString *)pushData
                                       success:(nullable void (^)(long messageId))successBlock
                                         error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock __deprecated_msg("Use [RCCoreClient sendDirectionalMessage:targetId:toUserIdList:content:pushContent:pushData:attached:success:error:] instead");

/*!
 发送定向消息
 
 @param message 消息实体
 @param userIdList       接收消息的用户 ID 列表
 @param pushContent      接收方离线时需要显示的远程推送内容
 @param pushData         接收方离线时需要在远程推送中携带的非显示数据
 @param successBlock     消息发送成功的回调 [successMessage:发送成功的消息]
 @param errorBlock       消息发送失败的回调 [nErrorCode:发送失败的错误码,errorMessage:发送失败的消息]
 
 @return 发送的消息实体
 
 @discussion 此方法用于在群组和讨论组中发送消息给其中的部分用户，其它用户不会收到这条消息。
 @discussion userIdList里ID个数不能超过300，超过会被截断。
 
 @warning 此方法目前仅支持普通群组和讨论组。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (nullable RCMessage *)sendDirectionalMessage:(RCMessage *)message
                                  toUserIdList:(NSArray<NSString *> *)userIdList
                                   pushContent:(nullable NSString *)pushContent
                                      pushData:(nullable NSString *)pushData
                                  successBlock:(nullable void (^)(RCMessage *successMessage))successBlock
                                    errorBlock:(nullable void (^)(RCErrorCode nErrorCode, RCMessage *errorMessage))errorBlock __deprecated_msg("Use [RCCoreClient sendDirectionalMessage:toUserIdList:pushContent:pushData:attached:successBlock:errorBlock:] instead");

/*!
 发送定向消息
 
 @param message 消息实体
 @param userIdList       接收消息的用户 ID 列表
 @param pushContent      接收方离线时需要显示的远程推送内容
 @param pushData         接收方离线时需要在远程推送中携带的非显示数据
 @param option              消息的相关配置
 @param successBlock     消息发送成功的回调 [successMessage:发送成功的消息]
 @param errorBlock       消息发送失败的回调 [nErrorCode:发送失败的错误码,errorMessage:发送失败的消息]
 
 @return 发送的消息实体
 
 @discussion 此方法用于在群组和讨论组中发送消息给其中的部分用户，其它用户不会收到这条消息。
 @discussion userIdList里ID个数不能超过300，超过会被截断。
 
 @warning 此方法目前仅支持普通群组和讨论组。
 
 @remarks 消息操作
 @since 5.1.2
 */
- (nullable RCMessage *)sendDirectionalMessage:(RCMessage *)message
                                  toUserIdList:(NSArray<NSString *> *)userIdList
                                   pushContent:(nullable NSString *)pushContent
                                      pushData:(nullable NSString *)pushData
                                        option:(RCSendMessageOption *)option
                                  successBlock:(nullable void (^)(RCMessage *successMessage))successBlock
                                    errorBlock:(nullable void (^)(RCErrorCode nErrorCode, RCMessage *errorMessage))errorBlock __deprecated_msg("Use [RCCoreClient sendDirectionalMessage:toUserIdList:pushContent:pushData:option:attached:successBlock:errorBlock:] instead");

/*!
 发送定向媒体消息（图片消息或文件消息）
 
 @param message             将要发送的消息实体（需要保证 message 中的 conversationType，targetId，messageContent 是有效值)
 @param userIdList       接收消息的用户 ID 列表
 @param pushContent         接收方离线时需要显示的远程推送内容
 @param pushData            接收方离线时需要在远程推送中携带的非显示数据
 @param progressBlock       消息发送进度更新的回调 [progress:当前的发送进度, 0 <= progress <= 100, progressMessage:消息实体]
 @param successBlock        消息发送成功的回调 [successMessage:消息实体]
 @param errorBlock          消息发送失败的回调 [nErrorCode:发送失败的错误码, errorMessage:消息实体]
 @param cancelBlock         用户取消了消息发送的回调 [cancelMessage:消息实体]
 @return                    发送的消息实体
 
 @discussion 当接收方离线并允许远程推送时，会收到远程推送。
 远程推送中包含两部分内容，一是 pushContent，用于显示；二是 pushData，用于携带不显示的数据。
 
 SDK 内置的消息类型，如果您将 pushContent 和 pushData 置为 nil，会使用默认的推送格式进行远程推送。
 自定义类型的消息，需要您自己设置 pushContent 和 pushData 来定义推送内容，否则将不会进行远程推送。
 
 如果您需要上传图片到自己的服务器，需要构建一个 RCImageMessage 对象，
 并将 RCImageMessage 中的 imageUrl 字段设置为上传成功的 URL 地址，然后使用 RCIMClient 的
 sendMessage:targetId:content:pushContent:pushData:success:error:方法
 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。
 
 如果您需要上传文件到自己的服务器，构建一个 RCFileMessage 对象，
 并将 RCFileMessage 中的 fileUrl 字段设置为上传成功的 URL 地址，然后使用 RCIMClient 的
 sendMessage:targetId:content:pushContent:pushData:success:error:方法
 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。
 
 @warning 如果您使用 IMLib，可以使用此方法发送媒体消息；
 如果您使用 IMKit，请使用 RCIM 中的同名方法发送媒体消息，否则不会自动更新 UI。
 
 @remarks 消息操作
 @since 5.2.5
 */
- (nullable RCMessage *)sendDirectionalMediaMessage:(RCMessage *)message
                                       toUserIdList:(NSArray<NSString *> *)userIdList
                                        pushContent:(nullable NSString *)pushContent
                                           pushData:(nullable NSString *)pushData
                                           progress:(nullable void (^)(int progress, RCMessage *progressMessage))progressBlock
                                       successBlock:(nullable void (^)(RCMessage *successMessage))successBlock
                                         errorBlock:(nullable void (^)(RCErrorCode nErrorCode, RCMessage *errorMessage))errorBlock
                                             cancel:(nullable void (^)(RCMessage *cancelMessage))cancelBlock __deprecated_msg("Use [RCCoreClient sendDirectionalMediaMessage:toUserIdList:pushContent:pushData:attached:progress:successBlock:errorBlock:cancel:] instead");

#pragma mark - 消息操作 -

/*!
 获取某个会话中指定数量的最新消息实体
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param count               需要获取的消息数量
 @return                    消息实体 RCMessage 对象列表
 
 @discussion
 此方法会获取该会话中指定数量的最新消息实体，返回的消息实体按照时间从新到旧排列。
 如果会话中的消息数量小于参数 count 的值，会将该会话中的所有消息返回。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (nullable NSArray<RCMessage *> *)getLatestMessages:(RCConversationType)conversationType targetId:(NSString *)targetId count:(int)count __deprecated_msg("Use [RCCoreClient getLatestMessages:targetId:count:completion:] instead");

/*!
 获取会话中，从指定消息之前、指定数量的最新消息实体
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param oldestMessageId     截止的消息 ID [0或-1 代表从最近的发送时间查起]
 @param count               需要获取的消息数量
 @return                    消息实体 RCMessage 对象列表
 
 @discussion
 此方法会获取该会话中，oldestMessageId 之前的、指定数量的最新消息实体，返回的消息实体按照时间从新到旧排列。
 返回的消息中不包含 oldestMessageId 对应那条消息，如果会话中的消息数量小于参数 count 的值，会将该会话中的所有消息返回。
 如：
 oldestMessageId 为 10，count 为 2，会返回 messageId 为 9 和 8 的 RCMessage 对象列表。
 
 @discussion 此方法不支持超级群的会话类型。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                             targetId:(NSString *)targetId
                                      oldestMessageId:(long)oldestMessageId
                                                count:(int)count __deprecated_msg("Use [RCCoreClient getHistoryMessages:targetId:oldestMessageId:count:completion:] instead");
/*!
 获取会话中，从指定消息之前、指定数量的、指定消息类型的最新消息实体
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param objectName          消息内容的类型名，如果想取全部类型的消息请传 nil
 @param oldestMessageId     截止的消息 ID [0或-1 代表从最近的发送时间查起]
 @param count               需要获取的消息数量
 @return                    消息实体 RCMessage 对象列表
 
 @discussion
 此方法会获取该会话中，oldestMessageId 之前的、指定数量和消息类型的最新消息实体，返回的消息实体按照时间从新到旧排列。
 返回的消息中不包含 oldestMessageId 对应的那条消息，如果会话中的消息数量小于参数 count
 的值，会将该会话中的所有消息返回。
 如：oldestMessageId 为 10，count 为 2，会返回 messageId 为 9 和 8 的 RCMessage 对象列表。
 
 @discussion 此方法不支持超级群的会话类型。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                             targetId:(NSString *)targetId
                                           objectName:(nullable NSString *)objectName
                                      oldestMessageId:(long)oldestMessageId
                                                count:(int)count __deprecated_msg("Use [RCCoreClient getHistoryMessages:targetId:objectName:oldestMessageId:count:completion:] instead");

/*!
 获取会话中，指定消息、指定数量、指定消息类型、向前或向后查找的消息实体列表
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param objectName          消息内容的类型名，如果想取全部类型的消息请传 nil
 @param baseMessageId       当前的消息 ID [0或-1 代表从最近的发送时间查起]
 @param isForward           查询方向 true 为向前，false 为向后
 @param count               需要获取的消息数量
 @return                    消息实体 RCMessage 对象列表
 
 @discussion
 此方法会获取该会话中，baseMessageId
 之前或之后的、指定数量、消息类型和查询方向的最新消息实体，返回的消息实体按照时间从新到旧排列。
 返回的消息中不包含 baseMessageId 对应的那条消息，如果会话中的消息数量小于参数 count 的值，会将该会话中的所有消息返回。
 
 @discussion 此方法不支持超级群的会话类型。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                             targetId:(NSString *)targetId
                                           objectName:(nullable NSString *)objectName
                                        baseMessageId:(long)baseMessageId
                                            isForward:(BOOL)isForward
                                                count:(int)count __deprecated_msg("Use [RCCoreClient getHistoryMessages:targetId:objectName:baseMessageId:isForward:count:completion:] instead");

/*!
 获取会话中，指定时间、指定数量、指定消息类型（多个）、向前或向后查找的消息实体列表
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param objectNames         消息内容的类型名称列表
 @param sentTime            当前的消息时间戳
 @param isForward           查询方向 true 为向前，false 为向后
 @param count               需要获取的消息数量
 @return                    消息实体 RCMessage 对象列表
 
 @discussion
 此方法会获取该会话中，sentTime
 之前或之后的、指定数量、指定消息类型（多个）的消息实体列表，返回的消息实体按照时间从新到旧排列。
 返回的消息中不包含 sentTime 对应的那条消息，如果会话中的消息数量小于参数 count 的值，会将该会话中的所有消息返回。
 
 @discussion 此方法不支持超级群的会话类型。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                             targetId:(NSString *)targetId
                                          objectNames:(NSArray<NSString *> *)objectNames
                                             sentTime:(long long)sentTime
                                            isForward:(BOOL)isForward
                                                count:(int)count __deprecated_msg("Use [RCCoreClient getHistoryMessages:targetId:objectNames:sentTime:isForward:count:completion:] instead");

/*!
 在会话中搜索指定消息的前 beforeCount 数量和后 afterCount
 数量的消息。返回的消息列表中会包含指定的消息。消息列表时间顺序从新到旧。
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param sentTime            消息的发送时间
 @param beforeCount         指定消息的前部分消息数量
 @param afterCount          指定消息的后部分消息数量
 @return                    消息实体 RCMessage 对象列表
 
 @discussion
 获取该会话的这条消息及这条消息前 beforeCount 条和后 afterCount 条消息,如前后消息不够则返回实际数量的消息。
 
 @discussion 此方法不支持超级群的会话类型。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                             targetId:(NSString *)targetId
                                             sentTime:(long long)sentTime
                                          beforeCount:(int)beforeCount
                                           afterCount:(int)afterCount __deprecated_msg("Use [RCCoreClient getHistoryMessages:targetId:sentTime:beforeCount:afterCount:completion:] instead");

/*!
 获取会话中 @ 提醒自己的消息
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 
 @discussion
 此方法从本地获取被@提醒的消息(最多返回 10 条信息)
 @warning 使用 IMKit 注意在进入会话页面前调用，否则在进入会话清除未读数的接口 clearMessagesUnreadStatus: targetId:
 以及 设置消息接收状态接口 setMessageReceivedStatus:receivedStatus:会同步清除被提示信息状态。
 
 @remarks 高级功能
 @since 5.0.0
 */
- (nullable NSArray<RCMessage *> *)getUnreadMentionedMessages:(RCConversationType)conversationType targetId:(NSString *)targetId __deprecated_msg("Use [RCCoreClient getUnreadMentionedMessages:targetId:completion:] instead");

/*!
 获取本地指定会话的未读条数的 @ 消息列表，仅支持群组
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param count           未读的 @ 消息，取值范围 [1,100]
 @param desc           是否是降序查
 @discussion 假如有 1000 条未读的 @ 消息，取 100 条未读
 desc 为 true 时获取后 100 条消息，messageList 的顺序是 901 到 1000
 desc 为 false 是获取前 100 条消息，messageList 的顺序是 1 到 100
 
 @warning 使用 IMKit 注意在进入会话页面前调用，否则在进入会话清除未读数的接口 clearMessagesUnreadStatus: targetId:
 以及 设置消息接收状态接口 setMessageReceivedStatus:receivedStatus:会同步清除被提示信息状态。
 @since 5.2.5
 */
- (nullable NSArray<RCMessage *> *)getUnreadMentionedMessages:(RCConversationType)conversationType targetId:(NSString *)targetId count:(int)count desc:(BOOL)desc __deprecated_msg("Use [RCCoreClient getUnreadMentionedMessages:targetId:count:desc:completion: instead");

/*!
 获取消息的发送时间（Unix 时间戳、毫秒）
 
 @param messageId   消息 ID
 @return            消息的发送时间（Unix 时间戳、毫秒）
 
 @remarks 消息操作
 @since 5.0.0
 */
- (long long)getMessageSendTime:(long)messageId __deprecated_msg("Use [RCCoreClient getMessageSendTime:completion:] instead");


/*!
 通过 messageId 获取消息实体
 
 @param messageId   消息 ID（数据库索引唯一值）
 @return            通过消息 ID 获取到的消息实体，当获取失败的时候，会返回 nil。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (nullable RCMessage *)getMessage:(long)messageId __deprecated_msg("Use [RCCoreClient getMessage:completion:] instead");

/*!
 通过全局唯一 ID 获取消息实体
 
 @param messageUId   全局唯一 ID（服务器消息唯一 ID）
 @return 通过全局唯一ID获取到的消息实体，当获取失败的时候，会返回 nil。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (nullable RCMessage *)getMessageByUId:(NSString *)messageUId __deprecated_msg("Use [RCCoreClient getMessageByUId:completion:] instead");

/**
 * 获取会话里第一条未读消息。
 *
 * @param conversationType 会话类型
 * @param targetId   会话 ID
 * @return 第一条未读消息的实体。
 * @remarks 消息操作
 * @since 5.0.0
 */
- (nullable RCMessage *)getFirstUnreadMessage:(RCConversationType)conversationType targetId:(NSString *)targetId __deprecated_msg("Use [RCCoreClient getFirstUnreadMessage:targetId:completion:] instead");

/*!
 删除消息
 
 @param messageIds  消息 ID 的列表，元素需要为 NSNumber 类型
 @return            是否删除成功
 
 @remarks 消息操作
 @since 5.0.0
 */
- (BOOL)deleteMessages:(NSArray<NSNumber *> *)messageIds __deprecated_msg("Use [RCCoreClient deleteMessages:completion:] instead");

/*!
 删除某个会话中的所有消息
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @return                    是否删除成功
 
 @remarks 消息操作
 @since 5.0.0
 */
- (BOOL)clearMessages:(RCConversationType)conversationType targetId:(NSString *)targetId __deprecated_msg("Use [RCCoreClient clearMessages:targetId:completion:] instead");

/*!
 设置消息的附加信息
 
 @param messageId   消息 ID
 @param value       附加信息，最大 1024 字节
 @return            是否设置成功
 
 @discussion 用于扩展消息的使用场景。只能用于本地使用，无法同步到远端。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (BOOL)setMessageExtra:(long)messageId value:(NSString *)value __deprecated_msg("Use [RCCoreClient setMessageExtra:value:completion:] instead");

/*!
 设置消息的接收状态
 
 @param messageId       消息 ID
 @param receivedStatus  消息的接收状态
 @return                是否设置成功
 
 @discussion 用于 UI 展示消息为已读，已下载等状态。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (BOOL)setMessageReceivedStatus:(long)messageId receivedStatus:(RCReceivedStatus)receivedStatus __deprecated_msg("Use [RCCoreClient setMessageReceivedStatus:receivedStatus:completion:] instead");

/*!
 设置消息的发送状态
 
 @param messageId       消息 ID
 @param sentStatus      消息的发送状态
 @return                是否设置成功
 
 @discussion 用于 UI 展示消息为正在发送，对方已接收等状态。
 @discussion 为了保证 UI 正常显示，5.1.8 版本起不再支持 app 将消息状态设置为 SentStatus_SENDING
 
 @discussion 此方法不支持超级群的会话类型。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (BOOL)setMessageSentStatus:(long)messageId sentStatus:(RCSentStatus)sentStatus __deprecated_msg("Use [RCCoreClient setMessageSentStatus:sentStatus:completion:] instead");;

#pragma mark - 会话列表操作 -
/*!
 获取会话列表
 
 @param conversationTypeList   会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 @return                        会话 RCConversation 的列表
 
 @discussion 此方法会从本地数据库中，读取会话列表。
 返回的会话列表按照时间从前往后排列，如果有置顶的会话，则置顶的会话会排列在前面。
 @discussion 当您的会话较多且没有清理机制的时候，强烈建议您使用 getConversationList: count: startTime:
 分页拉取会话列表,否则有可能造成内存过大。
 
 @remarks 会话列表
 @since 5.0.0
 */
- (nullable NSArray<RCConversation *> *)getConversationList:(NSArray<NSNumber *> *)conversationTypeList __deprecated_msg("Use [RCCoreClient getConversationList:completion:] instead");

/*!
 分页获取会话列表
 
 @param conversationTypeList 会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 @param count                获取的数量（当实际取回的会话数量小于 count 值时，表明已取完数据）
 @param startTime            会话的时间戳（获取这个时间戳之前的会话列表，0表示从最新开始获取）
 @return                     会话 RCConversation 的列表
 
 @discussion 此方法会从本地数据库中，读取会话列表。
 返回的会话列表按照时间从前往后排列，如果有置顶的会话，则置顶的会话会排列在前面。
 
 @remarks 会话列表
 @since 5.0.0
 */
- (nullable NSArray<RCConversation *> *)getConversationList:(NSArray<NSNumber *> *)conversationTypeList count:(int)count startTime:(long long)startTime __deprecated_msg("Use [RCCoreClient getConversationList:count:startTime:completion:] instead");

/*!
 获取单个会话数据
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @return                    会话的对象
 
 @remarks 会话
 @since 5.0.0
 */
- (nullable RCConversation *)getConversation:(RCConversationType)conversationType targetId:(NSString *)targetId __deprecated_msg("Use [RCCoreClient getConversation:targetId:completion:] instead");

/*!
 获取会话中的消息数量
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @return                    会话中的消息数量
 
 @discussion -1 表示获取消息数量出错。
 
 @remarks 会话
 @since 5.0.0
 */
- (int)getMessageCount:(RCConversationType)conversationType targetId:(NSString *)targetId __deprecated_msg("Use [RCCoreClient getMessageCount:targetId:completion:] instead");

/*!
 删除本地和服务的会话
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @return              本地会话是否删除成功
 
 @discussion 此方法会删除该会话，但是不会删除会话中的消息。如果此会话中有新的消息，该会话将重新在会话列表中显示，并显示最近的历史消息。
 @warning 此方法会同时删除本地和服务的会话。如果服务的会话删除失败，本地的会话依然会被删除
 SDK 在未连接的情况下，删除服务会话会失败
 
 @remarks 会话
 @since 5.0.0
 */
- (BOOL)removeConversation:(RCConversationType)conversationType targetId:(NSString *)targetId __deprecated_msg("Use [RCCoreClient removeConversation:targetId:completion:] instead");

/*!
 删除指定类型的会话

 @param conversationTypeList 会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 @return                        是否删除成功

 @discussion 此方法会从本地存储中删除该会话，同时删除会话中的消息。

 @discussion 此方法不支持超级群的会话类型，包含超级群时可能会造成数据异常。
 
 @remarks 会话
 @since 5.0.0
 */
- (BOOL)clearConversations:(NSArray<NSNumber *> *)conversationTypeList __deprecated_msg("Use [RCCoreClient clearConversations:completion:] instead");

/*!
 设置会话的置顶状态
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param isTop               是否置顶
 @return                    设置是否成功
 
 @discussion 会话不存在时设置置顶，会在会话列表生成会话。
 
 @remarks 会话
 @since 5.0.0
 */
- (BOOL)setConversationToTop:(RCConversationType)conversationType targetId:(NSString *)targetId isTop:(BOOL)isTop __deprecated_msg("Use [RCCoreClient setConversationToTop:targetId:isTop:completion:] instead");

/*!
 获取置顶的会话列表
 
 @param conversationTypeList 会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 @return                     置顶的会话 RCConversation 的列表
 
 @discussion 此方法会从本地数据库中，读取置顶的会话列表。
 
 @remarks 会话列表
 @since 5.0.0
 */
- (nullable NSArray<RCConversation *> *)getTopConversationList:(NSArray<NSNumber *> *)conversationTypeList __deprecated_msg("Use [RCCoreClient getTopConversationList:completion:] instead");

/*!
 获取会话的置顶状态
 
 @param conversationIdentifier 会话信息
 
 @discussion 此方法会从本地数据库中，读取该会话是否置顶。
 
 @remarks 会话
 @since 5.1.5
 */
- (BOOL)getConversationTopStatus:(RCConversationIdentifier *)conversationIdentifier __deprecated_msg("Use [RCCoreClient getConversationTopStatus:completion:] instead");

#pragma mark - 会话中的草稿操作 -
/*!
 获取会话中的草稿信息（用户输入但未发送的暂存消息）
 
 @param conversationType    会话类型
 @param targetId            会话目标 ID
 @return                    该会话中的草稿
 
 @remarks 会话
 @since 5.0.0
 */
- (nullable NSString *)getTextMessageDraft:(RCConversationType)conversationType targetId:(NSString *)targetId __deprecated_msg("Use [RCCoreClient getTextMessageDraft:targetId:completion:] instead");

/*!
 保存草稿信息（用户输入但未发送的暂存消息）
 
 @param conversationType    会话类型
 @param targetId            会话目标 ID
 @param content             草稿信息
 @return                    是否保存成功
 
 @remarks 会话
 @since 5.0.0
 */
- (BOOL)saveTextMessageDraft:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
                     content:(NSString *)content __deprecated_msg("Use [RCCoreClient saveTextMessageDraft:targetId:content:completion:] instead");

/*!
 删除会话中的草稿信息（用户输入但未发送的暂存消息）
 
 @param conversationType    会话类型
 @param targetId            会话目标 ID
 @return                    是否删除成功
 
 @remarks 会话
 @since 5.0.0
 */
- (BOOL)clearTextMessageDraft:(RCConversationType)conversationType targetId:(NSString *)targetId __deprecated_msg("Use [RCCoreClient clearTextMessageDraft:targetId:completion:] instead");


#pragma mark - 未读消息数 -

/*!
 获取所有的未读消息数（聊天室会话除外）
 
 @return    所有的未读消息数
 
 @remarks 会话
 @since 5.0.0
 */
- (int)getTotalUnreadCount __deprecated_msg("Use [RCCoreClient getTotalUnreadCountWith:] instead");

/*!
 获取某个会话内的未读消息数（聊天室会话除外）
 
 @param conversationType    会话类型
 @param targetId            会话目标 ID
 @return                    该会话内的未读消息数
 
 @remarks 会话
 @since 5.0.0
 */
- (int)getUnreadCount:(RCConversationType)conversationType targetId:(NSString *)targetId __deprecated_msg("Use [RCCoreClient getUnreadCount:targetId:completion:] instead");

/*!
 获取某个会话内的未读消息数
 
 @param conversationIdentifier 会话信息
 @param messageClassList            消息类型数组
 @return                    该会话内的未读消息数
 
 @discussion 此方法不支持聊天室和超级群的会话类型。
 
 @remarks 会话
 @since 5.1.5
 */
- (int)getUnreadCount:(RCConversationIdentifier *)conversationIdentifier messageClassList:(NSArray <Class> *)messageClassList __deprecated_msg("Use [RCCoreClient getUnreadCount:messageClassList:completion:] instead");

/*!
 获取某些会话的总未读消息数 （聊天室会话除外）
 
 @param conversations       会话列表 （ RCConversation 对象只需要 conversationType 和 targetId，channelId 按需使用）
 @return                    传入会话列表的未读消息数
 
 @discussion conversations会话个数不能超过300，超过会被截断。
 
 @remarks 会话
 @since 5.0.0
 */
- (int)getTotalUnreadCount:(NSArray<RCConversation *> *)conversations __deprecated_msg("Use [RCCoreClient getTotalUnreadCount:completion:] instead");

/*!
 获取某些类型的会话中所有的未读消息数 （聊天室会话除外）
 
 @param conversationTypes   会话类型的数组
 @param isContain           是否包含免打扰消息的未读数
 @return                    该类型的会话中所有的未读消息数
 
 @remarks 会话
 @since 5.0.0
 */
- (int)getUnreadCount:(NSArray<NSNumber *> *)conversationTypes containBlocked:(bool)isContain __deprecated_msg("Use [RCCoreClient getUnreadCount:containBlocked:completion:] instead");

/*!
 获取某个类型的会话中所有的未读消息数（聊天室会话除外）
 
 @param conversationTypes   会话类型的数组
 @return                    该类型的会话中所有的未读消息数
 
 @remarks 会话
 @since 5.0.0
 */
- (int)getUnreadCount:(NSArray<NSNumber *> *)conversationTypes __deprecated_msg("Use [RCCoreClient getUnreadCount:completion:] instead");

/*!
 获取某个类型的会话中所有未读的被 @ 的消息数
 
 @param conversationTypes   会话类型的数组
 @return                    该类型的会话中所有未读的被 @ 的消息数
 
 @remarks 会话
 @since 5.0.0
 */
- (int)getUnreadMentionedCount:(NSArray<NSNumber *> *)conversationTypes __deprecated_msg("Use [RCCoreClient getUnreadMentionedCount:completion:] instead");

/*!
 清除某个会话中的未读消息数
 
 @param conversationType    会话类型，不支持聊天室
 @param targetId            会话 ID
 @return                    是否清除成功
 
 @remarks 会话
 @discussion 此方法不支持超级群的会话类型。
 @since 5.0.0
 */
- (BOOL)clearMessagesUnreadStatus:(RCConversationType)conversationType targetId:(NSString *)targetId  __deprecated_msg("Use [RCCoreClient clearMessagesUnreadStatus:targetId:completion:] instead");

/*!
 清除某个会话中的未读消息数（该会话在时间戳 timestamp 之前的消息将被置成已读。）
 
 @param conversationType    会话类型，不支持聊天室
 @param targetId            会话 ID
 @param timestamp           该会话已阅读的最后一条消息的发送时间戳
 @return                    是否清除成功
 
 @remarks 会话
 @since 5.0.0
 */
- (BOOL)clearMessagesUnreadStatus:(RCConversationType)conversationType
                         targetId:(NSString *)targetId
                             time:(long long)timestamp  __deprecated_msg("Use [RCCoreClient clearMessagesUnreadStatus:targetId:time:completion:] instead");

#pragma mark - 会话的消息提醒 -

/*!
 设置会话的消息提醒状态
 
 @param conversationType            会话类型
 @param targetId                    会话 ID
 @param isBlocked                   是否屏蔽消息提醒
 @param successBlock                设置成功的回调
 [nStatus:会话设置的消息提醒状态]
 @param errorBlock                  设置失败的回调 [status:设置失败的错误码]
 
 @discussion
 如果您使用
 IMLibCore，此方法会屏蔽该会话的远程推送；如果您使用IMKit，此方法会屏蔽该会话的所有提醒（远程推送、本地通知、前台提示音）,该接口不支持聊天室。
 
 @remarks 会话
 @since 5.0.0
 */
- (void)setConversationNotificationStatus:(RCConversationType)conversationType
                                 targetId:(NSString *)targetId
                                isBlocked:(BOOL)isBlocked
                                  success:(nullable void (^)(RCConversationNotificationStatus nStatus))successBlock
                                    error:(nullable void (^)(RCErrorCode status))errorBlock __deprecated_msg("Use [RCChannelClient setConversationChannelNotificationLevel:targetId:channelId:level:success:error:] instead");

/*!
 获取消息免打扰会话列表
 
 @param conversationTypeList 会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 @return                     消息免打扰会话 RCConversation 的列表
 
 @discussion 此方法会从本地数据库中，读取消息免打扰会话列表。
 
 @remarks 会话列表
 @since 5.0.0
 */
- (nullable NSArray<RCConversation *> *)getBlockedConversationList:(NSArray<NSNumber *> *)conversationTypeList __deprecated_msg("Use [RCCoreClient getBlockedConversationList:completion:] instead");

#pragma mark - 全局消息提醒 -

/*!
 全局屏蔽某个时间段的消息提醒
 
 @param startTime       开始消息免打扰时间，格式为 HH:MM:SS
 @param spanMins        需要消息免打扰分钟数，0 < spanMins < 1440（ 比如，您设置的起始时间是 00：00， 结束时间为 01:00，则 spanMins 为 60 分钟。设置为 1439 代表全天免打扰 （23 * 60 + 59 = 1439 ））
 @param successBlock    屏蔽成功的回调
 @param errorBlock      屏蔽失败的回调 [status:屏蔽失败的错误码]
 
 @discussion 此方法设置的屏蔽时间会在每天该时间段时生效。
 如果您使用 IMLibCore，此方法会屏蔽所有会话在该时间段的远程推送；如果您使用
 IMKit，此方法会屏蔽所有会话在该时间段的所有提醒（远程推送、本地通知、前台提示音）。
 
 @remarks 会话
 @since 5.0.0
 */
- (void)setNotificationQuietHours:(NSString *)startTime
                         spanMins:(int)spanMins
                          success:(nullable void (^)(void))successBlock
                            error:(nullable void (^)(RCErrorCode status))errorBlock __deprecated_msg("Use [RCChannelClient  setNotificationQuietHoursLevel:spanMins:level:success:error:] instead");

/*!
 删除已设置的全局时间段消息提醒屏蔽
 
 @param successBlock    删除屏蔽成功的回调
 @param errorBlock      删除屏蔽失败的回调 [status:失败的错误码]
 
 @remarks 会话
 @since 5.0.0
 */
- (void)removeNotificationQuietHours:(nullable void (^)(void))successBlock
                               error:(nullable void (^)(RCErrorCode status))errorBlock
__deprecated_msg("Use [RCChannelClient removeNotificationQuietHours:success:error:] instead");

/*!
 查询已设置的全局时间段消息提醒屏蔽
 
 @param successBlock    屏蔽成功的回调 [startTime:已设置的屏蔽开始时间,
 spanMins:已设置的屏蔽时间分钟数，0 < spanMins < 1440]
 @param errorBlock      查询失败的回调 [status:查询失败的错误码]
 
 @remarks 会话
 @since 5.0.0
 */
- (void)getNotificationQuietHours:(nullable void (^)(NSString *startTime, int spanMins))successBlock
                            error:(nullable void (^)(RCErrorCode status))errorBlock
__deprecated_msg("Use [RCChannelClient getNotificationQuietHoursLevel:error:] instead");

#pragma mark - 工具类方法

/*!
 获取当前手机与服务器的时间差
 
 @return 时间差
 @discussion 消息发送成功后，SDK 会与服务器同步时间，消息所在数据库中存储的时间就是服务器时间。
 
 @remarks 数据获取
 @since 5.0.0
 */
- (long long)getDeltaTime  __deprecated_msg("Use [RCCoreClient getDeltaTime:] instead");

#pragma mark - 搜索

/*!
 根据关键字搜索指定会话中的消息
 
 @param conversationType 会话类型
 @param targetId         会话 ID
 @param keyword          关键字
 @param count            最大的查询数量
 @param startTime        查询 startTime 之前的消息（传 0 表示不限时间）
 
 @return 匹配的消息列表
 
 @discussion 超级群会话类型只支持搜索已存储到本地的消息。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (nullable NSArray<RCMessage *> *)searchMessages:(RCConversationType)conversationType
                                         targetId:(NSString *)targetId
                                          keyword:(NSString *)keyword
                                            count:(int)count
                                        startTime:(long long)startTime __deprecated_msg("Use [RCCoreClient searchMessages:targetId:keyword:count:startTime:completion:] instead");

/*!
 根据时间，偏移量和个数搜索指定会话中的消息
 
 @param conversationType 会话类型
 @param targetId         会话 ID
 @param keyword           关键字，传空默认为是查全部符合条件的消息
 @param startTime      查询 startTime 之后的消息， startTime >= 0
 @param endTime           查询 endTime 之前的消息，endTime > startTime
 @param offset             查询的消息的偏移量，offset >= 0
 @param limit               最大的查询数量，limit 需大于 0，最大值为100，如果大于100，会默认成100。
 
 @return 匹配的消息列表
 
 @discussion 超级群会话类型只支持搜索已存储到本地的消息。
 
 @remarks 消息操作
 @since 5.1.2
 */
- (nullable NSArray<RCMessage *> *)searchMessages:(RCConversationType)conversationType
                                         targetId:(NSString *)targetId
                                          keyword:(NSString *)keyword
                                        startTime:(long long)startTime
                                          endTime:(long long)endTime
                                           offset:(int)offset
                                            limit:(int)limit __deprecated_msg("Use [RCCoreClient searchMessages:targetId:keyword:count:startTime:endTime:offset:limit:completion:] instead");

/*!
 按用户 ID 搜索指定会话中的消息
 
 @param conversationType 会话类型
 @param targetId         会话 ID
 @param userId           搜索用户 ID
 @param count            最大的查询数量
 @param startTime        查询 startTime 之前的消息（传 0 表示不限时间）
 
 @return 匹配的消息列表
 
 @discussion 超级群会话类型只支持搜索已存储到本地的消息。
 
 @remarks 消息操作
 @since 5.0.0
 */
- (nullable NSArray<RCMessage *> *)searchMessages:(RCConversationType)conversationType
                                         targetId:(NSString *)targetId
                                           userId:(NSString *)userId
                                            count:(int)count
                                        startTime:(long long)startTime __deprecated_msg("Use [RCCoreClient searchMessages:targetId:userId:count:startTime:completion:] instead");

/*!
 根据关键字搜索会话
 
 @param conversationTypeList 需要搜索的会话类型列表
 @param objectNameList       需要搜索的消息类型名列表(即每个消息类方法 getObjectName 的返回值)
 @param keyword              关键字，非空
 
 @return 匹配的会话搜索结果列表
 
 @discussion 目前，SDK 内置的文本消息、文件消息、图文消息支持搜索。
 自定义的消息必须要实现 RCMessageContent 的 getSearchableWords 接口才能进行搜索。
 
 @discussion conversationTypeList 包含超级群会话类型时，超级群会话只搜索已存储到本地的消息记录。
 @discussion conversationTypeList中类型个数不能超过300，超过会被截断。
 @discussion objectNameList中类型名个数不能超过300，超过会被截断。
 
 @discussion conversationTypeList 传值时：
 OC 需转成 NSNumber 传入（例如 @[ @(ConversationType_PRIVATE) ]），
 Swift 需获取到 rawValue 强转成 NSNumber 传入
 （例如 let privateType = NSNumber(value: RCConversationType.ConversationType_PRIVATE.rawValue)
 [privateType]  ）
 
 @remarks 消息操作
 @since 5.0.0
 */
- (nullable NSArray<RCSearchConversationResult *> *)searchConversations:(NSArray<NSNumber *> *)conversationTypeList
                                                            messageType:(NSArray<NSString *> *)objectNameList
                                                                keyword:(NSString *)keyword __deprecated_msg("Use [RCCoreClient searchConversations:messageType:keyword:completion:] instead");

#pragma mark - 消息扩展 -

/*!
 获取标签列表
 
 @return 标签列表
 @remarks 高级功能
 @since 5.1.1
 */
- (NSArray<RCTagInfo *> *)getTags __deprecated_msg("Use [RCCoreClient getTags:] instead");

/*!
 获取会话的所有标签
 
 @param conversationIdentifier 会话信息
 @return  会话所属的标签列表
 
 @discussion 此方法不支持超级群的会话类型。
 @remarks 高级功能
 @since 5.1.1
 */
- (nullable NSArray<RCConversationTagInfo *> *)getTagsFromConversation:(RCConversationIdentifier *)conversationIdentifier __deprecated_msg("Use [RCCoreClient getTagsFromConversation:completion:] instead");

/*!
 分页获取标签中会话列表
 
 @param tagId 标签 ID
 @param timestamp            会话的时间戳（获取这个时间戳之前的会话列表，0表示从最新开始获取）
 @param count                获取的数量（当实际取回的会话数量小于 count 值时，表明已取完数据）
 @return                     会话 RCConversation 的列表
 
 @discussion 此方法不支持超级群的会话类型。
 @remarks 高级功能
 @since 5.1.1
 */
- (nullable NSArray<RCConversation *> *)getConversationsFromTagByPage:(NSString *)tagId
                                                            timestamp:(long long)timestamp
                                                                count:(int)count __deprecated_msg("Use [RCCoreClient getConversationsFromTagByPage:timestamp:count:completion:] instead");

/*!
 获取标签中会话消息未读数
 
 @param tagId 标签 ID
 @param isContain    是否包含免打扰会话
 @return 会话消息未读数
 
 @discussion 此方法不支持超级群的会话类型。
 @remarks 高级功能
 @since 5.1.1
 */
- (int)getUnreadCountByTag:(NSString *)tagId
            containBlocked:(BOOL)isContain __deprecated_msg("Use [RCCoreClient getUnreadCountByTag:containBlocked:completion:] instead");

/*!
 获取标签中的会话置顶状态
 
 @param conversationIdentifier 会话信息
 @param tagId 标签 ID
 @return 置顶状态
 
 @discussion 此方法不支持超级群的会话类型。
 @remarks 高级功能
 @since 5.1.1
 */
- (BOOL)getConversationTopStatusInTag:(RCConversationIdentifier *)conversationIdentifier tagId:(NSString *)tagId __deprecated_msg("Use [RCCoreClient getConversationTopStatusInTag:tagId:completion:] instead");

/*!
 清除标签对应会话的未读消息数
 
 @param tagId 标签 ID
 @return 是否清除成功
 
 @discussion 此方法不支持超级群的会话类型。
 @remarks 高级功能
 @since 5.1.5
 */
- (BOOL)clearMessagesUnreadStatusByTag:(NSString *)tagId  __deprecated_msg("Use [RCCoreClient clearMessagesUnreadStatusByTag:completion:] instead");

@end

NS_ASSUME_NONNULL_END
