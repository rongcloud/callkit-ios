//
//  RCPushProfile.h
//  RongIMLib
//
//  Created by 杜立召 on 16/12/26.
//  Copyright © 2016 年 RongCloud. All rights reserved.
//

#import <RongIMLibCore/RCStatusDefine.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCPushProfile : NSObject

/// 是否显示远程推送的内容
@property (nonatomic, assign, readonly) BOOL isShowPushContent;

/// 远程推送的语言
@property (nonatomic, assign, readonly) RCPushLanguage pushLanguage;

/// 其他端在线时，手机是否接收远程推送 (多个手机端登录，最后一个会接收)
@property (nonatomic, assign, readonly) BOOL receiveStatus;

/// 设置是否显示远程推送的内容
///
/// - Parameter isShowPushContent: 是否显示推送的具体内容（YES 显示 NO 不显示）
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
- (void)updateShowPushContentStatus:(BOOL)isShowPushContent
                            success:(nullable void (^)(void))successBlock
                              error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 设置推送内容的自然语言
///
/// - Parameter language: 通过 SDK 设置的语言环境，语言缩写内容格式为 (ISO-639 Language Code)_(ISO-3166 Country Codes)，如：zh_CN。目前融云支持的内置推送语言为 zh_CN、en_US、ar_SA
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
- (void)setPushLanguageCode:(NSString *)language
                    success:(nullable void (^)(void))successBlock
                      error:(nullable void (^)(RCErrorCode status))errorBlock;

/// 设置 Web 端在线时，手机端是否接收推送
///
/// - Parameter receiveStatus: 是否接收推送（YES 接收 NO 不接收）
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
- (void)setPushReceiveStatus:(BOOL)receiveStatus
                     success:(nullable void (^)(void))successBlock
                       error:(nullable void (^)(RCErrorCode status))errorBlock;

@end

@interface RCPushProfile (deprecated)

/// 远程推送的语言
@property (nonatomic, assign, readonly) RCPushLauguage pushLauguage __deprecated_msg("Use pushLanguage instead");

/// 设置推送内容的自然语言
///
/// - Parameter pushLanguage: 设置推送内容的自然语言
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
- (void)setPushLauguage:(RCPushLauguage)pushLauguage
                success:(nullable void (^)(void))successBlock
                  error:(nullable void (^)(RCErrorCode status))errorBlock
    __deprecated_msg("Use  setPushLanguageCode:success:error instead");


/// 设置推送内容的自然语言
///
/// - Parameter lauguage: 通过 SDK 设置的语言环境，语言缩写内容格式为 (ISO-639 Language Code)_(ISO-3166 Country Codes)，如：zh_CN。目前融云支持的内置推送语言为 zh_CN、en_US、ar_SA
/// - Parameter successBlock: 成功回调
/// - Parameter errorBlock: 失败回调
- (void)setPushLauguageCode:(NSString *)lauguage
                    success:(nullable void (^)(void))successBlock
                      error:(nullable void (^)(RCErrorCode status))errorBlock
    __deprecated_msg("Use  setPushLanguageCode:success:error instead");

@end

NS_ASSUME_NONNULL_END
