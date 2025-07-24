/**
 * Copyright (c) 2014-2015, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */

//  RCUserInfo.h
//  Created by Heq.Shinoda on 14-6-16.

#import <Foundation/Foundation.h>

/// 用户类型。
///
/// - Since: 5.22.0
typedef NS_ENUM(NSInteger, RCUserType) {
    /// 正常用户。
    RCUserTypeNormal = 0,
    /// 机器人。
    RCUserTypeRobot = 1,
};

NS_ASSUME_NONNULL_BEGIN

/// 用户信息类
@interface RCUserInfo : NSObject <NSCoding>

/// 用户 ID
@property (nonatomic, copy) NSString *userId;

/// 用户类型，默认为 `RCUserTypeNormal`。
@property (nonatomic, assign) RCUserType userType;

/// 用户名称
@property (nonatomic, copy) NSString *name;

/// 用户头像的 URL
@property (nonatomic, copy, nullable) NSString *portraitUri;

/// 用户备注
@property (nonatomic, copy, nullable) NSString *alias;

/// 用户信息附加字段
@property (nonatomic, copy, nullable) NSString *extra;

/// 用户信息的初始化方法
///
/// - Parameter userId: 用户 ID
/// - Parameter username: 用户名称
/// - Parameter portrait: 用户头像的 URL
/// - Returns: 用户信息对象
- (instancetype)initWithUserId:(NSString *)userId
                          name:(nullable NSString *)username
                      portrait:(nullable NSString *)portrait;

@end

NS_ASSUME_NONNULL_END
