//
//  RCRTCProxyInfo.h
//  RongRTCLib
//
//  Created by RongCloud on 2022/09/06.
//  Copyright © 2022 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RCRTCLibDefine.h"

NS_ASSUME_NONNULL_BEGIN

@interface RCRTCProxy : NSObject

/*!
 代理地址, 默认值: @"", 非 nil 或非 @"" 时有效
 */
@property (nonatomic, copy) NSString *host;

/*!
 代理地址对应IP, 只读, 不可设置
 */
@property (nonatomic, copy, readonly) NSString *ip;

/*!
 代理端口, 默认值: -1, 大于 0 时有效
 */
@property (nonatomic, assign) NSInteger port;

/*!
 代理服务登录用户名, 默认值: @""
 如果需要则填写, 不需要可不填写,
 userName 与 password 同时非 nil 或非 @"" 时有效
 */
@property (nonatomic, copy) NSString *userName;

/*!
 代理服务登录密码, 默认值: @""
 如果需要则填写, 不需要可不填写,
 userName 与 password 同时非 nil 或非 @"" 时有效
 */
@property (nonatomic, copy) NSString *password;

/*!
 可通过代理服务连接的协议类型, 默认值: RCRTCProxyOptionsAll, 全支持
 */
@property (nonatomic, assign) RCRTCProxyOptions proxyOption;

/*!
 验证设置数据是否有效
 */
- (BOOL)isValid;

@end

NS_ASSUME_NONNULL_END
