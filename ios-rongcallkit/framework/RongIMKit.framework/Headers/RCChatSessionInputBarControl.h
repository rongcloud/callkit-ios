//
//  RCChatSessionInputBarControl.h
//  RongExtensionKit
//
//  Created by xugang on 15/2/12.
//  Copyright (c) 2015年 RongCloud. All rights reserved.
//

#import "RCEmojiBoardView.h"
#import "RCPluginBoardView.h"
#import "RCTextView.h"
#import <RongIMLibCore/RongIMLibCore.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>
#import "RCInputContainerView.h"
#import "RCMenuContainerView.h"
#import "RCBaseNavigationController.h"
#define RC_ChatSessionInputBar_Height 49.5f
///输入栏扩展输入的唯一标识
#define INPUT_MENTIONED_SELECT_TAG 1000
#define PLUGIN_BOARD_ITEM_ALBUM_TAG 1001
#define PLUGIN_BOARD_ITEM_CAMERA_TAG 1002
#define PLUGIN_BOARD_ITEM_LOCATION_TAG 1003
#define PLUGIN_BOARD_ITEM_DESTRUCT_TAG 1004
#define PLUGIN_BOARD_ITEM_FILE_TAG 1006
#define PLUGIN_BOARD_ITEM_VOIP_TAG 1101
#define PLUGIN_BOARD_ITEM_VIDEO_VOIP_TAG 1102
#define PLUGIN_BOARD_ITEM_EVA_TAG 1103
#define PLUGIN_BOARD_ITEM_RED_PACKET_TAG 1104
#define PLUGIN_BOARD_ITEM_VOICE_INPUT_TAG 1105
#define PLUGIN_BOARD_ITEM_PTT_TAG 1106
#define PLUGIN_BOARD_ITEM_CARD_TAG 1107
#define PLUGIN_BOARD_ITEM_REMOTE_CONTROL_TAG 1108
#define PLUGIN_BOARD_ITEM_TRANSFER_TAG 1109

/*!
 输入工具栏的点击监听器
 */
@protocol RCChatSessionInputBarControlDelegate;

/*!
 输入工具栏的数据源
 */
@protocol RCChatSessionInputBarControlDataSource;

/**
 图片编辑的协议
 */
@protocol RCPictureEditDelegate;

/*!
 输入工具栏
 */
@interface RCChatSessionInputBarControl : UIView

#pragma mark - 会话属性

/*!
 当前的会话类型
 */
@property (nonatomic, assign) RCConversationType conversationType;

/*!
 当前的会话ID
 */
@property (nonatomic, strong) NSString *targetId;

#pragma mark - 代理监听
/*!
 输入工具栏的点击回调监听
 */
@property (weak, nonatomic) id<RCChatSessionInputBarControlDelegate> delegate;

/*!
 输入工具栏获取用户信息的回调
 */
@property (weak, nonatomic) id<RCChatSessionInputBarControlDataSource> dataSource;

/**
 点击编辑按钮会调用该代理的onClickEditPicture方法
 */
@property (weak, nonatomic) id<RCPictureEditDelegate> photoEditorDelegate __deprecated_msg("已废弃");

#pragma mark - 视图显示
/*!
 所处的会话页面View
 */
@property (weak, nonatomic, readonly) UIView *containerView;

/*!
 容器View
 */
@property (strong, nonatomic) RCInputContainerView *inputContainerView;

/*!
 公众服务菜单的容器View
 */
@property (strong, nonatomic) RCMenuContainerView *menuContainerView;

/*!
 公众服务菜单切换的按钮
 */
@property (strong, nonatomic) RCButton *pubSwitchButton;

/*!
 客服机器人转人工切换的按钮
 */
@property (strong, nonatomic) RCButton *robotSwitchButton;

/*!
 语音与文本输入切换的按钮
 */
@property (strong, nonatomic) RCButton *switchButton;

/*!
 录制语音消息的按钮
 */
@property (strong, nonatomic) RCButton *recordButton;

/*!
 文本输入框
 */
@property (strong, nonatomic) RCTextView *inputTextView;

/*!
 表情的按钮
 */
@property (strong, nonatomic) RCButton *emojiButton;

/*!
 扩展输入的按钮
 */
@property (strong, nonatomic) RCButton *additionalButton;

/*!
 公众服务账号菜单
 */
@property (strong, nonatomic) RCPublicServiceMenu *publicServiceMenu;

/*!
 输入扩展功能板View
 */
@property (nonatomic, strong) RCPluginBoardView *pluginBoardView;

/*!
 表情View
 */
@property (nonatomic, strong) RCEmojiBoardView *emojiBoardView;

/*!
 输入工具栏底部的 SafeArea view；当前设备没有 SafeArea，则该 view 为 nil
 */
@property (nonatomic, strong, readonly) UIView *safeAreaView;

/**
 输入工具栏上面的线

 - Since: 5.4.4，合入 5.3.6
 */
@property (nonatomic, strong, readonly) CALayer *topLineLayer;

/*!
 View即将显示的回调
 */
- (void)containerViewWillAppear;

/*!
 View已经显示的回调
 */
- (void)containerViewDidAppear;

/*!
 View即将隐藏的回调
 */
- (void)containerViewWillDisappear;

#pragma mark - 设置
/*!
 当前的输入状态
 */
@property (nonatomic,assign) KBottomBarStatus currentBottomBarStatus;

/**
 输入框最大输入行数

  该变量设置范围为: 1~6, 超过该范围会自动调整为边界值
 */
@property (nonatomic, assign) NSInteger maxInputLines;

/*!
 草稿
 */
@property (nonatomic, strong) NSString *draft;

/*!
 @提醒信息
 */
@property (nonatomic, strong, readonly) RCMentionedInfo *mentionedInfo;

/*!
 是否允许@功能
 */
@property (nonatomic, assign) BOOL isMentionedEnabled;

#pragma mark - 初始化

/*!
 初始化输入工具栏

 - Parameter frame:            显示的Frame
 - Parameter containerView:    所处的会话页面View
 - Parameter controlType:      菜单类型
 - Parameter controlStyle:     显示布局
 - Parameter defaultInputType: 默认的输入模式

 - Returns: 输入工具栏对象
 */
- (instancetype)initWithFrame:(CGRect)frame
            withContainerView:(UIView *)containerView
                  controlType:(RCChatSessionInputBarControlType)controlType
                 controlStyle:(RCChatSessionInputBarControlStyle)controlStyle
             defaultInputType:(RCChatSessionInputBarInputType)defaultInputType;

/*!
 设置输入工具栏的样式

 - Parameter type:  菜单类型
 - Parameter style: 显示布局

  您可以在会话页面RCConversationViewController的viewDidLoad之后设置，改变输入工具栏的样式。
 */
- (void)setInputBarType:(RCChatSessionInputBarControlType)type style:(RCChatSessionInputBarControlStyle)style;

/*!
 销毁公众账号弹出的菜单
 */
- (void)dismissPublicServiceMenuPopupView;

/*!
 撤销录音
 */
- (void)cancelVoiceRecord;

/*!
 结束录音
 */
- (void)endVoiceRecord;

/*!
 结束讯飞语音录入
 */
- (void)endVoiceTransfer;

/*!
 设置输入框的输入状态

 - Parameter status:          输入框状态
 - Parameter animated:        是否使用动画效果

  如果需要设置，请在输入框执行containerViewWillAppear之后（即会话页面viewWillAppear之后）。
 */
- (void)updateStatus:(KBottomBarStatus)status animated:(BOOL)animated;

/*!
 重置到默认状态
 */
- (void)resetToDefaultStatus;

- (void)clearInputData;

/*!
 内容区域大小发生变化。

  当本view所在的view frame发生变化，需要重新计算本view的frame时，调用此方法
 */
- (void)containerViewSizeChanged;

/**
 内容区域大小发生变化。

  当本view所在的view frame发生变化，需要重新计算本view的frame时，调用此方法，无动画
 */
- (void)containerViewSizeChangedNoAnnimation;

/*!
 设置默认的输入框类型

 - Parameter defaultInputType:  默认输入框类型
 */
- (void)setDefaultInputType:(RCChatSessionInputBarInputType)defaultInputType;

/*!
 添加被@的用户

 - Parameter userInfo:    被@的用户信息
 */
- (void)addMentionedUser:(RCUserInfo *)userInfo;

/*!
 打开系统相册，选择图片

  选择结果通过delegate返回
 */
- (void)openSystemAlbum;

/*!
 打开系统相机，拍摄图片

  拍摄结果通过delegate返回
 */
- (void)openSystemCamera;

/*!
 打开地图picker，选择位置

  选择结果通过delegate返回
 */
- (void)openLocationPicker;

/*!
 打开文件选择器，选择文件

  选择结果通过delegate返回
 */
- (void)openFileSelector;

/*!
 常用语列表设置

 - Parameter commonPhrasesList: 您需要展示的常用语列表

  常用语条数需大于 0 条，每条内容最多可配置 30 个字，且只支持单聊。
 */
- (BOOL)setCommonPhrasesList:(NSArray<NSString *> *)commonPhrasesList;

/*!
 按照 tag 触发扩展中某个 pluginItem 的事件
 
 - Parameter functionTag: 某个 pluginItem 的 tag
*/
- (void)openDynamicFunction:(NSInteger)functionTag;



/// 当前常用语视图的高度 0或者38
- (NSInteger)currentCommonPhrasesViewHeight;
/*!
 是否处于阅后即焚模式
*/
@property (nonatomic, assign) BOOL destructMessageMode;

@end

/*!
 输入工具栏的点击监听器
 */
@protocol RCChatSessionInputBarControlDelegate <NSObject>

/*!
 显示ViewController

 - Parameter viewController: 需要显示的ViewController
 - Parameter functionTag:    功能标识
 */
- (void)presentViewController:(UIViewController *)viewController functionTag:(NSInteger)functionTag;

@optional

/*!
 输入工具栏尺寸（高度）发生变化的回调

 - Parameter chatInputBar: 输入工具栏
 - Parameter frame:        输入工具栏最终需要显示的Frame
 */
- (void)chatInputBar:(RCChatSessionInputBarControl *)chatInputBar shouldChangeFrame:(CGRect)frame;

/*!
 点击键盘Return按钮的回调

 - Parameter inputTextView: 文本输入框
 */
- (void)inputTextViewDidTouchSendKey:(UITextView *)inputTextView;

/*!
 点击客服机器人切换按钮的回调
 */
- (void)robotSwitchButtonDidTouch;

/*!
 输入框中内容发生变化的回调

 - Parameter inputTextView: 文本输入框
 - Parameter range:         当前操作的范围
 - Parameter text:          插入的文本
 */
- (void)inputTextView:(UITextView *)inputTextView
    shouldChangeTextInRange:(NSRange)range
            replacementText:(NSString *)text;

/*!
 输入框中内容已经发生变化的回调

 - Parameter inputTextView: 文本输入框
 */
- (void)inputTextViewDidChange:(UITextView *)inputTextView;

/*!
 输入框中内容已经发生变化的回调-讯飞

 - Parameter inputTextView: 文本输入框
 */
- (void)inputTextViewDidChangeOnEndVoiceTransfer:(UITextView *)inputTextView;

/*!
 公众服务菜单的点击回调

 - Parameter selectedMenuItem: 点击的公众服务菜单项
 */
- (void)onPublicServiceMenuItemSelected:(RCPublicServiceMenuItem *)selectedMenuItem;

/*!
 点击扩展功能板中的扩展项的回调

 - Parameter pluginBoardView: 当前扩展功能板
 - Parameter tag:             点击的扩展项的唯一标识符
 */
- (void)pluginBoardView:(RCPluginBoardView *)pluginBoardView clickedItemWithTag:(NSInteger)tag;

/*!
 点击表情的回调

 - Parameter emojiView:    表情输入的View
 - Parameter touchedEmoji: 点击的表情对应的字符串编码
 */
- (void)emojiView:(RCEmojiBoardView *)emojiView didTouchedEmoji:(NSString *)touchedEmoji;

/*!
 点击发送按钮的回调

 - Parameter emojiView:  表情输入的View
 - Parameter sendButton: 发送按钮
 */
- (void)emojiView:(RCEmojiBoardView *)emojiView didTouchSendButton:(UIButton *)sendButton;

/// 常用语按钮点击事件
///
/// - Returns: 是否执行内部逻辑，返回 YES 不执行 SDK 内部逻辑，NO 执行 SDK 内部逻辑，
- (BOOL)commonPhrasesButtonDidTouch;

/*!
 点击常用语的回调

 - Parameter commonPhrases:  常用语
 */
- (void)commonPhrasesViewDidTouch:(NSString *)commonPhrases;

/*!
 即将开始录制语音消息
 返回 YES：继续录音
 返回 NO：停止录音（音频配占用时，可以处理弹窗等）
 */
- (BOOL)recordWillBegin;

/*!
 开始录制语音消息
 */
- (void)recordDidBegin;

/*!
 取消录制语音消息
 */
- (void)recordDidCancel;

/*!
 结束录制语音消息
 */
- (void)recordDidEnd:(NSData *)recordData duration:(long)duration error:(NSError *)error;

/*!
  相机拍照图片

 - Parameter image:   相机拍摄，选择发送的图片
 */
- (void)imageDidCapture:(UIImage *)image;

/**
 相机录制小视频完成后调用

 - Parameter url: 小视频url
 - Parameter image: 小视频首帧图片
 - Parameter duration: 小视频时长 单位秒
 */
- (void)sightDidFinishRecord:(NSString *)url thumbnail:(UIImage *)image duration:(NSUInteger)duration;

/**
 相机录制小视频失败后调用

 - Parameter error: 错误
 - Parameter status: AVAssetWriter 状态
 */
- (void)sightDidRecordFailedWith:(NSError *)error status:(NSInteger)status;

/*!
 地理位置选择完成之后的回调
 - Parameter location:       位置的二维坐标
 - Parameter locationName:   位置的名称
 - Parameter mapScreenShot:  位置在地图中的缩略图
  已废弃，请通过实现扩展区位置按钮点击跳转, 设置 RCLocationPickerViewController 的代理 RCLocationPickerViewControllerDelegate，来实现地理位置选择完成之后的代理回调方法。实现扩展区位置按钮点击跳转参考
 - (void)pluginBoardView:(RCPluginBoardView *)pluginBoardView clickedItemWithTag:(NSInteger)tag {
     if(tag == PLUGIN_BOARD_ITEM_LOCATION_TAG){
         RCLocationPickerViewController *picker = [[RCLocationPickerViewController alloc] init];
         picker.delegate = self;
         UINavigationController *rootVC = [[UINavigationController alloc] initWithRootViewController:picker];
         rootVC.modalPresentationStyle = UIModalPresentationFullScreen;
         [self.navigationController presentViewController:rootVC animated:YES completion:nil];
     }else{
        [super pluginBoardView:pluginBoardView clickedItemWithTag:tag];
     }
 }
 */
- (void)locationDidSelect:(CLLocationCoordinate2D)location
             locationName:(NSString *)locationName
            mapScreenShot:(UIImage *)mapScreenShot __deprecated_msg("Use RCLocationPickerViewControllerDelegate on RCLocationPickerViewController instead");

/*!
 相册选择图片列表,返回图片的 NSData

 - Parameter selectedImages:   选中的图片
 - Parameter full:             用户是否要求原图
 */
- (void)imageDataDidSelect:(NSArray *)selectedImages fullImageRequired:(BOOL)full;

/*!
 选择文件列表

 - Parameter filePathList:   被选中的文件路径list
 */
- (void)fileDidSelect:(NSArray *)filePathList;

/**
 会话页面发送文件消息，在文件选择页面选择某个文件时调用该方法方法

 - Parameter path: 文件路径
 - Returns: 返回 YES 允许文件被选中，否则不允许选中
  该方法默认返回YES，这个方法可以控制某些文件是否可以被选中。
 */
- (BOOL)canBeSelectedAtFilePath:(NSString *)path;

/*!
 输入工具栏状态变化时的回调（暂未实现）

 - Parameter bottomBarStatus: 当前状态
 */
- (void)chatSessionInputBarStatusChanged:(KBottomBarStatus)bottomBarStatus;

- (void)didSetDraft:(NSDictionary *)info;

@end

@protocol RCChatSessionInputBarControlDataSource <NSObject>

/*!
 获取待选择的用户ID列表

 - Parameter completion:  获取完成的回调
 - Parameter functionTag: 功能标识
 */
- (void)getSelectingUserIdList:(void (^)(NSArray<NSString *> *userIdList))completion functionTag:(NSInteger)functionTag;

/*!
 获取待选择的UserId的用户信息

 - Parameter userId:           用户ID
 - Returns: 用户信息
 */
- (RCUserInfo *)getSelectingUserInfo:(NSString *)userId;

/*!
 获取需要存入草稿的信息
 - Returns: 草稿信息
 */
- (NSDictionary *)getDraftExtraInfo;

@end

/**
 图片编辑的代理
 */
@protocol RCPictureEditDelegate <NSObject>

/**
 点击编辑按钮时的回调，可以通过rootCtrl控制器进行页面的跳转，在源码中默认跳转到RCPictureEditViewController

 - Parameter rootCtrl: 图片编辑根控制器，用于页面跳转
 - Parameter originalImage: 原图片
 - Parameter editCompletion: 编辑过的图片通过Block回传给SDK
 */
- (void)onClickEditPicture:(UIViewController *)rootCtrl
             originalImage:(UIImage *)originalImage
            editCompletion:(void (^)(UIImage *editedImage))editCompletion __attribute__((deprecated));

@end
