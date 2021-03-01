//
//  RCInputContainerView.h
//  RongIMKit
//
//  Created by 张改红 on 2020/5/26.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RCButton.h"
#import "RCTextView.h"
#import "RCExtensionKitDefine.h"

@protocol RCInputContainerViewDelegate;

@interface RCInputContainerView : UIView
/*!
 语音与文本输入切换的按钮
 */
@property (strong, nonatomic) RCButton *switchButton;

/*!
 录制语音消息的按钮
 */
@property (nonatomic, strong) RCButton *recordButton;

/*!
 文本输入框
 */
@property (nonatomic, strong) RCTextView *inputTextView;

/*!
 表情的按钮
 */
@property (nonatomic, strong) RCButton *emojiButton;

/*!
 扩展输入的按钮
 */
@property (nonatomic, strong) RCButton *additionalButton;

@property (nonatomic, assign) KBottomBarStatus currentBottomBarStatus;

/**
 输入框最大输入行数

 @discussion 该变量设置范围为: 1~6, 超过该范围会自动调整为边界值
 */
@property (nonatomic, assign) NSInteger maxInputLines;

//是否处于阅后即焚模式
@property (nonatomic, assign) BOOL destructMessageMode;

@property (nonatomic, weak) id<RCInputContainerViewDelegate> delegate;

- (void)setInputBarStyle:(RCChatSessionInputBarControlStyle)style;

- (void)setBottomBarWithStatus:(KBottomBarStatus)bottomBarStatus;

@end

@protocol RCInputContainerViewDelegate <NSObject>

- (void)inputContainerViewSwitchButtonClicked:(RCInputContainerView *)inputContainerView;

- (void)inputContainerViewEmojiButtonClicked:(RCInputContainerView *)inputContainerView;

- (void)inputContainerViewAdditionalButtonClicked:(RCInputContainerView *)inputContainerView;

- (void)inputContainerView:(RCInputContainerView *)inputContainerView forControlEvents:(UIControlEvents)controlEvents;

- (void)inputContainerView:(RCInputContainerView *)inputContainerView didChangeFrame:(CGRect)frame;

- (BOOL)inputTextView:(UITextView *)inputTextView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text;
@end
