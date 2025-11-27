//
//  RCIMClientProtocol.h
//  RongIMLib
//
//  Created by LiFei on 2020/4/29.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#ifndef RCIMClientProtocol_h
#define RCIMClientProtocol_h

NS_ASSUME_NONNULL_BEGIN

@class RCMessage, RCUserTypingStatus;
@class RCConversationStatusInfo;
@class RCBlockedMessageInfo;
@class RCUltraGroupTypingStatusInfo;
@class RCRobotInfo;

#pragma mark - 消息接收监听器

/*!
 IMlib消息接收的监听器

 
 设置IMLib的消息接收监听器请参考RCIMClient的setReceiveMessageDelegate:object:方法。

 - Warning: 如果您使用IMlib，可以设置并实现此Delegate监听消息接收；
 如果您使用IMKit，请使用RCIM中的RCIMReceiveMessageDelegate监听消息接收，而不要使用此监听器，否则会导致IMKit中无法自动更新UI！
 */
@protocol RCIMClientReceiveMessageDelegate <NSObject>

@optional

/*!
 接收消息的回调方法

 - Parameter message: 当前接收到的消息
 - Parameter nLeft: 还剩余的未接收的消息数，left>=0
 - Parameter object: 消息监听设置的key值

 如果您设置了IMlib消息监听之后，SDK在接收到消息时候会执行此方法。
 其中，left为还剩余的、还未接收的消息数量。比如刚上线一口气收到多条消息时，通过此方法，您可以获取到每条消息，left会依次递减直到0。
 您可以根据left数量来优化您的App体验和性能，比如收到大量消息时等待left为0再刷新UI。
 object为您在设置消息接收监听时的key值。
 */
- (void)onReceived:(RCMessage *)message left:(int)nLeft object:(nullable id)object;

/**
 接收消息的回调方法

 - Parameter message: 当前接收到的消息
 - Parameter nLeft: 还剩余的未接收的消息数，left>=0
 - Parameter object: 消息监听设置的key值
 - Parameter offline: 是否是离线消息
 - Parameter hasPackage: SDK 拉取服务器的消息以包(package)的形式批量拉取，有 package 存在就意味着远端服务器还有消息尚未被 SDK
 拉取
 和上面的 - (void)onReceived:(RCMessage *)message left:(int)nLeft object:(id)object 功能完全一致，额外把
 offline 和 hasPackage 参数暴露，开发者可以根据 nLeft、offline、hasPackage 来决定何时的时机刷新 UI ；建议当 hasPackage=0
 并且 nLeft=0 时刷新 UI
 - Warning: 如果使用此方法，那么就不能再使用 RCIM 中 - (void)onReceived:(RCMessage *)message left:(int)nLeft
 object:(id)object 的使用，否则会出现重复操作的情形
 */
- (void)onReceived:(RCMessage *)message
              left:(int)nLeft
            object:(nullable id)object
           offline:(BOOL)offline
        hasPackage:(BOOL)hasPackage;

/*!
 离线消息接收完成
*/
- (void)onOfflineMessageSyncCompleted;

/*!
 消息被撤回的回调方法

 - Parameter messageId: 被撤回的消息ID

 被撤回的消息会变更为RCRecallNotificationMessage，App需要在UI上刷新这条消息。
 */
- (void)onMessageRecalled:(long)messageId __deprecated_msg("Use messageDidRecall: instead");

/*!
 消息被撤回的回调方法

 - Parameter message: 被撤回的消息

 如果不删除被撤回的消息，被撤回的原消息会变更为RCRecallNotificationMessage ，参数 message 就是变更后的消息，App需要在UI上刷新这条消息。
 如果删除被撤回的消息，参数 message 就是被撤回的原消息，App需要在UI上找到删除这条消息。
 和上面的 - (void)onMessageRecalled:(long)messageId 功能完全一致，只能选择其中一个使用。
 */
- (void)messageDidRecall:(RCMessage *)message;

/*!
 请求消息已读回执（收到需要阅读时发送回执的请求，收到此请求后在会话页面已经展示该 messageUId 对应的消息或者调用
 getHistoryMessages 获取消息的时候，包含此 messageUId 的消息，需要调用 sendMessageReadReceiptResponse
 接口发送消息阅读回执）

 - Parameter messageUId: 请求已读回执的消息ID
 - Parameter conversationType: conversationType
 - Parameter targetId: targetId
 */
- (void)onMessageReceiptRequest:(RCConversationType)conversationType
                       targetId:(NSString *)targetId
                     messageUId:(NSString *)messageUId;


/*!
 消息已读回执响应（收到阅读回执响应，可以按照 messageUId 更新消息的阅读数）
 - Parameter messageUId: 请求已读回执的消息ID
 - Parameter conversationType: conversationType
 - Parameter targetId: targetId
 - Parameter userIdList: 已读userId列表，字典类型 key:userId,value:readTime，例如：{"uid100001":1683708891523}
 */
- (void)onMessageReceiptResponse:(RCConversationType)conversationType
                        targetId:(NSString *)targetId
                      messageUId:(NSString *)messageUId
                      readerList:(nullable NSMutableDictionary *)userIdList;

/// 消息修改回调。
///
/// - Parameters:
///   - messages: 被修改的消息数组。
///
/// - Since: 5.26.0
- (void)onMessagesModified:(NSArray<RCMessage *> *)messages;

/// 离线的消息修改记录同步完成。
///
/// - Since: 5.26.0
- (void)onModifiedMessageSyncCompleted;

@end

#pragma mark - 发送消息被拦截监听器
@protocol RCMessageBlockDelegate <NSObject>

/*!
 发送消息被拦截的回调方法
 - Parameter blockedMessageInfo: 被拦截消息的相关信息
 */
- (void)messageDidBlock:(RCBlockedMessageInfo *)blockedMessageInfo;

@end

#pragma mark - 连接状态监听器

/*!
 IMLib连接状态的的监听器

 
 设置IMLib的连接状态监听器，请参考RCIMClient的setRCConnectionStatusChangeDelegate:方法。

 - Warning: 如果您使用IMLib，可以设置并实现此Delegate监听连接状态变化；
 如果您使用IMKit，请使用RCIM中的RCIMConnectionStatusDelegate监听连接状态，而不要使用此监听器，否则会导致IMKit中无法自动更新UI！
 */
@protocol RCConnectionStatusChangeDelegate <NSObject>

/*!
 IMLib连接状态的的监听器

 - Parameter status: SDK与融云服务器的连接状态

 如果您设置了IMLib连接监听之后，当SDK与融云服务器的连接状态发生变化时，会回调此方法。
 */
- (void)onConnectionStatusChanged:(RCConnectionStatus)status;

@end

#pragma mark - 输入状态监听器

/*!
 IMLib输入状态的的监听器

 设置IMLib的输入状态监听器，请参考RCIMClient的 setRCTypingStatusDelegate:方法。

 - Warning: 
 如果您使用IMLib，可以设置并实现此Delegate监听消息输入状态；如果您使用IMKit，请直接设置RCIM中的
 enableTypingStatus，而不要使用此监听器，否则会导致IMKit中无法自动更新UI！
 */
@protocol RCTypingStatusDelegate <NSObject>

/*!
 用户输入状态变化的回调

 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话目标ID
 - Parameter userTypingStatusList: 正在输入的RCUserTypingStatus列表（nil表示当前没有用户正在输入）
 
 当客户端收到用户输入状态的变化时，会回调此接口，通知发生变化的会话以及当前正在输入的RCUserTypingStatus列表。

 - Warning: 目前仅支持单聊。
 */
- (void)onTypingStatusChanged:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                       status:(nullable NSArray<RCUserTypingStatus *> *)userTypingStatusList;

@end

#pragma mark - 日志监听器
/*!
 IMLib日志的监听器

 
 设置IMLib日志的监听器，请参考RCIMClient的setRCLogInfoDelegate:方法。

 您可以通过logLevel来控制日志的级别。
 */
@protocol RCLogInfoDelegate <NSObject>

/*!
 IMLib日志的回调

 - Parameter logInfo: 日志信息
 */
- (void)didOccurLog:(NSString *)logInfo;

@end

#pragma mark - 阅后即焚

/**
 IMLib阅后即焚监听器
 设置代理请参考 RCIMClient 的 setRCMessageDestructDelegate: 方法。
 */
@protocol RCMessageDestructDelegate <NSObject>

/**
 消息正在焚烧

 - Parameter message: 消息对象
 - Parameter remainDuration: 剩余焚烧时间
 */
- (void)onMessageDestructing:(RCMessage *)message remainDuration:(long long)remainDuration;

@end

#pragma mark - 会话监听

@protocol RCConversationDelegate <NSObject>
/**
 开了消息断档功能之后，sdk 会同步实时会话，实时会话同步完成的回调
 */
- (void)conversationDidSync;

@optional
/// 调用接口 -[RCCoreClient getRemoteConversationListWithSuccess:error:] 获取远端会话列表的回调
/// - Parameter code: RC_SUCCESS 获取成功，其他值获取失败
- (void)remoteConversationListDidSync:(RCErrorCode)code;

@end

#pragma mark - 会话状态同步

/**
 IMLib 会话状态同步监听器
 设置代理请参考 RCIMClient 的 setRCConversationStatusChangeDelegate: 方法。
 */
@protocol RCConversationStatusChangeDelegate <NSObject>

@optional

/// 会话状态同步完成。
///
/// - Since: 5.7.8
- (void)conversationStatusDidSync:(RCErrorCode)code;

/**
 IMLib 会话状态同步的回调

 - Parameter conversationStatusInfos: 改变过的会话状态的数组
 */
- (void)conversationStatusDidChange:(NSArray<RCConversationStatusInfo *> *)conversationStatusInfos;

@end

#pragma mark - 消息扩展监听
/**
 消息扩展内容变化回调
 设置代理请参考 RCIMClient 的 messageExpansionDelegate 方法
 代理回调在非主线程
 */
@protocol RCMessageExpansionDelegate <NSObject>
/**
 消息扩展信息更改的回调

 - Parameter expansionDic: 消息扩展信息中更新的键值对
 - Parameter message: 消息

 expansionDic 只包含更新的键值对，不是全部的数据。如果想获取全部的键值对，请使用 message 的 expansionDic 属性。
*/
- (void)messageExpansionDidUpdate:(NSDictionary<NSString *, NSString *> *)expansionDic message:(RCMessage *)message;

/**
 消息扩展信息删除的回调

 - Parameter keyArray: 消息扩展信息中删除的键值对 key 列表
 - Parameter message: 消息

*/
- (void)messageExpansionDidRemove:(NSArray<NSString *> *)keyArray message:(RCMessage *)message;

@end

#pragma mark - 消息拦截器

/**
 消息拦截器
 */
@protocol RCMessageInterceptor <NSObject>

@optional

/**
 上传多媒体内容之前的回调
 
 - Parameter message: 待上传的多媒体消息
 - Returns: 处理后的消息
 如果返回的 message 或 message.content 为 nil，该条消息不会上传到服务，状态设置为 SentStatus_FAILED， 并回调失败
 */
- (RCMessage *)mediaMessageWillUpload:(RCMessage *)message;

/**
 消息保存到数据库，发送到服务前调用此回调
 
 - Parameter message: 待发送的消息
 - Returns: 处理后的消息
 如果返回的 message 或 message.content 为 nil，该条消息不会上传到服务，状态设置为 SentStatus_FAILED， 并回调失败
 */
- (RCMessage *)messageWillSendAfterDB:(RCMessage *)message;

/**
 接收到消息准备入库前的回调，开发者可以通过此回调对消息进行自定义处理。
 
 - Parameter message: 待入库的消息
 - Returns: 处理后的消息，SDK 会将返回的消息入库并通过 RCIMClientReceiveMessageDelegate 的 onReceived 方法回调给上层
 如果返回的 message 或 message.content 为 nil, RCIMClientReceiveMessageDelegate 的 onReceived 方法会将原消息回调给上层
 */
- (RCMessage *)messageDidReceiveBeforeDB:(RCMessage *)message;

@end

#pragma mark - 媒体文件请求拦截器

/**
 媒体文件上传&下载拦截器
 */
@protocol RCDownloadInterceptor <NSObject>

/**
 下载前的同步回调
 - Remark: 推荐使用下载的异步回调接口
 
 - Parameter request: request 请求
 - Returns: request 请求，返回值不能为 nil，否则无法正常下载
 - Since: 5.1.2
 */
- (NSMutableURLRequest *)onDownloadRequest:(NSMutableURLRequest *)request;

/**
 下载前的异步回调
 
 - Parameter request request 请求
 - Parameter requestHandler 请求，返回值不能为 nil，否则无法正常下载
 - Remark: IMLib 不做线程切换，下载线程会使用当前回调的线程
 - Since: 5.8.0
 */
- (void)onDownloadRequest:(nonnull NSMutableURLRequest *)request
       withRequestHandler:(void (^)(NSMutableURLRequest *_Nonnull handledRequest))requestHandler;

/**
 上传前的异步回调
 
 - Parameter request request 请求
 - Parameter requestHandler 请求，返回值不能为 nil，否则无法正常上传
 - Remark: IMLib 不做线程切换，上传线程会使用当前回调的线程
 - Since: 5.8.0
 */
- (void)onUploadRequest:(nonnull NSMutableURLRequest *)request
     withRequestHandler:(void (^)(NSMutableURLRequest *_Nonnull handledRequest))requestHandler;


@end

#pragma mark - 超级群

/**
 超级群已读时间同步代理
 */
@protocol RCUltraGroupReadTimeDelegate <NSObject>

/**
 超级群已读时间同步
 
 - Parameter targetId: 会话 ID
 - Parameter channelId: 频道 ID
 - Parameter readTime: 已读时间
 */
- (void)onUltraGroupReadTimeReceived:(NSString *)targetId channelId:(NSString *)channelId readTime:(long long)readTime;

@end

/**
 超级群输入状态代理
 */
@protocol RCUltraGroupTypingStatusDelegate <NSObject>
/*!
 用户输入状态变化的回调

 - Parameter infoArr: 正在输入的RCUltraGroupTypingStatusInfo列表（nil表示当前没有用户正在输入）

 当客户端收到用户输入状态的变化时，会回调此接口，通知发生变化的会话以及当前正在输入的RCUltraGroupTypingStatusInfo列表。
 */
- (void)onUltraGroupTypingStatusChanged:(NSArray<RCUltraGroupTypingStatusInfo *> *)infoArr;
@end

/*!
 超级群消息变化回调
 */
@protocol RCUltraGroupMessageChangeDelegate <NSObject>

/*!
 消息扩展更新，删除
 
 - Parameter messages: 消息集合
 */
- (void)onUltraGroupMessageExpansionUpdated:(NSArray<RCMessage *> *)messages;

/*!
 消息内容发生变更
 
 - Parameter messages: 消息集合
 */
- (void)onUltraGroupMessageModified:(NSArray<RCMessage *> *)messages;

/*!
 消息撤回
 
 - Parameter messages: 消息集合
 */
- (void)onUltraGroupMessageRecalled:(NSArray<RCMessage *> *)messages;

@end

/*!
 数据库状态监听器
 
  - Since: 5.10.4
 */
@protocol RCDatabaseStatusDelegate <NSObject>

/*!
 数据库开始升级

 - Since: 5.10.4
 */
- (void)databaseUpgradeWillStart;

/*!
 数据库升级完成

 - Since: 5.10.4
 */
- (void)databaseUpgradeDidComplete:(RCErrorCode)code;

/*!
 数据库升级中
 
 - Parameter progress: 升级进度【0-100】
 - Since: 5.10.4
 */
- (void)databaseIsUpgrading:(int)progress;
@end

@class RCStreamMessageChunkInfo;

/// 流式消息事件代理。
/// - Since: 5.16.0
@protocol RCStreamMessageRequestEventDelegate <NSObject>

@optional

/// 请求准备完成回调，如果该消息之前是异常中止的，会清理异常数据。
- (void)didReceiveInitEventWithMessageUId:(NSString *)messageUId;

/// 收到流式消息请求增量数据的回调。
- (void)didReceiveDeltaEventWithMessage:(RCMessage *)message chunkInfo:(RCStreamMessageChunkInfo *)chunkInfo;

/// 收到流式消息请求接收完成的回调。
- (void)didReceiveCompleteEventWithMessageUId:(NSString *)messageUId code:(RCErrorCode)code;

@end

/// 用户级别事件代理。
///
/// - Warning: 需要开启用户级别设置。
/// 可以用 `RCCoreClient` 的 `getAppSettings` 接口，查询相关配置 `isUserSettingsEnabled`。
///
/// - Since: 5.7.8
@protocol RCUserSettingsDelegate <NSObject>

@optional

/// 用户级别的所有配置信息同步完成回调。
///
/// - Note: 在连接成功后，SDK 会同步当前用户的所有配置，同步完成后回调该方法。
///
/// - Parameter code: 错误码。
- (void)userSettingsDidSync:(RCErrorCode)code;

@end

/// 机器人事件代理。
/// - Since: 5.28.0
@protocol RCRobotEventDelegate <NSObject>

/// 机器人同步完成回调
/// 
/// - Parameter code: 错误码
/// - Parameter robots: 连接后同步服务器的增量机器人数组
- (void)onRobotSyncCompleted:(RCErrorCode)code
                      robots:(NSArray<RCRobotInfo *> *_Nullable)robots;

@end

NS_ASSUME_NONNULL_END

#endif /* RCIMClientProtocol_h */
