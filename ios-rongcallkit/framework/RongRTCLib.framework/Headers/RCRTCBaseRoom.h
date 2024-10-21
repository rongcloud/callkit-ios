//
//  RCBaseRoom.h
//  RongRTCLib
//
//  Created by RongCloud on 2020/8/3.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RongIMLibCore.h>
#import "RCRTCLibDefine.h"

NS_ASSUME_NONNULL_BEGIN

@class RCRTCRoomConfig;
@class RCRTCRemoteUser;

@interface RCRTCBaseRoom : NSObject

/*!
 房间ID
 */
@property (nonatomic, copy, readonly) NSString *roomId;

/*!
 加入房间时设置的房间配置
 */
@property (nonatomic, strong, readonly, nullable) RCRTCRoomConfig *roomConfig;

/*!
 会话 id, 用于 server API，会话唯一标识
 */
@property (nonatomic, copy, readonly, nullable) NSString *sessionId;

/*!
 参与用户
 */
@property (nonatomic, strong, readonly) NSArray<RCRTCRemoteUser *> *remoteUsers;

/*!
 获取指定远端用户
 
 @param userId 用户 ID
 @discussion
 根据用户 ID 获取房间内远端用户，不存在则返回 nil
 */
- (nullable RCRTCRemoteUser *)getRemoteUser:(NSString *)userId;

/*!
 发送消息

 @param content 消息的内容
 @param successBlock 消息发送成功的回调 [messageId:消息的ID]
 @param errorBlock 消息发送失败的回调 [nErrorCode:发送失败的错误码,messageId:消息的ID]
 @discussion
 该接口只能发送 persistentFlag 为 MessagePersistent_STATUS 的状态消息, 远端用户如果不在线则消息丢失, 自定义消息时下面标识一定要给出, 否则会导致消息发送失败
 + (RCMessagePersistent)persistentFlag {
    return MessagePersistent_STATUS;
 }

 @remarks 房间管理
 @return 发送的消息实体
 */
- (nullable RCMessage *)sendMessage:(RCMessageContent *)content
                            success:(nullable void (^)(long messageId))successBlock
                              error:(nullable void (^)(NSInteger nErrorCode, long messageId))errorBlock;

/*!
 设置房间属性

 @param attributeValue 属性值
 @param key 属性名称
 @param message 是否在设置属性的时候携带消息内容, 传空则不往房间中发送消息
 @param completion 设置完成回调
 @discussion
 设置房间属性

 @remarks 房间管理
 */
- (void)setRoomAttributeValue:(NSString *)attributeValue
                       forKey:(NSString *)key
                      message:(nullable RCMessageContent *)message
                   completion:(nullable RCRTCOperationCallback)completion
    DEPRECATED_MSG_ATTRIBUTE("use setAttribute:forKey:message:completion: API instead");

/*!
 设置房间属性

 @param attributeValue 属性值
 @param key 属性名称
 @param message 是否在设置属性的时候携带消息内容, 传空则不往房间中发送消息
 @param completion 设置完成回调
 @discussion
 设置房间属性

 @remarks 房间管理
 */
- (void)setAttribute:(NSString *)attributeValue
              forKey:(NSString *)key
             message:(nullable RCMessageContent *)message
          completion:(nullable RCRTCOperationCallback)completion;

/*!
 删除房间属性

 @param attributeKeys 属性名称数组
 @param message 是否在设置属性的时候携带消息内容, 传空则不往房间中发送消息
 @param completion 删除完成回调
 @discussion
 删除房间属性

 @remarks 房间管理
 */
- (void)deleteRoomAttributes:(NSArray<NSString *> *)attributeKeys
                     message:(nullable RCMessageContent *)message
                  completion:(nullable RCRTCOperationCallback)completion
    DEPRECATED_MSG_ATTRIBUTE("use deleteAttributes:message:completion: API instead");

/*!
 删除房间属性

 @param attributeKeys 属性名称数组
 @param message 是否在设置属性的时候携带消息内容, 传空则不往房间中发送消息
 @param completion 删除完成回调
 @discussion
 删除房间属性

 @remarks 房间管理
 */
- (void)deleteAttributes:(NSArray<NSString *> *)attributeKeys
                 message:(nullable RCMessageContent *)message
              completion:(nullable RCRTCOperationCallback)completion;

/*!
 获取房间属性

 @param attributeKeys 属性名称
 @param completion 获取结果回调
 @discussion
 获取房间属性

 @remarks 房间管理
 */
- (void)getRoomAttributes:(NSArray<NSString *> *)attributeKeys
               completion:(nullable RCRTCAttributeOperationCallback)completion
    DEPRECATED_MSG_ATTRIBUTE("use getAttributes:completion: API instead");

/*!
 获取房间属性

 @param attributeKeys 属性名称
 @param completion 获取结果回调
 @discussion
 获取房间属性

 @remarks 房间管理
 */
- (void)getAttributes:(NSArray<NSString *> *)attributeKeys
           completion:(nullable RCRTCAttributeOperationCallback)completion;

@end

NS_ASSUME_NONNULL_END
