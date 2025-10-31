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
#import "RCThemeDefine.h"
#import "RCButton.h"
#import "RCBaseButton.h"
#import "RCBaseImageView.h"
#import "RCReadReceiptProgressView.h"
#define HeadAndContentSpacing 8
#define PortraitViewEdgeSpace 12//头像与屏幕边缘距离
#define NameAndContentSpace 2
#define NameHeight 14
@class RCloudImageView;
@class RCCircularLoadingView;

/*!
 展示的消息Cell类

  需要展示用户信息和内容的消息Cell可以继承此类，
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
@property (nonatomic, strong) RCBaseImageView *bubbleBackgroundView;

/*!
 显示发送状态的View

  其中包含messageFailedStatusView子View。
 */
@property (nonatomic, strong) UIView *statusContentView;

/*!
 显示发送失败状态的View
 */
@property (nonatomic, strong) RCButton *messageFailedStatusView;

/// 消息编辑状态的 view，包含更新中、更新失败等状态
@property (nonatomic, strong) UIView *editStatusContentView;

/// 消息编辑状态的 label
@property (nonatomic, strong) UILabel *editStatusLabel;

/// 消息编辑失败时，显示的按钮
@property (nonatomic, strong) UIButton *editRetryButton;


@property (nonatomic, strong) RCCircularLoadingView *editCircularLoadingView;

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

  仅在群组和讨论组中显示
 */
@property (nonatomic, strong) RCBaseButton *receiptView;

/*!
 消息阅读状态的 Label

 */
@property (nonatomic, strong) UILabel *receiptStatusLabel;

/*!
 已读回执进度视图（V5 版本）
 用于显示群组消息已读进度
 */
@property (strong, nonatomic) RCReadReceiptProgressView *receiptProgressView;

/*!
 是否显示头像

 */
@property (nonatomic, assign) BOOL showPortrait;

@property (nonatomic, weak, readonly) UICollectionView *hostCollectionView;
/*!
 设置当前消息Cell的数据模型

 - Parameter model: 消息Cell的数据模型
 */
- (void)setDataModel:(RCMessageModel *)model;

/*!
 更新消息发送状态

 - Parameter model: 消息Cell的数据模型
 */
- (void)updateStatusContentView:(RCMessageModel *)model;

/*!
 是否显示消息的背景气泡 View

- Parameter show: 消息Cell的数据模型
*/
- (void)showBubbleBackgroundView:(BOOL)show;

/*!
 获取默认的消息气泡背景图片
 
 @return 消息气泡背景图片
 */
- (UIImage *)getDefaultMessageCellBackgroundImage;

/*!
阅后即焚的回调

 阅后即焚的消息，每过 1 秒都会触发该回调更新时间
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
