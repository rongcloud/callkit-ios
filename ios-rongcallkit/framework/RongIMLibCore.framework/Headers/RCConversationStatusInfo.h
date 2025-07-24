//
//  RCConversationStatusInfo.h
//  RongIMLib
//
//  Created by liyan on 2020/5/13.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCStatusDefine.h>

/// 会话状态类型

typedef NS_ENUM(NSUInteger, RCConversationStatusType) {
    /// 免打扰
    RCConversationStatusType_Mute = 1,

    /// 置顶
    RCConversationStatusType_Top = 2,
    /// 翻译
    RCConversationStatusType_Translation = 4
};

NS_ASSUME_NONNULL_BEGIN

@interface RCConversationStatusInfo : NSObject

/// 会话类型
@property (nonatomic, assign) RCConversationType conversationType;

/// 会话 ID
@property (nonatomic, copy) NSString *targetId;

/// 所属会话的业务标识
@property (nonatomic, copy, nullable) NSString *channelId;

/// 会话状态改变的类型
@property (nonatomic, assign) RCConversationStatusType conversationStatusType;

/*!
 如果 conversationStatusType  = RCConversationStatusType_Mute，conversationStatusValue = 1 是提醒，conversationStatusValue = 0 是免打扰。
 
 如果 conversationStatusType  = RCConversationStatusType_Top，conversationStatusValue = 0 是不置顶，conversationStatusValue = 1 是置顶。
 
 如果 conversationStatusType  = RCConversationStatusType_Translation，conversationStatusValue 代表以下功能：
 RCTranslateStrategyDefault = 0, 默认，会跟随用户级别的自动翻译方式。
 RCTranslateStrategyAutoOn = 1,自动翻译
 RCTranslateStrategyAutoOff = 2， 手动翻译

 
*/
@property (nonatomic, assign) int conversationStatusValue;

/*!
 会话免打扰类型
 
 当 conversationStatusType  = RCConversationStatusType_Mute 时，notificationLevel 值为有效值。
*/
@property (nonatomic, assign) RCPushNotificationLevel notificationLevel;

@end

@interface RCConversationStatusInfo (deprecated)

@property (nonatomic, assign) int conversationStatusvalue __deprecated_msg("Use conversationStatusValue instead");

@end

NS_ASSUME_NONNULL_END
