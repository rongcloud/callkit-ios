//
//  RCFullScreenEditView.h
//  RongIMKit
//
//  Created by RongCloud Code on 2025/7/17.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RongIMLibCore/RongIMLibCore.h>
#import "RCEditInputBarControl.h"

NS_ASSUME_NONNULL_BEGIN

@class RCFullScreenEditView;

@protocol RCFullScreenEditViewDelegate <NSObject>

/// 全屏编辑点击折叠退出全屏编辑
- (void)fullScreenEditViewCollapse:(RCFullScreenEditView *)fullScreenEditView;

/// 编辑输入控件点击确认
/// - Parameter fullScreenEditView: 全屏编辑 view
/// - Parameter text: 编辑输入框中的文本
- (void)fullScreenEditView:(RCFullScreenEditView *)fullScreenEditView didConfirmWithText:(NSString *)text;

/// 编辑点击取消
- (void)fullScreenEditViewCancel:(RCFullScreenEditView *)fullScreenEditView;

/// 编辑输入控件显示用户选择器
- (void)fullScreenEditView:(RCFullScreenEditView *)fullScreenEditView
          showUserSelector:(void (^)(RCUserInfo *selectedUser))selectedBlock
                    cancel:(void (^)(void))cancelBlock;

@end

@interface RCFullScreenEditView : UIView

/// 会话类型
@property (nonatomic, assign) RCConversationType conversationType;

/// 目标ID
@property (nonatomic, copy) NSString *targetId;

/// 代理
@property (nonatomic, weak) id<RCFullScreenEditViewDelegate> delegate;

/// 编辑输入容器
@property (nonatomic, strong) RCEditInputBarControl *editInputBarControl;

/// @ 功能是否开启
@property (nonatomic, assign) BOOL isMentionedEnabled;

/// 显示全屏编辑页面
/// - Parameter config: 编辑配置信息
/// - Parameter animated：是否开启动画
- (void)showWithConfig:(RCEditInputBarConfig *)config animation:(BOOL)animated;

/// 隐藏全屏编辑视图
/// - Parameter animated: 是否开启动画
/// - Parameter completion: 隐藏完成的回调
- (void)hideWithAnimation:(BOOL)animated completion:(void(^_Nullable)(void))completion;

@end

NS_ASSUME_NONNULL_END
