//
//  RCTranslateParams.h
//  RongIMLibCore
//
//  Created by shuai shao on 2025/6/30.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

enum RCTranslateMode : NSInteger;

/// 消息翻译参数对象。
///
/// - Since: 5.24.0
@interface RCTranslateMessageParam : NSObject
/// 消息内容的语言，为空时，会自动识别。
@property (nonatomic, copy, nullable) NSString *sourceLanguage;

// 翻译的语言，为空时，使用配置的全局语言。
@property (nonatomic, copy, nullable) NSString *targetLanguage;
/// 消息 UId。
@property (nonatomic, copy) NSString *messageUId;
/// 内容唯一标识，业务用来做内容和翻译内容匹配
@property (nonatomic, copy, readonly) NSString *identifier;

@end

/// 批量翻译消息参数对象。
///
/// - Since: 5.24.0
@interface RCTranslateMessagesParams : NSObject

/// 翻译模式，默认为 `RCTranslateModeMechanical`。
@property (nonatomic, assign) enum RCTranslateMode mode;

/// 是否强制重新翻译，默认为 NO。
///
/// - Note: 翻译过的消息会做缓存，如果需要重新翻译，设置 YES。
@property (nonatomic, assign) BOOL force;

/// 待翻译消息信息数组，最多 10 条消息。
@property (nonatomic, copy) NSArray<RCTranslateMessageParam *> *list;

@end

/// 文本翻译参数对象。
///
/// - Since: 5.24.0
@interface RCTranslateTextParam : NSObject
/// 消息内容的语言，为空时，会自动识别。
@property (nonatomic, copy, nullable) NSString *sourceLanguage;

// 翻译的语言，为空时，使用配置的全局语言。
@property (nonatomic, copy, nullable) NSString *targetLanguage;
/// 源文本。
@property (nonatomic, copy) NSString *text;

/// 内容唯一标识，业务用来做内容和翻译内容匹配
@property (nonatomic, copy, readonly) NSString *identifier;

@end

/// 批量翻译文本参数对象。
///
/// - Since: 5.24.0
@interface RCTranslateTextsParams : NSObject

/// 翻译模式，默认为 `RCTranslateModeMechanical`。
@property (nonatomic, assign) enum RCTranslateMode mode;

/// 待翻译文本信息数组，最多 10 条。
@property (nonatomic, copy) NSArray<RCTranslateTextParam *> *list;

@end

NS_ASSUME_NONNULL_END
