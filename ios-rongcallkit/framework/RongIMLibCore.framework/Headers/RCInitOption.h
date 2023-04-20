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
    RCAreaCodeBJ = 1, //默认值，北京数据中心
    RCAreaCodeSG = 2, //新加坡数据中心
    RCAreaCodeNA = 3  //北美数据中心
};

@interface RCInitOption : NSObject

/**
 导航服务器地址
 @warning 仅限独立数据中心使用，使用前必须先联系商务开通。
 @discussion 如果设置 naviServer， 必须为有效的服务器地址：
 1、如果使用 https，则设置为 https://cn.xxx.com:port 或 https://cn.xxx.com 或  cn.xxx.com【SDK 默认使用 https】，其中域名部分也可以是 IP，如果不指定端口，将默认使用 443 端口。
 2、如果使用 http，则设置为 http://cn.xxx.com:port 或 http://cn.xxx.com 格式，其中域名部分也可以是 IP，如果不指定端口，将默认使用 80 端口。
 @discussion iOS 默认只能使⽤ HTTPS 协议。如果您使⽤ http 协议，请参考 Apple 开发⽂档中的 ATS 设置说明。
 @discussion 与 RCCoreClient 中 setServerInfo:fileServer: 效果一致，任一种设置都生效
 @since 5.4.1
 */
@property (nonatomic, copy, nullable) NSString *naviServer;

/**
 文件服务器地址
 @warning 仅限独立数据中心使用，使用前必须先联系商务开通。
 @discussion 如果设置 fileServer， 必须为有效的服务器地址：
 1、如果使用 https，则设置为 https://cn.xxx.com:port 或 https://cn.xxx.com 或  cn.xxx.com【SDK 默认使用 https】，其中域名部分也可以是 IP，如果不指定端口，将默认使用 443 端口。
 2、如果使用 http，则设置为 http://cn.xxx.com:port 或 http://cn.xxx.com 格式，其中域名部分也可以是 IP，如果不指定端口，将默认使用 80 端口。
 @discussion iOS 默认只能使⽤ HTTPS 协议。如果您使⽤ http 协议，请参考 Apple 开发⽂档中的 ATS 设置说明。
 @discussion 与 RCCoreClient 中 setServerInfo:fileServer: 效果一致，任一种设置都生效
 @since 5.4.1
 */
@property (nonatomic, copy, nullable) NSString *fileServer;

/**
 统计服务器地址
 @warning 仅限独立数据中心使用，使用前必须先联系商务开通。
 @discussion 如果设置 statisticServer， 必须为有效的服务器地址：
 1、如果使用 https，则设置为 https://cn.xxx.com:port 或 https://cn.xxx.com 或  cn.xxx.com【SDK 默认使用 https】，其中域名部分也可以是 IP，如果不指定端口，将默认使用 443 端口。
 2、如果使用 http，则设置为 http://cn.xxx.com:port 或 http://cn.xxx.com 格式，其中域名部分也可以是 IP，如果不指定端口，将默认使用 80 端口。
 @discussion iOS 默认只能使⽤ HTTPS 协议。如果您使⽤ http 协议，请参考 Apple 开发⽂档中的 ATS 设置说明。
 @discussion 与 RCCoreClient 中 setStatisticServer: 效果一致，任一种设置都生效
 @since 5.4.1
 */
@property (nonatomic, copy, nullable) NSString *statisticServer;

/**
 日志服务器地址
 @warning 仅限独立数据中心使用，使用前必须先联系商务开通。
 @discussion 如果设置 logServer， 必须为有效的服务器地址：
 1、如果使用 https，则设置为 https://cn.xxx.com:port 或 https://cn.xxx.com 或  cn.xxx.com【SDK 默认使用 https】，其中域名部分也可以是 IP，如果不指定端口，将默认使用 443 端口。
 2、如果使用 http，则设置为 http://cn.xxx.com:port 或 http://cn.xxx.com 格式，其中域名部分也可以是 IP，如果不指定端口，将默认使用 80 端口。
 @discussion iOS 默认只能使⽤ HTTPS 协议。如果您使⽤ http 协议，请参考 Apple 开发⽂档中的 ATS 设置说明。
 @since 5.4.2
 */
@property (nonatomic, copy, nullable) NSString *logServer;

/**
 区域码
 @discussion 默认为北京数据中心，用户可以根据实际情况设置区域码，设置之后，SDK 将会使用特定区域的服务地址
 @discussion 每个数据中心都会有对应的 naviServer 、statisticServer 、logServer
 @discussion 如果开发者手动设置了本类的 naviServer 、statisticServer 、logServer 将会覆盖对应区域的配置
 例如：设置 areaCode 为北美数据中心，同时又设置了此处的 naviServer ，那么最终会使用此处的 naviServer 而不是北美数据中心的 naviServer
 @since 5.4.2
 */
@property (nonatomic, assign) RCAreaCode areaCode;

@end

NS_ASSUME_NONNULL_END
