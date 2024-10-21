//
//  RCChatRoomMemberActionModel.h
//  RongChatRoom
//
//  Created by chinaspx on 2023/10/18.
//  Copyright © 2023 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class RCChatRoomMemberAction;

@interface RCChatRoomMemberActionModel : NSObject

/// 聊天室 ID
@property (nonatomic, readonly) NSString *roomId;

/// 聊天室成员变更信息
@property (nonatomic, strong, readonly) NSArray<RCChatRoomMemberAction *> *chatRoomMemberActions;

/// 当前的聊天室人数
@property (nonatomic, assign, readonly) NSUInteger memberCount;


/// 初始化方法
/// - Parameter roomId: 聊天室 ID
/// - Parameter memberActions: 聊天室成员变更信息
/// - Parameter memberCount: 当前的聊天室人数
///
- (instancetype)initWithRoomId:(NSString *)roomId
                 memberActions:(NSArray<RCChatRoomMemberAction *> *)memberActions
                   memberCount:(NSUInteger)memberCount;
@end

NS_ASSUME_NONNULL_END
