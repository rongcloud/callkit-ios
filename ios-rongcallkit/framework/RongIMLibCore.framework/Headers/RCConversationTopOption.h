//
//  RCConversationTopOption.h
//  RongIMLibCore
//
//  Created by shuai shao on 2025/4/3.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 设置置顶的配置信息。
///
/// - Since: 5.20.0
@interface RCConversationTopOption : NSObject

/// 是否更新会话的操作时间。默认值为 YES。
@property (nonatomic, assign) BOOL needUpdateTime;

/// 会话不存在时，是否需要创建会话。默认值为 YES。
@property (nonatomic, assign) BOOL needCreateConversation;

/// 初始化方法。
/// - Parameter needUpdateTime: 是否更新时间。
/// - Parameter needCreateConversation: 是否创建会话。
- (instancetype)initWithNeedUpdateTime:(BOOL)needUpdateTime needCreateConversation:(BOOL)needCreateConversation;

@end

NS_ASSUME_NONNULL_END
