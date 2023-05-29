//
//  RCChatRoomProtocol.h
//  RongChatRoom
//
//  Created by 张改红 on 2020/8/12.
//  Copyright © 2020 张改红. All rights reserved.
//

#ifndef RCChatRoomProtocol_h
#define RCChatRoomProtocol_h

NS_ASSUME_NONNULL_BEGIN

@class RCChatRoomMemberAction;
@class RCChatRoomSyncEvent, RCChatRoomMemberBlockEvent, RCChatRoomMemberBanEvent;

typedef NS_ENUM(NSUInteger, RCChatRoomDestroyType) {
    /*!
     开发者主动销毁
     */
    RCChatRoomDestroyTypeManual = 0,

    /*!
     聊天室长时间不活跃，被系统自动回收
     */
    RCChatRoomDestroyTypeAuto = 3
};

#pragma mark - 聊天室监听器

/*!
 IMLib聊天室状态的的监听器

 @discussion
 设置IMLib的聊天室状态监听器，请参考RCIMClient的setChatRoomStatusDelegate:方法。
 */
@protocol RCChatRoomStatusDelegate <NSObject>

/*!
 开始加入聊天室的回调

 @param chatroomId 聊天室ID
 */
- (void)onChatRoomJoining:(NSString *)chatroomId;

/*!
 加入聊天室成功的回调

 @param chatroomId 聊天室ID
 */
- (void)onChatRoomJoined:(NSString *)chatroomId;

/*!
 加入聊天室失败的回调

 @param chatroomId 聊天室ID
 @param errorCode  加入失败的错误码

 @discussion
 如果错误码是KICKED_FROM_CHATROOM或RC_CHATROOM_NOT_EXIST，则不会自动重新加入聊天室，App需要按照自己的逻辑处理。
 */
- (void)onChatRoomJoinFailed:(NSString *)chatroomId errorCode:(RCErrorCode)errorCode;

/*!
 加入聊天室成功，但是聊天室被重置。接收到此回调后，还会收到 onChatRoomJoined：回调。

 @param chatroomId 聊天室ID
 */
- (void)onChatRoomReset:(NSString *)chatroomId;

/*!
 退出聊天室成功的回调

 @param chatroomId 聊天室ID
 */
- (void)onChatRoomQuited:(NSString *)chatroomId;

/*!
 聊天室被销毁的回调，用户在线的时候房间被销毁才会收到此回调。

 @param chatroomId 聊天室ID
 @param type 聊天室销毁原因

 */
- (void)onChatRoomDestroyed:(NSString *)chatroomId type:(RCChatRoomDestroyType)type;

@end


#pragma mark - 聊天室 KV 状态变化

/**
 IMLib 聊天室 KV 状态变化监听器
 @discussion 设置代理请参考 RCIMClient 的 setRCChatRoomKVStatusChangeDelegate: 方法。
 */
@protocol RCChatRoomKVStatusChangeDelegate <NSObject>


/**
 IMLib 刚加入聊天室时 KV 同步完成的回调
 
 @param roomId 聊天室 Id
 */
- (void)chatRoomKVDidSync:(NSString *)roomId;

/**
 IMLib 聊天室 KV 变化的回调
 
 @param roomId 聊天室 Id
 @param entry KV 字典，如果刚进入聊天室时存在  KV，会通过此回调将所有 KV 返回，再次回调时为其他人设置或者修改 KV
 */
- (void)chatRoomKVDidUpdate:(NSString *)roomId entry:(NSDictionary<NSString *, NSString *> *)entry;

/**
 IMLib 聊天室 KV 被删除的回调
 
 @param roomId 聊天室 Id
 @param entry KV 字典
 */
- (void)chatRoomKVDidRemove:(NSString *)roomId entry:(NSDictionary<NSString *, NSString *> *)entry;

@end


#pragma mark - 聊天室成员变化监听器
@protocol RCChatRoomMemberDelegate <NSObject>
/**
 有聊天室成员加入或退出的回调
 
 @param members 相关信息
 @param roomId 聊天室 Id
 */
- (void)memberDidChange:(NSArray <RCChatRoomMemberAction *> *)members inRoom:(NSString *)roomId;

@end



#pragma mark - 聊天室事件通知

/**
 @discussion 聊天室事件通知
 @discussion 封禁、解封、禁言、解除禁言、多端同步相关事件等
 
 @since 5.4.5
 */

@protocol RCChatRoomNotifyEventDelegate <NSObject>

/**
 @discussion 多端登录相关事件通知回调，包含三种通知 case
 
 1. 多端登录情况，一端加入聊天室，需要通知另一终端
 指定聊天室中所有成员，包括当前加入用户
 
 2. 多端登录情况，一端退出聊天室，需要通知另一终端
 指定聊天室中所有成员，包括当前退出用户
 
 3. 用户多端加入聊天室场景：用户在 iOS 端加入聊天室，在 Web 端登录后又加入一个新的聊天室，自动将用户从上一个聊天室踢出
 被踢出聊天室中的所有成员，包括被踢出用户
 注：case 3 如果开通了一个用户可加入多个聊天室的情况不会进行通知
 
 @param event 聊天室 RCChatRoomSyncEvent
 */
- (void)chatRoomNotifyMultiLoginSync:(RCChatRoomSyncEvent *)event;

/**
 @discussion 封禁用户相关事件通知回调, 包含两种通知 case
 
 1. 封禁用户，聊天室中所有成员，包括被封禁用户
 注：
 * 封禁后用户被自动踢出聊天室
 * 封禁后用户不会再收到被踢出的通知
 * 是否通知封禁本人外的其他成员，取决于 server API 的入参 needNotify（默认为 false 不通知其他成员）
 
 
 2. 解除封禁，被解除封禁的成员
 注：
 * 用户未在线时，再登录时不会收到通知
 * 服务端仅对主动解除封禁做通知，封禁时间到了，自动解除的不通知， 此刻调用加入聊天室接口可成功
 * 服务端仅对解除封禁的本人做通知，聊天室内其他成员不会收到通知，此处不受 server API 的入参 needNotify 影响

 @discussion 封禁时长最大值为43200分钟/1个月, 最小值1分钟
 @param event 聊天室 RCChatRoomMemberBlockEvent
 */
- (void)chatRoomNotifyBlock:(RCChatRoomMemberBlockEvent *)event;

/**
 @discussion 禁言相关事件通知回调，包含以下 case
 
 注：
 * 禁言，受到白名单保护，即白名单中用户不会被禁言
 * 是否通知禁言本人外的其他成员，取决于 server API 的入参 needNotify（默认为 false 不通知其他成员）
 1. 禁言指定聊天室中用户，指定聊天室中任何成员
 2. 解除指定聊天室中用户禁言，指定聊天室中任何成员
 
 注：
 * 全体禁言，也受到白名单保护，即白名单中用户不会被禁言
 * 是否通知禁言本人外的其他成员，取决于 server API 的入参 needNotify（默认为 false 不通知其他成员）
 3. 聊天室全体禁言，针对聊天室中所有成员
 4. 解除聊天室全体禁言，针对聊天室中所有成员
 
 注：
 * 白名单是聊天室维度，添加后，用户在此聊天室内无法被设置禁言，即被保护
 生命周期跟随聊天室，销毁后，清空白名单，重建聊天室时，需要再次调用接口添加
 * 是否通知禁言本人外的其他成员，取决于 server API 的入参 needNotify（默认为 false 不通知其他成员）
 5. 添加禁言用户白名单，对应聊天室中所有成员
 6. 移出禁言用户白名单，对应聊天室中所有成员
 
 注：
 * 全局禁言是最高优先级，全局禁言后，禁言用户在所有聊天室内都无法发言，即便配置白名单也不行
 * 只有全局禁言或解除全局禁言的用户，可以收到通知，其余成员不会收到通知，此处不受 server API 的入参 needNotify 影响
 7. 用户聊天室全局禁言，指定全局禁言用户
 8. 解除用户聊天室全局禁言，指定解除全局禁言用户
 
 @discussion 禁言时长最大值为43200分钟/1个月, 最小值1分钟
 @param event 聊天室 RCChatRoomMemberBanEvent
 */
- (void)chatRoomNotifyBan:(RCChatRoomMemberBanEvent *)event;

@end

NS_ASSUME_NONNULL_END

#endif /* RCChatRoomProtocol_h */

