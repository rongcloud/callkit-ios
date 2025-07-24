//
//  RCCombineMessage.h
//  RongIMLib
//
//  Created by liyan on 2019/8/13.
//  Copyright © 2019 RongCloud. All rights reserved.
//

#import <RongIMLibCore/RongIMLibCore.h>

NS_ASSUME_NONNULL_BEGIN

/// 合并转发消息的类型名
#define RCCombineMessageTypeIdentifier @"RC:CombineMsg"


/// 合并转发消息类
///
/// 合并转发消息，此消息会进行存储并计入未读消息数。
///
/// 该消息不支持超级群的会话类型。
///
/// - Remark: 内容类消息
@interface RCCombineMessage : RCMediaMessageContent

/// 转发的消息展示的缩略内容列表 (格式是发送者：缩略内容)
@property (nonatomic, strong) NSArray *summaryList;

/// 转发的全部消息的发送者名称列表（单聊是经过排重的，群聊是群组名称）
@property (nonatomic, strong) NSArray *nameList;

/// 转发的消息会话类型（目前仅支持单聊和群聊）
@property (nonatomic, assign) RCConversationType conversationType;


/// 初始化 RCCombineMessage 消息
///
/// - Parameter summaryList: 转发的消息展示的缩略内容列表
/// - Parameter nameList: 转发的全部消息的发送者名称列表（单聊是经过排重的，群聊是群组名称）
/// - Parameter conversationType: 转发的消息会话类型
/// - Parameter content: 转发的内容
///
/// - Returns: 消息对象
+ (instancetype)messageWithSummaryList:(NSArray *)summaryList
                              nameList:(NSArray *)nameList
                      conversationType:(RCConversationType)conversationType
                               content:(NSString *)content;

@end

NS_ASSUME_NONNULL_END
