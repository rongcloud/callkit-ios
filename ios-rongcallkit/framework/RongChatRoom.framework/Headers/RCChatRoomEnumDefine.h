//
//  RCChatRoomEnumDefine.h
//  RongChatRoom
//
//  Created by 张改红 on 2020/8/12.
//  Copyright © 2020 张改红. All rights reserved.
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

#endif /* RCChatRoomEnumDefine_h */
