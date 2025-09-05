//
//  RCRTCLocalUser.h
//  RongRTCLib
//
//  Created by RongCloud on 2019/1/9.
//  Copyright © 2019 RongCloud. All rights reserved.
//

#import <AvailabilityMacros.h>
#import <UIKit/UIKit.h>

#import "RCRTCCodeDefine.h"
#import "RCRTCUser.h"

NS_ASSUME_NONNULL_BEGIN

@class RCRTCOutputStream;
@class RCRTCInputStream;
@class RCMessageContent;

/*!
 音视频本地用户（当前登陆者）
 */
@interface RCRTCLocalUser : RCRTCUser

/*!
 本地用户发布的音视频流
 */
@property (nonatomic, copy, readonly)
    NSArray<RCRTCOutputStream *> *localStreams DEPRECATED_MSG_ATTRIBUTE("use streams property instead");

/*!
 本地用户发布的音视频流
 */
@property (nonatomic, copy, readonly) NSArray<RCRTCOutputStream *> *streams;

#pragma mark - 用户属性
/*!
 设置全局用户属性
 
 @param attributeValue 属性值
 @param key 属性名称
 @param message 是否在设置属性的时候携带消息内容，传空则不往房间中发送消息（也不会收到有用户属性变换的回调）
 @param completion 设置完成回调
 @discussion
 设置用户属性
 
 @remarks 房间管理
 */
- (void)setAttributeValue:(NSString *)attributeValue
                   forKey:(NSString *)key
                  message:(nullable RCMessageContent *)message
               completion:(nullable RCRTCOperationCallback)completion
    DEPRECATED_MSG_ATTRIBUTE("use setAttribute:forKey:message:completion: API instead");

/*!
 设置全局用户属性
 
 @param attributeValue 属性值
 @param key 属性名称
 @param message 是否在设置属性的时候携带消息内容，传空则不往房间中发送消息（也不会收到有用户属性变换的回调）
 @param completion 设置完成回调
 @discussion
 设置用户属性
 
 @remarks 房间管理
 */
- (void)setAttribute:(NSString *)attributeValue
              forKey:(NSString *)key
             message:(nullable RCMessageContent *)message
          completion:(nullable RCRTCOperationCallback)completion;

/*!
 删除全局用户属性
 
 @param attributeKeys 属性名称数组
 @param message 是否在设置属性的时候携带消息内容，传空则不往房间中发送消息
 @param completion 删除完成回调
 @discussion
 删除用户属性
 
 @remarks 房间管理
 */
- (void)deleteAttributes:(NSArray<NSString *> *)attributeKeys
                 message:(nullable RCMessageContent *)message
              completion:(nullable RCRTCOperationCallback)completion;

/*!
 获取全局用户属性
 
 @param attributeKeys 属性名称
 @param completion 获取结果回调
 @discussion
 获取用户属性
 
 @remarks 房间管理
 */
- (void)getAttributes:(NSArray<NSString *> *)attributeKeys
           completion:(nullable RCRTCAttributeOperationCallback)completion;

#pragma mark - 发布资源
/*!
 发布本地默认音视频流
 
 @param completion 发布完成回调
 @discussion
 发布默认音视频流
 
 @remarks 资源管理
 */
- (void)publishDefaultStreams:(nullable RCRTCOperationCallback)completion;

/*!
 发布本地指定音视频流
 
 @param stream 发布的音视频流
 @param completion 发布的音视频流结果
 @discussion
 发布音视频流
 
 @remarks 资源管理
 */
- (void)publishStream:(nullable RCRTCOutputStream *)stream completion:(nullable RCRTCOperationCallback)completion;

/*!
 发布多路本地指定音视频流
 
 @param streams 发布音视频流集合
 @param completion 发布的音视频流结果
 @discussion
 发布多路音视频流
 
 @remarks 资源管理
 */
- (void)publishStreams:(nullable NSArray<RCRTCOutputStream *> *)streams
            completion:(nullable RCRTCOperationCallback)completion;

/*!
 发布本地默认音视频流，直播模式专用
 
 @param completion 发布完成回调
 @discussion
 发布主播默认音视频流, 此接口仅直播模式的主播可用, 即 RCRTCRoomType 为 RCRTCRoomTypeLive 可用
 
 @remarks 资源管理
 */
- (void)publishDefaultLiveStreams:(nullable RCRTCLiveOperationCallback)completion;

/*!
 发布本地指定音视频流，直播模式专用
 
 @param stream 发布的音视频流
 @param completion 发布的音视频流结果, 包括此主播的推流 url
 @discussion
 发布直播音视频流, 此接口仅直播模式的主播可用, 即 RCRTCRoomType 为 RCRTCRoomTypeLive 可用
 
 @remarks 资源管理
 */
- (void)publishLiveStream:(nullable RCRTCOutputStream *)stream completion:(nullable RCRTCLiveOperationCallback)completion;

#pragma mark - 取消发布资源
/*!
 取消发布本地默认音视频流
 
 @param completion 取消发布完成回调
 @discussion
 取消发布默认音视频流
 
 @remarks 资源管理
 */
- (void)unpublishDefaultStreams:(nullable RCRTCOperationCallback)completion;

/*!
 取消发布本地指定音视频流
 
 @param stream 取消发布的音视频流
 @param completion 发布的音视频流结果
 @discussion
 取消发布音视频流
 
 @remarks 资源管理
 */
- (void)unpublishStream:(nullable RCRTCOutputStream *)stream completion:(nullable RCRTCOperationCallback)completion;

/*!
 取消发布多路本地指定音视频流
 
 @param streams 取消发布的音视频流集合
 @param completion 发布的音视频流结果
 @discussion
 取消发布多路音视频流
 
 @remarks 资源管理
 */
- (void)unpublishStreams:(nullable NSArray<RCRTCOutputStream *> *)streams
              completion:(nullable RCRTCOperationCallback)completion;

/*!
 取消发布本地默认音视频流，直播模式专用
 
 @param completion 取消发布完成回调
 @discussion
 取消发布默认音视频流，此接口仅直播模式的主播可用, 即 RCRTCRoomType 为 RCRTCRoomTypeLive 可用
 
 @remarks 资源管理
 */
- (void)unpublishDefaultLiveStreams:(nullable RCRTCOperationCallback)completion;

/*!
 取消发布本地指定音视频流，直播模式专用
 
 @param stream 取消发布的音视频流
 @param completion 发布的音视频流结果
 @discussion
 取消发布音视频流，此接口仅直播模式的主播可用, 即 RCRTCRoomType 为 RCRTCRoomTypeLive 可用
 
 @remarks 资源管理
 */
- (void)unpublishLiveStream:(nullable RCRTCOutputStream *)stream completion:(nullable RCRTCOperationCallback)completion;

#pragma mark - 订阅资源
/*!
 订阅多路远端指定音视频流
 
 @param avStreams 普通流数组
 @param tinyStreams 小流数组，同一个流只能填写在 avStreams 或 tinyStreams 中的一个数组中
 @param completion 完成的回调
 @discussion
 订阅流
 
 @remarks 资源管理
 */
- (void)subscribeStream:(nullable NSArray<RCRTCInputStream *> *)avStreams
            tinyStreams:(nullable NSArray<RCRTCInputStream *> *)tinyStreams
             completion:(nullable RCRTCOperationCallback)completion;

/*!
 订阅多路远端指定音视频流
 
 @param avStreams 普通流数组
 @param tinyStreams 小流数组，同一个流只能填写在 avStreams 或 tinyStreams 中的一个数组中
 @param callback 完成的回调
 @discussion
 订阅流，callback 返回订阅结果，callback 中 subscribeErrorList 为服务器返回的订阅失败列表；另外可能存在 isSuccess 为 YES，但是 subscribeErrorList 不为空的情况，这种情况是部分订阅成功，用户可以根据业务决定是否对 subscribeErrorList 中的流进行重新订阅
 
 @remarks 资源管理
 */
- (void)subscribeStreams:(nullable NSArray<RCRTCInputStream *> *)avStreams
             tinyStreams:(nullable NSArray<RCRTCInputStream *> *)tinyStreams
                callback:(nullable RCRTCSubscribeOperationCallback)callback;

/*!
 观众订阅合流资源

 @param liveUrl 主播直播的 liveUrl (针对 4x版本的主播兼容方案)
 @param streamType 需要具体订阅的媒体类型
 @param completion  完成的回调, 会依次回调合流的 RCRTCInputStream, 根据 streamType 区分是音频流还是视频流, 如主播发布了音视频流, 此回调会回调两次, 分别为音频的 RCRTCInputStream,  和视频的 RCRTCInputStream 。
 @discussion
 仅直播模式可用,  作为观众, 直接观看主播的直播, 通过传入主播的 url, 仅观众端可用，此接口可具体订阅音频流或视频流或大小流
 Added from 5.1.0
 
 @remarks 媒体流操作
 */
- (void)subscribeLiveUrl:(nullable NSString *)liveUrl
              streamType:(RCRTCAVStreamType)streamType
              completion:(nullable RCRTCLiveUrlCallback)completion;

#pragma mark - 取消订阅资源
/*!
 取消订阅远端指定音视频流
 
 @param stream 音视频流
 @param completion 音视频流结果
 @discussion
 取消订阅音视频流
 
 @remarks 资源管理
 */
- (void)unsubscribeStream:(nullable RCRTCInputStream *)stream completion:(nullable RCRTCOperationCallback)completion;

/*!
 取消订阅多路远端指定音视频流
 
 @param streams 音视频流集合
 @param completion 音视频流结果
 @discussion
 取消订阅多路音视频流
 
 @remarks 资源管理
 */
- (void)unsubscribeStreams:(nullable NSArray<RCRTCInputStream *> *)streams
                completion:(nullable RCRTCOperationCallback)completion;

#pragma mark - 订阅与取消订阅
/*!
 同时订阅+取消订阅多路远端指定音视频流
 
 在订阅时, 同一个流只能填写在 subStreams 或 subTinyStreams 中的一个数组中
 订阅列表与取消订阅列表不能存在重复的音视频流
 
 @param subStreams 普通音视频流列表
 @param subTinyStreams 需要携带小流的流数组
 @param unsubStreams 取消订阅的音视频数组
 @param completion 完成的回调
 @discussion
 订阅+取消订阅多路远端指定音视频流
 
 @remarks 资源管理
 */
- (void)subscribeStreams:(nullable NSArray<RCRTCInputStream *> *)subStreams
             tinyStreams:(nullable NSArray<RCRTCInputStream *> *)subTinyStreams
      unsubscribeStreams:(nullable NSArray<RCRTCInputStream *> *)unsubStreams
              completion:(nullable RCRTCOperationCallback)completion;

/*!
 同时订阅+取消订阅多路远端指定音视频流
 
 在订阅时, 同一个流只能填写在 subStreams 或 subTinyStreams 中的一个数组中
 订阅列表与取消订阅列表不能存在重复的音视频流
 
 @param subStreams 普通音视频流列表
 @param subTinyStreams 需要携带小流的流数组
 @param unsubStreams 取消订阅的音视频数组
 @param callback 完成的回调
 @discussion
 订阅+取消订阅多路远端指定音视频流，callback 返回订阅结果，callback 中 subscribeErrorList 为服务器返回的订阅失败列表；另外可能存在 isSuccess 为 YES，但是 subscribeErrorList 不为空的情况，这种情况是部分订阅成功，用户可以根据业务决定是否对 subscribeErrorList 中的流进行重新订阅
 
 @remarks 资源管理
 */
- (void)subscribeStreams:(nullable NSArray<RCRTCInputStream *> *)subStreams
             tinyStreams:(nullable NSArray<RCRTCInputStream *> *)subTinyStreams
      unsubscribeStreams:(nullable NSArray<RCRTCInputStream *> *)unsubStreams
                callback:(nullable RCRTCSubscribeOperationCallback)callback;

#pragma mark - 跨房间连麦
/*!
 向指定用户发送跨房间连麦请求
 
 @param inviteeRoomId 被邀请人所在房间号
 @param inviteeUserId 被邀请人userId
 @param autoMix 是否将被邀请人音视频资源合流到邀请人房间中
 @param extra 附加信息, 可随消息发送给被邀请人
 @param completion 完成的回调
 @discussion
 仅供连麦使用
 
 @remarks 资源管理
 */
- (void)requestJoinOtherRoom:(nullable NSString *)inviteeRoomId
                      userId:(nullable NSString *)inviteeUserId
                     autoMix:(BOOL)autoMix
                       extra:(nullable NSString *)extra
                  completion:(nullable RCRTCOperationCallback)completion DEPRECATED_MSG_ATTRIBUTE("use requestRoomPK:forKey:userId:autoMix:extra:completion: API instead");

/*!
 向指定用户发送PK连麦请求
 
 @param inviteeRoomId 被邀请人所在房间号
 @param inviteeUserId 被邀请人userId
 @param autoMix 是否将被邀请人音视频资源合流到邀请人房间中
 @param extra 附加信息, 可随消息发送给被邀请人
 @param completion 完成的回调
 @discussion
 仅供连麦使用
 
 @remarks 资源管理
 */
- (void)requestRoomPK:(nullable NSString *)inviteeRoomId
               userId:(nullable NSString *)inviteeUserId
              autoMix:(BOOL)autoMix
                extra:(nullable NSString *)extra
           completion:(nullable RCRTCOperationCallback)completion;

/*!
 取消正在进行中的跨房间连麦请求
 
 @param inviteeRoomId 被邀请人所在房间号
 @param inviteeUserId 被邀请人userId
 @param extra 附加信息, 可随消息发送给被邀请人
 @param completion 完成的回调
 @discussion
 仅供连麦使用
 
 @remarks 资源管理
 */
- (void)cancelRequestJoinOtherRoom:(nullable NSString *)inviteeRoomId
                            userId:(nullable NSString *)inviteeUserId
                             extra:(nullable NSString *)extra
                        completion:(nullable RCRTCOperationCallback)completion DEPRECATED_MSG_ATTRIBUTE("use cancelRequestJoinPK:userId:extra:completion: API instead");

/*!
 取消正在进行中的PK连麦请求
 
 @param inviteeRoomId 被邀请人所在房间号
 @param inviteeUserId 被邀请人userId
 @param extra 附加信息, 可随消息发送给被邀请人
 @param completion 完成的回调
 @discussion
 仅供连麦使用
 
 @remarks 资源管理
 */
- (void)cancelRequestJoinPK:(nullable NSString *)inviteeRoomId
                     userId:(nullable NSString *)inviteeUserId
                      extra:(nullable NSString *)extra
                 completion:(nullable RCRTCOperationCallback)completion;

/*!
 响应跨房间连麦请求
 
 @param inviterRoomId 邀请人所在的房间号
 @param inviterUserId 邀请人userId
 @param agree 是否同意加入副房间
 @param autoMix 是否将邀请人音视频资源合流到被邀请人（响应邀请的人）房间中
 @param extra 附加信息, 可随消息发送给邀请人
 @param completion 完成的回调
 @discussion
 取消订阅多路音视频流
 
 @remarks 资源管理
 */
- (void)responseJoinOtherRoom:(nullable NSString *)inviterRoomId
                       userId:(nullable NSString *)inviterUserId
                        agree:(BOOL)agree
                      autoMix:(BOOL)autoMix
                        extra:(nullable NSString *)extra
                   completion:(nullable RCRTCOperationCallback)completion DEPRECATED_MSG_ATTRIBUTE("use responseRoomPK:userId:agree:autoMix:extra:completion: API instead");

/*!
 响应PK连麦请求
 
 @param inviterRoomId 邀请人所在的房间号
 @param inviterUserId 邀请人userId
 @param agree 是否同意加入副房间
 @param autoMix 是否将邀请人音视频资源合流到被邀请人（响应邀请的人）房间中
 @param extra 附加信息, 可随消息发送给邀请人
 @param completion 完成的回调
 @discussion
 取消订阅多路音视频流
 
 @remarks 资源管理
 */
- (void)responseRoomPK:(nullable NSString *)inviterRoomId
                userId:(nullable NSString *)inviterUserId
                 agree:(BOOL)agree
               autoMix:(BOOL)autoMix
                 extra:(nullable NSString *)extra
            completion:(nullable RCRTCOperationCallback)completion;

/*!
 结束PK连麦
 
 @param roomId 副房间 Id
 @param completion 完成的回调
 @discussion
 通知所有连麦用户结束连麦
 
 @remarks 资源管理
 */
- (void)quitRoomPK:(nullable NSString *)roomId
        completion:(nullable RCRTCOperationCallback)completion;

#pragma mark - 身份切换
/*!
 主播切换到观众
 
 @param onSucceed 切换成功的回调。
 @param onFailed  切换失败会回调，但不影响当前角色继续音视频。
 @param onKicked  切换失败会回调，SDK内部会退出房间并清理所有资源，该用户只能重新加入房间才能继续音视频。
 
 @discussion
 当前角色为主播，切换角色到观众，仅限主播使用。
 如果当前用户加入了 RCRTCOtherRoom 切换为观众时，RTC SDK 内部会帮其退出所有 RCRTCOtherRoom。
 Added from 5.1.9
 */
- (void)switchToAudienceOnSucceed:(nullable void (^)(void))onSucceed
                         onFailed:(nullable void (^)(RCRTCCode code))onFailed
                         onKicked:(nullable void (^)(void))onKicked;

/*!
 观众切换到主播
 
 @param publishStreams 切换成主播后需要发布的流。
 @param onSucceed 切换成功的回调
 @param onFailed  切换失败会回调，但不影响当前角色继续音视频。
 @param onKicked  切换失败会回调，SDK内部会退出房间并清理所有资源，该用户只能重新加入房间才能继续音视频。
 
 @discussion
 观众切换角色到主播，仅限观众使用。
 Added from 5.1.9
 */
- (void)switchToBroadcaster:(NSArray<RCRTCOutputStream *> *)publishStreams
                  onSucceed:(nullable void (^)(RCRTCLiveInfo *liveInfo))onSucceed
                   onFailed:(nullable void (^)(RCRTCCode code))onFailed
                   onKicked:(nullable void (^)(void))onKicked;


/*!
 设置开启 SEI 功能

 @param enable YES 开启，NO 不开启，默认 NO
 @param completion 开启结果的回调

 @discussion 开启 SEI 功能观众身份调用无效，观众不允许发布流，所以不具备 SEI 能力。
 Added from 5.2.5
*/
- (void)setEnableSEI:(BOOL)enable
          completion:(void(^)(BOOL isSuccess, RCRTCCode errCode))completion;

/*!
 发送媒体增强补充信息
 
 @param SEI 数据字符
 @discussion 此接口可在开发者推流传输音视频流数据并且[setEnableSEI] 开启SEI 功能的同时，发送流媒体增强补充信息来同步一些其他附加信息。
 一般如同步音乐歌词或视频画面精准布局等场景，可选择使用发送 SEI。当推流方发送 SEI 后，拉流方可通过 RCRTCRoomEventDelegate 监听 [didReceiveSEI] & [didReceiveLiveStreamSEI] 的回调获取 SEI 内容。由于 SEI 信息跟随视频帧，由于网络问题有可能丢帧，因此 SEI 信息也有可能丢，为解决这种情况，应该在限制频率内多发几次。限制频率：1秒钟不要超过30次。SEI 数据长度限制为 4096 字节。
 @return 0 成功，非 0 失败，返回具体错误码
 Added from 5.2.5
*/
- (RCRTCCode)sendSEI:(NSString *)SEI;

/*!
 开启语音识别服务
 
 @param completion 开启语音识别服务回调
 
 @discussion
 开启语音识别服务，如果房间内没有人发布流，则无法开启语音识别服务，SDK 会在有人发布流后补偿进行开启语音识别服务
 
 @remarks 语音识别
 */
- (void)startASR:(nullable RCRTCOperationCallback)completion;

/*!
 停止语音识别服务
 
 @param completion 停止语音识别服务回调
 
 @discussion
 停止语音识别服务
 
 @remarks 语音识别
 */
- (void)stopASR:(nullable RCRTCOperationCallback)completion;

/*!
 获取语音识别服务是否可用
 
 @return YES 表示语音识别服务已经开启，NO 表示语音识别服务已经停止
 
 @discussion
 获取语音识别服务是否可用，非实时查询接口，根据端上缓存进行的判断
 
 @remarks 语音识别
 */
- (BOOL)asrIsAvailable;

/*!
 设置是否接收语音识别信息
 @param enable 是否接收语音识别信息
 
 @discussion
 设置接收语音识别信息时候，会通过 RCRTCRoomEventDelegate 的 didReceiveASRContent 回调返回语音识别结果
 
 @remarks 语音识别
 */
- (int)setEnableASR:(BOOL)enable;

@end

NS_ASSUME_NONNULL_END
