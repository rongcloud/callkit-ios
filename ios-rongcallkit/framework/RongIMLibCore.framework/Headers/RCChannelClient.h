//
//  RCChannelClient.h
//  RongIMLibCore
//
//  Created by 张改红 on 2021/1/29.
//  Copyright © 2021 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RCConversation.h"
#import "RCMessage.h"
#import "RCSearchConversationResult.h"
#import "RCStatusDefine.h"
#import "RCUploadMediaStatusListener.h"
#import "RCUserInfo.h"
#import "RCSendMessageOption.h"
#import "RCRemoteHistoryMsgOption.h"
#import "RCConversationChannelProtocol.h"
#import "RCHistoryMessageOption.h"
#import "RCConversationIdentifier.h"
#import "RCIMClientProtocol.h"
#import "RCMessageDigestInfo.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 融云 ConversationChannel 核心类
 
 @discussion 您需要通过 sharedCoreClient 方法，获取单例对象。
 */
@interface RCChannelClient : NSObject

/*!
 获取核心类单例

 @return 核心单例类
 */
+ (instancetype)sharedChannelManager;

#pragma mark 代理
/*!
 设置消息接收监听器

 @param delegate    RCChannelClient 消息已读回执监听器

 @discussion
 设置 IMLibCore 的消息接收监听器请参考 RCChannelClient 的 setChannelMessageReceiptDelegate:object:方法。

 @remarks 功能设置
 */
- (void)setChannelMessageReceiptDelegate:(id<RCConversationChannelMessageReceiptDelegate>)delegate;


/*!
 设置输入状态的监听器

 @param delegate         RCChannelClient 输入状态的的监听器

 @warning           目前仅支持单聊。

 @remarks 功能设置
 */
- (void)setRCConversationChannelTypingStatusDelegate:(id<RCConversationChannelTypingStatusDelegate>)delegate;

/*!
 设置超级群输入状态的监听器

 @param delegate         RCChannelClient 输入状态的的监听器

 @discussion 此方法只支持超级群的会话类型。
 @remarks 超级群
 */
- (void)setRCUltraGroupTypingStatusDelegate:(id<RCUltraGroupTypingStatusDelegate>)delegate;

/*!
 设置超级群已读时间回调监听器

 @param delegate    超级群已读时间回调监听器
 
 @discussion 此方法只支持超级群的会话类型。
 @remarks 超级群
 */
- (void)setRCUltraGroupReadTimeDelegate:(id<RCUltraGroupReadTimeDelegate>)delegate;

/*!
 设置超级群消息处理监听器

 @param delegate    超级群消息处理回调监听器
 
 @discussion 此方法只支持超级群的会话类型。
 @remarks 超级群
 */
- (void)setRCUltraGroupMessageChangeDelegate:(id<RCUltraGroupMessageChangeDelegate>)delegate;

#pragma mark 消息发送

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
 异步发送消息

 @param conversationType    发送消息的会话类型
 @param targetId            发送消息的会话 ID
 @param channelId          所属会话的业务标识
 @param content             消息的内容
 @param pushContent         接收方离线时需要显示的远程推送内容
 @param pushData            接收方离线时需要在远程推送中携带的非显示数据
 @param attachedBlock          入库回调[message: 已存数据库的消息体]
 @param successBlock        消息发送成功的回调 [messageId: 消息的 ID]
 @param errorBlock          消息发送失败的回调 [nErrorCode: 发送失败的错误码,
 messageId:消息的ID]

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
 @since 5.3.0
 */
- (void)sendMessage:(RCConversationType)conversationType
           targetId:(NSString *)targetId
          channelId:(nullable NSString *)channelId
            content:(RCMessageContent *)content
        pushContent:(nullable NSString *)pushContent
           pushData:(nullable NSString *)pushData
           attached:(nullable void(^)(RCMessage * _Nullable message))attachedBlock
            success:(nullable void (^)(long messageId))successBlock
              error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock;
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
 异步发送消息

 @param conversationType    发送消息的会话类型
 @param targetId            发送消息的会话 ID
 @param channelId          所属会话的业务标识
 @param content             消息的内容
 @param pushContent         接收方离线时需要显示的远程推送内容
 @param pushData            接收方离线时需要在远程推送中携带的非显示数据
 @param option              消息的相关配置
 @param attachedBlock          入库回调[message: 已存数据库的消息体]
 @param successBlock        消息发送成功的回调 [messageId: 消息的 ID]
 @param errorBlock          消息发送失败的回调 [nErrorCode: 发送失败的错误码,
 messageId: 消息的 ID]

 
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
 @since 5.3.0
 */
- (void)sendMessage:(RCConversationType)conversationType
           targetId:(NSString *)targetId
          channelId:(nullable NSString *)channelId
            content:(RCMessageContent *)content
        pushContent:(nullable NSString *)pushContent
           pushData:(nullable NSString *)pushData
             option:(RCSendMessageOption *)option
           attached:(nullable void(^)(RCMessage * _Nullable message))attachedBlock
            success:(nullable void (^)(long messageId))successBlock
              error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock;
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
 异步发送媒体消息（图片消息或文件消息）

 @param conversationType    发送消息的会话类型
 @param targetId            发送消息的会话 ID
 @param channelId          所属会话的业务标识
 @param content             消息的内容
 @param pushContent         接收方离线时需要显示的远程推送内容
 @param pushData            接收方离线时需要在远程推送中携带的非显示数据
 @param attachedBlock          入库回调[message: 已存数据库的消息体]
 @param progressBlock       消息发送进度更新的回调 [progress:当前的发送进度, 0
 <= progress <= 100, messageId:消息的 ID]
 @param successBlock        消息发送成功的回调 [messageId:消息的 ID]
 @param errorBlock          消息发送失败的回调 [errorCode:发送失败的错误码,
 messageId:消息的 ID]
 @param cancelBlock         用户取消了消息发送的回调 [messageId:消息的 ID]
 
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
 @since 5.3.0
 */
- (void)sendMediaMessage:(RCConversationType)conversationType
                targetId:(NSString *)targetId
               channelId:(nullable NSString *)channelId
                 content:(RCMessageContent *)content
             pushContent:(nullable NSString *)pushContent
                pushData:(nullable NSString *)pushData
                attached:(nullable void(^)(RCMessage * _Nullable message))attachedBlock
                progress:(nullable void (^)(int progress, long messageId))progressBlock
                 success:(nullable void (^)(long messageId))successBlock
                   error:(nullable void (^)(RCErrorCode errorCode, long messageId))errorBlock
                  cancel:(nullable void (^)(long messageId))cancelBlock;
/*!
 发送媒体消息(上传图片或文件等媒体信息到指定的服务器)

 @param conversationType    发送消息的会话类型
 @param targetId            发送消息的会话 ID
 @param channelId          所属会话的业务标识
 @param content             消息的内容
 @param pushContent         接收方离线时需要显示的远程推送内容
 @param pushData            接收方离线时需要在远程推送中携带的非显示数据
 @param uploadPrepareBlock  媒体文件上传进度更新的 IMKit 监听
 [uploadListener:当前的发送进度监听，SDK 通过此监听更新 IMKit UI]
 @param progressBlock       消息发送进度更新的回调 [progress:当前的发送进度, 0
 <= progress <= 100, messageId:消息的ID]
 @param successBlock        消息发送成功的回调 [messageId:消息的 ID]
 @param errorBlock          消息发送失败的回调 [errorCode:发送失败的错误码,
 messageId:消息的 ID]
 @param cancelBlock         用户取消了消息发送的回调 [messageId:消息的 ID]
 @return                    发送的消息实体

 @discussion 此方法仅用于 IMKit。
 如果您需要上传图片到自己的服务器并使用 IMLibCore，构建一个 RCImageMessage 对象，
 并将 RCImageMessage 中的 imageUrl 字段设置为上传成功的 URL 地址，然后使用 RCCoreClient 的
 sendMessage:targetId:content:pushContent:pushData:success:error:方法
 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。

 如果您需要上传文件到自己的服务器并使用 IMLibCore，构建一个 RCFileMessage 对象，
 并将 RCFileMessage 中的 fileUrl 字段设置为上传成功的 URL 地址，然后使用 RCCoreClient 的
 sendMessage:targetId:content:pushContent:pushData:success:error:方法
 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。

 @remarks 消息操作
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
 异步发送媒体消息(上传图片或文件等媒体信息到指定的服务器)

 @param conversationType    发送消息的会话类型
 @param targetId            发送消息的会话 ID
 @param channelId          所属会话的业务标识
 @param content             消息的内容
 @param pushContent         接收方离线时需要显示的远程推送内容
 @param pushData            接收方离线时需要在远程推送中携带的非显示数据
 @param attachedBlock          入库回调[message: 已存数据库的消息体]
 @param uploadPrepareBlock  媒体文件上传进度更新的 IMKit 监听
 [uploadListener:当前的发送进度监听，SDK 通过此监听更新 IMKit UI]
 @param progressBlock       消息发送进度更新的回调 [progress:当前的发送进度, 0
 <= progress <= 100, messageId:消息的ID]
 @param successBlock        消息发送成功的回调 [messageId:消息的 ID]
 @param errorBlock          消息发送失败的回调 [errorCode:发送失败的错误码,
 messageId:消息的 ID]
 @param cancelBlock         用户取消了消息发送的回调 [messageId:消息的 ID]

 @discussion 此方法仅用于 IMKit。
 如果您需要上传图片到自己的服务器并使用 IMLibCore，构建一个 RCImageMessage 对象，
 并将 RCImageMessage 中的 imageUrl 字段设置为上传成功的 URL 地址，然后使用 RCCoreClient 的
 sendMessage:targetId:content:pushContent:pushData:success:error:方法
 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。

 如果您需要上传文件到自己的服务器并使用 IMLibCore，构建一个 RCFileMessage 对象，
 并将 RCFileMessage 中的 fileUrl 字段设置为上传成功的 URL 地址，然后使用 RCCoreClient 的
 sendMessage:targetId:content:pushContent:pushData:success:error:方法
 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。

 @remarks 消息操作
 @since 5.3.0
 */
- (void)sendMediaMessage:(RCConversationType)conversationType
                targetId:(NSString *)targetId
               channelId:(nullable NSString *)channelId
                 content:(RCMessageContent *)content
             pushContent:(nullable NSString *)pushContent
                pushData:(nullable NSString *)pushData
                attached:(nullable void(^)(RCMessage * _Nullable message))attachedBlock
           uploadPrepare:(nullable void (^)(RCUploadMediaStatusListener *uploadListener))uploadPrepareBlock
                progress:(nullable void (^)(int progress, long messageId))progressBlock
                 success:(nullable void (^)(long messageId))successBlock
                   error:(nullable void (^)(RCErrorCode errorCode, long messageId))errorBlock
                  cancel:(nullable void (^)(long messageId))cancelBlock;


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
 */
- (nullable RCMessage *)insertOutgoingMessage:(RCConversationType)conversationType
                            targetId:(NSString *)targetId
                           channelId:(nullable NSString *)channelId
                          sentStatus:(RCSentStatus)sentStatus
                             content:(RCMessageContent *)content
                            sentTime:(long long)sentTime __deprecated_msg("Use [RCChannelClient insertOutgoingMessage:targetId:channelId:sentStatus:content:sentTime:completion:] instead");

/*!
 异步插入向外发送的、指定时间的消息（此方法如果 sentTime 有问题会影响消息排序，慎用！！）
（该消息只插入本地数据库，实际不会发送给服务器和对方）

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param sentStatus          发送状态
 @param content             消息的内容
 @param sentTime            消息发送的 Unix 时间戳，单位为毫秒（传 0 会按照本地时间插入）
 @param completion          异步回调[发送的消息实体]

 @discussion 此方法不支持聊天室的会话类型。如果 sentTime<=0，则被忽略，会以插入时的时间为准。

 @remarks 消息操作
 */
- (void)insertOutgoingMessage:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                    channelId:(nullable NSString *)channelId
                   sentStatus:(RCSentStatus)sentStatus
                      content:(RCMessageContent *)content
                     sentTime:(long long)sentTime
                   completion:(nullable void(^)(RCMessage * _Nullable message))completion;

/*!
 异步插入向外发送的、指定时间的消息（此方法如果 sentTime 有问题会影响消息排序，慎用！！）
（该消息只插入本地数据库，实际不会发送给服务器和对方）

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param canIncludeExpansion 是否支持扩展
 @param sentStatus          发送状态
 @param content             消息的内容
 @param sentTime            消息发送的 Unix 时间戳，单位为毫秒（传 0 会按照本地时间插入）
 @param completion          异步回调[发送的消息实体]

 @discussion 此方法不支持聊天室的会话类型。如果 sentTime<=0，则被忽略，会以插入时的时间为准。

 @remarks 消息操作
 @since 5.3.1
 */
- (void)insertOutgoingMessage:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                    channelId:(nullable NSString *)channelId
          canIncludeExpansion:(BOOL)canIncludeExpansion
                   sentStatus:(RCSentStatus)sentStatus
                      content:(RCMessageContent *)content
                     sentTime:(long long)sentTime
                   completion:(nullable void(^)(RCMessage * _Nullable message))completion;

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
 */
- (nullable RCMessage *)insertIncomingMessage:(RCConversationType)conversationType
                            targetId:(NSString *)targetId
                           channelId:(nullable NSString *)channelId
                        senderUserId:(NSString *)senderUserId
                      receivedStatus:(RCReceivedStatus)receivedStatus
                             content:(RCMessageContent *)content
                            sentTime:(long long)sentTime __deprecated_msg("Use [RCChannelClient insertIncomingMessage:targetId:channelId:senderUserId:receivedStatus:content:sentTime:completion:] instead");

/*!
 异步插入接收的消息（此方法如果 sentTime
 有问题会影响消息排序，慎用！！）（该消息只插入本地数据库，实际不会发送给服务器和对方）

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param senderUserId        发送者 ID
 @param receivedStatus      接收状态
 @param content             消息的内容
 @param sentTime            消息发送的 Unix 时间戳，单位为毫秒 （传 0 会按照本地时间插入）
 @param completion          异步回调[插入的消息实体]
 
 @discussion 此方法不支持聊天室的会话类型。

 @remarks 消息操作
 */
- (void)insertIncomingMessage:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                    channelId:(nullable NSString *)channelId
                 senderUserId:(NSString *)senderUserId
               receivedStatus:(RCReceivedStatus)receivedStatus
                      content:(RCMessageContent *)content
                     sentTime:(long long)sentTime
                   completion:(nullable void(^)(RCMessage * _Nullable message))completion;

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
 @param errorBlock       消息发送失败的回调 [errorCode:发送失败的错误码,
 messageId:消息的 ID]

 @return 发送的消息实体

 @discussion 此方法用于在群组和讨论组中发送消息给其中的部分用户，其它用户不会收到这条消息。
 如果您使用 IMLibCore，可以使用此方法发送定向消息；
 如果您使用 IMKit，请使用 RCIM 中的同名方法发送定向消息，否则不会自动更新 UI。
 @discussion userIdList里ID个数不能超过300，超过会被截断。

 @warning 此方法目前仅支持普通群组和讨论组。

 @remarks 消息操作
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
 异步发送定向消息

 @param conversationType 发送消息的会话类型
 @param targetId         发送消息的会话 ID
 @param channelId          所属会话的业务标识
 @param userIdList       接收消息的用户 ID 列表
 @param content          消息的内容
 @param pushContent      接收方离线时需要显示的远程推送内容
 @param pushData         接收方离线时需要在远程推送中携带的非显示数据
 @param attachedBlock          入库回调[message: 已存数据库的消息体]
 @param successBlock     消息发送成功的回调 [messageId:消息的 ID]
 @param errorBlock       消息发送失败的回调 [errorCode:发送失败的错误码,
 messageId:消息的 ID]

 @discussion 此方法用于在群组和讨论组中发送消息给其中的部分用户，其它用户不会收到这条消息。
 如果您使用 IMLibCore，可以使用此方法发送定向消息；
 如果您使用 IMKit，请使用 RCIM 中的同名方法发送定向消息，否则不会自动更新 UI。
 @discussion userIdList里ID个数不能超过300，超过会被截断。

 @warning 此方法目前仅支持普通群组和讨论组。

 @remarks 消息操作
 @since 5.3.0
 */
- (void)sendDirectionalMessage:(RCConversationType)conversationType
                      targetId:(NSString *)targetId
                     channelId:(nullable NSString *)channelId
                  toUserIdList:(NSArray<NSString *> *)userIdList
                       content:(RCMessageContent *)content
                   pushContent:(nullable NSString *)pushContent
                      pushData:(nullable NSString *)pushData
                      attached:(nullable void(^)(RCMessage * _Nullable message))attachedBlock
                       success:(nullable void (^)(long messageId))successBlock
                         error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock;
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

/*!
 异步发送定向消息

 @param conversationType 发送消息的会话类型
 @param targetId         发送消息的会话 ID
 @param channelId          所属会话的业务标识
 @param userIdList       接收消息的用户 ID 列表
 @param content          消息的内容
 @param pushContent      接收方离线时需要显示的远程推送内容
 @param pushData         接收方离线时需要在远程推送中携带的非显示数据
 @param option              消息的相关配置
 @param attachedBlock          入库回调[message: 已存数据库的消息体]
 @param successBlock     消息发送成功的回调 [messageId:消息的 ID]
 @param errorBlock       消息发送失败的回调 [errorCode:发送失败的错误码,
 messageId:消息的 ID]
 
 @discussion 此方法用于在群组和讨论组中发送消息给其中的部分用户，其它用户不会收到这条消息。
 如果您使用 IMLibCore，可以使用此方法发送定向消息；
 如果您使用 IMKit，请使用 RCIM 中的同名方法发送定向消息，否则不会自动更新 UI。
 userIdList里ID个数不能超过300，超过会被截断。

 @warning 此方法目前仅支持普通群组和讨论组。

 @remarks 消息操作
 @since 5.3.0
 */
- (void)sendDirectionalMessage:(RCConversationType)conversationType
                      targetId:(NSString *)targetId
                     channelId:(nullable NSString *)channelId
                  toUserIdList:(NSArray<NSString *> *)userIdList
                       content:(RCMessageContent *)content
                   pushContent:(nullable NSString *)pushContent
                      pushData:(nullable NSString *)pushData
                        option:(RCSendMessageOption *)option
                      attached:(nullable void(^)(RCMessage * _Nullable message))attachedBlock
                       success:(nullable void (^)(long messageId))successBlock
                         error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock;
#pragma mark 消息阅读回执

/*!
 发送某个会话中消息阅读的回执

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param timestamp           该会话中已阅读的最后一条消息的发送时间戳
 @param successBlock        发送成功的回调
 @param errorBlock          发送失败的回调[nErrorCode: 失败的错误码]

 @discussion 此接口只支持单聊, 如果使用 IMLibCore 可以注册监听
 RCLibDispatchReadReceiptNotification 通知,使用 IMKit 直接设置RCIM.h
 中的 enabledReadReceiptConversationTypeList。

 @warning 目前仅支持单聊。

 @remarks 高级功能
 */
- (void)sendReadReceiptMessage:(RCConversationType)conversationType
                      targetId:(NSString *)targetId
                     channelId:(nullable NSString *)channelId
                          time:(long long)timestamp
                       success:(nullable void (^)(void))successBlock
                         error:(nullable void (^)(RCErrorCode nErrorCode))errorBlock;

/*!
 发送阅读回执

 @param conversationType 会话类型
 @param targetId         会话 ID
 @param channelId          所属会话的业务标识
 @param messageList      已经阅读了的消息列表
 @param successBlock     发送成功的回调
 @param errorBlock       发送失败的回调[nErrorCode: 失败的错误码]

 @discussion 当用户阅读了需要阅读回执的消息，可以通过此接口发送阅读回执，消息的发送方即可直接知道那些人已经阅读。

 @remarks 高级功能
 */
- (void)sendReadReceiptResponse:(RCConversationType)conversationType
                       targetId:(NSString *)targetId
                      channelId:(nullable NSString *)channelId
                    messageList:(NSArray<RCMessage *> *)messageList
                        success:(nullable void (^)(void))successBlock
                          error:(nullable void (^)(RCErrorCode nErrorCode))errorBlock;

/*!
 同步会话阅读状态（把指定会话里所有发送时间早于 timestamp 的消息置为已读）

 @param conversationType 会话类型
 @param targetId         会话 ID
 @param channelId          所属会话的业务标识
 @param timestamp        已经阅读的最后一条消息的 Unix 时间戳(毫秒)
 @param successBlock     同步成功的回调
 @param errorBlock       同步失败的回调[nErrorCode: 失败的错误码]

 @discussion 此方法不支持超级群的会话类型。
 
 @remarks 高级功能
 */
- (void)syncConversationReadStatus:(RCConversationType)conversationType
                          targetId:(NSString *)targetId
                         channelId:(nullable NSString *)channelId
                              time:(long long)timestamp
                           success:(nullable void (^)(void))successBlock
                             error:(nullable void (^)(RCErrorCode nErrorCode))errorBlock;

/*!
 上报超级群的已读时间
 
 @param targetId   会话 ID
 @param channelId  所属会话的业务标识
 @param timestamp 已读时间，传入最后一条消息的 sentTime
 @param successBlock 成功的回调
 @param errorBlock 失败的回调
 
 @discussion 此方法只支持超级群的会话类型。
 @remarks 超级群
 */
- (void)syncUltraGroupReadStatus:(NSString *)targetId
                       channelId:(nullable NSString *)channelId
                            time:(long long)timestamp
                         success:(nullable void (^)(void))successBlock
                           error:(nullable void (^)(RCErrorCode errorCode))errorBlock;
#pragma mark - 消息操作

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
 */
- (nullable NSArray<RCMessage *> *)getLatestMessages:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId count:(int)count __deprecated_msg("Use [RCChannelClient getLatestMessages:targetId:channelId:count:completion:] instead");
/*!
 异步获取某个会话中指定数量的最新消息实体

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param count               需要获取的消息数量
 @param completion          异步回调[消息实体 RCMessage 对象列表]
 
 @discussion
 此方法会获取该会话中指定数量的最新消息实体，返回的消息实体按照时间从新到旧排列。
 如果会话中的消息数量小于参数 count 的值，会将该会话中的所有消息返回。

 @remarks 消息操作
 */
- (void)getLatestMessages:(RCConversationType)conversationType
                 targetId:(NSString *)targetId
                channelId:(nullable NSString *)channelId
                    count:(int)count
               completion:(nullable void(^)(NSArray<RCMessage *> * _Nullable messages))completion;
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
 */
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                    targetId:(NSString *)targetId
                                   channelId:(nullable NSString *)channelId
                             oldestMessageId:(long)oldestMessageId
                                       count:(int)count __deprecated_msg("Use [RCChannelClient getHistoryMessages:targetId:channelId:oldestMessageId:count:completion:] instead");

/*!
 异步获取会话中，从指定消息之前、指定数量的最新消息实体

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param oldestMessageId     截止的消息 ID [0或-1 代表从最近的发送时间查起]
 @param count               需要获取的消息数量
 @param completion          异步回调[消息实体 RCMessage 对象列表]
 
 @discussion
 此方法会获取该会话中，oldestMessageId 之前的、指定数量的最新消息实体，返回的消息实体按照时间从新到旧排列。
 返回的消息中不包含 oldestMessageId 对应那条消息，如果会话中的消息数量小于参数 count 的值，会将该会话中的所有消息返回。
 如：
 oldestMessageId 为 10，count 为 2，会返回 messageId 为 9 和 8 的 RCMessage 对象列表。

 @discussion 此方法不支持超级群的会话类型。
 
 @remarks 消息操作
 */
- (void)getHistoryMessages:(RCConversationType)conversationType
                  targetId:(NSString *)targetId
                 channelId:(nullable NSString *)channelId
           oldestMessageId:(long)oldestMessageId
                     count:(int)count
                completion:(nullable void(^)(NSArray<RCMessage *> * _Nullable messages))completion;

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
 */
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                    targetId:(NSString *)targetId
                                   channelId:(nullable NSString *)channelId
                                  objectName:(nullable NSString *)objectName
                             oldestMessageId:(long)oldestMessageId
                                       count:(int)count __deprecated_msg("Use [RCChannelClient getHistoryMessages:targetId:channelId:objectName:oldestMessageId:count:completion:] instead");
/*!
 异步获取会话中，从指定消息之前、指定数量的、指定消息类型的最新消息实体

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param objectName          消息内容的类型名，如果想取全部类型的消息请传 nil
 @param oldestMessageId     截止的消息 ID [0或-1 代表从最近的发送时间查起]
 @param count               需要获取的消息数量
 @param completion          异步回调[消息实体 RCMessage 对象列表]
 
 @discussion
 此方法会获取该会话中，oldestMessageId 之前的、指定数量和消息类型的最新消息实体，返回的消息实体按照时间从新到旧排列。
 返回的消息中不包含 oldestMessageId 对应的那条消息，如果会话中的消息数量小于参数 count
 的值，会将该会话中的所有消息返回。
 如：oldestMessageId 为 10，count 为 2，会返回 messageId 为 9 和 8 的 RCMessage 对象列表。

 @discussion 此方法不支持超级群的会话类型。
 
 @remarks 消息操作
 */
- (void)getHistoryMessages:(RCConversationType)conversationType
                  targetId:(NSString *)targetId
                 channelId:(nullable NSString *)channelId
                objectName:(nullable NSString *)objectName
           oldestMessageId:(long)oldestMessageId
                     count:(int)count
                completion:(nullable void(^)(NSArray<RCMessage *> * _Nullable messages))completion;
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
 */
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                    targetId:(NSString *)targetId
                                   channelId:(nullable NSString *)channelId
                                  objectName:(nullable NSString *)objectName
                               baseMessageId:(long)baseMessageId
                                   isForward:(BOOL)isForward
                                       count:(int)count __deprecated_msg("Use [RCChannelClient getHistoryMessages:targetId:channelId:objectName:baseMessageId:isForward:count:completion:] instead");
/*!
 异步获取会话中，指定消息、指定数量、指定消息类型、向前或向后查找的消息实体列表

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param objectName          消息内容的类型名，如果想取全部类型的消息请传 nil
 @param baseMessageId       当前的消息 ID [0或-1 代表从最近的发送时间查起]
 @param isForward           查询方向 true 为向前，false 为向后
 @param count               需要获取的消息数量
 @param completion          异步回调[消息实体 RCMessage 对象列表]
 
 @discussion
 此方法会获取该会话中，baseMessageId
 之前或之后的、指定数量、消息类型和查询方向的最新消息实体，返回的消息实体按照时间从新到旧排列。
 返回的消息中不包含 baseMessageId 对应的那条消息，如果会话中的消息数量小于参数 count 的值，会将该会话中的所有消息返回。

 @discussion 超级群不会接收离线消息，超级群调用该接口会出现消息断档的情况，请使用断档消息接口获取超级群消息。
 
 @remarks 消息操作
 */
- (void)getHistoryMessages:(RCConversationType)conversationType
                  targetId:(NSString *)targetId
                 channelId:(nullable NSString *)channelId
                objectName:(nullable NSString *)objectName
             baseMessageId:(long)baseMessageId
                 isForward:(BOOL)isForward
                     count:(int)count
                completion:(nullable void(^)(NSArray<RCMessage *> * _Nullable messages))completion;
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
 */
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                    targetId:(NSString *)targetId
                                   channelId:(nullable NSString *)channelId
                                 objectNames:(NSArray<NSString *> *)objectNames
                                    sentTime:(long long)sentTime
                                   isForward:(BOOL)isForward
                                                count:(int)count  __deprecated_msg("Use [RCChannelClient getHistoryMessages:targetId:channelId:objectName:sentTime:isForward:count:completion:] instead");
/*!
 异步获取会话中，指定时间、指定数量、指定消息类型（多个）、向前或向后查找的消息实体列表

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param objectNames         消息内容的类型名称列表
 @param sentTime            当前的消息时间戳
 @param isForward           查询方向 true 为向前，false 为向后
 @param count               需要获取的消息数量
 @param completion          异步回调[消息实体 RCMessage 对象列表]
 
 @discussion
 此方法会获取该会话中，sentTime
 之前或之后的、指定数量、指定消息类型（多个）的消息实体列表，返回的消息实体按照时间从新到旧排列。
 返回的消息中不包含 sentTime 对应的那条消息，如果会话中的消息数量小于参数 count 的值，会将该会话中的所有消息返回。

 @discussion 超级群不会接收离线消息，超级群调用该接口会出现消息断档的情况，请使用断档消息接口获取超级群消息。
 
 @remarks 消息操作
 */
- (void)getHistoryMessages:(RCConversationType)conversationType
                  targetId:(NSString *)targetId
                 channelId:(nullable NSString *)channelId
               objectNames:(NSArray<NSString *> *)objectNames
                  sentTime:(long long)sentTime
                 isForward:(BOOL)isForward
                     count:(int)count
                completion:(nullable void(^)(NSArray<RCMessage *> * _Nullable messages))completion;
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
 */
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                    targetId:(NSString *)targetId
                                   channelId:(nullable NSString *)channelId
                                    sentTime:(long long)sentTime
                                 beforeCount:(int)beforeCount
                                           afterCount:(int)afterCount __deprecated_msg("Use [RCChannelClient getHistoryMessages:targetId:channelId:sentTime:beforeCount:afterCount:completion:] instead");;
/*!
 在会话中异步搜索指定消息的前 beforeCount 数量和后 afterCount
 数量的消息。返回的消息列表中会包含指定的消息。消息列表时间顺序从新到旧。

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param sentTime            消息的发送时间
 @param beforeCount         指定消息的前部分消息数量
 @param afterCount          指定消息的后部分消息数量
 @param completion          异步回调[消息实体 RCMessage 对象列表]
 
 @discussion
 获取该会话的这条消息及这条消息前 beforeCount 条和后 afterCount 条消息,如前后消息不够则返回实际数量的消息。

 @discussion 此方法不支持超级群的会话类型。
 
 @remarks 消息操作
 */
- (void)getHistoryMessages:(RCConversationType)conversationType
                  targetId:(NSString *)targetId
                 channelId:(nullable NSString *)channelId
                  sentTime:(long long)sentTime
               beforeCount:(int)beforeCount
                afterCount:(int)afterCount
                completion:(nullable void(^)(NSArray<RCMessage *> * _Nullable messages))completion;
/*!
 从服务器端清除历史消息

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param recordTime          清除消息时间戳，【0 <= recordTime <= 当前会话最后一条消息的 sentTime,0
 清除所有消息，其他值清除小于等于 recordTime 的消息】
 @param successBlock        获取成功的回调
 @param errorBlock          获取失败的回调 [status:清除失败的错误码]

 @discussion
 此方法从服务器端清除历史消息，但是必须先开通历史消息云存储功能。
 例如，您不想从服务器上获取更多的历史消息，通过指定 recordTime 清除成功后只能获取该时间戳之后的历史消息。

 @remarks 消息操作
 */
- (void)clearRemoteHistoryMessages:(RCConversationType)conversationType
                          targetId:(NSString *)targetId
                         channelId:(nullable NSString *)channelId
                        recordTime:(long long)recordTime
                           success:(nullable void (^)(void))successBlock
                             error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 清除历史消息

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param recordTime          清除消息时间戳，【0 <= recordTime <= 当前会话最后一条消息的 sentTime,0
 清除所有消息，其他值清除小于等于 recordTime 的消息】
 @param clearRemote         是否同时删除服务端消息
 @param successBlock        获取成功的回调
 @param errorBlock          获取失败的回调 [ status:清除失败的错误码]

 @discussion
 此方法可以清除服务器端历史消息和本地消息，如果清除服务器端消息必须先开通历史消息云存储功能。
 例如，您不想从服务器上获取更多的历史消息，通过指定 recordTime 并设置 clearRemote 为 YES
 清除消息，成功后只能获取该时间戳之后的历史消息。如果 clearRemote 传 NO，
 只会清除本地消息。

 @remarks 消息操作
 */
- (void)clearHistoryMessages:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
                   channelId:(nullable NSString *)channelId
                  recordTime:(long long)recordTime
                 clearRemote:(BOOL)clearRemote
                     success:(nullable void (^)(void))successBlock
                       error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 从服务器端获取之前的历史消息

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param recordTime          截止的消息发送时间戳，毫秒
 @param count               需要获取的消息数量， 0 < count <= 20
 @param successBlock        获取成功的回调 [messages:获取到的历史消息数组, isRemaining 是否还有剩余消息 YES
 表示还有剩余，NO 表示无剩余]
 @param errorBlock          获取失败的回调 [status:获取失败的错误码]

 @discussion
 此方法从服务器端获取之前的历史消息，但是必须先开通历史消息云存储功能。
 例如，本地会话中有10条消息，您想拉取更多保存在服务器的消息的话，recordTime 应传入最早的消息的发送时间戳，count 传入
 2~20 之间的数值。

 @discussion 本地数据库可以查到的消息，该接口不会再返回，所以建议先用 getHistoryMessages
 相关接口取本地历史消息，本地消息取完之后再通过该接口获取远端历史消息

 @remarks 消息操作
 */
- (void)getRemoteHistoryMessages:(RCConversationType)conversationType
                        targetId:(NSString *)targetId
                       channelId:(nullable NSString *)channelId
                      recordTime:(long long)recordTime
                           count:(int)count
                         success:(nullable void (^)(NSArray <RCMessage *> *messages, BOOL isRemaining))successBlock
                           error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 从服务器端获取之前的历史消息

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param option              可配置的参数
 @param successBlock        获取成功的回调 [messages:获取到的历史消息数组, isRemaining 是否还有剩余消息 YES
 表示还有剩余，NO 表示无剩余]
 @param errorBlock          获取失败的回调 [status:获取失败的错误码]

 @discussion
 此方法从服务器端获取之前的历史消息，但是必须先开通历史消息云存储功能。
 例如，本地会话中有 10 条消息，您想拉取更多保存在服务器的消息的话，recordTime 应传入最早的消息的发送时间戳，count 传入
 2~20 之间的数值。

 @remarks 消息操作
 */
- (void)getRemoteHistoryMessages:(RCConversationType)conversationType
                        targetId:(NSString *)targetId
                       channelId:(nullable NSString *)channelId
                          option:(RCRemoteHistoryMsgOption *)option
                         success:(nullable void (^)(NSArray <RCMessage *> *messages, BOOL isRemaining))successBlock
                           error:(nullable void (^)(RCErrorCode status))errorBlock;


/*!
 获取历史消息（仅支持单群聊）

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param option              可配置的参数
 @param complete        获取成功的回调 [messages：获取到的历史消息数组； code : 获取是否成功，0表示成功，非 0 表示失败，此时 messages 数组可能存在断档]

 @discussion 必须开通历史消息云存储功能。
 @discussion count 传入 2~20 之间的数值。
 @discussion 此方法先从本地获取历史消息，本地有缺失的情况下会从服务端同步缺失的部分。当本地没有更多消息的时候，会从服务器拉取
 @discussion 从服务端同步失败的时候会返回非 0 的 errorCode，同时把本地能取到的消息回调上去。

 @remarks 消息操作
 */
- (void)getMessages:(RCConversationType)conversationType
           targetId:(NSString *)targetId
          channelId:(nullable NSString *)channelId
             option:(RCHistoryMessageOption *)option
           complete:(nullable void (^)(NSArray <RCMessage *> * _Nullable messages, RCErrorCode code))complete;
/*!
 * \~chinese
 获取历史消息

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param option              可配置的参数
 @param complete        获取成功的回调 [messages：获取到的历史消息数组； code : 获取是否成功，0表示成功，非 0 表示失败，此时 messages 数组可能存在断档]
 @param errorBlock 获取失败的回调 [status:获取失败的错误码]，参数合法性检查不通过会直接回调 errorBlock

 @discussion 必须开通历史消息云存储功能。
 @discussion count 传入 2~20 之间的数值。
 @discussion 此方法先从本地获取历史消息，本地有缺失的情况下会从服务端同步缺失的部分。当本地没有更多消息的时候，会从服务器拉取
 @discussion 从服务端同步失败的时候会返回非 0 的 errorCode，同时把本地能取到的消息回调上去。
 @discussion 在获取远端消息的时候，可能会拉到信令消息，信令消息会被 SDK 排除掉，导致 messages.count < option.count 此时只要 isRemaining 为 YES，那么下次拉取消息的时候，请用 timestamp 当做 option.recordTime 再去拉取
 * 如果 isRemaining 为 NO，则代表远端不再有消息了

 @remarks 消息操作
 */
- (void)getMessages:(RCConversationType)conversationType
           targetId:(NSString *)targetId
          channelId:(nullable NSString *)channelId
             option:(RCHistoryMessageOption *)option
           complete:(nullable void (^)(NSArray <RCMessage *> * _Nullable messages,long long timestamp,BOOL isRemaining, RCErrorCode code))complete
              error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 获取会话中@提醒自己的消息

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识

 @discussion
 此方法从本地获取被@提醒的消息(最多返回 10 条信息)
 @warning 使用 IMKit 注意在进入会话页面前调用，否则在进入会话清除未读数的接口 clearMessagesUnreadStatus: targetId:
 以及 设置消息接收状态接口 setMessageReceivedStatus:receivedStatus:会同步清除被提示信息状态。

 @remarks 高级功能
 */
- (nullable NSArray<RCMessage *> *)getUnreadMentionedMessages:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getUnreadMentionedMessages:targetId:channelId:completion:] instead");
/*!
 异步获取会话中@提醒自己的消息

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId           所属会话的业务标识
 @param completion          异步回调[消息实体 RCMessage 对象列表]
 
 @discussion
 此方法从本地获取被@提醒的消息(最多返回 10 条信息)
 @warning 使用 IMKit 注意在进入会话页面前调用，否则在进入会话清除未读数的接口 clearMessagesUnreadStatus: targetId:
 以及 设置消息接收状态接口 setMessageReceivedStatus:receivedStatus:会同步清除被提示信息状态。

 @remarks 高级功能
 */
- (void)getUnreadMentionedMessages:(RCConversationType)conversationType
                          targetId:(NSString *)targetId
                         channelId:(nullable NSString *)channelId
                        completion:(nullable void(^)(NSArray<RCMessage *> * _Nullable messages))completion;

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
*/

- (nullable NSArray<RCMessage *>  *)getUnreadMentionedMessages:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId count:(int)count desc:(BOOL)desc __deprecated_msg("Use [RCChannelClient getUnreadMentionedMessages:targetId:channelId:count:desc:completion:] instead");

/*!
异步获取本地指定会话的未读条数的 @ 消息列表，仅支持群组
 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId           所属会话的业务标识
 @param count               未读的 @ 消息，取值范围 [1,100]
 @param desc                是否是降序查
 @param completion          异步回调[消息实体 RCMessage 对象列表]
 
 @discussion 假如有 1000 条未读的 @ 消息，取 100 条未读
    desc 为 true 时获取后 100 条消息，messageList 的顺序是 901 到 1000
    desc 为 false 是获取前 100 条消息，messageList 的顺序是 1 到 100
 
 @warning 使用 IMKit 注意在进入会话页面前调用，否则在进入会话清除未读数的接口 clearMessagesUnreadStatus: targetId:
 以及 设置消息接收状态接口 setMessageReceivedStatus:receivedStatus:会同步清除被提示信息状态。
*/

- (void)getUnreadMentionedMessages:(RCConversationType)conversationType
                          targetId:(NSString *)targetId
                         channelId:(nullable NSString *)channelId
                             count:(int)count
                              desc:(BOOL)desc
                        completion:(nullable void(^)(NSArray<RCMessage *> * _Nullable messages))completion;

/*!
 根据会话 id 获取所有子频道的 @ 未读消息总数
 
 @param targetId  会话 ID
 @return         该会话内的未读消息数
 
 @remarks 超级群消息操作
 */
- (int)getUltraGroupUnreadMentionedCount:(NSString *)targetId __deprecated_msg("Use [RCChannelClient getUltraGroupUnreadMentionedCount:completion:] instead");

/*!
 异步根据会话 id 获取所有子频道的 @ 未读消息总数
 
 @param targetId  会话 ID
 @return         该会话内的未读消息数
 
 @remarks 超级群消息操作
 */
- (void)getUltraGroupUnreadMentionedCount:(NSString *)targetId
                               completion:(nullable void(^)(int num))completion;
/**
 消息修改

 @param messageUId 将被修改的消息id
 @param newContent 将被修改的消息内容
 @param successBlock 成功的回调
 @param errorBlock 失败的回调

 @discussion
 此方法只能修改相同频道的同类型消息，仅能修改自己发送的消息

 @remarks 消息操作
 */
- (void)modifyUltraGroupMessage:(NSString *)messageUId
                 messageContent:(RCMessageContent *)newContent
                        success:(nullable void (^)(void))successBlock
                          error:(nullable void (^)(RCErrorCode status))errorBlock;

/**
 更新消息扩展信息

 @param messageUId 消息 messageUId
 @param expansionDic 要更新的消息扩展信息键值对
 @param successBlock 成功的回调
 @param errorBlock 失败的回调
 
 @remarks 高级功能
*/
- (void)updateUltraGroupMessageExpansion:(NSString *)messageUId
                            expansionDic:(NSDictionary<NSString *, NSString *> *)expansionDic
                                 success:(nullable void (^)(void))successBlock
                                   error:(nullable void (^)(RCErrorCode status))errorBlock;

/**
 删除消息扩展信息中特定的键值对

 @param messageUId 消息 messageUId
 @param keyArray 消息扩展信息中待删除的 key 的列表
 @param successBlock 成功的回调
 @param errorBlock 失败的回调

 @discussion 扩展信息只支持单聊和群组，其它会话类型不能设置扩展信息
 
 @remarks 高级功能
*/
- (void)removeUltraGroupMessageExpansion:(NSString *)messageUId
                                keyArray:(NSArray<NSString *> *)keyArray
                                 success:(nullable void (^)(void))successBlock
                                   error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 撤回消息

 @param message      需要撤回的消息
 @param successBlock 撤回成功的回调 [messageId:撤回的消息 ID，该消息已经变更为新的消息]
 @param errorBlock   撤回失败的回调 [errorCode:撤回失败错误码]
 @remarks 高级功能
 */
- (void)recallUltraGroupMessage:(RCMessage *)message
                        success:(nullable void (^)(long messageId))successBlock
                          error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 撤回消息

 @param message      需要撤回的消息
 @param isDelete     是否移除远端消息记录
 @param successBlock 撤回成功的回调 [messageId:撤回的消息 ID，该消息已经变更为新的消息]
 @param errorBlock   撤回失败的回调 [errorCode:撤回失败错误码]
 @remarks 高级功能
 */
- (void)recallUltraGroupMessage:(RCMessage *)message
                       isDelete:(BOOL)isDelete
                        success:(nullable void (^)(long messageId))successBlock
                          error:(nullable void (^)(RCErrorCode errorcode))errorBlock;
/*!
 获取同一个超级群下的批量服务消息（含所有频道）
 获取成功后强制更新本地消息
 @param messages      消息列表 [最多20条,每个消息对象需包含ConversationType,targetId,channelId, messageUid,sentTime]
 @param successBlock 成功的回调 [matchedMsgList:成功的消息列表，notMatchMsgList:失败的消息列表]
 @param errorBlock   失败的回调 [errorCode:错误码]
 @remarks 高级功能
 */
- (void)getBatchRemoteUltraGroupMessages:(NSArray <RCMessage*>*)messages
                                 success:(nullable void (^)(NSArray<RCMessage *> *matchedMsgList, NSArray<RCMessage *> *notMatchMsgList))successBlock
                                   error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 批量获取本地消息,支持单聊、群聊、超级群、聊天室会话类型
 @param conversationType        会话类型[非法报错:INVALID_PARAMETER_CONVERSATIONTYPE]
 @param targetId                会话ID[非法报错:INVALID_PARAMETER_TARGETID]
 @param channelId               频道ID(非超级群时传nil)[非法报错:INVALID_PARAMETER_CHANNELID]
 @param messageUIDs             消息UID列表(最多20条)[数量大于20或为0,类型不对:INVALID_PARAMETER_MESSAGELIST]
 @param successBlock            成功的回调 [messages:成功的消息列表，mismatch:失败的消息UID列表]
 @param errorBlock              失败的回调 [errorCode:错误码]
 
 @discussion  mismatch不为空, 则代表本地没有对应的 message:
 1. messageUid 可能不是标准的UID字符串,本地无法匹配
 2. 超级群默认只同步会话最后一条消息, 可能本地找不到本地对应消息, 可以先调用 getBatchRemoteUltraGroupMessages 从远端拉去一下
 3. 聊天室退出之后, 本地消息会被清空, 调用该接口无法拿到本地消息
 @remarks 高级功能
 @since 5.3.0

 */
- (void)getBatchLocalMessages:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                    channelId:(nullable NSString *)channelId
                  messageUIDs:(NSArray<NSString *> *)messageUIDs
                      success:(nullable void (^)(NSArray<RCMessage *> *messages, NSArray<NSString *> *mismatch))successBlock
                        error:(nullable void (^)(RCErrorCode status))errorBlock;



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
 */
- (nullable RCMessage *)getFirstUnreadMessage:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getFirstUnreadMessage:targetId:channelId:completion:] instead");
/**
 * 异步获取会话里第一条未读消息。
 *
 * @param conversationType 会话类型
 * @param targetId   会话 ID
 * @param channelId  所属会话的业务标识
 * @param completion 异步回调[第一条未读消息的实体]
 
 * @remarks 消息操作
 * @discussion 前提：超级群会话不接收离线消息。
 *  用户在线接收的超级群未读消息已经保存到本地数据库，可以通过此接口获取到
 *  用户离线的超级群未读消息，用户在线之后不收离线未读消息，通过此接口获取第一条未读消息为空
 */
- (void)getFirstUnreadMessage:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                    channelId:(nullable NSString *)channelId
                   completion:(nullable void(^)(RCMessage * _Nullable message))completion;

/*!
 删除某个会话中的所有消息

 @param conversationType    会话类型，不支持聊天室
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param successBlock        成功的回调
 @param errorBlock          失败的回调

 @discussion 此方法删除数据库中该会话的消息记录，同时会整理压缩数据库，减少占用空间

 @remarks 消息操作
 */
- (void)deleteMessages:(RCConversationType)conversationType
              targetId:(NSString *)targetId
             channelId:(nullable NSString *)channelId
               success:(nullable void (^)(void))successBlock
                 error:(nullable void (^)(RCErrorCode status))errorBlock;

/**
 批量删除某个会话中的指定远端消息（同时删除对应的本地消息）

 @param conversationType 会话类型，不支持聊天室和超级群
 @param targetId 目标会话ID
 @param channelId          所属会话的业务标识
 @param messages 将被删除的消息列表
 @param successBlock 成功的回调
 @param errorBlock 失败的回调

 @discussion 此方法会同时删除远端和本地消息。
 一次批量操作仅支持删除属于同一个会话的消息，请确保消息列表中的所有消息来自同一会话
 一次最多删除 100 条消息。

 @remarks 消息操作
 */
- (void)deleteRemoteMessage:(RCConversationType)conversationType
                   targetId:(NSString *)targetId
                  channelId:(nullable NSString *)channelId
                   messages:(NSArray<RCMessage *> *)messages
                    success:(nullable void (^)(void))successBlock
                      error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 删除本地所有 channel 特定时间之前的消息

 @param targetId            会话 ID
 @param timestamp          会话的时间戳
 @return             是否删除成功

 @remarks 消息操作
 */
- (BOOL)deleteUltraGroupMessagesForAllChannel:(NSString *)targetId timestamp:(long long)timestamp __deprecated_msg("Use [RCChannelClient deleteUltraGroupMessagesForAllChannel:timestamp:completion:] instead");
/*!
 异步删除本地所有 channel 特定时间之前的消息

 @param targetId            会话 ID
 @param timestamp           会话的时间戳
 @param completion          异步回调[是否删除成功]

 @remarks 消息操作
 */
- (void)deleteUltraGroupMessagesForAllChannel:(NSString *)targetId
                                    timestamp:(long long)timestamp
                                   completion:(nullable void(^)(BOOL result))completion;
/*!
 删除本地特定 channel 特点时间之前的消息

 @param targetId            会话 ID
 @param channelId           频道 ID
 @param timestamp          会话的时间戳
 @return             是否删除成功

 @remarks 消息操作
 */
- (BOOL)deleteUltraGroupMessages:(NSString *)targetId
                       channelId:(nullable NSString *)channelId
                       timestamp:(long long)timestamp __deprecated_msg("Use [RCChannelClient deleteUltraGroupMessages:channelId:timestamp:completion:] instead");
/*!
 异步删除本地特定 channel 特点时间之前的消息

 @param targetId            会话 ID
 @param channelId           频道 ID
 @param timestamp           会话的时间戳
 @param completion          异步回调[是否删除成功]
 
 @return

 @remarks 消息操作
 */
- (void)deleteUltraGroupMessages:(NSString *)targetId
                       channelId:(nullable NSString *)channelId
                       timestamp:(long long)timestamp
                      completion:(nullable void(^)(BOOL result))completion;
/*!
 删除服务端特定 channel 特定时间之前的消息

 @param targetId            会话 ID
 @param channelId           频道 ID
 @param timestamp          会话的时间戳
 @param successBlock    成功的回调
 @param errorBlock         失败的回调

 @remarks 消息操作
 */
- (void)deleteRemoteUltraGroupMessages:(NSString *)targetId
                             channelId:(nullable NSString *)channelId
                             timestamp:(long long)timestamp
                               success:(nullable void (^)(void))successBlock
                                 error:(nullable void (^)(RCErrorCode status))errorBlock;
/*!
 删除某个会话中的所有消息

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @return                    是否删除成功

 @remarks 消息操作
 */
- (BOOL)clearMessages:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient clearMessages:targetId:channelId:completion:] instead");
/*!
 异步删除某个会话中的所有消息

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId           所属会话的业务标识
 @param completion          异步回调[是否删除成功]
 
 @remarks 消息操作
 */
- (void)clearMessages:(RCConversationType)conversationType
             targetId:(NSString *)targetId
            channelId:(nullable NSString *)channelId
           completion:(nullable void(^)(BOOL result))completion;
#pragma mark - 会话列表操作
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
 */
- (nullable NSArray<RCConversation *> *)getConversationList:(NSArray<NSNumber *> *)conversationTypeList channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getConversationList:channelId:completion:] instead");
/*!
 异步获取会话列表

 @param conversationTypeList    会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 @param channelId               所属会话的业务标识
 @param completion              异步回调[会话 RCConversation 的列表]
 
 @discussion 此方法会从本地数据库中，读取会话列表。
 返回的会话列表按照时间从前往后排列，如果有置顶的会话，则置顶的会话会排列在前面。
 @discussion 当您的会话较多且没有清理机制的时候，强烈建议您使用 getConversationList: count: startTime:
 分页拉取会话列表,否则有可能造成内存过大。
 @discussion conversationTypeList中类型个数不能超过300，超过会被截断。

 @remarks 会话列表
 */
- (void)getConversationList:(NSArray<NSNumber *> *)conversationTypeList
                  channelId:(nullable NSString *)channelId
                 completion:(nullable void(^)(NSArray<RCConversation *> * _Nullable conversationList))completion;
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
 */
- (nullable NSArray<RCConversation *> *)getConversationList:(NSArray<NSNumber *> *)conversationTypeList channelId:(nullable NSString *)channelId count:(int)count startTime:(long long)startTime __deprecated_msg("Use [RCChannelClient getConversationList:channelId:count:startTime:completion:] instead");

/*!
 异步分页获取会话列表

 @param conversationTypeList 会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 @param channelId          所属会话的业务标识
 @param count                获取的数量（当实际取回的会话数量小于 count 值时，表明已取完数据）
 @param startTime            会话的时间戳（获取这个时间戳之前的会话列表，0表示从最新开始获取）
 @param completion          异步回调[会话 RCConversation 的列表]
 
 @discussion 此方法会从本地数据库中，读取会话列表。
 返回的会话列表按照时间从前往后排列，如果有置顶的会话，则置顶的会话会排列在前面。
 @discussion conversationTypeList中类型个数不能超过300，超过会被截断。

 @remarks 会话列表
 */
- (void)getConversationList:(NSArray<NSNumber *> *)conversationTypeList
                  channelId:(nullable NSString *)channelId
                      count:(int)count
                  startTime:(long long)startTime
                 completion:(nullable void(^)(NSArray<RCConversation *> * _Nullable conversationList))completion;

/*!
获取特定会话下所有频道的会话列表

@param conversationType         会话类型
@param targetId                           会话 ID
@return                    会话 RCConversation 的列表

@discussion 此方法会从本地数据库中，读取会话列表。
返回的会话列表按照时间从前往后排列，如果有置顶的会话，则置顶的会话会排列在前面。

@remarks 会话列表
*/
- (nullable NSArray<RCConversation *> *)getConversationListForAllChannel:(RCConversationType)conversationType targetId:(NSString *)targetId __deprecated_msg("Use [RCChannelClient getConversationListForAllChannel:targetId:completion:] instead");
/*!
异步获取特定会话下所有频道的会话列表

@param conversationType         会话类型
@param targetId                 会话 ID
@param completion               异步回调[会话 RCConversation 的列表]
 
@discussion 此方法会从本地数据库中，读取会话列表。
返回的会话列表按照时间从前往后排列，如果有置顶的会话，则置顶的会话会排列在前面。

@remarks 会话列表
*/
- (void)getConversationListForAllChannel:(RCConversationType)conversationType
                                targetId:(NSString *)targetId
                              completion:(nullable void(^)(NSArray<RCConversation *> * _Nullable conversationList))completion;
/*!
 分页获取特定会话类型下所有 channel 的会话列表
 @param conversationTypeList         会话类型数组
 @param count                                           会话个数
 @param startTime                                 开始时间，首次可传入 0
 @return                    会话 RCConversation 的列表

 @discussion 此方法会从本地数据库中，读取会话列表。
 返回的会话列表按照时间从前往后排列，如果有置顶的会话，则置顶的会话会排列在前面。
 */
- (nullable NSArray<RCConversation *> *)getConversationListForAllChannel:(NSArray<NSNumber *> *)conversationTypeList count:(int)count startTime:(long long)startTime __deprecated_msg("Use [RCChannelClient getConversationListForAllChannel:count:startTime:completion:] instead");


/*!
分页异步获取特定会话类型下所有 channel 的会话列表
@param conversationTypeList         会话类型数组
@param count                        会话个数
@param startTime                    开始时间，首次可传入 0
@param completion                   异步回调[会话 RCConversation 的列表]
 
@discussion 此方法会从本地数据库中，读取会话列表。
返回的会话列表按照时间从前往后排列，如果有置顶的会话，则置顶的会话会排列在前面。
*/
- (void)getConversationListForAllChannel:(NSArray<NSNumber *> *)conversationTypeList
                                   count:(int)count
                               startTime:(long long)startTime
                              completion:(nullable void(^)(NSArray<RCConversation *> * _Nullable conversationList))completion;
/*!
 获取所有含 ChannelId 会话列表

 @param conversationTypeList 会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 @return                     会话 RCConversation 的列表

 @discussion 此方法会从本地数据库中，读取会话列表。
 返回的会话列表按照时间从前往后排列，如果有置顶的会话，则置顶的会话会排列在前面。
 
 @warning  当会话数量多的时候，会有性能问题，所以建议在非主线程调用该接口
 @remarks 会话列表
 */
- (nullable NSArray<RCConversation *> *)getConversationListForAllChannel:(NSArray<NSNumber *> *)conversationTypeList __deprecated_msg("Use [RCChannelClient getConversationListForAllChannel:completion:] instead");
/*!
 异步获取所有含 ChannelId 会话列表

 @param conversationTypeList 会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 @param completion           异步回调[会话 RCConversation 的列表]
 
 @discussion 此方法会从本地数据库中，读取会话列表。
 返回的会话列表按照时间从前往后排列，如果有置顶的会话，则置顶的会话会排列在前面。
 
 @warning  当会话数量多的时候，会有性能问题，所以建议在非主线程调用该接口
 @remarks 会话列表
 */
- (void)getConversationListForAllChannel:(NSArray<NSNumber *> *)conversationTypeList
                              completion:(nullable void(^)(NSArray<RCConversation *> * _Nullable conversationList))completion;

/*!
 获取单个会话数据

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @return                    会话的对象

 @remarks 会话
 */
- (nullable RCConversation *)getConversation:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getConversation:targetId:channelId:completion:] instead");
/*!
 异步获取单个会话数据

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId           所属会话的业务标识
 @param completion          异步回调[会话的对象]

 @remarks 会话
 */
- (void)getConversation:(RCConversationType)conversationType
               targetId:(NSString *)targetId
              channelId:(nullable NSString *)channelId
             completion:(nullable void(^)(RCConversation * _Nullable conversation))completion;
/*!
 获取会话中的消息数量

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId           所属会话的业务标识
 @param completion          异步回调[会话中的消息数量]
 
 @discussion -1 表示获取消息数量出错。

 @remarks 会话
 */
- (int)getMessageCount:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getMessageCount:targetId:channelId:completion:] instead");
/*!
 异步获取会话中的消息数量

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId           所属会话的业务标识
 @param completion          异步回调[会话中的消息数量]
 
 @discussion -1 表示获取消息数量出错。

 @remarks 会话
 */
- (void)getMessageCount:(RCConversationType)conversationType
               targetId:(NSString *)targetId
              channelId:(nullable NSString *)channelId
             completion:(nullable void(^)(int num))completion;
/*!
 删除指定类型的会话

 @param conversationTypeList 会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 @param channelId          所属会话的业务标识
 @return                        是否删除成功

 @discussion 此方法会从本地存储中删除该会话，同时删除会话中的消息。

 @discussion 此方法不支持超级群的会话类型，包含超级群时可能会造成数据异常。
 @discussion conversationTypeList中类型个数不能超过300，超过会被截断。
 
 @remarks 会话
 */
- (BOOL)clearConversations:(NSArray<NSNumber *> *)conversationTypeList channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient clearConversations:channelId:completion:] instead");
/*!
 异步删除指定类型的会话

 @param conversationTypeList 会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 @param channelId          所属会话的业务标识
 @param completion          异步回调[是否删除成功]

 @discussion 此方法会从本地存储中删除该会话，同时删除会话中的消息。

 @discussion 此方法不支持超级群的会话类型，包含超级群时可能会造成数据异常。
 @discussion conversationTypeList中类型个数不能超过300，超过会被截断。
 
 @remarks 会话
 */
- (void)clearConversations:(NSArray<NSNumber *> *)conversationTypeList
                 channelId:(nullable NSString *)channelId
                completion:(nullable void(^)(BOOL result))completion;
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
 */
- (BOOL)removeConversation:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient removeConversation:targetId:channelId:completion:] instead");
/*!
 异步删除本地和服务的会话

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param completion          异步回调[是否删除成功]

 @discussion 此方法会删除该会话，但是不会删除会话中的消息。如果此会话中有新的消息，该会话将重新在会话列表中显示，并显示最近的历史消息。
 @warning 此方法会同时删除本地和服务的会话。如果服务的会话删除失败，本地的会话依然会被删除
 SDK 在未连接的情况下，删除服务会话会失败

 @remarks 会话
 */
- (void)removeConversation:(RCConversationType)conversationType
                  targetId:(NSString *)targetId
                 channelId:(nullable NSString *)channelId
                completion:(nullable void(^)(BOOL result))completion;

/*!
 设置会话的置顶状态

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param isTop               是否置顶
 @return                    设置是否成功

 @discussion 会话不存在时设置置顶，会在会话列表生成会话。

 @remarks 会话
 */
- (BOOL)setConversationToTop:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId isTop:(BOOL)isTop __deprecated_msg("Use [RCChannelClient setConversationToTop:targetId:channelId:isTop:completion:] instead");

/*!
 异步设置会话的置顶状态

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param isTop               是否置顶
 @param completion          异步回调[设置是否成功]
 
 @discussion 会话不存在时设置置顶，会在会话列表生成会话。

 @remarks 会话
 */
- (void)setConversationToTop:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
                   channelId:(nullable NSString *)channelId
                       isTop:(BOOL)isTop
                  completion:(nullable void(^)(BOOL result))completion;

/*!
 获取会话的置顶状态

 @param conversationIdentifier 会话信息
 @param channelId          所属会话的业务标识

 @discussion 此方法会从本地数据库中，读取该会话是否置顶。

 @remarks 会话
 */
- (BOOL)getConversationTopStatus:(RCConversationIdentifier *)conversationIdentifier channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getConversationTopStatus:channelId:completion:] instead");
/*!
 异步获取会话的置顶状态

 @param conversationIdentifier 会话信息
 @param channelId          所属会话的业务标识
 @param completion          异步回调[是否置顶]

 @discussion 此方法会从本地数据库中，读取该会话是否置顶。

 @remarks 会话
 */
- (void)getConversationTopStatus:(RCConversationIdentifier *)conversationIdentifier
                       channelId:(nullable NSString *)channelId
                      completion:(nullable void(^)(BOOL result))completion;
/*!
 获取置顶的会话列表

 @param conversationTypeList 会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 @return                     置顶的会话 RCConversation 的列表

 @discussion 此方法会从本地数据库中，读取置顶的会话列表。

 @remarks 会话列表
 */
- (nullable NSArray<RCConversation *> *)getTopConversationList:(NSArray<NSNumber *> *)conversationTypeList channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getTopConversationList:channelId:completion:] instead");
/*!
 异步获取置顶的会话列表

 @param conversationTypeList 会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 @param completion          异步回调[置顶的会话 RCConversation 的列表]
 
 @discussion 此方法会从本地数据库中，读取置顶的会话列表。

 @remarks 会话列表
 */
- (void)getTopConversationList:(NSArray<NSNumber *> *)conversationTypeList
                     channelId:(nullable NSString *)channelId
                    completion:(nullable void(^)(NSArray<RCConversation *> * _Nullable conversationList))completion;
#pragma mark 会话中的草稿操作

/*!
 获取会话中的草稿信息（用户输入但未发送的暂存消息）

 @param conversationType    会话类型
 @param targetId            会话目标 ID
 @param channelId          所属会话的业务标识
 @return                    该会话中的草稿

 @remarks 会话
 */
- (nullable NSString *)getTextMessageDraft:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getTextMessageDraft:targetId:channelId:completion:] instead");

/*!
 异步获取会话中的草稿信息（用户输入但未发送的暂存消息）

 @param conversationType    会话类型
 @param targetId            会话目标 ID
 @param channelId          所属会话的业务标识
 @param completion          异步回调[该会话中的草稿]

 @remarks 会话
 */
- (void)getTextMessageDraft:(RCConversationType)conversationType
                   targetId:(NSString *)targetId
                  channelId:(nullable NSString *)channelId
                 completion:(nullable void(^)(NSString *  _Nullable content))completion;

/*!
 保存草稿信息（用户输入但未发送的暂存消息）

 @param conversationType    会话类型
 @param targetId            会话目标 ID
 @param channelId          所属会话的业务标识
 @param content             草稿信息
 @return                    是否保存成功

 @remarks 会话
 */
- (BOOL)saveTextMessageDraft:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
                   channelId:(nullable NSString *)channelId
                     content:(NSString *)content __deprecated_msg("Use [RCChannelClient saveTextMessageDraft:targetId:channelId:content:completion:] instead");
/*!
 异步保存草稿信息（用户输入但未发送的暂存消息）

 @param conversationType    会话类型
 @param targetId            会话目标 ID
 @param channelId          所属会话的业务标识
 @param content             草稿信息
 @param completion          异步回调[是否保存成功]

 @remarks 会话
 */
- (void)saveTextMessageDraft:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
                   channelId:(nullable NSString *)channelId
                     content:(NSString *)content
                  completion:(nullable void(^)(BOOL result))completion;
/*!
 删除会话中的草稿信息（用户输入但未发送的暂存消息）

 @param conversationType    会话类型
 @param targetId            会话目标 ID
 @param channelId          所属会话的业务标识
 @return                    是否删除成功

 @remarks 会话
 */
- (BOOL)clearTextMessageDraft:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient clearTextMessageDraft:targetId:channelId:completion:] instead");
/*!
 异步删除会话中的草稿信息（用户输入但未发送的暂存消息）

 @param conversationType    会话类型
 @param targetId            会话目标 ID
 @param channelId          所属会话的业务标识
 @param completion          异步回调[是否删除成功]

 @remarks 会话
 */
- (void)clearTextMessageDraft:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                    channelId:(nullable NSString *)channelId
                   completion:(nullable void(^)(BOOL result))completion;

#pragma mark 未读消息数

/*!
 获取所有的未读消息数（聊天室会话除外）
 
 @param channelId          所属会话的业务标识

 @return    所有的未读消息数（含免打扰会话未读数）

 @remarks 会话
 */
- (int)getTotalUnreadCountWithChannelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getTotalUnreadCountWithChannelId:completion:] instead");
/*!
 异步获取所有的未读消息数（聊天室会话除外）
 
 @param channelId          所属会话的业务标识
 @param completion          异步回调[所有的未读消息数（含免打扰会话未读数）]

 @remarks 会话
 */
- (void)getTotalUnreadCountWithChannelId:(nullable NSString *)channelId
                              completion:(nullable void(^)(int num))completion;

/*!
 获取所有的未读消息数（聊天室会话除外）
 
 @param channelId          所属会话的业务标识
 @param isContain          是否包含免打扰会话的未读数，YES 包含免打扰会话未读数

 @return    所有的未读消息数

 @remarks 会话
 */
- (int)getTotalUnreadCountWithChannelId:(nullable NSString *)channelId containBlocked:(BOOL)isContain __deprecated_msg("Use [RCChannelClient getTotalUnreadCountWithChannelId:containBlocked:completion:] instead");
/*!
 异步获取所有的未读消息数（聊天室会话除外）
 
 @param channelId          所属会话的业务标识
 @param isContain          是否包含免打扰会话的未读数，YES 包含免打扰会话未读数
 @param completion          异步回调[所有的未读消息数]

 @remarks 会话
 */
- (void)getTotalUnreadCountWithChannelId:(nullable NSString *)channelId
                          containBlocked:(BOOL)isContain
                              completion:(nullable void(^)(int num))completion;
/*!
 获取某个会话内的未读消息数（聊天室会话除外）

 @param conversationType    会话类型
 @param targetId            会话目标 ID
 @param channelId          所属会话的业务标识
 @return                    该会话内的未读消息数

 @remarks 会话
 */
- (int)getUnreadCount:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getUnreadCount:targetId:channelId:completion:] instead");
/*!
 异步获取某个会话内的未读消息数（聊天室会话除外）

 @param conversationType    会话类型
 @param targetId            会话目标 ID
 @param channelId          所属会话的业务标识
 @param completion          异步回调[该会话内的未读消息数]

 @remarks 会话
 */
- (void)getUnreadCount:(RCConversationType)conversationType
              targetId:(NSString *)targetId
             channelId:(nullable NSString *)channelId
            completion:(nullable void(^)(int num))completion;
/*!
 获取某个会话内的未读消息数

 @param conversationIdentifier 会话信息
 @param messageClassList          消息类型数组
 @param channelId                         所属会话的业务标识
 @return                    该会话内的未读消息数

 @discussion 此方法不支持聊天室和超级群的会话类型。
 
 @remarks 会话
 */
- (int)getUnreadCount:(RCConversationIdentifier *)conversationIdentifier messageClassList:(NSArray <Class> *)messageClassList channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getUnreadCount:messageClassList:channelId:completion:] instead");
/*!
 异步获取某个会话内的未读消息数

 @param conversationIdentifier 会话信息
 @param messageClassList          消息类型数组
 @param channelId                         所属会话的业务标识
 @param completion          异步回调[该会话内的未读消息数]

 @discussion 此方法不支持聊天室和超级群的会话类型。
 
 @remarks 会话
 */
- (void)getUnreadCount:(RCConversationIdentifier *)conversationIdentifier
      messageClassList:(NSArray <Class> *)messageClassList
             channelId:(nullable NSString *)channelId
            completion:(nullable void(^)(int num))completion;
/**
 获取某些类型的会话中所有的未读消息数 （聊天室会话除外）

 @param conversationTypes   会话类型的数组
 @param channelId          所属会话的业务标识
 @param isContain           是否包含免打扰消息的未读数
 @return                    该类型的会话中所有的未读消息数

 @discussion conversationTypes中类型个数不能超过300，超过会被截断。
 
 @remarks 会话
 */
- (int)getUnreadCount:(NSArray<NSNumber *> *)conversationTypes channelId:(nullable NSString *)channelId containBlocked:(bool)isContain __deprecated_msg("Use [RCChannelClient getUnreadCount:channelId:containBlocked:completion:] instead");
/**
 异步获取某些类型的会话中所有的未读消息数 （聊天室会话除外）

 @param conversationTypes   会话类型的数组
 @param channelId          所属会话的业务标识
 @param isContain           是否包含免打扰消息的未读数
 @param completion          异步回调[该类型的会话中所有的未读消息数]

 @discussion conversationTypes中类型个数不能超过300，超过会被截断。
 
 @remarks 会话
 */
- (void)getUnreadCount:(NSArray<NSNumber *> *)conversationTypes
             channelId:(nullable NSString *)channelId
        containBlocked:(bool)isContain
            completion:(nullable void(^)(int num))completion;

/*!
 获取某个类型的会话中所有未读的被@的消息数

 @param conversationTypes   会话类型的数组
 @param channelId          所属会话的业务标识
 @return                    该类型的会话中所有未读的被@的消息数

 @discussion conversationTypeList中类型个数不能超过300，超过会被截断。
 
 @remarks 会话
 */
- (int)getUnreadMentionedCount:(NSArray<NSNumber *> *)conversationTypes channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getUnreadMentionedCount:channelId:completion:] instead");
/*!
 异步获取某个类型的会话中所有未读的被@的消息数

 @param conversationTypes   会话类型的数组
 @param channelId          所属会话的业务标识
 @param completion          异步回调[该类型的会话中所有未读的被@的消息数]

 @discussion conversationTypeList中类型个数不能超过300，超过会被截断。
 
 @remarks 会话
 */
- (void)getUnreadMentionedCount:(NSArray<NSNumber *> *)conversationTypes
                      channelId:(nullable NSString *)channelId
                     completion:(nullable void(^)(int num))completion;
/*!
 清除某个会话中的未读消息数

 @param conversationType    会话类型，不支持聊天室
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @return                    是否清除成功

 @remarks 会话
 @discussion 此方法不支持超级群的会话类型。
 */
- (BOOL)clearMessagesUnreadStatus:(RCConversationType)conversationType targetId:(NSString *)targetId channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient clearMessagesUnreadStatus:targetId:channelId:completion:] instead");
/*!
 异步清除某个会话中的未读消息数

 @param conversationType    会话类型，不支持聊天室
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param completion          异步回调[是否清除成功]

 @remarks 会话
 @discussion 此方法不支持超级群的会话类型。
 */
- (void)clearMessagesUnreadStatus:(RCConversationType)conversationType
                         targetId:(NSString *)targetId
                        channelId:(nullable NSString *)channelId
                       completion:(nullable void(^)(BOOL result))completion;
/*!
 清除某个会话中的未读消息数（该会话在时间戳 timestamp 之前的消息将被置成已读。）

 @param conversationType    会话类型，不支持聊天室
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param timestamp           该会话已阅读的最后一条消息的发送时间戳
 @return                    是否清除成功

 @remarks 会话
 */
- (BOOL)clearMessagesUnreadStatus:(RCConversationType)conversationType
                         targetId:(NSString *)targetId
                        channelId:(nullable NSString *)channelId
                             time:(long long)timestamp __deprecated_msg("Use [RCChannelClient clearMessagesUnreadStatus:targetId:channelId:time:completion:] instead");
/*!
 异步清除某个会话中的未读消息数（该会话在时间戳 timestamp 之前的消息将被置成已读。）

 @param conversationType    会话类型，不支持聊天室
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param timestamp           该会话已阅读的最后一条消息的发送时间戳
 @param completion          异步回调[是否清除成功]


 @remarks 会话
 */
- (void)clearMessagesUnreadStatus:(RCConversationType)conversationType
                         targetId:(NSString *)targetId
                        channelId:(nullable NSString *)channelId
                             time:(long long)timestamp
                       completion:(nullable void(^)(BOOL result))completion;

#pragma mark - 会话的消息提醒

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
 */
- (void)setConversationNotificationStatus:(RCConversationType)conversationType
                                 targetId:(NSString *)targetId
                                channelId:(nullable NSString *)channelId
                                isBlocked:(BOOL)isBlocked
                                  success:(nullable void (^)(RCConversationNotificationStatus nStatus))successBlock
                                    error:(nullable void (^)(RCErrorCode status))errorBlock __deprecated_msg("Use [RCChannelClient setConversationChannelNotificationLevel:targetId:channelId:level:success:error:] instead");


/*!
 设置会话的消息提醒状态

 @param conversationType            会话类型
 @param targetId                    会话 ID
 @param channelId                   所属会话的业务标识
 @param level                       消息通知级别
 @param successBlock                设置成功的回调
 @param errorBlock                  设置失败的回调 [status:设置失败的错误码]

 @discussion
 如果您需要移除消息通知，level参数传入RCPushNotificationLevelDefault即可
 注：超级群通过该接口对具体频道进行免打扰设置
  
 @remarks 会话
 */
- (void)setConversationChannelNotificationLevel:(RCConversationType)conversationType
                                       targetId:(NSString *)targetId
                                      channelId:(nullable NSString *)channelId
                                          level:(RCPushNotificationLevel)level
                                        success:(nullable void (^)(void))successBlock
                                          error:(nullable void (^)(RCErrorCode status))errorBlock;



/*!
 查询会话的消息提醒状态

 @param conversationType    会话类型（不支持聊天室，聊天室是不接受会话消息提醒的）
 @param targetId            会话 ID
 @param channelId          所属会话的业务标识
 @param successBlock        查询成功的回调 [nStatus:会话设置的消息提醒状态]
 @param errorBlock          查询失败的回调 [status:设置失败的错误码]

 @remarks 会话
 */
- (void)getConversationNotificationStatus:(RCConversationType)conversationType
                                 targetId:(NSString *)targetId
                                channelId:(nullable NSString *)channelId
                                  success:(nullable void (^)(RCConversationNotificationStatus nStatus))successBlock
                                    error:(nullable void (^)(RCErrorCode status))errorBlock;
/*!
  查询消息通知级别

 @param conversationType    会话类型
 @param targetId            会话 ID
 @param channelId           所属会话的业务标识
 @param successBlock        设置成功的回调 [level:消息通知级别]
 @param errorBlock          查询失败的回调 [status:设置失败的错误码]

 @remarks 会话
 */
- (void)getConversationChannelNotificationLevel:(RCConversationType)conversationType
                                       targetId:(NSString *)targetId
                                      channelId:(nullable NSString *)channelId
                                        success:(nullable void (^)(RCPushNotificationLevel level))successBlock
                                          error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 获取消息免打扰会话列表
 @param conversationTypeList 会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 @param channelId          所属会话的业务标识
 @return                     消息免打扰会话 RCConversation 的列表

 @discussion 此方法会从本地数据库中，读取消息免打扰会话列表。

 @remarks 会话列表
 */
- (nullable NSArray<RCConversation *> *)getBlockedConversationList:(NSArray<NSNumber *> *)conversationTypeList channelId:(nullable NSString *)channelId __deprecated_msg("Use [RCChannelClient getBlockedConversationList:channelId:completion:] instead");
/*!
 异步获取消息免打扰会话列表
 @param conversationTypeList 会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 @param channelId          所属会话的业务标识
 @param completion          异步回调[消息免打扰会话 RCConversation 的列表]
 
 @discussion 此方法会从本地数据库中，读取消息免打扰会话列表。

 @remarks 会话列表
 */
- (void)getBlockedConversationList:(NSArray<NSNumber *> *)conversationTypeList
                         channelId:(nullable NSString *)channelId
                        completion:(nullable void(^)(NSArray<RCConversation *> * _Nullable conversationList))completion;
/*!
 设置超级群的默认消息状态
 一般由管理员设置的接口，针对超级群的所有群成员生效，针对超级群下所有频道生效，优先级较低。如果群成员自己超级群的免打扰级别，那么以群成员自己设置的为准。
 
 @param targetId 会话 ID
 @param level 等级
 @param successBlock 设置成功的回调
 @param errorBlock 设置失败的回调 [status:设置失败的错误码]
 */
- (void)setUltraGroupConversationDefaultNotificationLevel:(NSString *)targetId
                                                    level:(RCPushNotificationLevel)level
                                                  success:(nullable void (^)(void))successBlock
                                                    error:(nullable void (^)(RCErrorCode status))errorBlock;
/*!
 获取超级群的默认消息状态

 @param targetId                    会话 ID
 @param successBlock                设置成功的回调 [level:消息通知级别]
 @param errorBlock                  设置失败的回调 [status:设置失败的错误码]

 @remarks 会话
 */
- (void)getUltraGroupConversationDefaultNotificationLevel:(NSString *)targetId
                                                  success:(nullable void (^)(RCPushNotificationLevel level))successBlock
                                                    error:(nullable void (^)(RCErrorCode status))errorBlock;


#pragma mark - 输入状态提醒

/*!
 向会话中发送正在输入的状态

 @param conversationType    会话类型
 @param targetId            会话目标  ID
 @param channelId          所属会话的业务标识
 @param objectName         正在输入的消息的类型名

 @discussion
 contentType 为用户当前正在编辑的消息类型名，即 RCMessageContent 中 getObjectName 的返回值。
 如文本消息，应该传类型名"RC:TxtMsg"。

 @warning 目前仅支持单聊。

 @remarks 高级功能
 */
- (void)sendTypingStatus:(RCConversationType)conversationType
                targetId:(NSString *)targetId
               channelId:(nullable NSString *)channelId
             contentType:(NSString *)objectName;

/*!
 向会话中发送正在输入的状态

 @param targetId            会话目标  ID
 @param channelId          所属会话的频道id
 @param status                输入状态类型

 @remarks 高级功能
 */
- (void)sendUltraGroupTypingStatus:(NSString *)targetId
                         channelId:(nullable NSString *)channelId
                      typingStatus:(RCUltraGroupTypingStatus)status
                           success:(nullable void (^)(void))successBlock
                             error:(nullable void (^)(RCErrorCode status))errorBlock;
#pragma mark - 搜索

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
 */
- (nullable NSArray<RCMessage *> *)searchMessages:(RCConversationType)conversationType
                                         targetId:(NSString *)targetId
                                        channelId:(nullable NSString *)channelId
                                          keyword:(NSString *)keyword
                                            count:(int)count
                                        startTime:(long long)startTime __deprecated_msg("Use [RCChannelClient searchMessages:targetId:channelId:keyword:count:startTime:completion:] instead");
/*!
 根据关键字异步搜索指定会话中的消息

 @param conversationType 会话类型
 @param targetId         会话 ID
 @param channelId          所属会话的业务标识
 @param keyword          关键字
 @param count            最大的查询数量
 @param startTime        查询 startTime 之前的消息（传 0 表示不限时间）
 @param completion          异步回调[匹配的消息列表]
 
 @discussion 超级群会话类型只支持搜索已存储到本地的消息。
 
 @remarks 消息操作
 */
- (void)searchMessages:(RCConversationType)conversationType
              targetId:(NSString *)targetId
             channelId:(nullable NSString *)channelId
               keyword:(NSString *)keyword
                 count:(int)count
             startTime:(long long)startTime
            completion:(nullable void(^)(NSArray<RCMessage *> * _Nullable messages))completion;

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
 根据时间，偏移量和个数异步搜索指定会话中的消息

 @param conversationType 会话类型
 @param targetId         会话 ID
 @param keyword           关键字，传空默认为是查全部符合条件的消息
 @param startTime      查询 startTime 之后的消息， startTime >= 0
 @param endTime           查询 endTime 之前的消息，endTime > startTime
 @param offset             查询的消息的偏移量，offset >= 0
 @param limit               最大的查询数量，limit 需大于 0，最大值为100，如果大于100，会默认成100。
 @param completion          异步回调[匹配的消息列表]

 @discussion 超级群会话类型只支持搜索已存储到本地的消息。
 
 @remarks 消息操作
 */
- (void)searchMessages:(RCConversationType)conversationType
              targetId:(NSString *)targetId
             channelId:(nullable NSString *)channelId
               keyword:(nullable NSString *)keyword
             startTime:(long long)startTime
               endTime:(long long)endTime
                offset:(int)offset
                 limit:(int)limit
            completion:(nullable void(^)(NSArray<RCMessage *> * _Nullable messages))completion;

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
 */
- (nullable NSArray<RCMessage *> *)searchMessages:(RCConversationType)conversationType
                                         targetId:(NSString *)targetId
                                        channelId:(nullable NSString *)channelId
                                           userId:(NSString *)userId
                                            count:(int)count
                                        startTime:(long long)startTime __deprecated_msg("Use [RCChannelClient searchMessages:targetId:channelId:userId:count:startTime:completion:] instead");
/*!
 按用户 ID 异步搜索指定会话中的消息

 @param conversationType 会话类型
 @param targetId         会话 ID
 @param channelId          所属会话的业务标识
 @param userId           搜索用户 ID
 @param count            最大的查询数量
 @param startTime        查询 startTime 之前的消息（传 0 表示不限时间）
 @param completion          异步回调[匹配的消息列表]


 @discussion 超级群会话类型只支持搜索已存储到本地的消息。
 
 @remarks 消息操作
 */
- (void)searchMessages:(RCConversationType)conversationType
              targetId:(NSString *)targetId
             channelId:(nullable NSString *)channelId
                userId:(NSString *)userId
                 count:(int)count
             startTime:(long long)startTime
            completion:(nullable void(^)(NSArray<RCMessage *> * _Nullable messages))completion;

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
 */
- (nullable NSArray<RCMessage *> *)searchMessagesForAllChannel:(RCConversationType)conversationType
                                                      targetId:(NSString *)targetId
                                                       keyword:(NSString *)keyword
                                                         count:(int)count
                                                     startTime:(long long)startTime __deprecated_msg("Use [RCChannelClient searchMessagesForAllChannel:targetId:keyword:count:startTime:completion:] instead");

/*!
 异步搜索指定会话中所有 channelId 的消息

 @param conversationType 会话类型
 @param targetId         会话 ID
 @param keyword           关键字，非空
 @param count            最大的查询数量
 @param startTime        查询 startTime 之前的消息（传 0 表示不限时间）
 @param completion          异步回调[匹配的消息列表]

 @return 匹配的消息列表

 @discussion 超级群会话类型只支持搜索已存储到本地的消息。
 
 @remarks 消息操作
 */
- (void)searchMessagesForAllChannel:(RCConversationType)conversationType
                           targetId:(NSString *)targetId
                            keyword:(NSString *)keyword
                              count:(int)count
                          startTime:(long long)startTime
                         completion:(nullable void(^)(NSArray<RCMessage *> * _Nullable messages))completion;

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
 */
- (nullable NSArray<RCMessage *> *)searchMessagesForAllChannel:(RCConversationType)conversationType
                                                      targetId:(NSString *)targetId
                                                       keyword:(NSString *)keyword
                                                     startTime:(long long)startTime
                                                       endTime:(long long)endTime
                                                        offset:(int)offset
                                                         limit:(int)limit __deprecated_msg("Use [RCChannelClient searchMessagesForAllChannel:targetId:keyword:startTime:endTime:offset:limit:completion:] instead");
/*!
 分页异步搜索指定会话中所有 channelId 在指定时间范围内的消息

 @param conversationType 会话类型
 @param targetId         会话 ID
 @param keyword           关键字，非空
 @param startTime        开始时间（传 0 表示不限时间）
 @param endTime       结束时间，可传入当前 unix 时间，精确到毫秒
 @param offset            偏移量，默认填 0
 @param limit            最大的查询数量
 @param completion          异步回调[匹配的消息列表]


 @discussion 超级群会话类型只支持搜索已存储到本地的消息。
 
 @remarks 消息操作
 */
- (void)searchMessagesForAllChannel:(RCConversationType)conversationType
                           targetId:(NSString *)targetId
                            keyword:(NSString *)keyword
                          startTime:(long long)startTime
                            endTime:(long long)endTime
                             offset:(int)offset
                              limit:(int)limit
                         completion:(nullable void(^)(NSArray<RCMessage *> * _Nullable messages))completion;

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
 */
- (nullable NSArray<RCSearchConversationResult *> *)searchConversations:(NSArray<NSNumber *> *)conversationTypeList
                                                              channelId:(nullable NSString *)channelId
                                                            messageType:(NSArray<NSString *> *)objectNameList
                                                                keyword:(NSString *)keyword __deprecated_msg("Use [RCChannelClient searchConversations:targetId:messageType:keyword:completion:] instead");
/*!
 根据关键字异步搜索会话

 @param conversationTypeList 需要搜索的会话类型列表
 @param channelId          所属会话的业务标识
 @param objectNameList       需要搜索的消息类型名列表(即每个消息类方法 getObjectName 的返回值)
 @param keyword              关键字
 @param completion           异步回调[匹配的会话搜索结果列表]


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
 */
- (void)searchConversations:(NSArray<NSNumber *> *)conversationTypeList
                  channelId:(nullable NSString *)channelId
                messageType:(NSArray<NSString *> *)objectNameList
                    keyword:(NSString *)keyword
                 completion:(nullable void(^)(NSArray<RCSearchConversationResult *> * _Nullable results))completion;

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
 */
- (nullable NSArray<RCSearchConversationResult *> *)searchConversationsForAllChannel:(NSArray<NSNumber *> *)conversationTypeList
                                                                         messageType:(NSArray<NSString *> *)objectNameList
                                                                             keyword:(NSString *)keyword __deprecated_msg("Use [RCChannelClient searchConversationsForAllChannel:messageType:keyword:completion:] instead");

/*!
 根据关键字异步搜索特定会话类型下所有 channelId 的会话

 @param conversationTypeList 需要搜索的会话类型列表
 @param objectNameList       需要搜索的消息类型名列表(即每个消息类方法 getObjectName 的返回值)，不能为 nil
 @param keyword              关键字，非空
 @param completion           异步回调[匹配的会话搜索结果列表]

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
 */
- (void)searchConversationsForAllChannel:(NSArray<NSNumber *> *)conversationTypeList
                             messageType:(NSArray<NSString *> *)objectNameList
                                 keyword:(NSString *)keyword
                              completion:(nullable void(^)(NSArray<RCSearchConversationResult *> * _Nullable results))completion;

#pragma mark - 消息状态


/*!
 设置超级群频道的默认消息状态
 一般由管理员设置的的接口，针对超级群的所有群成员生效，仅针对设置的频道生效，优先级较低。如果群成员自己设置超级群的免打扰级别，那么以群成员自己设置的为准。
 @param targetId                    会话 ID
 @param channelId                   频道 ID
 @param level                       消息通知级别
 @param successBlock                设置成功的回调
 @param errorBlock                  设置失败的回调 [status:设置失败的错误码]

 @remarks 会话
 */
- (void)setUltraGroupConversationChannelDefaultNotificationLevel:(NSString *)targetId
                                                       channelId:(nullable NSString *)channelId
                                                           level:(RCPushNotificationLevel)level
                                                         success:(nullable void (^)(void))successBlock
                                                           error:(nullable void (^)(RCErrorCode status))errorBlock;


/*!
 获取超级群频道的默认消息状态

 @param targetId                    会话 ID
 @param channelId                   频道 ID
 @param successBlock                设置成功的回调 [level:消息通知级别]
 @param errorBlock                  设置失败的回调 [status:设置失败的错误码]

 @remarks 会话
 */
- (void)getUltraGroupConversationChannelDefaultNotificationLevel:(NSString *)targetId
                                                       channelId:(nullable NSString *)channelId
                                                         success:(nullable void (^)(RCPushNotificationLevel level))successBlock
                                                           error:(nullable void (^)(RCErrorCode status))errorBlock;

#pragma mark -- 超级群
/*!
 屏蔽某个时间段的消息提醒
 
 @param startTime       开始消息免打扰时间，格式为 HH:MM:SS
 @param spanMins        需要消息免打扰分钟数，0 < spanMins < 1440（ 比如，您设置的起始时间是 00：00， 结束时间为 01:00，则 spanMins 为 60 分钟。设置为 1439 代表全天免打扰 （23 * 60 + 59 = 1439 ））
 @param level           消息通知级别
 @param successBlock    屏蔽成功的回调
 @param errorBlock      屏蔽失败的回调 [status:屏蔽失败的错误码]
 
 @discussion 此方法设置的屏蔽时间会在每天该时间段时生效。
 
 @remarks 会话
 */
- (void)setNotificationQuietHoursLevel:(NSString *)startTime
                              spanMins:(int)spanMins
                                 level:(RCPushNotificationQuietHoursLevel)level
                               success:(nullable void (^)(void))successBlock
                                 error:(nullable void (^)(RCErrorCode status))errorBlock;


/*!
 查询已设置的时间段消息提醒屏蔽
 
 @param successBlock    屏蔽成功的回调 [startTime:已设置的屏蔽开始时间,
 spanMins:已设置的屏蔽时间分钟数，0 < spanMins < 1440]，level:消息通知级别
 @param errorBlock      查询失败的回调 [status:查询失败的错误码]
 
 @remarks 会话
 */
- (void)getNotificationQuietHoursLevel:(nullable void (^)(NSString *startTime, int spanMins, RCPushNotificationQuietHoursLevel level))successBlock
                                 error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 设置会话的消息提醒状态

 @param conversationType            会话类型
 @param targetId                    会话 ID
 @param level                       消息通知级别
 @param successBlock                设置成功的回调
 @param errorBlock                  设置失败的回调 [status:设置失败的错误码]

@discussion 如要移除消息提醒状态，设置level为RCPushNotificationLevelDefault
 注：超级群调用该接口，相当于设置了 channelId 为 空 的频道的免打扰，不会屏蔽整个超级群会话下所有频道的免打扰

 @remarks 会话
 */
- (void)setConversationNotificationLevel:(RCConversationType)conversationType
                                targetId:(NSString *)targetId
                                   level:(RCPushNotificationLevel)level
                                 success:(nullable void (^)(void))successBlock
                                   error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 获取会话的消息提醒状态

 @param conversationType            会话类型
 @param targetId                    会话 ID
 @param successBlock                设置成功的回调 [level:消息通知级别]
 @param errorBlock                  设置失败的回调 [status:设置失败的错误码]

 @remarks 会话
 */
- (void)getConversationNotificationLevel:(RCConversationType)conversationType
                                targetId:(NSString *)targetId
                                 success:(nullable void (^)(RCPushNotificationLevel level))successBlock
                                   error:(nullable void (^)(RCErrorCode status))errorBlock;


/*!
 设置会话类型的消息提醒状态

 @param conversationType            会话类型
 @param level                       消息通知级别
 @param successBlock                设置成功的回调
 @param errorBlock                  设置失败的回调 [status:设置失败的错误码]

@discussion 如要移除消息提醒状态，设置level为RCPushNotificationLevelDefault

 @remarks 会话
 */

- (void)setConversationTypeNotificationLevel:(RCConversationType)conversationType
                                       level:(RCPushNotificationLevel)level
                                     success:(nullable void (^)(void))successBlock
                                       error:(nullable void (^)(RCErrorCode status))errorBlock;


/*!
 获取会话类型的消息提醒状态

 @param conversationType            会话类型
 @param successBlock                设置成功的回调 [level:消息通知级别]
 @param errorBlock                  设置失败的回调 [status:设置失败的错误码]

 @remarks 会话
 */

- (void)getConversationTypeNotificationLevel:(RCConversationType)conversationType
                                     success:(nullable void (^)(RCPushNotificationLevel level))successBlock
                                       error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 删除已设置的全局时间段消息提醒屏蔽

 @param successBlock    删除屏蔽成功的回调
 @param errorBlock      删除屏蔽失败的回调 [status:失败的错误码]

 @remarks 会话
 */
- (void)removeNotificationQuietHours:(nullable void (^)(void))successBlock
                               error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 拉取超级群列表后回调功能
 
 超级群会话同步状态监听,要在初始化之后, 连接之前设置代理
 @param delegate 代理

 @remarks 超级群消息操作
 */

- (void)setUltraGroupConversationDelegate:(id<RCUltraGroupConversationDelegate>)delegate;

/*!
 超级群频道信息回调功能
 
 @param delegate 代理

 @remarks 超级群频道操作
 */

- (void)setUltraGroupChannelDelegate:(id<RCUltraGroupChannelDelegate>)delegate;


/*!
 获取指定超级群下所有频道的未读消息总数(子线程回调, 如有UI操作, 请切回主线程)

 @param targetId 会话ID
 @param successBlock        获取成功的回调 [消息数量]
 @param errorBlock          获取失败的回调 [status:清除失败的错误码]
 @remarks 超级群消息操作
 */
- (void)getUltraGroupUnreadCount:(NSString *)targetId
                        success:(nullable void (^)(NSInteger  count))successBlock
                          error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 获取超级群会话类型的所有未读消息数 (子线程回调, 如有UI操作, 请切回主线程)
 
 @param successBlock        获取成功的回调 [消息数量]
 @param errorBlock          获取失败的回调 [status:清除失败的错误码]
 @remarks 超级群消息操作
 */
- (void)getUltraGroupAllUnreadCount:(nullable void (^)(NSInteger count))successBlock
                              error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 获取超级群会话类型的@消息未读数接口 (子线程回调, 如有UI操作, 请切回主线程)
 
 @param successBlock        获取成功的回调 [消息数量]
 @param errorBlock          获取失败的回调 [status:清除失败的错误码]
 @remarks 超级群消息操作
 */
- (void)getUltraGroupAllUnreadMentionedCount:(nullable void (^)(NSInteger  count))successBlock
                                       error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 可以获取本地指定超级群下公有频道或者私有频道的列表
 @param targetId            会话ID
 @param channelType         频道类型
 @param successBlock        获取成功的回调 [会话列表]
 @param errorBlock          获取失败的回调 [status:清除失败的错误码]
 @remarks 超级群消息操作
 */
- (void)getUltraGroupChannelList:(NSString *)targetId
                     channelType:(RCUltraGroupChannelType)channelType
                         success:(nullable void (^)(NSArray<RCConversation *>* list))successBlock
                           error:(nullable void (^)(RCErrorCode status))errorBlock;
#pragma mark - 未读数
/*!
  获取会话未读消息数 (子线程回调, 如有UI操作, 请切回主线程)
  @param conversationTypes   会话类型数组：[单聊、群聊、超级群]
  @param levels              免打扰类型数组 [RCPushNotificationLevel]
  @param successBlock        获取成功的回调 [消息数量]
  @param errorBlock          获取失败的回调 [status:失败的错误码]
  @remarks 单聊、群聊、超级群消息操作
  @since 5.2.5
 */
- (void)getUnreadCount:(nonnull NSArray <NSNumber*>*)conversationTypes
                levels:(nonnull NSArray <NSNumber*>*)levels
               success:(nullable void (^)(NSInteger count))successBlock
                 error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 获取获取会话未读 @消息数 (子线程回调, 如有UI操作, 请切回主线程)
 @param conversationTypes   会话类型数组：[群聊、超级群]
 @param levels              免打扰类型数组 [RCPushNotificationLevel]
 @param successBlock        获取成功的回调 [消息数量]
 @param errorBlock          获取失败的回调 [status:失败的错误码]
 @remarks 群聊、超级群消息操作
 @since 5.2.5
 */
- (void)getUnreadMentionedCount:(nonnull NSArray <NSNumber*>*)conversationTypes
                         levels:(nonnull NSArray <NSNumber*>*)levels
                        success:(nullable void (^)(NSInteger count))successBlock
                          error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 获取指定超级群会话的未读消息数（包括所有频道) (子线程回调, 如有UI操作, 请切回主线程)
 @param targetId            超级群会话ID
 @param levels              免打扰类型数组 [RCPushNotificationLevel]
 @param successBlock        获取成功的回调 [消息数量]
 @param errorBlock          获取失败的回调 [status:失败的错误码]
 @remarks 超级群消息操作
 @since 5.2.5
 */
- (void)getUltraGroupUnreadCount:(nonnull NSString *)targetId
                          levels:(nonnull NSArray <NSNumber*>*)levels
                         success:(nullable void (^)(NSInteger count))successBlock
                           error:(nullable void (^)(RCErrorCode status))errorBlock;


/*!
 获取指定超级群会话的未读@消息数（包括所有频道） (子线程回调, 如有UI操作, 请切回主线程)
 @param targetId            超级群会话ID
 @param levels              免打扰类型数组 [RCPushNotificationLevel]
 @param successBlock        获取成功的回调 [消息数量]
 @param errorBlock          获取失败的回调 [status:失败的错误码]
 @remarks 超级群消息操作
 @since 5.2.5
 */
- (void)getUltraGroupUnreadMentionedCount:(nonnull NSString *)targetId
                                   levels:(nonnull NSArray <NSNumber*>*)levels
                                  success:(nullable void (^)(NSInteger count))successBlock
                                    error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
获取超级群会话类型未读的 @ 消息摘要列表接口 (子线程回调, 如有UI操作, 请切回主线程)
@param targetId            会话 ID
@param channelId           所属会话的业务标识
@param sendTime            消息发送的时间[毫秒,0代表从第一条开始查询]
@param count               查询数量 [1 - 50], 超过范围上报 INVALID_PARAMETER_COUNT 错误码
@param successBlock        获取成功的回调 [消息摘要列表]
@param errorBlock          获取失败的回调 [status:失败的错误码]
@remarks 超级群消息操作
@since 5.2.5
*/
- (void)getUltraGroupUnreadMentionedDigests:(nonnull NSString *)targetId
                                  channelId:(nullable NSString *)channelId
                                   sendTime:(long long)sendTime
                                     count:(NSInteger)count
                                    success:(nullable void (^)(NSArray<RCMessageDigestInfo*>* digests))successBlock
                                      error:(nullable void (^)(RCErrorCode status))errorBlock;
@end

NS_ASSUME_NONNULL_END
