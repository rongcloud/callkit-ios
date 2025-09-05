//
//  RCEditInputBarConfig.h
//  RongIMKit
//
//  Created by Lang on 2025/7/23.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

@class RCMentionedInfo;

NS_ASSUME_NONNULL_BEGIN

@interface RCEditInputBarConfig : NSObject

/// 消息唯一标识
@property (nonatomic, copy, nullable) NSString *messageUId;

/// 消息发送时间
@property (nonatomic, assign) long long sentTime;

/// 编辑消息的文本内容
@property (nonatomic, copy, nullable) NSString *textContent;

/// 被引用消息发送者姓名
@property (nonatomic, copy, nullable) NSString *referencedSenderName;

/// 被引用消息内容
@property (nonatomic, copy, nullable) NSString *referencedContent;

/// @信息
@property (nonatomic, strong, nullable) RCMentionedInfo *mentionedInfo;

/// 缓存的编辑信息，用于恢复编辑状态时，传入 messageUId 和 cachedStateData
@property (nonatomic, copy, nullable) NSDictionary *cachedStateData;

@end

NS_ASSUME_NONNULL_END
