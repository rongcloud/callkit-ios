//
//  RCRefreshReferenceMessageParams.h
//  RongIMLibCore
//
//  Created by shuai shao on 2025/7/21.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class RCConversationIdentifier;

/// 刷新引用消息的参数对象。
///
/// - Since: 5.26.0
@interface RCRefreshReferenceMessageParams : NSObject

/// 会话标识。
@property (nonatomic, strong) RCConversationIdentifier *conversationIdentifier;

/// 消息唯一 ID 数组，最多 20 个。
@property (nonatomic, copy) NSArray<NSString *> *messageUIds;

@end

NS_ASSUME_NONNULL_END
