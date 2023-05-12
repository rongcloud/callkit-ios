//
//  RCChannelClient+Deprecated.h
//  RongIMLibCore
//
//  Created by shuai shao on 2023/1/29.
//  Copyright © 2023 RongCloud. All rights reserved.
//

#import <RongIMLibCore/RongIMLibCore.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @since 5.4.1
 @warning 本文件的方法已经过期，请您替换 RCChannelClient 中的方法。
 */
@interface RCChannelClient (Deprecated)

#pragma mark - 消息发送 -

/*!
 发送消息
 
 @param conversationType    发送消息的会话类型
 @param targetId            发送消息的会话 ID
 @param channelId          所属会话的业务标识
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
 @since 5.1.1
 */
- (nullable RCMessage *)sendMessage:(RCConversationType)conversationType
                           targetId:(NSString *)targetId
                          channelId:(nullable NSString *)channelId
                            content:(RCMessageContent *)content
                        pushContent:(nullable NSString *)pushContent
                           pushData:(nullable NSString *)pushData
                            success:(nullable void (^)(long messageId))successBlock
                              error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock __deprecated_msg("Use [RCChannelClient sendMessage:targetId:channelId:content:pushContent:pushData:attached:success:error:] instead");

/*!
 发送消息
 
 @param conversationType    发送消息的会话类型
 @param targetId            发送消息的会话 ID
 @param channelId          所属会话的业务标识
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
 @since 5.1.1
 */
- (nullable RCMessage *)sendMessage:(RCConversationType)conversationType
                           targetId:(NSString *)targetId
                          channelId:(nullable NSString *)channelId
                            content:(RCMessageContent *)content
                        pushContent:(nullable NSString *)pushContent
                           pushData:(nullable NSString *)pushData
                             option:(RCSendMessageOption *)option
                            success:(nullable void (^)(long messageId))successBlock
                              error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock __deprecated_msg("Use [RCChannelClient sendMessage:targetId:channelId:content:pushContent:pushData:option:attached:success:error:] instead");

/*!
 发送媒体消息（图片消息或文件消息）
 
 @param conversationType    发送消息的会话类型
 @param targetId            发送消息的会话 ID
 @param channelId          所属会话的业务标识
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
 @since 5.1.1
 */
- (nullable RCMessage *)sendMediaMessage:(RCConversationType)conversationType
                                targetId:(NSString *)targetId
                               channelId:(nullable NSString *)channelId
                                 content:(RCMessageContent *)content
                             pushContent:(nullable NSString *)pushContent
                                pushData:(nullable NSString *)pushData
                                progress:(nullable void (^)(int progress, long messageId))progressBlock
                                 success:(nullable void (^)(long messageId))successBlock
                                   error:(nullable void (^)(RCErrorCode errorCode, long messageId))errorBlock
                                  cancel:(nullable void (^)(long messageId))cancelBlock __deprecated_msg("Use [RCChannelClient sendMediaMessage:targetId:channelId:content:pushContent:pushData:attached:progress:success:error:cancel:] instead");

/*!
 发送媒体消息(上传图片或文件等媒体信息到指定的服务器)
 
 @param conversationType    发送消息的会话类型
 @param targetId            发送消息的会话 ID
 @param channelId          所属会话的业务标识
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
 @since 5.1.1
 */
- (nullable RCMessage *)sendMediaMessage:(RCConversationType)conversationType
                                targetId:(NSString *)targetId
                               channelId:(nullable NSString *)channelId
                                 content:(RCMessageContent *)content
                             pushContent:(nullable NSString *)pushContent
                                pushData:(nullable NSString *)pushData
                           uploadPrepare:(nullable void (^)(RCUploadMediaStatusListener *uploadListener))uploadPrepareBlock
                                progress:(nullable void (^)(int progress, long messageId))progressBlock
                                 success:(nullable void (^)(long messageId))successBlock
                                   error:(nullable void (^)(RCErrorCode errorCode, long messageId))errorBlock
                                  cancel:(nullable void (^)(long messageId))cancelBlock  __deprecated_msg("Use [RCChannelClient sendMediaMessage:targetId:channelId:content:pushContent:pushData:attached:uploadPrepare:progress:success:error:cancel:] instead");



/*!
 插入向外发送的、指定时间的消息（此方法如果 sentTime 有问题会影响消息排序，慎用！！）
 （该消息只插入本地数据库，实际不会发送给服务器和对方）
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param sentStatus          发送状态
 @param content             消息的内容
 @param sentTime            消息发送的 Unix 时间戳，单位为毫秒（传 0 会按照本地时间插入）
 @return                    插入的消息实体
 
 @discussion 此方法不支持聊天室的会话类型。如果 sentTime<=0，则被忽略，会以插入时的时间为准。
 
 @remarks 消息操作
 @since 5.1.1
 */
- (nullable RCMessage *)insertOutgoingMessage:(RCConversationType)conversationType
                                     targetId:(NSString *)targetId
                                    channelId:(nullable NSString *)channelId
                                   sentStatus:(RCSentStatus)sentStatus
                                      content:(RCMessageContent *)content
                                     sentTime:(long long)sentTime __deprecated_msg("Use [RCChannelClient insertOutgoingMessage:targetId:channelId:sentStatus:content:sentTime:completion:] instead");

/*!
 插入接收的消息（此方法如果 sentTime
 有问题会影响消息排序，慎用！！）（该消息只插入本地数据库，实际不会发送给服务器和对方）
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param senderUserId        发送者 ID
 @param receivedStatus      接收状态
 @param content             消息的内容
 @param sentTime            消息发送的 Unix 时间戳，单位为毫秒 （传 0 会按照本地时间插入）
 @return                    插入的消息实体
 
 @discussion 此方法不支持聊天室的会话类型。
 
 @remarks 消息操作
 @since 5.1.1
 */
- (nullable RCMessage *)insertIncomingMessage:(RCConversationType)conversationType
                                     targetId:(NSString *)targetId
                                    channelId:(nullable NSString *)channelId
                                 senderUserId:(NSString *)senderUserId
                               receivedStatus:(RCReceivedStatus)receivedStatus
                                      content:(RCMessageContent *)content
                                     sentTime:(long long)sentTime __deprecated_msg("Use [RCChannelClient insertIncomingMessage:targetId:channelId:senderUserId:receivedStatus:content:sentTime:completion:] instead");

/*!
 发送定向消息
 
 @param conversationType 发送消息的会话类型
 @param targetId         发送消息的会话 ID
 @param channelId          所属会话的业务标识
 @param userIdList       接收消息的用户 ID 列表
 @param content          消息的内容
 @param pushContent      接收方离线时需要显示的远程推送内容
 @param pushData         接收方离线时需要在远程推送中携带的非显示数据
 @param successBlock     消息发送成功的回调 [messageId:消息的 ID]
 @param errorBlock       消息发送失败的回调 [errorCode:发送失败的错误码, messageId:消息的 ID]
 
 @return 发送的消息实体
 
 @discussion 此方法用于在群组和讨论组中发送消息给其中的部分用户，其它用户不会收到这条消息。
 如果您使用 IMLibCore，可以使用此方法发送定向消息；
 如果您使用 IMKit，请使用 RCIM 中的同名方法发送定向消息，否则不会自动更新 UI。
 @discussion userIdList里ID个数不能超过300，超过会被截断。
 
 @warning 此方法目前仅支持普通群组和讨论组。
 
 @remarks 消息操作
 @since 5.1.1
 */
- (nullable RCMessage *)sendDirectionalMessage:(RCConversationType)conversationType
                                      targetId:(NSString *)targetId
                                     channelId:(nullable NSString *)channelId
                                  toUserIdList:(NSArray<NSString *> *)userIdList
                                       content:(RCMessageContent *)content
                                   pushContent:(nullable NSString *)pushContent
                                      pushData:(nullable NSString *)pushData
                                       success:(nullable void (^)(long messageId))successBlock
                                         error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock __deprecated_msg("Use [RCChannelClient sendDirectionalMessage:targetId:channelId:toUserIdList:content:pushContent:pushData:attached:success:error:] instead");

/*!
 发送定向消息
 
 @param conversationType 发送消息的会话类型
 @param targetId         发送消息的会话 ID
 @param channelId          所属会话的业务标识
 @param userIdList       接收消息的用户 ID 列表
 @param content          消息的内容
 @param pushContent      接收方离线时需要显示的远程推送内容
 @param pushData         接收方离线时需要在远程推送中携带的非显示数据
 @param option              消息的相关配置
 @param successBlock     消息发送成功的回调 [messageId:消息的 ID]
 @param errorBlock       消息发送失败的回调 [errorCode:发送失败的错误码,
 messageId:消息的 ID]
 
 @return 发送的消息实体
 
 @discussion 此方法用于在群组和讨论组中发送消息给其中的部分用户，其它用户不会收到这条消息。
 如果您使用 IMLibCore，可以使用此方法发送定向消息；
 如果您使用 IMKit，请使用 RCIM 中的同名方法发送定向消息，否则不会自动更新 UI。
 userIdList里ID个数不能超过300，超过会被截断。
 
 @warning 此方法目前仅支持普通群组和讨论组。
 
 @remarks 消息操作
 @since 5.1.2
 */
- (nullable RCMessage *)sendDirectionalMessage:(RCConversationType)conversationType
                                      targetId:(NSString *)targetId
                                     channelId:(nullable NSString *)channelId
                                  toUserIdList:(NSArray<NSString *> *)userIdList
                                       content:(RCMessageContent *)content
                                   pushContent:(nullable NSString *)pushContent
                                      pushData:(nullable NSString *)pushData
                                        option:(RCSendMessageOption *)option
                                       success:(nullable void (^)(long messageId))successBlock
                                         error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock __deprecated_msg("Use [RCChannelClient sendDirectionalMessage:targetId:channelId:toUserIdList:content:pushContent:pushData:option:attached:success:error:] instead");

#pragma mark - 消息操作 -

/*!
 获取某个会话中指定数量的最新消息实体
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param count               需要获取的消息数量
 @return                    消息实体 RCMessage 对象列表
 
 @discussion
 此方法会获取该会话中指定数量的最新消息实体，返回的消息实体按照时间从新到旧排列。
 如果会话中的消息数量小于参数 count 的值，会将该会话中的所有消息返回。
 
 @remarks 消息操作
 @since 5.1.1
 */
- (nullable NSArray<RCMessage *> *)getLatestMessages:(RCConversationType)conversationType
                                            targetId:(NSString *)targetId
                                           channelId:(nullable NSString *)channelId
                                               count:(int)count
__deprecated_msg("Use [RCChannelClient getLatestMessages:targetId:channelId:count:completion:] instead");

/*!
 获取会话中，从指定消息之前、指定数量的最新消息实体
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
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
 @since 5.1.1
 */
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                             targetId:(NSString *)targetId
                                            channelId:(nullable NSString *)channelId
                                      oldestMessageId:(long)oldestMessageId
                                                count:(int)count
__deprecated_msg("Use [RCChannelClient getHistoryMessages:targetId:channelId:oldestMessageId:count:completion:] instead");

/*!
 获取会话中，从指定消息之前、指定数量的、指定消息类型的最新消息实体
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
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
 @since 5.1.1
 */
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                             targetId:(NSString *)targetId
                                            channelId:(nullable NSString *)channelId
                                           objectName:(nullable NSString *)objectName
                                      oldestMessageId:(long)oldestMessageId
                                                count:(int)count
__deprecated_msg("Use [RCChannelClient getHistoryMessages:targetId:channelId:objectName:oldestMessageId:count:completion:] instead");

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
 
 @discussion 超级群不会接收离线消息，超级群调用该接口会出现消息断档的情况，请使用断档消息接口获取超级群消息。
 
 @remarks 消息操作
 @since 5.1.1
 */
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                             targetId:(NSString *)targetId
                                            channelId:(nullable NSString *)channelId
                                           objectName:(nullable NSString *)objectName
                                        baseMessageId:(long)baseMessageId
                                            isForward:(BOOL)isForward
                                                count:(int)count
__deprecated_msg("Use [RCChannelClient getHistoryMessages:targetId:channelId:objectName:baseMessageId:isForward:count:completion:] instead");

/*!
 获取会话中，指定时间、指定数量、指定消息类型（多个）、向前或向后查找的消息实体列表
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param objectNames         消息内容的类型名称列表
 @param sentTime            当前的消息时间戳
 @param isForward           查询方向 true 为向前，false 为向后
 @param count               需要获取的消息数量
 @return                    消息实体 RCMessage 对象列表
 
 @discussion
 此方法会获取该会话中，sentTime
 之前或之后的、指定数量、指定消息类型（多个）的消息实体列表，返回的消息实体按照时间从新到旧排列。
 返回的消息中不包含 sentTime 对应的那条消息，如果会话中的消息数量小于参数 count 的值，会将该会话中的所有消息返回。
 
 @discussion 超级群不会接收离线消息，超级群调用该接口会出现消息断档的情况，请使用断档消息接口获取超级群消息。
 
 @remarks 消息操作
 @since 5.1.1
 */
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                             targetId:(NSString *)targetId
                                            channelId:(nullable NSString *)channelId
                                          objectNames:(NSArray<NSString *> *)objectNames
                                             sentTime:(long long)sentTime
                                            isForward:(BOOL)isForward
                                                count:(int)count  __deprecated_msg("Use [RCChannelClient getHistoryMessages:targetId:channelId:objectName:sentTime:isForward:count:completion:] instead");

/*!
 在会话中搜索指定消息的前 beforeCount 数量和后 afterCount
 数量的消息。返回的消息列表中会包含指定的消息。消息列表时间顺序从新到旧。
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param sentTime            消息的发送时间
 @param beforeCount         指定消息的前部分消息数量
 @param afterCount          指定消息的后部分消息数量
 @return                    消息实体 RCMessage 对象列表
 
 @discussion
 获取该会话的这条消息及这条消息前 beforeCount 条和后 afterCount 条消息,如前后消息不够则返回实际数量的消息。
 
 @discussion 此方法不支持超级群的会话类型。
 
 @remarks 消息操作
 @since 5.1.1
 */
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                             targetId:(NSString *)targetId
                                            channelId:(nullable NSString *)channelId
                                             sentTime:(long long)sentTime
                                          beforeCount:(int)beforeCount
                                           afterCount:(int)afterCount __deprecated_msg("Use [RCChannelClient getHistoryMessages:targetId:channelId:sentTime:beforeCount:afterCount:completion:] instead");;

/*!
 获取会话中 @ 提醒自己的消息
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 
 @discussion
 此方法从本地获取被@提醒的消息(最多返回 10 条信息)
 @warning 使用 IMKit 注意在进入会话页面前调用，否则在进入会话清除未读数的接口 clearMessagesUnreadStatus: targetId:
 以及 设置消息接收状态接口 setMessageReceivedStatus:receivedStatus:会同步清除被提示信息状态。
 
 @remarks 高级功能
 @since 5.1.1
 */
- (nullable NSArray<RCMessage *> *)getUnreadMentionedMessages:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getUnreadMentionedMessages:targetId:channelId:completion:] instead");

/*!
 获取本地指定会话的未读条数的 @ 消息列表，仅支持群组
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param count           未读的 @ 消息，取值范围 [1,100]
 @param desc           是否是降序查
 @discussion 假如有 1000 条未读的 @ 消息，取 100 条未读
 desc 为 true 时获取后 100 条消息，messageList 的顺序是 901 到 1000
 desc 为 false 是获取前 100 条消息，messageList 的顺序是 1 到 100
 
 @warning 使用 IMKit 注意在进入会话页面前调用，否则在进入会话清除未读数的接口 clearMessagesUnreadStatus: targetId:
 以及 设置消息接收状态接口 setMessageReceivedStatus:receivedStatus:会同步清除被提示信息状态。
 @discussion 5.1.9 stable 单独添加该接口
 @since 5.2.5
 */

- (nullable NSArray<RCMessage *> *)getUnreadMentionedMessages:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId count:(int)count desc:(BOOL)desc __deprecated_msg("Use [RCChannelClient getUnreadMentionedMessages:targetId:channelId:count:desc:completion:] instead");

/*!
 根据会话 id 获取所有子频道的 @ 未读消息总数
 
 @param targetId  会话 ID
 @return         该会话内的未读消息数
 
 @remarks 超级群消息操作
 @since 5.2.0
 */
- (int)getUltraGroupUnreadMentionedCount:(NSString *)targetId __deprecated_msg("Use [RCChannelClient getUltraGroupUnreadMentionedCount:completion:] instead");

/**
 * 获取会话里第一条未读消息。
 *
 * @param conversationType 会话类型
 * @param targetId   会话 ID
 * @param channelId  所属会话的业务标识
 * @return 第一条未读消息的实体。
 * @remarks 消息操作
 * @discussion 前提：超级群会话不接收离线消息。
 *  用户在线接收的超级群未读消息已经保存到本地数据库，可以通过此接口获取到
 *  用户离线的超级群未读消息，用户在线之后不收离线未读消息，通过此接口获取第一条未读消息为空
 * @since 5.1.1
 */
- (nullable RCMessage *)getFirstUnreadMessage:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getFirstUnreadMessage:targetId:channelId:completion:] instead");

/*!
 删除本地所有 channel 特定时间之前的消息
 
 @param targetId            会话 ID
 @param timestamp          会话的时间戳
 @return             是否删除成功
 
 @remarks 消息操作
 @since 5.2.0
 */
- (BOOL)deleteUltraGroupMessagesForAllChannel:(NSString *)targetId timestamp:(long long)timestamp __deprecated_msg("Use [RCChannelClient deleteUltraGroupMessagesForAllChannel:timestamp:completion:] instead");

/*!
 删除本地特定 channel 特点时间之前的消息
 
 @param targetId            会话 ID
 @param channelId           频道 ID
 @param timestamp          会话的时间戳
 @return             是否删除成功
 
 @remarks 消息操作
 @since 5.2.0
 */
- (BOOL)deleteUltraGroupMessages:(NSString *)targetId
                       channelId:(nullable NSString *)channelId
                       timestamp:(long long)timestamp __deprecated_msg("Use [RCChannelClient deleteUltraGroupMessages:channelId:timestamp:completion:] instead");

/*!
 删除某个会话中的所有消息
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @return                    是否删除成功
 
 @remarks 消息操作
 @since 5.1.1
 */
- (BOOL)clearMessages:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient clearMessages:targetId:channelId:completion:] instead");

#pragma mark - 会话列表操作 -

/*!
 获取会话列表
 
 @param conversationTypeList   会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 @param channelId          所属会话的业务标识
 @return                        会话 RCConversation 的列表
 
 @discussion 此方法会从本地数据库中，读取会话列表。
 返回的会话列表按照时间从前往后排列，如果有置顶的会话，则置顶的会话会排列在前面。
 @discussion 当您的会话较多且没有清理机制的时候，强烈建议您使用 getConversationList: count: startTime:
 分页拉取会话列表,否则有可能造成内存过大。
 @discussion conversationTypeList中类型个数不能超过300，超过会被截断。
 
 @remarks 会话列表
 @since 5.1.1
 */
- (nullable NSArray<RCConversation *> *)getConversationList:(NSArray<NSNumber *> *)conversationTypeList channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getConversationList:channelId:completion:] instead");

/*!
 分页获取会话列表
 
 @param conversationTypeList 会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 @param channelId          所属会话的业务标识
 @param count                获取的数量（当实际取回的会话数量小于 count 值时，表明已取完数据）
 @param startTime            会话的时间戳（获取这个时间戳之前的会话列表，0表示从最新开始获取）
 @return                     会话 RCConversation 的列表
 
 @discussion 此方法会从本地数据库中，读取会话列表。
 返回的会话列表按照时间从前往后排列，如果有置顶的会话，则置顶的会话会排列在前面。
 @discussion conversationTypeList中类型个数不能超过300，超过会被截断。
 
 @remarks 会话列表
 @since 5.1.1
 */
- (nullable NSArray<RCConversation *> *)getConversationList:(NSArray<NSNumber *> *)conversationTypeList channelId:(nullable NSString *)channelId count:(int)count startTime:(long long)startTime __deprecated_msg("Use [RCChannelClient getConversationList:channelId:count:startTime:completion:] instead");

/*!
 获取特定会话下所有频道的会话列表
 
 @param conversationType         会话类型
 @param targetId                           会话 ID
 @return                    会话 RCConversation 的列表
 
 @discussion 此方法会从本地数据库中，读取会话列表。
 返回的会话列表按照时间从前往后排列，如果有置顶的会话，则置顶的会话会排列在前面。
 
 @remarks 会话列表
 @since 5.2.0
 */
- (nullable NSArray<RCConversation *> *)getConversationListForAllChannel:(RCConversationType)conversationType targetId:(NSString *)targetId __deprecated_msg("Use [RCChannelClient getConversationListForAllChannel:targetId:completion:] instead");

/*!
 分页获取特定会话类型下所有 channel 的会话列表
 @param conversationTypeList         会话类型数组
 @param count                                           会话个数
 @param startTime                                 开始时间，首次可传入 0
 @return                    会话 RCConversation 的列表
 
 @discussion 此方法会从本地数据库中，读取会话列表。
 返回的会话列表按照时间从前往后排列，如果有置顶的会话，则置顶的会话会排列在前面。
 @since 5.2.3
 */
- (nullable NSArray<RCConversation *> *)getConversationListForAllChannel:(NSArray<NSNumber *> *)conversationTypeList count:(int)count startTime:(long long)startTime __deprecated_msg("Use [RCChannelClient getConversationListForAllChannel:count:startTime:completion:] instead");

/*!
 获取所有含 ChannelId 会话列表
 
 @param conversationTypeList 会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 @return                     会话 RCConversation 的列表
 
 @discussion 此方法会从本地数据库中，读取会话列表。
 返回的会话列表按照时间从前往后排列，如果有置顶的会话，则置顶的会话会排列在前面。
 
 @warning  当会话数量多的时候，会有性能问题，所以建议在非主线程调用该接口
 @remarks 会话列表
 @since 5.2.3
 */
- (nullable NSArray<RCConversation *> *)getConversationListForAllChannel:(NSArray<NSNumber *> *)conversationTypeList __deprecated_msg("Use [RCChannelClient getConversationListForAllChannel:completion:] instead");

/*!
 获取单个会话数据
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @return                    会话的对象
 
 @remarks 会话
 @since 5.1.1
 */
- (nullable RCConversation *)getConversation:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getConversation:targetId:channelId:completion:] instead");

/*!
 获取会话中的消息数量
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId           所属会话的业务标识
 @param completion          异步回调[会话中的消息数量]
 
 @discussion -1 表示获取消息数量出错。
 
 @remarks 会话
 @since 5.1.1
 */
- (int)getMessageCount:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getMessageCount:targetId:channelId:completion:] instead");

/*!
 删除指定类型的会话
 
 @param conversationTypeList 会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 @param channelId          所属会话的业务标识
 @return                        是否删除成功
 
 @discussion 此方法会从本地存储中删除该会话，同时删除会话中的消息。
 
 @discussion 此方法不支持超级群的会话类型，包含超级群时可能会造成数据异常。
 @discussion conversationTypeList中类型个数不能超过300，超过会被截断。
 
 @remarks 会话
 @since 5.1.1
 */
- (BOOL)clearConversations:(NSArray<NSNumber *> *)conversationTypeList channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient clearConversations:channelId:completion:] instead");

/*!
 删除本地和服务的会话
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @return              本地会话是否删除成功
 
 @discussion 此方法会删除该会话，但是不会删除会话中的消息。如果此会话中有新的消息，该会话将重新在会话列表中显示，并显示最近的历史消息。
 @warning 此方法会同时删除本地和服务的会话。如果服务的会话删除失败，本地的会话依然会被删除
 SDK 在未连接的情况下，删除服务会话会失败
 
 @remarks 会话
 @since 5.1.1
 */
- (BOOL)removeConversation:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient removeConversation:targetId:channelId:completion:] instead");

/*!
 设置会话的置顶状态
 
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param isTop               是否置顶
 @return                    设置是否成功
 
 @discussion 会话不存在时设置置顶，会在会话列表生成会话。
 
 @remarks 会话
 @since 5.1.1
 */
- (BOOL)setConversationToTop:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId isTop:(BOOL)isTop __deprecated_msg("Use [RCChannelClient setConversationToTop:targetId:channelId:isTop:completion:] instead");

/*!
 获取会话的置顶状态
 
 @param conversationIdentifier 会话信息
 @param channelId          所属会话的业务标识
 
 @discussion 此方法会从本地数据库中，读取该会话是否置顶。
 
 @remarks 会话
 @since 5.1.5
 */
- (BOOL)getConversationTopStatus:(RCConversationIdentifier *)conversationIdentifier channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getConversationTopStatus:channelId:completion:] instead");

/*!
 获取置顶的会话列表
 
 @param conversationTypeList 会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 @return                     置顶的会话 RCConversation 的列表
 
 @discussion 此方法会从本地数据库中，读取置顶的会话列表。
 
 @remarks 会话列表
 @since 5.1.1
 */
- (nullable NSArray<RCConversation *> *)getTopConversationList:(NSArray<NSNumber *> *)conversationTypeList channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getTopConversationList:channelId:completion:] instead");

#pragma mark - 会话中的草稿操作 -

/*!
 获取会话中的草稿信息（用户输入但未发送的暂存消息）
 
 @param conversationType    会话类型
 @param targetId            会话目标 ID
 @param channelId          所属会话的业务标识
 @return                    该会话中的草稿
 
 @remarks 会话
 @since 5.1.1
 */
- (nullable NSString *)getTextMessageDraft:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getTextMessageDraft:targetId:channelId:completion:] instead");

/*!
 保存草稿信息（用户输入但未发送的暂存消息）
 
 @param conversationType    会话类型
 @param targetId            会话目标 ID
 @param channelId          所属会话的业务标识
 @param content             草稿信息
 @return                    是否保存成功
 
 @remarks 会话
 @since 5.1.1
 */
- (BOOL)saveTextMessageDraft:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
                   channelId:(nullable NSString *)channelId
                     content:(NSString *)content __deprecated_msg("Use [RCChannelClient saveTextMessageDraft:targetId:channelId:content:completion:] instead");

/*!
 删除会话中的草稿信息（用户输入但未发送的暂存消息）
 
 @param conversationType    会话类型
 @param targetId            会话目标 ID
 @param channelId          所属会话的业务标识
 @return 是否删除成功
 
 @remarks 会话
 @since 5.1.1
 */
- (BOOL)clearTextMessageDraft:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient clearTextMessageDraft:targetId:channelId:completion:] instead");

#pragma mark - 未读消息数 -

/*!
 获取所有的未读消息数（聊天室会话除外）
 
 @param channelId          所属会话的业务标识
 
 @return    所有的未读消息数（含免打扰会话未读数）
 
 @remarks 会话
 @since 5.1.1
 */
- (int)getTotalUnreadCountWithChannelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getTotalUnreadCountWithChannelId:completion:] instead");

/*!
 获取所有的未读消息数（聊天室会话除外）
 
 @param channelId          所属会话的业务标识
 @param isContain          是否包含免打扰会话的未读数，YES 包含免打扰会话未读数
 
 @return    所有的未读消息数
 
 @remarks 会话
 @since 5.2.3
 */
- (int)getTotalUnreadCountWithChannelId:(nullable NSString *)channelId containBlocked:(BOOL)isContain __deprecated_msg("Use [RCChannelClient getTotalUnreadCountWithChannelId:containBlocked:completion:] instead");

/*!
 获取某个会话内的未读消息数（聊天室会话除外）
 
 @param conversationType    会话类型
 @param targetId            会话目标 ID
 @param channelId          所属会话的业务标识
 @return                    该会话内的未读消息数
 
 @remarks 会话
 @since 5.1.1
 */
- (int)getUnreadCount:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getUnreadCount:targetId:channelId:completion:] instead");

/*!
 获取某个会话内的未读消息数
 
 @param conversationIdentifier 会话信息
 @param messageClassList          消息类型数组
 @param channelId                         所属会话的业务标识
 @return                    该会话内的未读消息数
 
 @discussion 此方法不支持聊天室和超级群的会话类型。
 
 @remarks 会话
 @since 5.1.5
 */
- (int)getUnreadCount:(RCConversationIdentifier *)conversationIdentifier messageClassList:(NSArray <Class> *)messageClassList channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getUnreadCount:messageClassList:channelId:completion:] instead");

/**
 获取某些类型的会话中所有的未读消息数 （聊天室会话除外）
 
 @param conversationTypes   会话类型的数组
 @param channelId          所属会话的业务标识
 @param isContain           是否包含免打扰消息的未读数
 @return                    该类型的会话中所有的未读消息数
 
 @discussion conversationTypes中类型个数不能超过300，超过会被截断。
 
 @remarks 会话
 @since 5.1.1
 */
- (int)getUnreadCount:(NSArray<NSNumber *> *)conversationTypes channelId:(nullable NSString *)channelId containBlocked:(bool)isContain __deprecated_msg("Use [RCChannelClient getUnreadCount:channelId:containBlocked:completion:] instead");

/*!
 获取某个类型的会话中所有未读的被 @ 的消息数
 
 @param conversationTypes   会话类型的数组
 @param channelId          所属会话的业务标识
 @return                    该类型的会话中所有未读的被 @ 的消息数
 
 @discussion conversationTypeList中类型个数不能超过300，超过会被截断。
 
 @remarks 会话
 @since 5.1.1
 */
- (int)getUnreadMentionedCount:(NSArray<NSNumber *> *)conversationTypes channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getUnreadMentionedCount:channelId:completion:] instead");

/*!
 清除某个会话中的未读消息数
 
 @param conversationType    会话类型，不支持聊天室
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @return                    是否清除成功
 
 @remarks 会话
 @discussion 此方法不支持超级群的会话类型。
 @since 5.1.1
 */
- (BOOL)clearMessagesUnreadStatus:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient clearMessagesUnreadStatus:targetId:channelId:completion:] instead");

/*!
 清除某个会话中的未读消息数（该会话在时间戳 timestamp 之前的消息将被置成已读。）
 
 @param conversationType    会话类型，不支持聊天室
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param timestamp           该会话已阅读的最后一条消息的发送时间戳
 @return                    是否清除成功
 
 @remarks 会话
 @since 5.1.1
 */
- (BOOL)clearMessagesUnreadStatus:(RCConversationType)conversationType
                         targetId:(NSString *)targetId
                        channelId:(nullable NSString *)channelId
                             time:(long long)timestamp __deprecated_msg("Use [RCChannelClient clearMessagesUnreadStatus:targetId:channelId:time:completion:] instead");

#pragma mark - 会话的消息提醒 -

/*!
 设置会话的消息提醒状态
 
 @param conversationType            会话类型
 @param targetId                    会话 ID
 @param channelId          所属会话的业务标识
 @param isBlocked                   是否屏蔽消息提醒
 @param successBlock                设置成功的回调
 [nStatus:会话设置的消息提醒状态]
 @param errorBlock                  设置失败的回调 [status:设置失败的错误码]
 
 @discussion
 如果您使用
 IMLibCore，此方法会屏蔽该会话的远程推送；如果您使用IMKit，此方法会屏蔽该会话的所有提醒（远程推送、本地通知、前台提示音）,该接口不支持聊天室。
 
 @remarks 会话
 @since 5.1.1
 */
- (void)setConversationNotificationStatus:(RCConversationType)conversationType
                                 targetId:(NSString *)targetId
                                channelId:(nullable NSString *)channelId
                                isBlocked:(BOOL)isBlocked
                                  success:(nullable void (^)(RCConversationNotificationStatus nStatus))successBlock
                                    error:(nullable void (^)(RCErrorCode status))errorBlock __deprecated_msg("Use [RCChannelClient setConversationChannelNotificationLevel:targetId:channelId:level:success:error:] instead");

/*!
 获取消息免打扰会话列表
 @param conversationTypeList 会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 @param channelId          所属会话的业务标识
 @return                     消息免打扰会话 RCConversation 的列表
 
 @discussion 此方法会从本地数据库中，读取消息免打扰会话列表。
 
 @remarks 会话列表
 @since 5.1.1
 */
- (nullable NSArray<RCConversation *> *)getBlockedConversationList:(NSArray<NSNumber *> *)conversationTypeList channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getBlockedConversationList:channelId:completion:] instead");

#pragma mark - 搜索 -

/*!
 根据关键字搜索指定会话中的消息
 
 @param conversationType 会话类型
 @param targetId         会话 ID
 @param channelId          所属会话的业务标识
 @param keyword          关键字
 @param count            最大的查询数量
 @param startTime        查询 startTime 之前的消息（传 0 表示不限时间）
 
 @return 匹配的消息列表
 
 @discussion 此方法不支持超级群的会话类型。
 
 @remarks 消息操作
 @since 5.1.1
 */
- (nullable NSArray<RCMessage *> *)searchMessages:(RCConversationType)conversationType
                                         targetId:(NSString *)targetId
                                        channelId:(nullable NSString *)channelId
                                          keyword:(NSString *)keyword
                                            count:(int)count
                                        startTime:(long long)startTime __deprecated_msg("Use [RCChannelClient searchMessages:targetId:channelId:keyword:count:startTime:completion:] instead");

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
                                        channelId:(nullable NSString *)channelId
                                          keyword:(nullable NSString *)keyword
                                        startTime:(long long)startTime
                                          endTime:(long long)endTime
                                           offset:(int)offset
                                            limit:(int)limit __deprecated_msg("Use [RCChannelClient searchMessages:targetId:channelId:keyword:startTime:endTime:offset:limit:completion:] instead");

/*!
 按用户 ID 搜索指定会话中的消息
 
 @param conversationType 会话类型
 @param targetId         会话 ID
 @param channelId          所属会话的业务标识
 @param userId           搜索用户 ID
 @param count            最大的查询数量
 @param startTime        查询 startTime 之前的消息（传 0 表示不限时间）
 
 @return 匹配的消息列表
 
 @discussion 超级群会话类型只支持搜索已存储到本地的消息。
 
 @remarks 消息操作
 @since 5.1.1
 */
- (nullable NSArray<RCMessage *> *)searchMessages:(RCConversationType)conversationType
                                         targetId:(NSString *)targetId
                                        channelId:(nullable NSString *)channelId
                                           userId:(NSString *)userId
                                            count:(int)count
                                        startTime:(long long)startTime __deprecated_msg("Use [RCChannelClient searchMessages:targetId:channelId:userId:count:startTime:completion:] instead");

/*!
 搜索指定会话中所有 channelId 的消息
 
 @param conversationType 会话类型
 @param targetId         会话 ID
 @param keyword           关键字，非空
 @param count            最大的查询数量
 @param startTime        查询 startTime 之前的消息（传 0 表示不限时间）
 
 @return 匹配的消息列表
 
 @discussion 超级群会话类型只支持搜索已存储到本地的消息。
 
 @remarks 消息操作
 @since 5.2.3
 */
- (nullable NSArray<RCMessage *> *)searchMessagesForAllChannel:(RCConversationType)conversationType
                                                      targetId:(NSString *)targetId
                                                       keyword:(NSString *)keyword
                                                         count:(int)count
                                                     startTime:(long long)startTime __deprecated_msg("Use [RCChannelClient searchMessagesForAllChannel:targetId:keyword:count:startTime:completion:] instead");

/*!
 分页搜索指定会话中所有 channelId 在指定时间范围内的消息
 
 @param conversationType 会话类型
 @param targetId         会话 ID
 @param keyword           关键字，非空
 @param startTime        开始时间（传 0 表示不限时间）
 @param endTime       结束时间，可传入当前 unix 时间，精确到毫秒
 @param offset            偏移量，默认填 0
 @param limit            最大的查询数量
 
 @return 匹配的消息列表
 
 @discussion 超级群会话类型只支持搜索已存储到本地的消息。
 
 @remarks 消息操作
 @since 5.2.3
 */
- (nullable NSArray<RCMessage *> *)searchMessagesForAllChannel:(RCConversationType)conversationType
                                                      targetId:(NSString *)targetId
                                                       keyword:(NSString *)keyword
                                                     startTime:(long long)startTime
                                                       endTime:(long long)endTime
                                                        offset:(int)offset
                                                         limit:(int)limit __deprecated_msg("Use [RCChannelClient searchMessagesForAllChannel:targetId:keyword:startTime:endTime:offset:limit:completion:] instead");

/*!
 根据关键字搜索会话
 
 @param conversationTypeList 需要搜索的会话类型列表
 @param channelId          所属会话的业务标识
 @param objectNameList       需要搜索的消息类型名列表(即每个消息类方法 getObjectName 的返回值)
 @param keyword              关键字
 
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
 @since 5.2.3
 */
- (nullable NSArray<RCSearchConversationResult *> *)searchConversations:(NSArray<NSNumber *> *)conversationTypeList
                                                              channelId:(nullable NSString *)channelId
                                                            messageType:(NSArray<NSString *> *)objectNameList
                                                                keyword:(NSString *)keyword __deprecated_msg("Use [RCChannelClient searchConversations:targetId:messageType:keyword:completion:] instead");

/*!
 根据关键字搜索特定会话类型下所有 channelId 的会话
 
 @param conversationTypeList 需要搜索的会话类型列表
 @param objectNameList       需要搜索的消息类型名列表(即每个消息类方法 getObjectName 的返回值)，不能为 nil
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
 @since 5.2.3
 */
- (nullable NSArray<RCSearchConversationResult *> *)searchConversationsForAllChannel:(NSArray<NSNumber *> *)conversationTypeList
                                                                         messageType:(NSArray<NSString *> *)objectNameList
                                                                             keyword:(NSString *)keyword __deprecated_msg("Use [RCChannelClient searchConversationsForAllChannel:messageType:keyword:completion:] instead");

@end

NS_ASSUME_NONNULL_END
