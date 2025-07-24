//
//  RCUserGroupStatusDelegate.h
//  RongIMLibCore
//
//  Created by RobinCui on 2023/1/3.
//  Copyright © 2023 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCStatusDefine.h>
#import <RongIMLibCore/RCChannelIdentifier.h>
#import <RongIMLibCore/RCConversationIdentifier.h>

NS_ASSUME_NONNULL_BEGIN


@protocol RCUserGroupStatusDelegate <NSObject>
/*!
 当前用户收到超级群下的用户组中解散通知
 
 - Parameter identifier: 会话标识[type:ConversationType_ULTRAGROUP ]
 - Parameter userGroupIds: 用户组ID列表
 
 - Since: 5.4.0
 */
- (void)userGroupDisbandFrom:(RCConversationIdentifier *)identifier userGroupIds:(NSArray<NSString *> *)userGroupIds;

/*!
 当前用户被添加到超级群下的用户组
 
 - Parameter identifier: 会话标识[type:ConversationType_ULTRAGROUP ]
 - Parameter userGroupIds: 用户组ID列表
 
 - Since: 5.4.0
 */
- (void)userAddedTo:(RCConversationIdentifier *)identifier userGroupIds:(NSArray<NSString *> *)userGroupIds;

/*!
 当前用户从到超级群下的用户组中被移除
 
 - Parameter identifier: 会话标识[type:ConversationType_ULTRAGROUP ]
 - Parameter userGroupIds: 用户组ID列表
 
 - Since: 5.4.0
 */
- (void)userRemovedFrom:(RCConversationIdentifier *)identifier userGroupIds:(NSArray<NSString *> *)userGroupIds;


/*!
 频道中绑定用户组回调
 
 - Parameter identifier: 频道标识[type:ConversationType_ULTRAGROUP ]
 - Parameter channelType: 频道类型
 - Parameter userGroupIds: 用户组ID列表
 
 - Since: 5.4.0
 */
- (void)userGroupBindTo:(RCChannelIdentifier *)identifier
            channelType:(RCUltraGroupChannelType)channelType
           userGroupIds:(NSArray<NSString *> *)userGroupIds;

/*!
 频道解绑用户组回调
 
 - Parameter identifier: 频道标识[type:ConversationType_ULTRAGROUP ]
 - Parameter channelType: 频道类型
 - Parameter userGroupIds: 用户组ID列表
 
 - Since: 5.4.0
 */
- (void)userGroupUnbindFrom:(RCChannelIdentifier *)identifier
                channelType:(RCUltraGroupChannelType)channelType
               userGroupIds:(NSArray<NSString *> *)userGroupIds;
@end

NS_ASSUME_NONNULL_END
