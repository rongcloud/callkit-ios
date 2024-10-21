//
//  RCFriendEnum.h
//  RongIMLibCore
//
//  Created by Lang on 2024/8/12.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#ifndef RCFriendEnum_h
#define RCFriendEnum_h

/// 添加好友权限
typedef NS_ENUM(NSInteger, RCFriendAddPermission) {
    /// 不需本人同意，任何人直接添加好友
    RCFriendAddPermissionFree = 1,
    /// 需要用户同意添加好友
    RCFriendAddPermissionNeedVerify = 2,
    /// 不允许任何人添加好友
    RCFriendAddPermissionNoOneAllowed = 3,
};

/// - 好友方向类型：双向好友（目前只支持双向好友）
typedef NS_ENUM(NSInteger, RCDirectionType) {
    /// 双向好友
    RCDirectionTypeBoth = 2,
};

/// 好友关系类型
typedef NS_ENUM(NSInteger, RCFriendRelationType) {
    /// 不在双方的好友列表中
    RCFriendRelationTypeNone = 0,
    /// 在我的好友列表中
    RCFriendRelationTypeInMyFriendList = 1,
    /// 仅在对方的好友列表中
    RCFriendRelationTypeInOtherFriendList = 2,
    /// 在双方的好友列表中
    RCFriendRelationTypeBothWay = 3,
};

/// 好友申请类型
typedef NS_ENUM(NSInteger, RCFriendApplicationType) {
    /// 发送的好友请求
    RCFriendApplicationTypeSent = 1,
    /// 接收的好友请求
    RCFriendApplicationTypeReceived = 2
};

/// 好友申请状态
typedef NS_ENUM(NSInteger, RCFriendApplicationStatus) {
    /// 未处理
    RCFriendApplicationStatusUnHandled = 0,
    /// 已同意
    RCFriendApplicationStatusAccepted = 1,
    /// 已拒绝
    RCFriendApplicationStatusRefused = 2,
    /// 已过期
    RCFriendApplicationStatusExpired = 3,
};

/// 好友列表查询方向
typedef NS_ENUM(NSInteger, RCQueryFriendsDirectionType) {
    /// 双向好友
    RCQueryFriendsDirectionTypeBoth = 2,
};


#endif /* RCFriendEnum_h */
