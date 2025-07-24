//
//  RCGroupEnum.h
//  RongIMLibCore
//
//  Created by Lang on 2024/7/19.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#ifndef RCGroupEnum_h
#define RCGroupEnum_h

/// 加入群权限
typedef NS_ENUM(NSInteger, RCGroupJoinPermission) {
    /// 需要群主验证（默认）
    RCGroupJoinPermissionOwnerVerify = 0,
    /// 不用验证
    RCGroupJoinPermissionFree = 1,
    /// 群主或群管理员
    RCGroupJoinPermissionOwnerOrManagerVerify = 2,
    /// 不允许任何人加入
    RCGroupJoinPermissionNoOneAllowed = 3,
};

/// 群操作权限
typedef NS_ENUM(NSInteger, RCGroupOperationPermission) {
    /// 群主（默认）
    RCGroupOperationPermissionOwner = 0,
    /// 群主或群管理员
    RCGroupOperationPermissionOwnerOrManager = 1,
    /// 所有人
    RCGroupOperationPermissionEveryone = 2
};

/// 邀请加入群组处理权限
typedef NS_ENUM(NSInteger, RCGroupInviteHandlePermission) {
    /// 不需要被邀请人同意（默认）
    RCGroupInviteHandlePermissionFree = 0,
    /// 需要被邀请人同意
    RCGroupInviteHandlePermissionInviteeVerify = 1,
};

/// 群成员资料编辑权限
typedef NS_ENUM(NSInteger, RCGroupMemberInfoEditPermission) {
    /// 群主、群管理员和自己（默认）
    RCGroupMemberInfoEditPermissionOwnerOrManagerOrSelf = 0,
    /// 群主和自己
    RCGroupMemberInfoEditPermissionOwnerOrSelf = 1,
    /// 仅自己
    RCGroupMemberInfoEditPermissionSelf = 2,
};

/// 群成员身份
typedef NS_ENUM(NSInteger, RCGroupMemberRole) {
    /// 不区分角色（未加群时无角色）
    RCGroupMemberRoleUndef = 0,
    /// 普通群成员
    RCGroupMemberRoleNormal = 1,
    /// 管理员
    RCGroupMemberRoleManager = 2,
    /// 群主
    RCGroupMemberRoleOwner = 3,
};

/// 操作类型枚举
typedef NS_ENUM(NSInteger, RCGroupOperation) {
    /// 创建群
    RCGroupOperationCreate = 0,

    /// 加入
    RCGroupOperationJoin = 1,

    /// 踢出
    RCGroupOperationKick = 2,

    /// 退出
    RCGroupOperationQuit = 3,

    /// 解散
    RCGroupOperationDismiss = 4,

    /// 添加管理员
    RCGroupOperationAddManager = 5,

    /// 移除管理员
    RCGroupOperationRemoveManager = 6,

    /// 转让群主
    RCGroupOperationTransferGroupOwner = 7,
};

/// 群申请状态
typedef NS_ENUM(NSInteger, RCGroupApplicationStatus) {
    /// 管理员待处理
    RCGroupApplicationStatusManagerUnHandled = 0,
    /// 管理员已拒绝
    RCGroupApplicationStatusManagerRefused = 1,
    /// 被邀请人待处理
    RCGroupApplicationStatusInviteeUnHandled = 2,
    /// 被邀请人拒绝
    RCGroupApplicationStatusInviteeRefused = 3,
    /// 已加入
    RCGroupApplicationStatusJoined = 4,
    /// 已过期
    RCGroupApplicationStatusExpired = 5,
};

/// 操作类型
typedef NS_ENUM(NSInteger, RCGroupOperationType) {
    /// 添加
    RCGroupOperationTypeAdd = 1,
    /// 删除
    RCGroupOperationTypeRemove = 2
};

/// 群申请方向
typedef NS_ENUM(NSInteger, RCGroupApplicationDirection) {
    /// 发出的申请
    RCGroupApplicationDirectionApplicationSent = 0,
    /// 发出的邀请
    RCGroupApplicationDirectionInvitationSent = 1,
    /// 收到的邀请
    RCGroupApplicationDirectionInvitationReceived = 2,
    /// 收到的申请
    RCGroupApplicationDirectionApplicationReceived = 3
};

/// 群申请类型
typedef NS_ENUM(NSInteger, RCGroupApplicationType) {
    /// 主动加入群组
    RCGroupApplicationTypeApplication = 0,
    /// 被邀请加入群组
    RCGroupApplicationTypeInvitation = 1,
};


#endif /* RCGroupEnum_h */
