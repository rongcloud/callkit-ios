//
//  RCMessageReactionDelegate.h
//  RongIMLibCore
//
//  Created by RC on 2026/6/2.
//  Copyright © 2026 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCMessageReactionEventData.h>

NS_ASSUME_NONNULL_BEGIN

/// 消息回应变更监听器。
///
/// - Since: 5.42.0
@protocol RCMessageReactionDelegate <NSObject>

/// 消息回应变更通知。
///
/// - Parameter reactions: 消息回应变更数据列表。
- (void)onMessageReactionChanged:(NSArray<RCMessageReactionEventData *> *)reactions;

@end

NS_ASSUME_NONNULL_END
