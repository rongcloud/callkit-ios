//
//  RCIMKitThemeManager.h
//  RongIMKit
//
//  Created by RobinCui on 2025/9/17.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RCIMKitTheme.h"
NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, RCIMKitInnerThemesType) {
    RCIMKitInnerThemesTypeTradition, // 传统主题
    RCIMKitInnerThemesTypeLively // 欢快主题
};

@protocol RCIMKitThemeDelegate <NSObject>

/// 主题变更通知
/// - Parameters:
///   - customTheme: 变更后的的自定义主题(未设置自定义主题时为 nil)
///   - type: 变更后的内置主题类型
- (void) themeDidChanged:(RCIMKitTheme *)customTheme
        baseOnTheme:(RCIMKitInnerThemesType)type;

@end

@interface RCIMKitThemeManager : NSObject

/// 添加主题变更代理
/// - Parameter delegate: 代理
+ (void)addThemeDelegate:(id<RCIMKitThemeDelegate>)delegate;

/// 移除主题变更代理
/// - Parameter delegate: 代理
+ (void)removeThemeDelegate:(id<RCIMKitThemeDelegate>)delegate;

/// 当前内置主题
+ (RCIMKitInnerThemesType)currentInnerThemesType;

/// 修改内置主题
/// - Parameter type: 主体类别
+ (BOOL)changeInnerTheme:(RCIMKitInnerThemesType)type;

/// 修改自定义主题
/// - Parameters:
///   - theme: 自定义主题
///   - innerThemesType: 该主题依赖的内置主题类别
+ (BOOL)changeCustomTheme:(nullable RCIMKitTheme *)theme
              baseOnTheme:(RCIMKitInnerThemesType)innerThemesType;

/// 获取颜色
/// - Parameters:
///   - colorKey: 欢快主题颜色 key 值
///   - lightHex: 传统主题浅色模式 colorHex
///   - darkHex:  传统主题深色模式 colorHex
+ (UIColor *)dynamicColor:(nullable NSString *)colorKey
               lightColor:(nullable NSString *)lightHex
                darkColor:(nullable NSString *)darkHex;

/// 获取图片
/// - Parameters:
///   - imageKey: 欢快主题图片 key 值
///   - defaultImageName: 传统主题浅色模式图片名称
+ (UIImage *)dynamicImage:(nullable NSString *)imageKey
         defaultImageName:(nullable NSString *)defaultImageName;

/// 获取颜色
/// - Parameters:
///   - colorKey: 欢快主题颜色 key 值
///   - resourceKey: RCColor.plist 的key 字符串
///   - originalColor:  颜色 colorHex
+ (UIColor *)dynamicColor:(nullable NSString *)colorKey
              resourceKey:(nullable NSString *)resourceKey
            originalColor:(nullable NSString *)colorHex;
@end

NS_ASSUME_NONNULL_END
