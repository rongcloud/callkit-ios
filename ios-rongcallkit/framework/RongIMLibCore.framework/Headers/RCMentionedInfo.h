//
//  RCMentionedInfo.h
//  RongIMLib
//
//  Created by 杜立召 on 16/7/6.
//  Copyright © 2016 年 RongCloud. All rights reserved.
//

#import <RongIMLibCore/RCStatusDefine.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 消息中的 @ 提醒信息对象
@interface RCMentionedInfo : NSObject

/// @ 提醒的类型
@property (nonatomic, assign) RCMentionedType type;

/// @ 的用户 ID 列表
///
/// 如果 type 是 @ 所有人，则可以传 nil
@property (nonatomic, strong, nullable) NSArray<NSString *> *userIdList;

/// 包含 @ 提醒的消息，本地通知和远程推送显示的内容
///
/// 如果是 nil , 则按默认格式显示 [有人 @ 你]
@property (nonatomic, copy, nullable) NSString *mentionedContent;

/// 是否 @ 了我
@property (nonatomic, readonly) BOOL isMentionedMe;

/// 初始化 @ 提醒信息
///
/// - Parameter type: @ 提醒的类型
/// - Parameter userIdList: @ 的用户 ID 列表
/// - Parameter mentionedContent: @ Push 内容
///
/// - Returns: @ 提醒信息的对象
- (instancetype)initWithMentionedType:(RCMentionedType)type
                           userIdList:(nullable NSArray<NSString *> *)userIdList
                     mentionedContent:(nullable NSString *)mentionedContent;

@end

NS_ASSUME_NONNULL_END
