//
//  RCChatRoomEnumDefine.h
//  RongChatRoom
//
//  Created by 张改红 on 2020/8/12.
//  Copyright © 2020 张改红。All rights reserved.
//
#import <Foundation/Foundation.h>
#ifndef RCChatRoomEnumDefine_h
#define RCChatRoomEnumDefine_h

#pragma mark RCChatRoomStatus - 聊天室状态码
/*!
 聊天室状态码
 */
typedef NS_ENUM(NSInteger, RCChatRoomStatus) {
    /*!
     正在加入聊天室中
     */
    RCChatRoomStatus_Joining = 1,

    /*!
     加入聊天室成功
     */
    RCChatRoomStatus_Joined = 2,
    /*!
     加入聊天室失败
     */
    RCChatRoomStatus_JoinFailed = 3,

    /*!
     退出了聊天室
     */
    RCChatRoomStatus_Quited = 4,

    /*!
     聊天室被销毁
     */
    RCChatRoomStatus_Destroyed = 5,
    /*!
     聊天室被重置
     由于聊天室长时间不活跃，已经被系统回收。聊天室 KV 已经被清空，请开发者刷新界面。
     */
    RCChatRoomStatus_Reset = 6,

};

#pragma mark RCChatRoomMemberOrder - 聊天室成员排列顺序
/*!
 聊天室成员的排列顺序
 */
typedef NS_ENUM(NSUInteger, RCChatRoomMemberOrder) {
    /*!
     升序，返回最早加入的成员列表
     */
    RC_ChatRoom_Member_Asc = 1,

    /*!
     降序，返回最晚加入的成员列表
     */
    RC_ChatRoom_Member_Desc = 2,
};

#pragma mark RCChatRoomMemberActionType - 聊天室成员加入或退出
/*!
 聊天室成员加入或者退出
 */
typedef NS_ENUM(NSInteger, RCChatRoomMemberActionType) {
    /*!
     聊天室成员退出
     */
    RC_ChatRoom_Member_Quit = 0,

    /*!
     聊天室成员加入
     */
    RC_ChatRoom_Member_Join = 1,
};


#pragma mark RCChatRoomEvent - 聊天室事件
/*!
 聊天室多端登录同步时，消息中的状态
 */
typedef NS_ENUM(NSInteger, RCChatRoomSyncStatus) {
    /*!
     多端登录同步用户离开聊天室，
     1. 同一用户在一终端离开聊天室，通知另一终端
     2. 用户多端加入聊天室场景：用户在 Android 端加入聊天室，在 Web 端登录后又加入一个新的聊天室，自动将用户从上一个聊天室踢出
     被踢出聊天室中的所有成员，包括被踢出用户
     */
    RCChatRoomSyncStatusQuit = 0,

    /*!
     多端登录同步用户加入聊天室，
     同一用户在一终端加入聊天室，通知另一终端
     */
    RCChatRoomSyncStatusJoin = 1
};

/*!
 聊天室解封/封禁用户消息，操作类型枚举
 */
typedef NS_ENUM(NSInteger, RCChatRoomMemberOperateType) {
    /*!
     解封
     */
    RCChatRoomMemberOperateTypeDeblock = 0,

    /*!
     封禁
     */
    RCChatRoomMemberOperateTypeBlocked = 1
};


/*!
 聊天室禁言相关消息，操作类型枚举
 */
typedef NS_ENUM(NSInteger, RCChatRoomMemberBanType) {
    /*!
     解除指定聊天室中用户禁言
     */
    RCChatRoomMemberBanTypeUnmuteUsers = 0,

    /*!
     禁言指定聊天室中用户
     */
    RCChatRoomMemberBanTypeMuteUsers = 1,

    /*!
     解除聊天室全体禁言
     */
    RCChatRoomMemberBanTypeUnmuteAll = 2,

    /*!
     聊天室全体禁言
     */
    RCChatRoomMemberBanTypeMuteAll = 3,

    /*!
     移出禁言用户白名单
     */
    RCChatRoomMemberBanTypeRemoveWhitelist = 4,

    /*!
     添加禁言用户白名单
     */
    RCChatRoomMemberBanTypeAddWhitelist = 5,

    /*!
     解除用户聊天室全局禁言
     */
    RCChatRoomMemberBanTypeUnmuteGlobal = 6,

    /*!
     用户聊天室全局禁言
     */
    RCChatRoomMemberBanTypeMuteGlobal = 7
};

#endif /* RCChatRoomEnumDefine_h */
