//
//  RCSearchConversationResult.h
//  RongIMLib
//
//  Created by 杜立召 on 16/9/29.
//  Copyright © 2016 年 RongCloud. All rights reserved.
//

#import "RCConversation.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/// 搜索的会话结果
@interface RCSearchConversationResult : NSObject

/// 匹配的会话对象
@property (nonatomic, strong) RCConversation *conversation;

/// 会话匹配的消息条数
@property (nonatomic, assign) int matchCount;
@end

NS_ASSUME_NONNULL_END
