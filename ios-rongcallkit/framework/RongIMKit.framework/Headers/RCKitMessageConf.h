//
//  RCKitMessageConf.h
//  RongIMKit
//
//  Created by Sin on 2020/6/23.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface RCKitMessageConf : NSObject
#pragma mark - Config

#pragma mark 消息通知提醒
/*!
 是否关闭所有的本地通知，默认值是NO

 @discussion 当App处于后台时，默认会弹出本地通知提示，您可以通过将此属性设置为YES，关闭所有的本地通知。
 */
@property (nonatomic, assign) BOOL disableMessageNotificaiton;

/*!
 是否关闭所有的前台消息提示音，默认值是NO

 @discussion 当App处于前台时，默认会播放消息提示音，您可以通过将此属性设置为YES，关闭所有的前台消息提示音。
 */
@property (nonatomic, assign) BOOL disableMessageAlertSound;

/*!
 是否开启发送输入状态，默认值是 YES，开启之后在输入消息的时候对方可以看到正在输入的提示(目前只支持单聊)
 */
@property (nonatomic, assign) BOOL enableTypingStatus;

/*!
 开启已读回执功能的会话类型，默认为 单聊、群聊和讨论组

 @discussion 这些会话类型的消息在会话页面显示了之后会发送已读回执。目前仅支持单聊、群聊和讨论组。

 OC 需转成 NSNumber 传入（例如 @[ @(ConversationType_PRIVATE) ]），
 Swift 需获取到 rawValue 传入（例如 [ RCConversationType.ConversationType_PRIVATE.rawValue ]）。
 */
@property (nonatomic, copy) NSArray *enabledReadReceiptConversationTypeList;

/*!
 设置群组、讨论组发送已读回执请求的有效时间，单位是秒，默认值是 120s。

 @discussion 用户在群组或讨论组中发送消息，退出会话页面再次进入时，如果超过设置的时间，则不再显示已读回执的按钮。
 */
@property (nonatomic, assign) NSUInteger maxReadRequestDuration;

/*!
 是否开启多端同步未读状态的功能，默认值是 YES

 @discussion 开启之后，用户在其他端上阅读过的消息，当前客户端会清掉该消息的未读数。目前仅支持单聊、群聊、讨论组。
 */
@property (nonatomic, assign) BOOL enableSyncReadStatus;

/*!
 是否开启消息@提醒功能（只支持群聊和讨论组, App需要实现群成员数据源groupMemberDataSource），默认值是 YES。
 */
@property (nonatomic, assign) BOOL enableMessageMentioned;

/*!
 是否开启消息撤回功能，默认值是 YES。
 */
@property (nonatomic, assign) BOOL enableMessageRecall;

/*!
 消息可撤回的最大时间，单位是秒，默认值是120s。
 */
@property (nonatomic, assign) NSUInteger maxRecallDuration;

/*!
 是否在会话页面和会话列表界面显示未注册的消息类型，默认值是 YES

 @discussion App不断迭代开发，可能会在以后的新版本中不断增加某些自定义类型的消息，但是已经发布的老版本无法识别此类消息。
 针对这种情况，可以预先定义好未注册的消息的显示，以提升用户体验（如提示当前版本不支持，引导用户升级版本等）

 未注册的消息，可以通过RCConversationViewController中的rcUnkownConversationCollectionView:cellForItemAtIndexPath:和rcUnkownConversationCollectionView:layout:sizeForItemAtIndexPath:方法定制在会话页面的显示。
 未注册的消息，可以通过修改unknown_message_cell_tip字符串资源定制在会话列表界面的显示。
 */
@property (nonatomic, assign) BOOL showUnkownMessage;

/*!
 未注册的消息类型是否显示本地通知，默认值是NO

 @discussion App不断迭代开发，可能会在以后的新版本中不断增加某些自定义类型的消息，但是已经发布的老版本无法识别此类消息。
 针对这种情况，可以预先定义好未注册的消息的显示，以提升用户体验（如提示当前版本不支持，引导用户升级版本等）

 未注册的消息，可以通过修改unknown_message_notification_tip字符串资源定制本地通知的显示。

 */
@property (nonatomic, assign) BOOL showUnkownMessageNotificaiton;

/*!
 语音消息的最大长度

 @discussion 默认值是 60 秒
 */
@property (nonatomic, assign) NSUInteger maxVoiceDuration;

/*!
 APP是否独占音频

 @discussion 默认是NO,录音结束之后会调用AVAudioSession 的 setActive:NO ，
 恢复其他后台APP播放的声音，如果设置成YES,不会调用 setActive:NO，这样不会中断当前APP播放的声音
 (如果当前APP 正在播放音频，这时候如果调用SDK 的录音，可以设置这里为YES)
 */
@property (nonatomic, assign) BOOL isExclusiveSoundPlayer;

/*!
 选择媒体资源时，是否包含视频文件，默认值是NO

 @discussion 默认是不包含
 */
@property (nonatomic, assign) BOOL isMediaSelectorContainVideo;

/**
 GIF 消息自动下载的大小 size, 单位 KB
 */
@property (nonatomic, assign) NSInteger GIFMsgAutoDownloadSize;

/*!
 是否开启合并转发功能，默认值是NO，开启之后可以合并转发消息(目前只支持单聊和群聊)
 */
@property (nonatomic, assign) BOOL enableSendCombineMessage;

/*!
 是否开启阅后即焚功能，默认值是NO，开启之后可以在聊天页面扩展板中使用阅后即焚功能(目前只支持单聊)

 @discussion 目前 IMKit 仅支持文本、语音、图片、小视频消息。
 */
@property (nonatomic, assign) BOOL enableDestructMessage;

/*!
 消息撤回后可重新编辑的时间，单位是秒，默认值是 300s。

 @discussion 目前消息撤回后重新编辑仅为本地操作，卸载重装或者更换设备不会同步。
 */
@property (nonatomic, assign) NSUInteger reeditDuration;

/*!
 是否支持消息引用功能，默认值是YES ，聊天页面长按消息支持引用（目前仅支持文本消息、文件消息、图文消息、图片消息、引用消息的引用）
*/
@property (nonatomic, assign) BOOL enableMessageReference;

/**
小视频的最长录制时间，单位是秒，默认值是 10s。

@discussion 在集成了融云小视频功能后，可以通过此方法来设置小视频的最长录制时间。录制时间最长不能超过 2 分钟。
 */
@property (nonatomic, assign) NSUInteger sightRecordMaxDuration;

/*!
 是否开启消息自动重发功能，默认是 NO
 
 @discussion 开启后，在消息发送失败时 SDK 会自动重发
*/
@property (nonatomic, assign) BOOL enableMessageResend;

/*!
 视频上传的时长限制，单位是秒，默认值是 300。
*/
@property (nonatomic, assign) NSTimeInterval uploadVideoDurationLimit;

@end

