//
//  RCGroupReadReceiptV2Manager.h
//  RongIMLibCore
//
//  Created by 张改红 on 2021/3/9.
//  Copyright © 2021 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCGroupMessageReaderV2.h>
#import <RongIMLibCore/RCMessage.h>
#import <RongIMLibCore/RCGroupReadReceiptV2Protocol.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCGroupReadReceiptV2Manager : NSObject
/// 获取单例类
+ (instancetype)sharedManager;

/// 群已读回执代理
@property (nonatomic, weak, nullable) id<RCGroupReadReceiptV2Delegate> groupReadReceiptV2Delegate;

/*!
 发送阅读回执

 - Parameter conversationType: 会话类型
 - Parameter targetId: 会话 ID
 - Parameter channelId: 所属会话的业务标识
 - Parameter messageList: 已经阅读了的消息列表
 - Parameter successBlock: 发送成功的回调
 - Parameter errorBlock: 发送失败的回调[nErrorCode: 失败的错误码]

 当用户阅读了需要阅读回执的消息，可以通过此接口发送阅读回执，消息的发送方即可直接知道那些人已经阅读。

 - Remark: 高级功能
 */
- (void)sendReadReceiptResponse:(RCConversationType)conversationType
                       targetId:(NSString *)targetId
                      channelId:(nullable NSString *)channelId
                    messageList:(NSArray<RCMessage *> *)messageList
                        success:(nullable void (^)(void))successBlock
                          error:(nullable void (^)(RCErrorCode nErrorCode))errorBlock;

/*!
 获取群消息已读用户列表
 
 - Parameter message: 消息体
 - Parameter successBlock: 同步成功的回调
 - Parameter errorBlock: 同步失败的回调[nErrorCode: 失败的错误码]

 此方法不支持超级群的会话类型。
 
 - Remark: 高级功能
 */
- (void)getGroupMessageReaderList:(RCMessage *)message
                          success:(nullable void (^)(NSArray<RCGroupMessageReaderV2 *> *_Nullable readerList,
                                                     int totalCount))successBlock
                            error:(nullable void (^)(RCErrorCode nErrorCode))errorBlock;
@end

NS_ASSUME_NONNULL_END
