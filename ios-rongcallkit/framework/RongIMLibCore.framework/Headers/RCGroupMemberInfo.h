//
//  RCGroupMemberInfo.h
//  RongIMLibCore
//
//  Created by Lang on 2024/7/19.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCGroupEnum.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCGroupMemberInfo : NSObject

/// 用户 Id
@property (nonatomic, copy) NSString *userId;

/// 头像 URL
@property (nonatomic, copy) NSString *portraitUri;

/// 用户名
@property (nonatomic, copy) NSString *name;

/// 在群中的昵称（别名），默认为用户名
@property (nonatomic, copy, nullable) NSString *nickname;

///  附加信息
@property (nonatomic, copy, nullable) NSString *extra;

/// 入群时间戳
@property (nonatomic, assign) long long joinedTime;

/// 我群身份
@property (nonatomic, assign) RCGroupMemberRole role;

/// 是否是机器人
/// - Since 5.28.0
@property (nonatomic, assign) BOOL isRobot;

@end

NS_ASSUME_NONNULL_END
