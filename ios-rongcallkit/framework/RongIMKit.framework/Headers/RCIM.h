//
//  RCIM.h
//  RongIMKit
//
//  Created by xugang on 15/1/13.
//  Copyright (c) 2015年 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RongIMLibCore.h>

@class RCDiscussion,RCPublicServiceProfile;

NS_ASSUME_NONNULL_BEGIN

/// 收到消息的 Notification
/// 
/// 接收到消息后，SDK会分发此通知。
/// 
/// Notification中：
/// - object 为 `RCMessage` 消息对象。
/// - userInfo 为 NSDictionary 对象，其中 key 值为 @"left"，value 为还剩余未接收的消息数的 NSNumber 对象。
/// 
/// 与RCIMReceiveMessageDelegate的区别:
/// RCKitDispatchMessageNotification只要注册都可以收到通知；RCIMReceiveMessageDelegate需要设置监听，并同时只能存在一个监听。
FOUNDATION_EXPORT NSString *const RCKitDispatchMessageNotification;

/// 消息被撤回的Notification
/// 
/// 消息被撤回后，SDK会分发此通知。
/// 
/// Notification 的 object 为 NSNumber 的 messageId。
/// 
/// 与RCIMReceiveMessageDelegate的区别:
/// RCKitDispatchRecallMessageNotification只要注册都可以收到通知；RCIMReceiveMessageDelegate需要设置监听，并同时只能存在一个监听。
FOUNDATION_EXPORT NSString *const RCKitDispatchRecallMessageNotification;

/// 消息被撤回的Notification
/// 
/// 消息被撤回后，SDK会分发此通知。
/// 
/// Notification的object为 RCMessage 对象
/// 
/// 与RCIMReceiveMessageDelegate的区别:
/// RCKitDispatchRecallMessageDetailNotification只要注册都可以收到通知；RCIMReceiveMessageDelegate需要设置监听，并同时只能存在一个监听。
/// 
/// - Since: 5.3.3
FOUNDATION_EXPORT NSString *const RCKitDispatchRecallMessageDetailNotification;

/// 连接状态变化的Notification
/// 
/// SDK连接状态发生变化时，SDK会分发此通知。
/// 
/// Notification的object为NSNumber对象，对应于RCConnectionStatus的值。
/// 
/// 与RCIMConnectionStatusDelegate的区别:
/// RCKitDispatchConnectionStatusChangedNotification只要注册都可以收到通知；RCIMConnectionStatusDelegate需要设置监听，同时只能存在一个监听。
FOUNDATION_EXPORT NSString *const RCKitDispatchConnectionStatusChangedNotification;

/// 收到消息已读回执的响应
/// 通知的 object 中携带信息如下：
/// ```objc
/// @{@"targetId":targetId,
/// @"conversationType":@(conversationType),
/// @"messageUId": messageUId,
/// @"readCount":@(count)};
/// ```
FOUNDATION_EXPORT NSString *const RCKitDispatchMessageReceiptResponseNotification;

/// 收到消息已读回执的请求
/// 
/// 通知的 object 中携带信息如下：
/// ```objc
/// @{@"targetId":targetId,
/// @"conversationType":@(conversationType),
/// @"messageUId": messageUId};
/// ```
FOUNDATION_EXPORT NSString *const RCKitDispatchMessageReceiptRequestNotification;

/// 消息正在焚烧的Notification
/// 
/// 有消息处于焚烧倒计时，IMKit会分发此通知。
/// Notification的object为nil，userInfo为NSDictionary对象，
/// 其中key值分别为@"message"、@"remainDuration"
/// 对应的value为焚烧的消息对象、该消息剩余的焚烧时间。
/// 
/// 如果您使用IMLib请参考RCIMClient的RCMessageDestructDelegate
FOUNDATION_EXPORT NSString *const RCKitMessageDestructingNotification;

/// 收到会话状态同步的 Notification。
/// 
/// 收到会话状态同步之后，IMLib 会分发此通知。
/// 
/// Notification 的 object 是 `RCConversationStatusInfo` 对象的数组 ，userInfo 为 nil，
/// 
/// 收到这个消息之后可以更新您的会话的状态。
/// 
/// - Remark: 事件监听
FOUNDATION_EXPORT NSString *const RCKitDispatchConversationStatusChangeNotification;

/// 收到消息修改的 Notification。
/// 
/// 收到消息修改之后，IMKit 会分发此通知。
/// 
/// Notification 的 object 是 `RCMessage` 对象的数组，userInfo 为 nil。
/// 
/// 收到这个消息之后可以更新您的消息状态。
/// 
/// - Remark: 事件监听
FOUNDATION_EXPORT NSString *const RCKitDispatchMessagesModifiedNotification;

/// 收到会话草稿更新通知。
///
/// Notification 的 userInfo 结构是 @{ @"conversationType": @(conversationType), @"targetId": targetId, @"channelId": channelId}
///
/// 收到这个消息之后可以更新您的会话的状态。
///
/// - Remark: 事件监听
FOUNDATION_EXPORT NSString *const RCKitDispatchConversationDraftUpdateNotification;

/// 用户在线状态变化的通知
/// 
/// 用户在线状态发生变化时，SDK会分发此通知。
/// 
/// Notification 的 userInfo 结构是 @{ RCKitUserOnlineStatusChangedUserIdsKey : changedUserIds }
/// 
/// 收到这个消息之后可以更新您的用户在线状态。
/// 
/// - Remark: 事件监听
FOUNDATION_EXPORT NSString *const RCKitUserOnlineStatusChangedNotification;

/// 用户在线状态变化的通知中用户ID列表的key
FOUNDATION_EXPORT NSString *const RCKitUserOnlineStatusChangedUserIdsKey;

/// 会话列表中在线状态变化的通知
/// 
/// 会话列表中在线状态发生变化时，SDK会分发此通知。
/// 
/// Notification 的 userInfo 结构是 @{ RCKitUserOnlineStatusChangedUserIdsKey : changedUserIds }
/// 
/// 收到这个消息之后可以更新您的会话列表中的在线状态。
/// 
/// - Remark: 事件监听
FOUNDATION_EXPORT NSString *const RCKitConversationCellOnlineStatusUpdateNotification;

#pragma mark - 用户信息提供者、群组信息提供者、群名片信息提供者

typedef NS_ENUM(NSUInteger, RCDataSourceType) {
    /// 信息提供者
    RCDataSourceTypeInfoProvider = 0,
    /// 信息托管
    RCDataSourceTypeInfoManagement,
};

/// 用户信息提供者
/// 
/// SDK需要通过您实现的用户信息提供者，获取用户信息并显示。
@protocol RCIMUserInfoDataSource <NSObject>

/// SDK 的回调，用于向 App 获取用户信息
/// 
/// - Parameter userId:      用户ID
/// - Parameter completion:  获取用户信息完成之后需要执行的Block [userInfo:该用户ID对应的用户信息]
/// 
/// SDK通过此方法获取用户信息并显示，请在completion中返回该用户ID对应的用户信息。
/// 在您设置了用户信息提供者之后，SDK在需要显示用户信息的时候，会调用此方法，向您请求用户信息用于显示。
- (void)getUserInfoWithUserId:(NSString *)userId completion:(void (^)(RCUserInfo *_Nullable userInfo))completion;

@end

/// 公众号信息提供者
/// 
/// SDK 需要通过您实现的公众号信息提供者，获取公众号信息并显示。
@protocol RCIMPublicServiceProfileDataSource <NSObject>

/// SDK 的回调，用于向 App 获取公众号信息
/// 
/// - Parameter accountId: 公众号 ID
/// - Parameter completion:  获取公众号信息完成之后需要执行的 Block[profile: 该公众号 ID 对应的公众号信息]
/// 
/// SDK 通过此方法获取公众号信息并显示，请在 completion 中返回该公众号 ID 对应的公众号信息。
/// 在您设置了公众号信息提供者之后，SDK 在需要显示公众号信息的时候，会调用此方法，向您请求公众号信息用于显示。
- (void)getPublicServiceProfile:(NSString *)accountId completion:(void (^)(RCPublicServiceProfile *profile))completion;

/// SDK 的回调，用于向 App 同步获取公众号信息
/// 
/// - Parameter accountId: 公众号 ID
/// - Returns: 公众号信息
- (RCPublicServiceProfile *)publicServiceProfile:(NSString *)accountId;

@end

/// 群组信息提供者
/// 
/// SDK需要通过您实现的群组信息提供者，获取群组信息并显示。
@protocol RCIMGroupInfoDataSource <NSObject>

/// SDK 的回调，用于向 App 获取群组信息
/// 
/// - Parameter groupId:     群组ID
/// - Parameter completion:  获取群组信息完成之后需要执行的Block [groupInfo:该群组ID对应的群组信息]
/// 
/// SDK通过此方法获取群组信息并显示，请在completion的block中返回该群组ID对应的群组信息。
/// 在您设置了群组信息提供者之后，SDK在需要显示群组信息的时候，会调用此方法，向您请求群组信息用于显示。
- (void)getGroupInfoWithGroupId:(NSString *)groupId completion:(void (^)(RCGroup *_Nullable groupInfo))completion;

@end

/// 群名片信息提供者
/// 
/// 如果您使用了群名片功能，SDK需要通过您实现的群名片信息提供者，获取用户在群组中的名片信息并显示。
@protocol RCIMGroupUserInfoDataSource <NSObject>

/// SDK 的回调，用于向 App 获取用户在群组中的群名片信息
/// 
/// - Parameter userId:          用户ID
/// - Parameter groupId:         群组ID
/// - Parameter completion:      获取群名片信息完成之后需要执行的Block [userInfo:该用户ID在群组中对应的群名片信息]
/// 
/// 如果您使用了群名片功能，SDK需要通过您实现的群名片信息提供者，获取用户在群组中的名片信息并显示。
- (void)getUserInfoWithUserId:(NSString *)userId
                      inGroup:(NSString *)groupId
                   completion:(void (^)(RCUserInfo *_Nullable userInfo))completion;

@end

/// 群组成员列表提供者
@protocol RCIMGroupMemberDataSource <NSObject>
@optional

/// SDK 的回调，用于向 App 获取当前群组成员列表（需要实现用户信息提供者 RCIMUserInfoDataSource）
/// 
/// - Parameter groupId:     群ID
/// - Parameter resultBlock: 获取成功之后需要执行的Block [userIdList:群成员ID列表]
/// 
/// SDK通过此方法群组中的成员列表，请在resultBlock中返回该群组ID对应的群成员ID列表。
/// 在您设置了群组成员列表提供者之后，SDK在需要获取群组成员列表的时候，会调用此方法，向您请求群组成员用于显示。
- (void)getAllMembersOfGroup:(NSString *)groupId result:(void (^)(NSArray<NSString *> *_Nullable userIdList))resultBlock;
@end

#pragma mark - 消息接收监听器

/// IMKit消息接收的监听器
/// 
/// 设置 IMKit 的消息接收监听器请参考 RCIM 的 receiveMessageDelegate 属性。
/// 
/// - Warning: 如果您使用 IMKit，可以设置并实现此 Delegate 监听消息接收；
/// 如果您使用 IMLib，请使用 RCIMClient 中的 RCIMClientReceiveMessageDelegate 监听消息接收，而不要使用此监听器。
@protocol RCIMReceiveMessageDelegate <NSObject>

@optional

/// 接收消息的回调方法
/// 
/// - Parameter message:     当前接收到的消息
/// - Parameter left:        还剩余的未接收的消息数，left>=0
/// 
/// 如果您设置了IMKit消息监听之后，SDK在接收到消息时候会执行此方法（无论App处于前台或者后台）。
/// 其中，left为还剩余的、还未接收的消息数量。比如刚上线一口气收到多条消息时，通过此方法，您可以获取到每条消息，left会依次递减直到0。
/// 您可以根据left数量来优化您的App体验和性能，比如收到大量消息时等待left为0再刷新UI。
- (void)onRCIMReceiveMessage:(RCMessage *)message left:(int)left;

/// 接收消息的回调方法
/// 
/// - Parameter message: 当前接收到的消息
/// - Parameter nLeft: 还剩余的未接收的消息数，left>=0
/// - Parameter offline: 是否是离线消息
/// - Parameter hasPackage: SDK 拉取服务器的消息以包(package)的形式批量拉取，有 package 存在就意味着远端服务器还有消息尚未被 SDK
/// 拉取
///
/// 和 ``onRCIMReceiveMessage:left:`` 功能完全一致，额外把
/// offline 和 hasPackage 参数暴露，开发者可以根据 nLeft、offline、hasPackage 来决定何时的时机刷新 UI ；
///
/// 建议当 hasPackage=0 并且 nLeft=0 时刷新 UI
/// - Warning: 如果使用此方法，那么就不能再使用 RCIM 中 - (void)onRCIMReceived:(RCMessage *)message left:(int)nLeft 的使用，否则会出现重复操作的情形
- (void)onRCIMReceived:(RCMessage *)message
                  left:(int)nLeft
               offline:(BOOL)offline
            hasPackage:(BOOL)hasPackage;

/// 当App处于后台时，接收到消息并弹出本地通知的回调方法
/// 
/// - Parameter message:     接收到的消息
/// - Parameter senderName:  消息发送者的用户名称
/// - Returns: 当返回值为NO时，SDK会弹出默认的本地通知提示；当返回值为YES时，SDK针对此消息不再弹本地通知提示
/// 
/// 如果您设置了IMKit消息监听之后，当App处于后台，收到消息时弹出本地通知之前，会执行此方法。
/// 如果App没有实现此方法，SDK会弹出默认的本地通知提示。
/// 流程：
/// SDK接收到消息 -> App处于后台状态 -> 通过用户/群组/群名片信息提供者获取消息的用户/群组/群名片信息
/// -> 用户/群组信息为空 -> 不弹出本地通知
/// -> 用户/群组信息存在 -> 回调此方法准备弹出本地通知 -> App实现并返回YES        -> SDK不再弹出此消息的本地通知
/// -> App未实现此方法或者返回NO -> SDK弹出默认的本地通知提示
/// 
/// 
/// 您可以通过RCIM的disableMessageNotificaiton属性，关闭所有的本地通知(此时不再回调此接口)。
/// 
/// - Warning: 如果App在后台想使用SDK默认的本地通知提醒，需要实现用户/群组/群名片信息提供者，并返回正确的用户信息或群组信息。
/// 参考RCIMUserInfoDataSource、RCIMGroupInfoDataSource与RCIMGroupUserInfoDataSource
- (BOOL)onRCIMCustomLocalNotification:(RCMessage *)message withSenderName:(NSString *)senderName;

/// 当App处于前台时，接收到消息并播放提示音的回调方法
/// 
/// - Parameter message: 接收到的消息
/// - Returns: 当返回值为NO时，SDK会播放默认的提示音；当返回值为YES时，SDK针对此消息不再播放提示音
/// 
/// 收到消息时播放提示音之前，会执行此方法。
/// 如果App没有实现此方法，SDK会播放默认的提示音。
/// 流程：
/// SDK接收到消息 -> App处于前台状态 -> 回调此方法准备播放提示音 -> App实现并返回YES        -> SDK针对此消息不再播放提示音
/// -> App未实现此方法或者返回NO -> SDK会播放默认的提示音
/// 
/// 您可以通过 RCKitConfigCenter.message.disableMessageAlertSound 属性，关闭所有前台消息的提示音(此时不再回调此接口)。
- (BOOL)onRCIMCustomAlertSound:(RCMessage *)message;

/// 消息被撤回的回调方法
/// 
/// - Parameter messageId: 被撤回的消息ID
/// 
/// 被撤回的消息会变更为RCRecallNotificationMessage，App需要在UI上刷新这条消息。
- (void)onRCIMMessageRecalled:(long)messageId __deprecated_msg("Use  messageDidRecall on RCIM instead");

/// 消息被撤回的回调方法
/// 
/// - Parameter message: 被撤回的消息
/// 
/// - 如果不删除被撤回的消息，被撤回的原消息会变更为RCRecallNotificationMessage ，参数 message 就是变更后的消息，App需要在UI上刷新这条消息。
/// - 如果删除被撤回的消息，参数 message 就是被撤回的原消息，App需要在UI上找到删除这条消息。
/// 
/// 和上面的 - (void)onRCIMMessageRecalled:(long)messageId 功能完全一致，只能选择其中一个使用。
- (void)messageDidRecall:(RCMessage *)message;

/// 当 Kit 收到消息回调的方法
/// 
/// - Parameter message: 接收到的消息
/// - Returns: YES 拦截, 不显示  NO: 不拦截, 显示此消息。
/// 此处只处理实时收到消息时，在界面上是否显示此消息。
/// 在重新加载会话页面时，不受此处逻辑控制。
/// 若要永久不显示此消息，需要从数据库删除该消息，在回调处理中调用 deleteMessages,
/// 否则在重新加载会话时会将此消息重新加载出来
/// 
/// 收到消息，会执行此方法。
- (BOOL)interceptMessage:(RCMessage *)message;

@end

#pragma mark - 连接状态监听器

/// IMKit连接状态的的监听器
/// 
/// 设置IMKit的连接状态监听器，请参考RCIM的connectionStatusDelegate属性。
/// 
/// - Warning: 如果您使用IMKit，可以设置并实现此Delegate监听连接状态；
/// 如果您使用IMLib，请使用RCIMClient中的RCConnectionStatusChangeDelegate监听连接状态，而不要使用此监听器。
@protocol RCIMConnectionStatusDelegate <NSObject>

/// IMKit连接状态的的监听器
/// 
/// - Parameter status:  SDK与融云服务器的连接状态
/// 
/// 如果您设置了IMKit消息监听之后，当SDK与融云服务器的连接状态发生变化时，会回调此方法。
- (void)onRCIMConnectionStatusChanged:(RCConnectionStatus)status;

@end

#pragma mark - 消息发送监听器

/// IMKit消息发送监听器
/// 
/// 设置IMKit的消息发送监听器，可以监听消息发送前以及消息发送后的结果。
/// 
/// - Warning: 如果您使用IMKit，可以设置并实现此Delegate监听消息发送；
@protocol RCIMSendMessageDelegate <NSObject>

/// 准备发送消息的监听器
/// 
/// - Parameter messageContent: 消息内容
/// 
/// - Returns: 修改后的消息内容
/// 
/// 此方法在消息准备向外发送时会执行，您可以在此方法中对消息内容进行过滤和修改等操作。
/// 如果此方法的返回值不为 nil，SDK 会对外发送返回的消息内容。
/// 
/// 如果您使用了RCConversationViewController 中的 willSendMessage: 方法，请不要重复使用此方法。
/// 选择其中一种方式实现您的需求即可。
- (RCMessageContent *)willSendIMMessage:(RCMessageContent *)messageContent __deprecated_msg("Use [RCIMMessageInterceptor interceptWillSendMessage:] instead");

/// 发送消息完成的监听器
/// 
/// - Parameter messageContent:   消息内容
/// 
/// - Parameter status:          发送状态，0表示成功，非0表示失败的错误码
/// 
/// 此方法在消息向外发送结束之后会执行。您可以通过此方法监听消息发送情况。
/// 
/// 如果您使用了 RCConversationViewController 中的 didSendMessage:content: 方法，请不要重复使用此方法。
/// 选择其中一种方式实现您的需求即可。
- (void)didSendIMMessage:(RCMessageContent *)messageContent status:(NSInteger)status __deprecated_msg("Use [RCIMMessageInterceptor interceptDidSendMessage:] instead");


@end


#pragma mark - 消息发送拦截

/// IMKit消息发送拦截
/// 设置IMKit的消息发送拦截器，可以拦截消息发送前以及消息发送后的结果。
/// 例如消息合并转发，附件上传自己到 App File Server 时，可以使用此拦截器
/// 
/// - Warning: 如果您使用IMKit，可以设置并实现；
/// - Warning: 如果您使用- (RCMessageContent *)willSendMessage:(RCMessageContent *)message， 拦截发送消息，推荐使用此拦截器；
/// 
/// 两者根据使用场景二选其一， 多媒体附件上传到 App File Server 时，推荐使用此方式来实现
/// - Since: 5.3.5
@protocol RCIMMessageInterceptor <NSObject>

/// 准备发送消息的拦截回调
/// 
/// - Parameter message: 准备发送的消息
/// - Returns: YES 用户拦截此次消息，SDK不再做后续处理，NO 交由SDK处理
/// 此方法在消息准备向外发送时会执行，您可以在此方法中对消息内容进行过滤拦截。
/// 如果只进行拦截，修改发送内容，修改后， return NO SDK 会继续执行发送。
/// 
/// - Since: 5.3.5
- (BOOL)interceptWillSendMessage:(RCMessage *)message;

@optional
/// 发送消息成功的拦截回调
/// 
/// - Parameter message: 发送成功的消息
/// 此方法在消息向外发送成功后会执行，您可以在此方法中收到回调通知。
/// message.sentStatus, RCSentStatus 可根据枚举值判断发送成功或失败
/// 
/// - Since: 5.3.5
- (void)interceptDidSendMessage:(RCMessage *)message;

@end


#pragma mark - IMKit核心类

/// 融云IMKit核心类
/// 
/// 您需要通过sharedRCIM方法，获取单例对象
@interface RCIM : NSObject

/// 获取融云界面组件IMKit的核心类单例
/// 
/// - Returns: 融云界面组件IMKit的核心类单例
/// 
/// 您可以通过此方法，获取IMKit的单例，访问对象中的属性和方法。
+ (instancetype)sharedRCIM;

#pragma mark - SDK初始化

/// 初始化融云SDK
/// 
/// - Parameter appKey:  从融云开发者平台创建应用后获取到的App Key
/// - Parameter option:  设置配置信息，详细配置项信息请查看 RCInitOption.h 文件
/// 
/// 您在使用融云SDK所有功能（包括显示SDK中或者继承于SDK的View）之前，您必须先调用此方法初始化SDK。
/// 在App整个生命周期中，您只需要执行一次初始化。
/// 
/// - Warning: 如果您使用IMKit，请使用此方法初始化SDK；
/// 如果您使用IMLib，请使用RCIMClient中的同名方法初始化，而不要使用此方法。
- (void)initWithAppKey:(NSString *)appKey option:(nullable RCInitOption *)option;

#pragma mark - 连接与断开服务器

/// 与融云服务器建立连接
/// 
/// - Parameter token:                   从您服务器端获取的 token (用户身份令牌)
/// - Parameter dbOpenedBlock:                本地消息数据库打开的回调
/// - Parameter successBlock:            连接建立成功的回调 [ userId: 当前连接成功所用的用户 ID]
/// - Parameter errorBlock:              连接建立失败的回调，触发该回调代表 SDK 无法继续重连 [errorCode: 连接失败的错误码]
/// 
/// 调用该接口，SDK 会在连接失败之后尝试重连，直到连接成功或者出现 SDK 无法处理的错误（如 token 非法）。
/// 如果您不想一直进行重连，可以使用 connectWithToken:timeLimit:dbOpened:success:error: 接口并设置连接超时时间 timeLimit。
/// 
/// 连接成功后，SDK 将接管所有的重连处理。当因为网络原因断线的情况下，SDK 会不停重连直到连接成功为止，不需要您做额外的连接操作。
/// 
/// 对于 errorBlock 需要特定关心 tokenIncorrect 的情况：
/// 1. token 错误，请您检查客户端初始化使用的 AppKey 和您服务器获取 token 使用的 AppKey 是否一致；
/// 2. token 过期，是因为您在开发者后台设置了 token 过期时间，您需要请求您的服务器重新获取 token 并再次用新的 token 建立连接。
/// 在此种情况下，您需要请求您的服务器重新获取 token 并建立连接，但是注意避免无限循环，以免影响 App 用户体验。
/// 
/// - Warning: 如果您使用 IMKit，请使用该方法建立与融云服务器的连接。
/// 
/// 此方法的回调并非为原调用线程，您如果需要进行 UI 操作，请注意切换到主线程。
- (void)connectWithToken:(NSString *)token
                dbOpened:(nullable void (^)(RCDBErrorCode code))dbOpenedBlock
                 success:(nullable void (^)(NSString *userId))successBlock
                   error:(nullable void (^)(RCConnectErrorCode errorCode))errorBlock;

/// 与融云服务器建立连接
/// 
/// - Parameter token:                   从您服务器端获取的 token (用户身份令牌)
/// - Parameter timeLimit:                 SDK 连接的超时时间，单位: 秒
/// timeLimit <= 0，SDK 会一直连接，直到连接成功或者出现 SDK 无法处理的错误（如 token 非法）。
/// timeLimit > 0，SDK 最多连接 timeLimit 秒，超时时返回 RC_CONNECT_TIMEOUT 错误，并不再重连。
/// - Parameter dbOpenedBlock:                本地消息数据库打开的回调
/// - Parameter successBlock:            连接建立成功的回调 [ userId: 当前连接成功所用的用户 ID]
/// - Parameter errorBlock:              连接建立失败的回调，触发该回调代表 SDK 无法继续重连 [errorCode: 连接失败的错误码]
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
/// - Warning: 如果您使用 IMKit，请使用 RCIM 中的同名方法建立与融云服务器的连接。
/// 
/// 此方法的回调并非为原调用线程，您如果需要进行 UI 操作，请注意切换到主线程。
- (void)connectWithToken:(NSString *)token
               timeLimit:(int)timeLimit
                dbOpened:(nullable void (^)(RCDBErrorCode code))dbOpenedBlock
                 success:(nullable void (^)(NSString *userId))successBlock
                   error:(nullable void (^)(RCConnectErrorCode errorCode))errorBlock;


/// 断开与融云服务器的连接
/// 
/// - Parameter isReceivePush:   App在断开连接之后，是否还接收远程推送
/// 
/// 因为SDK在前后台切换或者网络出现异常都会自动重连，会保证连接的可靠性。
/// 所以除非您的App逻辑需要登出，否则一般不需要调用此方法进行手动断开。
/// 
/// - Warning: 如果您使用IMKit，请使用此方法断开与融云服务器的连接；
/// 如果您使用IMLib，请使用RCIMClient中的同名方法断开与融云服务器的连接，而不要使用此方法。
/// 
/// isReceivePush指断开与融云服务器的连接之后，是否还接收远程推送。
/// [[RCIM sharedRCIM] disconnect:YES]与[[RCIM sharedRCIM] disconnect]完全一致；
/// [[RCIM sharedRCIM] disconnect:NO]与[[RCIM sharedRCIM] logout]完全一致。
/// 您只需要按照您的需求，使用disconnect:与disconnect以及logout三个接口其中一个即可。
- (void)disconnect:(BOOL)isReceivePush;

/// 断开与融云服务器的连接，但仍然接收远程推送
/// 
/// 因为SDK在前后台切换或者网络出现异常都会自动重连，会保证连接的可靠性。
/// 所以除非您的App逻辑需要登出，否则一般不需要调用此方法进行手动断开。
/// 
/// - Warning: 如果您使用IMKit，请使用此方法断开与融云服务器的连接；
/// 如果您使用IMLib，请使用RCIMClient中的同名方法断开与融云服务器的连接，而不要使用此方法。
/// 
/// [[RCIM sharedRCIM] disconnect:YES]与[[RCIM sharedRCIM] disconnect]完全一致；
/// [[RCIM sharedRCIM] disconnect:NO]与[[RCIM sharedRCIM] logout]完全一致。
/// 您只需要按照您的需求，使用disconnect:与disconnect以及logout三个接口其中一个即可。
- (void)disconnect;

/// 断开与融云服务器的连接，并不再接收远程推送
/// 
/// 因为SDK在前后台切换或者网络出现异常都会自动重连，会保证连接的可靠性。
/// 所以除非您的App逻辑需要登出，否则一般不需要调用此方法进行手动断开。
/// 
/// - Warning: 如果您使用IMKit，请使用此方法断开与融云服务器的连接；
/// 如果您使用IMLib，请使用RCIMClient中的同名方法断开与融云服务器的连接，而不要使用此方法。
/// 
/// [[RCIM sharedRCIM] disconnect:YES]与[[RCIM sharedRCIM] disconnect]完全一致；
/// [[RCIM sharedRCIM] disconnect:NO]与[[RCIM sharedRCIM] logout]完全一致。
/// 您只需要按照您的需求，使用disconnect:与disconnect以及logout三个接口其中一个即可。
- (void)logout;

#pragma mark 连接状态监听

/// IMKit连接状态的监听器
/// 
/// - Warning: 如果您使用IMKit，可以设置并实现此Delegate监听消息接收；
/// 如果您使用IMLib，请使用RCIMClient中的 setRCConnectionStatusChangeDelegate 监听连接状态，而不要使用此方法。
@property (nonatomic, weak, nullable) id<RCIMConnectionStatusDelegate> connectionStatusDelegate;

/// 添加 IMKit 连接状态监听
/// 
/// - Parameter delegate: 代理
- (void)addConnectionStatusDelegate:(id<RCIMConnectionStatusDelegate>)delegate;

/// 移除 IMKit 连接状态监听
/// 
/// - Parameter delegate: 代理
- (void)removeConnectionStatusDelegate:(id<RCIMConnectionStatusDelegate>)delegate;

/// 获取当前SDK的连接状态
/// 
/// - Returns: 当前SDK的连接状态
- (RCConnectionStatus)getConnectionStatus;

#pragma mark - 消息接收与发送

/// 注册自定义的消息类型
/// 
/// - Parameter messageClass:    自定义消息的类，该自定义消息需要继承于RCMessageContent
/// 
/// 如果您需要自定义消息，必须调用此方法注册该自定义消息的消息类型，否则SDK将无法识别和解析该类型消息。
/// 
/// - Warning: 如果您使用IMKit，请使用此方法注册自定义的消息类型；
/// 如果您使用IMLib，请使用RCIMClient中的同名方法注册自定义的消息类型，而不要使用此方法。
- (void)registerMessageType:(Class)messageClass;

#pragma mark 消息发送监听

/// 消息发送监听
@property (nonatomic, weak, nullable) id<RCIMSendMessageDelegate> sendMessageDelegate;

#pragma mark 消息发送拦截

/// 消息发送拦截
/// - Since: 5.3.5
@property (nonatomic, weak, nullable) id<RCIMMessageInterceptor> messageInterceptor;

#pragma mark 消息发送

/// 发送消息(除图片消息、文件消息外的所有消息)，会自动更新UI
/// 
/// - Parameter conversationType:    发送消息的会话类型
/// - Parameter targetId:            发送消息的目标会话ID
/// - Parameter content:             消息的内容
/// - Parameter pushContent:         接收方离线时需要显示的远程推送内容
/// - Parameter pushData:            接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter successBlock:        消息发送成功的回调 [messageId:消息的ID]
/// - Parameter errorBlock:          消息发送失败的回调 [nErrorCode:发送失败的错误码, messageId:消息的ID]
/// - Returns: 发送的消息实体
/// 
/// 当接收方离线并允许远程推送时，会收到远程推送。
/// 远程推送中包含两部分内容，一是pushContent，用于显示；二是pushData，用于携带不显示的数据。
/// 
/// SDK内置的消息类型，如果您将 `pushContent` 和 `pushData` 置为nil，会使用默认的推送格式进行远程推送。
/// 自定义类型的消息，需要您自己设置 `pushContent` 和 `pushData` 来定义推送内容，否则将不会进行远程推送。
/// 
/// - Warning: 如果您使用IMKit，使用此方法发送消息SDK会自动更新UI；
/// 如果您使用IMLib，请使用RCIMClient中的同名方法发送消息，不会自动更新UI。
- (RCMessage *)sendMessage:(RCConversationType)conversationType
                  targetId:(NSString *)targetId
                   content:(RCMessageContent *)content
               pushContent:(nullable NSString *)pushContent
                  pushData:(nullable NSString *)pushData
                   success:(nullable void (^)(long messageId))successBlock
                     error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock;

/// 发送消息(除图片消息、文件消息外的所有消息)，会自动更新UI
/// 
/// - Parameter message:             将要发送的消息实体（需要保证 message 中的 conversationType，targetId，messageContent 是有效值)
/// - Parameter pushContent:         接收方离线时需要显示的远程推送内容
/// - Parameter pushData:            接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter successBlock:        消息发送成功的回调 [successMessage: 消息实体]
/// - Parameter errorBlock:          消息发送失败的回调 [nErrorCode: 发送失败的错误码, errorMessage:消息实体]
/// - Returns: 发送的消息实体
/// 
/// 当接收方离线并允许远程推送时，会收到远程推送。
/// 远程推送中包含两部分内容，一是pushContent，用于显示；二是pushData，用于携带不显示的数据。
/// 
/// SDK内置的消息类型，如果您将pushContent和pushData置为nil，会使用默认的推送格式进行远程推送。
/// 自定义类型的消息，需要您自己设置pushContent和pushData来定义推送内容，否则将不会进行远程推送。
/// 
/// - Warning: 如果您使用IMKit，使用此方法发送消息SDK会自动更新UI；
/// 如果您使用IMLib，请使用RCIMClient中的同名方法发送消息，不会自动更新UI。
/// 
/// - Remark: 消息操作
- (RCMessage *)sendMessage:(RCMessage *)message
               pushContent:(nullable NSString *)pushContent
                  pushData:(nullable NSString *)pushData
              successBlock:(nullable void (^)(RCMessage *successMessage))successBlock
                errorBlock:(nullable void (^)(RCErrorCode nErrorCode, RCMessage *errorMessage))errorBlock;

/// 发送媒体文件消息，会自动更新UI
/// 
/// - Parameter conversationType:    发送消息的会话类型
/// - Parameter targetId:            发送消息的目标会话ID
/// - Parameter content:             消息的内容
/// - Parameter pushContent:         接收方离线时需要显示的远程推送内容
/// - Parameter pushData:            接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter progressBlock:       消息发送进度更新的回调 [progress:当前的发送进度, 0 <= progress <= 100, messageId:消息的ID]
/// - Parameter successBlock:        消息发送成功的回调 [messageId:消息的ID]
/// - Parameter errorBlock:          消息发送失败的回调 [errorCode:发送失败的错误码, messageId:消息的ID]
/// - Parameter cancelBlock:         用户取消了消息发送的回调 [messageId:消息的ID]
/// - Returns: 发送的消息实体
/// 
/// 当接收方离线并允许远程推送时，会收到远程推送。
/// 远程推送中包含两部分内容，一是pushContent，用于显示；二是pushData，用于携带不显示的数据。
/// 
/// SDK内置的消息类型，如果您将pushContent和pushData置为nil，会使用默认的推送格式进行远程推送。
/// 自定义类型的消息，需要您自己设置pushContent和pushData来定义推送内容，否则将不会进行远程推送。
/// 
/// - Warning: 如果您使用IMKit，使用此方法发送媒体文件消息SDK会自动更新UI；
/// 如果您使用IMLib，请使用RCIMClient中的同名方法发送媒体文件消息，不会自动更新UI。
- (RCMessage *)sendMediaMessage:(RCConversationType)conversationType
                       targetId:(NSString *)targetId
                        content:(RCMessageContent *)content
                    pushContent:(nullable NSString *)pushContent
                       pushData:(nullable NSString *)pushData
                       progress:(nullable void (^)(int progress, long messageId))progressBlock
                        success:(nullable void (^)(long messageId))successBlock
                          error:(nullable void (^)(RCErrorCode errorCode, long messageId))errorBlock
                         cancel:(nullable void (^)(long messageId))cancelBlock;

/// 发送媒体文件消息，会自动更新UI
/// 
/// - Parameter message:             将要发送的消息实体（需要保证 message 中的 conversationType，targetId，messageContent 是有效值)
/// - Parameter pushContent:         接收方离线时需要显示的远程推送内容
/// - Parameter pushData:            接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter progressBlock:       消息发送进度更新的回调 [progress:当前的发送进度, 0 <= progress <= 100, progressMessage:消息实体]
/// - Parameter successBlock:        消息发送成功的回调 [successMessage:消息实体]
/// - Parameter errorBlock:          消息发送失败的回调 [nErrorCode:发送失败的错误码, errorMessage:消息实体]
/// - Parameter cancelBlock:         用户取消了消息发送的回调 [cancelMessage:消息实体]
/// - Returns: 发送的消息实体
/// 
/// 当接收方离线并允许远程推送时，会收到远程推送。
/// 远程推送中包含两部分内容，一是pushContent，用于显示；二是pushData，用于携带不显示的数据。
/// 
/// SDK内置的消息类型，如果您将pushContent和pushData置为nil，会使用默认的推送格式进行远程推送。
/// 自定义类型的消息，需要您自己设置pushContent和pushData来定义推送内容，否则将不会进行远程推送。
/// 
/// - Warning: 如果您使用IMKit，使用此方法发送媒体文件消息SDK会自动更新UI；
/// 如果您使用IMLib，请使用RCIMClient中的同名方法发送媒体文件消息，不会自动更新UI。
- (RCMessage *)sendMediaMessage:(RCMessage *)message
                    pushContent:(nullable NSString *)pushContent
                       pushData:(nullable NSString *)pushData
                       progress:(nullable void (^)(int progress, RCMessage *progressMessage))progressBlock
                   successBlock:(nullable void (^)(RCMessage *successMessage))successBlock
                     errorBlock:(nullable void (^)(RCErrorCode nErrorCode, RCMessage *errorMessage))errorBlock
                         cancel:(nullable void (^)(RCMessage *cancelMessage))cancelBlock;


/// 发送媒体文件消息，会自动更新UI(上传图片或文件到App指定的服务器)
/// 
/// - Parameter message:             将要发送的消息实体（需要保证 message 中的 conversationType，targetId，messageContent 是有效值)
/// - Parameter pushContent:         接收方离线时需要显示的远程推送内容
/// - Parameter pushData:            接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter uploadPrepareBlock:  媒体文件上传监听，可实现 block 自定义处理文件上传
/// [uploadListener:当前的发送进度监听，SDK 通过此监听更新 IMKit UI]
/// - Parameter progressBlock:       消息发送进度更新的回调 [progress:当前的发送进度, 0 <= progress <= 100, progressMessage:消息实体]
/// - Parameter successBlock:        消息发送成功的回调 [successMessage:消息实体]
/// - Parameter errorBlock:          消息发送失败的回调 [nErrorCode:发送失败的错误码, errorMessage:消息实体]
/// - Parameter cancelBlock:         用户取消了消息发送的回调 [cancelMessage:消息实体]
/// - Returns: 发送的消息实体
/// 
/// 此方法用于上传媒体信息到您自己的服务器
/// 当接收方离线并允许远程推送时，会收到远程推送。
/// 远程推送中包含两部分内容，一是pushContent，用于显示；二是pushData，用于携带不显示的数据。
/// 
/// SDK内置的消息类型，如果您将pushContent和pushData置为nil，会使用默认的推送格式进行远程推送。
/// 自定义类型的消息，需要您自己设置pushContent和pushData来定义推送内容，否则将不会进行远程推送。
/// 
/// - Warning: 如果您使用IMKit，使用此方法发送媒体文件消息SDK会自动更新UI；
/// 如果您使用IMLib，请使用 RCCoreClient 中的同名方法发送媒体文件消息，不会自动更新UI。
/// 
/// - Since: 5.3.5
- (RCMessage *)sendMediaMessage:(RCMessage *)message
                    pushContent:(nullable NSString *)pushContent
                       pushData:(nullable NSString *)pushData
                  uploadPrepare:(nullable void (^)(RCUploadMediaStatusListener *uploadListener))uploadPrepareBlock
                       progress:(nullable void (^)(int progress, long messageId))progressBlock
                   successBlock:(nullable void (^)(long messageId))successBlock
                     errorBlock:(nullable void (^)(RCErrorCode errorCode, long messageId))errorBlock
                         cancel:(nullable void (^)(long messageId))cancelBlock;

/// 取消发送中的媒体信息
/// 
/// - Parameter messageId:           媒体消息的messageId
/// 
/// - Returns: YES表示取消成功，NO表示取消失败，即已经发送成功或者消息不存在。
- (BOOL)cancelSendMediaMessage:(long)messageId;

/// 下载消息中的媒体文件
/// 
/// - Parameter messageId:       消息ID
/// - Parameter progressBlock:   下载进度更新的回调 [progress:当前的发送进度, 0 <= progress <= 100]
/// - Parameter successBlock:    下载成功的回调 [mediaPath:下载完成后文件在本地的存储路径]
/// - Parameter errorBlock:      下载失败的回调 [errorCode:下载失败的错误码]
/// - Parameter cancelBlock:     下载取消的回调
/// 
/// 媒体消息仅限于图片消息和文件消息。
- (void)downloadMediaMessage:(long)messageId
                    progress:(nullable void (^)(int progress))progressBlock
                     success:(nullable void (^)(NSString *mediaPath))successBlock
                       error:(nullable void (^)(RCErrorCode errorCode))errorBlock
                      cancel:(nullable void (^)(void))cancelBlock;

/// 根据文件 URL 地址下载文件内容
///
/// - Parameter fileName: 指定的文件名称 需要开发者指定文件后缀 (例如 rongCloud.mov)
/// - Parameter mediaUrl: 文件的 URL 地址
/// - Parameter progressBlock: 文件下载进度更新的回调 [progress:当前的下载进度, 0 <= progress <= 100]
/// - Parameter successBlock: 下载成功的回调[mediaPath:下载成功后本地存放的文件路径 文件路径为文件消息的默认地址]
/// - Parameter errorBlock: 下载失败的回调[errorCode:下载失败的错误码]
/// - Parameter cancelBlock: 用户取消了下载的回调
///
/// 用来获取媒体原文件时调用。如果本地缓存中包含此文件，则从本地缓存中直接获取，否则将从服务器端下载。
///
/// - Warning: 此方法仅仅是文件下载器，不会操作消息体。
///
/// - Remark: 多媒体下载
/// - Since: 5.10.0
- (void)downloadMediaFile:(NSString *_Nonnull)fileName
                 mediaUrl:(NSString *_Nonnull)mediaUrl
                 progress:(nullable void (^)(int progress))progressBlock
                  success:(nullable void (^)(NSString * mediaPath))successBlock
                    error:(nullable void (^)(RCErrorCode errorCode))errorBlock
                   cancel:(nullable void (^)(void))cancelBlock;

/// 取消下载中的媒体信息
/// 
/// - Parameter messageId: 媒体消息的messageId
/// 
/// - Returns: YES表示取消成功，NO表示取消失败，即已经下载完成或者消息不存在。
- (BOOL)cancelDownloadMediaMessage:(long)messageId;

/// 发送定向消息，会自动更新UI
/// 
/// - Parameter conversationType: 发送消息的会话类型
/// - Parameter targetId:         发送消息的目标会话ID
/// - Parameter userIdList:       发送给的用户ID列表
/// - Parameter content:          消息的内容
/// - Parameter pushContent:      接收方离线时需要显示的远程推送内容
/// - Parameter pushData:         接收方离线时需要在远程推送中携带的非显示数据
/// - Parameter successBlock:     消息发送成功的回调 [messageId:消息的ID]
/// - Parameter errorBlock:       消息发送失败的回调 [errorCode:发送失败的错误码,
/// messageId:消息的ID]
/// 
/// - Returns: 发送的消息实体
/// 
/// 此方法用于在群组和讨论组中发送消息给其中的部分用户，其它用户不会收到这条消息。
/// 如果您使用IMKit，使用此方法发送定向消息SDK会自动更新UI；
/// 如果您使用IMLib，请使用RCIMClient中的同名方法发送定向消息，不会自动更新UI。
/// 
/// - Warning: 此方法目前仅支持普通群组和讨论组。
- (RCMessage *)sendDirectionalMessage:(RCConversationType)conversationType
                             targetId:(NSString *)targetId
                         toUserIdList:(NSArray *)userIdList
                              content:(RCMessageContent *)content
                          pushContent:(nullable NSString *)pushContent
                             pushData:(nullable NSString *)pushData
                              success:(nullable void (^)(long messageId))successBlock
                                error:(nullable void (^)(RCErrorCode nErrorCode, long messageId))errorBlock;

/// 发起VoIP语音通话
/// 
/// - Parameter targetId:    要发起语音通话的对方的用户ID
/// 
/// - Warning: 旧版本VoIP接口，不再支持，请升级到最新VoIP版本。
//- (void)startVoIPCallWithTargetId:(NSString *)targetId;

#pragma mark 消息接收监听

/// IMKit消息接收的监听器
/// 
/// - Warning: 如果您使用IMKit，可以设置并实现此Delegate监听消息接收；
/// 如果您使用IMLib，请使用RCIMClient中的 `RCIMClientReceiveMessageDelegate` 监听消息接收，而不要使用此方法。
@property (nonatomic, weak, nullable) id<RCIMReceiveMessageDelegate> receiveMessageDelegate;

/// 添加 IMKit 接收消息监听
/// 
/// - Parameter delegate: 代理
- (void)addReceiveMessageDelegate:(id<RCIMReceiveMessageDelegate>)delegate;

/// 移除 IMKit 接收消息监听
/// 
/// - Parameter delegate: 代理
- (void)removeReceiveMessageDelegate:(id<RCIMReceiveMessageDelegate>)delegate;


#pragma mark - 讨论组相关操作

/// 创建讨论组
/// 
/// - Parameter name:            讨论组名称
/// - Parameter userIdList:      用户ID的列表
/// - Parameter successBlock:    创建讨论组成功的回调 [discussion:创建成功返回的讨论组对象]
/// - Parameter errorBlock:      创建讨论组失败的回调 [status:创建失败的错误码]
- (void)createDiscussion:(NSString *)name
              userIdList:(NSArray *)userIdList
                 success:(void (^)(RCDiscussion *discussion))successBlock
                   error:(void (^)(RCErrorCode status))errorBlock __attribute__((deprecated));

/// 讨论组加人，将用户加入讨论组
/// 
/// - Parameter discussionId:    讨论组ID
/// - Parameter userIdList:      需要加入的用户ID列表
/// - Parameter successBlock:    讨论组加人成功的回调 [discussion:讨论组加人成功返回的讨论组对象]
/// - Parameter errorBlock:      讨论组加人失败的回调 [status:讨论组加人失败的错误码]
/// 
/// 设置的讨论组名称长度不能超过40个字符，否则将会截断为前40个字符。
- (void)addMemberToDiscussion:(NSString *)discussionId
                   userIdList:(NSArray *)userIdList
                      success:(void (^)(RCDiscussion *discussion))successBlock
                        error:(void (^)(RCErrorCode status))errorBlock __attribute__((deprecated));

/// 讨论组踢人，将用户移出讨论组
/// 
/// - Parameter discussionId:    讨论组ID
/// - Parameter userId:          需要移出的用户ID
/// - Parameter successBlock:    讨论组踢人成功的回调 [discussion:讨论组踢人成功返回的讨论组对象]
/// - Parameter errorBlock:      讨论组踢人失败的回调 [status:讨论组踢人失败的错误码]
/// 
/// 如果当前登录用户不是此讨论组的创建者并且此讨论组没有开放加人权限，则会返回错误。
/// 
/// - Warning: 不能使用此接口将自己移除，否则会返回错误。
/// 如果您需要退出该讨论组，可以使用-quitDiscussion:success:error:方法。
- (void)removeMemberFromDiscussion:(NSString *)discussionId
                            userId:(NSString *)userId
                           success:(void (^)(RCDiscussion *discussion))successBlock
                             error:(void (^)(RCErrorCode status))errorBlock __attribute__((deprecated));

/// 退出当前讨论组
/// 
/// - Parameter discussionId:    讨论组ID
/// - Parameter successBlock:    退出成功的回调 [discussion:退出成功返回的讨论组对象]
/// - Parameter errorBlock:      退出失败的回调 [status:退出失败的错误码]
- (void)quitDiscussion:(NSString *)discussionId
               success:(void (^)(RCDiscussion *discussion))successBlock
                 error:(void (^)(RCErrorCode status))errorBlock __attribute__((deprecated));

/// 获取讨论组的信息
/// 
/// - Parameter discussionId:    需要获取信息的讨论组ID
/// - Parameter successBlock:    获取讨论组信息成功的回调 [discussion:获取的讨论组信息]
/// - Parameter errorBlock:      获取讨论组信息失败的回调 [status:获取讨论组信息失败的错误码]
- (void)getDiscussion:(NSString *)discussionId
              success:(void (^)(RCDiscussion *discussion))successBlock
                error:(void (^)(RCErrorCode status))errorBlock __attribute__((deprecated));

/// 设置讨论组名称
/// 
/// - Parameter discussionId:            需要设置的讨论组ID
/// - Parameter discussionName:          需要设置的讨论组名称，discussionName 长度 <= 40
/// - Parameter successBlock:            设置成功的回调
/// - Parameter errorBlock:              设置失败的回调 [status:设置失败的错误码]
/// 
/// 设置的讨论组名称长度不能超过40个字符，否则将会截断为前40个字符。
- (void)setDiscussionName:(NSString *)discussionId
                     name:(NSString *)discussionName
                  success:(void (^)(void))successBlock
                    error:(void (^)(RCErrorCode status))errorBlock __attribute__((deprecated));

/// 设置讨论组是否开放加人权限
/// 
/// - Parameter discussionId:    论组ID
/// - Parameter isOpen:          是否开放加人权限
/// - Parameter successBlock:    设置成功的回调
/// - Parameter errorBlock:      设置失败的回调[status:设置失败的错误码]
/// 
/// 讨论组默认开放加人权限，即所有成员都可以加人。
/// 如果关闭加人权限之后，只有讨论组的创建者有加人权限。
- (void)setDiscussionInviteStatus:(NSString *)discussionId
                           isOpen:(BOOL)isOpen
                          success:(void (^)(void))successBlock
                            error:(void (^)(RCErrorCode status))errorBlock __attribute__((deprecated));

#pragma mark - 用户信息、群组信息相关

/// 当前登录的用户的用户信息
/// 
/// 与融云服务器建立连接之后，应该设置当前用户的用户信息，用于SDK显示和发送。
/// 
/// - Warning: 如果传入的用户信息中的用户ID与当前登录的用户ID不匹配，则将会忽略。
@property (nonatomic, strong, nullable) RCUserInfo *currentUserInfo;

/// 是否将用户信息和群组信息在本地持久化存储，默认值为 NO
/// 
/// 如果设置为NO，则SDK在需要显示用户信息时，会调用用户信息提供者获取用户信息并缓存到 Cache，
/// 此 Cache 在 App 生命周期结束时会被移除，下次启动时会再次通过用户信息提供者获取信息。
/// 如果设置为 YES，则会将获取到的用户信息持久化存储在本地，App下次启动时 Cache 会仍然有效。
@property (nonatomic, assign) BOOL enablePersistentUserInfoCache;

/// 是否在发送的所有消息中携带当前登录的用户信息，默认值为NO
/// 
/// 如果设置为YES，则会在每一条发送的消息中携带当前登录用户的用户信息。
/// 收到一条携带了用户信息的消息，SDK会将其信息加入用户信息的cache中并显示；
/// 若消息中不携带用户信息，则仍然会通过用户信息提供者获取用户信息进行显示。
/// 
/// - Warning: 需要先设置当前登录用户的用户信息，参考RCIM的currentUserInfo。
@property (nonatomic, assign) BOOL enableMessageAttachUserInfo;

/// 用户信息类型， 默认为 RCDataSourceTypeInfoProvider， 表示使用信息提供者
@property (nonatomic, assign) RCDataSourceType currentDataSourceType;

#pragma mark 用户信息

/// 用户信息提供者
/// 
/// SDK需要通过您实现的用户信息提供者，获取用户信息并显示。
@property (nonatomic, weak, nullable) id<RCIMUserInfoDataSource> userInfoDataSource;

/// 更新SDK中的用户信息缓存
/// 
/// - Parameter userInfo:     需要更新的用户信息
/// - Parameter userId:       需要更新的用户ID
/// 
/// 使用此方法，可以更新SDK缓存的用户信息。
/// 但是处于性能和使用场景权衡，SDK不会在当前View立即自动刷新（会在切换到其他View的时候再刷新该用户的显示信息）。
/// 如果您想立即刷新，您可以在会话列表或者会话页面reload强制刷新。
- (void)refreshUserInfoCache:(RCUserInfo *)userInfo withUserId:(NSString *)userId;

/// 获取SDK中缓存的用户信息
/// 
/// - Parameter userId:  用户ID
/// - Returns: SDK中缓存的用户信息
- (nullable RCUserInfo *)getUserInfoCache:(NSString *)userId;

/// 清空SDK中所有的用户信息缓存
/// 
/// 使用此方法，会清空SDK中所有的用户信息缓存。
/// 但是处于性能和使用场景权衡，SDK不会在当前View立即自动刷新（会在切换到其他View的时候再刷新所显示的用户信息）。
/// 如果您想立即刷新，您可以在会话列表或者会话页面reload强制刷新。
- (void)clearUserInfoCache;

/// 修改自己的用户信息
///
/// - Parameter profile: 用户信息
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// - Since: 5.16.0
- (void)updateMyUserProfile:(RCUserProfile *)profile
               successBlock:(void (^)(void))successBlock
                 errorBlock:(nullable void (^)(RCErrorCode errorCode,  NSArray<NSString *> * _Nullable errorKeys))errorBlock;

/// 好友信息设置
/// - Parameter userId: 用户ID
/// - Parameter remark: 好友备注，最多为 64 个字符，不传或为空时清除备注名。
/// - Parameter extProfile: 扩展信息
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.16.0
- (void)setFriendInfo:(NSString *)userId
               remark:(nullable NSString *)remark
           extProfile:(nullable NSDictionary<NSString *, NSString*> *)extProfile
         successBlock:(void (^)(void))successBlock
           errorBlock:(void (^)(RCErrorCode errorCode, NSArray<NSString *> * _Nullable errorKeys))errorBlock;


#pragma mark 群组信息

/// 群组信息提供者
/// 
/// SDK需要通过您实现的群组信息提供者，获取群组信息并显示。
@property (nonatomic, weak, nullable) id<RCIMGroupInfoDataSource> groupInfoDataSource;

/// 更新SDK中的群组信息缓存
/// 
/// - Parameter groupInfo:   需要更新的群组信息
/// - Parameter groupId:     需要更新的群组ID
/// 
/// 使用此方法，可以更新SDK缓存的群组信息。
/// 但是处于性能和使用场景权衡，SDK不会在当前View立即自动刷新（会在切换到其他View的时候再刷新该群组的显示信息）。
/// 如果您想立即刷新，您可以在会话列表或者会话页面reload强制刷新。
- (void)refreshGroupInfoCache:(RCGroup *)groupInfo withGroupId:(NSString *)groupId;

/// 获取SDK中缓存的群组信息
/// 
/// - Parameter groupId:     群组ID
/// - Returns: SDK中缓存的群组信息
- (nullable RCGroup *)getGroupInfoCache:(NSString *)groupId;

/// 清空SDK中所有的群组信息缓存
/// 
/// 使用此方法，会清空SDK中所有的群组信息缓存。
/// 但是处于性能和使用场景权衡，SDK不会在当前View立即自动刷新（会在切换到其他View的时候再刷新所显示的群组信息）。
/// 如果您想立即刷新，您可以在会话列表或者会话页面reload强制刷新。
- (void)clearGroupInfoCache;

/// 更新群组信息
/// - Parameter groupInfo: 群组信息，groupId 必填，否则更新失败
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.16.0

- (void)updateGroupInfo:(RCGroupInfo *)groupInfo
           successBlock:(void (^)(void))successBlock
             errorBlock:(void (^)(RCErrorCode errorCode, NSArray<NSString *> * _Nullable errorKeys))errorBlock NS_SWIFT_NAME(updateGroupInfo(_:successBlock:errorBlock:));


/// 设置群组备注名
/// - Parameter groupId: 群组ID
/// - Parameter remark: 群备注，字符串长度不超过 64 个字符。传 nil 或 空字符串 表示移除群备注
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.2
- (void)setGroupRemark:(NSString *)groupId
                remark:(nullable NSString *)remark
               success:(void (^)(void))successBlock
                 error:(void (^)(RCErrorCode errorCode))errorBlock;

/// 设置群成员资料
/// - Parameter groupId: 群组ID
/// - Parameter userId: 用户ID， 必填项，支持传入当前登录用户 ID
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
                errorBlock:(void (^)(RCErrorCode errorCode, NSArray<NSString *> * _Nullable errorKeys))errorBlock;

#pragma mark 群名片信息（可选）

/// 群名片信息提供者
/// 
/// 如果您使用了群名片功能，SDK需要通过您实现的群名片信息提供者，获取用户在群组中的名片信息并显示。
@property (nonatomic, weak, nullable) id<RCIMGroupUserInfoDataSource> groupUserInfoDataSource;

/// 获取SDK中缓存的群名片信息
/// 
/// - Parameter userId:      用户ID
/// - Parameter groupId:     群组ID
/// - Returns: 群名片信息
- (nullable RCUserInfo *)getGroupUserInfoCache:(NSString *)userId withGroupId:(NSString *)groupId;

/// 更新SDK中的群名片信息缓存
/// 
/// - Parameter userInfo:     需要更新的用户信息
/// - Parameter userId:       需要更新的用户ID
/// - Parameter groupId:      需要更新群名片信息的群组ID
/// 
/// 使用此方法，可以更新SDK缓存的群名片信息。
/// 但是处于性能和使用场景权衡，SDK不会在当前 View 立即自动刷新（会在切换到其他View的时候再刷新该群名片的显示信息）。
/// 如果您想立即刷新，您可以在会话列表或者会话页面 reload 强制刷新。
- (void)refreshGroupUserInfoCache:(RCUserInfo *)userInfo withUserId:(NSString *)userId withGroupId:(NSString *)groupId;

/// 清空SDK中所有的群名片信息缓存
/// 
/// 使用此方法，会清空SDK中所有的群名片信息缓存。
/// 但是处于性能和使用场景权衡，SDK不会在当前View立即自动刷新（会在切换到其他View的时候再刷新所显示的群名片信息）。
/// 如果您想立即刷新，您可以在会话列表或者会话页面reload强制刷新。
- (void)clearGroupUserInfoCache;

#pragma mark 群成员信息提供者

/// 群成员信息提供者
/// 
/// 如果您使用了 @ 功能，SDK需要通过您实现的群用户成员提供者，获取群组中的用户列表。
@property (nonatomic, weak, nullable) id<RCIMGroupMemberDataSource> groupMemberDataSource;

#pragma mark 高质量语音消息自动下载

/// 在线时是否自动下载高质量语音消息
/// 
/// 默认为 YES
@property (nonatomic, assign) BOOL automaticDownloadHQVoiceMsgEnable;

#pragma mark - 公众号信息提供者

/// 公众号信息提供者
///
/// SDK需要通过您实现公众号信息提供者，获取公众号信息并显示。
@property (nonatomic, weak, nullable) id<RCIMPublicServiceProfileDataSource> publicServiceInfoDataSource;

#pragma mark - 网页展示模式

/// 点击Cell中的URL时，优先使用 WebView 还是 SFSafariViewController 打开。
/// 
/// 默认为NO。
/// - 如果设置为YES，将使用WebView打开URL链接，
/// 则您需要在 App 的 `Info.plist` 的 `NSAppTransportSecurity` 中增加 `NSAllowsArbitraryLoadsInWebContent` 和 `NSAllowsArbitraryLoads` 字段，并在苹果审核的时候提供额外的说明。
/// - 如果设置为NO，将优先使用SFSafariViewController，在iOS 8及之前的系统中使用WebView，在审核的时候不需要提供额外说明。
/// 
/// 更多内容可以参考：[apple 官方文档](https://developer.apple.com/library/content/documentation/General/Reference/InfoPlistKeyReference/Articles/CocoaKeys.html#//apple_ref/doc/uid/TP40009251-SW55)
@property (nonatomic, assign) BOOL embeddedWebViewPreferred;

#pragma mark - Extension module

/// 设置Extension Module的URL scheme。
/// - Parameter scheme:      URL scheme
/// - Parameter moduleName:  Extension module name
/// 
/// 有些第三方扩展需要打开其他应用（比如使用支付宝进行支付），然后等待返回结果。因此首先要为第三方扩展设置一个URL
/// scheme并加入到info.plist中，然后再告诉该扩展模块scheme。
- (void)setScheme:(NSString *)scheme forExtensionModule:(NSString *)moduleName;

/// 第三方扩展处理openUrl
/// 
/// - Parameter url:     url
/// - Returns: YES处理，NO未处理。
- (BOOL)openExtensionModuleUrl:(NSURL *)url;

/// 获取 SDK 版本号
/// - Returns: SDK 版本号
+ (NSString *)getVersion;

@end

NS_ASSUME_NONNULL_END
