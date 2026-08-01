//
//  RCReferenceInputBarView.h
//  RongIMKit
//
//  Created by RongCloud on 2026/6/16.
//  Copyright © 2026 RongCloud. All rights reserved.
//

#import "RCBaseView.h"

@class RCMessageModel;

/// 聊天页面输入框上方引用区域 View 的基础类。
///
/// SDK 默认引用条 `RCReferencingView` 继承该类；开发者如需完全自定义输入框上方
/// 引用区域 UI，也应继承该类并通过 `RCConversationViewController` 的自定义方法返回。
///
/// 该类仅保存当前被引用消息模型并提供基础位置移动能力，不包含默认 UI、取消按钮或点击逻辑。
@interface RCReferenceInputBarView : RCBaseView

/// 当前输入框引用的消息模型。
@property (nonatomic, strong, readonly, nullable) RCMessageModel *messageModel;

/// 绑定当前输入框引用的消息模型。
///
/// 子类重写时建议先调用 super，以保证 `messageModel` 及时更新。
/// - Parameter messageModel: 当前输入框引用的消息模型。
- (void)setReferencedMessageModel:(nullable RCMessageModel *)messageModel;

/// 设置当前 View 的 Y 值。
/// - Parameter offsetY: 目标 Y 值。
- (void)setOffsetY:(CGFloat)offsetY;

@end
