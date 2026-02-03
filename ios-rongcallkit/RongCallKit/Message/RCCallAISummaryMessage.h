//
//  RCCallAISummaryMessage.h
//  RongCallKit
//
//  Created by RongCloud on 25/12/8.
//  Copyright © 2025年 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RongIMLibCore.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 通话智能总结的类型名
 */
#define RCCallAISummaryMessageTypeIdentifier @"RC:CallAISummary"

/*!
 通话只能总结消息类

 @discussion 通话智能总结消息类，此消息会进行存储并计入未读消息数。
 */
@interface RCCallAISummaryMessage : RCMessageContent

/*!
 智能总结任务 ID
 */
@property (nonatomic, strong) NSString *taskId;

/*!
 智能总结发生的 Call ID
 */
@property (nonatomic, strong) NSString *callId;

/*!
 通话开始时间
 */
@property (nonatomic, assign) NSTimeInterval startTime;

/*!
 初始化方法
 */
- (instancetype)initWithTaskId:(NSString *)taskId
                        callId:(NSString *)callId
                     startTime:(NSTimeInterval)startTime;

@end

NS_ASSUME_NONNULL_END
