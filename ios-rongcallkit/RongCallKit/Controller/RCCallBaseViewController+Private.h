//
//  RCCallBaseViewController+Private.h
//  RongCallKit
//
//  Created by RongCloud on 25/12/5.
//  Copyright © 2025年 RongCloud. All rights reserved.
//

#import "RCCallBaseViewController.h"

@interface RCCallBaseViewController (Private)

- (instancetype)initWithIncomingCall:(RCCallSession *)callSession;
- (instancetype)initWithOutgoingCall:(RCConversationType)conversationType
                            targetId:(NSString *)targetId
                           mediaType:(RCCallMediaType)mediaType
                          userIdList:(NSArray *)userIdList;
- (instancetype)initWithOutgoingCrossCall:(RCConversationType)conversationType
                                 targetId:(NSString *)targetId
                                mediaType:(RCCallMediaType)mediaType
                               userIdList:(NSArray *)userIdList;
- (instancetype)initWithActiveCall:(RCCallSession *)callSession;

- (void)hangupButtonClicked;
- (void)inviteUserButtonClicked;

/*!
 若需要则先弹出防诈提醒，用户确认后执行 continueBlock，取消则挂断通话。

 @discussion
 当防诈开关开启、且本次通话尚未提示过时，弹出防诈 Alert：
 - 点击「确认」：关闭 Alert 并执行 continueBlock（如系统权限检查等后续流程）。
 - 点击「取消」：调用 hangupButtonClicked 挂断当前通话。
 其余情况（开关关闭 / 已提示过 / 从最小化恢复的通话）直接同步执行 continueBlock。
 子类应在 viewDidAppear: 中，将原本的后续流程（如权限检查）通过本方法包裹调用。

 @param continueBlock 用户确认或无需提醒时执行的后续流程
 */
- (void)rc_showAntiFraudTipIfNeededThen:(void (^)(void))continueBlock;

/*!
 主叫防诈延迟发起：用户确认后，呼叫邀请已真正发出、callSession 已就绪时的回调。

 @discussion
 仅在「防诈开关开启导致主叫被延迟发起」的场景下，用户点击确认后触发。
 基类默认会刷新布局；子类可覆写以重建依赖 callSession 的界面模型（如多人界面的用户列表、
 单人界面的远端信息）。覆写时应先调用 super。
 */
- (void)rc_didStartPendingOutgoingCall;

@end
