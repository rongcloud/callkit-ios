//
//  RCConversationsContainingRobotsOption.h
//  RongIMLibCore
//
//  Created by huan xu on 2025/9/3.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
///- Since 5.28.0
@interface RCConversationsContainingRobotsOption : NSObject

/// 会话类型列表，RCConversationType 转换 NSNumber 的集合，目前仅支持单聊会话、系统会话。
/// 非法值返错误码 34284（包含非单聊、系统会话，或长度为 0）
@property (nonatomic, copy)NSArray<NSNumber *> *conversationTypes;

/// 获取数量，有效范围 [1, 100]，返错误码 34232
@property (nonatomic, assign)NSInteger count;

/// 时间戳，单位毫秒，默认值为 0，表示从最新的会话开始获取
@property (nonatomic, assign)NSTimeInterval timestamp;

/// 是否置顶优先级，默认值为 NO
@property (nonatomic, assign)BOOL topPriority;

@end

NS_ASSUME_NONNULL_END
