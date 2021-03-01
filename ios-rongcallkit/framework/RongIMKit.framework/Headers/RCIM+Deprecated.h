//
//  RCIM+Deprecated.h
//  RongIMKit
//
//  Created by Sin on 2020/7/2.
//  Copyright © 2020 RongCloud. All rights reserved.
//


#import <UIKit/UIKit.h>
#import "RCIM.h"

/// RCIM 的废弃接口，配置已被移动到 RCKitConfig 类中
@interface RCIM (Deprecated)
#pragma mark - Config

#pragma mark 消息通知提醒
/*!
 是否关闭所有的本地通知，默认值是NO

 @discussion 当App处于后台时，默认会弹出本地通知提示，您可以通过将此属性设置为YES，关闭所有的本地通知。
 */
@property (nonatomic, assign) BOOL disableMessageNotificaiton __deprecated_msg("已废弃，请使用 RCKitConfigCenter.message.disableMessageNotificaiton");

/*!
 是否关闭所有的前台消息提示音，默认值是NO

 @discussion 当App处于前台时，默认会播放消息提示音，您可以通过将此属性设置为YES，关闭所有的前台消息提示音。
 */
@property (nonatomic, assign) BOOL disableMessageAlertSound __deprecated_msg("已废弃，请使用 RCKitConfigCenter.message.disableMessageAlertSound");

/*!
 是否开启发送输入状态，默认值是 YES，开启之后在输入消息的时候对方可以看到正在输入的提示(目前只支持单聊)
 */
@property (nonatomic, assign) BOOL enableTypingStatus __deprecated_msg("已废弃，请使用 RCKitConfigCenter.message.enableTypingStatus");

/*!
 开启已读回执功能的会话类型，默认为 单聊、群聊和讨论组

 @discussion 这些会话类型的消息在会话页面显示了之后会发送已读回执。目前仅支持单聊、群聊和讨论组。

 OC 需转成 NSNumber 传入（例如 @[ @(ConversationType_PRIVATE) ]），
 Swift 需获取到 rawValue 传入（例如 [ RCConversationType.ConversationType_PRIVATE.rawValue ]）。
 */
@property (nonatomic, copy) NSArray *enabledReadReceiptConversationTypeList __deprecated_msg(
   "已废弃，请使用 RCKitConfigCenter.message.enabledReadReceiptConversationTypeList，设置开启回执的会话类型。");

/*!
 设置群组、讨论组发送已读回执请求的有效时间，单位是秒，默认值是 120s。

 @discussion 用户在群组或讨论组中发送消息，退出会话页面再次进入时，如果超过设置的时间，则不再显示已读回执的按钮。
 */
@property (nonatomic, assign) NSUInteger maxReadRequestDuration __deprecated_msg(
  "已废弃，请使用 RCKitConfigCenter.message.maxReadRequestDuration");

/*!
 是否开启多端同步未读状态的功能，默认值是 YES

 @discussion 开启之后，用户在其他端上阅读过的消息，当前客户端会清掉该消息的未读数。目前仅支持单聊、群聊、讨论组。
 */
@property (nonatomic, assign) BOOL enableSyncReadStatus __deprecated_msg(
 "已废弃，请使用 RCKitConfigCenter.message.enableSyncReadStatus");

/*!
 是否开启消息@提醒功能（只支持群聊和讨论组, App需要实现群成员数据源groupMemberDataSource），默认值是 YES。
 */
@property (nonatomic, assign) BOOL enableMessageMentioned __deprecated_msg(
"已废弃，请使用 RCKitConfigCenter.message.enableMessageMentioned");

/*!
 是否开启消息撤回功能，默认值是 YES。
 */
@property (nonatomic, assign) BOOL enableMessageRecall __deprecated_msg(
"已废弃，请使用 RCKitConfigCenter.message.enableMessageRecall");

/*!
 消息可撤回的最大时间，单位是秒，默认值是120s。
 */
@property (nonatomic, assign) NSUInteger maxRecallDuration __deprecated_msg(
"已废弃，请使用 RCKitConfigCenter.message.maxRecallDuration");

/*!
 是否在会话页面和会话列表界面显示未注册的消息类型，默认值是 YES

 @discussion App不断迭代开发，可能会在以后的新版本中不断增加某些自定义类型的消息，但是已经发布的老版本无法识别此类消息。
 针对这种情况，可以预先定义好未注册的消息的显示，以提升用户体验（如提示当前版本不支持，引导用户升级版本等）

 未注册的消息，可以通过RCConversationViewController中的rcUnkownConversationCollectionView:cellForItemAtIndexPath:和rcUnkownConversationCollectionView:layout:sizeForItemAtIndexPath:方法定制在会话页面的显示。
 未注册的消息，可以通过修改unknown_message_cell_tip字符串资源定制在会话列表界面的显示。
 */
@property (nonatomic, assign) BOOL showUnkownMessage __deprecated_msg(
"已废弃，请使用 RCKitConfigCenter.message.showUnkownMessage");

/*!
 未注册的消息类型是否显示本地通知，默认值是NO

 @discussion App不断迭代开发，可能会在以后的新版本中不断增加某些自定义类型的消息，但是已经发布的老版本无法识别此类消息。
 针对这种情况，可以预先定义好未注册的消息的显示，以提升用户体验（如提示当前版本不支持，引导用户升级版本等）

 未注册的消息，可以通过修改unknown_message_notification_tip字符串资源定制本地通知的显示。

 @warning **已废弃，请勿使用。**
 */
@property (nonatomic, assign) BOOL showUnkownMessageNotificaiton __deprecated_msg(
"已废弃，请使用 RCKitConfigCenter.message.showUnkownMessageNotificaiton");

/*!
 语音消息的最大长度

 @discussion 默认值是60s，有效值为不小于5秒，不大于60秒
 */
@property (nonatomic, assign) NSUInteger maxVoiceDuration __deprecated_msg(
"已废弃，请使用 RCKitConfigCenter.message.maxVoiceDuration");

/*!
 APP是否独占音频

 @discussion 默认是NO,录音结束之后会调用AVAudioSession 的 setActive:NO ，
 恢复其他后台APP播放的声音，如果设置成YES,不会调用 setActive:NO，这样不会中断当前APP播放的声音
 (如果当前APP 正在播放音频，这时候如果调用SDK 的录音，可以设置这里为YES)
 */
@property (nonatomic, assign) BOOL isExclusiveSoundPlayer __deprecated_msg(
"已废弃，请使用 RCKitConfigCenter.message.isExclusiveSoundPlayer");

/*!
 选择媒体资源时，是否包含视频文件，默认值是NO

 @discussion 默认是不包含
 */
@property (nonatomic, assign) BOOL isMediaSelectorContainVideo __deprecated_msg(
"已废弃，请使用 RCKitConfigCenter.message.isMediaSelectorContainVideo");

/**
 GIF 消息自动下载的大小 size, 单位 KB
 */
@property (nonatomic, assign) NSInteger GIFMsgAutoDownloadSize __deprecated_msg(
"已废弃，请使用 RCKitConfigCenter.message.GIFMsgAutoDownloadSize");

/*!
 是否开启合并转发功能，默认值是NO，开启之后可以合并转发消息(目前只支持单聊和群聊)
 */
@property (nonatomic, assign) BOOL enableSendCombineMessage __deprecated_msg(
"已废弃，请使用 RCKitConfigCenter.message.enableSendCombineMessage");

/*!
 是否开启阅后即焚功能，默认值是NO，开启之后可以在聊天页面扩展板中使用阅后即焚功能(目前只支持单聊)

 @discussion 目前 IMKit 仅支持文本、语音、图片、小视频消息。
 */
@property (nonatomic, assign) BOOL enableDestructMessage __deprecated_msg(
"已废弃，请使用 RCKitConfigCenter.message.enableDestructMessage");

/*!
 消息撤回后可重新编辑的时间，单位是秒，默认值是 300s。

 @discussion 目前消息撤回后重新编辑仅为本地操作，卸载重装或者更换设备不会同步。
 */
@property (nonatomic, assign) NSUInteger reeditDuration __deprecated_msg(
"已废弃，请使用 RCKitConfigCenter.message.reeditDuration");

/*!
 是否支持消息引用功能，默认值是YES ，聊天页面长按消息支持引用（目前仅支持文本消息、文件消息、图文消息、图片消息、引用消息的引用）
*/
@property (nonatomic, assign) BOOL enableMessageReference __deprecated_msg(
"已废弃，请使用 RCKitConfigCenter.message.enableMessageReference");

/**
小视频的最长录制时间，单位是秒，默认值是 10s。

@discussion 在集成了融云小视频功能后，可以通过此方法来设置小视频的最长录制时间。录制时间最长不能超过 2 分钟。
 */
@property (nonatomic, assign) NSUInteger sightRecordMaxDuration __deprecated_msg(
"已废弃，请使用 RCKitConfigCenter.message.sightRecordMaxDuration");

#pragma mark 头像显示

/*!
 SDK中全局的导航按钮字体颜色

 @discussion 默认值为[UIColor whiteColor]
 */
@property (nonatomic, strong) UIColor *globalNavigationBarTintColor __deprecated_msg(
"已废弃，请使用 RCKitConfigCenter.ui.globalNavigationBarTintColor");

/*!
 SDK会话列表界面中显示的头像形状，矩形或者圆形

 @discussion 默认值为矩形，即RC_USER_AVATAR_RECTANGLE
 */
@property (nonatomic, assign) RCUserAvatarStyle globalConversationAvatarStyle __deprecated_msg(
"已废弃，请使用 RCKitConfigCenter.ui.globalConversationAvatarStyle");

/*!
 SDK会话列表界面中显示的头像大小，高度必须大于或者等于36

 @discussion 默认值为46*46
 */
@property (nonatomic, assign) CGSize globalConversationPortraitSize __deprecated_msg(
"已废弃，请使用 RCKitConfigCenter.ui.globalConversationPortraitSize");

/*!
 SDK会话页面中显示的头像形状，矩形或者圆形

 @discussion 默认值为矩形，即RC_USER_AVATAR_RECTANGLE
 */
@property (nonatomic, assign) RCUserAvatarStyle globalMessageAvatarStyle __deprecated_msg(
"已废弃，请使用 RCKitConfigCenter.ui.globalMessageAvatarStyle");

/*!
 SDK会话页面中显示的头像大小

 @discussion 默认值为40*40
 */
@property (nonatomic, assign) CGSize globalMessagePortraitSize __deprecated_msg(
"已废弃，请使用 RCKitConfigCenter.ui.globalMessagePortraitSize");

/*!
 SDK会话列表界面和会话页面的头像的圆角曲率半径

 @discussion 默认值为4，只有当头像形状设置为矩形时才会生效。
 参考RCIM的globalConversationAvatarStyle和globalMessageAvatarStyle。
 */
@property (nonatomic, assign) CGFloat portraitImageViewCornerRadius __deprecated_msg(
"已废弃，请使用 RCKitConfigCenter.ui.portraitImageViewCornerRadius");

/*!
是否支持暗黑模式，默认值是NO，开启之后 UI 支持暗黑模式，可以跟随系统切换
*/
@property (nonatomic, assign) BOOL enableDarkMode __deprecated_msg(
"已废弃，请使用 RCKitConfigCenter.ui.enableDarkMode");
@end
