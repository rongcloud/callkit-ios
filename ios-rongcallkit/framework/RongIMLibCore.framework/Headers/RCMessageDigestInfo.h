//
//  RCMessageDigestInfo.h
//  RongIMLibCore
//
//  Created by RobinCui on 2022/8/3.
//  Copyright © 2022 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCStatusDefine.h>
NS_ASSUME_NONNULL_BEGIN

@interface RCMessageDigestInfo : NSObject
/*!
会话类型
*/
@property (nonatomic, assign) RCConversationType conversationType;

/*!
会话 ID
*/
@property (nonatomic, copy) NSString *targetId;

/*!
该会话的业务标识，长度限制 20 字符
*/
@property (nonatomic, copy) NSString *channelId;
/*!
消息的全局唯一 ID

服务器消息唯一 ID（在同一个 AppKey 下全局唯一）
*/
@property (nonatomic, copy) NSString *messageUid;

/*!
消息的发送时间（Unix时间戳、毫秒）
*/
@property (nonatomic, assign) long long sentTime;

/*!
消息是否 @所有人
*/
@property (nonatomic, assign) BOOL isMentionAll;


/*!
消息类型
*/
@property (nonatomic, copy) NSString *objectName;

@end

NS_ASSUME_NONNULL_END
