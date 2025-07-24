//
//  RCConversationIdentifier.h
//  RongIMLib
//
//  Created by 张改红 on 2021/1/27.
//  Copyright © 2021 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCStatusDefine.h>

NS_ASSUME_NONNULL_BEGIN

/// 会话标识
@interface RCConversationIdentifier : NSObject
/// 会话类型
@property (nonatomic, assign) RCConversationType type;
/// 会话 ID
@property (nonatomic, copy) NSString *targetId;

/// 频道 ID
/// - Since: 5.6.7
@property (nonatomic, copy, nullable) NSString *channelId;


/// 初始化方法
///
/// - Parameter type: 会话类型
/// - Parameter targetId: 会话 ID
- (instancetype)initWithConversationIdentifier:(RCConversationType)type targetId:(NSString *)targetId;

/// 初始化方法
///
/// - Parameter type: 会话类型
/// - Parameter targetId: 会话 id
/// - Parameter channel: 频道 id
/// - Since: 5.6.7
- (instancetype)initWithConversationIdentifier:(RCConversationType)type
                                      targetId:(NSString *)targetId
                                     channelId:(nullable NSString *)channelId;

@end

NS_ASSUME_NONNULL_END
