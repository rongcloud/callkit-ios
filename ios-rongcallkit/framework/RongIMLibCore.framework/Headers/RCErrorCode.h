/**
 * Copyright (c) 2014-2023, RongCloud.
 * All rights reserved.
 */

// RCErrorCode.h
// 融云 IM 错误码
// 本文件由 ErrorCodeGenerator 自动生成，请勿擅自修改

#import <Foundation/Foundation.h>

#ifndef RCErrorCode_h
#define RCErrorCode_h

typedef NS_ENUM(NSInteger, RCErrorCode) {
    /// 成功
    /// 
    RC_SUCCESS = 0,

    /// 已被对方加入黑名单，消息发送失败
    /// 
    REJECTED_BY_BLACKLIST = 405,

    /// 系统会话不支持发送该消息
    /// 
    /// - Since: 5.6.2
    RC_CONVERSATION_NOT_SUPPORT_MESSAGE = 20109,

    ///  appkey的数据中心与请求云控的数据中心不匹配
    /// 
    /// - Since: 5.6.6
    CLOUD_DATA_CENTER_INVALID = 20512,

    /// 发送消息频率过高，1 秒钟最多只允许发送 5 条消息
    /// 
    SEND_MSG_FREQUENCY_OVERRUN = 20604,

    /// 操作被禁止，此错误码已被弃用
    /// 
    RC_OPERATION_BLOCKED = 20605,

    /// 操作不支持，仅私有云有效，服务端禁用了该操作
    /// 
    RC_OPERATION_NOT_SUPPORT = 20606,

    /// 请求超出了调用频率限制，请稍后再试
    /// 
    RC_REQUEST_OVERFREQUENCY = 20607,

    /// 不在讨论组
    /// 
    NOT_IN_DISCUSSION = 21406,

    /// 发送的消息中包含敏感词 （发送方发送失败，接收方不会收到消息）
    /// 
    RC_MSG_BLOCKED_SENSITIVE_WORD = 21501,

    /// 消息中敏感词已经被替换 （接收方可以收到被替换之后的消息）
    /// 
    RC_MSG_REPLACED_SENSITIVE_WORD = 21502,

    /// 超级群扩展消息，但是原始消息不存在。
    /// 
    /// - Since: 5.2.0
    RC_ORIGINAL_MESSAGE_NOT_EXIST = 22201,

    /// 超级群扩展消息，但是原始消息不支持扩展
    /// 
    /// - Since: 5.2.0
    RC_ORIGINAL_MESSAGE_CANT_EXPAND = 22202,

    /// 超级群扩展消息，扩展内容格式错误
    /// 
    /// - Since: 5.2.0
    RC_MESSAGE_EXPAND_FORMAT_ERROR = 22203,

    /// 超级群扩展消息，无操作权限
    /// 
    /// - Since: 5.2.0
    RC_MESSAGE_EXPAND_NOT_AUTHORIZED = 22204,

    /// 不在该群组中
    /// 
    NOT_IN_GROUP = 22406,

    /// 在群组中已被禁言。
    /// 
    FORBIDDEN_IN_GROUP = 22408,

    /// 不在该聊天室中。
    /// 
    NOT_IN_CHATROOM = 23406,

    /// 聊天室禁言白名单人数超限(最多5个)
    /// 创建聊天室时,禁言白名单用户列表，支持批量设置，最多不超过 20 个
    /// 
    RC_GET_USER_INFO_ERROR = 23407,

    /// 在该聊天室中已被禁言
    /// 
    FORBIDDEN_IN_CHATROOM = 23408,

    /// 已被踢出并禁止加入聊天室。被禁止的时间取决于服务端调用踢出接口时传入的时间。
    /// 
    KICKED_FROM_CHATROOM = 23409,

    /// 聊天室不存在
    /// 
    RC_CHATROOM_NOT_EXIST = 23410,

    /// 聊天室成员超限，开发者可以提交工单申请聊天室人数限制变更。
    /// 
    RC_CHATROOM_IS_FULL = 23411,

    /// 聊天室接口参数无效。请确认参数是否为空或者有效。
    /// 
    RC_PARAMETER_INVALID_CHATROOM = 23412,

    /// 聊天室云存储业务未开通
    /// 
    RC_ROAMING_SERVICE_UNAVAILABLE_CHATROOM = 23414,

    /// 聊天室的 KV 属性个数超限，单个聊天室默认上限为 100 个
    /// 
    RC_EXCCED_MAX_KV_SIZE = 23423,

    /// 没有权限修改聊天室中已存在的属性值
    /// 
    RC_TRY_OVERWRITE_INVALID_KEY = 23424,

    /// 超过聊天室中状态设置频率，1 个聊天室 1 秒钟最多设置和删除状态 100 次
    /// 
    RC_EXCCED_MAX_CALL_API_SIZE = 23425,

    /// 聊天室属性自定义设置，您可以在开发者后台免费基础功能页面中开启该功能。
    /// 
    RC_KV_STORE_NOT_AVAILABLE = 23426,

    /// 聊天室属性不存在
    /// 
    RC_KEY_NOT_EXIST = 23427,

    /// 聊天室批量设置或删除KV部分不成功
    /// 
    RC_KV_STORE_NOT_ALL_SUCCESS = 23428,

    /// 聊天室批量设置或删除KV数量超限（最多一次10条）
    /// 
    RC_KV_STORE_OUT_OF_LIMIT = 23429,

    /// 聊天室设置 KV 失败，出现在两人或者多端同时操作一个 KV。 如果出现该错误，为避免和其他端同时操作，请延时一定时间再试
    /// 
    RC_KV_CONCURRENT_SET_ERROR = 23431,

    /// 加入聊天室附加信息长度超限，默认最大长度为 128 个字符，服务可配置
    /// 
    /// - Since: 5.10.3
    RC_CHATROOM_EXTRA_SIZE_LIMIT_EXCEED = 23437,

    /// 没有设置该用户托管属性的权限
    /// 
    /// - Since: 5.10.0
    RC_USER_PROFILE_KEY_NOT_ALLOW_SDK_SET = 24360,

    /// 用户托管基本属性的key列表中没有此key
    /// 
    /// - Since: 5.10.0
    RC_USER_PROFILE_KEY_NOT_EXIST = 24361,

    /// 用户托管扩展属性的 key 列表中没有此 key
    /// 
    /// - Since: 5.10.0
    RC_USER_PROFILE_EXT_KEY_NOT_EXIST = 24362,

    /// 超过了可以设置的用户托管扩展属性的最大上限
    /// 
    /// - Since: 5.10.0
    RC_USER_PROFILE_EXT_KV_COUNT_EXCEED_LIMIT = 24363,

    /// 用户托管基本属性或扩展属性的Value，字符超过最大上限
    /// 
    /// - Since: 5.10.0
    RC_USER_PROFILE_VALUE_LENGTH_EXCEED_LIMIT = 24364,

    /// 批量查询用户托管资料的数量超过了可以查询的上限 100 个
    /// 
    /// - Since: 5.10.0
    RC_USER_PROFILE_QUERY_COUNT_EXCEED_LIMIT = 24365,

    /// 没有此用户
    /// 
    /// - Since: 5.10.0
    RC_USER_PROFILE_USER_NOT_EXIST = 24366,

    /// 用户托管此属性Value只能是数字
    /// 
    /// - Since: 5.10.0
    RC_USER_PROFILE_VALUE_CAN_ONLY_BE_NUMBERS = 24367,

    /// 用户托管此属性 Value 值超过设置取值范围
    /// 
    /// - Since: 5.10.0
    RC_USER_PROFILE_VALUE_EXCEED_RANGE = 24368,

    /// 未开启用户信息托管功能
    /// 
    /// - Since: 5.10.0
    RC_USER_PROFILE_SERVICE_UNAVAILABLE = 24369,

    /// 超级群功能未开通
    /// 
    /// - Since: 5.2.0
    RC_ULTRA_GROUP_DISABLED = 24401,

    /// 超级群服务异常
    /// 
    /// - Since: 5.2.0
    RC_ULTRA_GROUP_SERVICE_ABNORMAL = 24402,

    /// 超级群参数错误
    /// 
    /// - Since: 5.2.0
    RC_ULTRA_GROUP_PARAMETER_ERROR = 24403,

    /// 超级群未知异常
    /// 
    /// - Since: 5.2.0
    RC_ULTRA_GROUP_UNKNOWN_ERROR = 24404,

    /// 非超级群成员
    /// 
    /// - Since: 5.2.0
    RC_NOT_IN_ULTRA_GROUP = 24406,

    /// 超级群成员禁言
    /// 
    /// - Since: 5.2.0
    RC_FORBIDDEN_IN_ULTRA_GROUP = 24408,

    /// 超级群不存在
    /// 
    /// - Since: 5.2.0
    RC_ULTRA_GROUP_NOT_EXIST = 24410,

    /// 超级群成员超限制
    /// 
    /// - Since: 5.2.0
    RC_ULTRA_GROUP_MEMBERS_EXCEED_LIMIT = 24411,

    /// 用户加入超级群数量超限
    /// 
    /// - Since: 5.2.0
    RC_ULTRA_GROUP_NUMBER_EXCEED_LIMIT = 24412,

    /// 创建超级群频道，频道数超限
    /// 
    /// - Since: 5.2.0
    RC_ULTRA_GROUP_CHANNELS_EXCEED_LIMIT = 24413,

    /// 超级群频道 ID 不存在
    /// 
    /// - Since: 5.2.0
    RC_ULTRA_GROUP_CHANNEL_ID_NOT_EXIST = 24414,

    /// 超级群频道发送消息超限：超级群下每个频道有消息发送频率限制，默认每秒 30 条 频道内每秒发送消息总量超过限制会收到该错误码，建议延时发送或重试发送
    /// 
    /// - Since: 5.2.1
    RC_ULTRA_GROUP_CHANNEL_MESSAGE_EXCEED_LIMIT = 24415,

    /// 用户不在超级群私有频道中
    /// 
    /// - Since: 5.2.4
    RC_ULTRA_GROUP_USER_NOT_IN_PRIVATE_CHANNEL = 24416,

    /// 撤回消息参数无效，请确认撤回消息参数是否正确的填写
    /// 
    RC_RECALLMESSAGE_PARAMETER_INVALID = 25101,

    /// 未开通单群聊云存储服务
    /// 
    RC_MESSAGE_STORAGE_SERVICE_UNAVAILABLE = 25102,

    /// 未知异常
    /// 
    /// - Since: 5.6.7
    RC_SERVER_UNKNOWN_ERROR = 25104,

    /// IMLib 撤回消息可以撤回自己发送的消息和别人发送的消息，IM 服务有开关，控制只可以撤回自己发送的消息，当服务该开关打开时，撤回别人的消息会报这个错误。
    /// 
    /// - Since: 5.2.4
    RC_RECALL_MESSAGE_USER_INVALID = 25107,

    /// 托管服务异常
    /// 
    /// - Since: 5.12.0
    RC_ENTRUST_SERVER_ERROR = 25402,

    /// 托管服务参数错误
    /// 
    /// - Since: 5.12.0
    RC_ENTRUST_SERVER_PARAMETER_ERROR = 25403,

    /// 非法操作，非群主修改群权限相关，msg中返回传的对应的key
    /// 
    /// - Since: 5.12.0
    RC_GROUP_ILLEGAL_ERROR = 25404,

    /// 没有权限操作
    /// 
    /// - Since: 5.12.0
    RC_GROUP_AUTHORITY_ERROR = 25405,

    /// 参数异常，存在长度超限
    /// 
    /// - Since: 5.12.0
    RC_GROUP_PARAMETER_LENGTH_EXCEED_LIMIT = 25406,

    /// 参数异常，非法字符
    /// 
    /// - Since: 5.12.0
    RC_GROUP_PARAMETER_FORMAT_ERROR = 25407,

    /// 参数值必须是数字
    /// 
    /// - Since: 5.12.0
    RC_GROUP_PARAMETER_VALUE_CAN_ONLY_BE_NUMBERS = 25408,

    /// 群组 ID 已存在
    /// 
    /// - Since: 5.12.0
    RC_GROUP_ID_ALREADY_EXIST = 25409,

    /// 群 ID 不存在
    /// 
    /// - Since: 5.12.0
    RC_GROUP_ID_NOT_EXIST = 25410,

    /// 群成员超限
    /// 
    /// - Since: 5.12.0
    RC_GROUP_MEMBERS_COUNT_EXCEED_LIMIT = 25411,

    /// 群成员 ID 已在当前群组中
    /// 
    /// - Since: 5.12.0
    RC_GROUP_MEMBERS_ALREADY_IN_GROUP = 25412,

    /// 不允许通过 SDK 进行此操作
    /// 
    /// - Since: 5.12.0
    RC_GROUP_NOT_ALLOW_SDK_OPERATION = 25413,

    /// 不允许任何人加入，无法加入群组
    /// 
    /// - Since: 5.12.0
    RC_GROUP_NOT_ALLOW_JOIN = 25414,

    /// 扩展信息 Key 值不存在
    /// 
    /// - Since: 5.12.0
    RC_GROUP_EXT_KEY_NOT_EXIST = 25415,

    /// 查询频率超限
    /// 
    /// - Since: 5.12.0
    RC_GROUP_REQUEST_OVERFREQUENCY = 25416,

    /// 群主不能被踢出/退出群组
    /// 
    /// - Since: 5.12.0
    RC_GROUP_OWNER_NOT_ALLOW_QUIT_OR_KICK = 25417,

    /// 用户ID不在群组中
    /// 
    /// - Since: 5.12.0
    RC_GROUP_USER_NOT_IN_GROUP = 25418,

    /// 管理员/关注 人数超过上限
    /// 
    /// - Since: 5.12.0
    RC_GROUP_MANAGER_OR_FOLLOW_COUNT_EXCEED_LIMIT = 25419,

    /// 用户 ID 不在当前群管理员
    /// 
    /// - Since: 5.12.0
    RC_GROUP_USER_IS_NOT_MANAGER_IN_GROUP = 25420,

    /// 无对应群 ID 和用户 ID 的邀请请求
    /// 
    /// - Since: 5.12.0
    RC_GROUP_APPLICATION_NOT_EXIST = 25421,

    /// 查询群信息个数超限
    /// 
    /// - Since: 5.12.0
    RC_GROUP_QUERY_GROUP_COUNT_EXCEED_LIMIT = 25422,

    /// 群名称不能为空
    /// 
    /// - Since: 5.12.0
    RC_GROUP_NAME_INVALID = 25423,

    /// 申请进群需要等待管理员审批
    /// 
    /// - Since: 5.12.0
    RC_GROUP_JOIN_GROUP_NEED_MANAGER_ACCEPT = 25424,

    /// 群主不支持设置为管理员
    /// 
    /// - Since: 5.12.0
    RC_GROUP_OWNER_NOT_ALLOW_BE_MANAGER = 25425,

    /// 邀请人进群时没有权限
    /// 
    /// - Since: 5.12.0
    RC_GROUP_NO_INVITE_PERMISSION = 25426,

    /// 邀请进群需要被邀请人同意
    /// 
    /// - Since: 5.12.0
    RC_GROUP_NEED_INVITEE_ACCEPT = 25427,

    /// 管理员或群主处理请求时，别的管理员已处理
    /// 
    /// - Since: 5.12.0
    RC_GROUP_APPLICATION_ALREADY_HANDLE = 25428,

    /// 老的群不支持调用托管接口，需要导入后才能调用
    /// 
    /// - Since: 5.12.0
    RC_GROUP_OLD_GROUP_NOT_ENTRUST = 25429,

    /// 群ID不合法，包含特殊字符
    /// 
    /// - Since: 5.12.0
    RC_GROUP_ID_INVALID = 25430,

    /// pagetoken解析失败
    /// 
    /// - Since: 5.12.0
    RC_PAGE_TOKEN_PARSING_FAILED = 25432,

    /// 已经互为好友，操作无效
    /// 
    /// - Since: 5.12.0
    RC_FRIEND_ALREADY_FRIEND = 25460,

    /// 待对方同意后才能加为好友
    /// 
    /// - Since: 5.12.0
    RC_FRIEND_NEED_ACCEPT = 25461,

    /// 在目标用户黑名单中，不能添加好友
    /// 
    /// - Since: 5.12.0
    RC_FRIEND_IN_OTHER_BLACK_LIST = 25462,

    /// 不在目标用户白名单中，不能添加好友
    /// 
    /// - Since: 5.12.0
    RC_FRIEND_NOT_IN_OTHER_WHITE_LIST = 25463,

    /// 目标用户在当前用户黑名单中，不能添加好友
    /// 
    /// - Since: 5.12.0
    RC_FRIEND_IN_MY_BLACK_LIST = 25464,

    /// 不在当前用户白名单中，不能添加好友
    /// 
    /// - Since: 5.12.0
    RC_FRIEND_NOT_IN_MY_WHITE_LIST = 25465,

    /// 操作无效，该好友请求不存在或已经过期
    /// 
    /// - Since: 5.12.0
    RC_FRIEND_APPLICATION_NOT_EXIST = 25466,

    /// 当前用户好友数超出上限
    /// 
    /// - Since: 5.12.0
    RC_FRIEND_MY_FRIEND_COUNT_EXCEED_LIMIT = 25467,

    /// 目标用户好友数超出上限
    /// 
    /// - Since: 5.12.0
    RC_FRIEND_OTHER_FRIEND_COUNT_EXCEED_LIMIT = 25468,

    /// 非好友关系，不能执行此操作
    /// 
    /// - Since: 5.12.0
    RC_FRIEND_NOT_FRIEND = 25469,

    /// 好友自定义属性超出上限
    /// 
    /// - Since: 5.12.0
    RC_FRIEND_FIELDS_LENGTH_EXCEED_LIMIT = 25470,

    /// 对方设置了不允许加为好友
    /// 
    /// - Since: 5.12.0
    RC_FRIEND_OTHER_NOT_ALLOW_ADD_FRIEND = 25471,

    /// 好友不存在
    /// 
    /// - Since: 5.12.0
    RC_FRIEND_NOT_EXIST = 25472,

    /// 不能添加自己为好友
    /// 
    /// - Since: 5.12.0
    RC_FRIEND_NOT_ALLOW_ADD_SELF = 25473,

    /// 用户级设置服务  请求参数不合法
    /// 
    RC_PUSHSETTING_PARAMETER_INVALID = 26001,

    /// 表示客户端版本号低，需要同步版本号，可以提交工单申请打开用户级别配置开关
    /// 
    RC_SETTING_SYNC_FAILED = 26002,

    /// 服务内部错误
    /// 
    RC_SERVICE_INTERNAL_ERROR = 26003,

    /// 用户会话标签个数超限，最多支持添加 20 个标签
    /// 
    RC_TAG_LIMIT_EXCEED = 26004,

    /// 未开通v4已读回执
    /// 
    /// - Since: 5.6.7
    RC_READ_RECEIPT_V4_INVALID = 26005,

    /// 未开通会话驱动
    /// 
    /// - Since: 5.6.7
    RC_SERVER_DRIVE_UNREAD_COUNT_INVALID = 26006,

    /// 消息 id 顺序错误
    /// 
    /// - Since: 5.6.7
    RC_SERVER_PARAMETER_MESSAGEUIDS_CONFUSED = 26007,

    /// 上报时间不支持同步
    /// 
    /// - Since: 5.6.9
    RC_SERVER_PARAMETER_TIMESTAMP_NOT_SUPPORT_SYNC = 26008,

    /// 消息id不合法
    /// 
    /// - Since: 5.6.7
    RC_SERVER_PARAMETER_MESSAGEUID_INVALID = 26009,

    /// 参数有误
    /// 
    /// - Since: 5.6.7
    RC_SERVER_PARAMETER_INVALID = 26010,

    /// 未开启在线状态订阅功能
    /// 
    RC_SUBSCRIBE_ONLINE_SERVICE_UNAVAILABLE = 26020,

    /// 用户被订阅量达到上限， 详细查看开发文档。
    /// 
    /// - Solution 比如A/B/C等很多用户都订阅了用户X，  如果再有a/b/c等继续订阅X， 用户X的被订阅量超过上限
    RC_BESUBSCRIBED_USERIDS_COUNT_EXCEED_LIMIT = 26021,

    /// 订阅用户数达到上限， 详细查看开发文档。
    /// 
    RC_SUBSCRIBED_USERIDS_EXCEED_LIMIT = 26022,

    /// 小视频服务未开通。可以在融云开发者后台中开启该服务。
    /// (已经不需要开通)
    /// 
    RC_SIGHT_SERVICE_UNAVAILABLE = 26101,

    /// 上传文件超过最大限制
    /// 
    RC_FILE_SIZE_EXCEED_LIMIT = 26106,

    /// 开启限制未传 size 参数
    /// 
    INVALID_PARAMETER_SIZE_NOT_FOUND = 26107,

    /// (MP)公众号默认已关注，针对会话类型：ConversationType_APP_PUBLIC_SERVICE
    /// 
    RC_APP_PUBLICSERVICE_DEFFOLLOWED = 29102,

    /// (MP)公众号已关注，针对会话类型：ConversationType_APP_PUBLIC_SERVICE
    /// 
    RC_APP_PUBLICSERVICE_FOLLOWED = 29103,

    /// 公众号默认已取消关注，针对会话类型：ConversationType_APP_PUBLIC_SERVICE
    /// (错误码已废弃)
    /// 
    RC_APP_PUBLICSERVICE_DEFUNFOLLOWED = 29104,

    /// (MP)公众号已经取消关注，针对会话类型：ConversationType_APP_PUBLIC_SERVICE
    /// 
    RC_APP_PUBLICSERVICE_UNFOLLOWED = 29105,

    /// (MP)未关注此公众号，针对会话类型：ConversationType_APP_PUBLIC_SERVICE
    /// 
    RC_APP_PUBLICSERVICE_UNFOLLOW = 29106,

    /// 无效的公众号。(由会话类型和 Id 所标识的公众号会话是无效的)
    /// 针对会话类型：ConversationType_PUBLIC_SERVICE
    /// 
    RC_APP_PUBLICSERVICE_ERROR_TYPE = 29201,

    /// 公众号默认已关注，针对会话类型：ConversationType_PUBLIC_SERVICE
    /// 
    RC_PUBLICSERVICE_DEFFOLLOWED = 29202,

    /// 公众号已关注，针对会话类型：ConversationType_PUBLIC_SERVICE
    /// 
    RC_PUBLICSERVICE_FOLLOWED = 29203,

    /// 公众号默认已取消关注，针对会话类型：ConversationType_PUBLIC_SERVICE
    /// (错误码已废弃)
    /// 
    RC_PUBLICSERVICE_DEFUNFOLLOWED = 29204,

    /// 公众号已经取消关注，针对会话类型：ConversationType_PUBLIC_SERVICE
    /// 
    RC_PUBLICSERVICE_UNFOLLOWED = 29205,

    /// 公众号未关注，针对会话类型：ConversationType_PUBLIC_SERVICE
    /// 
    RC_PUBLICSERVICE_UNFOLLOW = 29206,

    /// 当前连接已经被释放
    /// 
    RC_CHANNEL_INVALID = 30001,

    /// 当前连接不可用
    /// 
    RC_NETWORK_UNAVAILABLE = 30002,

    /// 客户端发送消息请求，融云服务端响应超时
    /// 
    RC_MSG_RESPONSE_TIMEOUT = 30003,

    /// 请求连接导航地址失败
    /// 
    RC_NAVIGATION_REQUEST_TIMEOUT = 30005,

    /// 导航操作时，HTTP 接收失败
    /// 
    RC_NAVIGATION_RESPONSE_ERROR = 30006,

    /// 导航数据解析后，其中不存在有效 IP 地址
    /// 
    RC_DOMAIN_NOT_FOUND = 30009,

    /// 连接过于频繁
    /// 
    RC_CONNECT_OVER_FREQUENCY = 30015,

    /// 消息大小超限，消息体（序列化成 json 格式之后的内容）最大 128k bytes
    /// 
    RC_MSG_SIZE_OUT_OF_LIMIT = 30016,

    /// 网络连接不可用
    /// 
    RC_NETWORK_IS_DOWN_OR_UNREACHABLE = 30019,

    /// tcp 连接成功，rmtp 连接失败
    /// 
    RC_RMTP_CONNECTED_ERROR = 30021,

    /// 客户端 info 字段格式错误，正确格式：{平台类型}-{设备信息}-{sdk版本}。 其中设备信息：{手机类型}|{手机型号}|{网络类型，4G/WIFI}|{运营商标识, 移动/电信/联通}
    /// 
    RC_CONN_ID_REJECT = 31002,

    /// Token 无效；AppKey 和 Token 不匹配；Token 过期
    /// 
    RC_CONN_TOKEN_INCORRECT = 31004,

    /// App 校验未通过（开通了 App 校验功能，但是校验未通过）
    /// 
    RC_CONN_NOT_AUTHRORIZED = 31005,

    /// 包名与后台注册信息不匹配
    /// 
    RC_CONN_PACKAGE_NAME_INVALID = 31007,

    /// AppKey 被封禁或已删除
    /// 
    RC_CONN_APP_BLOCKED_OR_DELETED = 31008,

    /// 连接失败，用户被封禁（客户端主动连接失败返回）
    /// 
    RC_CONN_USER_BLOCKED = 31009,

    /// 用户被踢下线
    /// 
    RC_DISCONN_KICK = 31010,

    /// Token 已过期
    /// 
    RC_CONN_TOKEN_EXPIRE = 31020,

    /// 开启禁止把已在线客户端踢下线开关后，该错误码标识已有同类型端在线
    /// 
    RC_CONN_OTHER_DEVICE_LOGIN = 31023,

    /// 连接总数量超过服务设定的并发限定值（私有云专属）
    /// 
    CONCURRENT_LIMIT_ERROR = 31024,

    /// 客户端连错环境，引发连接拒绝；如使用开发环境 Appkey 连接到生产环境
    /// 
    RC_CONN_CLUSTER_ERROR = 31025,

    /// 开启AppServer联合鉴权功能后，到AppServer认证失败
    /// 
    RC_CONN_APP_AUTH_FAILED = 31026,

    /// 该 token 已经被使用过,无法进行连接 一次性 token 只能连接一次，之后再使用会上报此错误
    /// 
    RC_CONN_DISPOSABLE_TOKEN_USED = 31027,

    /// 用户已销户
    /// 
    /// - Since: 5.3.0
    RC_CONN_USER_ABANDON = 31029,

    /// 私有云 License 检查不通过;APP License 过期
    /// 
    /// - Since: 5.3.0
    RC_CONN_APP_LICENSE_EXPIRED = 31030,

    /// 协议层内部错误，查询，上传，下载过程中数据错误
    /// 
    RC_QUERY_ACK_NO_DATA = 32001,

    /// 协议层内部错误
    /// 
    RC_MESSAGE_DATA_INCOMPLETE = 32002,

    /// 服务器主动断开连接（仅 quic 协议下触发）
    /// 
    RC_UDP_DISCONNECTED = 32011,

    /// 链接被服务器中断，可能原因是运营商认为此链接非法或无效，直接断开 出现此错误码后，SDK 会自动触发重连，App 无需处理
    /// 
    RC_CONNECTION_RESET_BY_PEER = 32054,

    /// 将消息存储到本地数据时失败。 发送或插入消息时，消息需要存储到本地数据库，当存库失败时，会回调此错误码
    /// 
    BIZ_SAVE_MESSAGE_ERROR = 33000,

    /// 协议栈未初始化（可能原因：1,没有调用SDK初始化接口；2，SDK的so未正常加载）
    /// 
    CLIENT_NOT_INIT = 33001,

    /// 数据库错误
    /// 
    DATABASE_ERROR = 33002,

    /// 开发者接口调用时传入的参数错误
    /// 
    INVALID_PARAMETER = 33003,

    /// 历史消息云存储业务未开通
    /// 
    MSG_ROAMING_SERVICE_UNAVAILABLE = 33007,

    /// 消息存入本地数据库失败
    /// 
    RC_PROTOCOL_MESSAGE_INSERTED_ERROR = 33008,

    /// 聊天室被回收
    /// 
    RC_CHATROOM_RESET = 33009,

    /// 标签不存在
    /// 
    RC_TAG_NOT_EXIST = 33100,

    /// 标签已存在
    /// 
    RC_TAG_ALREADY_EXISTS = 33101,

    /// 标签不在会话中
    /// 
    RC_TAG_INVALID_FOR_CONVERSATION = 33102,

    /// 连接已存在
    /// 
    RC_CONNECTION_EXIST = 34001,

    /// 小视频时间长度超出限制，默认小视频时长上限为 2 分钟
    /// 
    RC_SIGHT_MSG_DURATION_LIMIT_EXCEED = 34002,

    /// GIF 消息文件大小超出限制
    /// 
    RC_GIF_MSG_SIZE_LIMIT_EXCEED = 34003,

    /// 聊天室状态未同步完成，刚加入聊天室时调用获取 KV 接口，极限情况下会存在本地数据和服务器未同步完成的情况，建议延时一段时间再获取
    /// 
    RC_KV_STORE_NOT_SYNC = 34004,

    /// 连接环境不正确
    /// 
    RC_ENVIRONMENT_ERROR = 34005,

    /// 连接超时
    /// 
    RC_CONNECT_TIMEOUT = 34006,

    /// 查询的公共服务信息不存在，请确认查询的公共服务的类型和公共服务 id 是否匹配
    /// 
    RC_PUBLIC_SERVICE_PROFILE_NOT_EXIST = 34007,

    /// 消息不能被扩展，只支持单群聊，其他类型消息会返回此错误，消息在发送时，Message 对象的属性 canIncludeExpansion 置为 true 才能进行扩展
    /// 
    RC_MESSAGE_CANT_EXPAND = 34008,

    /// 消息扩展失败，一般是网络原因导致的，请确保网络状态良好，并且融云 SDK 连接正常
    /// 
    RC_MESSAGE_EXPAND_FAIL = 34009,

    /// 消息扩展大小超出限制， 默认消息扩展字典 key 长度不超过 32 个字符，value 长度不超过 4096 个字符，设置的 Expansion 键值对不超过 300 个
    /// 
    RC_MSG_EXPANSION_SIZE_LIMIT_EXCEED = 34010,

    /// 媒体消息媒体文件 http 上传失败
    /// 
    RC_FILE_UPLOAD_FAILED = 34011,

    /// 指定的会话类型不支持标签功能，会话标签仅支持单群聊会话、系统会话
    /// 
    RC_CONVERSATION_TAG_INVALID_CONVERSATION_TYPE = 34012,

    /// 标签中添加/删除的会话数量超限，最多支持添加/删除 1000 个会话
    /// 
    RC_CONVERSATION_TAG_LIMIT_EXCEED = 34013,

    /// 群已读回执版本不支持
    /// 
    RC_Group_Read_Receipt_Version_Not_Support = 34014,

    /// 视频压缩失败
    /// 
    RC_SIGHT_COMPRESS_FAILED = 34015,

    /// 用户级别设置未开通
    /// 
    RC_USER_SETTING_DISABLED = 34016,

    /// 消息拦截器处理接口返回的消息为空
    /// 
    RC_MESSAGE_NULL_EXCEPTION = 34017,

    /// 媒体文件上传异常，媒体文件不存在或文件大小为 0
    /// 
    RC_MEDIA_EXCEPTION = 34018,

    /// 上传媒体文件格式不支持
    /// 
    RC_MEDIA_FILETYPE_INVALID = 34019,

    /// 文件已过期或被清理 小视频文件默认存储 7 天，其它文件默认存储 6个月。到期后自动清理
    /// 
    RC_FILE_EXPIRED = 34020,

    /// 消息未被注册
    /// 
    RC_MESSAGE_NOT_REGISTERED = 34021,

    /// 该接口不支持超级群会话
    /// 
    /// - Since: 5.2.0
    RC_ULTRA_GROUP_NOT_SUPPORT = 34022,

    /// 超级群频道不存在
    /// 
    /// - Since: 5.2.0
    RC_ULTRA_GROUP_CHANNEL_NOT_EXIST = 34024,

    /// 扩展消息失败，因为消息中的会话类别与接口支持的会话类别不一致
    /// 
    /// - Since: 5.4.4
    RC_MESSAGE_EXPAND_CONVERSATION_TYPE_NOT_MATCH = 34025,

    /// 连接时connection option 为空
    /// 
    INVALID_PARAMETER_CONNECTOPTIONNULL = 34129,

    /// 开发者接口调用时传入的语言非法
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_LAUGUAGE = 34200,

    /// 开发者调用的接口不支持传入的会话类型
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_CONVERSATIONTYPENOTSUPPORT = 34201,

    /// 开发者接口调用时传入的时间戳非法
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_TIMESTAMP = 34202,

    /// 开发者接口调用时传入的 uid (服务器消息唯一 id)非法
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_MESSAGEUID = 34203,

    /// 开发者接口调用时传入的 messageId 非法或者找不到对应的 Message
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_MESSAGEID = 34204,

    /// 开发者接口调用时传入的 Message 非法，或者 MessageContent 非法
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_MESSAGECONTENT = 34205,

    /// 开发者接口调用时传入的 messageList 非法
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_MESSAGELIST = 34206,

    /// 开发者接口调用时传入的 mediaType 非法
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_MEDIATYPE = 34207,

    /// 开发者接口调用时传入的 requestUrl 非法
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_REQUESTURL = 34208,

    /// 开发者接口调用时传入的 ConversationType 非法
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_CONVERSATIONTYPE = 34209,

    /// 开发者接口调用时传入的 targetId 非法
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_TARGETID = 34210,

    /// 开发者调用频道相关接口时传入的 channelId 非法
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_CHANNELID = 34211,

    /// 开发者接口调用时传入的 tagId 非法
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_TAGID = 34212,

    /// 开发者接口调用时传入的 tagName 非法
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_TAGNAME = 34213,

    /// 开发者接口调用时传入的 userId 非法
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_USERID = 34214,

    /// 开发者接口调用时传入的 userIdList 非法
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_USERIDLIST = 34215,

    /// 开发者接口调用时传入的 UserOnlineStatus 非法。  可能原因： 用户自定义的在线状态(1 < customerStatus <= 255)，  设置自定义的在线状态，默认的在线状态值为 1，若离线则为 0
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_USERONLINESTATUS = 34216,

    /// 开发者接口调用时传入的 downloadMediaFileName 非法
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_DOWNLOADMEDIAFILENAME = 34217,

    /// 开发者调用接口 setOfflineMessageDuration 传入的参数非法
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_SETOFFLINEMESSAGEDURATION = 34218,

    /// 开发者接口调用时传入的 HistoryMessageOption 非法
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_RCHISTORYMESSAGEOPTION_COUNT = 34219,

    /// 开发者接口调用时传入的 MessageExpansion 非法
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_MESSAGEEXPANSION = 34220,

    /// 开发者接口调用时传入的UltraGroupMessageExpansion keyArray 非法
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_ULTRAGROUPMESSAGEEXPANSION_KEYARRAY = 34221,

    /// uploadVoIPDeviceToken 接口检测到无效的  VoIP DeviceToken
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_UPLOADVOIPDEVICETOKEN = 34222,

    /// 开发者sendMediaMessage 传入的 Message.content 不是多媒体消息
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_NOTMEDIAMESSAGE = 34223,

    /// 开发者调用接口传入的时间（字符串）参数非法。可能原因：开发者调用接口传入的时间（字符串）参数类型不是字符串或者字符串为空。
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_TIMESTRING = 34224,

    /// RCConversationIdentifier 参数非法。  可能原因：开发者调用接口传入的 RCConversationIdentifier 参数类型不对或者参数为空
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_CONVERSATIONIDENTIFIER = 34225,

    /// 开发者调用接口 GetBlockPush 接口获取失败
    /// 
    /// - Since: 5.2.2
    RC_GETBLOCKPUSH_FAILED = 34226,

    /// 开发者调用数据库查询接口,查询失败
    /// 
    /// - Since: 5.2.2
    RC_DB_QUERY_ERROR = 34227,

    /// PushNotificationLevel 无效
    /// 
    /// - Since: 5.2.2
    INVALID_PARAMETER_NOTIFICATION_LEVEL = 34228,

    /// 无效的超级群频道类型
    /// 
    /// - Since: 5.2.4
    INVALID_PARAMETER_CHANNEL_TYPE = 34231,

    /// 开发者接口调用时传入的 count 非法
    /// 
    /// - Since: 5.2.5
    INVALID_PARAMETER_COUNT = 34232,

    /// 开发者接口调用时传入的 sendTime 非法
    /// 
    /// - Since: 5.3.0
    INVALID_PARAMETER_SEND_TIME = 34233,

    /// 开发者调用接口传入的 local path 地址不存在
    /// 
    INVALID_PARAMETER_LOCAL_PATH = 34234,

    /// 开发者调用接口传入的 mediaUrl 地址为空
    /// 
    INVALID_PARAMETER_MEDIA_URL = 34235,

    /// 开发者调用接口传入的 uniqueId 为空或者""
    /// 
    INVALID_PARAMETER_UNIQUE_ID = 34236,

    /// 开发者调用接口传入的 MessageTag 为空 或者MessageTag.value()为空或者 ""
    /// 
    INVALID_PARAMETER_MSG_TAG = 34237,

    /// 非法的代理配置，RongIMProxy 为空或者非法
    /// 
    /// - Since: 5.3.0
    INVALID_PARAMETER_PROXY = 34238,

    /// 开发者接口调用 testProxy 时传入的代理测试服务非法
    /// 
    /// - Since: 5.3.0
    INVALID_PARAMETER_TESTHOST = 34239,

    /// 开发者接口调用 testProxy 接口时无法联通
    /// 
    /// - Since: 5.3.0
    INVALID_CONNECT_TESTHOST_FAILED = 34240,

    /// 开发者接口调用recallUltraGroupMessage时，撤回了不支持的消息类型
    /// 
    /// - Since: 5.3.0
    INVALID_PARAMETER_ULTRA_GROUP_MESSAGE_OBJECT_NAME = 34241,

    /// 开发者调用接口传入的 conversations 参数为 null 或者 conversations 数组包含 null 对象
    /// 
    INVALID_PARAMETER_CONVERSATIONS = 34242,

    /// 开发者调用接口传入的 message 参数为空
    /// 
    INVALID_PARAMETER_MESSAGE = 34243,

    /// 开发者调用接口传入的 Message.SentStatus 参数为 null
    /// 
    INVALID_PARAMETER_SENT_STATUS = 34244,

    /// 设置的代理地址不可用
    /// 
    RC_CONN_PROXY_UNAVAILABLE = 34245,

    /// 文件保存失败
    /// 
    FILE_SAVED_FAILED = 34251,

    /// 文件不存在
    /// 
    FILE_NOT_EXIST = 34252,

    /// 文件长度错误
    /// 
    FILE_SIZE_ERROR = 34253,

    /// 下载链接无效
    /// 
    DOWNLOAD_URL_INVALID = 34254,

    /// 分片索引错误
    /// 
    SLICE_INDEX_ERROR = 34255,

    /// 上传ID无效
    /// 
    UPLOAD_ID_INVALID = 34256,

    /// App Key 无效
    /// 
    INVALID_APP_KEY = 34257,

    /// 参数 JoinMode 非法
    /// 
    INVALID_PARAMETER_JOIN_MODE = 34258,

    /// 参数 rtcRoomID 非法
    /// 
    INVALID_PARAMETER_RTCROOMID = 34259,

    /// 参数 key 非法
    /// 
    INVALID_PARAMETER_KEY = 34260,

    /// 参数keys 非法
    /// 
    INVALID_PARAMETER_KEYS = 34261,

    /// 参数 value 非法
    /// 
    INVALID_PARAMETER_VALUE = 34262,

    /// 参数 entries 非法
    /// 
    INVALID_PARAMETER_ENTRIES = 34263,

    /// 参数 notificationExtra  非法
    /// 
    INVALID_PARAMETER_NOTIFICATION_EXTRA = 34264,

    /// 参数 ChatRoomMemberOrder 非法
    /// 
    INVALID_PARAMETER_CHATROOM_MEMBER_ORDER = 34265,

    /// 参数 TimestampOrder 非法
    /// 
    INVALID_PARAMETER_TIMESTAMP_ORDER = 34266,

    /// 参数 status 非法
    /// 
    INVALID_PARAMETER_STATUS = 34268,

    /// 参数 title 非法
    /// 
    INVALID_PARAMETER_TITLE = 34269,

    /// 参数 portrait 非法
    /// 
    INVALID_PARAMETER_PORTRAIT = 34270,

    /// 参数 objectName 非法
    /// 
    MESSAGE_OBJECT_NAME_INVALID = 34271,

    /// 参数 keyword 非法
    /// 
    INVALID_PARAMETER_KEYWORD = 34274,

    /// 参数 objectName 列表非法
    /// 
    /// - Solution message object name list invalid
    INVALID_PARAMETER_OBJECTNAMELIST = 34275,

    /// 参数 limit 非法
    /// 
    INVALID_PARAMETER_LIMIT = 34279,

    /// MessageDirection错误
    /// 
    INVALID_MESSAGE_DIRECTION = 34280,

    /// SentStatus错误
    /// 
    INVALID_MESSAGE_SENT_STATUS = 34281,

    /// 参数 target id 列表非法
    /// 
    INVALID_PARAMETER_TARGETID_LIST = 34282,

    /// 参数 span minutes 非法
    /// 
    INVALID_PARAMETER_SPAN_MINUTES = 34283,

    /// 请求导航时的url 为空
    /// 
    RC_INVALID_ARGUMENT = 34286,

    /// 开发者调用接口传入的 ConversationIdentifier 数组参数为空、数组长度为 0或超过限制、包含 null 或非法对象
    /// 
    /// - Since: 5.6.7
    INVALID_PARAMETER_CONVERSATION_IDENTIFIER_LIST = 34287,

    /// 开发者调用接口传入的 ClearMessageOption 数组参数为空、数组长度为 0或超过限制、包含 null 或非法对象
    /// 
    /// - Since: 5.6.7
    INVALID_PARAMETER_CLEAR_MESSAGE_OPTION_LIST = 34288,

    /// 参数 startMessageUID 无效
    /// 
    /// - Since: 5.6.7
    INVALID_PARAMETER_START_MESSAGEUID = 34289,

    /// 参数 endMessageUID 无效
    /// 
    /// - Since: 5.6.7
    INVALID_PARAMETER_END_MESSAGEUID = 34290,

    /// 不支持V4已读回执功能
    /// 
    /// - Since: 5.6.7
    RC_READ_RECEIPT_V4_NOT_SUPPORT = 34291,

    /// 不支持更新v4已读回执信息
    /// 
    /// - Since: 5.6.7
    RC_READ_RECEIPT_V4_UPDATE_NOT_SUPPORT = 34292,

    /// invalid parameter hours
    /// 
    /// - Since: 5.4.5.107
    INVALID_PARAMETER_HOURS = 34293,

    /// fetch message changed info unavailable
    /// 
    /// - Since: 5.4.5.107
    RC_ACTIVE_FETCH_MESSAGE_CHANGED_INFO_UNAVAILABLE = 34294,

    /// message changed info have fetched
    /// 
    /// - Since: 5.4.5.107
    RC_MESSAGE_CHANGED_INFO_HAVE_FETCHED = 34295,

    /// 发送定向消息时，传入的会话类型不支持
    /// 
    /// - Solution 发送定向消息时，传入的会话类型不支持
    /// - Since: 5.6.9
    RC_DIRECTIONAL_MESSAGE_INVALID_CONVERSATION_TYPE = 34296,

    /// 多媒体上传&下载拦截器，处理接口返回的 conn 为空
    /// 
    /// - Since: 5.8.0
    RC_REQUEST_INTERCEPTOR_NULL_EXCEPTION = 34300,

    /// 数据库未初始化
    /// 
    RC_DB_NOT_INIT = 34301,

    /// 数据库错误
    /// 
    RC_DB_CORRUPT = 34302,

    /// 数据库 SQL 执行异常
    /// 
    RC_DB_SQL_ERROR = 34303,

    /// 查询数据不存在
    /// 
    RC_DB_DATA_NOT_FOUND = 34304,

    /// 网络数据解析失败
    /// 
    RC_NET_DATA_ERROR = 34305,

    /// 订阅事件传入的订阅类型非法
    /// 
    /// - Solution 订阅相关接口传入的订阅类型不支持
    INVALID_PARAMETER_SUBSCRIBE_TYPE = 34306,

    /// 订阅事件传入的订阅时长非法[60s ~ 30天]
    /// 
    /// - Solution 订阅相关接口传入的订阅时长非法
    INVALID_PARAMETER_SUBSCRIBE_EXPIRY = 34307,

    /// 订阅事件传入的订阅用户列表空或者数据类型非法
    /// 
    /// - Solution 订阅相关接口传入的订阅用户列表非法
    INVALID_PARAMETER_SUBSCRIBE_PUBLISHER_USERIDS = 34308,

    /// 订阅事件传入的分页大小非法
    /// 
    /// - Solution 订阅相关接口传入的分页大小非法[1~200]
    INVALID_PARAMETER_SUBSCRIBE_PAGESIZE = 34309,

    /// 参数 userProfile 非法
    /// 
    /// - Since: 5.10.0
    INVALID_PARAMETER_USER_PROFILE = 34312,

    /// 参数 userProfileVisibility 非法
    /// 
    /// - Since: 5.10.0
    INVALID_PARAMETER_USER_PROFILE_VISIBILITY = 34313,

    /// 参数 extra 无效
    /// 
    /// - Since: 5.10.2
    INVALID_PARAMETER_EXTRA = 34314,

    /// 数据库升级失败
    /// 
    /// - Since: 5.10.4
    RC_DB_UPGRADE_FAILED = 34315,

    /// 开发者接口调用时传入的参数 GroupInfo 非法
    /// 
    /// - Since: 5.12.0
    INVALID_PARAMETER_GROUP_INFO = 34318,

    /// 开发者接口调用时传入的参数 groupId 非法
    /// 
    /// - Since: 5.12.0
    INVALID_PARAMETER_GROUP_ID = 34319,

    /// 开发者接口调用时传入的参数 groupName 非法
    /// 
    /// - Since: 5.12.0
    INVALID_PARAMETER_GROUP_NAME = 34320,

    /// 开发者接口调用时传入的参数 groupIds 非法
    /// 
    /// - Since: 5.12.0
    INVALID_PARAMETER_GROUP_IDS = 34321,

    /// 开发者接口调用时传入的参数 GroupMemberRole 非法
    /// 
    /// - Since: 5.12.0
    INVALID_PARAMETER_GROUP_MEMBER_ROLE = 34322,

    /// 开发者接口调用时传入的参数 GroupApplicationStatus 非法
    /// 
    /// - Since: 5.12.0
    INVALID_PARAMETER_GROUP_APPLICATION_STATUS = 34323,

    /// 开发者接口调用时传入的参数 GroupApplicationDirection 非法
    /// 
    /// - Since: 5.12.0
    INVALID_PARAMETER_GROUP_APPLICATION_DIRECTION = 34324,

    /// 开发者接口调用时传入的参数 nickname 非法
    /// 
    /// - Since: 5.12.0
    INVALID_PARAMETER_NICK_NAME = 34325,

    /// 开发者接口调用时传入的参数 reason 非法
    /// 
    /// - Since: 5.12.0
    INVALID_PARAMETER_REASON = 34326,

    /// 开发者接口调用时传入的参数 remark 非法
    /// 
    /// - Since: 5.12.0
    INVALID_PARAMETER_REMARK = 34327,

    /// 开发者接口调用时传入的参数 PagingQueryOption 非法
    /// 
    /// - Since: 5.12.0
    INVALID_PARAMETER_PAGING_QUERY_OPTION = 34328,

    /// 数据正在同步中
    /// 
    /// - Since: 5.12.0
    NET_DATA_IS_SYNCHRONIZING = 34329,

    /// 开发者接口调用时传入的参数 QueryFriendsDirectionType 非法
    /// 
    /// - Since: 5.12.0
    INVALID_PARAMETER_QUERY_FRIENDS_DIRECTION_TYPE = 34330,

    /// 开发者接口调用时传入的参数 DirectionType 非法
    /// 
    /// - Since: 5.12.0
    INVALID_PARAMETER_DIRECTION_TYPE = 34331,

    /// 开发者接口调用时传入的参数 FriendApplicationType 非法
    /// 
    /// - Since: 5.12.0
    INVALID_PARAMETER_FRIEND_APPLICATION_TYPE = 34332,

    /// 开发者接口调用时传入的参数 FriendApplicationStatus 非法
    /// 
    /// - Since: 5.12.0
    INVALID_PARAMETER_FRIEND_APPLICATION_STATUS = 34333,

    /// 开发者接口调用时传入的参数 FriendAddPermission 非法
    /// 
    /// - Since: 5.12.0
    INVALID_PARAMETER_FRIEND_ADD_PERMISSION = 34334,

    /// 开发者接口调用时传入的参数 extProfile 非法
    /// 
    /// - Since: 5.12.0
    INVALID_PARAMETER_FRIEND_INFO_EXT_FIELDS = 34335,

    /// 取消暂停失败
    /// 
    /// - Solution 取消 / 暂停下载失败, 失败的原因现在为下载任务已经结束
    /// - Since: 5.6.6
    OPERATION_MEDIA_NOT_FOUND = -3,

    /// 未知错误
    /// 
    ERRORCODE_UNKNOWN = -1

};

#endif /* RCErrorCode_h */
