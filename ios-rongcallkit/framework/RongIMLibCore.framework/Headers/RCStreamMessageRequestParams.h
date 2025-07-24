//
//  RCStreamMessageRequest.h
//  RongIMLibCore
//
//  Created by shuai shao on 2025/2/20.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 流式消息一次片段的信息。
@interface RCStreamMessageChunkInfo : NSObject

/// 流消息增量数据。
@property (nonatomic, copy) NSString *content;

@end

@interface RCStreamMessageRequestParams : NSObject

/// 消息唯一 ID
@property (nonatomic, copy) NSString *messageUId;

@end

NS_ASSUME_NONNULL_END
