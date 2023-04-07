//
//  RCInitOption.h
//  RongIMLibCore
//
//  Created by shuai shao on 2023/3/16.
//  Copyright © 2023 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCInitOption : NSObject

/**
 导航服务器地址
 @warning 仅限独立数据中心使用，使用前必须先联系商务开通。
 @discussion 如果设置 naviServer， 必须为有效的服务器地址：
 1、如果使用 https，则设置为 https://cn.xxx.com:port 或 https://cn.xxx.com 格式，其中域名部分也可以是 IP，如果不指定端口，将默认使用 443 端口。
 2、如果使用 http，则设置为 cn.xxx.com:port 或 cn.xxx.com 格式，其中域名部分也可以是 IP，如果不指定端口，将默认使用 80 端口。
 @discussion iOS 默认只能使⽤ HTTPS 协议。如果您使⽤ http 协议，请参考 Apple 开发⽂档中的 ATS 设置说明。
 @discussion 与 RCCoreClient 中 setServerInfo:fileServer: 效果一致，任一种设置都生效
 @since 5.4.1
 */
@property (nonatomic, copy, nullable) NSString *naviServer;

/**
 文件服务器地址
 @warning 仅限独立数据中心使用，使用前必须先联系商务开通。
 @discussion 如果设置 fileServer， 必须为有效的服务器地址：
 1、如果使用 https，则设置为 https://cn.xxx.com:port 或 https://cn.xxx.com 格式，其中域名部分也可以是 IP，如果不指定端口，将默认使用 443 端口。
 2、如果使用 http，则设置为 cn.xxx.com:port 或 cn.xxx.com 格式，其中域名部分也可以是 IP，如果不指定端口，将默认使用 80 端口。
 @discussion iOS 默认只能使⽤ HTTPS 协议。如果您使⽤ http 协议，请参考 Apple 开发⽂档中的 ATS 设置说明。
 @discussion 与 RCCoreClient 中 setServerInfo:fileServer: 效果一致，任一种设置都生效
 @since 5.4.1
 */
@property (nonatomic, copy, nullable) NSString *fileServer;

/**
 统计服务器地址
 @discussion 仅限独立数据中心使用，使用前必须先联系商务开通。
 @discussion 如果设置 statisticServer， 必须为有效的服务器地址：
 1、如果使用 https，则设置为 https://cn.xxx.com:port 或 https://cn.xxx.com 格式，其中域名部分也可以是 IP，如果不指定端口，将默认使用 443 端口。
 2、如果使用 http，则设置为 cn.xxx.com:port 或 cn.xxx.com 格式，其中域名部分也可以是 IP，如果不指定端口，将默认使用 80 端口。
 @discussion iOS 默认只能使⽤ HTTPS 协议。如果您使⽤ http 协议，请参考 Apple 开发⽂档中的 ATS 设置说明。
 @discussion 与 RCCoreClient 中 setStatisticServer: 效果一致，任一种设置都生效
 @since 5.4.1
 */
@property (nonatomic, copy, nullable) NSString *statisticServer;

@end

NS_ASSUME_NONNULL_END
