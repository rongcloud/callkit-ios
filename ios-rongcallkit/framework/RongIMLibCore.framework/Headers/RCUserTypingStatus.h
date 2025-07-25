//
//  RCUserTypingStatus.h
//  RongIMLib
//
//  Created by 岑裕 on 16/1/8.
//  Copyright © 2016 年 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 用户输入状态类
@interface RCUserTypingStatus : NSObject

/// 当前正在输入的用户 ID
@property (nonatomic, copy) NSString *userId;

/// 当前正在输入的消息类型名
///
/// contentType 为用户当前正在编辑的消息类型名，即 RCMessageContent 中 getObjectName 的返回值。
/// 如文本消息，应该传类型名"RC:TxtMsg"。
@property (nonatomic, copy) NSString *contentType;

/// 用户输入状态消息发送时间
@property (nonatomic, assign) long long sentTime;

/// 初始化用户输入状态对象
///
/// - Parameter userId: 当前正在输入的用户 ID
/// - Parameter objectName: 当前正在输入的消息类型名
///
/// - Returns: 用户输入状态对象
- (instancetype)initWithUserId:(NSString *)userId contentType:(NSString *)objectName;

@end

NS_ASSUME_NONNULL_END
