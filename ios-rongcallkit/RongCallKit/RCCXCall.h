//
//  RCCXCall.h
//  RongCallKit
//
//  Created by LiFei on 2018/1/17.
//  Copyright © 2018年 Rong Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

/// 默认不开启 系统 Callkit 功能
#define PUBLIC 1

/*!
 融云适配苹果 CallKit 核心类
 */
@interface RCCXCall : NSObject

/*!
 收到呼叫时, 是否直接显示已接听页面
 从后台进入App时为 YES , 不显示来电页面, 直接显示已接听页面
 App在前台时为 NO , 显示来电页面
 */
@property (nonatomic, assign) BOOL acceptedFromCallKit;

/*!
 获取 RCCXCall 单例

 @return RCCXCall 单例
 */
+ (instancetype)sharedInstance;

/*!
 通知苹果 Callkit 开始呼出电话
 
 @param callId 呼叫 id
 @param userId 呼叫用户 id，如果是多人通话则传多个用户 id，以:::分隔
 */
- (void)startCallId:(NSString *)callId userId:(NSString *)userId;

/*!
 通知苹果 Callkit 呼出电话已连接
 
 */
- (void)reportOutgoingCallConnected;

/*!
 通知苹果 Callkit 来电

 @param callId 通话 id
 @param inviterId 来电人用户 id
 @param userIdList 被邀请者的 userId 列表。nil 表示单人通话
 @param isVideo 是否视频通话。YES: video NO: audio
 */
- (void)reportIncomingCallWithCallId:(NSString *)callId
                             inviter:(NSString *)inviterId
                          userIdList:(NSArray<NSString *> *)userIdList
                             isVideo:(BOOL)isVideo;

/*!
 接通苹果 Callkit 通话
 */
- (void)answerCXCall;

/*!
 挂断苹果 Callkit 通话
 */
- (void)endCXCall;

/*!
 当系统来电接通时，如果没有激活苹果 Callkit 通话，则挂断 VOIP
 
 @param UUID 系统来电 UUID
 */
- (void)hangupIfNeedWithUUID:(NSString *)UUID;

@end
