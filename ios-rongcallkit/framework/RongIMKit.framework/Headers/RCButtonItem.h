//
//  RCButtonItemModel.h
//  RongIMKit
//
//  Created by zgh on 2024/8/22.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN

/// 按钮 item
/// - Since: 5.12.0
@interface RCButtonItem : NSObject

/// 按钮名称
@property (nonatomic, copy, nullable) NSString *title;

/// 按钮名称颜色
@property (nonatomic, strong, nullable) UIColor *titleColor;

/// 按钮背景色
@property (nonatomic, strong, nullable) UIColor *backgroundColor;

/// 按钮边框颜色
@property (nonatomic, strong, nullable) UIColor *borderColor;

/// 按钮点击回调
@property (nonatomic, copy) void (^clickBlock)(void);

/// 实例化 RCButtonItem
///
/// - Parameters title: 按钮名称
/// - Parameters titleColor: 按钮名称颜色
/// - Parameters backgroundColor: 按钮背景色
+ (instancetype)itemWithTitle:(NSString *)title
                   titleColor:(nullable UIColor *)titleColor
              backgroundColor:(nullable UIColor *)backgroundColor;

@end

NS_ASSUME_NONNULL_END
