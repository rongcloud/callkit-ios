//
//  RCEditInputBarControl.h
//  RongIMKit
//
//  Created by RongCloud Code on 2025/7/16.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RongIMLibCore/RongIMLibCore.h>
#import "RCEditInputContainerView.h"
#import "RCEmojiBoardView.h"
#import "RCEditInputBarConfig.h"

NS_ASSUME_NONNULL_BEGIN

@class RCEditInputBarControl;

@protocol RCEditInputBarControlDelegate <NSObject>

@required
/// 编辑确认
/// - Parameter editInputBarControl: 编辑控件
/// - Parameter text: 编辑后的文本
- (void)editInputBarControl:(RCEditInputBarControl *)editInputBarControl didConfirmWithText:(NSString *)text;

/// 编辑取消
/// - Parameter editInputBarControl: 编辑控件
- (void)editInputBarControlDidCancel:(RCEditInputBarControl *)editInputBarControl;

/// 请求全屏编辑
- (void)editInputBarControlRequestFullScreenEdit:(RCEditInputBarControl *)editInputBarControl;

/// 请求退出全屏编辑
- (void)editInputBarControlCollapseFromFullScreenEdit:(RCEditInputBarControl *)editInputBarControl;

@optional

/// 请求显示用户选择界面（用于 @ 功能）
/// - Parameter editInputBarControl: 编辑控件
/// - Parameter selectedBlock: 用户选择完成回调
/// - Parameter cancelBlock: 取消回调
- (void)editInputBarControl:(RCEditInputBarControl *)editInputBarControl
           showUserSelector:(void (^)(RCUserInfo *selectedUser))selectedBlock
                     cancel:(void (^)(void))cancelBlock;

/// 编辑控件高度变化
/// - Parameter editInputBarControl: 编辑控件
/// - Parameter frame: 新的frame
- (void)editInputBarControl:(RCEditInputBarControl *)editInputBarControl shouldChangeFrame:(CGRect)frame;

@end

@protocol RCEditInputBarControlDataSource <NSObject>

@optional

/// 获取用户信息（用于 @ 功能）
/// - Parameter editInputBarControl: 编辑控件
/// - Parameter userId: 用户ID
/// - Returns 用户信息
- (nullable RCUserInfo *)editInputBarControl:(RCEditInputBarControl *)editInputBarControl
                                 getUserInfo:(NSString *)userId;

@end

/// 专门的编辑控件
@interface RCEditInputBarControl : UIView <RCEditInputContainerViewDelegate, RCEmojiViewDelegate>

#pragma mark - 基本属性

/// 编辑控件的代理
@property (nonatomic, weak, nullable) id<RCEditInputBarControlDelegate> delegate;

/// 编辑控件的数据源
@property (nonatomic, weak, nullable) id<RCEditInputBarControlDataSource> dataSource;

/// 会话类型
@property (nonatomic, assign) RCConversationType conversationType;

/// 目标ID
@property (nonatomic, copy) NSString *targetId;

/// 底部面板的父视图，如果提供了父视图，底部面板的 origin.x 和 origin.y 都为 0
/// 如果不设置此参数，底部面板默认显示在 RCEditInputBarControl 的父视图上，布局在屏幕底部。
@property (nonatomic, strong) UIView *bottomPanelsContainerView;

/// 是否可见
@property (nonatomic, assign) BOOL isVisible;

/// 是否全屏模式
@property (nonatomic, assign, readonly) BOOL isFullScreen;

/// 当前编辑是否可用（业务逻辑状态）默认为可编辑。
/// 如需设置不可编辑，请调用 `setEditStatus:reason:` 方法。
@property (nonatomic, assign, readonly) BOOL canEdit;

/// 当前编辑的 @ 信息（用于发送消息时获取）
@property (nonatomic, strong, readonly, nullable) RCMentionedInfo *mentionedInfo;

/// 是否启用 @ 功能
@property (nonatomic, assign) BOOL isMentionedEnabled;

/// 当前底部面板的状态
@property (nonatomic, assign, readonly) KBottomBarStatus currentBottomBarStatus;

/// 编辑输入框的配置信息
@property (nonatomic, strong) RCEditInputBarConfig *inputBarConfig;

/// 初始化方法
- (instancetype)initWithIsFullScreen:(BOOL)isFullScreen;

/// 添加 @ 用户（支持symbolRequest参数）
/// - Parameter userInfo: 用户信息
/// - Parameter symbolRequest: 是否需要插入@符号（YES=插入@符号+用户名，NO=只插入用户名，假设@符号已存在）
- (void)addMentionedUser:(RCUserInfo *)userInfo symbolRequest:(BOOL)symbolRequest;

/// 设置引用消息信息，一般用来更新引用消息的内容显示
/// - Parameter senderName: 引用消息发送者姓名
/// - Parameter content:    引用消息内容
- (void)setReferenceInfo:(NSString *)senderName content:(NSString *)content;

#pragma mark - 核心组件

/// 编辑输入容器
@property (nonatomic, strong, readonly) RCEditInputContainerView *editInputContainer;

/// 表情面板
@property (nonatomic, strong, readonly, nullable) RCEmojiBoardView *emojiBoardView;

#pragma mark - 编辑状态管理

/// 标记编辑已过期
- (void)markEditAsExpired;

/// 恢复编辑状态
- (void)restoreEditStatus;

#pragma mark - 公共方法

/// 显示编辑输入框
- (void)showWithConfig:(RCEditInputBarConfig *)config;

/// 退出编辑输入框
- (void)exitWithAnimation:(BOOL)animated completion:(void (^ _Nullable)(void))completion;

/// 获取当前编辑文本
- (NSString *)currentEditText;

/// 设置编辑文本
/// - Parameter text: 文本内容
- (void)setEditText:(NSString *)text;

/// 恢复输入焦点
- (void)restoreFocus;

/// 隐藏底部面板，包含表情面板或键盘
- (void)hideBottomPanelsWithAnimation:(BOOL)animated completion:(void (^ _Nullable)(void))completion;

/// 设置编辑控件显示/隐藏状态（不退出编辑模式）
/// - Parameter hidden: 是否隐藏
- (void)hideEditInputBar:(BOOL)hidden;

/// 重置编辑控件，清空编辑内容
- (void)resetEditInputBar;

/// 检查是否有编辑内容
- (BOOL)hasContent;

#pragma mark - 光标位置

/// 获取当前光标位置
- (NSRange)getCurrentCursorPosition;

/// 设置光标位置
/// - Parameter range: 光标位置范围
- (void)setCursorPosition:(NSRange)range;

@end

NS_ASSUME_NONNULL_END
