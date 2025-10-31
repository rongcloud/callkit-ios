//
//  RCMenuItem.h
//  PopMenu
//
//  Created by RobinCui on 2025/10/18.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * RCMenuItem 继承自 UIMenuItem，扩展了图片属性
 * 用于表示一个菜单项的数据模型
 */
@interface RCMenuItem : UIMenuItem

/// 菜单项的图标
@property (nonatomic, strong, nullable) UIImage *image;

/**
 * 便利构造方法
 * @param title 菜单项标题
 * @param image 菜单项图标
 * @param action 点击菜单项时触发的方法
 */
- (instancetype)initWithTitle:(NSString *)title image:(nullable UIImage *)image action:(SEL)action;

+ (instancetype)menuItemWithItem:(UIMenuItem *)item;
@end

NS_ASSUME_NONNULL_END

