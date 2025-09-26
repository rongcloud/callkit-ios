//
//  RCConversationBatchDeletionParams.h
//  RongIMLibCore
//
//  Created by RongCloud on 2025/8/5.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
@class RCConversationIdentifier;
@interface RCConversationBatchDeletionParams : NSObject

/// 待删除的会话列表，最多同时删除 100 个会话
@property (nonatomic, copy) NSArray<RCConversationIdentifier *> *identifiers;

/// 是否同步删除服务器端会话
@property (nonatomic, assign) BOOL deleteRemotely;

///是否同步删除会话中的历史消息
/// 1. 当 deleteRemotely && deleteMessages 为 YES 时，将同时删除本地和远端会话中的历史消息
/// 2. 当 deleteRemotely 为 NO 而 deleteMessages 为 YES 时，只删除本地会话中的历史消息
/// 3. 当 deleteMessages 为 NO，只删会话
@property (nonatomic, assign) BOOL deleteMessages;

@end

NS_ASSUME_NONNULL_END
