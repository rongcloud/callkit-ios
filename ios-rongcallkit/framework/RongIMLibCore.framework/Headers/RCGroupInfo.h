//
//  RCGroupInfo.h
//  RongIMLibCore
//
//  Created by Lang on 2024/7/19.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <RongIMLibCore/RCGroupEnum.h>


NS_ASSUME_NONNULL_BEGIN

/// 群组信息属性 key 值
typedef NSString *RCGroupInfoKeys NS_STRING_ENUM;

/// 群名称 key
FOUNDATION_EXPORT RCGroupInfoKeys const RCGroupInfoKeysName;
/// 群头像 URL 地址 key
FOUNDATION_EXPORT RCGroupInfoKeys const RCGroupInfoKeysPortraitUri;
/// 群简介 key
FOUNDATION_EXPORT RCGroupInfoKeys const RCGroupInfoKeysIntroduction;
/// 群公告 key
FOUNDATION_EXPORT RCGroupInfoKeys const RCGroupInfoKeysNotice;
/// 主动加入群权限 key
FOUNDATION_EXPORT RCGroupInfoKeys const RCGroupInfoKeysJoinPermission;
/// 将群成员移出群组设置 key
FOUNDATION_EXPORT RCGroupInfoKeys const RCGroupInfoKeysRemoveMemberPerm;
/// 谁可以邀请他人入群 key
FOUNDATION_EXPORT RCGroupInfoKeys const RCGroupInfoKeysInvitePermission;
/// 被邀请加入群组权限 key
FOUNDATION_EXPORT RCGroupInfoKeys const RCGroupInfoKeysInviteHandlePermission;
/// 修改群资料权限 key
FOUNDATION_EXPORT RCGroupInfoKeys const RCGroupInfoKeysGroupInfoEditPermission;
/// 修改群成员资料权限 key
FOUNDATION_EXPORT RCGroupInfoKeys const RCGroupInfoKeysMemberInfoEditPermission;
/// 群扩展信息 key
FOUNDATION_EXPORT RCGroupInfoKeys const RCGroupInfoKeysExtProfile;

@interface RCGroupInfo : NSObject

/// 群组 ID
@property (nonatomic, copy) NSString *groupId;

/// 群名称
@property (nonatomic, copy) NSString *groupName;

/// 群头像 URL 地址，长度不超过 1024 个字符
@property (nonatomic, copy, nullable) NSString *portraitUri;

/// 群简介，长度不超过 512 个字符
@property (nonatomic, copy, nullable) NSString *introduction;

/// 群公告，长度不超过 1024 个字符
@property (nonatomic, copy, nullable) NSString *notice;

/// 扩展信息，
/// 自定义属性需要通过开发者后台或 服务端 API 设置后才能使用，否则返回设置失败
@property (nonatomic, strong) NSDictionary<NSString *, NSString *> *extProfile;

/// 主动加入群权限
/// 默认需要群主验证
@property (nonatomic, assign) RCGroupJoinPermission joinPermission;

/// 移除群成员权限
/// 默认群主
@property (nonatomic, assign) RCGroupOperationPermission removeMemberPermission;

/// 邀请他人入群权限
/// 默认群主
@property (nonatomic, assign) RCGroupOperationPermission invitePermission;

/// 被邀请加入群组权限
/// 默认不需要被邀请人同意
@property (nonatomic, assign) RCGroupInviteHandlePermission inviteHandlePermission;

/// 修改群资料权限
/// 默认群主
@property (nonatomic, assign) RCGroupOperationPermission groupInfoEditPermission;

/// 修改群成员资料权限
/// 默认群主、群管理员、自已都可以
@property (nonatomic, assign) RCGroupMemberInfoEditPermission memberInfoEditPermission;

#pragma mark - 只读属性

/// 创建者 userId
@property (nonatomic, copy, readonly) NSString *creatorId;

/// 群主 userId
@property (nonatomic, copy, readonly) NSString *ownerId;

/// 群备注
/// 自己设置备注名，其他人看不到
@property (nonatomic, copy, readonly, nullable) NSString *remark;

/// 群组创建时间。
@property (nonatomic, assign, readonly) long long createTime;

/// 群当前成员人数。
@property (nonatomic, assign, readonly) NSUInteger membersCount;

/// 当前用户加入时间：用户多次加入群组时，以最后一次加入时间为准
@property (nonatomic, assign, readonly) long long joinedTime;

/// 我的群身份
@property (nonatomic, assign, readonly) RCGroupMemberRole role;

@end

NS_ASSUME_NONNULL_END
