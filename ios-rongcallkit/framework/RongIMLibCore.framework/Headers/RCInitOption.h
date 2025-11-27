//
//  RCInitOption.h
//  RongIMLibCore
//
//  Created by shuai shao on 2023/3/16.
//  Copyright © 2023 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, RCAreaCode) {
    /// 默认值，北京数据中心
    RCAreaCodeBJ = 1,
    /// 新加坡数据中心
    RCAreaCodeSG = 2,
    /// 北美数据中心
    RCAreaCodeNA = 3,
    /// 新增的新加坡数据中心
    RCAreaCodeSG_B = 4,
    /// 废弃枚举
    RCAreaCodeSG_A __deprecated_msg("Use RCAreaCodeSG_B instead") = RCAreaCodeSG_B,
    /// 沙特数据中心
    RCAreaCodeSA = 5,
    /// 阿曼数据中心
    RCAreaCodeOman = 6,
    /// 无效枚举值，业务上不用
    RCAreaCodeInvalid
};

// 心跳级别
typedef NS_ENUM(NSInteger, RCHeartbeatLevel) {
    /// 紧急：2 次心跳超时后重连 IM
    RCHeartbeatLevelUrgent = 2,
    /// 优先：3 次心跳超时后重连 IM
    RCHeartbeatLevelPriority = 3,
    /// 立即：4 次心跳超时后重连 IM
    RCHeartbeatLevelImmediate = 4,
    /// 迫切：5 次心跳超时后重连 IM
    RCHeartbeatLevelPressing = 5,
    /// 常规：6 次心跳超时后重连 IM(默认值)
    RCHeartbeatLevelNormal = 6
};
@interface RCInitOption : NSObject

/// 导航服务器地址
///
/// - Warning: 仅限独立数据中心使用，使用前必须先联系商务开通。
/// 如果设置 naviServer，必须为有效的服务器地址：
/// 1. 如果使用 https，则设置为 https://cn.xxx.com:port 或 https://cn.xxx.com 或  cn.xxx.com【SDK ///默认使用 https】，其中域名部分也可以是 IP，如果不指定端口，将默认使用 443 端口。
/// 2. 如果使用 http，则设置为 http://cn.xxx.com:port 或 http://cn.xxx.com ///格式，其中域名部分也可以是 IP，如果不指定端口，将默认使用 80 端口。
/// iOS 默认只能使⽤ HTTPS 协议。如果您使⽤ http 协议，请参考 Apple 开发⽂档中的 ATS 设置说明。
/// 与 RCCoreClient 中 setServerInfo:fileServer: 效果一致，任一种设置都生效
/// - Since: 5.4.1
@property (nonatomic, copy, nullable) NSString *naviServer;

/// 文件服务器地址
///
/// - Warning: 仅限独立数据中心使用，使用前必须先联系商务开通。
/// 如果设置 fileServer，必须为有效的服务器地址：
/// 1. 如果使用 https，则设置为 https://cn.xxx.com:port 或 https://cn.xxx.com 或  cn.xxx.com【SDK ///默认使用 https】，其中域名部分也可以是 IP，如果不指定端口，将默认使用 443 端口。
/// 2. 如果使用 http，则设置为 http://cn.xxx.com:port 或 http://cn.xxx.com ///格式，其中域名部分也可以是 IP，如果不指定端口，将默认使用 80 端口。
/// iOS 默认只能使⽤ HTTPS 协议。如果您使⽤ http 协议，请参考 Apple 开发⽂档中的 ATS 设置说明。
/// 与 RCCoreClient 中 setServerInfo:fileServer: 效果一致，任一种设置都生效
/// - Since: 5.4.1
@property (nonatomic, copy, nullable) NSString *fileServer;

/// 统计服务器地址
///
/// - Warning: 仅限独立数据中心使用，使用前必须先联系商务开通。
/// 如果设置 statisticServer，必须为有效的服务器地址：
/// 1. 如果使用 https，则设置为 https://cn.xxx.com:port 或 https://cn.xxx.com 或  cn.xxx.com【SDK ///默认使用 https】，其中域名部分也可以是 IP，如果不指定端口，将默认使用 443 端口。
/// 2. 如果使用 http，则设置为 http://cn.xxx.com:port 或 http://cn.xxx.com ///格式，其中域名部分也可以是 IP，如果不指定端口，将默认使用 80 端口。
/// iOS 默认只能使⽤ HTTPS 协议。如果您使⽤ http 协议，请参考 Apple 开发⽂档中的 ATS 设置说明。
/// 与 RCCoreClient 中 setStatisticServer: 效果一致，任一种设置都生效
/// - Since: 5.4.1
@property (nonatomic, copy, nullable) NSString *statisticServer;

/// 日志服务器地址
///
/// - Warning: 仅限独立数据中心使用，使用前必须先联系商务开通。
/// 如果设置 logServer，必须为有效的服务器地址：
/// 1、如果使用 https，则设置为 https://cn.xxx.com:port 或 https://cn.xxx.com 或  cn.xxx.com【SDK 默认使用 https】，其中域名部分也可以是 IP，如果不指定端口，将默认使用 443 端口。
/// 2、如果使用 http，则设置为 http://cn.xxx.com:port 或 http://cn.xxx.com 格式，其中域名部分也可以是 IP，如果不指定端口，将默认使用 80 端口。
/// iOS 默认只能使⽤ HTTPS 协议。如果您使⽤ http 协议，请参考 Apple 开发⽂档中的 ATS 设置说明。
/// - Since: 5.4.2
@property (nonatomic, copy, nullable) NSString *logServer;

/// 云控服务器地址。
///
/// - Since: 5.24.0
@property (nonatomic, copy, nullable) NSString *cloudControlServer;

/// 区域码
///
/// 默认为北京数据中心，用户可以根据实际情况设置区域码，设置之后，SDK 将会使用特定区域的服务地址
/// 每个数据中心都会有对应的 naviServer、statisticServer、logServer
/// 如果开发者手动设置了本类的 naviServer、statisticServer、logServer 将会覆盖对应区域的配置
/// 例如：设置 areaCode 为北美数据中心，同时又设置了此处的 naviServer，那么最终会使用此处的 naviServer 而不是北美数据中心的 naviServer
/// - Since: 5.4.2
@property (nonatomic, assign) RCAreaCode areaCode;

/// crash 监控开关，默认开启
///
/// - Since: 5.6.5
@property (nonatomic, assign) BOOL crashMonitorEnable;

/// 心跳级别 (默认 RCHeartbeatLevelNormal)
///
/// - Since: 5.6.7
@property (nonatomic, assign) RCHeartbeatLevel heartbeatLevel;

/// 网络环境标识
/// 标志客户端所在当前网络环境，例如 intranet 内网，private 专网。如果不配置，使用对应于的默认环境配置
///
/// - Note: 私有云专用属性，公有云客户设置无效。
@property (nonatomic, copy, nullable) NSString *environment;

/// 是否开启同步空置顶会话能力
///
/// - Note: 如不设置，则默认为 NO，即不同步空置顶会话
/// - Since: 5.10.0
@property (nonatomic, assign) BOOL enableSyncEmptyTopConversation;

@end

NS_ASSUME_NONNULL_END
