//
//  RCCallAISummaryController.h
//  RongCallKit
//
//  Created by RongCloud on 25/12/8.
//  Copyright © 2025年 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 AI 通话智能总结详情页
 */
@interface RCCallAISummaryController : UIViewController

/// 内容更新回调，当获取到新的总结内容时调用
@property (nonatomic, copy, nullable) void (^contentUpdateCallback)(NSString *content);

- (instancetype)initWithTaskId:(NSString *)taskId
                        callId:(NSString *)callId
     displayStartSummaryButton:(BOOL)displayStartSummaryButton
              isSummaryStarted:(BOOL)isSummaryStarted
                  isASRStarted:(BOOL)isASRStarted
                autoGenSummary:(BOOL)autoGenSummary
                defaultContent:(nullable NSString *)defaultContent;

@end

NS_ASSUME_NONNULL_END

