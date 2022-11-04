//
//  RCMessageCell.h
//  RongIMKit
//
//  Created by xugang on 15/1/28.
//  Copyright (c) 2015年 RongCloud. All rights reserved.
//

#import "RCContentView.h"
#import "RCMessageBaseCell.h"
#import "RCMessageCellDelegate.h"
#import "RCMessageCellNotificationModel.h"
#import "RCThemeDefine.h"
#import "RCButton.h"
#define HeadAndContentSpacing 8
#define PortraitViewEdgeSpace 12//头像与屏幕边缘距离
#define NameAndContentSpace 2
#define NameHeight 14
@class RCloudImageView;

/*!
 展示的消息Cell类

 @discussion 需要展示用户信息和内容的消息Cell可以继承此类，
 如：RCTextMessageCell、RCImageMessageCell、RCLocationMessageCell、RCVoiceMessageCell、RCRichContentMessageCell等。
 如果您需要显示自定义消息，可以继承此类。
 */
@interface RCMessageCell : RCMessageBaseCell

/*!
消息发送者的用户头像
*/
@property (nonatomic, strong) RCloudImageView *portraitImageView;

/*!
 消息发送者的用户名称
 */
@property (nonatomic, strong) UILabel *nicknameLabel;

/*!
 消息内容的View
 */
@property (nonatomic, strong) RCContentView *messageContentView;

/*!
 消息的背景View
 */
@property (nonatomic, strong) UIImageView *bubbleBackgroundView;

/*!
 显示发送状态的View

 @discussion 其中包含messageFailedStatusView子View。
 */
@property (nonatomic, strong) UIView *statusContentView;

/*!
 显示发送失败状态的View
 */
@property (nonatomic, strong) RCButton *messageFailedStatusView;

/*!
 消息发送指示View
 */
@property (nonatomic, strong) UIActivityIndicatorView *messageActivityIndicatorView;

/*!
 显示的用户头像形状
 */
@property (nonatomic, assign, setter=setPortraitStyle:) RCUserAvatarStyle portraitStyle;

/*!
 显示是否消息回执的Button

 @discussion 仅在群组和讨论组中显示
 */
@property (nonatomic, strong) UIButton *receiptView;

/*!
 消息阅读状态的 Label

 */
@property (nonatomic, strong) UILabel *receiptStatusLabel;

/*!
 是否显示头像

 */
@property (nonatomic, assign) BOOL showPortrait;
/*!
 设置当前消息Cell的数据模型

 @param model 消息Cell的数据模型
 */
- (void)setDataModel:(RCMessageModel *)model;

/*!
 更新消息发送状态

 @param model 消息Cell的数据模型
 */
- (void)updateStatusContentView:(RCMessageModel *)model;

/*!
 是否显示消息的背景气泡 View

@param show 消息Cell的数据模型
*/
- (void)showBubbleBackgroundView:(BOOL)show;

/*!
阅后即焚的回调

@discussion 阅后即焚的消息，每过 1 秒都会触发该回调更新时间
*/
- (void)messageDestructing;

/*!
阅后即焚的 UI 设置
*/
- (void)setDestructViewLayout;

/*!
点击消息视图 messageContentView 回调
*/
- (void)didTapMessageContentView;
@end
