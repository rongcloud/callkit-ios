//
//  RCUserProfile.h
//  RongIMLibCore
//
//  Created by Lang on 2024/4/19.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

/// 用户信息访问权限
typedef NS_ENUM(NSUInteger, RCUserProfileVisibility) {
    /// 未设置，以 AppKey 权限设置为准，默认是此状态。
    RCUserProfileVisibilityNotSet = 0,
    /// 都不可见，任何人都不能搜索到我的用户信息，名称、头像除外
    RCUserProfileVisibilityInvisible = 1,
    /// 所有人可见，应用中任何用户都可以查看到我的用户信息
    RCUserProfileVisibilityEveryone = 2,
    /// 仅好友可见
    RCUserProfileVisibilityFriendVisible = 3,
};

/// 性别
typedef NS_ENUM(NSInteger, RCUserGender) {
    RCUserGenderUnknown = 0,  // 未知性别
    RCUserGenderMale = 1,     // 男性
    RCUserGenderFemale = 2,   // 女性
};

NS_ASSUME_NONNULL_BEGIN

@interface RCUserProfile : NSObject

/// 用户 id
@property (nonatomic, copy) NSString *userId;

/// 昵称
///
/// 长度不超过 32 个字符
@property (nonatomic, copy) NSString *name;

/// 头像地址
///
/// 长度不超过 128 个字符
@property (nonatomic, copy, nullable) NSString *portraitUri;

/// 用户应用号
///
/// 客户端无法直接修改
@property (nonatomic, copy) NSString *uniqueId;

/// 电子邮件
///
/// 长度不超过 128 个字符
@property (nonatomic, copy, nullable) NSString *email;

/// 生日
///
/// 长度不超过 32 个字符
@property (nonatomic, copy, nullable) NSString *birthday;

/// 性别
@property (nonatomic, assign) RCUserGender gender;

/// 所在地
///
/// 长度不超过 32 个字符
@property (nonatomic, copy, nullable) NSString *location;

/// 角色
///
/// 支持 0~100 以内数字
@property (nonatomic, assign) NSUInteger role;

/// 级别
///
/// 支持 0~100 以内数字
@property (nonatomic, assign) NSUInteger level;

/// 自定义用户扩展信息
///
/// 设置时请确保字典 key 值已在开发者后台配置过。
@property (nonatomic, copy, nullable) NSDictionary<NSString *, NSString *> *userExtProfile;

@end

NS_ASSUME_NONNULL_END
