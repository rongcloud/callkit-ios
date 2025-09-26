/**
 * Copyright (c) 2014-2015, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */

//  RCCoreClient.h
//  RongIMLibCore
//  Created by xugang on 14/12/23.

#ifndef __RongCoreClient
#define __RongCoreClient
#import <Foundation/Foundation.h>

#import <RongIMLibCore/RCConversation.h>
#import <RongIMLibCore/RCMessage.h>
#import <RongIMLibCore/RCPushProfile.h>
#import <RongIMLibCore/RCSearchConversationResult.h>
#import <RongIMLibCore/RCReadReceiptDefine.h>
#import <RongIMLibCore/RCUploadMediaStatusListener.h>
#import <RongIMLibCore/RCUserInfo.h>
#import <RongIMLibCore/RCSendMessageOption.h>
#import <RongIMLibCore/RCRemoteHistoryMsgOption.h>
#import <RongIMLibCore/RCIMClientProtocol.h>
#import <RongIMLibCore/RCTagInfo.h>
#import <RongIMLibCore/RCConversationIdentifier.h>
#import <RongIMLibCore/RCConversationTagInfo.h>
#import <RongIMLibCore/RCTagProtocol.h>
#import <RongIMLibCore/RCImageCompressConfig.h>
#import <RongIMLibCore/RCHistoryMessageOption.h>
#import <RongIMLibCore/RCClearConversationOption.h>
#import <RongIMLibCore/RCRecallMessageOption.h>
#import <RongIMLibCore/RCGroupReadReceiptV2Protocol.h>
#import <RongIMLibCore/RCGroupMessageReaderV2.h>
#import <RongIMLibCore/RCDownloadInfo.h>

#import <RongIMLibCore/RCUserProfile.h>

#import <RongIMLibCore/RCGroupEventDelegate.h>
#import <RongIMLibCore/RCGroupInfo.h>
#import <RongIMLibCore/RCGroupApplicationInfo.h>
#import <RongIMLibCore/RCQuitGroupConfig.h>
#import <RongIMLibCore/RCPagingQueryOption.h>
#import <RongIMLibCore/RCPagingQueryResult.h>
#import <RongIMLibCore/RCFollowInfo.h>

#import <RongIMLibCore/RCFriendInfo.h>
#import <RongIMLibCore/RCFriendRelationInfo.h>
#import <RongIMLibCore/RCFriendApplicationInfo.h>
#import <RongIMLibCore/RCFriendEventDelegate.h>

#import <RongIMLibCore/RCStreamMessageRequestParams.h>

NS_ASSUME_NONNULL_BEGIN

@class RCIMProxy;
@class RCAppSettings;
@class RCInitOption, RCConversationTopOption;
@class RCSearchMessageParams;
@class RCSubscribeEvent, RCSubscribeInfoEvent, RCSubscribeEventRequest;
@class RCMessageIdentifier;
@class RCConversationBatchDeletionParams;
@class RCAppSettings;
@class RCGetUnreadMentionMeConversationListParams;
@class RCSubscribeUserOnlineStatus;
@class RCEditedMessageDraft;
@protocol RCSubscribeEventDelegate;

/// 收到已读回执的 Notification
///
/// 收到消息已读回执之后，IMLibCore 会分发此通知。
///
/// Notification 的 object 为 nil，userInfo 为 NSDictionary 对象，
/// 其中 key 值分别为 @"cType"、@"tId"、@"messageTime",
/// 对应的 value 为会话类型的 NSNumber 对象、会话的 targetId、已阅读的最后一条消息的 sendTime。
/// 如：
/// ```objc
/// NSNumber *type = [notification.userInfo objectForKey:@"cType"];
/// NSNumber *time = [notification.userInfo objectForKey:@"messageTime"];
/// NSString *targetId = [notification.userInfo objectForKey:@"tId"];
/// NSString *channelId = [notification.userInfo objectForKey:@"cId"];
/// NSString *fromUserId = [notification.userInfo objectForKey:@"fId"];
/// ```
/// 收到这个消息之后可以更新这个会话中 messageTime 以前的消息 UI 为已读（底层数据库消息状态已经改为已读）。
///
/// - Remark: 事件监听
FOUNDATION_EXPORT NSString *const RCLibDispatchReadReceiptNotification;

#pragma mark - IMLibCore 核心类

/// 融云 IMLibCore 核心类
///  
/// 您需要通过 sharedCoreClient 方法，获取单例对象。
@interface RCCoreClient : NSObject

/// 获取融云通讯能力库 IMLibCore 的核心类单例
///
/// - Returns: 融云通讯能力库 IMLibCore 的核心单例类
///
/// 您可以通过此方法，获取 IMLibCore 的单例，访问对象中的属性和方法。
/// - Since: 5.0.0
+ (instancetype)sharedCoreClient;


#pragma mark - SDK初始化

/// 初始化融云 SDK
///
/// - Parameter appKey: 从融云开发者平台创建应用后获取到的 App Key
/// - Parameter option: 设置配置信息，详细配置项信息请查看 RCInitOption.h 文件
///
/// 初始化后，SDK 会监听 app 生命周期，用于判断应用处于前台、后台，根据前后台状态调整链接心跳
///
/// 您在使用融云 SDK 所有功能（包括显示 SDK 中或者继承于 SDK 的 View）之前，您必须先调用此方法初始化 SDK。
/// 在 App 整个生命周期中，您只需要执行一次初始化。
///
/// - Warning: 如果您使用 IMLibCore，请使用此方法初始化 SDK；
/// 如果您使用 IMKit，请使用 RCIM 中的同名方法初始化，而不要使用此方法。
///
/// - Remark: 连接
///
/// - Since: 5.4.1
- (void)initWithAppKey:(NSString *)appKey option:(nullable RCInitOption *)option;

/// 设置 deviceToken（已兼容 iOS 13），用于远程推送
///
/// - Parameter deviceTokenData: 从系统获取到的设备号 deviceTokenData  (不需要处理)
///
/// deviceToken 是系统提供的，从苹果服务器获取的，用于 APNs 远程推送必须使用的设备唯一值。
/// 您需要将 -application:didRegisterForRemoteNotificationsWithDeviceToken: 获取到的 deviceToken 作为参数传入此方法。
///
/// 如：
/// ```objc
/// - (void)application:(UIApplication *)application
/// didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
///     [[RCCoreClient sharedCoreClient] setDeviceTokenData:deviceToken];
/// }
/// ```
/// - Remark: 功能设置
/// - Since: 5.0.0
- (void)setDeviceTokenData:(NSData *)deviceTokenData;

/// 设置 deviceToken，用于远程推送
///
/// - Parameter deviceToken: 从系统获取到的设备号 deviceToken
///
///
/// deviceToken 是系统提供的，从苹果服务器获取的，用于 APNs 远程推送必须使用的设备唯一值。
/// 您需要将 -application:didRegisterForRemoteNotificationsWithDeviceToken: 获取到的
/// deviceToken，转换成十六进制字符串，作为参数传入此方法。
///
/// 如：
/// ```objc
/// - (void)application:(UIApplication *)application
/// didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
///     NSString *token = [self getHexStringForData:deviceToken];
///     [[RCCoreClient sharedCoreClient] setDeviceToken:token];
/// }
///
/// - (NSString *)getHexStringForData:(NSData *)data {
///     NSUInteger length = [data length];
///     char *chars = (char *)[data bytes];
///     NSMutableString *hexString = [[NSMutableString alloc] init];
///     for (NSUInteger i = 0; i < length; i ++) {
///         [hexString appendString:[NSString stringWithFormat:@"%0.2hhx", chars[i]]];
///     }
///     return hexString;
/// }
/// ```
/// - Remark: 功能设置
/// - Since: 5.0.0
- (void)setDeviceToken:(NSString *)deviceToken;

#pragma mark - 连接与断开服务器

/// 与融云服务器建立连接
///
/// - Parameter token: 从您服务器端获取的 token (用户身份令牌)
/// - Parameter dbOpenedBlock: 本地消息数据库打开的回调
/// - Parameter successBlock: 连接建立成功的回调 [ userId: 当前连接成功所用的用户 ID]
/// - Parameter errorBlock: 连接建立失败的回调，触发该回调代表 SDK 无法继续重连 [errorCode: 连接失败的错误码]
///
/// 调用该接口，SDK 会在连接失败之后尝试重连，直到连接成功或者出现 SDK 无法处理的错误（如 token 非法）。
/// 如果您不想一直进行重连，可以使用 connectWithToken:timeLimit:dbOpened:success:error: 接口并设置连接超时时间 timeLimit。
///
/// 连接成功后，SDK 将接管所有的重连处理。当因为网络原因断线的情况下，SDK 会不停重连直到连接成功为止，不需要您做额外的连接操作。
///
/// 对于 errorBlock 需要特定关心 tokenIncorrect 的情况：
/// 一是 token 错误，请您检查客户端初始化使用的 AppKey 和您服务器获取 token 使用的 AppKey 是否一致；
/// 二是 token 过期，是因为您在开发者后台设置了 token 过期时间，您需要请求您的服务器重新获取 token 并再次用新的 token 建立连接。
/// 在此种情况下，您需要请求您的服务器重新获取 token 并建立连接，但是注意避免无限循环，以免影响 App 用户体验。
///
/// - Warning: 如果您使用 IMLibCore，请使用此方法建立与融云服务器的连接；
/// 如果您使用 IMKit，请使用 RCIM 中的同名方法建立与融云服务器的连接，而不要使用此方法。
///
/// 此方法的回调并非为原调用线程，您如果需要进行 UI 操作，请注意切换到主线程。
/// - Since: 5.0.0
- (void)connectWithToken:(NSString *)token
                dbOpened:(nullable void (^)(RCDBErrorCode code))dbOpenedBlock
                 success:(nullable void (^)(NSString *userId))successBlock
                   error:(nullable void (^)(RCConnectErrorCode errorCode))errorBlock;

/// 与融云服务器建立连接
///
/// - Parameter token: 从您服务器端获取的 token (用户身份令牌)
/// - Parameter timeLimit: SDK 连接的超时时间，单位：秒
/// timeLimit <= 0，SDK 会一直连接，直到连接成功或者出现 SDK 无法处理的错误（如 token 非法）。
/// timeLimit > 0，SDK 最多连接 timeLimit 秒，超时时返回 RC_CONNECT_TIMEOUT 错误，并不再重连。
/// - Parameter dbOpenedBlock: 本地消息数据库打开的回调
/// - Parameter successBlock: 连接建立成功的回调 [ userId: 当前连接成功所用的用户 ID]
/// - Parameter errorBlock: 连接建立失败的回调，触发该回调代表 SDK 无法继续重连 [errorCode: 连接失败的错误码]
///
/// 调用该接口，SDK 会在 timeLimit 秒内尝试重连，直到出现下面三种情况之一：
/// 第一、连接成功，回调 successBlock(userId)。
/// 第二、超时，回调 errorBlock(RC_CONNECT_TIMEOUT)。
/// 第三、出现 SDK 无法处理的错误，回调 errorBlock(errorCode)（如 token 非法）。
///
/// 连接成功后，SDK 将接管所有的重连处理。当因为网络原因断线的情况下，SDK 会不停重连直到连接成功为止，不需要您做额外的连接操作。
///
/// 对于 errorBlock 需要特定关心 tokenIncorrect 的情况：
/// 一是 token 错误，请您检查客户端初始化使用的 AppKey 和您服务器获取 token 使用的 AppKey 是否一致；
/// 二是 token 过期，是因为您在开发者后台设置了 token 过期时间，您需要请求您的服务器重新获取 token 并再次用新的 token 建立连接。
/// 在此种情况下，您需要请求您的服务器重新获取 token 并建立连接，但是注意避免无限循环，以免影响 App 用户体验。
///
/// - Warning: 如果您使用 IMLibCore，请使用此方法建立与融云服务器的连接；
/// 如果您使用 IMKit，请使用 RCIM 中的同名方法建立与融云服务器的连接，而不要使用此方法。
///
/// 此方法的回调并非为原调用线程，您如果需要进行 UI 操作，请注意切换到主线程。
/// - Since: 5.0.0
- (void)connectWithToken:(NSString *)token
               timeLimit:(int)timeLimit
                dbOpened:(nullable void (^)(RCDBErrorCode code))dbOpenedBlock
                 success:(nullable void (^)(NSString *userId))successBlock
                   error:(nullable void (^)(RCConnectErrorCode errorCode))errorBlock;

/// 与融云服务器建立连接。
///
/// - Parameter userId: 融云服务器的用户 ID，与 `token` 对应。
/// - Parameter token: 融云服务器端的用户身份令牌。
/// - Parameter timeLimit: SDK 连接的超时时间，单位：秒。
///     timeLimit 大于 0 时，SDK 最多连接 timeLimit 秒，超时时返回 `RC_CONNECT_TIMEOUT` 错误，并不再重连。
///     timeLimit 小于或等于 0 时，直到连接成功或者出现 SDK 无法处理的错误（如 token 非法）。
/// - Parameter dbOpenedBlock: 本地消息数据库打开的回调。
/// - Parameter successBlock: 连接建立成功的回调 [ userId: 当前连接成功所用的用户 ID]。
/// - Parameter errorBlock: 连接建立失败的回调，触发该回调代表 SDK 无法继续重连 [errorCode: 连接失败的错误码]。对于 errorBlock 需要特定关心 tokenIncorrect 的情况：
///     一是 token 错误，请您检查客户端初始化使用的 AppKey 和您服务器获取 token 使用的 AppKey 是否一致；
///     二是 token 过期，是因为您在开发者后台设置了 token 过期时间，您需要请求您的服务器重新获取 token 并再次用新的 token 建立连接。但要注意避免无限循环，以免影响 App 用户体验。
///
/// - Note:
///     连接成功后，SDK 将接管所有的重连处理。当因为网络原因断线的情况下，SDK 会不停重连直到连接成功为止，不需要您做额外的连接操作。
///
/// - Warning:
///     此方法的回调线程是 SDK 的内部线程，不是该接口的调用线程。您如果需要进行 UI 操作，请注意切换到主线程。
///
/// - Since: 5.20.0
- (void)connectWithUserId:(NSString *)userId
                    token:(NSString *)token
                timeLimit:(int)timeLimit
                 dbOpened:(nullable void (^)(RCDBErrorCode code))dbOpenedBlock
                  success:(nullable void (^)(NSString *userId))successBlock
                    error:(nullable void (^)(RCConnectErrorCode errorCode))errorBlock;

/// 与融云服务器建立连接。
///
/// - Parameter userId: 融云服务器的用户 ID，与 `token` 对应。
/// - Parameter token: 融云服务器端的用户身份令牌。
/// - Parameter timeLimit: SDK 连接的超时时间，单位：秒。
///     timeLimit 大于 0 时，SDK 最多连接 timeLimit 秒，超时时返回 `RC_CONNECT_TIMEOUT` 错误，并不再重连。
///     timeLimit 小于或等于 0 时，直到连接成功或者出现 SDK 无法处理的错误（如 token 非法）。
/// - Parameter dbOpenedBlock: 本地消息数据库打开的回调。
/// - Parameter dbCreatedBlock: 本地消息数据库是否是重建的回调。
/// - Parameter successBlock: 连接建立成功的回调 [ userId: 当前连接成功所用的用户 ID]。
/// - Parameter errorBlock: 连接建立失败的回调，触发该回调代表 SDK 无法继续重连 [errorCode: 连接失败的错误码]。对于 errorBlock 需要特定关心 tokenIncorrect 的情况：
///     一是 token 错误，请您检查客户端初始化使用的 AppKey 和您服务器获取 token 使用的 AppKey 是否一致；
///     二是 token 过期，是因为您在开发者后台设置了 token 过期时间，您需要请求您的服务器重新获取 token 并再次用新的 token 建立连接。但要注意避免无限循环，以免影响 App 用户体验。
///
/// - Note:
///     连接成功后，SDK 将接管所有的重连处理。当因为网络原因断线的情况下，SDK 会不停重连直到连接成功为止，不需要您做额外的连接操作。
///
/// - Warning:
///     此方法的回调线程是 SDK 的内部线程，不是该接口的调用线程。您如果需要进行 UI 操作，请注意切换到主线程。
///
/// - Since: 5.28.0
- (void)connectWithUserId:(NSString *)userId
                    token:(NSString *)token
                timeLimit:(int)timeLimit
                 dbOpened:(nullable void (^)(RCDBErrorCode code))dbOpenedBlock
                dbCreated:(nullable void (^)(BOOL isRecreated))dbCreatedBlock
                  success:(nullable void (^)(NSString *userId))successBlock
                    error:(nullable void (^)(RCConnectErrorCode errorCode))errorBlock;

/// 断开与融云服务器的连接
///
/// - Parameter isReceivePush: App 在断开连接之后，是否还接收远程推送
///
///
/// 因为 SDK 在前后台切换或者网络出现异常都会自动重连，会保证连接的可靠性。
/// 所以除非您的 App 逻辑需要登出，否则一般不需要调用此方法进行手动断开。
///
/// - Warning: 如果您使用 IMLibCore，请使用此方法断开与融云服务器的连接；
/// 如果您使用 IMKit，请使用 RCIM 中的同名方法断开与融云服务器的连接，而不要使用此方法。
///
/// isReceivePush 指断开与融云服务器的连接之后，是否还接收远程推送。
/// [[RCCoreClient sharedCoreClient] disconnect:YES] 与 [[RCCoreClient sharedCoreClient]
/// disconnect] 完全一致；
/// [[RCCoreClient sharedCoreClient] disconnect:NO] 与 [ [RCCoreClient sharedCoreClient]
/// logout] 完全一致。
/// 您只需要按照您的需求，使用 disconnect: 与 disconnect 以及 logout 三个接口其中一个即可。
///
/// - Remark: 连接
/// - Since: 5.0.0
- (void)disconnect:(BOOL)isReceivePush;

/// 断开与融云服务器的连接，但仍然接收远程推送
///
///
/// 因为 SDK 在前后台切换或者网络出现异常都会自动重连，会保证连接的可靠性。
/// 所以除非您的 App 逻辑需要登出，否则一般不需要调用此方法进行手动断开。
///
/// - Warning: 如果您使用 IMLibCore，请使用此方法断开与融云服务器的连接；
/// 如果您使用 IMKit，请使用 RCIM 中的同名方法断开与融云服务器的连接，而不要使用此方法。
///
/// [[RCCoreClient sharedCoreClient] disconnect:YES] 与 [[RCCoreClient sharedCoreClient]
/// disconnect] 完全一致；
/// [[RCCoreClient sharedCoreClient] disconnect:NO] 与 [[RCCoreClient sharedCoreClient]
/// logout] 完全一致。
/// 您只需要按照您的需求，使用 disconnect: 与 disconnect 以及 logout 三个接口其中一个即可。
///
/// - Remark: 连接
/// - Since: 5.0.0
- (void)disconnect;

/// 断开与融云服务器的连接，并不再接收远程推送
///
///
/// 因为 SDK 在前后台切换或者网络出现异常都会自动重连，会保证连接的可靠性。
/// 所以除非您的 App 逻辑需要登出，否则一般不需要调用此方法进行手动断开。
///
/// - Warning: 如果您使用 IMKit，请使用此方法断开与融云服务器的连接；
/// 如果您使用 IMLibCore，请使用 RCCoreClient 中的同名方法断开与融云服务器的连接，而不要使用此方法。
///
/// [[RCCoreClient sharedCoreClient] disconnect:YES] 与 [[RCCoreClient sharedCoreClient]
/// disconnect] 完全一致；
/// [[RCCoreClient sharedCoreClient] disconnect:NO] 与 [[RCCoreClient sharedCoreClient]
/// logout] 完全一致。
/// 您只需要按照您的需求，使用 disconnect: 与 disconnect 以及 logout 三个接口其中一个即可。
///
/// - Remark: 连接
/// - Since: 5.0.0
- (void)logout;

/// 设置断线重连时是否踢出当前正在重连的设备
///
///
/// 用户没有开通多设备登录功能的前提下，同一个账号在一台新设备上登录的时候，会把这个账号在之前登录的设备上踢出。
/// 由于 SDK 有断线重连功能，存在下面情况。
/// 用户在 A 设备登录，A 设备网络不稳定，没有连接成功，SDK 启动重连机制。
/// 用户此时又在 B 设备登录，B 设备连接成功。
/// A 设备网络稳定之后，用户在 A 设备连接成功，B 设备被踢出。
/// 这个接口就是为这种情况加的。
/// 设置 enable 为 YES 时，SDK 重连的时候发现此时已有别的设备连接成功，不再强行踢出已有设备，而是踢出重连设备。
///
/// - Parameter enable: 是否踢出重连设备
///
/// - Remark: 功能设置
/// - Since: 5.0.0
- (void)setReconnectKickEnable:(BOOL)enable;

/// 是否允许 SDK 排重，默认值为 YES
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
/// 该接口不支持聊天室、超级群会话类型关闭消息排重。
///
/// - Parameter enableCheck: 是否允许 SDK 排重
///
/// - Since: 5.3.4
- (void)setCheckDuplicateMessage:(bool)enableCheck;

#pragma mark - 连接状态监听

/// 添加 IMLib 连接状态监听
///
/// - Parameter delegate: 代理
/// - Since: 5.1.5
- (void)addConnectionStatusChangeDelegate:(id<RCConnectionStatusChangeDelegate>)delegate
    NS_SWIFT_NAME(addConnectionStatusChangeDelegate(_:));

/// 移除 IMLib 连接状态监听
///
/// - Parameter delegate: 代理
/// - Since: 5.1.5
- (void)removeConnectionStatusChangeDelegate:(id<RCConnectionStatusChangeDelegate>)delegate
    NS_SWIFT_NAME(removeConnectionStatusChangeDelegate(_:));

/// 获取当前 SDK 的连接状态
///
/// - Returns: 当前 SDK 的连接状态
///
/// - Remark: 数据获取
/// - Since: 5.0.0
- (RCConnectionStatus)getConnectionStatus;

/// 获取当前的网络状态
///
/// - Returns: 当前的网路状态
///
/// - Remark: 数据获取
/// - Since: 5.0.0
- (RCNetworkStatus)getCurrentNetworkStatus;

/// SDK 当前所处的运行状态
///
/// - Remark: 数据获取
/// - Since: 5.0.0
@property (nonatomic, assign, readonly) RCSDKRunningMode sdkRunningMode;

/// 媒体文件上传&下载拦截器
///
/// - Remark: 功能设置
/// - Since: 5.1.2
@property (nonatomic, weak, nullable) id<RCDownloadInterceptor> downloadInterceptor;

#pragma mark - 阅后即焚监听

///
/// 设置 IMLibCore 的阅后即焚监听器
///
/// - Parameter delegate: 阅后即焚监听器
/// 可以设置并实现此 Delegate 监听消息焚烧
/// - Warning: 如果您使用 IMKit，请不要使用此监听器，否则会导致 IMKit 中无法自动更新 UI！
///
/// - Remark: 功能设置
/// - Since: 5.0.0
- (void)setRCMessageDestructDelegate:(nullable id<RCMessageDestructDelegate>)delegate;

#pragma mark - 用户信息

/// 当前登录用户的用户信息
///
/// 用于与融云服务器建立连接之后，设置当前用户的用户信息。
///
/// - Warning: 如果传入的用户信息中的用户 ID 与当前登录的用户 ID 不匹配，则将会忽略。
/// 如果您使用 IMLibCore，请使用此字段设置当前登录用户的用户信息；
/// 如果您使用 IMKit，请使用 RCIM 中的 currentUserInfo 设置当前登录用户的用户信息，而不要使用此字段。
///
/// - Remark: 数据获取
/// - Since: 5.0.0
@property (nonatomic, strong, nullable) RCUserInfo *currentUserInfo;

#pragma mark - 消息接收与发送

/// 注册自定义的消息类型
///
/// - Parameter messageClass: 自定义消息的类，该自定义消息需要继承于 RCMessageContent
///
///
/// 如果您需要自定义消息，必须调用此方法注册该自定义消息的消息类型，否则 SDK 将无法识别和解析该类型消息。
/// 请在初始化 appkey 之后，token 连接之前调用该方法注册自定义消息
///
/// - Warning: 如果您使用 IMLibCore，请使用此方法注册自定义的消息类型；
/// 如果您使用 IMKit，请使用 RCIM 中的同名方法注册自定义的消息类型，而不要使用此方法。
///
/// - Remark: 消息操作
/// - Since: 5.0.0
- (void)registerMessageType:(Class)messageClass;

#pragma mark 消息发送

/// 异步发送消息
///
/// - Parameter conversationType: 发送消息的会话类型
/// - Parameter targetId: 发送消息的会话 ID
/// - Parameter content: 消息的内容
/// - Parameter pushContent: 接收方离线时需要显示的远程推送内容
/// - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter attachedBlock: 入库回调 [message: 已存数据库的消息体]
/// - Parameter successBlock: 消息发送成功的回调 [messageId: 消息的 ID]
/// - Parameter errorBlock: 消息发送失败的回调 [nErrorCode: 发送失败的错误码，messageId:消息的 ID]
///
///
/// 当接收方离线并允许远程推送时，会收到远程推送。
/// 远程推送中包含两部分内容，一是 pushContent，用于显示；二是 pushData，用于携带不显示的数据。
///
/// SDK 内置的消息类型，如果您将 pushContent 和 pushData 置为 nil，会使用默认的推送格式进行远程推送。
/// 自定义类型的消息，需要您自己设置 pushContent 和 pushData 来定义推送内容，否则将不会进行远程推送。
///
/// 如果您使用此方法发送图片消息，需要您自己实现图片的上传，构建一个 RCImageMessage 对象，
/// 并将 RCImageMessage 中的 imageUrl 字段设置为上传成功的 URL 地址，然后使用此方法发送。
///
/// 如果您使用此方法发送文件消息，需要您自己实现文件的上传，构建一个 RCFileMessage 对象，
/// 并将 RCFileMessage 中的 fileUrl 字段设置为上传成功的 URL 地址，然后使用此方法发送。
///
/// - Warning: 如果您使用 IMLibCore，可以使用此方法发送消息；
/// 如果您使用 IMKit，请使用 RCIM 中的同名方法发送消息，否则不会自动更新 UI。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)sendMessage:(RCConversationType)conversationType
           targetId:(NSString *)targetId
            content:(RCMessageContent *)content
        pushContent:(nullable NSString *)pushContent
           pushData:(nullable NSString *)pushData
           attached:(nullable void (^)(RCMessage *_Nullable message))attachedBlock
            success:(nullable void (^)(long messageId))successBlock
              error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock;

/// 异步发送消息
///
/// - Parameter conversationType: 发送消息的会话类型
/// - Parameter targetId: 发送消息的会话 ID
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
/// 自定义类型的消息，需要您自己设置 pushContent 和 pushData 来定义推送内容，否则将不会进行远程推送。
///
/// 如果您使用此方法发送图片消息，需要您自己实现图片的上传，构建一个 RCImageMessage 对象，
/// 并将 RCImageMessage 中的 imageUrl 字段设置为上传成功的 URL 地址，然后使用此方法发送。
///
/// 如果您使用此方法发送文件消息，需要您自己实现文件的上传，构建一个 RCFileMessage 对象，
/// 并将 RCFileMessage 中的 fileUrl 字段设置为上传成功的 URL 地址，然后使用此方法发送。
///
/// - Warning: 如果您使用 IMLibCore，可以使用此方法发送消息；
/// 如果您使用 IMKit，请使用 RCIM 中的同名方法发送消息，否则不会自动更新 UI。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)sendMessage:(RCConversationType)conversationType
           targetId:(NSString *)targetId
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
/// 自定义类型的消息，需要您自己设置 pushContent 和 pushData 来定义推送内容，否则将不会进行远程推送。
///
/// 如果您需要上传图片到自己的服务器，需要构建一个 RCImageMessage 对象，
/// 并将 RCImageMessage 中的 imageUrl 字段设置为上传成功的 URL 地址，然后使用 RCCoreClient 的
/// sendMessage:targetId:content:pushContent:pushData:success:error:方法
/// 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。
///
/// 如果您需要上传文件到自己的服务器，构建一个 RCFileMessage 对象，
/// 并将 RCFileMessage 中的 fileUrl 字段设置为上传成功的 URL 地址，然后使用 RCCoreClient 的
/// sendMessage:targetId:content:pushContent:pushData:success:error:方法
/// 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。
///
/// - Warning: 如果您使用 IMLibCore，可以使用此方法发送媒体消息；
/// 如果您使用 IMKit，请使用 RCIM 中的同名方法发送媒体消息，否则不会自动更新 UI。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)sendMediaMessage:(RCConversationType)conversationType
                targetId:(NSString *)targetId
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
/// - Parameter content: 消息的内容
/// - Parameter pushContent: 接收方离线时需要显示的远程推送内容
/// - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter attachedBlock: 入库回调 [message: 已存数据库的消息体]
/// - Parameter uploadPrepareBlock: 媒体文件上传进度更新的监听
/// [uploadListener:当前的发送进度监听]
/// - Parameter progressBlock: 消息发送进度更新的回调 [progress:当前的发送进度，0
/// <= progress <= 100, messageId:消息的 ID]
/// - Parameter successBlock: 消息发送成功的回调 [messageId:消息的 ID]
/// - Parameter errorBlock: 消息发送失败的回调 [errorCode:发送失败的错误码，
/// messageId:消息的 ID]
/// - Parameter cancelBlock: 用户取消了消息发送的回调 [messageId:消息的 ID]
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)sendMediaMessage:(RCConversationType)conversationType
                targetId:(NSString *)targetId
                 content:(RCMessageContent *)content
             pushContent:(nullable NSString *)pushContent
                pushData:(nullable NSString *)pushData
                attached:(nullable void (^)(RCMessage *_Nullable message))attachedBlock
           uploadPrepare:(nullable void (^)(RCUploadMediaStatusListener *uploadListener))uploadPrepareBlock
                progress:(nullable void (^)(int progress, long messageId))progressBlock
                 success:(nullable void (^)(long messageId))successBlock
                   error:(nullable void (^)(RCErrorCode errorCode, long messageId))errorBlock
                  cancel:(nullable void (^)(long messageId))cancelBlock;

/// 异步发送媒体消息 (上传图片或文件等媒体信息到指定的服务器)
///
/// - Parameter message: 将要发送的消息实体（需要保证 message 中的 conversationType，targetId，messageContent 是有效值)
/// - Parameter pushContent: 接收方离线时需要显示的远程推送内容
/// - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter attachedBlock: 入库回调 [message: 已存数据库的消息体]
/// - Parameter uploadPrepareBlock: 媒体文件上传进度更新的监听
/// [uploadListener:当前的发送进度监听]
/// - Parameter progressBlock: 消息发送进度更新的回调 [progress:当前的发送进度，0
/// <= progress <= 100, messageId:消息的 ID]
/// - Parameter successBlock: 消息发送成功的回调 [messageId:消息的 ID]
/// - Parameter errorBlock: 消息发送失败的回调 [errorCode:发送失败的错误码，
/// messageId:消息的 ID]
/// - Parameter cancelBlock: 用户取消了消息发送的回调 [messageId:消息的 ID]
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)sendMediaMessage:(RCMessage *)message
             pushContent:(nullable NSString *)pushContent
                pushData:(nullable NSString *)pushData
                attached:(nullable void (^)(RCMessage *_Nullable message))attachedBlock
           uploadPrepare:(nullable void (^)(RCUploadMediaStatusListener *uploadListener))uploadPrepareBlock
                progress:(nullable void (^)(int progress, long messageId))progressBlock
                 success:(nullable void (^)(long messageId))successBlock
                   error:(nullable void (^)(RCErrorCode errorCode, long messageId))errorBlock
                  cancel:(nullable void (^)(long messageId))cancelBlock;

/// 异步发送消息
///
/// - Parameter message: 将要发送的消息实体（需要保证 message 中的 conversationType，targetId，messageContent 是有效值)
/// - Parameter pushContent: 接收方离线时需要显示的远程推送内容
/// - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter attachedBlock: 入库回调 [message: 已存数据库的消息体]
/// - Parameter successBlock: 消息发送成功的回调 [successMessage: 消息实体]
/// - Parameter errorBlock: 消息发送失败的回调 [nErrorCode: 发送失败的错误码，errorMessage:消息实体]
///
/// 当接收方离线并允许远程推送时，会收到远程推送。
/// 远程推送中包含两部分内容，一是 pushContent，用于显示；二是 pushData，用于携带不显示的数据。
///
/// SDK 内置的消息类型，如果您将 pushContent 和 pushData 置为 nil，会使用默认的推送格式进行远程推送。
/// 自定义类型的消息，需要您自己设置 pushContent 和 pushData 来定义推送内容，否则将不会进行远程推送。
///
/// 如果您使用此方法发送图片消息，需要您自己实现图片的上传，构建一个 RCImageMessage 对象，
/// 并将 RCImageMessage 中的 imageUrl 字段设置为上传成功的 URL 地址，然后使用此方法发送。
///
/// 如果您使用此方法发送文件消息，需要您自己实现文件的上传，构建一个 RCFileMessage 对象，
/// 并将 RCFileMessage 中的 fileUrl 字段设置为上传成功的 URL 地址，然后使用此方法发送。
///
/// - Warning: 如果您使用 IMLibCore，可以使用此方法发送消息；
/// 如果您使用 IMKit，请使用 RCIM 中的同名方法发送消息，否则不会自动更新 UI。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)sendMessage:(RCMessage *)message
        pushContent:(nullable NSString *)pushContent
           pushData:(nullable NSString *)pushData
           attached:(nullable void (^)(RCMessage *_Nullable message))attachedBlock
       successBlock:(nullable void (^)(RCMessage *successMessage))successBlock
         errorBlock:(nullable void (^)(RCErrorCode nErrorCode, RCMessage *errorMessage))errorBlock;

/// 异步发送消息
///
/// - Parameter message: 将要发送的消息实体（需要保证 message 中的 conversationType，targetId，messageContent 是有效值)
/// - Parameter pushContent: 接收方离线时需要显示的远程推送内容
/// - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter option: 消息的相关配置
/// - Parameter attachedBlock: 入库回调 [message: 已存数据库的消息体]
/// - Parameter successBlock: 消息发送成功的回调 [successMessage: 消息实体]
/// - Parameter errorBlock: 消息发送失败的回调 [nErrorCode: 发送失败的错误码，errorMessage:消息实体]
///
/// 当接收方离线并允许远程推送时，会收到远程推送。
/// 远程推送中包含两部分内容，一是 pushContent，用于显示；二是 pushData，用于携带不显示的数据。
///
/// SDK 内置的消息类型，如果您将 pushContent 和 pushData 置为 nil，会使用默认的推送格式进行远程推送。
/// 自定义类型的消息，需要您自己设置 pushContent 和 pushData 来定义推送内容，否则将不会进行远程推送。
///
/// 如果您使用此方法发送图片消息，需要您自己实现图片的上传，构建一个 RCImageMessage 对象，
/// 并将 RCImageMessage 中的 imageUrl 字段设置为上传成功的 URL 地址，然后使用此方法发送。
///
/// 如果您使用此方法发送文件消息，需要您自己实现文件的上传，构建一个 RCFileMessage 对象，
/// 并将 RCFileMessage 中的 fileUrl 字段设置为上传成功的 URL 地址，然后使用此方法发送。
///
/// - Warning: 如果您使用 IMLibCore，可以使用此方法发送消息；
/// 如果您使用 IMKit，请使用 RCIM 中的同名方法发送消息，否则不会自动更新 UI。
///
/// - Remark: 消息操作
/// - Since: 5.6.8
- (void)sendMessage:(RCMessage *)message
        pushContent:(nullable NSString *)pushContent
           pushData:(nullable NSString *)pushData
             option:(nullable RCSendMessageOption *)option
           attached:(nullable void (^)(RCMessage *_Nullable message))attachedBlock
       successBlock:(nullable void (^)(RCMessage *successMessage))successBlock
         errorBlock:(nullable void (^)(RCErrorCode nErrorCode, RCMessage *errorMessage))errorBlock;

/// 异步发送媒体消息（图片消息或文件消息）
///
/// - Parameter message: 将要发送的消息实体（需要保证 message 中的 conversationType，targetId，messageContent 是有效值)
/// - Parameter pushContent: 接收方离线时需要显示的远程推送内容
/// - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter attachedBlock: 入库回调 [message: 已存数据库的消息体]
/// - Parameter progressBlock: 消息发送进度更新的回调 [progress:当前的发送进度，0 <= progress <= 100, progressMessage:消息实体]
/// - Parameter successBlock: 消息发送成功的回调 [successMessage:消息实体]
/// - Parameter errorBlock: 消息发送失败的回调 [nErrorCode:发送失败的错误码，errorMessage:消息实体]
/// - Parameter cancelBlock: 用户取消了消息发送的回调 [cancelMessage:消息实体]
///
/// 当接收方离线并允许远程推送时，会收到远程推送。
/// 远程推送中包含两部分内容，一是 pushContent，用于显示；二是 pushData，用于携带不显示的数据。
///
/// SDK 内置的消息类型，如果您将 pushContent 和 pushData 置为 nil，会使用默认的推送格式进行远程推送。
/// 自定义类型的消息，需要您自己设置 pushContent 和 pushData 来定义推送内容，否则将不会进行远程推送。
///
/// 如果您需要上传图片到自己的服务器，需要构建一个 RCImageMessage 对象，
/// 并将 RCImageMessage 中的 imageUrl 字段设置为上传成功的 URL 地址，然后使用 RCCoreClient 的
/// sendMessage:targetId:content:pushContent:pushData:success:error:方法
/// 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。
///
/// 如果您需要上传文件到自己的服务器，构建一个 RCFileMessage 对象，
/// 并将 RCFileMessage 中的 fileUrl 字段设置为上传成功的 URL 地址，然后使用 RCCoreClient 的
/// sendMessage:targetId:content:pushContent:pushData:success:error:方法
/// 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。
///
/// - Warning: 如果您使用 IMLibCore，可以使用此方法发送媒体消息；
/// 如果您使用 IMKit，请使用 RCIM 中的同名方法发送媒体消息，否则不会自动更新 UI。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)sendMediaMessage:(RCMessage *)message
             pushContent:(nullable NSString *)pushContent
                pushData:(nullable NSString *)pushData
                attached:(nullable void (^)(RCMessage *_Nullable message))attachedBlock
                progress:(nullable void (^)(int progress, RCMessage *progressMessage))progressBlock
            successBlock:(nullable void (^)(RCMessage *successMessage))successBlock
              errorBlock:(nullable void (^)(RCErrorCode nErrorCode, RCMessage *errorMessage))errorBlock
                  cancel:(nullable void (^)(RCMessage *cancelMessage))cancelBlock;

/// 异步发送媒体消息（图片消息或文件消息）
///
/// - Parameter message: 将要发送的消息实体（需要保证 message 中的 conversationType，targetId，messageContent 是有效值)
/// - Parameter pushContent: 接收方离线时需要显示的远程推送内容
/// - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter option: 消息的相关配置
/// - Parameter attachedBlock: 入库回调 [message: 已存数据库的消息体]
/// - Parameter progressBlock: 消息发送进度更新的回调 [progress:当前的发送进度，0 <= progress <= 100, progressMessage:消息实体]
/// - Parameter successBlock: 消息发送成功的回调 [successMessage:消息实体]
/// - Parameter errorBlock: 消息发送失败的回调 [nErrorCode:发送失败的错误码，errorMessage:消息实体]
/// - Parameter cancelBlock: 用户取消了消息发送的回调 [cancelMessage:消息实体]
///
/// 当接收方离线并允许远程推送时，会收到远程推送。
/// 远程推送中包含两部分内容，一是 pushContent，用于显示；二是 pushData，用于携带不显示的数据。
///
/// SDK 内置的消息类型，如果您将 pushContent 和 pushData 置为 nil，会使用默认的推送格式进行远程推送。
/// 自定义类型的消息，需要您自己设置 pushContent 和 pushData 来定义推送内容，否则将不会进行远程推送。
///
/// 如果您需要上传图片到自己的服务器，需要构建一个 RCImageMessage 对象，
/// 并将 RCImageMessage 中的 imageUrl 字段设置为上传成功的 URL 地址，然后使用 RCCoreClient 的
/// sendMessage:targetId:content:pushContent:pushData:success:error:方法
/// 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。
///
/// 如果您需要上传文件到自己的服务器，构建一个 RCFileMessage 对象，
/// 并将 RCFileMessage 中的 fileUrl 字段设置为上传成功的 URL 地址，然后使用 RCCoreClient 的
/// sendMessage:targetId:content:pushContent:pushData:success:error:方法
/// 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。
///
/// - Warning: 如果您使用 IMLibCore，可以使用此方法发送媒体消息；
/// 如果您使用 IMKit，请使用 RCIM 中的同名方法发送媒体消息，否则不会自动更新 UI。
///
/// - Remark: 消息操作
/// - Since: 5.4.4
- (void)sendMediaMessage:(RCMessage *)message
             pushContent:(nullable NSString *)pushContent
                pushData:(nullable NSString *)pushData
                  option:(nullable RCSendMessageOption *)option
                attached:(nullable void (^)(RCMessage *_Nullable message))attachedBlock
                progress:(nullable void (^)(int progress, RCMessage *progressMessage))progressBlock
            successBlock:(nullable void (^)(RCMessage *successMessage))successBlock
              errorBlock:(nullable void (^)(RCErrorCode nErrorCode, RCMessage *errorMessage))errorBlock
                  cancel:(nullable void (^)(RCMessage *cancelMessage))cancelBlock;

/// 取消发送中的媒体信息
///
/// - Parameter messageId: 媒体消息的 messageId
///
/// - Returns: YES 表示取消成功，NO 表示取消失败，即已经发送成功或者消息不存在。
///
/// - Remark: 消息操作
/// - Since: 5.0.0
- (BOOL)cancelSendMediaMessage:(long)messageId;

/// 异步插入向外发送的消息（该消息只插入本地数据库，实际不会发送给服务器和对方）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter sentStatus: 发送状态
/// - Parameter content: 消息的内容
/// - Parameter completion: 异步回调 [message: 发送的消息实体]
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)insertOutgoingMessage:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                   sentStatus:(RCSentStatus)sentStatus
                      content:(RCMessageContent *)content
                   completion:(nullable void (^)(RCMessage *_Nullable message))completion;

/// 异步插入向外发送的、指定时间的消息（此方法如果 sentTime 有问题会影响消息排序，慎用！！）
/// （该消息只插入本地数据库，实际不会发送给服务器和对方）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter sentStatus: 发送状态
/// - Parameter content: 消息的内容
/// - Parameter sentTime: 消息发送的 Unix 时间戳，单位为毫秒（传 0 会按照本地时间插入）
/// - Parameter completion: 异步回调 [message: 发送的消息实体]
///
/// - Note: 如果 sentTime <= 0，则被忽略，会以插入时的时间为准。
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)insertOutgoingMessage:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                   sentStatus:(RCSentStatus)sentStatus
                      content:(RCMessageContent *)content
                     sentTime:(long long)sentTime
                   completion:(nullable void (^)(RCMessage *_Nullable message))completion;


/// 异步插入接收的消息（该消息只插入本地数据库，实际不会发送给服务器和对方）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter senderUserId: 发送者 ID
/// - Parameter receivedStatusInfo: 消息接收状态的 RCReceivedStatusInfo 对象
/// - Parameter content: 消息的内容
/// - Parameter completion: 异步回调 [message: 发送的消息实体]
///
/// - Note: 新接口使用 RCReceivedStatusInfo 类来记录已读、已下载、已听等状态，通过按位计算的方式，支持多种状态并存；可以通过 RCReceivedStatusInfo 对外接口直接获取是否已读/已下载/已听等
/// - Warning: 新、旧接口原则上不混用，否则接收状态可能出现偏差
/// - Remark: 消息操作
/// - Since: 5.6.8
- (void)insertIncomingMessage:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                 senderUserId:(NSString *)senderUserId
           receivedStatusInfo:(RCReceivedStatusInfo *)receivedStatusInfo
                      content:(RCMessageContent *)content
                   completion:(nullable void (^)(RCMessage *_Nullable message))completion;

/// 异步插入接收的消息（此方法如果 sentTime
/// 有问题会影响消息排序，慎用！！）（该消息只插入本地数据库，实际不会发送给服务器和对方）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter senderUserId: 发送者 ID
/// - Parameter receivedStatusInfo: 消息接收状态的 RCReceivedStatusInfo 对象
/// - Parameter content: 消息的内容
/// - Parameter sentTime: 消息发送的 Unix 时间戳，单位为毫秒（传 0 会按照本地时间插入）
/// - Parameter completion: 异步回调 [message: 发送的消息实体]
///
/// - Note: 新接口使用 RCReceivedStatusInfo 类来记录已读、已下载、已听等状态，通过按位计算的方式，支持多种状态并存；可以通过 RCReceivedStatusInfo 对外接口直接获取是否已读/已下载/已听等
/// - Note: 如果 sentTime <= 0，则被忽略，会以插入时的时间为准。
/// - Warning: 新、旧接口原则上不混用，否则接收状态可能出现偏差
/// - Remark: 消息操作
/// - Since: 5.6.8
- (void)insertIncomingMessage:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                 senderUserId:(NSString *)senderUserId
           receivedStatusInfo:(RCReceivedStatusInfo *)receivedStatusInfo
                      content:(RCMessageContent *)content
                     sentTime:(long long)sentTime
                   completion:(nullable void (^)(RCMessage *_Nullable message))completion;


/// 异步插入消息（此方法如果 message.sentTime 有问题会影响消息排序，慎用！！）
/// （该消息只插入本地数据库，实际不会发送给服务器和对方）
///
/// - Parameter message: 将要插入的消息实体（message 中的 conversationType、targetId、messageContent、messageDirection、senderUserId 必须是有效值)
/// MessageDirection_SEND 时必须设置 sentStatus；MessageDirection_RECEIVE 时必须设置 receivedStatusInfo
/// - Parameter successBlock: 异步回调 [message: 插入消息的完整实体]
/// - Parameter errorBlock: 异步回调 [errorCode: 插入失败错误码]
///
/// - Note: 如果 message.sentTime <= 0，则被忽略，会以插入时的时间为准。
/// - Remark: 消息操作
/// - Since: 5.12.2
/**
    RCTextMessage *txtMessage = [RCTextMessage messageWithContent:@"insert a message"];
    // 构造一条接收到的单聊消息，用于插入本地数据库
    RCMessage *incoming = [[RCMessage alloc] initWithType:ConversationType_PRIVATE
                                                 targetId:@"targetID"
                                                direction:MessageDirection_RECEIVE
                                                  content:txtMessage];
    incoming.senderUserId = @"senderUserId";
    RCReceivedStatusInfo *statusInfo = [[RCReceivedStatusInfo alloc] initWithReceivedStatus:0];
    [statusInfo markAsRead];
    incoming.receivedStatusInfo = statusInfo;
    incoming.disableUpdateLastMessage = YES;

    // 构造一条发送的超级群消息，用于插入本地数据库
    RCMessage *outgoing = [[RCMessage alloc] initWithType:ConversationType_PRIVATE
                                                 targetId:@"targetID"
                                                channelId:@"channelID"
                                                direction:MessageDirection_SEND
                                                  content:txtMessage];
    outgoing.senderUserId = @"own user id";
    outgoing.sentStatus = SentStatus_SENT;
    outgoing.canIncludeExpansion = YES;// 如需后续支持扩展能力，插入前需要设置
    outgoing.disableUpdateLastMessage = YES;
*/
- (void)insertMessage:(RCMessage *)message
         successBlock:(void (^)(RCMessage *successMessage))successBlock
           errorBlock:(void (^)(RCErrorCode errorCode))errorBlock;


/// 异步批量插入接收的消息（该消息只插入本地数据库，实际不会发送给服务器和对方）
/// RCMessage 下列属性会被入库，其余属性会被抛弃
/// conversationType    会话类型
/// targetId            会话 ID
/// messageUId          消息唯一 ID,  此属性入库 5.3.5 开始支持
/// messageDirection    消息方向
/// senderUserId        发送者 ID
/// receivedStatus[已废弃]      接收状态；消息方向为接收方，并且 receivedStatus 为 ReceivedStatus_UNREAD 时，该条消息未读
/// receivedStatusInfo      接收状态对象；消息方向为接收方，并且 receivedStatusInfo.receivedStatus 为 0 时，该条消息未读
/// sentStatus          发送状态
/// content             消息的内容
/// sentTime            消息发送的 Unix 时间戳，单位为毫秒，会影响消息排序
/// extra            RCMessage 的额外字段
///
/// - Parameter msgs: 插入的批量 RCMessage 数据（此方法不执行排重）
/// - Parameter completion: 完成回调
///
/// 此方法不支持聊天室和超级群的会话类型。每批最多处理  500 条消息，超过 500 条返回 NO
/// 消息的未读会累加到会话的未读数上
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)batchInsertMessage:(NSArray<RCMessage *> *)msgs completion:(nullable void (^)(BOOL ret))completion;

/// 异步批量插入接收的消息（该消息只插入本地数据库，实际不会发送给服务器和对方）
/// RCMessage 下列属性会被入库，其余属性会被抛弃
/// conversationType    会话类型
/// targetId            会话 ID
/// messageUId          消息唯一 ID
/// messageDirection    消息方向
/// senderUserId        发送者 ID
/// receivedStatus[已废弃]      接收状态；消息方向为接收方，并且 receivedStatus 为 ReceivedStatus_UNREAD 时，该条消息未读
/// receivedStatusInfo      接收状态对象；消息方向为接收方，并且 receivedStatusInfo.receivedStatus 为 0 时，该条消息未读
/// sentStatus          发送状态
/// content             消息的内容
/// sentTime            消息发送的 Unix 时间戳，单位为毫秒，会影响消息排序
/// extra               RCMessage 的额外字段
///
/// - Parameter msgs: 插入的批量 RCMessage 数据
/// - Parameter checkDuplicate: 是否根据 messageUId 排重
/// - Parameter completion: 完成回调
///
/// 此方法不支持聊天室和超级群的会话类型。每批最多处理  500 条消息，超过 500 条返回 NO
/// 消息的未读会累加到会话的未读数上
///
/// - Remark: 消息操作
/// - Since: 5.3.5

- (void)batchInsertMessage:(NSArray<RCMessage *> *)msgs
            checkDuplicate:(BOOL)checkDuplicate
                completion:(nullable void (^)(BOOL ret))completion;

/// 根据文件 URL 地址下载文件内容
///
/// - Parameter fileName: 指定的文件名称 需要开发者指定文件后缀 (例如 rongCloud.mov)
/// - Parameter mediaUrl: 文件的 URL 地址
/// - Parameter progressBlock: 文件下载进度更新的回调 [progress:当前的下载进度，0 <= progress <= 100]
/// - Parameter successBlock: 下载成功的回调 [mediaPath:下载成功后本地存放的文件路径 文件路径为文件消息的默认地址]
/// - Parameter errorBlock: 下载失败的回调 [errorCode:下载失败的错误码]
/// - Parameter cancelBlock: 用户取消了下载的回调
///
/// 用来获取媒体原文件时调用。如果本地缓存中包含此文件，则从本地缓存中直接获取，否则将从服务器端下载。
///
/// - Warning: 此方法仅仅是文件下载器，不会操作消息体。
///
/// - Remark: 多媒体下载
/// - Since: 5.0.0
- (void)downloadMediaFile:(NSString *)fileName
                 mediaUrl:(NSString *)mediaUrl
                 progress:(nullable void (^)(int progress))progressBlock
                  success:(nullable void (^)(NSString *mediaPath))successBlock
                    error:(nullable void (^)(RCErrorCode errorCode))errorBlock
                   cancel:(nullable void (^)(void))cancelBlock;

/// 下载消息内容中的媒体信息
///
/// - Parameter conversationType: 消息的会话类型
/// - Parameter targetId: 消息的会话 ID
/// - Parameter mediaType: 消息内容中的多媒体文件类型，目前仅支持图片
/// - Parameter mediaUrl: 多媒体文件的网络 URL
/// - Parameter progressBlock: 消息下载进度更新的回调 [progress:当前的下载进度，0
/// <= progress <= 100]
/// - Parameter successBlock: 下载成功的回调
/// [mediaPath:下载成功后本地存放的文件路径]
/// - Parameter errorBlock: 下载失败的回调 [errorCode:下载失败的错误码]
/// - Parameter cancelBlock: 用户取消了下载的回调
///
/// 用来获取媒体原文件时调用。如果本地缓存中包含此文件，则从本地缓存中直接获取，否则将从服务器端下载。
///
/// - Warning: 此方法仅仅是文件下载器，不会操作消息体。
///
/// - Remark: 多媒体下载
/// - Since: 5.0.0
- (void)downloadMediaFile:(RCConversationType)conversationType
                 targetId:(NSString *)targetId
                mediaType:(RCMediaType)mediaType
                 mediaUrl:(NSString *)mediaUrl
                 progress:(nullable void (^)(int progress))progressBlock
                  success:(nullable void (^)(NSString *mediaPath))successBlock
                    error:(nullable void (^)(RCErrorCode errorCode))errorBlock
                   cancel:(nullable void (^)(void))cancelBlock;

/// 下载消息内容中的媒体信息
///
/// - Parameter message: 媒体消息
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
/// - Since: 5.6.4
- (void)downloadMediaMessage:(RCMessage *)message
               progressBlock:(nullable void (^)(int progress))progressBlock
                successBlock:(nullable void (^)(NSString *mediaPath))successBlock
                  errorBlock:(nullable void (^)(RCErrorCode errorCode))errorBlock
                 cancelBlock:(nullable void (^)(void))cancelBlock;

/// 取消发送中的媒体信息
///
/// - Parameter message: 媒体消息
/// - Parameter successBlock: 取消成功
/// - Parameter errorBlock: 取消失败
///
/// - Remark: 消息操作
/// - Since: 5.6.4
- (void)cancelDownloadMediaMessage:(RCMessage *)message
                      successBlock:(nullable void (^)(void))successBlock
                        errorBlock:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 取消下载中的媒体信息
///
/// - Parameter mediaUrl: 媒体消息 Url
/// - Parameter successBlock: 成功
/// - Parameter errorBlock: 失败
///
/// - Remark: 多媒体下载
/// - Since: 5.6.4
- (void)cancelDownloadMediaUrl:(NSString *)mediaUrl
                  successBlock:(nullable void (^)(void))successBlock
                    errorBlock:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 暂停下载中的媒体消息，如需继续下载重新调用 download 方法即可。
///
/// - Parameter message: 媒体消息
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Remark: 多媒体下载
/// - Since: 5.6.4
- (void)pauseDownloadMediaMessage:(RCMessage *)message
                     successBlock:(nullable void (^)(void))successBlock
                       errorBlock:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 暂停下载中的媒体消息，如需继续下载重新调用 download 方法即可。
///
/// - Parameter mediaUrl: 媒体消息 Url
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Remark: 多媒体下载
/// - Since: 5.6.4
- (void)pauseDownloadMediaUrl:(NSString *)mediaUrl
                 successBlock:(nullable void (^)(void))successBlock
                   errorBlock:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 可通过此接口获取文件的下载信息，包含进度、已下载文件大小、总文件大小等。
///
/// 1. 调用 `downloadMediaMessage:progressBlock:successBlock:errorBlock:cancelBlock:` 接口下载的文件
/// 传入 message.remoteUrl 获取 RCDownloadInfo；
/// 如需判断文件是否已下载，可通过 message.localPath 来判断文件是否存在。
///
/// 2. 调用 `downloadMediaFile:mediaUrl:progress:success:error:cancel:` 接口下载的文件
/// 传入文件远端地址获取 RCDownloadInfo；
/// 如需判断文件是否已经下载过，可通过以下代码拼接出本地路径来判断文件是否存在。
/// ```
/// NSString *fileLocalPath = [RCUtilities getFileStoragePath];
/// fileLocalPath = [fileLocalPath stringByAppendingPathComponent:fileName];
/// ```
- (nullable RCDownloadInfo *)getDownloadInfo:(NSString *)mediaUrl;

/// 异步发送定向消息
///
/// - Parameter conversationType: 发送消息的会话类型
/// - Parameter targetId: 发送消息的会话 ID
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
/// 如果您使用 IMLibCore，可以使用此方法发送定向消息；
/// 如果您使用 IMKit，请使用 RCIM 中的同名方法发送定向消息，否则不会自动更新 UI。
/// userIdList 里 ID 个数不能超过 300，超过会被截断。
///
/// - Warning: 此方法目前仅支持普通群组和讨论组。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)sendDirectionalMessage:(RCConversationType)conversationType
                      targetId:(NSString *)targetId
                  toUserIdList:(NSArray<NSString *> *)userIdList
                       content:(RCMessageContent *)content
                   pushContent:(nullable NSString *)pushContent
                      pushData:(nullable NSString *)pushData
                      attached:(nullable void (^)(RCMessage *_Nullable message))attachedBlock
                       success:(nullable void (^)(long messageId))successBlock
                         error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock;

/// 异步发送定向消息
///
/// - Parameter message: 消息实体
/// - Parameter userIdList: 接收消息的用户 ID 列表
/// - Parameter pushContent: 接收方离线时需要显示的远程推送内容
/// - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter attachedBlock: 入库回调 [message: 已存数据库的消息体]
/// - Parameter successBlock: 消息发送成功的回调 [successMessage:发送成功的消息]
/// - Parameter errorBlock: 消息发送失败的回调 [nErrorCode:发送失败的错误码，errorMessage:发送失败的消息]
///
/// 此方法用于在群组和讨论组中发送消息给其中的部分用户，其它用户不会收到这条消息。
/// userIdList 里 ID 个数不能超过 300，超过会被截断。
///
/// - Warning: 此方法目前仅支持普通群组和讨论组。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)sendDirectionalMessage:(RCMessage *)message
                  toUserIdList:(NSArray<NSString *> *)userIdList
                   pushContent:(nullable NSString *)pushContent
                      pushData:(nullable NSString *)pushData
                      attached:(nullable void (^)(RCMessage *_Nullable message))attachedBlock
                  successBlock:(nullable void (^)(RCMessage *successMessage))successBlock
                    errorBlock:(nullable void (^)(RCErrorCode nErrorCode, RCMessage *errorMessage))errorBlock;

/// 异步发送定向消息
///
/// - Parameter message: 消息实体
/// - Parameter userIdList: 接收消息的用户 ID 列表
/// - Parameter pushContent: 接收方离线时需要显示的远程推送内容
/// - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter option: 消息的相关配置
/// - Parameter attachedBlock: 入库回调 [message: 已存数据库的消息体]
/// - Parameter successBlock: 消息发送成功的回调 [successMessage:发送成功的消息]
/// - Parameter errorBlock: 消息发送失败的回调 [nErrorCode:发送失败的错误码，errorMessage:发送失败的消息]
///
/// 此方法用于在群组和讨论组中发送消息给其中的部分用户，其它用户不会收到这条消息。
/// userIdList 里 ID 个数不能超过 300，超过会被截断。
///
/// - Warning: 此方法目前仅支持普通群组和讨论组。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)sendDirectionalMessage:(RCMessage *)message
                  toUserIdList:(NSArray<NSString *> *)userIdList
                   pushContent:(nullable NSString *)pushContent
                      pushData:(nullable NSString *)pushData
                        option:(nullable RCSendMessageOption *)option
                      attached:(nullable void (^)(RCMessage *_Nullable message))attachedBlock
                  successBlock:(nullable void (^)(RCMessage *successMessage))successBlock
                    errorBlock:(nullable void (^)(RCErrorCode nErrorCode, RCMessage *errorMessage))errorBlock;

/// 异步发送定向媒体消息（图片消息或文件消息）
///
/// - Parameter message: 将要发送的消息实体（需要保证 message 中的 conversationType，targetId，messageContent 是有效值)
/// - Parameter userIdList: 接收消息的用户 ID 列表
/// - Parameter pushContent: 接收方离线时需要显示的远程推送内容
/// - Parameter pushData: 接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter attachedBlock: 入库回调 [message: 已存数据库的消息体]
/// - Parameter progressBlock: 消息发送进度更新的回调 [progress:当前的发送进度，0 <= progress <= 100, progressMessage:消息实体]
/// - Parameter successBlock: 消息发送成功的回调 [successMessage:消息实体]
/// - Parameter errorBlock: 消息发送失败的回调 [nErrorCode:发送失败的错误码，errorMessage:消息实体]
/// - Parameter cancelBlock: 用户取消了消息发送的回调 [cancelMessage:消息实体]
///
/// 当接收方离线并允许远程推送时，会收到远程推送。
/// 远程推送中包含两部分内容，一是 pushContent，用于显示；二是 pushData，用于携带不显示的数据。
///
/// SDK 内置的消息类型，如果您将 pushContent 和 pushData 置为 nil，会使用默认的推送格式进行远程推送。
/// 自定义类型的消息，需要您自己设置 pushContent 和 pushData 来定义推送内容，否则将不会进行远程推送。
///
/// 如果您需要上传图片到自己的服务器，需要构建一个 RCImageMessage 对象，
/// 并将 RCImageMessage 中的 imageUrl 字段设置为上传成功的 URL 地址，然后使用 RCIMClient 的
/// sendMessage:targetId:content:pushContent:pushData:success:error:方法
/// 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。
///
/// 如果您需要上传文件到自己的服务器，构建一个 RCFileMessage 对象，
/// 并将 RCFileMessage 中的 fileUrl 字段设置为上传成功的 URL 地址，然后使用 RCIMClient 的
/// sendMessage:targetId:content:pushContent:pushData:success:error:方法
/// 或 sendMessage:targetId:content:pushContent:success:error:方法进行发送，不要使用此方法。
///
/// - Warning: 如果您使用 IMLib，可以使用此方法发送媒体消息；
/// 如果您使用 IMKit，请使用 RCIM 中的同名方法发送媒体消息，否则不会自动更新 UI。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)sendDirectionalMediaMessage:(RCMessage *)message
                       toUserIdList:(NSArray<NSString *> *)userIdList
                        pushContent:(nullable NSString *)pushContent
                           pushData:(nullable NSString *)pushData
                           attached:(nullable void (^)(RCMessage *_Nullable message))attachedBlock
                           progress:(nullable void (^)(int progress, RCMessage *progressMessage))progressBlock
                       successBlock:(nullable void (^)(RCMessage *successMessage))successBlock
                         errorBlock:(nullable void (^)(RCErrorCode nErrorCode, RCMessage *errorMessage))errorBlock
                             cancel:(nullable void (^)(RCMessage *cancelMessage))cancelBlock;

#pragma mark 消息接收监听

/// 添加 IMLib 接收消息监听
///
/// - Parameter delegate: 代理
/// - Since: 5.1.5
- (void)addReceiveMessageDelegate:(id<RCIMClientReceiveMessageDelegate>)delegate
    NS_SWIFT_NAME(addReceiveMessageDelegate(_:));

/// 移除 IMLib 接收消息监听
///
/// - Parameter delegate: 代理
/// - Since: 5.1.5
- (void)removeReceiveMessageDelegate:(id<RCIMClientReceiveMessageDelegate>)delegate
    NS_SWIFT_NAME(removeReceiveMessageDelegate(_:));

#pragma mark - 消息入库前预处理监听
/// 设置消息拦截器
///
/// 可以设置并实现此拦截器来进行消息的拦截处理
///
/// - Remark: 功能设置
/// - Since: 5.1.2
@property (nonatomic, weak, nullable) id<RCMessageInterceptor> messageInterceptor;

#pragma mark - 发送消息被拦截监听

/// 设置发送消息被拦截的监听器
///
/// 可以设置并实现此拦截器来处理发送消息被拦截时的处理
///
/// - Remark: 功能设置
/// - Since: 5.1.4
@property (nonatomic, weak, nullable) id<RCMessageBlockDelegate> messageBlockDelegate;

#pragma mark - 消息阅读回执

/// 发送某个会话中消息阅读的回执
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
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
/// - Since: 5.0.0
- (void)sendReadReceiptMessage:(RCConversationType)conversationType
                      targetId:(NSString *)targetId
                          time:(long long)timestamp
                       success:(nullable void (^)(void))successBlock
                         error:(nullable void (^)(RCErrorCode nErrorCode))errorBlock;

/// 请求消息阅读回执
///
/// - Parameter message: 要求阅读回执的消息
/// - Parameter successBlock: 请求成功的回调
/// - Parameter errorBlock: 请求失败的回调 [nErrorCode: 失败的错误码]
///
/// 通过此接口，可以要求阅读了这条消息的用户发送阅读回执。
///
/// 此方法不支持超级群的会话类型。
///
/// - Remark: 高级功能
/// - Since: 5.0.0
- (void)sendReadReceiptRequest:(RCMessage *)message
                       success:(nullable void (^)(void))successBlock
                         error:(nullable void (^)(RCErrorCode nErrorCode))errorBlock;

/// 发送阅读回执
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter messageList: 已经阅读了的消息列表
/// - Parameter successBlock: 发送成功的回调
/// - Parameter errorBlock: 发送失败的回调 [nErrorCode: 失败的错误码]
///
/// 当用户阅读了需要阅读回执的消息，可以通过此接口发送阅读回执，消息的发送方即可直接知道那些人已经阅读。
///
/// 此方法不支持超级群的会话类型。
///
/// - Remark: 高级功能
/// - Since: 5.0.0
- (void)sendReadReceiptResponse:(RCConversationType)conversationType
                       targetId:(NSString *)targetId
                    messageList:(NSArray<RCMessage *> *)messageList
                        success:(nullable void (^)(void))successBlock
                          error:(nullable void (^)(RCErrorCode nErrorCode))errorBlock;

/// 同步会话阅读状态（把指定会话里所有发送时间早于 timestamp 的消息置为已读）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter timestamp: 已经阅读的最后一条消息的 Unix 时间戳，单位：毫秒
/// - Parameter successBlock: 同步成功的回调
/// - Parameter errorBlock: 同步失败的回调 [nErrorCode: 失败的错误码]
///
/// 此方法不支持超级群的会话类型。
///
/// - Remark: 高级功能
/// - Since: 5.0.0
- (void)syncConversationReadStatus:(RCConversationType)conversationType
                          targetId:(NSString *)targetId
                              time:(long long)timestamp
                           success:(nullable void (^)(void))successBlock
                             error:(nullable void (^)(RCErrorCode nErrorCode))errorBlock;

#pragma mark - 消息撤回

/// 撤回消息
///
/// - Parameter message: 需要撤回的消息
/// - Parameter option: 撤回消息的配置项，无配置可传 nil
/// - Parameter pushContent: 当下发 push 消息时，在通知栏里会显示这个字段，不设置将使用融云默认推送内容。将优先使用 message.messagePushConfig.pushContent 否则才会使用该方法的 pushContent
/// - Parameter successBlock: 撤回成功的回调 [message:撤回的消息体。isDelete:NO 时，该消息已经变更为新的消息 `RCRecallNotificationMessage`; isDelete:YES 时，该消息已经被删除]
/// - Parameter errorBlock: 撤回失败的回调 [errorCode:撤回失败错误码]
///
/// - Warning: 仅支持单聊、群组、聊天室和讨论组。
///
/// 如果需要使用该接口的 pushContent 生效，则需要将 message.messagePushConfig 置为 nil 或者直接修改 message.messagePushConfig.pushContent
///
/// - Remark: 高级功能
/// - Since: 5.16.0
- (void)recallMessage:(RCMessage *)message
               option:(nullable RCRecallMessageOption *)option
          pushContent:(nullable NSString *)pushContent
              success:(nullable void (^)(RCMessage *message))successBlock
                error:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 撤回消息
///
/// - Parameter message: 需要撤回的消息
/// - Parameter pushContent: 当下发 push 消息时，在通知栏里会显示这个字段，不设置将使用融云默认推送内容。将优先使用 message.messagePushConfig.pushContent 否则才会使用该方法的 pushContent
/// - Parameter successBlock: 撤回成功的回调 [messageId:撤回的消息 ID，该消息已经变更为新的消息 `RCRecallNotificationMessage`]
/// - Parameter errorBlock: 撤回失败的回调 [errorCode:撤回失败错误码]
///
/// - Warning: 仅支持单聊、群组、聊天室和讨论组。
///
/// 如果需要使用该接口的 pushContent 生效，则需要将 message.messagePushConfig 置为 nil 或者直接修改 message.messagePushConfig.pushContent
///
/// - Remark: 高级功能
/// - Since: 5.0.0
- (void)recallMessage:(RCMessage *)message
          pushContent:(nullable NSString *)pushContent
              success:(nullable void (^)(long messageId))successBlock
                error:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 撤回消息
///
/// - Parameter message: 需要撤回的消息
/// - Parameter successBlock: 撤回成功的回调 [messageId:撤回的消息 ID，该消息已经变更为新的消息 `RCRecallNotificationMessage`]
/// - Parameter errorBlock: 撤回失败的回调 [errorCode:撤回失败错误码]
/// - Warning: 仅支持单聊、群组、聊天室和讨论组。
/// - Remark: 高级功能
/// - Since: 5.0.0
- (void)recallMessage:(RCMessage *)message
              success:(nullable void (^)(long messageId))successBlock
                error:(nullable void (^)(RCErrorCode errorCode))errorBlock;

#pragma mark - 消息操作

/// 异步获取某个会话中指定数量的最新消息实体
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter count: 需要获取的消息数量
/// - Parameter completion: 异步回调 [消息实体 RCMessage 对象列表]
///
///
/// 此方法会获取该会话中指定数量的最新消息实体，返回的消息实体按照时间从新到旧排列。
/// 如果会话中的消息数量小于参数 count 的值，会将该会话中的所有消息返回。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)getLatestMessages:(RCConversationType)conversationType
                 targetId:(NSString *)targetId
                    count:(int)count
               completion:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages))completion;

/// 异步获取会话中，从指定消息之前、指定数量的最新消息实体
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter oldestMessageId: 截止的消息 ID [0 或 -1 代表从最近的发送时间查起]
/// - Parameter count: 需要获取的消息数量
/// - Parameter completion: 异步回调 [消息实体 RCMessage 对象列表]
///
///
/// 此方法会获取该会话中，oldestMessageId 之前的、指定数量的最新消息实体，返回的消息实体按照时间从新到旧排列。
/// 返回的消息中不包含 oldestMessageId 对应那条消息，如果会话中的消息数量小于参数 count 的值，会将该会话中的所有消息返回。
/// 如：
/// oldestMessageId 为 10，count 为 2，会返回 messageId 为 9 和 8 的 RCMessage 对象列表。
///
/// 此方法不支持超级群的会话类型。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)getHistoryMessages:(RCConversationType)conversationType
                  targetId:(NSString *)targetId
           oldestMessageId:(long)oldestMessageId
                     count:(int)count
                completion:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages))completion;

/// 获取会话中，从指定消息之前、指定数量的、指定消息类型的最新消息实体
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter objectName: 消息内容的类型名，如果想取全部类型的消息请传 nil
/// - Parameter oldestMessageId: 截止的消息 ID [0 或 -1 代表从最近的发送时间查起]
/// - Parameter count: 需要获取的消息数量
/// - Parameter completion: 异步回调 [消息实体 RCMessage 对象列表]
///
///
/// 此方法会获取该会话中，oldestMessageId 之前的、指定数量和消息类型的最新消息实体，返回的消息实体按照时间从新到旧排列。
/// 返回的消息中不包含 oldestMessageId 对应的那条消息，如果会话中的消息数量小于参数 count
/// 的值，会将该会话中的所有消息返回。
/// 如：oldestMessageId 为 10，count 为 2，会返回 messageId 为 9 和 8 的 RCMessage 对象列表。
///
/// 此方法不支持超级群的会话类型。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)getHistoryMessages:(RCConversationType)conversationType
                  targetId:(NSString *)targetId
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
///
/// 此方法会获取该会话中，baseMessageId
/// 之前或之后的、指定数量、消息类型和查询方向的最新消息实体，返回的消息实体按照时间从新到旧排列。
/// 返回的消息中不包含 baseMessageId 对应的那条消息，如果会话中的消息数量小于参数 count 的值，会将该会话中的所有消息返回。
///
/// 此方法不支持超级群的会话类型。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)getHistoryMessages:(RCConversationType)conversationType
                  targetId:(NSString *)targetId
                objectName:(nullable NSString *)objectName
             baseMessageId:(long)baseMessageId
                 isForward:(BOOL)isForward
                     count:(int)count
                completion:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages))completion;

/// 异步获取会话中，指定时间、指定数量、指定消息类型（多个）、向前或向后查找的消息实体列表（按照时间从新到旧排列）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter objectNames: 消息内容的类型名称列表
/// - Parameter sentTime: 当前的消息时间戳，单位：毫秒
/// - Parameter isForward: 查询方向 true 为向前，false 为向后
/// - Parameter count: 需要获取的消息数量
/// - Parameter completion: 异步回调 [消息实体 RCMessage 对象列表]
///
///
/// 此方法会获取该会话中，sentTime
/// 之前或之后的、指定数量、指定消息类型（多个）的消息实体列表，返回的消息实体按照时间从新到旧排列。
/// 返回的消息中不包含 sentTime 对应的那条消息，如果会话中的消息数量小于参数 count 的值，会将该会话中的所有消息返回。
///
/// 此方法不支持超级群的会话类型。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)getHistoryMessages:(RCConversationType)conversationType
                  targetId:(NSString *)targetId
               objectNames:(NSArray<NSString *> *)objectNames
                  sentTime:(long long)sentTime
                 isForward:(BOOL)isForward
                     count:(int)count
                completion:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages))completion;

/// 在会话中异步搜索指定消息的前 beforeCount 数量和后 afterCount
/// 数量的消息。返回的消息列表中会包含指定的消息。消息列表时间顺序从新到旧。
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter sentTime: 消息的发送时间，单位：毫秒
/// - Parameter beforeCount: 指定消息的前部分消息数量
/// - Parameter afterCount: 指定消息的后部分消息数量
/// - Parameter completion: 异步回调 [消息实体 RCMessage 对象列表]
///
///
/// 获取该会话的这条消息及这条消息前 beforeCount 条和后 afterCount 条消息，如前后消息不够则返回实际数量的消息。
///
/// 此方法不支持超级群的会话类型。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)getHistoryMessages:(RCConversationType)conversationType
                  targetId:(NSString *)targetId
                  sentTime:(long long)sentTime
               beforeCount:(int)beforeCount
                afterCount:(int)afterCount
                completion:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages))completion;


/// 从服务器端清除历史消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter recordTime: 清除消息时间戳，【0 <= recordTime <= 当前会话最后一条消息的 sentTime,0
/// 清除所有消息，其他值清除小于等于 recordTime 的消息】，单位：毫秒
/// - Parameter successBlock: 获取成功的回调
/// - Parameter errorBlock: 获取失败的回调 [status:清除失败的错误码]
///
///
/// 此方法从服务器端清除历史消息，但是必须先开通历史消息云存储功能。
/// 例如，您不想从服务器上获取更多的历史消息，通过指定 recordTime 清除成功后只能获取该时间戳之后的历史消息。
///
/// - Remark: 消息操作
/// - Since: 5.0.0
- (void)clearRemoteHistoryMessages:(RCConversationType)conversationType
                          targetId:(NSString *)targetId
                        recordTime:(long long)recordTime
                           success:(nullable void (^)(void))successBlock
                             error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 清除历史消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter recordTime: 清除消息时间戳，【0 <= recordTime <= 当前会话最后一条消息的 sentTime,0
/// 清除所有消息，其他值清除小于等于 recordTime 的消息】，单位：毫秒
/// - Parameter clearRemote: 是否同时删除服务端消息
/// - Parameter successBlock: 获取成功的回调
/// - Parameter errorBlock: 获取失败的回调 [ status:清除失败的错误码]
///
///
/// 此方法可以清除服务器端历史消息和本地消息，如果清除服务器端消息必须先开通历史消息云存储功能。
/// 例如，您不想从服务器上获取更多的历史消息，通过指定 recordTime 并设置 clearRemote 为 YES
/// 清除消息，成功后只能获取该时间戳之后的历史消息。如果 clearRemote 传 NO，
/// 只会清除本地消息。
///
/// - Remark: 消息操作
/// - Since: 5.0.0
- (void)clearHistoryMessages:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
                  recordTime:(long long)recordTime
                 clearRemote:(BOOL)clearRemote
                     success:(nullable void (^)(void))successBlock
                       error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 从服务器端获取之前的历史消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter recordTime: 截止的消息发送时间戳，单位：毫秒
/// - Parameter count: 需要获取的消息数量，1 < count <= 100
/// - Parameter successBlock: 获取成功的回调 [messages:获取到的历史消息数组，isRemaining 是否还有剩余消息 YES
/// 表示还有剩余，NO 表示无剩余]
/// - Parameter errorBlock: 获取失败的回调 [status:获取失败的错误码]
///
///
/// 此方法从服务器端获取之前的历史消息，但是必须先开通历史消息云存储功能。
///
/// 本地数据库可以查到的消息，该接口不会再返回，所以建议先用 getHistoryMessages
/// 相关接口取本地历史消息，本地消息取完之后再通过该接口获取远端历史消息
///
/// - Remark: 消息操作
/// - Since: 5.0.0
- (void)getRemoteHistoryMessages:(RCConversationType)conversationType
                        targetId:(NSString *)targetId
                      recordTime:(long long)recordTime
                           count:(int)count
                         success:(nullable void (^)(NSArray<RCMessage *> *messages, BOOL isRemaining))successBlock
                           error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 从服务器端获取之前的历史消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter option: 可配置的参数
/// - Parameter successBlock: 获取成功的回调 [messages:获取到的历史消息数组，isRemaining 是否还有剩余消息 YES
/// 表示还有剩余，NO 表示无剩余]
/// - Parameter errorBlock: 获取失败的回调 [status:获取失败的错误码]
///
///
/// 此方法从服务器端获取之前的历史消息，但是必须先开通历史消息云存储功能。
///
/// - Remark: 消息操作
/// - Since: 5.0.0
- (void)getRemoteHistoryMessages:(RCConversationType)conversationType
                        targetId:(NSString *)targetId
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
/// - Since: 5.14.0
- (void)getMessages:(RCConversationType)conversationType
           targetId:(NSString *)targetId
             option:(RCHistoryMessageOption *)option
           complete:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages, long long timestamp, BOOL isRemaining,
                                       RCErrorCode code))complete
              error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 异步获取会话中 @ 提醒自己的消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter completion: 异步回调 [消息实体 RCMessage 对象列表]
///
///
/// 此方法从本地获取被@提醒的消息 (最多返回 10 条信息)
/// - Warning: 使用 IMKit 注意在进入会话页面前调用，否则在进入会话清除未读数的接口 clearMessagesUnreadStatus: targetId:
/// 以及 设置消息接收状态接口 setMessageReceivedStatus:receivedStatus:会同步清除被提示信息状态。
///
/// - Remark: 高级功能
/// - Since: 5.3.0
- (void)getUnreadMentionedMessages:(RCConversationType)conversationType
                          targetId:(NSString *)targetId
                        completion:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages))completion;
/// 异步获取本地指定会话的未读条数的 @ 消息列表，仅支持群组
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter count: 未读的 @ 消息，取值范围 [1,100]
/// - Parameter desc: 是否是降序查
/// - Parameter completion: 异步回调 [消息实体 RCMessage 对象列表]
///
///
/// 假如有 1000 条未读的 @ 消息，取 100 条未读
/// desc 为 true 时获取后 100 条消息，messageList 的顺序是 901 到 1000
/// desc 为 false 是获取前 100 条消息，messageList 的顺序是 1 到 100
///
/// - Warning: 使用 IMKit 注意在进入会话页面前调用，否则在进入会话清除未读数的接口 clearMessagesUnreadStatus: targetId:
/// 以及 设置消息接收状态接口 setMessageReceivedStatus:receivedStatus:会同步清除被提示信息状态。
/// - Since: 5.3.0
- (void)getUnreadMentionedMessages:(RCConversationType)conversationType
                          targetId:(NSString *)targetId
                             count:(int)count
                              desc:(BOOL)desc
                        completion:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages))completion;

/// 异步获取消息的发送时间（Unix 时间戳、毫秒）
///
/// - Parameter messageId: 消息 ID
/// - Parameter completion: 异步回调 [消息的发送时间（Unix 时间戳、毫秒）]
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)getMessageSendTime:(long)messageId completion:(nullable void (^)(long long time))completion;

/// 异步通过 messageId 获取消息实体
///
/// - Parameter messageId: 消息 ID（数据库索引唯一值）
/// - Parameter completion: 异步回调 [消息实体，当获取失败的时候，会返回 nil]
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)getMessage:(long)messageId completion:(nullable void (^)(RCMessage *_Nullable message))completion;

/// 异步通过全局唯一 ID 获取消息实体
///
/// - Parameter messageUId: 全局唯一 ID（服务器消息唯一 ID）
/// - Parameter completion: 异步回调 [消息实体，当获取失败的时候，会返回 nil]
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)getMessageByUId:(NSString *)messageUId completion:(nullable void (^)(RCMessage *_Nullable message))completion;

///
/// 获取会话里第一条未读消息。
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter completion: 异步回调 [第一条未读消息的实体]
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)getFirstUnreadMessage:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                   completion:(nullable void (^)(RCMessage *_Nullable message))completion;

/// 异步删除消息
///
/// - Parameter messageIds: 消息 ID 的列表，元素需要为 NSNumber 类型
/// - Parameter completion: 异步回调 [是否删除成功]
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)deleteMessages:(NSArray<NSNumber *> *)messageIds completion:(nullable void (^)(BOOL ret))completion;

/// 删除某个会话中的所有消息
///
/// - Parameter conversationType: 会话类型，不支持聊天室
/// - Parameter targetId: 会话 ID
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// 此方法删除数据库中该会话的消息记录，同时会整理压缩数据库，减少占用空间
///
/// - Remark: 消息操作
/// - Since: 5.0.0
- (void)deleteMessages:(RCConversationType)conversationType
              targetId:(NSString *)targetId
               success:(nullable void (^)(void))successBlock
                 error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 批量删除某个会话中的指定远端消息（同时删除对应的本地消息）
///
/// - Parameter conversationType: 会话类型，不支持聊天室
/// - Parameter targetId: 目标会话 ID
/// - Parameter messages: 将被删除的消息列表
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// 此方法会同时删除远端和本地消息。
/// 一次批量操作仅支持删除属于同一个会话的消息，请确保消息列表中的所有消息来自同一会话
/// 一次最多删除 100 条消息。
///
/// - Remark: 消息操作
/// - Since: 5.0.0
- (void)deleteRemoteMessage:(RCConversationType)conversationType
                   targetId:(NSString *)targetId
                   messages:(NSArray<RCMessage *> *)messages
                    success:(nullable void (^)(void))successBlock
                      error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 异步删除某个会话中的所有消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter completion: 异步回调 [是否删除成功]
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)clearMessages:(RCConversationType)conversationType
             targetId:(NSString *)targetId
           completion:(nullable void (^)(BOOL ret))completion;

/// 异步设置消息的附加信息
///
/// - Parameter messageId: 消息 ID
/// - Parameter value: 附加信息，最大 1024 字节
/// - Parameter completion: 异步回调 [是否设置成功]
///
/// 用于扩展消息的使用场景。只能用于本地使用，无法同步到远端。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)setMessageExtra:(long)messageId
                  value:(nullable NSString *)value
             completion:(nullable void (^)(BOOL ret))completion;

/// 异步设置消息的接收状态
///
/// - Parameter messageId: 消息 ID
/// - Parameter receivedStatusInfo: 消息接收状态的 RCReceivedStatusInfo 对象
/// - Parameter completion: 异步回调 [是否设置成功]
///
/// 用于 UI 展示消息为已读，已下载等状态。
/// 新接口使用 RCReceivedStatusInfo 类来记录已读、已下载、已听等状态，通过按位计算的方式，支持多种状态并存
/// 可以通过 RCReceivedStatusInfo 对外接口直接获取是否已读/已下载/已听等
///
/// - Warning: 新、旧接口原则上不混用，否则接收状态可能出现偏差
/// - Remark: 消息操作
/// - Since: 5.6.8
- (void)setMessageReceivedStatus:(long)messageId
              receivedStatusInfo:(RCReceivedStatusInfo *)receivedStatusInfo
                      completion:(nullable void (^)(BOOL ret))completion;

/// 异步设置消息的发送状态
///
/// - Parameter messageId: 消息 ID
/// - Parameter sentStatus: 消息的发送状态
/// - Parameter completion: 异步回调 [是否设置成功]
///
/// 用于 UI 展示消息为正在发送，对方已接收等状态。
/// 为了保证 UI 正常显示，5.1.8 版本起不再支持 app 将消息状态设置为 SentStatus_SENDING
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)setMessageSentStatus:(long)messageId
                  sentStatus:(RCSentStatus)sentStatus
                  completion:(nullable void (^)(BOOL ret))completion;

/// 开始焚烧消息（目前仅支持单聊）
///
/// - Parameter message: 消息类
/// 仅限接收方调用
///
/// - Remark: 高级功能
/// - Since: 5.0.0
- (void)messageBeginDestruct:(RCMessage *)message;

/// 停止焚烧消息（目前仅支持单聊）
///
/// - Parameter message: 消息类
/// 仅限接收方调用
///
/// - Remark: 高级功能
/// - Since: 5.0.0
- (void)messageStopDestruct:(RCMessage *)message;

#pragma mark - 会话列表操作

/// 获取 @我未读消息的会话列表
/// - Parameters: param 详见 RCGetUnreadMentionMeConversationListParams 定义
///   - completion: 异步回调 [会话 RCConversation 的列表] [code : 获取是否成功，0 表示成功，非 0 表示失败]
///
/// - Since: 5.28.0
- (void)getUnreadMentionMeConversationList:(RCGetUnreadMentionMeConversationListParams *)params
                                completion:(nullable void(^)(NSArray<RCConversation *> *conversations,
                                                             RCErrorCode code))completion;


/// 拉取远端会话列表
/// - Parameters:
///   - successBlock: 接口调用成功的回调
///   - errorBlock: 接口调用失败的回调 [携带错误码]
/// 此方法会从 IM 服务器中拉取会话列表。结果回调只代码接口是否成功，不会返回具体的会话列表数据。
/// 拉取完成的回调，请监听 -[RCConversationDelegate remoteConversationListDidSync:] 。
/// - Warning: 不支持超级群
/// - Remark: 远端会话列表
/// - Since 5.20.0
- (void)getRemoteConversationListWithSuccess:(nullable void (^)(void))successBlock
                                       error:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 异步获取会话列表
///
/// - Parameter conversationTypeList: 会话类型的数组 (需要将 RCConversationType 转为 NSNumber 构建 NSArray)
/// - Parameter completion: 异步回调 [会话 RCConversation 的列表]
///
/// 此方法会从本地数据库中，读取会话列表。
/// 返回的会话列表按照时间从前往后排列，如果有置顶的会话，则置顶的会话会排列在前面。
/// 当您的会话较多且没有清理机制的时候，强烈建议您使用 getConversationList: count: startTime:
/// 分页拉取会话列表，否则有可能造成内存过大。
///
/// - Remark: 会话列表
/// - Since: 5.3.0
- (void)getConversationList:(NSArray<NSNumber *> *)conversationTypeList
                 completion:(nullable void (^)(NSArray<RCConversation *> *_Nullable conversationList))completion;

/// 异步分页获取会话列表
///
/// - Parameter conversationTypeList: 会话类型的数组 (需要将 RCConversationType 转为 NSNumber 构建 NSArray)
/// - Parameter count: 获取的数量（当实际取回的会话数量小于 count 值时，表明已取完数据）
/// - Parameter startTime: 会话的时间戳（获取这个时间戳之前的会话列表，0 表示从最新开始获取，单位：毫秒）
/// - Parameter completion: 异步回调 [会话 RCConversation 的列表]
///
/// 此方法会从本地数据库中，读取会话列表。
/// 返回的会话列表按照时间从前往后排列，如果有置顶的会话，则置顶的会话会排列在前面。
///
/// - Remark: 会话列表
/// - Since: 5.3.0
- (void)getConversationList:(NSArray<NSNumber *> *)conversationTypeList
                      count:(int)count
                  startTime:(long long)startTime
                 completion:(nullable void (^)(NSArray<RCConversation *> *_Nullable conversationList))completion;
/// 异步分页获取会话列表
///
/// - Parameter conversationTypeList: 会话类型的数组 (需要将 RCConversationType 转为 NSNumber 构建 NSArray)
/// - Parameter count: 获取的数量（当实际取回的会话数量小于 count 值时，表明已取完数据）
/// - Parameter startTime: 会话的时间戳（获取这个时间戳之前的会话列表，0 表示从最新开始获取，单位：毫秒）
/// - Parameter topPriority: 查询结果的排序方式，是否置顶优先，传 true 表示置顶会话优先返回，否则结果只以会话时间排序
/// - Parameter completion: 异步回调 [会话 RCConversation 的列表]
///
/// 此方法会从本地数据库中，读取会话列表。
/// 返回的会话列表按照时间从前往后排列，如果有置顶的会话，则置顶的会话会排列在前面。
///
/// - Remark: 会话列表
/// - Since: 5.6.6
- (void)getConversationList:(NSArray<NSNumber *> *)conversationTypeList
                      count:(int)count
                  startTime:(long long)startTime
                topPriority:(BOOL)topPriority
                 completion:(nullable void (^)(NSArray<RCConversation *> *_Nullable conversationList))completion;

/// 获取所有的未读会话列表
///
/// - Parameter conversationTypeList: 会话类型的数组 (需要将 RCConversationType 转为 NSNumber 构建 NSArray)
/// - Parameter completion: 异步回调 [会话 RCConversation 的列表]
///
/// 此方法会从本地数据库中，读取会话列表。
/// 返回的会话列表按照时间从前往后排列，如果有置顶的会话，则置顶的会话会排列在前面。
///
/// - Remark: 会话列表
/// - Since: 5.3.2
- (void)getUnreadConversationList:(NSArray<NSNumber *> *)conversationTypeList
                       completion:(nullable void (^)(NSArray<RCConversation *> *_Nullable conversationList))completion;

/// 异步获取单个会话数据
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter completion: 异步回调 [会话的对象]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)getConversation:(RCConversationType)conversationType
               targetId:(NSString *)targetId
             completion:(nullable void (^)(RCConversation *_Nullable conversation))completion;

/// 批量获取会话数据
///
/// - Parameter conversationIdentifiers: 会话信息列表，每次获取会话个数最大为 100
/// - Parameter success: 成功回调 [会话的对象]
/// - Parameter error: 错误回调 [错误码]
///
/// 此方法会从本地数据库中读取会话，支持单聊、群聊、系统会话。
/// - Remark: 会话
/// - Since: 5.8.2
- (void)getConversations:(NSArray<RCConversationIdentifier *> *)conversationIdentifiers
                 success:(nullable void (^)(NSArray<RCConversation *> *conversations))successBlock
                   error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 异步获取会话中的消息数量
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter completion: 异步回调 [会话中的消息数量]
///
/// -1 表示获取消息数量出错。
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)getMessageCount:(RCConversationType)conversationType
               targetId:(NSString *)targetId
             completion:(nullable void (^)(int count))completion;

/// 异步获取会话中某段时间范围内的消息数量 (子线程回调，如有 UI 操作，请切回主线程)
///
/// - Parameter conversationType    会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter startTime      查询 startTime 之后的消息，startTime >= 0
/// - Parameter endTime           查询 endTime 之前的消息，endTime > startTime
/// - Parameter success           异步回调 [会话中的消息数量]
/// - Parameter error               错误回调 [错误码]
///
/// - Remark: 会话
/// - Since: 5.6.4
- (void)getMessageCountByTimeRange:(RCConversationType)conversationType
                          targetId:(NSString *)targetId
                         startTime:(long long)startTime
                           endTime:(long long)endTime
                           success:(nullable void (^)(NSInteger count))successBlock
                             error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 异步删除指定类型的会话
///
/// - Parameter conversationTypeList: 会话类型的数组 (需要将 RCConversationType 转为 NSNumber 构建 NSArray)
/// - Parameter completion: 异步回调 [是否删除成功]
///
/// 此方法会从本地存储中删除该会话，同时删除会话中的消息。
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)clearConversations:(NSArray<NSNumber *> *)conversationTypeList
                completion:(nullable void (^)(BOOL ret))completion;

/// 异步删除本地和服务的会话
///
/// - Parameter conversationType: 会话类型
///   - conversationType: 会话类型
///   - targetId: 会话 ID
///   - isDeleteRemote: 是否删除服务的会话
///   - successBlock: 删除成功的回调
///   - errorBlock: 删除失败的回调 [携带错误码]
/// 此方法会删除该会话，但是不会删除会话中的消息。如果此会话中有新的消息，该会话将重新在会话列表中显示，并显示最近的历史消息。
/// - Warning: 此方法会同时删除本地和服务的会话。如果服务的会话删除失败，本地的会话不会被删除
/// SDK 在未连接的情况下，删除服务会话会失败
///
/// - Remark: 会话
/// - Since: 5.10.2
- (void)removeConversation:(RCConversationType)conversationType
                  targetId:(NSString *)targetId
            isDeleteRemote:(BOOL)isDeleteRemote
                   success:(nullable void (^)(void))successBlock
                     error:(nullable void (^)(RCErrorCode errorCode))errorBlock;


/// 批量删除会话
/// - Parameters: RCConversationBatchDeletionParams: 批量删除会话的参数
///   - params: 批量删除会话的参数，具体参数请参考 `RCConversationBatchDeletionParams` 类
///   - successBlock: 删除成功的回调
///   - errorBlock: 删除失败的回调 [携带错误码]
///   - Since 5.26.0
- (void)batchDeleteConversations:(RCConversationBatchDeletionParams *)params
                         success:(nullable void (^)(void))successBlock
                           error:(nullable void (^)(RCErrorCode errorCode))errorBlock;


/// 异步设置会话的置顶状态
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter isTop: 是否置顶
/// - Parameter completion: 异步回调 [设置是否成功]
///
/// 会话不存在时设置置顶，会在会话列表生成会话。
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)setConversationToTop:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
                       isTop:(BOOL)isTop
                  completion:(nullable void (^)(BOOL ret))completion;

/// 异步设置会话的置顶状态
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter isTop: 是否置顶
/// - Parameter needUpdateTime: 是否更新时间
/// - Parameter completion: 异步回调 [设置是否成功]
///
/// 会话不存在时设置置顶，会在会话列表生成会话。
///
/// - Remark: 会话
- (void)setConversationToTop:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
                       isTop:(BOOL)isTop
              needUpdateTime:(BOOL)needUpdateTime
                  completion:(nullable void (^)(BOOL result))completion;

/// 更新会话的置顶状态。
/// - Parameters:
///   - conversationIdentifiers: 需要更新的会话。
///   - isTop: 是否置顶。
///   - option: 置顶状态信息。
///   - completion: 结果回调。
///
/// - Since: 5.20.0
- (void)setConversationsToTop:(NSArray<RCConversationIdentifier *> *)conversationIdentifiers
                        isTop:(BOOL)isTop
                       option:(nullable RCConversationTopOption *)option
                   completion:(nullable void (^)(RCErrorCode code))completion;

/// 异步获取置顶的会话列表
///
/// - Parameter conversationTypeList: 会话类型的数组 (需要将 RCConversationType 转为 NSNumber 构建 NSArray)
/// - Parameter completion: 异步回调 [置顶的会话 RCConversation 的列表]
///
/// 此方法会从本地数据库中，读取置顶的会话列表。
///
/// - Remark: 会话列表
/// - Since: 5.3.0
- (void)getTopConversationList:(NSArray<NSNumber *> *)conversationTypeList
                    completion:(nullable void (^)(NSArray<RCConversation *> *_Nullable conversationList))completion;

/// 异步获取会话的置顶状态
///
/// - Parameter conversationIdentifier: 会话信息
/// - Parameter completion: 异步回调 [是否获取成功]
///
/// 此方法会从本地数据库中，读取该会话是否置顶。
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)getConversationTopStatus:(RCConversationIdentifier *)conversationIdentifier
                      completion:(nullable void (^)(BOOL ret))completion;

/// 设置实时会话监听
/// - Parameter delegate: 代理
/// - Since: 5.1.2
- (void)setRCConversationDelegate:(nullable id<RCConversationDelegate>)delegate;

#pragma mark 会话中的草稿操作

/// 异步获取会话中的草稿信息（用户输入但未发送的暂存消息）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话目标 ID
/// - Parameter completion: 异步回调 [该会话中的草稿]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)getTextMessageDraft:(RCConversationType)conversationType
                   targetId:(NSString *)targetId
                 completion:(nullable void (^)(NSString *_Nullable draft))completion;

/// 异步保存草稿信息（用户输入但未发送的暂存消息）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话目标 ID
/// - Parameter content: 草稿信息
/// - Parameter completion: 异步回调 [是否保存成功]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)saveTextMessageDraft:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
                     content:(NSString *)content
                  completion:(nullable void (^)(BOOL ret))completion;

/// 异步删除会话中的草稿信息（用户输入但未发送的暂存消息）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话目标 ID
/// - Parameter completion: 异步回调 [是否删除成功]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)clearTextMessageDraft:(RCConversationType)conversationType
                     targetId:(NSString *)targetId
                   completion:(nullable void (^)(BOOL ret))completion;

#pragma mark 未读消息数

/// 获取所有的未读消息数（聊天室会话除外）
/// - Parameter completion: 异步回调 [所有的未读消息数]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)getTotalUnreadCountWith:(nullable void (^)(int unreadCount))completion;

/// 异步获取某个会话内的未读消息数（聊天室会话除外）
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话目标 ID
/// - Parameter completion: 异步回调 [该会话内的未读消息数]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)getUnreadCount:(RCConversationType)conversationType
              targetId:(NSString *)targetId
            completion:(nullable void (^)(int count))completion;

/// 异步获取某个会话内的未读消息数
///
/// - Parameter conversationIdentifier: 会话信息
/// - Parameter messageClassList: 消息类型数组
/// - Parameter completion: 异步回调 [该会话内的未读消息数]
///
/// 此方法不支持聊天室和超级群的会话类型。
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)getUnreadCount:(RCConversationIdentifier *)conversationIdentifier
      messageClassList:(NSArray<Class> *)messageClassList
            completion:(nullable void (^)(int count))completion;

/// 异步获取某些会话的总未读消息数（聊天室会话除外）
///
/// - Parameter conversations: 会话列表（RCConversation 对象只需要 conversationType 和 targetId，channelId 按需使用）
/// - Parameter completion: 异步回调 [传入会话列表的未读消息数]
///
/// conversations 会话个数不能超过 300，超过会被截断。
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)getTotalUnreadCount:(NSArray<RCConversation *> *)conversations
                 completion:(nullable void (^)(int count))completion;

/// 异步获取某些类型的会话中所有的未读消息数（聊天室会话除外）
///
/// - Parameter conversationTypes: 会话类型的数组
/// - Parameter isContain: 是否包含免打扰消息的未读数
/// - Parameter completion: 异步回调 [该类型的会话中所有的未读消息数]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)getUnreadCount:(NSArray<NSNumber *> *)conversationTypes
        containBlocked:(bool)isContain
            completion:(nullable void (^)(int count))completion;

/// 异步获取某个类型的会话中所有的未读消息数（聊天室会话除外）
///
/// - Parameter conversationTypes: 会话类型的数组
/// - Parameter completion: 异步回调 [该类型的会话中所有的未读消息数]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)getUnreadCount:(NSArray<NSNumber *> *)conversationTypes completion:(nullable void (^)(int count))completion;

/// 异步获取某个类型的会话中所有未读的被@的消息数
///
/// - Parameter conversationTypes: 会话类型的数组
/// - Parameter completion: 异步回调 [该类型的会话中所有未读的被@的消息数]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)getUnreadMentionedCount:(NSArray<NSNumber *> *)conversationTypes
                     completion:(nullable void (^)(int count))completion;

/// 异步清除某个会话中的未读消息数
///
/// - Parameter conversationType: 会话类型，不支持聊天室
/// - Parameter targetId: 会话 ID
/// - Parameter completion: 异步回调 [是否清除成功]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)clearMessagesUnreadStatus:(RCConversationType)conversationType
                         targetId:(NSString *)targetId
                       completion:(nullable void (^)(BOOL ret))completion;

/// 异步清除某个会话中的未读消息数（该会话在时间戳 timestamp 之前的消息将被置成已读。）
///
/// - Parameter conversationType: 会话类型，不支持聊天室
/// - Parameter targetId: 会话 ID
/// - Parameter timestamp: 该会话已阅读的最后一条消息的发送时间戳，单位：毫秒
/// - Parameter completion: 异步回调 [是否清除成功]
///
/// - Remark: 会话
/// - Since: 5.3.0
- (void)clearMessagesUnreadStatus:(RCConversationType)conversationType
                         targetId:(NSString *)targetId
                             time:(long long)timestamp
                       completion:(nullable void (^)(BOOL ret))completion;

#pragma mark - 会话的消息提醒

/// 查询会话的消息提醒状态
///
/// - Parameter conversationType: 会话类型（不支持聊天室，聊天室是不接受会话消息提醒的）
/// - Parameter targetId: 会话 ID
/// - Parameter successBlock: 查询成功的回调 [nStatus:会话设置的消息提醒状态]
/// - Parameter errorBlock: 查询失败的回调 [status:设置失败的错误码]
///
/// - Remark: 会话
/// - Since: 5.0.0
- (void)getConversationNotificationStatus:(RCConversationType)conversationType
                                 targetId:(NSString *)targetId
                                  success:(nullable void (^)(RCConversationNotificationStatus nStatus))successBlock
                                    error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 异步获取消息免打扰会话列表
///
/// - Parameter conversationTypeList: 会话类型的数组 (需要将 RCConversationType 转为 NSNumber 构建 NSArray)
/// - Parameter completion: 异步回调 [消息免打扰会话 RCConversation 的列表]
///
/// 此方法会从本地数据库中，读取消息免打扰会话列表。
///
/// - Remark: 会话列表
/// - Since: 5.3.0
- (void)getBlockedConversationList:(NSArray<NSNumber *> *)conversationTypeList
                        completion:(nullable void (^)(NSArray<RCConversation *> *_Nullable conversationList))completion;

#pragma mark - 输入状态提醒

/// typing 状态更新的时间，默认是 6s
///
/// - Remark: 功能设置
/// - Since: 5.1.1
@property (nonatomic, assign) NSInteger typingUpdateSeconds;

/// 设置输入状态的监听器
///
/// - Parameter delegate: IMLibCore 输入状态的的监听器
///
/// - Warning: 目前仅支持单聊。
///
/// - Remark: 功能设置
/// - Since: 5.0.0
- (void)setRCTypingStatusDelegate:(nullable id<RCTypingStatusDelegate>)delegate;

/// 向会话中发送正在输入的状态
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话目标  ID
/// - Parameter objectName: 正在输入的消息的类型名
///
///
/// contentType 为用户当前正在编辑的消息类型名，即 RCMessageContent 中 getObjectName 的返回值。
/// 如文本消息，应该传类型名"RC:TxtMsg"。
///
/// - Warning: 目前仅支持单聊。
///
/// - Remark: 高级功能
/// - Since: 5.0.0
- (void)sendTypingStatus:(RCConversationType)conversationType
                targetId:(NSString *)targetId
             contentType:(NSString *)objectName;

#pragma mark - 黑名单

/// 将某个用户加入黑名单
///
/// - Parameter userId: 需要加入黑名单的用户 ID
/// - Parameter successBlock: 加入黑名单成功的回调
/// - Parameter errorBlock: 加入黑名单失败的回调 [status:失败的错误码]
///
/// 将对方加入黑名单后，对方再发消息时，就会提示“您的消息已经发出，但被对方拒收”。但您仍然可以给对方发送消息。
///
/// - Remark: 高级功能
/// - Since: 5.0.0
- (void)addToBlacklist:(NSString *)userId
               success:(nullable void (^)(void))successBlock
                 error:(nullable void (^)(RCErrorCode status))errorBlock
    NS_SWIFT_NAME(addToBlacklist(_:success:error:));

/// 将某个用户移出黑名单
///
/// - Parameter userId: 需要移出黑名单的用户 ID
/// - Parameter successBlock: 移出黑名单成功的回调
/// - Parameter errorBlock: 移出黑名单失败的回调 [status:失败的错误码]
///
/// - Remark: 高级功能
/// - Since: 5.0.0
- (void)removeFromBlacklist:(NSString *)userId
                    success:(nullable void (^)(void))successBlock
                      error:(nullable void (^)(RCErrorCode status))errorBlock
    NS_SWIFT_NAME(removeFromBlacklist(_:success:error:));

/// 查询某个用户是否已经在黑名单中
///
/// - Parameter userId: 需要查询的用户 ID
/// - Parameter successBlock: 查询成功的回调
/// [bizStatus:该用户是否在黑名单中。0 表示已经在黑名单中，101 表示不在黑名单中]
/// - Parameter errorBlock: 查询失败的回调 [status:失败的错误码]
///
/// - Remark: 高级功能
/// - Since: 5.0.0
- (void)getBlacklistStatus:(NSString *)userId
                   success:(nullable void (^)(int bizStatus))successBlock
                     error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 查询已经设置的黑名单列表
///
/// - Parameter successBlock: 查询成功的回调
/// [blockUserIds:已经设置的黑名单中的用户 ID 列表]
/// - Parameter errorBlock: 查询失败的回调 [status:失败的错误码]
///
/// - Remark: 高级功能
/// - Since: 5.0.0
- (void)getBlacklist:(nullable void (^)(NSArray<NSString *> *blockUserIds))successBlock
               error:(nullable void (^)(RCErrorCode status))errorBlock;

#pragma mark - 推送业务数据统计

/// 统计本地通知的点击事件
///
/// - Parameter userInfo: 本地通知的内容
///
/// 此方法用于统计本地通知的点击率。
///

/// 杀掉 app 通过 AppDelegate 的 -application:didFinishLaunchingWithOptions: 获取本地推送内容；
/// 如：
/// - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
///     NSDictionary *userInfo;
///     if (@available(iOS 10.0, *)) {
///         userInfo = launchOptions[UIApplicationLaunchOptionsLocalNotificationKey];
///     } else {
///         UILocalNotification *localNotification = launchOptions[UIApplicationLaunchOptionsLocalNotificationKey];
///         userInfo = localNotification.userInfo;
///     }
///     if (userInfo) {
///         [[RCCoreClient sharedCoreClient] recordLocalNotificationResponseEvent:userInfo];
///     }
///     return YES;
/// }
///
/// app 在后台或者前台时，点击通知
/// 在 iOS 10 以下版本中，通过在 AppDelegate 的 -application:didReceiveLocalNotification: 获取远程推送内容，
/// - (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification {
///     [[RCCoreClient sharedCoreClient] recordLocalNotificationResponseEvent:notification.userInfo];
/// }
///
/// 在 iOS 10 及以上版本中，只通过在 AppDelegate 实现 UNUserNotificationCenterDelegate 的方法 -userNotificationCenter:didReceiveNotificationResponse:withCompletionHandler:，获取 response.notification.request.content.userInfo，
/// 如：
/// - (void)userNotificationCenter:(UNUserNotificationCenter *)center
/// didReceiveNotificationResponse:(UNNotificationResponse *)response
/// withCompletionHandler:(void (^)(void))completionHandler {
///     // 不需要 app 层区分本地通知和远程推送，recordLocalNotificationResponseEvent 内部判断只在本地时统计
///     [[RCCoreClient sharedCoreClient] recordLocalNotificationResponseEvent:response.notification.request.content.userInfo];
///     completionHandler();
/// }
///
/// - Since: 5.14.0
- (void)recordLocalNotificationResponseEvent:(NSDictionary *)userInfo;

/// 统计收到远程推送的事件
///
/// - Parameter userInfo: 远程推送的内容
///
/// 此方法用于统计融云推送服务的到达率。
/// 如果您需要统计推送服务的到达率，需要在 App  中实现通知扩展，并在 NotificationService  的 -didReceiveNotificationRequest: withContentHandler: 中
/// 先初始化 appkey 再调用此方法并将推送内容 userInfo 传入即可。
///
/// 如果有单独的统计服务地址，还需要在初始化之后设置独立的统计服务地址
///
/// 如：
///
/// - (void)didReceiveNotificationRequest:(UNNotificationRequest *)request withContentHandler:(void (^)(UNNotificationContent * _Nonnull))contentHandler {
/// self.contentHandler = contentHandler;
/// self.bestAttemptContent = [request.content mutableCopy];
///
/// NSDictionary *userInfo = self.bestAttemptContent.userInfo;
/// [[RCCoreClient sharedCoreClient] initWithAppKey:RONGCLOUD_IM_APPKEY];
/// if (RONGCLOUD_STATS_SERVER.length > 0) {
/// [[RCCoreClient sharedCoreClient] setStatisticServer:RONGCLOUD_STATS_SERVER];
/// }
/// [[RCCoreClient sharedCoreClient] recordReceivedRemoteNotificationEvent:userInfo];
///
/// self.contentHandler(self.bestAttemptContent);
/// }
///
/// - Remark: 高级功能
/// - Since: 5.1.3
- (void)recordReceivedRemoteNotificationEvent:(NSDictionary *)userInfo;

/// 统计远程推送的点击事件
///
/// - Parameter userInfo: 远程推送的内容
///
/// 此方法用于统计融云推送服务的点击率。
/// 杀掉 app 通过 AppDelegate 的 -application:didFinishLaunchingWithOptions: 获取远程推送内容；

/// - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
///     NSDictionary *remoteNotification = launchOptions[UIApplicationLaunchOptionsRemoteNotificationKey];
///     if (remoteNotification) {
///         [[RCCoreClient sharedCoreClient] recordRemoteNotificationEvent:remoteNotification];
///     }
///     return YES;
/// }
///
/// app 在后台或者前台时，点击推送
/// 在 iOS 10 以下版本中，通过在 AppDelegate 的 -application:didReceiveRemoteNotification: 获取远程推送内容，
/// - (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo {
///     [[RCCoreClient sharedCoreClient] recordRemoteNotificationEvent:userInfo];
/// }
/// 在 iOS 10 及以上版本中，只通过在 AppDelegate 实现 UNUserNotificationCenterDelegate 的方法 -userNotificationCenter:didReceiveNotificationResponse:withCompletionHandler:，获取 response.notification.request.content.userInfo，
/// 如：
/// - (void)userNotificationCenter:(UNUserNotificationCenter *)center
/// didReceiveNotificationResponse:(UNNotificationResponse *)response
/// withCompletionHandler:(void (^)(void))completionHandler {
///     // 不需要 app 层区分本地通知和远程推送，recordLocalNotificationResponseEvent 内部判断只在远程推送时统计
///     [[RCCoreClient sharedCoreClient] recordLocalNotificationResponseEvent:response.notification.request.content.userInfo];
///     completionHandler();
/// }
///
/// - Remark: 高级功能
/// - Since: 5.0.0
- (void)recordRemoteNotificationEvent:(NSDictionary *)userInfo;

/// 获取点击的启动事件中，融云推送服务的扩展字段
///
/// - Parameter launchOptions: App 的启动附加信息
/// - Returns: 收到的融云推送服务的扩展字段，nil 表示该启动事件不包含来自融云的推送服务
///
/// 此方法仅用于获取融云推送服务的扩展字段。
///
/// - Remark: 高级功能
/// - Since: 5.0.0
- (nullable NSDictionary *)getPushExtraFromLaunchOptions:(nullable NSDictionary *)launchOptions;

/// 获取点击的远程推送中，融云推送服务的扩展字段
///
/// - Parameter userInfo: 远程推送的内容
/// - Returns: 收到的融云推送服务的扩展字段，nil 表示该远程推送不包含来自融云的推送服务
///
/// 此方法仅用于获取融云推送服务的扩展字段。
///
/// - Remark: 高级功能
/// - Since: 5.0.0
- (nullable NSDictionary *)getPushExtraFromRemoteNotification:(NSDictionary *)userInfo;

#pragma mark - 工具类方法

/// 获取当前 IMLibCore SDK 的版本号
///
/// - Returns: 当前 IMLibCore SDK 的版本号，如：@"2.0.0"
///
/// - Remark: 数据获取
/// - Since: 5.0.0
+ (NSString *)getVersion;

/// 获取当前手机与服务器的时间差
///
/// - Parameter completion: 回调
/// 消息发送成功后，SDK 会与服务器同步时间，消息所在数据库中存储的时间就是服务器时间，单位：毫秒。
///
/// - Remark: 数据获取
/// - Since: 5.3.0
- (void)getDeltaTime:(nullable void (^)(long long))completion;

/// 将 AMR 格式的音频数据转化为 WAV 格式的音频数据，数据开头携带 WAVE 文件头
///
/// - Parameter data: AMR 格式的音频数据，必须是 AMR-NB 的格式
/// - Returns: WAV 格式的音频数据
///
/// - Remark: 数据获取
/// - Since: 5.0.0
- (nullable NSData *)decodeAMRToWAVE:(NSData *)data;

/// 将 AMR 格式的音频数据转化为 WAV 格式的音频数据，数据开头不携带 WAV 文件头
///
/// - Parameter data: AMR 格式的音频数据，必须是 AMR-NB 的格式
/// - Returns: WAV 格式的音频数据
///
/// - Remark: 数据获取
/// - Since: 5.0.0
- (nullable NSData *)decodeAMRToWAVEWithoutHeader:(NSData *)data;

#pragma mark - 语音消息设置

/// 语音消息类型，默认 RCVoiceMessageTypeHighQuality
///
/// 老版本 SDK 不兼容新版本语音消息
/// 2.9.19 之前的版本无法播放高音质语音消息；
/// 2.9.19 及之后的版本可以同时兼容普通音质语音消息和高音质语音消息；
/// 客服会话类型 (ConversationType_CUSTOMERSERVICE) 不支持高音质语音消息。
///
/// - Remark: 功能设置
/// - Since: 5.0.0
@property (nonatomic, assign) RCVoiceMessageType voiceMsgType;

#pragma mark - 搜索

/// 搜索本地消息。
///
/// - Parameters:
///   - params: 搜索参数。
///   - completionHandler: 结果回调。
///
/// - Since: 5.22.0
- (void)searchMessagesWithParams:(RCSearchMessageParams *)params
               completionHandler:(RCSearchMessageListCompletion)completionHandler;

/// 根据关键字异步搜索指定会话中的消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter keyword: 关键字
/// - Parameter count: 最大的查询数量
/// - Parameter startTime: 查询 startTime 之前的消息（传 0 表示不限时间），单位：毫秒
/// - Parameter completion: 异步回调 [匹配的消息列表]
///
/// 只支持搜索已存储到本地的消息。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)searchMessages:(RCConversationType)conversationType
              targetId:(NSString *)targetId
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
               keyword:(NSString *)keyword
             startTime:(long long)startTime
               endTime:(long long)endTime
                offset:(int)offset
                 limit:(int)limit
            completion:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages))completion;

/// 按用户 ID 异步搜索指定会话中的消息
///
/// - Parameter conversationType: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter userId: 搜索用户 ID
/// - Parameter count: 最大的查询数量
/// - Parameter startTime: 查询 startTime 之前的消息（传 0 表示不限时间），单位：毫秒
/// - Parameter completion: 异步回调 [匹配的消息列表]
///
/// 只支持搜索已存储到本地的消息。
///
/// - Remark: 消息操作
/// - Since: 5.3.0
- (void)searchMessages:(RCConversationType)conversationType
              targetId:(NSString *)targetId
                userId:(NSString *)userId
                 count:(int)count
             startTime:(long long)startTime
            completion:(nullable void (^)(NSArray<RCMessage *> *_Nullable messages))completion;

/// 根据关键字搜索指定会话中，指定消息类型的本地历史消息
///
/// - Parameter conversationIdentifier: 会话类型、会话 ID
/// - Parameter keyword: 关键字，非空
/// - Parameter objectNameList: 需要搜索的消息类型名列表 (即每个消息类方法 getObjectName 的返回值)，非空
/// - Parameter limit: 最大的查询数量 [最大 100，超过则使用 100]
/// - Parameter startTime: 查询 startTime 之前的消息（传 0 表示从最新消息开始搜索），单位：毫秒
/// - Parameter success: 异步成功回调 [匹配的消息列表]
/// - Parameter error: 异步失败回调 [错误码]
///
/// 超级群会话类型只支持搜索已存储到本地的消息。
///
/// - Remark: 消息操作
/// - Since: 5.8.1
- (void)searchMessages:(RCConversationIdentifier *)conversationIdentifier
               keyword:(NSString *)keyword
        objectNameList:(NSArray<NSString *> *)objectNameList
                 limit:(int)limit
             startTime:(long long)startTime
               success:(nullable void (^)(NSArray<RCMessage *> *messages))successBlock
                 error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 根据关键字异步搜索会话
///
/// - Parameter conversationTypeList: 需要搜索的会话类型的数组 (需要将 RCConversationType 转为 NSNumber 构建 NSArray)
/// - Parameter objectNameList: 需要搜索的消息类型名列表 (即每个消息类方法 getObjectName 的返回值)
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
- (void)searchConversations:(NSArray<NSNumber *> *)conversationTypeList
                messageType:(NSArray<NSString *> *)objectNameList
                    keyword:(NSString *)keyword
                 completion:(nullable void (^)(NSArray<RCSearchConversationResult *> *_Nullable results))completion;
#pragma mark - 日志

/// 设置日志级别
///
/// - Remark: 高级功能
/// - Since: 5.0.0
@property (nonatomic, assign) RCLogLevel logLevel;

/// 设置 IMLibCore 日志的监听器
///
/// - Parameter delegate: IMLibCore 日志的监听器
///
/// 您可以通过 logLevel 来控制日志的级别。
///
/// - Remark: 功能设置
/// - Since: 5.0.0
- (void)setRCLogInfoDelegate:(nullable id<RCLogInfoDelegate>)delegate;

#pragma mark - File Storage

/// 文件消息下载路径
///
/// 默认值为沙盒下的 Documents/MyFile 目录。您可以通过修改 RCConfig.plist 中的 RelativePath 来修改该路径。
///
/// - Remark: 数据获取
/// - Since: 5.0.0
@property (nonatomic, strong, readonly) NSString *fileStoragePath;

#pragma mark - 第三方平台厂商接口
/// 获取 Vendor token. 仅供融云第三方服务厂家使用。
///
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Remark: 数据获取
/// - Since: 5.0.0
- (void)getVendorToken:(nullable void (^)(NSString *vendorToken))successBlock
                 error:(nullable void (^)(RCErrorCode nErrorCode))errorBlock;

/// 远程推送相关设置
///
/// - Remark: 功能设置
/// - Since: 5.0.0
@property (nonatomic, strong, readonly) RCPushProfile *pushProfile;

#pragma mark - 历史消息

/// 设置离线消息在服务端的存储时间（以天为单位）
///
/// - Parameter duration: 存储时间，范围【1~7 天】
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Remark: 功能设置
/// - Since: 5.0.0
- (void)setOfflineMessageDuration:(int)duration
                          success:(nullable void (^)(void))successBlock
                          failure:(nullable void (^)(RCErrorCode nErrorCode))errorBlock;

/// 获取离线消息时间（以天为单位）
///
/// - Returns: 离线消息存储时间
///
/// - Remark: 数据获取
/// - Since: 5.0.0
- (int)getOfflineMessageDuration;

/// 异步获取离线消息时间（以天为单位）
/// - Parameter completion: 异步回调 [离线消息存储时间]
///
/// - Remark: 数据获取
/// - Since: 5.3.0
- (void)getOfflineMessageDuration:(nullable void (^)(int duration))completion;

/// 上报客户 App 版本信息。服务端支持按上报的 App 版本处理自定义消息的推送内容。
///
/// setAppVer 接口需要在 connect 接口前调用
/// - Parameter appVer: 用户 APP 的版本信息，String 类型，非空，长度小于 20，示例如  "1.1.0"。
///
/// - Remark: 功能设置
/// - Since: 5.0.0
- (void)setAppVer:(NSString *)appVer;

/// GIF 消息大小限制，以 KB 为单位，超过这个大小的 GIF 消息不能被发送
///
/// - Returns: GIF 消息大小，以 KB 为单位
///
/// - Remark: 数据获取
/// - Since: 5.0.0
- (NSInteger)getGIFLimitSize;

/// 小视频消息时长限制，以 秒 为单位，超过这个时长的小视频消息不能在相册中被选择发送
///
/// - Returns: 小视频消息时长，以 秒 为单位
/// - Since: 5.1.0
- (NSTimeInterval)getVideoDurationLimit;

#pragma mark - 会话状态同步，免打扰，置顶

/// 设置会话状态（包含置顶，消息免打扰）同步的监听器
///
/// - Parameter delegate: 会话状态同步的监听器
///
/// 可以设置并实现此 delegate 来进行会话状态同步。SDK 会在回调的 conversationStatusChange:方法中通知您会话状态的改变。
///
/// - Remark: 功能设置
/// - Since: 5.0.0
- (void)setRCConversationStatusChangeDelegate:(nullable id<RCConversationStatusChangeDelegate>)delegate;

/// 添加会话状态（包含置顶，消息免打扰）同步的监听器。
///
/// - Parameter delegate: 会话状态同步的监听器。
///
/// - Since: 5.24.0
- (void)addConversationStatusChangeDelegate:(nullable id<RCConversationStatusChangeDelegate>)delegate
    NS_SWIFT_NAME(addConversationStatusChangeDelegate(_:));

/// 移除会话状态（包含置顶，消息免打扰）同步的监听器。
///
/// - Parameter delegate: 会话状态同步的监听器。
///
/// - Since: 5.24.0
- (void)removeConversationStatusChangeDelegate:(nullable id<RCConversationStatusChangeDelegate>)delegate
    NS_SWIFT_NAME(removeConversationStatusChangeDelegate(_:));

#pragma mark - 消息扩展

/// 更新消息扩展信息
///
/// - Parameter expansionDic: 要更新的消息扩展信息键值对
/// - Parameter messageUId: 消息 messageUId
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// - Warning: 调用更新扩展的一方必须通过 successBlock 来处理本端的数据刷新。仅被动接收扩展变更的用户（包含本用户的其他端）通过监听方法 [RCMessageExpansionDelegate messageExpansionDidUpdate:message:] 获取通知。
///
/// 消息扩展信息是以字典形式存在。设置的时候从 expansionDic 中读取 key，如果原有的扩展信息中 key 不存在则添加新的 KV 对，如果 key 存在则替换成新的 value。
/// 扩展信息只支持单聊和群组，其它会话类型不能设置扩展信息
/// 扩展信息字典中的 Key 支持大小写英文字母、数字、部分特殊符号 + = - _ 的组合方式，最大长度 32；Value 最长长度，单次设置扩展数量最大为 20，消息的扩展总数不能超过 300
///
/// - Remark: 高级功能
/// - Since: 5.0.0
- (void)updateMessageExpansion:(NSDictionary<NSString *, NSString *> *)expansionDic
                    messageUId:(NSString *)messageUId
                       success:(nullable void (^)(void))successBlock
                         error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 删除消息扩展信息中特定的键值对
///
/// - Parameter keyArray: 消息扩展信息中待删除的 key 的列表
/// - Parameter messageUId: 消息 messageUId
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// - Warning: 调用删除扩展的一方必须通过 successBlock 来处理本端的数据刷新。仅被动接收扩展变更的用户（包含本用户的其他端）通过监听方法 [RCMessageExpansionDelegate messageExpansionDidRemove:message:] 通知的
///
/// 扩展信息只支持单聊和群组，其它会话类型不能设置扩展信息
///
/// - Remark: 高级功能
/// - Since: 5.0.0
- (void)removeMessageExpansionForKey:(NSArray<NSString *> *)keyArray
                          messageUId:(NSString *)messageUId
                             success:(nullable void (^)(void))successBlock
                               error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 设置 IMLibCore 的消息扩展监听器
///
/// 代理回调在非主线程
///
/// - Remark: 高级功能
/// - Since: 5.0.0
@property (nonatomic, weak, nullable) id<RCMessageExpansionDelegate> messageExpansionDelegate;

#pragma mark - 标签
/// 添加标签
///
/// - Parameter tagInfo: 标签信息。只需要设置标签信息的 tagId 和 tagName。
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// 最多支持添加 20 个标签
/// - Remark: 高级功能
/// - Since: 5.1.1
- (void)addTag:(RCTagInfo *)tagInfo
       success:(nullable void (^)(void))successBlock
         error:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 移除标签
///
/// - Parameter tagId: 标签 ID
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// - Remark: 高级功能
/// - Since: 5.1.1
- (void)removeTag:(NSString *)tagId
          success:(nullable void (^)(void))successBlock
            error:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 更新标签信息
///
/// - Parameter tagInfo: 标签信息。只支持修改标签信息的 tagName
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// - Remark: 高级功能
/// - Since: 5.1.1
- (void)updateTag:(RCTagInfo *)tagInfo
          success:(nullable void (^)(void))successBlock
            error:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 获取标签列表
/// - Parameter completion: 异步回调 [标签列表]
///
/// - Remark: 高级功能
/// - Since: 5.3.0
- (void)getTags:(nullable void (^)(NSArray<RCTagInfo *> *))completion;

/// 标签变化监听器
///
/// 标签添加移除更新会触发此监听器，用于多端同步
/// 本端添加删除更新标签，不会触发此监听器，在相关调用方法的 block 块直接回调
///
/// - Remark: 高级功能
/// - Since: 5.1.1
@property (nonatomic, weak, nullable) id<RCTagDelegate> tagDelegate;

/// 添加会话到指定标签
///
/// - Parameter tagId: 标签 ID
/// - Parameter conversationIdentifiers: 会话信息列表
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// 每次添加会话个数最大为 1000。最多支持添加 1000 个会话，如果标签添加的会话总数已超过 1000，会自动覆盖早期添加的会话
/// 会话标签功能仅支持单群聊会话、系统会话
/// - Remark: 高级功能
/// - Since: 5.1.1
- (void)addConversationsToTag:(NSString *)tagId
      conversationIdentifiers:(NSArray<RCConversationIdentifier *> *)conversationIdentifiers
                      success:(nullable void (^)(void))successBlock
                        error:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 从指定标签移除会话
///
/// - Parameter tagId: 标签 ID
/// - Parameter conversationIdentifiers: 会话信息列表
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// 每次移除会话个数最大为 1000
/// 会话标签功能仅支持单群聊会话、系统会话
/// - Remark: 高级功能
/// - Since: 5.1.1
- (void)removeConversationsFromTag:(NSString *)tagId
           conversationIdentifiers:(NSArray<RCConversationIdentifier *> *)conversationIdentifiers
                           success:(nullable void (^)(void))successBlock
                             error:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 从指定会话中移除标签
///
/// - Parameter conversationIdentifier: 会话信息
/// - Parameter tagIds: 标签 ID 列表
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// 会话标签功能仅支持单群聊会话、系统会话
/// - Remark: 高级功能
/// - Since: 5.1.1
- (void)removeTagsFromConversation:(RCConversationIdentifier *)conversationIdentifier
                            tagIds:(NSArray<NSString *> *)tagIds
                           success:(nullable void (^)(void))successBlock
                             error:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 异步获取会话的所有标签
///
/// - Parameter conversationIdentifier: 会话信息
/// - Parameter completion: 异步回调 [会话所属的标签列表]
///
/// 会话标签功能仅支持单群聊会话、系统会话
/// - Remark: 高级功能
/// - Since: 5.3.0
- (void)getTagsFromConversation:(RCConversationIdentifier *)conversationIdentifier
                     completion:(nullable void (^)(NSArray<RCConversationTagInfo *> *_Nullable results))completion;

/// 异步分页获取标签中会话列表
///
/// - Parameter tagId: 标签 ID
/// - Parameter timestamp: 会话的时间戳（获取这个时间戳之前的会话列表，0 表示从最新开始获取，单位：毫秒）
/// - Parameter count: 获取的数量（当实际取回的会话数量小于 count 值时，表明已取完数据）
/// - Parameter completion: 异步回调 [会话 RCConversation 的列表]
///
/// 会话标签功能仅支持单群聊会话、系统会话
/// - Remark: 高级功能
/// - Since: 5.3.0
- (void)getConversationsFromTagByPage:(NSString *)tagId
                            timestamp:(long long)timestamp
                                count:(int)count
                           completion:(nullable void (^)(NSArray<RCConversation *> *_Nullable results))completion;

/// 异步分页获取未打标签的会话列表。
///
/// - Parameter timestamp: 会话的时间戳（获取这个时间戳之前的会话列表，0 表示从最新开始获取，单位：毫秒）。
/// - Parameter count: 获取的数量，有效值 [1, 100]。（当实际取回的会话数量小于 count 值时，表明已取完数据）。
/// - Parameter topPriority: 查询结果的排序方式，是否置顶优先，传 YES 表示置顶会话优先返回，否则结果只以会话时间排序。
/// - Parameter completion: 异步回调 [ 会话 RCConversation 的列表 ]。
///
/// - Note: `count` 小于 1 时，取 20，大于 100 时，取 100。
///
/// - Remark: 高级功能
///
/// - Since: 5.7.8
- (void)getUntaggedConversationListByPage:(long long)timestamp
                                    count:(NSInteger)count
                              topPriority:(BOOL)topPriority
                        completionHandler:
                            (void (^)(NSArray<RCConversation *> *conversations, RCErrorCode code))completionHandler;

/// 异步获取标签中会话消息未读数
///
/// - Parameter tagId: 标签 ID
/// - Parameter isContain: 是否包含免打扰会话
/// - Parameter completion: 异步回调 [会话消息未读数]
///
/// 会话标签功能仅支持单群聊会话、系统会话
/// - Remark: 高级功能
/// - Since: 5.3.0
- (void)getUnreadCountByTag:(NSString *)tagId
             containBlocked:(BOOL)isContain
                 completion:(nullable void (^)(int count))completion;

/// 设置标签中的会话置顶
///
/// - Parameter tagId: 标签 ID
/// - Parameter conversationIdentifier: 会话信息
/// - Parameter top: 是否置顶
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// 会话标签功能仅支持单群聊会话、系统会话
/// - Remark: 高级功能
/// - Since: 5.1.1
- (void)setConversationToTopInTag:(NSString *)tagId
           conversationIdentifier:(RCConversationIdentifier *)conversationIdentifier
                            isTop:(BOOL)top
                          success:(nullable void (^)(void))successBlock
                            error:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 异步获取标签中的会话置顶状态
///
/// - Parameter conversationIdentifier: 会话信息
/// - Parameter tagId: 标签 ID
/// - Parameter completion: 异步回调 [置顶状态]
///
/// 会话标签功能仅支持单群聊会话、系统会话
/// - Remark: 高级功能
/// - Since: 5.3.0
- (void)getConversationTopStatusInTag:(RCConversationIdentifier *)conversationIdentifier
                                tagId:(NSString *)tagId
                           completion:(nullable void (^)(BOOL ret))completion;

/// 异步清除标签对应会话的未读消息数
///
/// - Parameter tagId: 标签 ID
/// - Parameter completion: 异步回调 [是否清除成功]
///
/// 会话标签功能仅支持单群聊会话、系统会话
/// - Remark: 高级功能
/// - Since: 5.3.0
- (void)clearMessagesUnreadStatusByTag:(NSString *)tagId completion:(nullable void (^)(BOOL ret))completion;


/// 删除标签对应的会话
///
/// - Parameter tagId: 标签 ID
/// - Parameter option: 可配置的参数
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// 会话标签功能仅支持单群聊会话、系统会话
/// - Remark: 高级功能
/// - Since: 5.1.5
- (void)clearConversationsByTag:(NSString *)tagId
                         option:(RCClearConversationOption *)option
                        success:(nullable void (^)(void))successBlock
                          error:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 会话标签变化监听器
///
/// 会话标签添加移除更新会触发此监听器，用于多端同步
/// 本端操作会话标签，不会触发此监听器，在相关调用方法的 block 块直接回调
///
/// 此监听器仅支持单群聊会话、系统会话
/// - Remark: 高级功能
/// - Since: 5.1.1
@property (nonatomic, weak, nullable) id<RCConversationTagDelegate> conversationTagDelegate;

/// 缩略图压缩配置
///
/// - Remark: 缩略图压缩配置，如果此处设置了配置就按照这个配置进行压缩。如果此处没有设置，会按照 RCConfig.plist 中的配置进行压缩。
/// - Since: 5.1.1
@property (nonatomic, strong, nullable) RCImageCompressConfig *imageCompressConfig;

/// 子模块是否正在使用声音通道，特指 RTCLib
/// - Since: 5.1.2
- (BOOL)isAudioHolding;

/// 子模块是否正在使用摄像头，特指 RTCLib
/// - Since: 5.1.2
- (BOOL)isCameraHolding;

#pragma mark - socks proxy
/// 在初始化之前设置代理，目前仅支持 socks5 代理
/// 设置 socks 代理
/// - Returns: 代理设置是否成功
/// - Parameter proxy: RCIMProxy 具体的代理配置，为空或者无效则代表为取消代理设置
///
/// 不需认证的代理，只需要设置代理信息的 host 和 port；如需认证还需设置 userName 和 password。
/// 如果需要再次设置代理，那么 app 先要 disconnect 将上次连接给断掉再设置 并且需要设置代理后需要重新调用 connect 接口，SDK 使用新代理连接
///
/// - Warning: 建议开发者在 testProxy 成功后再调用该接口设置代理，以此来保证用户手动输入的代理是正确的
/// //  如果开发者设置错误的 proxy，SDK 也会直接使用，出现问题就是 SDK 连接不上
/// // SDK 的代理设置只保存在内存中，杀死 app 重打开代理就失效了，需要 app 每次启动后重新设置
/// - Remark: 高级功能
/// - Since: 5.3.0

- (BOOL)setProxy:(nullable RCIMProxy *)proxy;

/// 获取当前 socks 代理配置
///
/// - Returns: getCurrentProxy RCIMProxy 具体的代理配置
/// - Remark: 高级功能
/// - Since: 5.3.0

- (nullable RCIMProxy *)getCurrentProxy;

/// 检测代理是否可用，SDK 使用代理参数连接 testHost，检测代理配置是否可用
/// 检测 http 协议的可用性，不支持验证 tcp udp 的有效性验证
///
/// - Parameter proxy: RCIMProxy 具体的代理配置，proxy 必须为有效值，否则返回失败回调
/// - Parameter testHost: NSString 建议设置为 AppServer 的域名，需要 http 头或者 https 头，否则 SDK 会为其拼接 https:// 前缀
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// callback 测试结果，超时时间 5 秒，callback 在非 UI 线程返回
/// - Remark: 高级功能
/// - Since: 5.3.0

- (void)testProxy:(RCIMProxy *)proxy
         testHost:(NSString *)testHost
     successBlock:(nullable void (^)(void))successBlock
       errorBlock:(nullable void (^)(RCErrorCode code))errorBlock;

/// 配置 AppGroupId 与代理
///
/// - Parameter identifier: AppGroupId
/// - Parameter isMainApp: 是否为宿主 app
///
/// 保存 AppGroupId，并设置 APP & NotificationService 的跨进程监听
/// 该方法仅限于推送统计，若无统计需求无需调用
/// 当做推送到达统计时需要同时做到两点
/// 1. 在 push extension 中初始化后先调用该接口，再调用 recordReceivedRemoteNotificationEvent 方法
/// 2. 在主进程中在初始化后调用该接口
///
/// - Since: 5.3.0
- (void)configApplicationGroupIdentifier:(NSString *)identifier isMainApp:(BOOL)isMainApp API_AVAILABLE(ios(10.0));

#pragma mark - 已读回执V4


/// 获取某条消息的已读回执信息
/// - Parameters:
/// - targetId: 会话 ID
/// - channelId: 业务 ID
/// - successBlock: 成功回调
/// - errorBlock: 失败回调
/// - Since: 5.6.7
- (void)getMessageReadReceiptV4:(nonnull NSString *)targetId
                     messageUID:(nonnull NSString *)messageUID
                   successBlock:(nullable void (^)(NSInteger readCount, NSInteger totalCount,
                                                   NSArray<RCGroupMessageReaderV2 *> *list))successBlock
                     errorBlock:(nullable void (^)(RCErrorCode status))errorBlock;


/// 发送消息的已读回执，会将区间内的消息在服务端全部添加已读状态，本地不进行处理。需要 lib 自己调用清除未读等相关接口处理其他业务。
/// - Parameters:
/// - conversationType: 会话类型
/// - targetId: 会话 ID
/// - startMessageUID: 开始的消息 UID
/// - endMessageUID: 结束的消息 UID
/// - successBlock: 成功回调
/// - errorBlock: 失败回调
/// - Since: 5.6.7
- (void)sendReadReceiptMessageV4:(RCConversationType)conversationType
                        targetId:(nonnull NSString *)targetId
                 startMessageUID:(nullable NSString *)startMessageUID
                   endMessageUID:(nonnull NSString *)endMessageUID
                    successBlock:(nullable void (^)(void))successBlock
                      errorBlock:(nullable void (^)(RCErrorCode status))errorBlock;

/// v4 已读回执代理
/// - Parameter delegate: 代理
/// - Since: 5.6.7
- (void)setReadReceiptV4Delegate:(nullable id<RCReadReceiptV4Delegate>)delegate;

/// 已读状态代理 (设置该代理可忽略 RCLibDispatchReadReceiptNotification)
/// - Parameter delegate: 代理
/// - Since: 5.6.7
- (void)setConversationReadStatusDelegate:
    (nullable id<RCConversationChannelSyncConversationReadStatusDelegate>)delegate;

#pragma mark - 订阅事件相关

/// 订阅事件。
/// 当订阅事件的状态发生变化时，将通过回调接口通知调用者。
/// 订阅接口 一次最多订阅 200 个订阅对象，订阅上限查看开发文档
///
/// - Parameter request: 订阅请求对象，包含了需要订阅事件状态的必要信息。
/// request 必须包含（subscribeType、expiry、userIds）
/// - Parameter completion: 结果回调，用于接收订阅操作的结果或状态更新通知。
/// - Since: 5.8.1
- (void)subscribeEvent:(RCSubscribeEventRequest *)request
            completion:(void (^)(RCErrorCode status, NSArray<NSString *> *_Nullable failedUserIds))completion;


/// 取消订阅事件。
///
/// - Parameter request: 取消订阅的请求对象，包含了需要取消订阅事件状态的必要信息。
/// request 必须包含（subscribeType、userIds）
/// - Parameter completion: 结果回调，用于接收取消订阅操作的结果。
/// - Since: 5.8.1
- (void)unSubscribeEvent:(RCSubscribeEventRequest *)request
              completion:(void (^)(RCErrorCode status, NSArray<NSString *> *_Nullable failedUserIds))completion;

/// 查询已订阅事件状态数据。
/// 此方法用于获取指定对象，指定订阅类型的订阅事件状态信息。
///
/// - Parameter request: 查询请求对象，可按订阅类型、指定对象，查询具体订阅事件状态信息。
/// request 必须包含（subscribeType、userIds）
/// - Parameter completion: 查询操作完成后，订阅事件状态的列表通过此回调返回。
/// - Since: 5.8.1
- (void)querySubscribeEvent:(RCSubscribeEventRequest *)request
                 completion:(void (^)(RCErrorCode status,
                                      NSArray<RCSubscribeInfoEvent *> *_Nullable subscribeEvents))completion;

/// 分页查询已订阅的所有事件状态数据。
/// 此方法用于分页获取指定订阅类型的所有订阅事件状态信息。
///
/// - Parameter request: 查询请求对象，可按订阅类型，查询所有具体订阅事件状态信息。
/// request 必须包含（subscribeType）
/// - Parameter pageSize: 分页大小 [1~200]。
/// - Parameter startIndex: 第一页传 0，下一页取返回所有数据的数组数量（比如 pageSize = 20，第二页传 20，第三页传 40）。
/// - Parameter completion: 查询操作完成后，订阅事件状态的列表通过此回调返回。
///
/// ```objc
///@property (nonatomic, strong) NSMutableArray<RCSubscribeInfoEvent *> *subscribeEventList;
///- (void)queryAllSubscribeEventWithStartIndex:(NSInteger)index {
///    RCSubscribeEventRequest *request = [[RCSubscribeEventRequest alloc] init];
///    request.subscribeType = RCSubscribeTypeOnlineStatus;
///    [[RCCoreClient sharedCoreClient] querySubscribeEvent:request pageSize:20 startIndex:index completion:^(RCErrorCode status, NSArray<RCSubscribeInfoEvent *> * _Nullable subscribeEvents) {
///        if (RC_SUCCESS == status && subscribeEvents.count > 0) {
///            [self.subscribeEventList addObjectsFromArray:subscribeEvents];
///            [self queryAllSubscribeEventWithStartIndex:self.subscribeEventList.count];
///        }
///    }];
///}
///
/// ```
///
/// - Since: 5.8.1
- (void)querySubscribeEvent:(RCSubscribeEventRequest *)request
                   pageSize:(NSInteger)pageSize
                 startIndex:(NSInteger)startIndex
                 completion:(nullable void (^)(RCErrorCode status,
                                               NSArray<RCSubscribeInfoEvent *> *_Nullable subscribeEvents))completion;

/// 添加订阅事件监听器。
/// 用于添加一个监听器来接收所有订阅的用户状态变化事件。
///
/// - Parameter delegate: 订阅事件监听器。
/// - Since: 5.8.1
- (void)addSubscribeEventDelegate:(id<RCSubscribeEventDelegate>)delegate NS_SWIFT_NAME(addSubscribeEventDelegate(_:));

/// 移除订阅事件监听器。
///
/// - Parameter delegate: 订阅事件监听器。
/// - Since: 5.8.1
- (void)removeSubscribeEventDelegate:(id<RCSubscribeEventDelegate>)delegate
    NS_SWIFT_NAME(removeSubscribeEventDelegate(_:));

/// 查询已订阅用户的在线状态
/// - Parameters:
///   - userIds: 用户id集合，限制范围在 [0 ~ 200] 超出限制或者长度为0 会报错 34215
///   - completion: 结果回调
/// - Since: 5.28.0
- (void)getSubscribeUsersOnlineStatus:(NSArray<NSString *> *)userIds
                           completion:(void(^)(RCErrorCode code,
                                               NSArray <RCSubscribeUserOnlineStatus *> *status))completion;
#pragma mark - 用户信息托管

/// 设置自己的信息访问权限
///
/// - Parameter visibility: 用户信息的访问权限
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// - Since: 5.10.0
- (void)updateMyUserProfileVisibility:(RCUserProfileVisibility)visibility
                              success:(nullable void (^)(void))successBlock
                                error:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 获取自己的信息访问权限
///
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// - Since: 5.10.0
- (void)getMyUserProfileVisibility:(nullable void (^)(RCUserProfileVisibility visibility))successBlock
                             error:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 修改自己的用户信息
///
/// - Parameter profile: 用户信息
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// - Since: 5.16.0
- (void)updateMyUserProfile:(RCUserProfile *)profile
               successBlock:(nullable void (^)(void))successBlock
                 errorBlock:
                     (nullable void (^)(RCErrorCode errorCode, NSArray<NSString *> *_Nullable errorKeys))errorBlock;

/// 查询自己的用户信息
///
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// - Since: 5.10.0
- (void)getMyUserProfile:(nullable void (^)(RCUserProfile *userProfile))successBlock
                   error:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 批量获取用户信息
///
/// - Parameter userIds: 用户 ID 列表
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// - Since: 5.10.0
- (void)getUserProfiles:(NSArray<NSString *> *)userIds
                success:(nullable void (^)(NSArray<RCUserProfile *> *userProfiles))successBlock
                  error:(nullable void (^)(RCErrorCode errorCode))errorBlock;


/// 按用户应用号精确搜索
///
/// - Parameter uniqueId: 用户应用号
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调，如果搜不到用户，会返回错误码 RC_USER_PROFILE_USER_NOT_EXIST (24366)
///
/// - Since: 5.10.0
- (void)searchUserProfileByUniqueId:(NSString *)uniqueId
                            success:(nullable void (^)(RCUserProfile *userProfile))successBlock
                              error:(nullable void (^)(RCErrorCode errorCode))errorBlock;

#pragma mark - 数据库

/// 添加数据库状态监听器（连接前调用）
///
/// - Parameter delegate: 添加数据库状态监听器。
/// - Since: 5.10.4
- (void)addDatabaseStatusDelegate:(id<RCDatabaseStatusDelegate>)delegate NS_SWIFT_NAME(addDatabaseStatusDelegate(_:));

/// 移除数据库状态监听器
///
/// - Parameter delegate: 数据库状态监听器。
/// - Since: 5.10.4
- (void)removeDatabaseStatusDelegate:(id<RCDatabaseStatusDelegate>)delegate
    NS_SWIFT_NAME(removeDatabaseStatusDelegate(_:));

#pragma mark - Group

/// 添加群组事件回调代理
/// - Since: 5.12.0
- (void)addGroupEventDelegate:(id<RCGroupEventDelegate>)delegate NS_SWIFT_NAME(addGroupEventDelegate(_:));

/// 移除群组事件回调代理
/// - Since: 5.12.0
- (void)removeGroupEventDelegate:(id<RCGroupEventDelegate>)delegate NS_SWIFT_NAME(removeGroupEventDelegate(_:));

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
/// - Since: 5.16.0
- (void)createGroup:(RCGroupInfo *)groupInfo
     inviteeUserIds:(nullable NSArray<NSString *> *)inviteeUserIds
       successBlock:(void (^)(RCErrorCode processCode))successBlock
         errorBlock:(void (^)(RCErrorCode errorCode, NSArray<NSString *> *_Nullable errorKeys))errorBlock;


/// 更新群组信息
/// - Parameter groupInfo: 群组信息，groupId 必填，否则更新失败
/// - Parameter success: 成功回调
/// - Parameter error: 失败回调
///
/// - Since: 5.16.0
- (void)updateGroupInfo:(RCGroupInfo *)groupInfo
           successBlock:(void (^)(void))successBlock
             errorBlock:(void (^)(RCErrorCode errorCode, NSArray<NSString *> *_Nullable errorKeys))errorBlock
    NS_SWIFT_NAME(updateGroupInfo(_:successBlock:errorBlock:));

/// 批量获取群组资料
/// - Parameter groupIds: 群组 ID 列表，一次最多允许 20 个群组
/// - Parameter success: 成功回调
/// - Parameter error: 失败回调
///
/// - Note: 每秒钟最多查询 5 次
/// - Since: 5.12.0
- (void)getGroupsInfo:(NSArray<NSString *> *)groupIds
              success:(void (^)(NSArray<RCGroupInfo *> *groupInfos))successBlock
                error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 踢出群成员
/// - Parameter groupId: 群组 ID
/// - Parameter userIds: 用户 ID 列表，一次最多允许 100 个用户
/// - Parameter config: 移除成员配置
/// - Parameter success: 成功回调
/// - Parameter error: 失败回调
///
/// - Since: 5.12.0
- (void)kickGroupMembers:(NSString *)groupId
                 userIds:(NSArray<NSString *> *)userIds
                  config:(nullable RCQuitGroupConfig *)config
                 success:(void (^)(void))successBlock
                   error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 主动退出群组
/// 用户退出后，群会话信息仍然保留，但不再能接收此群的消息，本地历史消息不删除
/// - Parameter groupId: 群组 ID
/// - Parameter config: 退出群组配置
/// - Parameter success: 成功回调
/// - Parameter error: 失败回调
///
/// - Since: 5.12.0
- (void)quitGroup:(NSString *)groupId
           config:(nullable RCQuitGroupConfig *)config
          success:(void (^)(void))successBlock
            error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 解散群组
/// 只有群主，可以解散自已创建的群组
/// - Parameter groupId: 群组 ID，必填项
/// - Parameter success: 成功回调，无参数
/// - Parameter error: 失败回调，包含错误信息
///
/// - Since: 5.12.0
- (void)dismissGroup:(NSString *)groupId
             success:(void (^)(void))successBlock
               error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 转让群组
/// - Parameter groupId: 群组 ID
/// - Parameter newOwnerId: 新群主用户 ID
/// - Parameter quitGroup: 是否退出群组
/// - Parameter config: 转让群组配置
/// - Parameter success: 成功回调
/// - Parameter error: 失败回调
///
/// - Since: 5.12.0
- (void)transferGroupOwner:(NSString *)groupId
                newOwnerId:(NSString *)newOwnerId
                 quitGroup:(BOOL)quitGroup
                    config:(nullable RCQuitGroupConfig *)config
                   success:(void (^)(void))successBlock
                     error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 添加群管理员
/// - Parameter groupId: 群组 ID，必填项
/// - Parameter userIds: 用户 ID 数组，必填项。用户 ID 必须为群成员，一次最多设置 10 个群成员为管理员，管理员上限为 10 个。群主不支持设置为管理员
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调，包含错误信息
///
/// - Since: 5.12.0
- (void)addGroupManagers:(NSString *)groupId
                 userIds:(NSArray<NSString *> *)userIds
                 success:(void (^)(void))successBlock
                   error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 移除群管理员
/// - Parameter groupId: 群组 ID，必填项
/// - Parameter userIds: 用户 ID 数组，必填项。一次最多操作 10 个管理员
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调，包含错误信息
///
/// - Since: 5.12.0
- (void)removeGroupManagers:(NSString *)groupId
                    userIds:(NSArray<NSString *> *)userIds
                    success:(void (^)(void))successBlock
                      error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 分页获取群成员信息
/// - Parameter groupId: 群组 ID
/// - Parameter role: 群成员角色
/// - Parameter option: 查询选项，包含 页面标识（非必填，不填返回第一页数据）、每页条数（最大不超过 100 条）、是否正序查询（默认按加入群组时间倒序）
/// - Parameter successBlock: 成功回调，此接口不返回分页数据的总条数
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)getGroupMembersByRole:(NSString *)groupId
                         role:(RCGroupMemberRole)role
                       option:(RCPagingQueryOption *)option
                      success:(void (^)(RCPagingQueryResult<RCGroupMemberInfo *> *result))successBlock
                        error:(void (^)(RCErrorCode errorCode))errorBlock
    NS_SWIFT_NAME(getGroupMembersByRole(_:role:option:success:error:));


/// 获取已加入指定群成员信息
/// - Parameter groupId: 群组 ID
/// - Parameter userIds: 用户 ID 列表，一次最多不超过 100 个
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)getGroupMembers:(NSString *)groupId
                userIds:(NSArray<NSString *> *)userIds
                success:(void (^)(NSArray<RCGroupMemberInfo *> *groupMembers))successBlock
                  error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 设置群成员资料
/// - Parameter groupId: 群组 ID
/// - Parameter userId: 用户 ID，必填项，支持传入当前登录用户 ID
/// - Parameter nickname: 用户昵称，非必填项，长度不超过 64 个字符，传 nil 或 空字符串表示移除用户昵称
/// - Parameter extra: 附加信息，非必填项，长度不超过 128 个字符
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.16.0
- (void)setGroupMemberInfo:(NSString *)groupId
                    userId:(NSString *)userId
                  nickname:(nullable NSString *)nickname
                     extra:(nullable NSString *)extra
              successBlock:(void (^)(void))successBlock
                errorBlock:(void (^)(RCErrorCode errorCode, NSArray<NSString *> *_Nullable errorKeys))errorBlock;

/// 根据群成员昵称查询群成员
/// - Parameter groupId: 群组 ID
/// - Parameter name: 群成员昵称，必填，不能为空最长不超过 64 个字符。
/// - Parameter option: 查询选项，包含 页面标识（非必填，不填返回第一页数据）、每页条数（最大不超过 200 条）、是否正序查询（默认倒序）
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
/// - Note: 优先匹配群成员昵称 nickname，再匹配群成员用户名 name。只要其中一个字段匹配成功，即返回搜索结果。
/// - Since: 5.12.0
- (void)searchGroupMembers:(NSString *)groupId
                      name:(NSString *)name
                    option:(RCPagingQueryOption *)option
                   success:(void (^)(RCPagingQueryResult<RCGroupMemberInfo *> *result))successBlock
                     error:(void (^)(RCErrorCode errorCode))errorBlock;


/// 主动加入群组
/// - Parameter groupId: 群组 ID
/// - Parameter successBlock: 成功回调。
/// - Parameter errorBlock: 失败回调
/// - Note:
///
/// **`successBlock` 的 `processCode` 参数说明**
/// - 当群组的 `joinPermission` 为需要群主或管理员审批时，`processCode` 返回 `RC_GROUP_JOIN_GROUP_NEED_MANAGER_ACCEPT` ( 25424 )，表示需要等待群主或管理员的审批。
/// - 当群组的 `joinPermission` 为不用验证时，`processCode` 返回 RC_SUCCESS ( 0 )，表示加入群组成功。
/// - Since: 5.12.0
- (void)joinGroup:(NSString *)groupId
          success:(void (^)(RCErrorCode processCode))successBlock
            error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 邀请用户加入群组
/// - Parameter groupId: 群组 ID
/// - Parameter userIds: 用户 ID 列表，一次最多不超过 30 个
/// - Parameter successBlock: 邀请成功回调
/// - Parameter errorBlock: 失败回调
/// - Note:
///
/// **`successBlock` 的 `processCode` 参数说明**
/// - 当群组的 `joinPermission`  为需要群主或管理员审批时，`processCode` 返回 `RC_GROUP_JOIN_GROUP_NEED_MANAGER_ACCEPT` ( 25424 )，表示需要等待群主或管理员审批。
/// - 当群组的 `joinPermission` 为不用验证，同时 `inviteHandlePermission` 为需要被邀请人同意时，`processCode` 返回 `RC_GROUP_NEED_INVITEE_ACCEPT` ( 25427 )，表示需要被邀请人同意后才能进入群组。
/// - Since: 5.12.0
- (void)inviteUsersToGroup:(NSString *)groupId
                   userIds:(NSArray<NSString *> *)userIds
                   success:(void (^)(RCErrorCode processCode))successBlock
                     error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 用户同意加入群组
/// - Parameter groupId: 群组 ID
/// - Parameter inviterId: 邀请者 ID
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)acceptGroupInvite:(NSString *)groupId
                inviterId:(NSString *)inviterId
                  success:(void (^)(void))successBlock
                    error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 用户拒绝加入群组
/// - Parameter groupId: 群组 ID
/// - Parameter inviterId: 邀请者 ID
/// - Parameter reason: 拒绝原因，非必填项，拒绝时可选择是否输入拒绝原因，内容不超过 128 个字符。
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)refuseGroupInvite:(NSString *)groupId
                inviterId:(NSString *)inviterId
                   reason:(nullable NSString *)reason
                  success:(void (^)(void))successBlock
                    error:(void (^)(RCErrorCode errorCode))errorBlock;


/// 群主或管理员同意用户加入群组
/// - Parameter groupId: 群组 ID
/// - Parameter inviterId: 邀请人用户 ID，非必填，如果是邀请入群，则传邀请人 ID；如果是用户主动加群，可以为空。
/// - Parameter applicantId: 申请入群用户 ID
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
/// - Note:
///
/// **`successBlock` 的 `processCode` 参数说明**
///
/// - 当群组的 `inviteHandlePermission` 为需要被邀请人同意时，若 `processCode` 返回 `RC_GROUP_NEED_INVITEE_ACCEPT` (25427)，表示需等待被邀请人同意方可加入群组。
/// - 当群组的 `inviteHandlePermission` 为无需被邀请人同意时，若 `processCode` 返回 `RC_SUCCESS` (0)，表示被邀请人已成功加入群组。
///
///  以上仅适用于邀请加入群组的情况，当用户主动申请加入群组时，`processCode` 始终为 `RC_SUCCESS` (0)。
/// - Since: 5.12.0
- (void)acceptGroupApplication:(NSString *)groupId
                     inviterId:(nullable NSString *)inviterId
                   applicantId:(NSString *)applicantId
                       success:(void (^)(RCErrorCode processCode))successBlock
                         error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 群主或管理员拒绝用户加入群组
/// - Parameter groupId: 群组 ID
/// - Parameter inviterId: 邀请人用户 ID，非必填，如果是邀请入群，则传邀请人 ID；如果是主动加群，可以为空。
/// - Parameter applicantId: 申请者 ID
/// - Parameter reason: 拒绝原因，内容不超过 128 个字符。
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)refuseGroupApplication:(NSString *)groupId
                     inviterId:(nullable NSString *)inviterId
                   applicantId:(NSString *)applicantId
                        reason:(nullable NSString *)reason
                       success:(void (^)(void))successBlock
                         error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 分页获取群组申请列表
/// - Parameter option: 查询选项，包含 页面标识（非必填，不填返回第一页数据）、每页条数（最大不超过 200 条）、是否正序查询（默认倒序）
/// - Parameter directions: 申请方向 `RCGroupApplicationDirection` 数组
/// - Parameter status: 状态类型 `RCGroupApplicationStatus` 数组
/// - Parameter successBlock: 成功回调，此接口不支持返回请求总数。
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)getGroupApplications:(RCPagingQueryOption *)option
                  directions:(NSArray<NSNumber *> *)directions
                      status:(NSArray<NSNumber *> *)status
                     success:(void (^)(RCPagingQueryResult<RCGroupApplicationInfo *> *result))successBlock
                       error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 按角色获取已加入群组的资料
/// - Parameter role: 群成员角色
/// - Parameter option: 查询选项，包含 页面标识（非必填，不填返回第一页数据）、每页条数（最大不超过 100 条）、是否正序查询（默认倒序）
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)getJoinedGroupsByRole:(RCGroupMemberRole)role
                       option:(RCPagingQueryOption *)option
                      success:(void (^)(RCPagingQueryResult<RCGroupInfo *> *result))successBlock
                        error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 按群名称搜索已加入群组的资料
/// - Parameter groupName: 群名称，不能为空最长不超过 64 个字符
/// - Parameter option: 查询选项，包含 页面标识（非必填，不填返回第一页数据）、每页条数（最大不超过 200 条）、是否正序查询（默认倒序）
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)searchJoinedGroups:(NSString *)groupName
                    option:(RCPagingQueryOption *)option
                   success:(void (^)(RCPagingQueryResult<RCGroupInfo *> *result))successBlock
                     error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 获取指定已加入群组的资料
/// - Parameter groupIds: 群 ID 列表，一次最多查询 20 个群组
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)getJoinedGroups:(NSArray<NSString *> *)groupIds
                success:(void (^)(NSArray<RCGroupInfo *> *groupInfos))successBlock
                  error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 设置群组备注名
/// - Parameter groupId: 群组 ID
/// - Parameter remark: 群备注，字符串长度不超过 64 个字符。传 nil 或 空字符串 表示移除群备注
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)setGroupRemark:(NSString *)groupId
                remark:(nullable NSString *)remark
               success:(void (^)(void))successBlock
                 error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 添加群组特别关注用户
/// - Parameter groupId: 群组 ID
/// - Parameter userIds: 用户 ID 列表，单次最多关注 100 个用户
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)addGroupFollows:(NSString *)groupId
                userIds:(NSArray<NSString *> *)userIds
                success:(void (^)(void))successBlock
                  error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 删除群组特别关注用户
/// - Parameter groupId: 群组 ID
/// - Parameter userIds: 用户 ID 列表，单次取消关注 100 个用户
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)removeGroupFollows:(NSString *)groupId
                   userIds:(NSArray<NSString *> *)userIds
                   success:(void (^)(void))successBlock
                     error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 获取群组特别关注用户
/// - Parameter groupId: 群组 ID
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)getGroupFollows:(NSString *)groupId
                success:(void (^)(NSArray<RCFollowInfo *> *followInfos))successBlock
                  error:(void (^)(RCErrorCode errorCode))errorBlock;


#pragma mark - Friend

/// 添加好友事件监听
/// - Since: 5.12.0
- (void)addFriendEventDelegate:(id<RCFriendEventDelegate>)delegate NS_SWIFT_NAME(addFriendEventDelegate(_:));

/// 移除好友事件监听
/// - Since: 5.12.0
- (void)removeFriendEventDelegate:(id<RCFriendEventDelegate>)delegate NS_SWIFT_NAME(removeFriendEventDelegate(_:));

/// 添加好友
/// - Parameter userId: 用户 ID
/// - Parameter directionType: 好友方向类型
/// - Parameter extra: 发送好友请求时的附加信息，长度不超过 128 个字符。
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Note:
///
/// **`successBlock` 的 `processCode` 参数说明**
/// - 当对方添加好友权限为需要同意才能添加好友时，`processCode` 返回 `RC_FRIEND_NEED_ACCEPT` ( 25461 )，表示对方需要同意之后才能添加为好友。
/// - 当对方添加好友权限为不需要同意时，`processCode` 返回 `RC_SUCCESS` ( 0 )，好友直接添加成功。
/// - Since: 5.12.0
- (void)addFriend:(NSString *)userId
    directionType:(RCDirectionType)directionType
            extra:(nullable NSString *)extra
          success:(void (^)(RCErrorCode processCode))successBlock
            error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 删除好友
/// - Parameter userIds: 用户 ID 列表，一次最多解除 100 个用户
/// - Parameter directionType: 好友方向类型
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)deleteFriends:(NSArray<NSString *> *)userIds
        directionType:(RCDirectionType)directionType
              success:(void (^)(void))successBlock
                error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 同意加为好友
/// - Parameter userId: 用户 ID
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)acceptFriendApplication:(NSString *)userId
                        success:(void (^)(void))successBlock
                          error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 拒绝加为好友
/// - Parameter userId: 用户 ID
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)refuseFriendApplication:(NSString *)userId
                        success:(void (^)(void))successBlock
                          error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 好友信息设置
/// - Parameter userId: 用户 ID
/// - Parameter remark: 好友备注，最多为 64 个字符，不传或为空时清除备注名。
/// - Parameter extProfile: 扩展信息
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.16.0
- (void)setFriendInfo:(NSString *)userId
               remark:(nullable NSString *)remark
           extProfile:(nullable NSDictionary<NSString *, NSString *> *)extProfile
         successBlock:(void (^)(void))successBlock
           errorBlock:(void (^)(RCErrorCode errorCode, NSArray<NSString *> *_Nullable errorKeys))errorBlock;

/// 检查好友关系
/// - Parameter userIds: 用户 ID 列表，一次最多查询 100 个用户
/// - Parameter directionType: 好友方向类型，目前只支持双向检查
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)checkFriends:(NSArray<NSString *> *)userIds
       directionType:(RCDirectionType)directionType
             success:(void (^)(NSArray<RCFriendRelationInfo *> *friendRelations))successBlock
               error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 获取好友列表
/// - Parameter directionType: 好友方向类型
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)getFriends:(RCQueryFriendsDirectionType)directionType
           success:(void (^)(NSArray<RCFriendInfo *> *friendInfos))successBlock
             error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 分页获取好友请求列表
/// - Parameter option: 查询选项，包含 页面标识（非必填，不填返回第一页数据）、每页条数（最大不超过 100 条）、是否正序查询（默认倒序）
/// - Parameter types: 请求类型数组 RCFriendApplicationType
/// - Parameter status: 申请状态数组 RCFriendApplicationStatus
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)getFriendApplications:(RCPagingQueryOption *)option
                        types:(NSArray<NSNumber *> *)types
                       status:(NSArray<NSNumber *> *)status
                      success:(void (^)(RCPagingQueryResult<RCFriendApplicationInfo *> *result))successBlock
                        error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 根据用户 ID 获取好友信息
/// - Parameter userIds: 用户 ID 列表，一次最多获取 100 个好友信息
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)getFriendsInfo:(NSArray<NSString *> *)userIds
               success:(void (^)(NSArray<RCFriendInfo *> *friendInfos))successBlock
                 error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 根据好友昵称搜索好友信息
/// - Parameter name: 用户昵称，不能为空最长不超过 64 个字符
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
/// - Note: 默认先匹配好友备注名 remark，再匹配好友名称 name。只要其中一个字段匹配成功，即返回搜索结果。
/// - Since: 5.12.0
- (void)searchFriendsInfo:(NSString *)name
                  success:(void (^)(NSArray<RCFriendInfo *> *friendInfos))successBlock
                    error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 设置加好友权限
/// - Parameter permission: 加好友权限
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)setFriendAddPermission:(RCFriendAddPermission)permission
                       success:(void (^)(void))successBlock
                         error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 获取加好友权限
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.0
- (void)getFriendAddPermission:(void (^)(RCFriendAddPermission permission))successBlock
                         error:(void (^)(RCErrorCode errorCode))errorBlock;

#pragma mark - Stream

/// 添加流式消息请求事件监听。
/// - Since: 5.16.0
- (void)addStreamMessageRequestEventDelegate:(id<RCStreamMessageRequestEventDelegate>)delegate
    NS_SWIFT_NAME(addStreamMessageRequestEventDelegate(_:));

/// 移除流式消息请求事件监听。
/// - Since: 5.16.0
- (void)removeStreamMessageRequestEventDelegate:(id<RCStreamMessageRequestEventDelegate>)delegate
    NS_SWIFT_NAME(removeStreamMessageRequestEventDelegate(_:));

/// 请求流式消息。
/// 请求事件会在 RCStreamMessageRequestEventDelegate 代理中回调。
///
/// - Parameters:
///   - params: 请求参数对象。
///   - completionHandler: 发起请求结果回调。流式消息的接收回调在 `RCStreamMessageRequestEventDelegate` 中。
///
/// - Since: 5.16.0
- (void)requestStreamMessageWithParams:(RCStreamMessageRequestParams *)params
                     completionHandler:(void (^)(RCErrorCode code))completionHandler;



/// 保存撤回消息编辑草稿
/// @param draft 详见 RCEditedMessageDraft 定义
/// @param identifier - identifier.type 只允许单聊，群聊，超级群，identifier.targetId 必填参数，identifier.channeld 非必填
/// @param completion 结果回调
///
/// - Since 5.28.0
- (void)saveEditedMessageDraft:(nullable RCEditedMessageDraft *)draft
                    identifier:(RCConversationIdentifier *)identifier
                    completion:(void(^)(RCErrorCode code))completion;

/// 获取撤回消息编辑草稿
/// @param identifier identifier.type 只允许单聊，群聊，超级群，identifier.targetId 必填参数，identifier.channeld 非必填
/// @param completion 结果回调
///
/// - Since 5.28.0
- (void)getEditedMessageDraft:(RCConversationIdentifier *)identifier
                   completion:(void(^)(RCErrorCode code, RCEditedMessageDraft * _Nullable draft))completion;

/// 清除撤回消息编辑草稿
/// @param identifier identifier.type 只允许单聊，群聊，超级群，identifier.targetId 必填参数，identifier.channeld 非必填
/// @param completion 结果回调
///
/// - Since 5.28.0
- (void)clearEditedMessageDraft:(RCConversationIdentifier *)identifier
                     completion:(void(^)(RCErrorCode code))completion;
@end

@protocol RCReadReceiptV5Delegate;

@interface RCCoreClient (ReadReceiptV5)

/// 发送已读回执（V5）。
///
/// - Parameters:
///   - identifier: 会话标识。
///   - messageUIds: 消息唯一 Id 列表，最多 100 条。
///   - completion: 结果回调。
///
/// - Note:
///     消息中 `needReceipt` 为 YES 时，接收方调用本接口，通知消息发送方已读。
///     消息发送方会收到 `didReceiveMessageReadReceiptInfo:` 回调。
///
/// - Warning:
///     `identifier` 只支持单群聊，`messageUIds` 必须是会话中的消息。
///
/// - Since: 5.20.0
- (void)sendReadReceiptResponseV5:(RCConversationIdentifier *)identifier
                      messageUIds:(NSArray<NSString *> *)messageUIds
                       completion:(nullable void (^)(RCErrorCode code))completion;

/// 批量获取已发送消息回执信息。
///
/// - Parameters:
///   - identifier: 会话标识。
///   - messageUIds: 消息唯一 ID 数组，最多 100 条。
///   - completion: 结果回调。
///
/// - Warning:
///     `identifier` 只支持单群聊，`messageUIds` 必须是会话中的消息。
///
/// - Since: 5.20.0
- (void)getMessageReadReceiptInfoV5:(RCConversationIdentifier *)identifier
                        messageUIds:(NSArray<NSString *> *)messageUIds
                         completion:(RCReadReceiptInfoListCompletion)completion;

/// 批量获取已发送消息回执信息。
///
/// - Parameters:
///   - identifiers: 消息标识数组，最多 100 个。
///   - completion: 结果回调。
///
/// - Since: 5.20.2
- (void)getMessageReadReceiptInfoV5ByIdentifiers:(NSArray<RCMessageIdentifier *> *)identifiers
                                      completion:(RCReadReceiptInfoListCompletion)completion;

/// 分页查询已读回执用户列表。
///
/// - Parameters:
///   - identifier: 会话标识。
///   - messageUId: 消息唯一 ID。
///   - option: 查询条件。
///   - completion: 结果回调。
///
/// - Warning:
///     `identifier` 只支持单群聊，`messageUId` 必须是会话中的消息。
///
/// - Since: 5.20.0
- (void)getMessagesReadReceiptUsersByPageV5:(RCConversationIdentifier *)identifier
                                 messageUId:(NSString *)messageUId
                                     option:(RCReadReceiptUsersOption *)option
                                 completion:(RCReadReceiptUserListCompletion)completion;

/// 查询指定的用户列表已读回执状态。
///
/// - Parameters:
///   - identifier: 会话标识。
///   - messageUId: 消息唯一 ID。
///   - userIds: 用户 Id 数组，最多 100 个用户。
///   - completion: 结果回调。
///
/// - Warning:
///     `identifier` 只支持单群聊，`messageUId` 必须是会话中的消息。
///
/// - Since: 5.20.0
- (void)getMessagesReadReceiptByUsersV5:(RCConversationIdentifier *)identifier
                             messageUId:(NSString *)messageUId
                                userIds:(NSArray<NSString *> *)userIds
                             completion:(RCReadReceiptUserListCompletion)completion;

/// 添加已读回执 V5 事件监听。
///
/// - Parameter delegate: 事件代理。
///
/// - Since: 5.20.0
- (void)addReadReceiptV5Delegate:(id<RCReadReceiptV5Delegate>)delegate NS_SWIFT_NAME(addReadReceiptV5Delegate(_:));

/// 移除已读回执 V5 事件监听。
///
/// - Parameter delegate: 事件代理。
///
/// - Since: 5.20.0
- (void)removeReadReceiptV5Delegate:(id<RCReadReceiptV5Delegate>)delegate
    NS_SWIFT_NAME(removeReadReceiptV5Delegate(_:));

@end

@protocol RCSpeechToTextDelegate;

/// 语音转文字。
///
/// - Since: 5.22.0
@interface RCCoreClient (STT)

/// 发起语音转换文本请求。
///
/// - Parameter messageUId: 消息唯一 ID。
/// - Parameter completionHandler: 结果回调。
///
/// - Note: `completionHandler` 是发起请求的结果回调，转换完成的结果会通过全局代理 `RCSpeechToTextDelegate` 回调。
///
/// - Since: 5.22.0
- (void)requestSpeechToTextForMessage:(NSString *)messageUId
                    completionHandler:(nullable void (^)(RCErrorCode code))completionHandler;

/// 设置语音转换文本功能的可见性。
///
/// - Parameters:
///   - messageId: 消息本地 ID。
///   - isVisible: 是否可见。
///   - completionHandler: 结果回调。
///
/// - Note: 可见状态会同步到本地数据库。
///
/// - Since: 5.20.0
- (void)setMessageSpeechToTextVisible:(NSUInteger)messageId
                            isVisible:(BOOL)isVisible
                    completionHandler:(nullable void (^)(RCErrorCode code))completionHandler;

/// 添加语音转文本代理。
///
/// - Parameter delegate: 代理。
///
/// - Since: 5.20.0
- (void)addSpeechToTextDelegate:(id<RCSpeechToTextDelegate>)delegate NS_SWIFT_NAME(addSpeechToTextDelegate(_:));

/// 移除语音转文本代理。
///
/// - Parameter delegate: 代理。
///
/// - Since: 5.20.0
- (void)removeSpeechToTextDelegate:(id<RCSpeechToTextDelegate>)delegate NS_SWIFT_NAME(removeSpeechToTextDelegate(_:));

@end

@class RCTranslateMessagesParams;
@class RCTranslateTextsParams;
@protocol RCTranslationDelegate;

@interface RCCoreClient (Translate)

/// 批量翻译文本消息。
///
/// - Parameters:
///   - params: 翻译的消息参数。
///   - completionHandler: 结果回调。
///
/// - Since: 5.24.0
- (void)translateMessagesWithParams:(RCTranslateMessagesParams *)params
                  completionHandler:(nullable void (^)(RCErrorCode code))completionHandler;

/// 批量翻译文本内容。
///
/// - Parameters:
///   - params: 翻译的文本参数。
///   - completionHandler: 结果回调。
///
/// - Since: 5.24.0
- (void)translateTextsWithParams:(RCTranslateTextsParams *)params
               completionHandler:(nullable void (^)(RCErrorCode code))completionHandler;

/// 设置用户级别的翻译语言。
///
/// - Parameters:
///   - language: 语言。
///   - completionHandler: 结果回调。
///
/// - Note: 设置的 `language`，请使用开发者文档中支持的语言设置。
///
/// - Since: 5.24.0
- (void)setTranslationLanguage:(NSString *)language completionHandler:(void (^)(RCErrorCode code))completionHandler;

/// 获取用户级别的翻译语言。
///
/// - Parameters:
///   - successBlock: 成功回调。
///   - errorBlock: 失败回调。
///
/// - Since: 5.24.0
- (void)getTranslationLanguage:(nullable void (^)(NSString *language))successBlock
                    errorBlock:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 设置用户级别的自动翻译是否开启。
///
/// - Parameters:
///   - isEnable: 是否自动翻译。
///   - completionHandler: 结果回调。
///
/// - Since: 5.24.0
- (void)setAutoTranslateState:(BOOL)isEnable completionHandler:(void (^)(RCErrorCode code))completionHandler;

/// 获取用户级别的自动翻译是否开启。
///
/// - Parameters:
///   - successBlock: 成功回调。
///   - errorBlock: 失败回调。
///
/// - Since: 5.24.0
- (void)getAutoTranslateEnabled:(nullable void (^)(BOOL isEnable))successBlock
                     errorBlock:(nullable void (^)(RCErrorCode errorCode))errorBlock;

/// 批量设置会话翻译策略。
///
/// - Parameters:
///   - identifiers: 会话列表。
///   - strategy: 翻译策略。
///   - completionHandler: 结果回调。
///
/// - Since: 5.24.0
- (void)batchSetConversationTranslateStrategy:(NSArray<RCConversationIdentifier *> *)identifiers
                                     strategy:(RCTranslateStrategy)strategy
                            completionHandler:(void (^)(RCErrorCode code))completionHandler;

/// 添加翻译事件代理。
///
/// - Parameter delegate: 代理。
///
/// - Since: 5.24.0
- (void)addTranslationDelegate:(id<RCTranslationDelegate>)delegate NS_SWIFT_NAME(addTranslationDelegate(_:));

/// 移除翻译事件代理。
///
/// - Parameter delegate: 代理。
///
/// - Since: 5.24.0
- (void)removeTranslationDelegate:(id<RCTranslationDelegate>)delegate NS_SWIFT_NAME(removeTranslationDelegate(_:));

@end

#pragma mark - Settings -

@class RCAppSettings;

/// 设置相关。
@interface RCCoreClient (Settings)

/// 连接成功后，AppKey 对应的配置。
///
/// - Since: 5.22.0
- (nullable RCAppSettings *)getAppSettings;

/// 添加用户配置事件代理。
///
/// - Parameter delegate: 代理。
///
/// - Since: 5.7.8
- (void)addUserSettingsDelegate:(id<RCUserSettingsDelegate>)delegate NS_SWIFT_NAME(addUserSettingsDelegate(_:));

/// 移除用户配置事件代理。
///
/// - Parameter delegate: 代理。
///
/// - Since: 5.7.8
- (void)removeUserSettingsDelegate:(id<RCUserSettingsDelegate>)delegate NS_SWIFT_NAME(removeUserSettingsDelegate(_:));

@end

@class RCMessageResult;
@class RCModifyMessageParams;
@class RCRefreshReferenceMessageParams;

/// 消息编辑。
///
/// - Since: 5.26.0
@interface RCCoreClient (RCMessageModify)

/// 消息修改。
///
/// - Parameters:
///   - params: 消息修改参数对象。
///   - completionHandler: 回调结果。
- (void)modifyMessageWithParams:(RCModifyMessageParams *)params
              completionHandler:(void (^)(RCMessage *message, RCErrorCode code))completionHandler;

/// 批量查询需要刷新的引用消息。
///
/// - Parameter params: 刷新引用消息参数对象。
/// - Parameter localMessageBlock: 获取到的本地消息回调。
/// - Parameter remoteMessageBlock: 获取到的远端消息回调。
/// - Parameter errorBlock: 错误回调。
///
/// - Note:
///     通过 `params.messageUIds` 获取的消息分为两部分：
///     1. 先从本地查找消息，查询到之后，将结果通过 `localMessageBlock` 回调返回。
///     2. 本地没有查到的消息，会从服务器查询，并将结果通过 `remoteMessageBlock` 回调返回。
- (void)refreshReferenceMessageWithParams:(RCRefreshReferenceMessageParams *)params
                        localMessageBlock:(void (^)(NSArray<RCMessageResult *> *results))localMessageBlock
                       remoteMessageBlock:(void (^)(NSArray<RCMessageResult *> *results))remoteMessageBlock
                               errorBlock:(void (^)(RCErrorCode code))errorBlock;

@end

NS_ASSUME_NONNULL_END

#endif
