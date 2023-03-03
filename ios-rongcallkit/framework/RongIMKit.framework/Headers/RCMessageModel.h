//
//  RCMessageModel.h
//  RongIMKit
//
//  Created by xugang on 15/1/22.
//  Copyright (c) 2015年 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RongIMLibCore.h>

/*!
 消息Cell的数据模型类
 */
@interface RCMessageModel : NSObject

/*!
 是否显示时间
 */
@property (nonatomic, assign) BOOL isDisplayMessageTime;

/*!
 是否显示用户名
 */
@property (nonatomic, assign) BOOL isDisplayNickname;

/*!
 用户信息
 */
@property (nonatomic, strong) RCUserInfo *userInfo;

/*!
 会话类型
 */
@property (nonatomic, assign) RCConversationType conversationType;

/*!
 目标会话ID
 */
@property (nonatomic, copy) NSString *targetId;

/*!
 消息ID
 */
@property (nonatomic, assign) long messageId;

/*!
 消息方向
 */
@property (nonatomic, assign) RCMessageDirection messageDirection;

/*!
 发送者的用户ID
 */
@property (nonatomic, copy) NSString *senderUserId;

/*!
 消息的接收状态
 */
@property (nonatomic, assign) RCReceivedStatus receivedStatus;

/*!
 消息的发送状态
 */
@property (nonatomic, assign) RCSentStatus sentStatus;

/*!
 消息的接收时间（Unix时间戳、毫秒）
 */
@property (nonatomic, assign) long long receivedTime;

/*!
 消息的发送时间（Unix时间戳、毫秒）
 */
@property (nonatomic, assign) long long sentTime;

/*!
 消息的类型名
 */
@property (nonatomic, copy) NSString *objectName;

/*!
 消息的内容
 */
@property (nonatomic, strong) RCMessageContent *content;

/*!
 阅读回执状态
 */
@property (nonatomic, strong) RCReadReceiptInfo *readReceiptInfo;

/*!
 消息的附加字段
 */
@property (nonatomic, copy) NSString *extra;

/*!
 消息展示时的Cell高度

 @discussion 用于大量消息的显示优化
 */
@property (nonatomic) CGSize cellSize;
/*!
 全局唯一ID

 @discussion 服务器消息唯一ID（在同一个Appkey下全局唯一）
 */
@property (nonatomic, copy) NSString *messageUId;

/*!
 消息是否可以发送请求回执

 */
@property (nonatomic, assign) BOOL isCanSendReadReceipt;

/*!
 已读人数

 */
@property (nonatomic, assign) NSInteger readReceiptCount;

/*!
 消息是否可以包含扩展信息
 
 @discussion 该属性在消息发送时确定，发送之后不能再做修改
 @discussion 扩展信息只支持单聊和群组，其它会话类型不能设置扩展信息
*/
@property (nonatomic, assign) BOOL canIncludeExpansion;

/*!
 消息扩展信息列表
 
 @discussion 扩展信息只支持单聊和群组，其它会话类型不能设置扩展信息
*/
@property (nonatomic, strong) NSDictionary<NSString *, NSString *> *expansionDic;

/*!
 初始化消息Cell的数据模型

 @param rcMessage   消息实体
 @return            消息Cell的数据模型对象
 */
+ (instancetype)modelWithMessage:(RCMessage *)rcMessage;

/*!
 初始化消息Cell的数据模型

 @param rcMessage   消息实体
 @return            消息Cell的数据模型对象
 */
- (instancetype)initWithMessage:(RCMessage *)rcMessage;
@end
