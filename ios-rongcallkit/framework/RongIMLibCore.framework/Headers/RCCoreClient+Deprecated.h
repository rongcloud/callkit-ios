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
 - Since: 5.4.1
 - Warning: 本文件的方法已经过期，请您替换 RCCoreClient 中的方法。
 */
@interface RCCoreClient (Deprecated)

#pragma mark - SDK初始化

/// 初始化融云 SDK
///
/// - Parameter appKey: 从融云开发者平台创建应用后获取到的 App Key
/// 初始化后，SDK 会监听 app 生命周期，用于判断应用处于前台、后台，根据前后台状态调整链接心跳
///
/// 您在使用融云 SDK 所有功能（包括显示 SDK 中或者继承于 SDK 的 View）之前，您必须先调用此方法初始化 SDK。
/// 在 App 整个生命周期中，您只需要执行一次初始化。
///
/// **升级说明:**
/// **从 2.4.1 版本开始，为了兼容 Swift 的风格与便于使用，将原有的 init: 方法升级为此方法，方法的功能和使用均不变。**
///
/// - Warning: 如果您使用 IMLibCore，请使用此方法初始化 SDK；
/// 如果您使用 IMKit，请使用 RCIM 中的同名方法初始化，而不要使用此方法。
///
/// - Remark: 连接
/// - Since: 5.0.0
- (void)initWithAppKey:(NSString *)appKey __deprecated_msg("Use [RCCoreClient initWithAppKey:option:] instead");

#pragma mark-- 监听器

/// 设置 IMLibCore 的连接状态监听器
///
/// - Parameter delegate: IMLibCore 连接状态监听器
///
/// - Warning: 如果您使用 IMLibCore，可以设置并实现此 Delegate 监听连接状态变化；
/// 如果您使用 IMKit，请使用 RCIM 中的 connectionStatusDelegate 监听连接状态变化，而不要使用此方法，否则会导致 IMKit
/// 中无法自动更新 UI！
///
/// - Remark: 功能设置
/// - Since: 5.0.0
- (void)setRCConnectionStatusChangeDelegate:(id<RCConnectionStatusChangeDelegate>)delegate
    __deprecated_msg("Use [RCCoreClient addConnectionStatusChangeDelegate:] instead");

/// 设置 IMLibCore 的消息接收监听器
///
/// - Parameter delegate: IMLibCore 消息接收监听器
/// - Parameter userData: 用户自定义的监听器 Key 值，可以为 nil
///
///
/// 设置 IMLibCore 的消息接收监听器请参考 RCCoreClient 的 setReceiveMessageDelegate:object:方法。
///
/// - Warning: 如果您使用 IMLibCore，可以设置并实现此 Delegate 监听消息接收；
/// 如果您使用 IMKit，请使用 RCIM 中的 receiveMessageDelegate 监听消息接收，而不要使用此方法，否则会导致 IMKit
/// 中无法自动更新 UI！
///
/// - Remark: 功能设置
/// - Since: 5.0.0
- (void)setReceiveMessageDelegate:(id<RCIMClientReceiveMessageDelegate>)delegate
                           object:(nullable id)userData
    __deprecated_msg("Use [RCCoreClient addReceiveMessageDelegate:] instead");

#pragma mark - 设置导航服务器和上传文件服务器(仅限独立数据中心使用，使用前必须先联系商务开通)

/// 设置导航服务器和上传文件服务器信息
///
/// - Parameter naviServer: 导航服务器地址，具体的格式参考下面的说明
/// - Parameter fileServer: 文件服务器地址，具体的格式参考下面的说明
/// - Returns: 是否设置成功
///
/// - Warning: 仅限独立数据中心使用，使用前必须先联系商务开通。必须在 SDK init 之前进行设置。
///
/// naviServer 必须为有效的服务器地址，fileServer 如果想使用默认的，可以传 nil。
/// naviServer 和 fileServer 的格式说明：
/// 1. 如果使用 https，则设置为 https://cn.xxx.com:port" 或 https://cn.xxx.com 或  cn.xxx.com【SDK 默认使用 https】，其中域名部分也可以是 IP，如果不指定端口，将默认使用 443 端口。
/// 2. 如果使用 http，则设置为 http://cn.xxx.com:port 或 http://cn.xxx.com 格式，其中域名部分也可以是 IP，如果不指定端口，将默认使用 80
/// 端口。（iOS 默认只能使⽤ HTTPS 协议。如果您使⽤ http 协议，请参考 iOS 官方开发
/// ⽂档中的 ATS 设置说明。链接如下：https://developer.apple.com/documentation/security/preventing_insecure_network_connections#3138036）
///
/// 本接口和 initWithAppKey:option: 中 RCInitOption 传入的 naviServer 和 fileServer 效果一致，任一种设置都生效
///
/// - Remark: 功能设置
/// - Since: 5.0.0
- (BOOL)setServerInfo:(NSString *)naviServer
           fileServer:(nullable NSString *)fileServer
    __deprecated_msg("Use [RCCoreClient initWithAppKey:option:] instead");

/// 设置统计服务器的信息
///
/// - Parameter statisticServer: 统计服务器地址，具体的格式参考下面的说明
/// - Returns: 是否设置成功
///
/// - Warning: 仅限独立数据中心使用，使用前必须先联系商务开通。必须在 SDK init 和 setDeviceToken 之前进行设置。
///
/// statisticServer 必须为有效的服务器地址，否则会造成推送等业务不能正常使用。
/// 格式说明：
/// 1、如果使用 https，则设置为 https://cn.xxx.com:port 或 https://cn.xxx.com 或  cn.xxx.com【SDK 默认使用 https】，其中域名部分也可以是 IP，如果不指定端口，将默认使用 443 端口。
/// 2、如果使用 http，则设置为 http://cn.xxx.com:port 或 http://cn.xxx.com 格式，其中域名部分也可以是 IP，如果不指定端口，将默认使用 80
/// 端口。（iOS 默认只能使⽤ HTTPS 协议。如果您使⽤ http 协议，请参考 iOS 官方开发
/// ⽂档中的 ATS 设置说明。链接如下：https://developer.apple.com/documentation/security/preventing_insecure_network_connections#3138036）
/// 本接口和 initWithAppKey:option: 中 RCInitOption 传入的 statisticServer 效果一致，任一种设置都生效
///
/// - Remark: 功能设置
/// - Since: 5.0.0
- (BOOL)setStatisticServer:(NSString *)statisticServer
    __deprecated_msg("Use [RCCoreClient initWithAppKey:option:] instead");


#pragma mark-- config
/**
 语音消息采样率，默认 8KHz

 
 2.9.12 之前的版本只支持 8KHz。如果设置为 16KHz，老版本将无法播放 16KHz 的语音消息。
 客服会话只支持 8KHz。

 - Remark: 功能设置
 - Since: 5.0.0
 */
@property (nonatomic, assign) RCSampleRate sampleRate __attribute__((deprecated));

#pragma mark - 消息发送 -

/*!
 发送消息
 
 - Parameter conversationType: 发送消息的会话类型
 - Parameter targetId: 发送消息的会话 ID
 - Parameter content: 消息的内容
 - Parameter pushContent: 接收方离线时需要显示的远程推送内容
 - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
 - Parameter successBlock: 消息发送成功的回调 [messageId: 消息的 ID]
 - Parameter errorBlock: 消息发送失败的回调 [nErrorCode: 发送失败的错误码,
 messageId:消息的ID]
 - Returns: 发送的消息实体
 
 当接收方离线并允许远程推送时，会收到远程推送。
 远程推送中包含两部分内容，一是 pushContent ，用于显示；二是 pushData ，用于携带不显示的数据。
 
 SDK 内置的消息类型，如果您将 pushContent 和 pushData 置为 nil ，会使用默认的推送格式进行远程推送。
 自定义类型的消息，需要您自己设置 pushContent 和 pushData 来定义推送内容，否则将不会进行远程推送。
 
 如果您使用此方法发送图片消息，需要您自己实现图片的上传，构建一个 RCImageMessage 对象，
 并将 RCImageMessage 中的 imageUrl 字段设置为上传成功的 URL 地址，然后使用此方法发送。
 
 如果您使用此方法发送文件消息，需要您自己实现文件的上传，构建一个 RCFileMessage 对象，
 并将 RCFileMessage 中的 fileUrl 字段设置为上传成功的 URL 地址，然后使用此方法发送。
 
 - Warning: 如果您使用 IMLibCore，可以使用此方法发送消息；
 如果您使用 IMKit，请使用 RCIM 中的同名方法发送消息，否则不会自动更新 UI。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (nullable RCMessage *)sendMessage:(RCConversationType)conversationType
                           targetId:(NSString *)targetId
                            content:(RCMessageContent *)content
                        pushContent:(nullable NSString *)pushContent
                           pushData:(nullable NSString *)pushData
                            success:(nullable void (^)(long messageId))successBlock
                              error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock
    __deprecated_msg(
        "Use [RCCoreClient sendMessage:targetId:content:pushContent:pushData:attached:success:error:] instead");

/*!
 发送消息
 
 - Parameter conversationType: 发送消息的会话类型
 - Parameter targetId: 发送消息的会话 ID
 - Parameter content: 消息的内容
 - Parameter pushContent: 接收方离线时需要显示的远程推送内容
 - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
 - Parameter option: 消息的相关配置
 - Parameter successBlock: 消息发送成功的回调 [messageId: 消息的 ID]
 - Parameter errorBlock: 消息发送失败的回调 [nErrorCode: 发送失败的错误码,
 messageId: 消息的 ID]
 - Returns: 发送的消息实体
 
 当接收方离线并允许远程推送时，会收到远程推送。
 远程推送中包含两部分内容，一是 pushContent，用于显示；二是 pushData，用于携带不显示的数据。
 
 SDK 内置的消息类型，如果您将 pushContent 和 pushData 置为 nil，会使用默认的推送格式进行远程推送。
 自定义类型的消息，需要您自己设置 pushContent 和 pushData 来定义推送内容，否则将不会进行远程推送。
 
 如果您使用此方法发送图片消息，需要您自己实现图片的上传，构建一个 RCImageMessage 对象，
 并将 RCImageMessage 中的 imageUrl 字段设置为上传成功的 URL 地址，然后使用此方法发送。
 
 如果您使用此方法发送文件消息，需要您自己实现文件的上传，构建一个 RCFileMessage 对象，
 并将 RCFileMessage 中的 fileUrl 字段设置为上传成功的 URL 地址，然后使用此方法发送。
 
 - Warning: 如果您使用 IMLibCore，可以使用此方法发送消息；
 如果您使用 IMKit，请使用 RCIM 中的同名方法发送消息，否则不会自动更新 UI。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (nullable RCMessage *)sendMessage:(RCConversationType)conversationType
                           targetId:(NSString *)targetId
                            content:(RCMessageContent *)content
                        pushContent:(nullable NSString *)pushContent
                           pushData:(nullable NSString *)pushData
                             option:(RCSendMessageOption *)option
                            success:(nullable void (^)(long messageId))successBlock
                              error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock
    __deprecated_msg(
        "Use [RCCoreClient sendMessage:targetId:content:pushContent:pushData:option:attached:success:error:] instead");

/*!
 发送媒体消息（图片消息或文件消息）
 
 - Parameter conversationType: 发送消息的会话类型
 - Parameter targetId: 发送消息的会话 ID
 - Parameter content: 消息的内容
 - Parameter pushContent: 接收方离线时需要显示的远程推送内容
 - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
 - Parameter progressBlock: 消息发送进度更新的回调 [progress:当前的发送进度, 0
 <= progress <= 100, messageId:消息的 ID]
 - Parameter successBlock: 消息发送成功的回调 [messageId:消息的 ID]
 - Parameter errorBlock: 消息发送失败的回调 [errorCode:发送失败的错误码,
 messageId:消息的 ID]
 - Parameter cancelBlock: 用户取消了消息发送的回调 [messageId:消息的 ID]
 - Returns: 发送的消息实体
 
 当接收方离线并允许远程推送时，会收到远程推送。
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
 
 - Warning: 如果您使用 IMLibCore，可以使用此方法发送媒体消息；
 如果您使用 IMKit，请使用 RCIM 中的同名方法发送媒体消息，否则不会自动更新 UI。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (nullable RCMessage *)sendMediaMessage:(RCConversationType)conversationType
                                targetId:(NSString *)targetId
                                 content:(RCMessageContent *)content
                             pushContent:(nullable NSString *)pushContent
                                pushData:(nullable NSString *)pushData
                                progress:(nullable void (^)(int progress, long messageId))progressBlock
                                 success:(nullable void (^)(long messageId))successBlock
                                   error:(nullable void (^)(RCErrorCode errorCode, long messageId))errorBlock
                                  cancel:(nullable void (^)(long messageId))cancelBlock
    __deprecated_msg(
        "Use [RCCoreClient "
        "sendMediaMessage:targetId:content:pushContent:pushData:attached:progress:success:error:cancel:] instead");

/*!
 发送媒体消息(上传图片或文件等媒体信息到指定的服务器)
 
 - Parameter conversationType: 发送消息的会话类型
 - Parameter targetId: 发送消息的会话 ID
 - Parameter content: 消息的内容
 - Parameter pushContent: 接收方离线时需要显示的远程推送内容
 - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
 - Parameter uploadPrepareBlock: 媒体文件上传进度更新的监听
 [uploadListener:当前的发送进度监听]
 - Parameter progressBlock: 消息发送进度更新的回调 [progress:当前的发送进度, 0
 <= progress <= 100, messageId:消息的ID]
 - Parameter successBlock: 消息发送成功的回调 [messageId:消息的 ID]
 - Parameter errorBlock: 消息发送失败的回调 [errorCode:发送失败的错误码,
 messageId:消息的 ID]
 - Parameter cancelBlock: 用户取消了消息发送的回调 [messageId:消息的 ID]
 - Returns: 发送的消息实体
 
 
 如果您需要上传图片到自己的服务器并使用 IMLibCore，构建一个 RCImageMessage 对象，
 并将 RCImageMessage 中的 imageUrl 字段设置为上传成功的 URL 地址，然后使用 RCCoreClient 的
 sendMessage:targetId:content:pushContent:pushData:success:error:方法
 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。
 
 如果您需要上传文件到自己的服务器并使用 IMLibCore，构建一个 RCFileMessage 对象，
 并将 RCFileMessage 中的 fileUrl 字段设置为上传成功的 URL 地址，然后使用 RCCoreClient 的
 sendMessage:targetId:content:pushContent:pushData:success:error:方法
 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (nullable RCMessage *)sendMediaMessage:(RCConversationType)conversationType
                                targetId:(NSString *)targetId
                                 content:(RCMessageContent *)content
                             pushContent:(nullable NSString *)pushContent
                                pushData:(nullable NSString *)pushData
                           uploadPrepare:
                               (nullable void (^)(RCUploadMediaStatusListener *uploadListener))uploadPrepareBlock
                                progress:(nullable void (^)(int progress, long messageId))progressBlock
                                 success:(nullable void (^)(long messageId))successBlock
                                   error:(nullable void (^)(RCErrorCode errorCode, long messageId))errorBlock
                                  cancel:(nullable void (^)(long messageId))cancelBlock
    __deprecated_msg("Use [RCCoreClient "
                     "sendMediaMessage:targetId:content:pushContent:pushData:attached:uploadPrepare:progress:success:"
                     "error:cancel:] instead");

/*!
 发送消息
 
 - Parameter message: 将要发送的消息实体（需要保证 message 中的 conversationType，targetId，messageContent 是有效值)
 - Parameter pushContent: 接收方离线时需要显示的远程推送内容
 - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
 - Parameter successBlock: 消息发送成功的回调 [successMessage: 消息实体]
 - Parameter errorBlock: 消息发送失败的回调 [nErrorCode: 发送失败的错误码, errorMessage:消息实体]
 - Returns: 发送的消息实体
 
 当接收方离线并允许远程推送时，会收到远程推送。
 远程推送中包含两部分内容，一是 pushContent ，用于显示；二是 pushData ，用于携带不显示的数据。
 
 SDK 内置的消息类型，如果您将 pushContent 和 pushData 置为 nil ，会使用默认的推送格式进行远程推送。
 自定义类型的消息，需要您自己设置 pushContent 和 pushData 来定义推送内容，否则将不会进行远程推送。
 
 如果您使用此方法发送图片消息，需要您自己实现图片的上传，构建一个 RCImageMessage 对象，
 并将 RCImageMessage 中的 imageUrl 字段设置为上传成功的 URL 地址，然后使用此方法发送。
 
 如果您使用此方法发送文件消息，需要您自己实现文件的上传，构建一个 RCFileMessage 对象，
 并将 RCFileMessage 中的 fileUrl 字段设置为上传成功的 URL 地址，然后使用此方法发送。
 
 - Warning: 如果您使用 IMLibCore，可以使用此方法发送消息；
 如果您使用 IMKit，请使用 RCIM 中的同名方法发送消息，否则不会自动更新 UI。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (nullable RCMessage *)sendMessage:(RCMessage *)message
                        pushContent:(nullable NSString *)pushContent
                           pushData:(nullable NSString *)pushData
                       successBlock:(nullable void (^)(RCMessage *successMessage))successBlock
                         errorBlock:(nullable void (^)(RCErrorCode nErrorCode, RCMessage *errorMessage))errorBlock
    __deprecated_msg("Use [RCCoreClient sendMessage: pushContent:pushData:attached:successBlock:errorBlock:] instead");

/*!
 发送媒体消息(上传图片或文件等媒体信息到指定的服务器)
 
 - Parameter message: 将要发送的消息实体（需要保证 message 中的 conversationType，targetId，messageContent 是有效值)
 - Parameter pushContent: 接收方离线时需要显示的远程推送内容
 - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
 - Parameter uploadPrepareBlock: 媒体文件上传进度更新的监听
 [uploadListener:当前的发送进度监听]
 - Parameter progressBlock: 消息发送进度更新的回调 [progress:当前的发送进度, 0
 <= progress <= 100, messageId:消息的ID]
 - Parameter successBlock: 消息发送成功的回调 [messageId:消息的 ID]
 - Parameter errorBlock: 消息发送失败的回调 [errorCode:发送失败的错误码,
 messageId:消息的 ID]
 - Parameter cancelBlock: 用户取消了消息发送的回调 [messageId:消息的 ID]
 - Returns: 发送的消息实体
 
 
 如果您需要上传图片到自己的服务器并使用 IMLibCore，构建一个 RCImageMessage 对象，
 并将 RCImageMessage 中的 imageUrl 字段设置为上传成功的 URL 地址，然后使用 RCCoreClient 的
 sendMessage:targetId:content:pushContent:pushData:success:error:方法
 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。
 
 如果您需要上传文件到自己的服务器并使用 IMLibCore，构建一个 RCFileMessage 对象，
 并将 RCFileMessage 中的 fileUrl 字段设置为上传成功的 URL 地址，然后使用 RCCoreClient 的
 sendMessage:targetId:content:pushContent:pushData:success:error:方法
 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。
 
 - Remark: 消息操作
 - Since: 5.2.1
 */
- (nullable RCMessage *)sendMediaMessage:(RCMessage *)message
                             pushContent:(nullable NSString *)pushContent
                                pushData:(nullable NSString *)pushData
                           uploadPrepare:
                               (nullable void (^)(RCUploadMediaStatusListener *uploadListener))uploadPrepareBlock
                                progress:(nullable void (^)(int progress, long messageId))progressBlock
                                 success:(nullable void (^)(long messageId))successBlock
                                   error:(nullable void (^)(RCErrorCode errorCode, long messageId))errorBlock
                                  cancel:(nullable void (^)(long messageId))cancelBlock
    __deprecated_msg(
        "Use [RCCoreClient "
        "sendMediaMessage:pushContent:pushData:attached:uploadPrepare:progress:success:error:cancel:] instead");

/*!
 发送媒体消息（图片消息或文件消息）
 
 - Parameter message: 将要发送的消息实体（需要保证 message 中的 conversationType，targetId，messageContent 是有效值)
 - Parameter pushContent: 接收方离线时需要显示的远程推送内容
 - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
 - Parameter progressBlock: 消息发送进度更新的回调 [progress:当前的发送进度, 0 <= progress <= 100, progressMessage:消息实体]
 - Parameter successBlock: 消息发送成功的回调 [successMessage:消息实体]
 - Parameter errorBlock: 消息发送失败的回调 [nErrorCode:发送失败的错误码, errorMessage:消息实体]
 - Parameter cancelBlock: 用户取消了消息发送的回调 [cancelMessage:消息实体]
 - Returns: 发送的消息实体
 
 当接收方离线并允许远程推送时，会收到远程推送。
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
 
 - Warning: 如果您使用 IMLibCore，可以使用此方法发送媒体消息；
 如果您使用 IMKit，请使用 RCIM 中的同名方法发送媒体消息，否则不会自动更新 UI。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (nullable RCMessage *)sendMediaMessage:(RCMessage *)message
                             pushContent:(nullable NSString *)pushContent
                                pushData:(nullable NSString *)pushData
                                progress:(nullable void (^)(int progress, RCMessage *progressMessage))progressBlock
                            successBlock:(nullable void (^)(RCMessage *successMessage))successBlock
                              errorBlock:(nullable void (^)(RCErrorCode nErrorCode, RCMessage *errorMessage))errorBlock
                                  cancel:(nullable void (^)(RCMessage *cancelMessage))cancelBlock
    __deprecated_msg(
        "Use [RCCoreClient sendMediaMessage:pushContent:pushData:attached:progress:successBlock:errorBlock:cancel:] "
        "instead");

#pragma mark - 插入消息 -

/*!
 插入向外发送的消息（该消息只插入本地数据库，实际不会发送给服务器和对方）
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话 ID
 - Parameter sentStatus: 发送状态
 - Parameter content: 消息的内容
 - Returns: 插入的消息实体
 
 此方法不支持聊天室的会话类型。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (nullable RCMessage *)insertOutgoingMessage:(RCConversationType)conversationType
                                     targetId:(NSString *)targetId
                                   sentStatus:(RCSentStatus)sentStatus
                                      content:(RCMessageContent *)content
    __deprecated_msg("Use [RCCoreClient insertOutgoingMessage:targetId:sentStatus:content:completion:] instead");

/*!
 插入向外发送的、指定时间的消息（此方法如果 sentTime 有问题会影响消息排序，慎用！！）
 （该消息只插入本地数据库，实际不会发送给服务器和对方）
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话 ID
 - Parameter sentStatus: 发送状态
 - Parameter content: 消息的内容
 - Parameter sentTime: 消息发送的 Unix 时间戳，单位为毫秒（传 0 会按照本地时间插入）
 - Returns: 插入的消息实体
 
 此方法不支持聊天室的会话类型。如果 sentTime<=0，则被忽略，会以插入时的时间为准。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (nullable RCMessage *)insertOutgoingMessage:(RCConversationType)conversationType
                                     targetId:(NSString *)targetId
                                   sentStatus:(RCSentStatus)sentStatus
                                      content:(RCMessageContent *)content
                                     sentTime:(long long)sentTime
    __deprecated_msg(
        "Use [RCCoreClient insertOutgoingMessage:targetId:sentStatus:content:sentTime:completion:] instead");

/*!
 插入接收的消息（该消息只插入本地数据库，实际不会发送给服务器和对方）
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话 ID
 - Parameter senderUserId: 发送者 ID
 - Parameter receivedStatus: 接收状态
 - Parameter content: 消息的内容
 - Returns: 插入的消息实体
 
 此方法不支持聊天室的会话类型。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (nullable RCMessage *)insertIncomingMessage:(RCConversationType)conversationType
                                     targetId:(NSString *)targetId
                                 senderUserId:(NSString *)senderUserId
                               receivedStatus:(RCReceivedStatus)receivedStatus
                                      content:(RCMessageContent *)content
    __deprecated_msg("Use [RCCoreClient "
                     "insertIncomingMessage:targetId:senderUserId:receivedStatusInfo:content:completion:] instead");

/*!
 插入接收的消息（此方法如果 sentTime
 有问题会影响消息排序，慎用！！）（该消息只插入本地数据库，实际不会发送给服务器和对方）
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话 ID
 - Parameter senderUserId: 发送者 ID
 - Parameter receivedStatus: 接收状态
 - Parameter content: 消息的内容
 - Parameter sentTime: 消息发送的 Unix 时间戳，单位为毫秒 （传 0 会按照本地时间插入）
 - Returns: 插入的消息实体
 
 此方法不支持聊天室的会话类型。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (nullable RCMessage *)insertIncomingMessage:(RCConversationType)conversationType
                                     targetId:(NSString *)targetId
                                 senderUserId:(NSString *)senderUserId
                               receivedStatus:(RCReceivedStatus)receivedStatus
                                      content:(RCMessageContent *)content
                                     sentTime:(long long)sentTime
    __deprecated_msg(
        "Use [RCCoreClient "
        "insertIncomingMessage:targetId:senderUserId:receivedStatusInfo:content:sentTime:completion:] instead");

/// 异步插入接收的消息（该消息只插入本地数据库，实际不会发送给服务器和对方）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter senderUserId: 发送者 ID
/// - Parameter receivedStatus: 接收状态
/// - Parameter content: 消息的内容
/// - Parameter completion: 异步回调 [message: 发送的消息实体]
///
/// 此方法不支持聊天室的会话类型。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)insertIncomingMessage:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                 senderUserId:(NSString *)senderUserId
               receivedStatus:(RCReceivedStatus)receivedStatus
                      content:(RCMessageContent *)content
                   completion:(nullable void (^)(RCMessage *_Nullable message))completion
    __deprecated_msg(
        "Use [RCCoreClient insertIncomingMessage:targetId:senderUserId:receivedStatusInfo:content:completion] instead");

/// 异步插入接收的消息（此方法如果 sentTime
/// 有问题会影响消息排序，慎用！！）（该消息只插入本地数据库，实际不会发送给服务器和对方）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter senderUserId: 发送者 ID
/// - Parameter receivedStatus: 接收状态
/// - Parameter content: 消息的内容
/// - Parameter sentTime: 消息发送的 Unix 时间戳，单位为毫秒（传 0 会按照本地时间插入）
/// - Parameter completion: 异步回调 [message: 发送的消息实体]
///
/// 此方法不支持聊天室的会话类型。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)insertIncomingMessage:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                 senderUserId:(NSString *)senderUserId
               receivedStatus:(RCReceivedStatus)receivedStatus
                      content:(RCMessageContent *)content
                     sentTime:(long long)sentTime
                   completion:(nullable void (^)(RCMessage *_Nullable message))completion
    __deprecated_msg(
        "Use [RCCoreClient insertIncomingMessage:targetId:senderUserId:receivedStatusInfo:content:sentTime:completion] "
        "instead");

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
 
 此方法不支持聊天室的会话类型。每批最多处理  500 条消息，超过 500 条返回 NO
 消息的未读会累加到会话的未读数上

 - Remark: 消息操作
 - Since: 5.1.1
 */
- (BOOL)batchInsertMessage:(NSArray<RCMessage *> *)msgs
    __deprecated_msg("Use [RCCoreClient batchInsertMessage:completion:] instead");

#pragma mark - 定向消息 -

/*!
 发送定向消息
 
 - Parameter conversationType: 发送消息的会话类型
 - Parameter targetId: 发送消息的会话 ID
 - Parameter userIdList: 接收消息的用户 ID 列表
 - Parameter content: 消息的内容
 - Parameter pushContent: 接收方离线时需要显示的远程推送内容
 - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
 - Parameter successBlock: 消息发送成功的回调 [messageId:消息的 ID]
 - Parameter errorBlock: 消息发送失败的回调 [errorCode:发送失败的错误码,
 messageId:消息的 ID]
 
 - Returns: 发送的消息实体
 
 此方法用于在群组和讨论组中发送消息给其中的部分用户，其它用户不会收到这条消息。
 如果您使用 IMLibCore，可以使用此方法发送定向消息；
 如果您使用 IMKit，请使用 RCIM 中的同名方法发送定向消息，否则不会自动更新 UI。
 userIdList里ID个数不能超过300，超过会被截断。
 
 - Warning: 此方法目前仅支持普通群组和讨论组。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (nullable RCMessage *)sendDirectionalMessage:(RCConversationType)conversationType
                                      targetId:(NSString *)targetId
                                  toUserIdList:(NSArray<NSString *> *)userIdList
                                       content:(RCMessageContent *)content
                                   pushContent:(nullable NSString *)pushContent
                                      pushData:(nullable NSString *)pushData
                                       success:(nullable void (^)(long messageId))successBlock
                                         error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock
    __deprecated_msg(
        "Use [RCCoreClient "
        "sendDirectionalMessage:targetId:toUserIdList:content:pushContent:pushData:attached:success:error:] instead");

/*!
 发送定向消息
 
 - Parameter message: 消息实体
 - Parameter userIdList: 接收消息的用户 ID 列表
 - Parameter pushContent: 接收方离线时需要显示的远程推送内容
 - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
 - Parameter successBlock: 消息发送成功的回调 [successMessage:发送成功的消息]
 - Parameter errorBlock: 消息发送失败的回调 [nErrorCode:发送失败的错误码,errorMessage:发送失败的消息]
 
 - Returns: 发送的消息实体
 
 此方法用于在群组和讨论组中发送消息给其中的部分用户，其它用户不会收到这条消息。
 userIdList里ID个数不能超过300，超过会被截断。
 
 - Warning: 此方法目前仅支持普通群组和讨论组。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (nullable RCMessage *)sendDirectionalMessage:(RCMessage *)message
                                  toUserIdList:(NSArray<NSString *> *)userIdList
                                   pushContent:(nullable NSString *)pushContent
                                      pushData:(nullable NSString *)pushData
                                  successBlock:(nullable void (^)(RCMessage *successMessage))successBlock
                                    errorBlock:
                                        (nullable void (^)(RCErrorCode nErrorCode, RCMessage *errorMessage))errorBlock
    __deprecated_msg(
        "Use [RCCoreClient sendDirectionalMessage:toUserIdList:pushContent:pushData:attached:successBlock:errorBlock:] "
        "instead");

/*!
 发送定向消息
 
 - Parameter message: 消息实体
 - Parameter userIdList: 接收消息的用户 ID 列表
 - Parameter pushContent: 接收方离线时需要显示的远程推送内容
 - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
 - Parameter option: 消息的相关配置
 - Parameter successBlock: 消息发送成功的回调 [successMessage:发送成功的消息]
 - Parameter errorBlock: 消息发送失败的回调 [nErrorCode:发送失败的错误码,errorMessage:发送失败的消息]
 
 - Returns: 发送的消息实体
 
 此方法用于在群组和讨论组中发送消息给其中的部分用户，其它用户不会收到这条消息。
 userIdList里ID个数不能超过300，超过会被截断。
 
 - Warning: 此方法目前仅支持普通群组和讨论组。
 
 - Remark: 消息操作
 - Since: 5.1.2
 */
- (nullable RCMessage *)sendDirectionalMessage:(RCMessage *)message
                                  toUserIdList:(NSArray<NSString *> *)userIdList
                                   pushContent:(nullable NSString *)pushContent
                                      pushData:(nullable NSString *)pushData
                                        option:(RCSendMessageOption *)option
                                  successBlock:(nullable void (^)(RCMessage *successMessage))successBlock
                                    errorBlock:
                                        (nullable void (^)(RCErrorCode nErrorCode, RCMessage *errorMessage))errorBlock
    __deprecated_msg(
        "Use [RCCoreClient "
        "sendDirectionalMessage:toUserIdList:pushContent:pushData:option:attached:successBlock:errorBlock:] instead");

/*!
 发送定向媒体消息（图片消息或文件消息）
 
 - Parameter message: 将要发送的消息实体（需要保证 message 中的 conversationType，targetId，messageContent 是有效值)
 - Parameter userIdList: 接收消息的用户 ID 列表
 - Parameter pushContent: 接收方离线时需要显示的远程推送内容
 - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
 - Parameter progressBlock: 消息发送进度更新的回调 [progress:当前的发送进度, 0 <= progress <= 100, progressMessage:消息实体]
 - Parameter successBlock: 消息发送成功的回调 [successMessage:消息实体]
 - Parameter errorBlock: 消息发送失败的回调 [nErrorCode:发送失败的错误码, errorMessage:消息实体]
 - Parameter cancelBlock: 用户取消了消息发送的回调 [cancelMessage:消息实体]
 - Returns: 发送的消息实体
 
 当接收方离线并允许远程推送时，会收到远程推送。
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
 
 - Warning: 如果您使用 IMLib，可以使用此方法发送媒体消息；
 如果您使用 IMKit，请使用 RCIM 中的同名方法发送媒体消息，否则不会自动更新 UI。
 
 - Remark: 消息操作
 - Since: 5.2.5
 */
- (nullable RCMessage *)
    sendDirectionalMediaMessage:(RCMessage *)message
                   toUserIdList:(NSArray<NSString *> *)userIdList
                    pushContent:(nullable NSString *)pushContent
                       pushData:(nullable NSString *)pushData
                       progress:(nullable void (^)(int progress, RCMessage *progressMessage))progressBlock
                   successBlock:(nullable void (^)(RCMessage *successMessage))successBlock
                     errorBlock:(nullable void (^)(RCErrorCode nErrorCode, RCMessage *errorMessage))errorBlock
                         cancel:(nullable void (^)(RCMessage *cancelMessage))cancelBlock
    __deprecated_msg("Use [RCCoreClient "
                     "sendDirectionalMediaMessage:toUserIdList:pushContent:pushData:attached:progress:successBlock:"
                     "errorBlock:cancel:] instead");

#pragma mark - 消息操作 -

/*!
 获取某个会话中指定数量的最新消息实体
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话 ID
 - Parameter count: 需要获取的消息数量
 - Returns: 消息实体 RCMessage 对象列表
 
 
 此方法会获取该会话中指定数量的最新消息实体，返回的消息实体按照时间从新到旧排列。
 如果会话中的消息数量小于参数 count 的值，会将该会话中的所有消息返回。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (nullable NSArray<RCMessage *> *)getLatestMessages:(RCConversationType)conversationType
                                            targetId:(NSString *)targetId
                                               count:(int)count
    __deprecated_msg("Use [RCCoreClient getLatestMessages:targetId:count:completion:] instead");

/*!
 获取会话中，从指定消息之前、指定数量的最新消息实体
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话 ID
 - Parameter oldestMessageId: 截止的消息 ID [0或-1 代表从最近的发送时间查起]
 - Parameter count: 需要获取的消息数量
 - Returns: 消息实体 RCMessage 对象列表
 
 
 此方法会获取该会话中，oldestMessageId 之前的、指定数量的最新消息实体，返回的消息实体按照时间从新到旧排列。
 返回的消息中不包含 oldestMessageId 对应那条消息，如果会话中的消息数量小于参数 count 的值，会将该会话中的所有消息返回。
 如：
 oldestMessageId 为 10，count 为 2，会返回 messageId 为 9 和 8 的 RCMessage 对象列表。
 
 此方法不支持超级群的会话类型。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                             targetId:(NSString *)targetId
                                      oldestMessageId:(long)oldestMessageId
                                                count:(int)count
    __deprecated_msg("Use [RCCoreClient getHistoryMessages:targetId:oldestMessageId:count:completion:] instead");
/*!
 获取会话中，从指定消息之前、指定数量的、指定消息类型的最新消息实体
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话 ID
 - Parameter objectName: 消息内容的类型名，如果想取全部类型的消息请传 nil
 - Parameter oldestMessageId: 截止的消息 ID [0或-1 代表从最近的发送时间查起]
 - Parameter count: 需要获取的消息数量
 - Returns: 消息实体 RCMessage 对象列表
 
 
 此方法会获取该会话中，oldestMessageId 之前的、指定数量和消息类型的最新消息实体，返回的消息实体按照时间从新到旧排列。
 返回的消息中不包含 oldestMessageId 对应的那条消息，如果会话中的消息数量小于参数 count
 的值，会将该会话中的所有消息返回。
 如：oldestMessageId 为 10，count 为 2，会返回 messageId 为 9 和 8 的 RCMessage 对象列表。
 
 此方法不支持超级群的会话类型。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                             targetId:(NSString *)targetId
                                           objectName:(nullable NSString *)objectName
                                      oldestMessageId:(long)oldestMessageId
                                                count:(int)count
    __deprecated_msg(
        "Use [RCCoreClient getHistoryMessages:targetId:objectName:oldestMessageId:count:completion:] instead");

/*!
 获取会话中，指定消息、指定数量、指定消息类型、向前或向后查找的消息实体列表
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话 ID
 - Parameter objectName: 消息内容的类型名，如果想取全部类型的消息请传 nil
 - Parameter baseMessageId: 当前的消息 ID [0或-1 代表从最近的发送时间查起]
 - Parameter isForward: 查询方向 true 为向前，false 为向后
 - Parameter count: 需要获取的消息数量
 - Returns: 消息实体 RCMessage 对象列表
 
 
 此方法会获取该会话中，baseMessageId
 之前或之后的、指定数量、消息类型和查询方向的最新消息实体，返回的消息实体按照时间从新到旧排列。
 返回的消息中不包含 baseMessageId 对应的那条消息，如果会话中的消息数量小于参数 count 的值，会将该会话中的所有消息返回。
 
 此方法不支持超级群的会话类型。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                             targetId:(NSString *)targetId
                                           objectName:(nullable NSString *)objectName
                                        baseMessageId:(long)baseMessageId
                                            isForward:(BOOL)isForward
                                                count:(int)count
    __deprecated_msg(
        "Use [RCCoreClient getHistoryMessages:targetId:objectName:baseMessageId:isForward:count:completion:] instead");

/*!
 获取会话中，指定时间、指定数量、指定消息类型（多个）、向前或向后查找的消息实体列表
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话 ID
 - Parameter objectNames: 消息内容的类型名称列表
 - Parameter sentTime: 当前的消息时间戳
 - Parameter isForward: 查询方向 true 为向前，false 为向后
 - Parameter count: 需要获取的消息数量
 - Returns: 消息实体 RCMessage 对象列表
 
 
 此方法会获取该会话中，sentTime
 之前或之后的、指定数量、指定消息类型（多个）的消息实体列表，返回的消息实体按照时间从新到旧排列。
 返回的消息中不包含 sentTime 对应的那条消息，如果会话中的消息数量小于参数 count 的值，会将该会话中的所有消息返回。
 
 此方法不支持超级群的会话类型。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                             targetId:(NSString *)targetId
                                          objectNames:(NSArray<NSString *> *)objectNames
                                             sentTime:(long long)sentTime
                                            isForward:(BOOL)isForward
                                                count:(int)count
    __deprecated_msg(
        "Use [RCCoreClient getHistoryMessages:targetId:objectNames:sentTime:isForward:count:completion:] instead");

/*!
 在会话中搜索指定消息的前 beforeCount 数量和后 afterCount
 数量的消息。返回的消息列表中会包含指定的消息。消息列表时间顺序从新到旧。
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话 ID
 - Parameter sentTime: 消息的发送时间
 - Parameter beforeCount: 指定消息的前部分消息数量
 - Parameter afterCount: 指定消息的后部分消息数量
 - Returns: 消息实体 RCMessage 对象列表
 
 
 获取该会话的这条消息及这条消息前 beforeCount 条和后 afterCount 条消息,如前后消息不够则返回实际数量的消息。
 
 此方法不支持超级群的会话类型。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (nullable NSArray<RCMessage *> *)getHistoryMessages:(RCConversationType)conversationType
                                             targetId:(NSString *)targetId
                                             sentTime:(long long)sentTime
                                          beforeCount:(int)beforeCount
                                           afterCount:(int)afterCount
    __deprecated_msg(
        "Use [RCCoreClient getHistoryMessages:targetId:sentTime:beforeCount:afterCount:completion:] instead");

/// 获取历史消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter option: 可配置的参数
/// - Parameter complete: 获取成功的回调 [messages：获取到的历史消息数组；code : 获取是否成功，0 表示成功，非 0 表示失败，此时 messages 数组可能存在断档]
///
/// 必须开通历史消息云存储功能。
/// 此方法先从本地获取历史消息，本地有缺失的情况下会从服务端同步缺失的部分。
/// 从服务端同步失败的时候会返回非 0 的 errorCode，同时把本地能取到的消息回调上去。
///
/// - Remark: 消息操作
/// - Since: 5.1.2
- (void)getMessages:(RCConversationType)conversationType
           targetId:(NSString *)targetId
             option:(RCHistoryMessageOption *)option
           complete:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages, RCErrorCode code))complete
    __deprecated_msg("Use [RCCoreClient getMessages:targetId:option:completion:error:] instead");

/*!
 获取会话中 @ 提醒自己的消息
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话 ID
 
 
 此方法从本地获取被@提醒的消息(最多返回 10 条信息)
 - Warning: 使用 IMKit 注意在进入会话页面前调用，否则在进入会话清除未读数的接口 clearMessagesUnreadStatus: targetId:
 以及 设置消息接收状态接口 setMessageReceivedStatus:receivedStatus:会同步清除被提示信息状态。
 
 - Remark: 高级功能
 - Since: 5.0.0
 */
- (nullable NSArray<RCMessage *> *)getUnreadMentionedMessages:(RCConversationType)conversationType
                                                     targetId:(NSString *)targetId
    __deprecated_msg("Use [RCCoreClient getUnreadMentionedMessages:targetId:completion:] instead");

/*!
 获取本地指定会话的未读条数的 @ 消息列表，仅支持群组
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话 ID
 - Parameter count: 未读的 @ 消息，取值范围 [1,100]
 - Parameter desc: 是否是降序查
 假如有 1000 条未读的 @ 消息，取 100 条未读
 desc 为 true 时获取后 100 条消息，messageList 的顺序是 901 到 1000
 desc 为 false 是获取前 100 条消息，messageList 的顺序是 1 到 100
 
 - Warning: 使用 IMKit 注意在进入会话页面前调用，否则在进入会话清除未读数的接口 clearMessagesUnreadStatus: targetId:
 以及 设置消息接收状态接口 setMessageReceivedStatus:receivedStatus:会同步清除被提示信息状态。
 - Since: 5.2.5
 */
- (nullable NSArray<RCMessage *> *)getUnreadMentionedMessages:(RCConversationType)conversationType
                                                     targetId:(NSString *)targetId
                                                        count:(int)count
                                                         desc:(BOOL)desc
    __deprecated_msg("Use [RCCoreClient getUnreadMentionedMessages:targetId:count:desc:completion: instead");

/*!
 获取消息的发送时间（Unix 时间戳、毫秒）
 
 - Parameter messageId: 消息 ID
 - Returns: 消息的发送时间（Unix 时间戳、毫秒）
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (long long)getMessageSendTime:(long)messageId
    __deprecated_msg("Use [RCCoreClient getMessageSendTime:completion:] instead");


/*!
 通过 messageId 获取消息实体
 
 - Parameter messageId: 消息 ID（数据库索引唯一值）
 - Returns: 通过消息 ID 获取到的消息实体，当获取失败的时候，会返回 nil。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (nullable RCMessage *)getMessage:(long)messageId
    __deprecated_msg("Use [RCCoreClient getMessage:completion:] instead");

/*!
 通过全局唯一 ID 获取消息实体
 
 - Parameter messageUId: 全局唯一 ID（服务器消息唯一 ID）
 - Returns: 通过全局唯一ID获取到的消息实体，当获取失败的时候，会返回 nil。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (nullable RCMessage *)getMessageByUId:(NSString *)messageUId
    __deprecated_msg("Use [RCCoreClient getMessageByUId:completion:] instead");

/**
 * 获取会话里第一条未读消息。
 *
 * - Parameter conversationType: 会话类型
 * - Parameter targetId: 会话 ID
 * - Returns: 第一条未读消息的实体。
 * - Remark: 消息操作
 * - Since: 5.0.0
 */
- (nullable RCMessage *)getFirstUnreadMessage:(RCConversationType)conversationType
                                     targetId:(NSString *)targetId
    __deprecated_msg("Use [RCCoreClient getFirstUnreadMessage:targetId:completion:] instead");

/*!
 删除消息
 
 - Parameter messageIds: 消息 ID 的列表，元素需要为 NSNumber 类型
 - Returns: 是否删除成功
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (BOOL)deleteMessages:(NSArray<NSNumber *> *)messageIds
    __deprecated_msg("Use [RCCoreClient deleteMessages:completion:] instead");

/*!
 删除某个会话中的所有消息
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话 ID
 - Returns: 是否删除成功
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (BOOL)clearMessages:(RCConversationType)conversationType
             targetId:(NSString *)targetId
    __deprecated_msg("Use [RCCoreClient clearMessages:targetId:completion:] instead");

/*!
 设置消息的附加信息
 
 - Parameter messageId: 消息 ID
 - Parameter value: 附加信息，最大 1024 字节
 - Returns: 是否设置成功
 
 用于扩展消息的使用场景。只能用于本地使用，无法同步到远端。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (BOOL)setMessageExtra:(long)messageId
                  value:(NSString *)value
    __deprecated_msg("Use [RCCoreClient setMessageExtra:value:completion:] instead");

/*!
 设置消息的接收状态
 
 - Parameter messageId: 消息 ID
 - Parameter receivedStatus: 消息的接收状态
 - Returns: 是否设置成功
 
 用于 UI 展示消息为已读，已下载等状态。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (BOOL)setMessageReceivedStatus:(long)messageId
                  receivedStatus:(RCReceivedStatus)receivedStatus
    __deprecated_msg("Use [RCCoreClient setMessageReceivedStatus:receivedStatusInfo:completion:] instead");

/// 异步设置消息的接收状态
///
/// - Parameter messageId: 消息 ID
/// - Parameter receivedStatus: 消息的接收状态
/// - Parameter completion: 异步回调 [是否设置成功]
///
/// 用于 UI 展示消息为已读，已下载等状态。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)setMessageReceivedStatus:(long)messageId
                  receivedStatus:(RCReceivedStatus)receivedStatus
                      completion:(nullable void (^)(BOOL ret))completion
    __deprecated_msg("Use [RCCoreClient setMessageReceivedStatus:receivedStatusInfo:completion] instead");
/*!
 设置消息的发送状态
 
 - Parameter messageId: 消息 ID
 - Parameter sentStatus: 消息的发送状态
 - Returns: 是否设置成功
 
 用于 UI 展示消息为正在发送，对方已接收等状态。
 为了保证 UI 正常显示，5.1.8 版本起不再支持 app 将消息状态设置为 SentStatus_SENDING
 
 此方法不支持超级群的会话类型。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (BOOL)setMessageSentStatus:(long)messageId
                  sentStatus:(RCSentStatus)sentStatus
    __deprecated_msg("Use [RCCoreClient setMessageSentStatus:sentStatus:completion:] instead");
;

#pragma mark - 会话列表操作 -
/*!
 获取会话列表
 
 - Parameter conversationTypeList: 会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 - Returns: 会话 RCConversation 的列表
 
 此方法会从本地数据库中，读取会话列表。
 返回的会话列表按照时间从前往后排列，如果有置顶的会话，则置顶的会话会排列在前面。
 当您的会话较多且没有清理机制的时候，强烈建议您使用 getConversationList: count: startTime:
 分页拉取会话列表,否则有可能造成内存过大。
 
 - Remark: 会话列表
 - Since: 5.0.0
 */
- (nullable NSArray<RCConversation *> *)getConversationList:(NSArray<NSNumber *> *)conversationTypeList
    __deprecated_msg("Use [RCCoreClient getConversationList:completion:] instead");

/*!
 分页获取会话列表
 
 - Parameter conversationTypeList: 会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 - Parameter count: 获取的数量（当实际取回的会话数量小于 count 值时，表明已取完数据）
 - Parameter startTime: 会话的时间戳（获取这个时间戳之前的会话列表，0表示从最新开始获取）
 - Returns: 会话 RCConversation 的列表
 
 此方法会从本地数据库中，读取会话列表。
 返回的会话列表按照时间从前往后排列，如果有置顶的会话，则置顶的会话会排列在前面。
 
 - Remark: 会话列表
 - Since: 5.0.0
 */
- (nullable NSArray<RCConversation *> *)getConversationList:(NSArray<NSNumber *> *)conversationTypeList
                                                      count:(int)count
                                                  startTime:(long long)startTime
    __deprecated_msg("Use [RCCoreClient getConversationList:count:startTime:completion:] instead");

/*!
 获取单个会话数据
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话 ID
 - Returns: 会话的对象
 
 - Remark: 会话
 - Since: 5.0.0
 */
- (nullable RCConversation *)getConversation:(RCConversationType)conversationType
                                    targetId:(NSString *)targetId
    __deprecated_msg("Use [RCCoreClient getConversation:targetId:completion:] instead");

/*!
 获取会话中的消息数量
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话 ID
 - Returns: 会话中的消息数量
 
 -1 表示获取消息数量出错。
 
 - Remark: 会话
 - Since: 5.0.0
 */
- (int)getMessageCount:(RCConversationType)conversationType
              targetId:(NSString *)targetId
    __deprecated_msg("Use [RCCoreClient getMessageCount:targetId:completion:] instead");

/*!
 删除本地和服务的会话
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话 ID
 - Returns: 本地会话是否删除成功
 
 此方法会删除该会话，但是不会删除会话中的消息。如果此会话中有新的消息，该会话将重新在会话列表中显示，并显示最近的历史消息。
 - Warning: 此方法会同时删除本地和服务的会话。如果服务的会话删除失败，本地的会话依然会被删除
 SDK 在未连接的情况下，删除服务会话会失败
 
 - Remark: 会话
 - Since: 5.0.0
 */
- (BOOL)removeConversation:(RCConversationType)conversationType
                  targetId:(NSString *)targetId
    __deprecated_msg("Use [RCCoreClient removeConversation:targetId:completion:] instead");

/// 异步删除本地会话
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter completion: 异步回调 [是否删除成功]
///
/// - Warning: 此方法会删除该会话，但是不会删除会话中的消息。如果此会话中有新的消息，该会话将重新在会话列表中显示，并显示最近的历史消息。
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)removeConversation:(RCConversationType)conversationType
                  targetId:(NSString *)targetId
                completion:(nullable void (^)(BOOL ret))completion
    NS_SWIFT_NAME(removeConversation(_:targetId:completion:))
        __deprecated_msg("Use -[RCCoreClient removeConversation:targetId:isDeleteRemote:success:error:] instead");

/*!
 删除指定类型的会话

 - Parameter conversationTypeList: 会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 - Returns: 是否删除成功

 此方法会从本地存储中删除该会话，同时删除会话中的消息。

 此方法不支持超级群的会话类型，包含超级群时可能会造成数据异常。
 
 - Remark: 会话
 - Since: 5.0.0
 */
- (BOOL)clearConversations:(NSArray<NSNumber *> *)conversationTypeList
    __deprecated_msg("Use [RCCoreClient clearConversations:completion:] instead");

/*!
 设置会话的置顶状态
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话 ID
 - Parameter isTop: 是否置顶
 - Returns: 设置是否成功
 
 会话不存在时设置置顶，会在会话列表生成会话。
 
 - Remark: 会话
 - Since: 5.0.0
 */
- (BOOL)setConversationToTop:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
                       isTop:(BOOL)isTop
    __deprecated_msg("Use [RCCoreClient setConversationToTop:targetId:isTop:completion:] instead");

/*!
 获取置顶的会话列表
 
 - Parameter conversationTypeList: 会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 - Returns: 置顶的会话 RCConversation 的列表
 
 此方法会从本地数据库中，读取置顶的会话列表。
 
 - Remark: 会话列表
 - Since: 5.0.0
 */
- (nullable NSArray<RCConversation *> *)getTopConversationList:(NSArray<NSNumber *> *)conversationTypeList
    __deprecated_msg("Use [RCCoreClient getTopConversationList:completion:] instead");

/*!
 获取会话的置顶状态
 
 - Parameter conversationIdentifier: 会话信息
 
 此方法会从本地数据库中，读取该会话是否置顶。
 
 - Remark: 会话
 - Since: 5.1.5
 */
- (BOOL)getConversationTopStatus:(RCConversationIdentifier *)conversationIdentifier
    __deprecated_msg("Use [RCCoreClient getConversationTopStatus:completion:] instead");

#pragma mark - 会话中的草稿操作 -
/*!
 获取会话中的草稿信息（用户输入但未发送的暂存消息）
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话目标 ID
 - Returns: 该会话中的草稿
 
 - Remark: 会话
 - Since: 5.0.0
 */
- (nullable NSString *)getTextMessageDraft:(RCConversationType)conversationType
                                  targetId:(NSString *)targetId
    __deprecated_msg("Use [RCCoreClient getTextMessageDraft:targetId:completion:] instead");

/*!
 保存草稿信息（用户输入但未发送的暂存消息）
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话目标 ID
 - Parameter content: 草稿信息
 - Returns: 是否保存成功
 
 - Remark: 会话
 - Since: 5.0.0
 */
- (BOOL)saveTextMessageDraft:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
                     content:(NSString *)content
    __deprecated_msg("Use [RCCoreClient saveTextMessageDraft:targetId:content:completion:] instead");

/*!
 删除会话中的草稿信息（用户输入但未发送的暂存消息）
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话目标 ID
 - Returns: 是否删除成功
 
 - Remark: 会话
 - Since: 5.0.0
 */
- (BOOL)clearTextMessageDraft:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
    __deprecated_msg("Use [RCCoreClient clearTextMessageDraft:targetId:completion:] instead");


#pragma mark - 未读消息数 -

/*!
 获取所有的未读消息数（聊天室会话除外）
 
 - Returns: 所有的未读消息数
 
 - Remark: 会话
 - Since: 5.0.0
 */
- (int)getTotalUnreadCount __deprecated_msg("Use [RCCoreClient getTotalUnreadCountWith:] instead");

/*!
 获取某个会话内的未读消息数（聊天室会话除外）
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话目标 ID
 - Returns: 该会话内的未读消息数
 
 - Remark: 会话
 - Since: 5.0.0
 */
- (int)getUnreadCount:(RCConversationType)conversationType
             targetId:(NSString *)targetId
    __deprecated_msg("Use [RCCoreClient getUnreadCount:targetId:completion:] instead");

/*!
 获取某个会话内的未读消息数
 
 - Parameter conversationIdentifier: 会话信息
 - Parameter messageClassList: 消息类型数组
 - Returns: 该会话内的未读消息数
 
 此方法不支持聊天室和超级群的会话类型。
 
 - Remark: 会话
 - Since: 5.1.5
 */
- (int)getUnreadCount:(RCConversationIdentifier *)conversationIdentifier
     messageClassList:(NSArray<Class> *)messageClassList
    __deprecated_msg("Use [RCCoreClient getUnreadCount:messageClassList:completion:] instead");

/*!
 获取某些会话的总未读消息数 （聊天室会话除外）
 
 - Parameter conversations: 会话列表 （ RCConversation 对象只需要 conversationType 和 targetId，channelId 按需使用）
 - Returns: 传入会话列表的未读消息数
 
 conversations会话个数不能超过300，超过会被截断。
 
 - Remark: 会话
 - Since: 5.0.0
 */
- (int)getTotalUnreadCount:(NSArray<RCConversation *> *)conversations
    __deprecated_msg("Use [RCCoreClient getTotalUnreadCount:completion:] instead");

/*!
 获取某些类型的会话中所有的未读消息数 （聊天室会话除外）
 
 - Parameter conversationTypes: 会话类型的数组
 - Parameter isContain: 是否包含免打扰消息的未读数
 - Returns: 该类型的会话中所有的未读消息数
 
 - Remark: 会话
 - Since: 5.0.0
 */
- (int)getUnreadCount:(NSArray<NSNumber *> *)conversationTypes
       containBlocked:(bool)isContain
    __deprecated_msg("Use [RCCoreClient getUnreadCount:containBlocked:completion:] instead");

/*!
 获取某个类型的会话中所有的未读消息数（聊天室会话除外）
 
 - Parameter conversationTypes: 会话类型的数组
 - Returns: 该类型的会话中所有的未读消息数
 
 - Remark: 会话
 - Since: 5.0.0
 */
- (int)getUnreadCount:(NSArray<NSNumber *> *)conversationTypes
    __deprecated_msg("Use [RCCoreClient getUnreadCount:completion:] instead");

/*!
 获取某个类型的会话中所有未读的被 @ 的消息数
 
 - Parameter conversationTypes: 会话类型的数组
 - Returns: 该类型的会话中所有未读的被 @ 的消息数
 
 - Remark: 会话
 - Since: 5.0.0
 */
- (int)getUnreadMentionedCount:(NSArray<NSNumber *> *)conversationTypes
    __deprecated_msg("Use [RCCoreClient getUnreadMentionedCount:completion:] instead");

/*!
 清除某个会话中的未读消息数
 
 - Parameter conversationType: 会话类型，不支持聊天室
 - Parameter targetId: 会话 ID
 - Returns: 是否清除成功
 
 - Remark: 会话
 - Since: 5.0.0
 */
- (BOOL)clearMessagesUnreadStatus:(RCConversationType)conversationType
                         targetId:(NSString *)targetId
    __deprecated_msg("Use [RCCoreClient clearMessagesUnreadStatus:targetId:completion:] instead");

/*!
 清除某个会话中的未读消息数（该会话在时间戳 timestamp 之前的消息将被置成已读。）
 
 - Parameter conversationType: 会话类型，不支持聊天室
 - Parameter targetId: 会话 ID
 - Parameter timestamp: 该会话已阅读的最后一条消息的发送时间戳
 - Returns: 是否清除成功
 
 - Remark: 会话
 - Since: 5.0.0
 */
- (BOOL)clearMessagesUnreadStatus:(RCConversationType)conversationType
                         targetId:(NSString *)targetId
                             time:(long long)timestamp
    __deprecated_msg("Use [RCCoreClient clearMessagesUnreadStatus:targetId:time:completion:] instead");

/// 下载消息内容中的媒体信息
///
/// - Parameter messageId: 媒体消息的 messageId
/// - Parameter progressBlock: 消息下载进度更新的回调 [progress:当前的下载进度，0 <= progress <= 100]
/// - Parameter successBlock: 下载成功的回调 [mediaPath:下载成功后本地存放的文件路径]
/// - Parameter errorBlock: 下载失败的回调 [errorCode:下载失败的错误码]
/// - Parameter cancelBlock: 用户取消了下载的回调
///
/// 用来获取媒体原文件时调用。如果本地缓存中包含此文件，则从本地缓存中直接获取，否则将从服务器端下载。
///
/// - Warning: 多媒体下载成功后，会更新消息体的 localPath。
///
/// - Remark: 多媒体下载
/// - Since: 5.0.0
- (void)downloadMediaMessage:(long)messageId
                    progress:(nullable void (^)(int progress))progressBlock
                     success:(nullable void (^)(NSString *mediaPath))successBlock
                       error:(nullable void (^)(RCErrorCode errorCode))errorBlock
                      cancel:(nullable void (^)(void))cancelBlock
    __deprecated_msg(
        "Use [RCCoreClient downloadMediaMessage:progressBlock:successBlock:errorBlock:cancelBlock:] instead");

/// 取消下载中的媒体信息
///
/// - Parameter messageId: 媒体消息的 messageId
///
/// - Returns: YES 表示取消成功，NO 表示取消失败，即已经下载完成或者消息不存在。
///
/// - Remark: 多媒体下载
/// - Since: 5.0.0
- (BOOL)cancelDownloadMediaMessage:(long)messageId
    __deprecated_msg("Use [RCCoreClient cancelDownloadMediaMessage:successBlock:errorBlock:] instead");

/// 取消下载中的媒体信息
///
/// - Parameter mediaUrl: 媒体消息 Url
///
/// - Returns: YES 表示取消成功，NO 表示取消失败，即已经下载完成或者消息不存在。
///
/// - Remark: 多媒体下载
/// - Since: 5.0.0
- (BOOL)cancelDownloadMediaUrl:(NSString *)mediaUrl
    __deprecated_msg("Use [RCCoreClient cancelDownloadMediaUrl:successBlock:errorBlock:] instead");

#pragma mark - 会话的消息提醒 -

/*!
 设置会话的消息提醒状态
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话 ID
 - Parameter isBlocked: 是否屏蔽消息提醒
 - Parameter successBlock: 设置成功的回调
 [nStatus:会话设置的消息提醒状态]
 - Parameter errorBlock: 设置失败的回调 [status:设置失败的错误码]
 
 
 如果您使用
 IMLibCore，此方法会屏蔽该会话的远程推送；如果您使用IMKit，此方法会屏蔽该会话的所有提醒（远程推送、本地通知、前台提示音）,该接口不支持聊天室。
 
 - Remark: 会话
 - Since: 5.0.0
 */
- (void)setConversationNotificationStatus:(RCConversationType)conversationType
                                 targetId:(NSString *)targetId
                                isBlocked:(BOOL)isBlocked
                                  success:(nullable void (^)(RCConversationNotificationStatus nStatus))successBlock
                                    error:(nullable void (^)(RCErrorCode status))errorBlock
    __deprecated_msg("Use [RCChannelClient "
                     "setConversationChannelNotificationLevel:targetId:channelId:level:success:error:] instead");

/*!
 获取消息免打扰会话列表
 
 - Parameter conversationTypeList: 会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 - Returns: 消息免打扰会话 RCConversation 的列表
 
 此方法会从本地数据库中，读取消息免打扰会话列表。
 
 - Remark: 会话列表
 - Since: 5.0.0
 */
- (nullable NSArray<RCConversation *> *)getBlockedConversationList:(NSArray<NSNumber *> *)conversationTypeList
    __deprecated_msg("Use [RCCoreClient getBlockedConversationList:completion:] instead");

#pragma mark - 全局消息提醒 -

/*!
 全局屏蔽某个时间段的消息提醒
 
 - Parameter startTime: 开始消息免打扰时间，格式为 HH:MM:SS
 - Parameter spanMins: 需要消息免打扰分钟数，0 < spanMins < 1440（ 比如，您设置的起始时间是 00：00， 结束时间为 01:00，则 spanMins 为 60 分钟。设置为 1439 代表全天免打扰 （23 * 60 + 59 = 1439 ））
 - Parameter successBlock: 屏蔽成功的回调
 - Parameter errorBlock: 屏蔽失败的回调 [status:屏蔽失败的错误码]
 
 此方法设置的屏蔽时间会在每天该时间段时生效。
 如果您使用 IMLibCore，此方法会屏蔽所有会话在该时间段的远程推送；如果您使用
 IMKit，此方法会屏蔽所有会话在该时间段的所有提醒（远程推送、本地通知、前台提示音）。
 
 - Remark: 会话
 - Since: 5.0.0
 */
- (void)setNotificationQuietHours:(NSString *)startTime
                         spanMins:(int)spanMins
                          success:(nullable void (^)(void))successBlock
                            error:(nullable void (^)(RCErrorCode status))errorBlock
    __deprecated_msg("Use [RCChannelClient  setNotificationQuietHoursLevel:spanMins:level:success:error:] instead");

/*!
 删除已设置的全局时间段消息提醒屏蔽
 
 - Parameter successBlock: 删除屏蔽成功的回调
 - Parameter errorBlock: 删除屏蔽失败的回调 [status:失败的错误码]
 
 - Remark: 会话
 - Since: 5.0.0
 */
- (void)removeNotificationQuietHours:(nullable void (^)(void))successBlock
                               error:(nullable void (^)(RCErrorCode status))errorBlock
    __deprecated_msg("Use [RCChannelClient removeNotificationQuietHours:success:error:] instead");

/*!
 查询已设置的全局时间段消息提醒屏蔽
 
 - Parameter successBlock: 屏蔽成功的回调 [startTime:已设置的屏蔽开始时间,
 spanMins:已设置的屏蔽时间分钟数，0 < spanMins < 1440]
 - Parameter errorBlock: 查询失败的回调 [status:查询失败的错误码]
 
 - Remark: 会话
 - Since: 5.0.0
 */
- (void)getNotificationQuietHours:(nullable void (^)(NSString *startTime, int spanMins))successBlock
                            error:(nullable void (^)(RCErrorCode status))errorBlock
    __deprecated_msg("Use [RCChannelClient getNotificationQuietHoursLevel:error:] instead");

#pragma mark - 工具类方法

/*!
 获取当前手机与服务器的时间差
 
 - Returns: 时间差
 消息发送成功后，SDK 会与服务器同步时间，消息所在数据库中存储的时间就是服务器时间。
 
 - Remark: 数据获取
 - Since: 5.0.0
 */
- (long long)getDeltaTime __deprecated_msg("Use [RCCoreClient getDeltaTime:] instead");

#pragma mark - 搜索

/*!
 根据关键字搜索指定会话中的消息
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话 ID
 - Parameter keyword: 关键字
 - Parameter count: 最大的查询数量
 - Parameter startTime: 查询 startTime 之前的消息（传 0 表示不限时间）
 
 - Returns: 匹配的消息列表
 
 只支持搜索已存储到本地的消息。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (nullable NSArray<RCMessage *> *)searchMessages:(RCConversationType)conversationType
                                         targetId:(NSString *)targetId
                                          keyword:(NSString *)keyword
                                            count:(int)count
                                        startTime:(long long)startTime
    __deprecated_msg("Use [RCCoreClient searchMessages:targetId:keyword:count:startTime:completion:] instead");

/*!
 根据时间，偏移量和个数搜索指定会话中的消息
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话 ID
 - Parameter keyword: 关键字，传空默认为是查全部符合条件的消息
 - Parameter startTime: 查询 startTime 之后的消息， startTime >= 0
 - Parameter endTime: 查询 endTime 之前的消息，endTime > startTime
 - Parameter offset: 查询的消息的偏移量，offset >= 0
 - Parameter limit: 最大的查询数量，limit 需大于 0，最大值为100，如果大于100，会默认成100。
 
 - Returns: 匹配的消息列表
 
 只支持搜索已存储到本地的消息。
 
 - Remark: 消息操作
 - Since: 5.1.2
 */
- (nullable NSArray<RCMessage *> *)searchMessages:(RCConversationType)conversationType
                                         targetId:(NSString *)targetId
                                          keyword:(NSString *)keyword
                                        startTime:(long long)startTime
                                          endTime:(long long)endTime
                                           offset:(int)offset
                                            limit:(int)limit
    __deprecated_msg(
        "Use [RCCoreClient searchMessages:targetId:keyword:count:startTime:endTime:offset:limit:completion:] instead");

/*!
 按用户 ID 搜索指定会话中的消息
 
 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话 ID
 - Parameter userId: 搜索用户 ID
 - Parameter count: 最大的查询数量
 - Parameter startTime: 查询 startTime 之前的消息（传 0 表示不限时间）
 
 - Returns: 匹配的消息列表
 
 只支持搜索已存储到本地的消息。
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (nullable NSArray<RCMessage *> *)searchMessages:(RCConversationType)conversationType
                                         targetId:(NSString *)targetId
                                           userId:(NSString *)userId
                                            count:(int)count
                                        startTime:(long long)startTime
    __deprecated_msg("Use [RCCoreClient searchMessages:targetId:userId:count:startTime:completion:] instead");

/*!
 根据关键字搜索会话
 
 - Parameter conversationTypeList: 需要搜索的会话类型的数组(需要将 RCConversationType 转为 NSNumber 构建 NSArray)
 - Parameter objectNameList: 需要搜索的消息类型名列表(即每个消息类方法 getObjectName 的返回值)
 - Parameter keyword: 关键字，非空
 
 - Returns: 匹配的会话搜索结果列表
 
 目前，SDK 内置的文本消息、文件消息、图文消息支持搜索。
 自定义的消息必须要实现 RCMessageContent 的 getSearchableWords 接口才能进行搜索。
 
 conversationTypeList 包含超级群会话类型时，超级群会话只搜索已存储到本地的消息记录。
 objectNameList中类型名个数不能超过300，超过会被截断。
 
 conversationTypeList 传值时：
 OC 需转成 NSNumber 传入（例如 @[ @(ConversationType_PRIVATE) ]），
 Swift 需获取到 rawValue 强转成 NSNumber 传入
 （例如 let privateType = NSNumber(value: RCConversationType.ConversationType_PRIVATE.rawValue)
 [privateType]  ）
 
 - Remark: 消息操作
 - Since: 5.0.0
 */
- (nullable NSArray<RCSearchConversationResult *> *)searchConversations:(NSArray<NSNumber *> *)conversationTypeList
                                                            messageType:(NSArray<NSString *> *)objectNameList
                                                                keyword:(NSString *)keyword
    __deprecated_msg("Use [RCCoreClient searchConversations:messageType:keyword:completion:] instead");

#pragma mark - 消息扩展 -

/*!
 获取标签列表
 
 - Returns: 标签列表
 - Remark: 高级功能
 - Since: 5.1.1
 */
- (NSArray<RCTagInfo *> *)getTags __deprecated_msg("Use [RCCoreClient getTags:] instead");

/*!
 获取会话的所有标签
 
 - Parameter conversationIdentifier: 会话信息
 - Returns: 会话所属的标签列表
 
 此方法不支持超级群的会话类型。
 - Remark: 高级功能
 - Since: 5.1.1
 */
- (nullable NSArray<RCConversationTagInfo *> *)getTagsFromConversation:
    (RCConversationIdentifier *)conversationIdentifier
    __deprecated_msg("Use [RCCoreClient getTagsFromConversation:completion:] instead");

/*!
 分页获取标签中会话列表
 
 - Parameter tagId: 标签 ID
 - Parameter timestamp: 会话的时间戳（获取这个时间戳之前的会话列表，0表示从最新开始获取）
 - Parameter count: 获取的数量（当实际取回的会话数量小于 count 值时，表明已取完数据）
 - Returns: 会话 RCConversation 的列表
 
 此方法不支持超级群的会话类型。
 - Remark: 高级功能
 - Since: 5.1.1
 */
- (nullable NSArray<RCConversation *> *)getConversationsFromTagByPage:(NSString *)tagId
                                                            timestamp:(long long)timestamp
                                                                count:(int)count
    __deprecated_msg("Use [RCCoreClient getConversationsFromTagByPage:timestamp:count:completion:] instead");

/*!
 获取标签中会话消息未读数
 
 - Parameter tagId: 标签 ID
 - Parameter isContain: 是否包含免打扰会话
 - Returns: 会话消息未读数
 
 此方法不支持超级群的会话类型。
 - Remark: 高级功能
 - Since: 5.1.1
 */
- (int)getUnreadCountByTag:(NSString *)tagId
            containBlocked:(BOOL)isContain
    __deprecated_msg("Use [RCCoreClient getUnreadCountByTag:containBlocked:completion:] instead");

/*!
 获取标签中的会话置顶状态
 
 - Parameter conversationIdentifier: 会话信息
 - Parameter tagId: 标签 ID
 - Returns: 置顶状态
 
 此方法不支持超级群的会话类型。
 - Remark: 高级功能
 - Since: 5.1.1
 */
- (BOOL)getConversationTopStatusInTag:(RCConversationIdentifier *)conversationIdentifier
                                tagId:(NSString *)tagId
    __deprecated_msg("Use [RCCoreClient getConversationTopStatusInTag:tagId:completion:] instead");

/*!
 清除标签对应会话的未读消息数
 
 - Parameter tagId: 标签 ID
 - Returns: 是否清除成功
 
 此方法不支持超级群的会话类型。
 - Remark: 高级功能
 - Since: 5.1.5
 */
- (BOOL)clearMessagesUnreadStatusByTag:(NSString *)tagId
    __deprecated_msg("Use [RCCoreClient clearMessagesUnreadStatusByTag:completion:] instead");

#pragma mark-- 统计

/// 统计 App 启动的事件
///
/// - Parameter launchOptions: App 的启动附加信息
///
/// 此方法用于统计融云推送服务的点击率。
/// 如果您需要统计推送服务的点击率，只需要在 AppDelegate 的-application:didFinishLaunchingWithOptions:中，
/// 调用此方法并将 launchOptions  传入即可。
///
/// - Remark: 高级功能
/// - Since: 5.0.0
- (void)recordLaunchOptionsEvent:(nullable NSDictionary *)launchOptions
    __deprecated_msg("Remote notification use [RCCoreClient recordRemoteNotificationEvent:] instead, local "
                     "notification use [RCCoreClient recordLocalNotificationResponseEvent:] instead");

/// 统计本地通知的事件
///
/// - Parameter notification: 本地通知的内容
///
/// 此方法用于统计融云推送服务的点击率。
/// 如果您需要统计推送服务的点击率，只需要在 AppDelegate 的-application:didReceiveLocalNotification:中，
/// 调用此方法并将 launchOptions 传入即可。
///
/// - Remark: 高级功能
/// - Since: 5.0.0
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
- (void)recordLocalNotificationEvent:(UILocalNotification *)notification
    __deprecated_msg("Use [RCCoreClient recordLocalNotificationResponseEvent:] instead");
#pragma clang diagnostic pop

#pragma mark-- 信息托管

/// 创建群组
/// - Parameter groupInfo: 群组信息及权限，groupId、groupName 必填，否则创建失败
/// - Parameter inviteeUserIds: 被邀请的用户 Id 列表，可以为空，一次最多允许 30 个用户加入。
/// - Parameter success: 成功回调。
/// - Parameter error: 失败回调
///
/// - Note:
///
/// **`groupInfo` 参数说明**
/// - `groupId` 最大长度 64 个字符。支持大小写英文字母与数字的组合
/// - `groupName` 最长不超过 64 个字符，群名称可以重复创建
///
/// **`successBlock` 的 `processCode` 参数说明**
/// - 当群组的 `inviteHandlePermission` 为被邀请人需要同意才能进群时，`processCode` 返回 `RC_GROUP_NEED_INVITEE_ACCEPT` ( 25427 )，表示需要被邀请人同意后才能进入群组。
/// - 当群组的 `inviteHandlePermission` 为不需被邀请人同意时，`processCode` 返回 RC_SUCCESS ( 0 )，被邀请人会直接加入群组。
/// - Since: 5.12.0
- (void)createGroup:(RCGroupInfo *)groupInfo
     inviteeUserIds:(nullable NSArray<NSString *> *)inviteeUserIds
            success:(void (^)(RCErrorCode processCode))successBlock
              error:(void (^)(RCErrorCode errorCode, NSString *_Nullable errorKey))errorBlock
    __deprecated_msg("Use -[RCCoreClient createGroup:inviteeUserIds:successBlock:errorBlock:] instead");

/// 更新群组信息
/// - Parameter groupInfo: 群组信息，groupId 必填，否则更新失败
/// - Parameter success: 成功回调
/// - Parameter error: 失败回调
///
/// - Since: 5.12.0
- (void)updateGroupInfo:(RCGroupInfo *)groupInfo
                success:(void (^)(void))successBlock
                  error:(void (^)(RCErrorCode errorCode, NSString *_Nullable errorKey))errorBlock
    NS_SWIFT_NAME(updateGroupInfo(_:success:error:))
        __deprecated_msg("Use -[RCCoreClient updateGroupInfo:successBlock:errorBlock:] instead");

/// 设置群成员资料
/// - Parameter groupId: 群组 ID
/// - Parameter userId: 用户 ID，必填项，支持传入当前登录用户 ID
/// - Parameter nickname: 用户昵称，非必填项，长度不超过 64 个字符，传 nil 或 空字符串表示移除用户昵称
/// - Parameter extra: 附加信息，非必填项，长度不超过 128 个字符
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)setGroupMemberInfo:(NSString *)groupId
                    userId:(NSString *)userId
                  nickname:(nullable NSString *)nickname
                     extra:(nullable NSString *)extra
                   success:(void (^)(void))successBlock
                     error:(void (^)(RCErrorCode errorCode))errorBlock
    __deprecated_msg("Use -[RCCoreClient setGroupMemberInfo:userId:nickname:extra:successBlock:errorBlock:] instead");

/// 修改自己的用户信息
///
/// - Parameter profile: 用户信息
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// - Since: 5.10.0
- (void)updateMyUserProfile:(RCUserProfile *)profile
                    success:(nullable void (^)(void))successBlock
                      error:(nullable void (^)(RCErrorCode errorCode, NSString *_Nullable errorKey))errorBlock
    __deprecated_msg("Use -[RCCoreClient updateMyUserProfile:successBlock:errorBlock:] instead");

/// 好友信息设置
/// - Parameter userId: 用户 ID
/// - Parameter remark: 好友备注，最多为 64 个字符，不传或为空时清除备注名。
/// - Parameter extProfile: 扩展信息
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)setFriendInfo:(NSString *)userId
               remark:(nullable NSString *)remark
           extProfile:(nullable NSDictionary<NSString *, NSString *> *)extProfile
              success:(void (^)(void))successBlock
                error:(void (^)(RCErrorCode errorCode))errorBlock
    __deprecated_msg("Use -[RCCoreClient setFriendInfo:remark:extProfile:successBlock:errorBlock:] instead");

@end

NS_ASSUME_NONNULL_END
