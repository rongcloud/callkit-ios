//
//  RCConversationModel.h
//  RongIMKit
//
//  Created by xugang on 15/1/22.
//  Copyright (c) 2015年 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RongIMLibCore.h>

/*!
 会话Cell数据模型的显示类型
 */
typedef NS_ENUM(NSUInteger, RCConversationModelType) {
    /*!
     默认显示
     */
    RC_CONVERSATION_MODEL_TYPE_NORMAL = 1,
    /*!
     聚合显示
     */
    RC_CONVERSATION_MODEL_TYPE_COLLECTION = 2,
    /*!
     用户自定义的会话显示
     */
    RC_CONVERSATION_MODEL_TYPE_CUSTOMIZATION = 3,
    /*!
     公众服务的会话显示
     */
    RC_CONVERSATION_MODEL_TYPE_PUBLIC_SERVICE = 4
};

NS_ASSUME_NONNULL_BEGIN

/*!
 会话Cell的数据模型类
 */
@interface RCConversationModel : NSObject

/*!
 会话Cell数据模型的显示类型
 */
@property (nonatomic, assign) RCConversationModelType conversationModelType;

/*!
 用户自定义的扩展数据
 */
@property (nonatomic, strong, nullable) id extend;

/*!
 会话类型
 */
@property (nonatomic, assign) RCConversationType conversationType;

/*!
 目标会话ID
 */
@property (nonatomic, copy) NSString *targetId;

/*!
 目标频道会话ID
 */
@property (nonatomic, copy, nullable) NSString *channelId;

/*!
 会话的标题
 */
@property (nonatomic, copy, nullable) NSString *conversationTitle;

/*!
 会话中的未读消息数
 */
@property (nonatomic, assign) NSInteger unreadMessageCount;

/*!
 当前会话是否置顶
 */
@property (nonatomic, assign) BOOL isTop;

/*!
当前会话是否是免打扰状态
*/
@property (nonatomic, assign) RCConversationNotificationStatus blockStatus;

/*!
 置顶Cell的背景颜色
 */
@property (nonatomic, strong, nullable) UIColor *topCellBackgroundColor;

/*!
 非置顶的Cell的背景颜色
 */
@property (nonatomic, strong, nullable) UIColor *cellBackgroundColor;

/*!
 会话中最后一条消息的接收状态
 */
@property (nonatomic, assign) RCReceivedStatus receivedStatus __deprecated_msg("Use receivedStatusInfo instead");

/// 消息的接收状态类(针对接收的消息生效)
@property (nonatomic, strong, nullable) RCReceivedStatusInfo *receivedStatusInfo;

/*!
 会话中最后一条消息的发送状态
 */
@property (nonatomic, assign) RCSentStatus sentStatus;

/*!
 会话中最后一条消息的接收时间（Unix时间戳、毫秒）
 */
@property (nonatomic, assign) long long receivedTime;

/*!
 会话中最后一条消息的发送时间（Unix时间戳、毫秒）
 */
@property (nonatomic, assign) long long sentTime;

/// 会话的操作时间（Unix时间戳、毫秒），用于分页获取会话列表时传入的时间戳
/// 初始值与 sentTime 相同，置顶等操作会更新此时间戳
/// - Since: 5.6.7
@property (nonatomic, assign) long long operationTime;

/*!
 会话中存在的草稿
 */
@property (nonatomic, copy, nullable) NSString *draft;

/// 会话中存在的编辑草稿
@property (nonatomic, strong, nullable) RCEditedMessageDraft *editedMessageDraft;

/*!
 会话中最后一条消息的类型名
 */
@property (nonatomic, copy, nullable) NSString *objectName;

/*!
 会话中最后一条消息的发送者用户ID
 */
@property (nonatomic, copy, nullable) NSString *senderUserId;

/*!
 会话中最后一条消息的消息ID
 */
@property (nonatomic, assign) long lastestMessageId;

/*!
 会话中最后一条消息的内容
 */
@property (nonatomic, strong, nullable) RCMessageContent *lastestMessage;

/*!
 会话中最后一条消息的方向
 */
@property (nonatomic, assign) RCMessageDirection lastestMessageDirection;

/*!
 会话中最后一条消息的json Dictionary
 */
@property (nonatomic, strong, nullable) NSDictionary *jsonDict;

/*!
 会话中有被提及的消息（有@你的消息）
 */
@property (nonatomic, assign, readonly) BOOL hasUnreadMentioned;

/*!
会话中有被@的消息数量
*/
@property (nonatomic, assign) int mentionedCount;


/*!
 免打扰级别
 */
@property (nonatomic, assign) RCPushNotificationLevel notificationLevel;

/*!
 会话中第一条未读消息时间戳（Unix时间戳、毫秒）

 仅支持 超级群会话
 - Since: 5.2.5

*/
@property (nonatomic, assign) long long firstUnreadMsgSendTime;

/// 最后一条消息 messageUId。
///
/// - Since: 5.20.0
@property (nonatomic, copy, nullable) NSString *latestMessageUId;

/// 消息已读回执 v5 操作标识。
///
/// - Since: 5.30.0
@property (nonatomic, assign) BOOL needReceipt;

/// 消息已读回执 v5 信息
@property (nonatomic, strong) RCReadReceiptInfoV5 *readReceiptInfoV5;

/// 是否显示用户在线状态
@property (nonatomic, assign) BOOL displayOnlineStatus;

/// 用户在线状态
/// - Note: 只在单聊类型会话中显示在线状态，其他类型会话不显示在线状态
/// - Since: 5.32.0
@property (nonatomic, strong) RCSubscribeUserOnlineStatus *onlineStatus;

/*!
 初始化会话显示数据模型

 - Parameter conversation:          会话
 - Parameter extend:                用户自定义的扩展数据
 - Returns: 会话Cell的数据模型对象
 */
- (instancetype)initWithConversation:(RCConversation *)conversation extend:(nullable id)extend;

/*!
 更新数据模型中的消息

 - Parameter message: 此会话中最新的消息
 */
- (void)updateWithMessage:(RCMessage *)message;

/*!
 会话和数据模型是否匹配

 - Parameter conversationType: 会话类型
 - Parameter targetId:         目标会话ID
 - Returns: 会话和数据模型是否匹配
 */
- (BOOL)isMatching:(RCConversationType)conversationType targetId:(NSString *)targetId;
@end
NS_ASSUME_NONNULL_END
