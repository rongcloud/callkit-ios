//
//  RCChatRoomSyncEvent.h
//  RongChatRoom
//
//  Created by chinaspx on 2023/5/6.
//  Copyright © 2023 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RCChatRoomEnumDefine.h"

NS_ASSUME_NONNULL_BEGIN

@interface RCChatRoomSyncEvent : NSObject
/*!
 聊天室 ID
 */
@property (nonatomic, copy) NSString *chatroomId;

/**
 同步通知的变更状态
 */
@property (nonatomic, assign) RCChatRoomSyncStatus status;

/**
 如果status是0的情况，区分离开类型：
 1，自己主动离开，
 2，多端加入互踢导致离开
 */
@property (nonatomic, assign) NSInteger reason;

/**
 同步通知的变更时间
 用户加入/退出/被踢的时间(毫秒时间戳)
 */
@property (nonatomic, assign) long long time;

/**
 附加信息
 */
@property (nonatomic, copy, nullable) NSString *extra;

@end

NS_ASSUME_NONNULL_END
