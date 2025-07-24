//
//  RCBlockedMessageInfo.h
//  RongIMLibCore
//
//  Created by 孙浩 on 2021/7/9.
//  Copyright © 2021 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCStatusDefine.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCBlockedMessageInfo : NSObject

/// 会话类型
@property (nonatomic, assign) RCConversationType type;

/// 会话 ID
@property (nonatomic, copy) NSString *targetId;

/// 频道 ID
@property (nonatomic, copy, nullable) NSString *channelId;

/// 被拦截的消息 UID
@property (nonatomic, copy) NSString *blockedMsgUId;

/// 拦截原因
/// 1. 全局敏感词：命中了融云内置的全局敏感词
/// 2. 自定义敏感词拦截：命中了客户在融云自定义的敏感词
/// 3. 第三方审核拦截：命中了第三方（数美）或消息回调服务决定不下发的状态
@property (nonatomic, assign) RCMessageBlockType blockType;

/// 附加信息
@property (nonatomic, copy, nullable) NSString *extra;

/// 消息的发送时间（Unix 时间戳、毫秒）
@property (nonatomic, assign) long long sentTime;

/// 消息源触发类型。0 默认，原始消息；1 消息扩展；2 消息修改
@property (nonatomic, assign) NSInteger sourceType;

/// 源内容 Json 字符串。sourceType 为 1、2 时返回；1 扩展内容，2 消息内容
///
/// - sourceType 为 0，sourceContent 内容为 nil
/// - sourceType 为 1，sourceContent 是扩展内容，示例 {"mid":"xxx-xxx-xxx-xxx","put":{"key":"敏感词"}}
/// - sourceType 为 2，sourceContent 是消息修改后内容，示例 {"content":"敏感词"}
@property (nonatomic, copy) NSString *sourceContent;

/// RCBlockedMessageInfo 初始化方法
///
/// - Parameter type: 会话类型
/// - Parameter targetId: 会话 ID
/// - Parameter blockedMsgUId: 被拦截的消息 ID
/// - Parameter blockType: 会话 id
- (instancetype)initWithConversationType:(RCConversationType)type
                                targetId:(NSString *)targetId
                           blockedMsgUId:(NSString *)blockedMsgUId
                               blockType:(RCMessageBlockType)blockType;

@end

NS_ASSUME_NONNULL_END
