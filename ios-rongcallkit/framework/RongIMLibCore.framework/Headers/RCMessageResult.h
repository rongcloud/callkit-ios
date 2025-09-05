//
//  RCMessageResult.h
//  RongIMLibCore
//
//  Created by shuai shao on 2025/7/14.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCErrorCode.h>

NS_ASSUME_NONNULL_BEGIN

@class RCMessage;

/// 消息查询结果。
///
/// - Since: 5.26.0
@interface RCMessageResult : NSObject

/// 消息唯一 ID。
@property (nonatomic, readonly, copy) NSString *messageUId;

/// 查询到的消息。
@property (nonatomic, readonly, strong, nullable) RCMessage *message;

/// 查询的错误码。
@property (nonatomic, readonly, assign) RCErrorCode code;

@end

NS_ASSUME_NONNULL_END
