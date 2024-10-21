//
//  RCJoinChatRoomResponse.h
//  RongChatRoom
//
//  Created by chinaspx on 2023/7/31.
//  Copyright © 2023 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCJoinChatRoomResponse : NSObject

// 创建时间（毫秒时间戳）
@property (nonatomic, assign) long long createTime;

// 成员数量
@property (nonatomic, assign) NSInteger memberCount;

// 是否全局禁言
@property (nonatomic, assign) BOOL isAllChatRoomBanned;

// 是否当前用户被禁言
@property (nonatomic, assign) BOOL isCurrentUserBanned;

// 当前用户是否在此聊天室被禁言
@property (nonatomic, assign) BOOL isCurrentChatRoomBanned;

// 当前用户是否在此聊天室的白名单中
@property (nonatomic, assign) BOOL isCurrentChatRoomInWhitelist;

// 加入时间（毫秒时间戳）
// - Since: 5.10.2
@property (nonatomic, assign) long long joinTime;

@end

NS_ASSUME_NONNULL_END
