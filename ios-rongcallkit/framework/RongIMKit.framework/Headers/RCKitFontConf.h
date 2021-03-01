//
//  RCKitFontConf.h
//  RongIMKit
//
//  Created by Sin on 2020/6/23.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
// IMKit 字体配置
///IMKit 内部禁用 UIFont 构建字体，只通过该类构建字体，方便统一管理
@interface RCKitFontConf : NSObject
/// 一级标题，默认 fontSize 为 18
@property (nonatomic, assign) CGFloat firstLevel;
/// 二级标题，默认 fontSize 为 17 (文本消息，引用消息内容，会话列表 title)
@property (nonatomic, assign) CGFloat secondLevel;
/// 三级标题，默认 fontSize 为 15
@property (nonatomic, assign) CGFloat thirdLevel;
/// 四级标题，默认 fontSize 为 14 (富文本消息的标题，小灰条消息，引用消息引用内容)
@property (nonatomic, assign) CGFloat fourthLevel;
/// 引导文字，默认 fontSize 为 13
@property (nonatomic, assign) CGFloat guideLevel;
/// 少数注释文字，默认 fontSize 为 12 (富文本消息的内容)
@property (nonatomic, assign) CGFloat annotationLevel;
/// 极少数辅助说明，默认 fontSize 为 10 (gif 消息大小)
@property (nonatomic, assign) CGFloat assistantLevel;

/// firstLevel 的 font，默认 fontSize 为 18
- (UIFont *)fontOfFirstLevel;

/// secondLevel 的 font，默认 fontSize 为 17
- (UIFont *)fontOfSecondLevel;

/// thirdLevel 的 font，默认 fontSize 为 15
- (UIFont *)fontOfThirdLevel;

/// fourthLevel 的 font，默认 fontSize 为 14
- (UIFont *)fontOfFourthLevel;

/// guideLevel 的 font，默认 fontSize 为 13
- (UIFont *)fontOfGuideLevel;

/// annotationLevel 的 font，默认 fontSize 为 12
- (UIFont *)fontOfAnnotationLevel;

/// assistantLevel 的 font，默认 fontSize 为 10
- (UIFont *)fontOfAssistantLevel;

/// 自定义字体大小
/// @param size 字体大小
- (UIFont *)fontOfSize:(CGFloat)size;
@end
