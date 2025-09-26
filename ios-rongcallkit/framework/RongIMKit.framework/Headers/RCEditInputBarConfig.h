//
//  RCEditInputBarConfig.h
//  RongIMKit
//
//  Created by Lang on 2025/7/23.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RCMentionedStringRangeInfo.h"
#import <RongIMLibCore/RCReferenceMessage.h>

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

/// 被引用消息的状态。
@property (nonatomic, assign) RCReferenceMessageStatus referencedMsgStatus;

/// @ 信息
@property (nonatomic, copy, nullable) NSArray<RCMentionedStringRangeInfo *> *mentionedRangeInfo;

/// 初始化
- (instancetype)initWithData:(NSString *)data;

/// 序列化为字典
- (NSString *)encode;

@end

NS_ASSUME_NONNULL_END
