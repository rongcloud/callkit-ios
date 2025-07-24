//
//  RCChatRoomClient+Deprecated.h
//  RongChatRoom
//
//  Created by zgh on 2024/12/27.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <RongChatRoom/RongChatRoom.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCChatRoomClient (Deprecated)
#pragma mark - 聊天室操作

/*!
 加入聊天室（如果聊天室不存在则会创建）

 - Parameter targetId:        聊天室 ID，最大长度为 64 个字符
 - Parameter messageCount:    进入聊天室时获取历史消息的数量，-1 <= messageCount <= 50
 - Parameter successBlock:    加入聊天室成功的回调
 - Parameter errorBlock:      加入聊天室失败的回调 [status: 加入聊天室失败的错误码]

 可以通过传入的 messageCount 设置加入聊天室成功之后需要获取的历史消息数量。
 -1 表示不获取任何历史消息，0 表示不特殊设置而使用SDK默认的设置（默认为获取 10 条），0 < messageCount <= 50
 为具体获取的消息数量,最大值为 50。注：如果是 7.x 系统获取历史消息数量不要大于 30
 
 从5.3.1版本开始， 加入聊天室后，断网重新加入聊天室默认获取聊天室消息条数，为主动加入时获取的历史消息条数。由于每次传入的条数固定, 可能会导致消息重复，App 需要做消息排重。
 
 - Warning: 没有加入过的聊天室(或杀死 app 重新打开)，调用该接口会把该聊天室本地的消息与 KV 清除
 
 - Remark: 聊天室
 */
- (void)joinChatRoom:(NSString *)targetId
        messageCount:(int)messageCount
             success:(nullable void (^)(void))successBlock
               error:(nullable void (^)(RCErrorCode status))errorBlock
    __deprecated_msg("Use [RCChatRoomClient joinExistChatRoom:messageCount:successBlock:errorBlock:] instead");

/*!
 加入已经存在的聊天室（如果聊天室不存在返回错误 23410，人数超限返回错误 23411）

 - Parameter targetId:        聊天室 ID，最大长度为 64 个字符
 - Parameter messageCount:    进入聊天室时获取历史消息的数量，-1 <= messageCount <= 50
 - Parameter successBlock:    加入聊天室成功的回调
 - Parameter errorBlock:      加入聊天室失败的回调 [status: 加入聊天室失败的错误码]

 可以通过传入的 messageCount 设置加入聊天室成功之后，需要获取的历史消息数量。
 -1 表示不获取任何历史消息，0 表示不特殊设置而使用SDK默认的设置（默认为获取 10 条），0 < messageCount <= 50
 为具体获取的消息数量，最大值为 50。
 没有加入过的聊天室(或杀死 app 重新打开)，调用该接口会把该聊天室本地的消息与 KV 清除
 
 - Remark: 聊天室
 */
- (void)joinExistChatRoom:(NSString *)targetId
             messageCount:(int)messageCount
                  success:(nullable void (^)(void))successBlock
                    error:(nullable void (^)(RCErrorCode status))errorBlock
    __deprecated_msg("Use [RCChatRoomClient joinExistChatRoom:messageCount:successBlock:errorBlock:] instead");

#pragma mark-- 监听器
/*!
 设置 IMLib 的聊天室状态监听器

 - Parameter delegate: IMLib 聊天室状态监听器

 - Remark: 聊天室
 */
- (void)setChatRoomStatusDelegate:(id<RCChatRoomStatusDelegate>)delegate
    __deprecated_msg("Use [RCChatRoomClient addChatRoomStatusDelegate:] instead");

/*!
设置聊天室 KV 状态变化监听器

- Parameter delegate: 聊天室 KV 状态变化的监听器

可以设置并实现此 delegate 来进行聊天室状态变化的监听 。SDK 会在回调中通知您聊天室状态的改变。

- Remark: 功能设置
*/
- (void)setRCChatRoomKVStatusChangeDelegate:(id<RCChatRoomKVStatusChangeDelegate>)delegate
    __deprecated_msg("Use [RCChatRoomClient addChatRoomKVStatusChangeDelegate:] instead");
@end

NS_ASSUME_NONNULL_END
