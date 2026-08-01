//
//  RCMessageCellReferenceContentView.h
//  RongIMKit
//
//  Created by RongCloud on 2026/6/15.
//  Copyright © 2026 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RCMessageModel.h"
#import <RongIMLibCore/RongIMLibCore.h>

/// 消息 cell 内的自定义引用展示 View。
///
/// 当 Quote V2 被引用消息加载完成后，开发者可以继承该类，
/// 自定义消息列表中回复消息 cell 内的被引用消息展示区域。
///
/// 该 View 仅用于消息 cell 内的引用展示；聊天页面输入框上方的引用区域请通过
/// `RCConversationViewController` 的输入框引用区域自定义方法实现。
@interface RCMessageCellReferenceContentView : UIView

/// 当前引用展示区关联的消息模型。
/// 消息 cell 场景通常为当前回复消息模型。
@property (nonatomic, strong, readonly, nullable) RCMessageModel *messageModel;

/// 当前展示的被引用消息内容。
@property (nonatomic, strong, readonly, nullable) RCMessageContent *referencedContent;

/// 返回消息 cell 内自定义引用展示内容 View 的尺寸。
/// - Parameters:
///   - referencedContent: 被引用消息内容。
///   - messageModel: 当前引用展示区关联的消息模型，通常为当前回复消息模型。
///   - maxWidth: 可展示的最大宽度，返回的宽度不应超过该值。
+ (CGSize)sizeForReferencedContent:(RCMessageContent *)referencedContent
                       messageModel:(RCMessageModel *)messageModel
                           maxWidth:(CGFloat)maxWidth;

/// 绑定消息 cell 内的自定义引用展示内容。
///
/// 如果子类重写该方法，建议先调用 super，以保证 `messageModel` 和
/// `referencedContent` 上下文属性及时更新。
/// - Parameters:
///   - referencedContent: 被引用消息内容。
///   - messageModel: 当前引用展示区关联的消息模型，通常为当前回复消息模型。
- (void)setReferencedContent:(RCMessageContent *)referencedContent
                messageModel:(RCMessageModel *)messageModel;

/// 触发消息 cell 内引用内容的自定义事件。
///
/// SDK 会将事件转发到 `RCConversationViewController`
/// 的 `messageCellReferenceContentView:didPerformAction:extra:` 方法。
/// - Parameters:
///   - action: 业务自定义事件标识。
///   - extra: 业务自定义事件参数。
- (void)performAction:(NSString *)action
                extra:(nullable NSDictionary *)extra;

@end
