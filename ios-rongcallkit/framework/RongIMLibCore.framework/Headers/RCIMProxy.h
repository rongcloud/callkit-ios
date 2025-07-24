//
//  RCIMProxy.h
//  RongIMLibCore
//
//  Created by chinaspx on 2022/9/7.
//  Copyright © 2022 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCIMProxy : NSObject

// socks 代理地址
@property (nonatomic, copy, readonly) NSString *host;

// socks 代理端口号
@property (nonatomic, assign, readonly) NSInteger port;

/*
 *  用户名和密码
 *
 *  - userName 和 password 均存在有效值，则使用认证方式，连接代理
 *  - userName 和 password 有一个为空，则使用不认证的方式，连接代理
 *
 */
// 代理认证的用户名，默认为空字符串
@property (nonatomic, copy, readonly) NSString *userName;
// 代理认证的密码，默认为空字符串
@property (nonatomic, copy, readonly) NSString *password;

// 合法性检测，自身为空则不合法、host 为空则不合法、port <=0 则不合法
- (BOOL)isValid;

// 默认构造，不带认证方式连接代理
- (instancetype)initWithHost:(NSString *)host port:(NSInteger)port;

// 默认构造，认证方式连接代理
- (instancetype)initWithHost:(NSString *)host
                        port:(NSInteger)port
                    userName:(NSString *)userName
                    password:(NSString *)password;


+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
