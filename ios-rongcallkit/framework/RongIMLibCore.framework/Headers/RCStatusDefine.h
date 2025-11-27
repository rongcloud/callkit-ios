/**
 * Copyright (c) 2014-2015, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */

//  RCStatusDefine.h
//  Created by Heq.Shinoda on 14-4-21.

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCErrorCode.h>
#ifndef __RCStatusDefine
#define __RCStatusDefine

#pragma mark - 错误码相关

typedef RCErrorCode RCConnectErrorCode;

typedef NS_ENUM(NSInteger, RCDBErrorCode) {
    RCDBOpenSuccess = 0,
    RCDBOpenFailed = 33002,
};

#pragma mark - 连接状态

#pragma mark RCConnectionStatus - 网络连接状态码
/// 网络连接状态码
typedef NS_ENUM(NSInteger, RCConnectionStatus) {
    /// 未知状态
    /// 建立连接中出现异常的临时状态，SDK 会做好自动重连，开发者无须处理。
    ConnectionStatus_UNKNOWN = -1,

    /// 连接成功
    ConnectionStatus_Connected = 0,

    /// 连接过程中，当前设备网络不可用
    /// 当网络恢复可用时，SDK 会做好自动重连，开发者无须处理。
    ConnectionStatus_NETWORK_UNAVAILABLE = 1,

    /// 当前用户在其他设备上登录，此设备被踢下线
    ConnectionStatus_KICKED_OFFLINE_BY_OTHER_CLIENT = 6,

    /// 连接中
    ConnectionStatus_Connecting = 10,

    /// 连接失败或未连接
    ConnectionStatus_Unconnected = 11,

    /// 已登出
    ConnectionStatus_SignOut = 12,

    /// 连接暂时挂起（多是由于网络问题导致），SDK 会在合适时机进行自动重连
    ConnectionStatus_Suspend = 13,

    /// 自动连接超时，SDK 将不会继续连接，用户需要做超时处理，再自行调用 connectWithToken 接口进行连接
    ConnectionStatus_Timeout = 14,

    /// Token 无效
    /// Token 无效一般有两种原因。一是 token 错误，请您检查客户端初始化使用的 AppKey 和您服务器获取 token 使用的 AppKey
    /// 是否一致；二是 token 过期，是因为您在开发者后台设置了 token 过期时间，您需要请求您的服务器重新获取 token
    /// 并再次用新的 token 建立连接。
    ConnectionStatus_TOKEN_INCORRECT = 15,

    /// 与服务器的连接已断开，用户被封禁
    ConnectionStatus_DISCONN_EXCEPTION = 16,

    /// proxy 服务不可用，SDK 将不会继续连接，用户需要检查 proxy 是否可用，再自行调用 connectWithToken 接口进行连接
    ConnectionStatus_PROXY_UNAVAILABLE = 17,

    /// 用户账号已销户，不再进行连接
    ConnectionStatus_USER_ABANDON = 19
};

#pragma mark RCNetworkStatus - 当前所处的网络
/// 当前所处的网络
typedef NS_ENUM(NSUInteger, RCNetworkStatus) {
    /// 当前网络不可用
    RC_NotReachable = 0,

    /// 当前处于 WiFi 网络
    RC_ReachableViaWiFi = 1,

    /// 移动网络
    RC_ReachableViaWWAN = 2,
};

#pragma mark RCSDKRunningMode - SDK当前所处的状态

/// SDK 当前所处的状态
typedef NS_ENUM(NSUInteger, RCSDKRunningMode) {
    /// 后台运行状态
    RCSDKRunningMode_Background = 0,

    /// 前台运行状态
    RCSDKRunningMode_Foreground = 1
};

#pragma mark - 会话相关

#pragma mark RCConversationType - 会话类型

/// 会话类型
typedef NS_ENUM(NSUInteger, RCConversationType) {
    /// 单聊
    ConversationType_PRIVATE = 1,

    /// 讨论组
    ConversationType_DISCUSSION = 2,

    /// 群组
    ConversationType_GROUP = 3,

    /// 聊天室
    ConversationType_CHATROOM = 4,

    /// 客服
    ConversationType_CUSTOMERSERVICE = 5,

    /// 系统会话
    ConversationType_SYSTEM = 6,

    /// 应用内公众服务会话
    ///
    /// 客服 2.0 使用应用内公众服务会话（ConversationType_APPSERVICE）的方式实现。
    /// 即客服 2.0  会话是其中一个应用内公众服务会话，这种方式我们目前不推荐，
    /// 请尽快升级到新客服，升级方法请参考官网的客服文档。文档链接
    /// https://docs.rongcloud.cn/services/public/app/prepare/
    ConversationType_APPSERVICE = 7,

    /// 跨应用公众服务会话
    ConversationType_PUBLICSERVICE = 8,

    /// 推送服务会话
    ConversationType_PUSHSERVICE = 9,

    /// 超级群
    ConversationType_ULTRAGROUP = 10,

    /// 加密会话（仅对部分私有云用户开放，公有云用户不适用）
    ConversationType_Encrypted = 11,
    /// RTC 会话
    ConversationType_RTC = 12,

    /// 无效类型
    ConversationType_INVALID

};

#pragma mark RCConversationNotificationStatus - 会话提醒状态
/// 会话提醒状态
typedef NS_ENUM(NSUInteger, RCConversationNotificationStatus) {
    /// 免打扰
    DO_NOT_DISTURB = 0,

    /// 新消息提醒
    NOTIFY = 1,
};

#pragma mark RCReadReceiptMessageType - 消息回执
/// 已读状态消息类型
typedef NS_ENUM(NSUInteger, RCReadReceiptMessageType) {
    /// 根据会话来更新未读消息状态
    RC_ReadReceipt_Conversation = 1,
};

#pragma mark - 消息相关

#pragma mark RCMessagePersistent - 消息的存储策略
/// 消息的存储策略
typedef NS_ENUM(NSUInteger, RCMessagePersistent) {
    /// 在本地不存储，不计入未读数
    MessagePersistent_NONE = 0,

    /// 在本地只存储，但不计入未读数
    MessagePersistent_ISPERSISTED = 1,

    /// 在本地进行存储并计入未读数
    MessagePersistent_ISCOUNTED = 3,

    /// 在本地不存储，不计入未读数，并且如果对方不在线，服务器会直接丢弃该消息，对方如果之后再上线也不会再收到此消息。
    /// 一般用于发送输入状态之类的消息。
    MessagePersistent_STATUS = 16
};

#pragma mark RCMessageDirection - 消息的方向
/// 消息的方向
typedef NS_ENUM(NSUInteger, RCMessageDirection) {
    /// 发送
    MessageDirection_SEND = 1,

    /// 接收
    MessageDirection_RECEIVE = 2
};

#pragma mark RCSentStatus - 消息的发送状态
/// 消息的发送状态
typedef NS_ENUM(NSUInteger, RCSentStatus) {
    /// 发送中
    SentStatus_SENDING = 10,

    /// 发送失败
    SentStatus_FAILED = 20,

    /// 已发送成功
    SentStatus_SENT = 30,

    /// 对方已接收
    SentStatus_RECEIVED = 40,

    /// 对方已阅读
    SentStatus_READ = 50,

    /// 对方已销毁
    SentStatus_DESTROYED = 60,

    /// 发送已取消
    SentStatus_CANCELED = 70,

    /// 无效类型
    SentStatus_INVALID
};

#pragma mark RCReceivedStatus - 消息的接收状态
/// 消息的接收状态
typedef NS_ENUM(NSUInteger, RCReceivedStatus) {
    /// 未读
    ReceivedStatus_UNREAD = 0,

    /// 已读
    ReceivedStatus_READ = 1,

    /// 已听
    /// 仅用于语音消息
    ReceivedStatus_LISTENED = 2,

    /// 已下载
    ReceivedStatus_DOWNLOADED = 4,

    /// 该消息已被同时在线或之前登录的其他设备接收。只要任何其他设备先收到该消息，当前设备就会有该状态值。
    ReceivedStatus_RETRIEVED = 8,

    /// 该消息是被多端同时收取的。（即其他端正同时登录，一条消息被同时发往多端。客户可以通过这个状态值更新自己的某些 UI
    /// 状态）。
    ReceivedStatus_MULTIPLERECEIVE = 16,

} __deprecated_msg("Use RCReceivedStatusInfo instead");

#pragma mark RCMediaType - 消息内容中多媒体文件的类型
/// 消息内容中多媒体文件的类型
typedef NS_ENUM(NSUInteger, RCMediaType) {
    /// 图片
    MediaType_IMAGE = 1,

    /// 语音
    MediaType_AUDIO = 2,

    /// 视频
    MediaType_VIDEO = 3,

    /// 其他文件
    MediaType_FILE = 4,

    /// 小视频
    MediaType_SIGHT = 5,

    /// 合并转发
    MediaType_HTML = 6
};

#pragma mark RCTypingStatus - 输入状态
typedef NS_ENUM(NSUInteger, RCUltraGroupTypingStatus) {
    /// 正在输入文本
    RCUltraGroupTypingStatusText = 0,
};

#pragma mark RCMediaType - 消息中@提醒的类型
/// @提醒的类型
typedef NS_ENUM(NSUInteger, RCMentionedType) {
    /// @ 所有人
    RC_Mentioned_All = 1,

    /// @ 部分指定用户
    RC_Mentioned_Users = 2,
};

#pragma mark - 消息内容审核配置

typedef NS_ENUM(NSInteger, RCMessageAuditType) {
    /// 不需要审核
    RCMessageAuditTypeDisallow = 0,

    /// 需要审核
    RCMessageAuditTypeAllow = 1,
};


/// 语音消息采样率
typedef NS_ENUM(NSInteger, RCSampleRate) {
    /// 8KHz
    RCSample_Rate_8000 = 1,
    /// 16KHz
    RCSample_Rate_16000 = 2,
};

/// 语音消息类型
typedef NS_ENUM(NSInteger, RCVoiceMessageType) {
    /// 普通音质语音消息
    RCVoiceMessageTypeOrdinary = 1,
    /// 高音质语音消息
    RCVoiceMessageTypeHighQuality = 2,
};

#pragma mark - 公众服务相关

#pragma mark RCPublicServiceType - 公众服务账号类型

/// 公众服务账号类型
typedef NS_ENUM(NSUInteger, RCPublicServiceType) {
    /// 应用内公众服务账号
    RC_APP_PUBLIC_SERVICE = 7,

    /// 跨应用公众服务账号
    RC_PUBLIC_SERVICE = 8,
};

#pragma mark RCSearchType - 公众服务查找匹配方式
/// 公众服务查找匹配方式
typedef NS_ENUM(NSUInteger, RCSearchType) {
    /// 精确匹配
    RC_SEARCH_TYPE_EXACT = 0,

    /// 模糊匹配
    RC_SEARCH_TYPE_FUZZY = 1,

    /// 无效类型
    RCSearchType_INVALID
};

#pragma mark - RCLogLevel - 日志级别
/// 日志级别
typedef NS_ENUM(NSUInteger, RCLogLevel) {

    /// 不输出任何日志
    RC_Log_Level_None = 0,

    /// 只输出错误的日志
    RC_Log_Level_Error = 1,

    /// 输出错误和警告的日志
    RC_Log_Level_Warn = 2,

    /// 输出错误、警告和一般的日志
    RC_Log_Level_Info = 3,

    /// 输出输出错误、警告和一般的日志以及 debug 日志
    RC_Log_Level_Debug = 4,

    /// 输出所有日志
    RC_Log_Level_Verbose = 5,
};

#pragma mark - RCTimestampOrder - 历史消息查询顺序

/// 日志级别
typedef NS_ENUM(NSUInteger, RCTimestampOrder) {
    /// 降序，按照时间戳从大到小
    RC_Timestamp_Desc = 0,

    /// 升序，按照时间戳从小到大
    RC_Timestamp_Asc = 1,
};

#pragma mark - RCPlatform - 在线平台

/// 在线平台
typedef NS_ENUM(NSUInteger, RCPlatform) {
    /// 其它平台
    RCPlatform_Other = 0,

    /// iOS
    RCPlatform_iOS = 1,

    /// Android
    RCPlatform_Android = 2,

    /// Web
    RCPlatform_Web = 3,

    /// PC
    RCPlatform_PC = 4,

    /// 小程序
    RCPlatform_MiniWeb = 5,

    /// 鸿蒙
    RCPlatform_HarmonyOS = 6,
};

#pragma mark - RCPushLanguageType - push 语言设置

/// push 语言设置
typedef NS_ENUM(NSUInteger, RCPushLanguage) {
    /// 英文
    RCPushLanguage_EN_US = 1,
    /// 中文
    RCPushLanguage_ZH_CN = 2,
    /// 阿拉伯文
    RCPushLanguage_AR_SA
};

/// push 语言设置
typedef NS_ENUM(NSUInteger, RCPushLauguage) {
    /// 英文
    RCPushLauguage_EN_US = 1,
    /// 中文
    RCPushLauguage_ZH_CN = 2,
    /// 阿拉伯文
    RCPushLauguage_AR_SA
} __deprecated_msg("Use RCPushLanguage instead");

#pragma mark - RCMessageBlockType - 消息被拦截类型

/// 消息被拦截类型
typedef NS_ENUM(NSUInteger, RCMessageBlockType) {
    /// 全局敏感词：命中了融云内置的全局敏感词
    RCMessageBlockTypeGlobal = 1,

    /// 自定义敏感词拦截：命中了客户在融云自定义的敏感词
    RCMessageBlockTypeCustom = 2,

    /// 第三方审核拦截：命中了第三方（数美）或消息回调服务决定不下发的状态
    RCMessageBlockTypeThirdParty = 3,
};

typedef NS_ENUM(NSInteger, RCPushNotificationLevel) {
    /// 全部消息通知（接收全部消息通知 -- 显示指定关闭免打扰功能）
    /// 超级群设置全部消息通知时
    /// @ 消息一定收到推送通知
    /// 普通消息的推送频率受到超级群服务端默认推送频率设置的影响，无法做到所有普通消息都通知
    RCPushNotificationLevelAllMessage = -1,
    /// 未设置（向上查询群或者 APP 级别设置）,存量数据中 0 表示未设置
    RCPushNotificationLevelDefault = 0,
    /// 群聊，超级群 @所有人 或者 @成员列表有自己 时通知；单聊代表消息不通知
    RCPushNotificationLevelMention = 1,
    /// 群聊，超级群 @成员列表有自己时通知，@所有人不通知；单聊代表消息不通知
    RCPushNotificationLevelMentionUsers = 2,
    /// 群聊，超级群 @所有人通知，其他情况都不通知；单聊代表消息不通知
    RCPushNotificationLevelMentionAll = 4,
    /// 消息通知被屏蔽，即不接收消息通知
    RCPushNotificationLevelBlocked = 5,
};

typedef NS_ENUM(NSInteger, RCPushNotificationQuietHoursLevel) {
    /// 未设置（向上查询群或者 APP 级别设置）
    RCPushNotificationQuietHoursLevelDefault = 0,
    /// 群聊超级群仅 @ 消息通知，单聊代表消息不通知
    RCPushNotificationQuietHoursLevelMention = 1,
    /// 消息通知被屏蔽，即不接收消息通知
    RCPushNotificationQuietHoursLevelBlocked = 5,
};

typedef NS_ENUM(NSInteger, RCUltraGroupChannelType) {
    /// 超级群公有频道
    RCUltraGroupChannelTypePublic = 0,
    /// 超级群私有频道
    RCUltraGroupChannelTypePrivate = 1
};


typedef NS_ENUM(NSInteger, RCUltraGroupChannelChangeType) {
    /// 超级群公有频道变成了私有频道
    RCUltraGroupChannelChangeTypePublicToPrivate = 2,
    /// 超级群私有频道变成了共有频道
    RCUltraGroupChannelChangeTypePrivateToPublic = 3,
    /// 超级群公有频道变成了私有频道，但是当前用户不再该私有频道中
    RCUltraGroupChannelChangeTypePublicToPrivateUserNotIn = 6
};

/// 排序。
///
/// - Since: 5.20.0
typedef NS_ENUM(NSInteger, RCOrder) { RCOrderDescending = 0, RCOrderAscending };

@class RCConversation;
typedef void (^RCConversationListCompletion)(NSArray<RCConversation *> *conversations, RCErrorCode code);

@class RCMessage;
typedef void (^RCMessageListCompletion)(NSArray<RCMessage *> *messages, RCErrorCode code);
typedef void (^RCSearchMessageListCompletion)(NSArray<RCMessage *> *messages, NSUInteger matchCount, RCErrorCode code);

#pragma mark - 翻译

/// 翻译类型。
///
/// - Since: 5.24.0
typedef NS_ENUM(NSInteger, RCTranslateMode) {
    /// 高速翻译，主要采用机器翻译。
    RCTranslateModeMechanical = 0,
    /// 智能翻译。
    RCTranslateModeIntelligent = 1
};

/// 会话翻译方式。
///
/// - Since: 5.24.0
typedef NS_ENUM(NSInteger, RCTranslateStrategy) {
    /// 默认，会跟随用户级别的自动翻译方式。
    RCTranslateStrategyDefault = 0,
    /// 自动翻译。
    RCTranslateStrategyAutoOn = 1,
    /// 手动翻译。
    RCTranslateStrategyAutoOff = 2,
};

@class RCTranslateItem;

/**
 消息已读回执功能版本
 */
typedef NS_ENUM(NSInteger, RCMessageReadReceiptVersion) {
    /**
     消息已读回执功能版本1
     */
    RCMessageReadReceiptVersion1 = 0,
    /**
     消息已读回执功能版本2
     */
    RCMessageReadReceiptVersion2 = 1,
    /**
     消息已读回执功能版本4
     */
    RCMessageReadReceiptVersion4 = 3,
    /**
     消息读回执功能版本5
     */
    RCMessageReadReceiptVersion5 = 4,
};




#endif
