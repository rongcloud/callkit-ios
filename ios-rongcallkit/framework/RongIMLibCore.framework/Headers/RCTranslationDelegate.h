//
//  RCTranslationDelegate.h
//  RongIMLibCore
//
//  Created by shuai shao on 2025/6/30.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

@class RCConversationIdentifier;

enum RCTranslateStrategy : NSInteger;

NS_ASSUME_NONNULL_BEGIN

/// 语言翻译事件代理。
///
/// - Since: 5.24.0
@protocol RCTranslationDelegate <NSObject>

@optional

/// 用户级别翻译语言更新。
///
/// - Parameter language: 用户级别翻译语言。
- (void)translationLanguageDidChange:(NSString *)language;

/// 用户级别的自动翻译状态更新。
///
/// - Parameter isEnable: 是否开启自动翻译。
- (void)autoTranslateStateDidChange:(BOOL)isEnable;


/// 翻译完成回调
/// - Parameter items:翻译内容
- (void)translationDidFinished:(NSArray<RCTranslateItem *> *)items;

@end

NS_ASSUME_NONNULL_END
