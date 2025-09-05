//
//  RCModifyMessageParams.h
//  RongIMLibCore
//
//  Created by shuai shao on 2025/7/21.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class RCMessageContent;

/// 消息修改参数对象。
///
/// - Since: 5.26.0
@interface RCModifyMessageParams : NSObject

/// 消息唯一 ID。
@property (nonatomic, copy) NSString *messageUId;

/// 修改后的消息体。
@property (nonatomic, strong) RCMessageContent *messageContent;

@end

NS_ASSUME_NONNULL_END
