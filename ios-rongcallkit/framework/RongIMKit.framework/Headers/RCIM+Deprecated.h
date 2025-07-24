//
//  RCIM+Deprecated.h
//  RongIMKit
//
//  Created by Sin on 2020/7/2.
//  Copyright © 2020 RongCloud. All rights reserved.
//


#import <UIKit/UIKit.h>
#import "RCIM.h"
#import "RCThemeDefine.h"

/// RCIM 的废弃接口，配置已被移动到 RCKitConfig 类中
@interface RCIM (Deprecated)

#pragma mark -- 初始化
/// 初始化融云SDK
///
/// - Parameter appKey:  从融云开发者平台创建应用后获取到的App Key
///
/// 您在使用融云SDK所有功能（包括显示SDK中或者继承于SDK的View）之前，您必须先调用此方法初始化SDK。
/// 在App整个生命周期中，您只需要执行一次初始化。
///
/// - Warning: 如果您使用IMKit，请使用此方法初始化SDK；
/// 如果您使用IMLib，请使用RCIMClient中的同名方法初始化，而不要使用此方法。
- (void)initWithAppKey:(NSString *)appKey __deprecated_msg("Use [RCIM initWithAppKey:option:] instead");

#pragma mark - Config

#pragma mark 消息通知提醒
/*!
 是否关闭所有的本地通知，默认值是NO

  当App处于后台时，默认会弹出本地通知提示，您可以通过将此属性设置为YES，关闭所有的本地通知。
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, assign) BOOL disableMessageNotificaiton __deprecated_msg("Use RCKitConfigCenter.message.disableMessageNotificaiton instead");

/*!
 是否关闭所有的前台消息提示音，默认值是NO

  当App处于前台时，默认会播放消息提示音，您可以通过将此属性设置为YES，关闭所有的前台消息提示音。
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, assign) BOOL disableMessageAlertSound __deprecated_msg("Use RCKitConfigCenter.message.disableMessageAlertSound instead");

/*!
 是否开启发送输入状态，默认值是 YES，开启之后在输入消息的时候对方可以看到正在输入的提示(目前只支持单聊)
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, assign) BOOL enableTypingStatus __deprecated_msg("Use RCKitConfigCenter.message.enableTypingStatus instead");

/*!
 开启已读回执功能的会话类型，默认为 单聊、群聊和讨论组

  这些会话类型的消息在会话页面显示了之后会发送已读回执。目前仅支持单聊、群聊和讨论组。

 OC 需转成 NSNumber 传入（例如 @[ @(ConversationType_PRIVATE) ]），
 Swift 需获取到 rawValue 传入（例如 [ RCConversationType.ConversationType_PRIVATE.rawValue ]）。
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, copy) NSArray *enabledReadReceiptConversationTypeList __deprecated_msg(
   "Use RCKitConfigCenter.message.enabledReadReceiptConversationTypeList instead");

/*!
 设置群组、讨论组发送已读回执请求的有效时间，单位是秒，默认值是 120s。

  用户在群组或讨论组中发送消息，退出会话页面再次进入时，如果超过设置的时间，则不再显示已读回执的按钮。
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, assign) NSUInteger maxReadRequestDuration __deprecated_msg(
  "Use RCKitConfigCenter.message.maxReadRequestDuration instead");

/*!
 是否开启多端同步未读状态的功能，默认值是 YES

  开启之后，用户在其他端上阅读过的消息，当前客户端会清掉该消息的未读数。目前仅支持单聊、群聊、讨论组。
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, assign) BOOL enableSyncReadStatus __deprecated_msg(
 "Use RCKitConfigCenter.message.enableSyncReadStatus instead");

/*!
 是否开启消息@提醒功能（只支持群聊和讨论组, App需要实现群成员数据源groupMemberDataSource），默认值是 YES。
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, assign) BOOL enableMessageMentioned __deprecated_msg(
"Use RCKitConfigCenter.message.enableMessageMentioned instead");

/*!
 是否开启消息撤回功能，默认值是 YES。
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, assign) BOOL enableMessageRecall __deprecated_msg(
"Use RCKitConfigCenter.message.enableMessageRecall instead");

/*!
 消息可撤回的最大时间，单位是秒，默认值是120s。
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, assign) NSUInteger maxRecallDuration __deprecated_msg(
"Use RCKitConfigCenter.message.maxRecallDuration instead");

/*!
 是否在会话页面和会话列表界面显示未注册的消息类型，默认值是 YES

  App不断迭代开发，可能会在以后的新版本中不断增加某些自定义类型的消息，但是已经发布的老版本无法识别此类消息。
 针对这种情况，可以预先定义好未注册的消息的显示，以提升用户体验（如提示当前版本不支持，引导用户升级版本等）

 未注册的消息，可以通过RCConversationViewController中的rcUnkownConversationCollectionView:cellForItemAtIndexPath:和rcUnkownConversationCollectionView:layout:sizeForItemAtIndexPath:方法定制在会话页面的显示。
 未注册的消息，可以通过修改unknown_message_cell_tip字符串资源定制在会话列表界面的显示。
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, assign) BOOL showUnkownMessage __deprecated_msg(
"Use RCKitConfigCenter.message.showUnkownMessage instead");

/*!
 未注册的消息类型是否显示本地通知，默认值是NO

  App不断迭代开发，可能会在以后的新版本中不断增加某些自定义类型的消息，但是已经发布的老版本无法识别此类消息。
 针对这种情况，可以预先定义好未注册的消息的显示，以提升用户体验（如提示当前版本不支持，引导用户升级版本等）

 未注册的消息，可以通过修改unknown_message_notification_tip字符串资源定制本地通知的显示。

 - Warning: **已废弃，请勿使用。**
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, assign) BOOL showUnkownMessageNotificaiton __deprecated_msg(
"Use RCKitConfigCenter.message.showUnkownMessageNotificaiton instead");

/*!
 语音消息的最大长度

  默认值是60s，有效值为不小于5秒，不大于60秒
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, assign) NSUInteger maxVoiceDuration __deprecated_msg(
"Use RCKitConfigCenter.message.maxVoiceDuration instead");

/*!
 APP是否独占音频

  默认是NO,录音结束之后会调用AVAudioSession 的 setActive:NO ，
 恢复其他后台APP播放的声音，如果设置成YES,不会调用 setActive:NO，这样不会中断当前APP播放的声音
 (如果当前APP 正在播放音频，这时候如果调用SDK 的录音，可以设置这里为YES)
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, assign) BOOL isExclusiveSoundPlayer __deprecated_msg(
"Use RCKitConfigCenter.message.isExclusiveSoundPlayer instead");

/*!
 选择媒体资源时，是否包含视频文件，默认值是NO

  默认是不包含
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, assign) BOOL isMediaSelectorContainVideo __deprecated_msg(
"Use RCKitConfigCenter.message.isMediaSelectorContainVideo instead");

/**
 GIF 消息自动下载的大小 size, 单位 KB
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, assign) NSInteger GIFMsgAutoDownloadSize __deprecated_msg(
"Use RCKitConfigCenter.message.GIFMsgAutoDownloadSize instead");

/*!
 是否开启合并转发功能，默认值是NO，开启之后可以合并转发消息(目前只支持单聊和群聊)
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, assign) BOOL enableSendCombineMessage __deprecated_msg(
"Use RCKitConfigCenter.message.enableSendCombineMessage instead");

/*!
 是否开启阅后即焚功能，默认值是NO，开启之后可以在聊天页面扩展板中使用阅后即焚功能(目前只支持单聊)

  目前 IMKit 仅支持文本、语音、图片、小视频消息。
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, assign) BOOL enableDestructMessage __deprecated_msg(
"Use RCKitConfigCenter.message.enableDestructMessage instead");

/*!
 消息撤回后可重新编辑的时间，单位是秒，默认值是 300s。

  目前消息撤回后重新编辑仅为本地操作，卸载重装或者更换设备不会同步。
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, assign) NSUInteger reeditDuration __deprecated_msg(
"Use RCKitConfigCenter.message.reeditDuration instead");

/*!
 是否支持消息引用功能，默认值是YES ，聊天页面长按消息支持引用（目前仅支持文本消息、文件消息、图文消息、图片消息、引用消息的引用）
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
*/
@property (nonatomic, assign) BOOL enableMessageReference __deprecated_msg(
"Use RCKitConfigCenter.message.enableMessageReference instead");

/**
小视频的最长录制时间，单位是秒，默认值是 10s。

 在集成了融云小视频功能后，可以通过此方法来设置小视频的最长录制时间。录制时间最长不能超过 2 分钟。
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, assign) NSUInteger sightRecordMaxDuration __deprecated_msg(
"Use RCKitConfigCenter.message.sightRecordMaxDuration instead");

#pragma mark 头像显示

/*!
 SDK中全局的导航按钮字体颜色

  默认值为[UIColor blackColor]
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, strong) UIColor *globalNavigationBarTintColor __deprecated_msg(
"Use RCKitConfigCenter.ui.globalNavigationBarTintColor instead");

/*!
 SDK会话列表界面中显示的头像形状，矩形或者圆形

  默认值为矩形，即RC_USER_AVATAR_RECTANGLE
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, assign) RCUserAvatarStyle globalConversationAvatarStyle __deprecated_msg(
"Use RCKitConfigCenter.ui.globalConversationAvatarStyle instead");

/*!
 SDK会话列表界面中显示的头像大小，高度必须大于或者等于36

  默认值为46*46
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, assign) CGSize globalConversationPortraitSize __deprecated_msg(
"Use RCKitConfigCenter.ui.globalConversationPortraitSize instead");

/*!
 SDK会话页面中显示的头像形状，矩形或者圆形

  默认值为矩形，即RC_USER_AVATAR_RECTANGLE
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, assign) RCUserAvatarStyle globalMessageAvatarStyle __deprecated_msg(
"Use RCKitConfigCenter.ui.globalMessageAvatarStyle instead");

/*!
 SDK会话页面中显示的头像大小

  默认值为40*40
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, assign) CGSize globalMessagePortraitSize __deprecated_msg(
"Use RCKitConfigCenter.ui.globalMessagePortraitSize instead");

/*!
 SDK会话列表界面和会话页面的头像的圆角曲率半径

  默认值为4，只有当头像形状设置为矩形时才会生效。
 参考RCIM的globalConversationAvatarStyle和globalMessageAvatarStyle。
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
 */
@property (nonatomic, assign) CGFloat portraitImageViewCornerRadius __deprecated_msg(
"Use RCKitConfigCenter.ui.portraitImageViewCornerRadius instead");

/*!
是否支持暗黑模式，默认值是NO，开启之后 UI 支持暗黑模式，可以跟随系统切换
  swift 如果调用宏定义 RCKitConfigCenter 报错，替换为 RCKitConfig 的单例构造方法
*/
@property (nonatomic, assign) BOOL enableDarkMode __deprecated_msg(
"Use RCKitConfigCenter.ui.enableDarkMode instead");

/// 更新群组信息
/// - Parameter groupInfo: 群组信息，groupId 必填，否则更新失败
/// - Parameter success: 成功回调
/// - Parameter error: 失败回调
///
/// - Since: 5.12.2
- (void)updateGroupInfo:(RCGroupInfo *)groupInfo
                success:(void (^)(void))successBlock
                  error:(void (^)(RCErrorCode errorCode, NSString *errorKey))errorBlock NS_SWIFT_NAME(updateGroupInfo(_:success:error:))__deprecated_msg("Use -[RCIM updateGroupInfo:successBlock:errorBlock:] instead");

/// 设置群成员资料
/// - Parameter groupId: 群组ID
/// - Parameter userId: 用户ID， 必填项，支持传入当前登录用户 ID
/// - Parameter nickname: 用户昵称，非必填项，长度不超过 64 个字符，传 nil 或 空字符串表示移除用户昵称
/// - Parameter extra: 附加信息，非必填项，长度不超过 128 个字符
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.2
- (void)setGroupMemberInfo:(NSString *)groupId
                    userId:(NSString *)userId
                  nickname:(nullable NSString *)nickname
                     extra:(nullable NSString *)extra
                   success:(void (^)(void))successBlock
                     error:(void (^)(RCErrorCode errorCode))errorBlock __deprecated_msg("Use -[RCIM setGroupMemberInfo:userId:nickname:extra:successBlock:errorBlock:] instead");
/// 修改自己的用户信息
///
/// - Parameter profile: 用户信息
/// - Parameter successBlock: 成功的回调
/// - Parameter errorBlock: 失败的回调
///
/// - Since: 5.12.2
- (void)updateMyUserProfile:(RCUserProfile *)profile
                    success:(void (^)(void))successBlock
                      error:(nullable void (^)(RCErrorCode errorCode, NSString * _Nullable errorKey))errorBlock __deprecated_msg("Use -[RCIM updateMyUserProfile:successBlock:errorBlock:] instead");
/// 好友信息设置
/// - Parameter userId: 用户ID
/// - Parameter remark: 好友备注，最多为 64 个字符，不传或为空时清除备注名。
/// - Parameter extProfile: 扩展信息
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
///
/// - Since: 5.12.2
- (void)setFriendInfo:(NSString *)userId
               remark:(nullable NSString *)remark
           extProfile:(nullable NSDictionary<NSString *, NSString*> *)extProfile
              success:(void (^)(void))successBlock
                error:(void (^)(RCErrorCode errorCode))errorBlock __deprecated_msg("Use -[RCIM setFriendInfo:remark:extProfile:successBlock:errorBlock:] instead");
@end
