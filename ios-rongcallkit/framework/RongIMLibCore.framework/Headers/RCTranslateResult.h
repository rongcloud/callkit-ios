//
//  RCTranslateResult.h
//  RongIMLibCore
//
//  Created by shuai shao on 2025/6/30.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RCErrorCode.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, RCTranslateStatus) {
    RCTranslateStatusNone,
    RCTranslateStatusTranslating,
    RCTranslateStatusSuccess,
    RCTranslateStatusFailed
};

typedef NS_ENUM(NSInteger, RCTranslateResultType) {
    RCTranslateResultTypeMessage,    // 消息
    RCTranslateResultTypeCustomText  // 自定义
};

/// 翻译结果。
///
/// - Since: 5.24.0
@interface RCTranslateInfo : NSObject

/// 翻译后的内容。
@property (nonatomic, copy) NSString *translatedText;

/// 状态
@property (nonatomic, assign) RCTranslateStatus status;

// 翻译目标的语言。
@property (nonatomic, copy) NSString *targetLanguage;

@end

/// 消息翻译结果。
///
/// - Since: 5.24.0
@interface RCTranslateItem : NSObject

/// 翻译内容标识：消息的 UId 或内容的 hash。
@property (nonatomic, copy) NSString *identifier;

/// 翻译信息
@property (nonatomic, strong) RCTranslateInfo *translateInfo;

/// 状态码
@property (nonatomic, assign) RCErrorCode code;

/// 翻译来源
@property (nonatomic, assign) RCTranslateResultType from;
@end

NS_ASSUME_NONNULL_END
