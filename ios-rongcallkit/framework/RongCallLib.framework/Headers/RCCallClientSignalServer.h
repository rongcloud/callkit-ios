//
//  RCCallClientSignalServer.h
//  RongCallLib
//
//  Created by RongCloud on 2017/7/25.
//  Copyright © 2017年 Rong Cloud. All rights reserved.
//

#ifndef RCCallClientSignalServer_h
#define RCCallClientSignalServer_h
#import <RongCallLib/RongCallLib.h>
#import "RCCallSummaryMessage.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 信令服务代理
 */
@protocol RCCallSignalServerDelegate <NSObject>

/*!
 获取通话参与者的唯一媒体ID, 必须保证每次电话会议的每个人的媒体ID都是全局唯一的

 @param successBlock  为当前用户分配的媒体Id成功的回调
 @param errorBlcok    获取媒体Id失败的回调
 @discussion
 获取通话参与者的唯一媒体ID, 必须保证每次电话会议的每个人的媒体ID都是全局唯一的
 
 @remarks 代理
 */
- (void)getUniqueMediaId:(nullable void (^)(NSString *mediaId))successBlock error:(nullable void (^)(int errorCode))errorBlcok;

/*!
 发送 VoIP 信令消息

 @param messageContent  消息内容
 @param toUserIdList    接收者的Id
 @param pushContent     pushContent
 @param pushData        pushData
 @param successBlock    成功的回调
 @param errorBlcok      失败的回调
 @discussion
 发送 VoIP 信令消息
 
 @remarks 代理
 */
- (void)sendVoipSignalMessage:(RCMessageContent *)messageContent
                 toUserIdList:(NSArray<NSString *> *)toUserIdList
                  pushContent:(nullable NSString *)pushContent
                     pushData:(nullable NSString *)pushData
                      success:(nullable void (^)(void))successBlock
                        error:(nullable void (^)(int errorCode))errorBlcok;

/*!
 VoIP 通话结束返回的统计信息
 
 @param summary  通话统计
 @discussion
 VoIP 通话结束返回的统计信息
 
 @remarks 代理
 */
- (void)onVoipCallSummary:(RCCallSummaryMessage *)summary;

@end

NS_ASSUME_NONNULL_END

#endif /* RCCallClientSignalServer_h */
