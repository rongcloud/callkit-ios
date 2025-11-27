//
//  RCEditInputContainerView.h
//  RongIMKit
//
//  Created by RongCloud on 2025/07/28.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RCButton.h"
#import "RCTextView.h"
#import "RCBaseView.h"
#import "RCExtensionKitDefine.h"

NS_ASSUME_NONNULL_BEGIN

// 编辑模式高度状态
typedef NS_ENUM(NSInteger, RCEditHeightMode) {
    RCEditHeightModeNormal = 0,     // 普通编辑
    RCEditHeightModeExpanded = 1    // 全屏编辑
};

@protocol RCEditInputContainerViewDelegate;

@interface RCEditInputContainerView : RCBaseView

#pragma mark - 核心属性

/// 文本输入框
@property (nonatomic, strong, readonly) RCTextView *inputTextView;

/// 编辑模式高度状态
@property (nonatomic, assign, readonly) RCEditHeightMode heightMode;

/// 输入框最大输入行数
/// 该变量设置范围为: 1~6, 超过该范围会自动调整为边界值
@property (nonatomic, assign) NSInteger maxInputLines;

/// 代理
@property (nonatomic, weak) id<RCEditInputContainerViewDelegate> delegate;

/// 输入框编辑状态（用于键盘弹起判断）
@property (nonatomic, assign, readonly) BOOL textViewBeginEditing;

#pragma mark - 编辑模式按钮

/// 展开/收起按钮
@property (nonatomic, strong, readonly) UIButton *editExpandButton;

/// 确认按钮
@property (nonatomic, strong, readonly) UIButton *editConfirmButton;

/// 取消按钮
@property (nonatomic, strong, readonly) UIButton *editCancelButton;

/// 编辑模式表情按钮
@property (nonatomic, strong, readonly) UIButton *editEmojiButton;

#pragma mark - 引用消息支持

/// 是否有引用消息
@property (nonatomic, assign) BOOL hasReferenceMessage;

/// 引用消息发送者姓名
@property (nonatomic, copy, nullable) NSString *referencedSenderName;

/// 引用消息内容
@property (nonatomic, copy, nullable) NSString *referencedContent;

#pragma mark - 公共方法

/// 初始化方法
/// - Parameter heightMode: 输入框的高度模式，普通还是全屏
- (instancetype)initWithHeightMode:(RCEditHeightMode)heightMode;

/// 设置引用消息内容
/// - Parameter senderName: 发送者姓名
/// - Parameter content: 消息内容
- (void)setReferencedContentWithSenderName:(NSString * _Nullable)senderName content:(NSString * _Nullable)content;

/// 清除引用消息
- (void)clearReferencedMessage;

/// 设置输入文本
/// - Parameter text: 文本内容
- (void)setInputText:(NSString *)text;

/// 获取输入文本
- (NSString *)getInputText;

/// 让输入框成为第一响应者
- (void)becomeInputViewFirstResponder;

/// 让输入框失去第一响应者
- (void)resignInputViewFirstResponder;

/// 设置输入容器的可用状态（包含UI和交互状态）
/// - Parameter enabled: 是否可用
/// - Parameter statusMessage: 状态提示信息，nil则隐藏提示
- (void)setEditEnabled:(BOOL)enabled withStatusMessage:(NSString * _Nullable)statusMessage;

@end

#pragma mark - 代理协议

@protocol RCEditInputContainerViewDelegate <NSObject>

@required

/// 请求展开到全屏编辑模式
/// - Parameter editContainerView: 编辑容器视图
- (void)editInputContainerViewRequestFullScreenEdit:(RCEditInputContainerView *)editContainerView;

/// 请求从全屏编辑模式收起
/// - Parameter editContainerView: 编辑容器视图
- (void)editInputContainerViewCollapseFromFullScreenEdit:(RCEditInputContainerView *)editContainerView;

/// 编辑确认
/// - Parameter editContainerView: 编辑容器视图
/// - Parameter text: 编辑后的文本
- (void)editInputContainerViewEditConfirm:(RCEditInputContainerView *)editContainerView withText:(NSString *)text;

/// 编辑取消
/// - Parameter editContainerView: 编辑容器视图
- (void)editInputContainerViewEditCancel:(RCEditInputContainerView *)editContainerView;

/// 编辑模式表情按钮点击
/// - Parameter editContainerView: 编辑容器视图
- (void)editInputContainerViewEditEmojiButtonClicked:(RCEditInputContainerView *)editContainerView;

@optional

/// 容器视图高度发生变化
/// - Parameter editContainerView: 编辑容器视图
/// - Parameter frame: 新的frame
- (void)editInputContainerView:(RCEditInputContainerView *)editContainerView didChangeFrame:(CGRect)frame;

/// 输入文本发生变化
/// - Parameter editContainerView: 编辑容器视图
/// - Parameter textView: 文本输入框
- (void)editInputContainerView:(RCEditInputContainerView *)editContainerView inputTextViewDidChange:(UITextView *)textView;

/// 输入文本将要变化
/// - Parameter editContainerView: 编辑容器视图
/// - Parameter textView: 文本输入框
/// - Parameter range: 变化范围
/// - Parameter text: 替换文本
- (BOOL)editInputContainerView:(RCEditInputContainerView *)editContainerView
                 inputTextView:(UITextView *)textView
         shouldChangeTextInRange:(NSRange)range 
                 replacementText:(NSString *)text;

@end

NS_ASSUME_NONNULL_END
