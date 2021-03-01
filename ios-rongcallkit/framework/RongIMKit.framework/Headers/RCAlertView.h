//
//  RCAlertView.h
//  RongIMKit
//
//  Created by 张改红 on 2020/5/25.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface RCAlertView : UIView

/*!
 显示 AlertController
 
 @param title title
 @param message  message
 @param cancelTitle 取消 title
 
 @discussion 默认显示在 keyWindow rootViewController 上
 */
+ (void)showAlertController:(NSString *)title
                    message:(NSString *)message
                cancelTitle:(NSString *)cancelTitle;

/*!
 显示 AlertController
 
 @param title title
 @param message  message
 @param cancelTitle 取消 title
 @param controller AlertController 展示的父类控制器，如果 controller 为 nil，则显示在 keyWindow rootViewController 上
 */
+ (void)showAlertController:(NSString *)title
                    message:(NSString *)message
                cancelTitle:(NSString *)cancelTitle
           inViewController:(UIViewController *)controller;

/*!
 显示 AlertController（可设置自动消失时间）
 
 @param title title
 @param message  message
 @param timeInterval 消失时间
 
 @discussion 默认显示在 keyWindow rootViewController 上
 */
+ (void)showAlertController:(NSString *)title
                    message:(NSString *)message
           hiddenAfterDelay:(NSTimeInterval)timeInterval;

/*!
 显示 AlertController（可设置自动消失时间）
 
 @param title title
 @param message  message
 @param timeInterval 消失时间
 @param controller AlertController 展示的父类控制器，如果 controller 为 nil，则显示在 keyWindow rootViewController 上
 */
+ (void)showAlertController:(NSString *)title
                    message:(NSString *)message
           hiddenAfterDelay:(NSTimeInterval)timeInterval
           inViewController:(UIViewController *)controller;

/*!
 显示 AlertController（可设置自动消失时间）
 
 @param title title
 @param message  message
 @param timeInterval 消失时间
 @param controller AlertController 展示的父类控制器，如果 controller 为 nil，则显示在 keyWindow rootViewController 上
 @param completion  AlertController 消失回调
 */
+ (void)showAlertController:(NSString *)title
                    message:(NSString *)message
           hiddenAfterDelay:(NSTimeInterval)timeInterval
           inViewController:(UIViewController *)controller
          dismissCompletion: (void (^)(void))completion;

/*!
 显示 AlertController
 
 @param actionTitles 操作事件 title 列表
 @param cancelTitle 取消 title
 @param style    ActionSheet or Alert
 @param actionsBlock 操作事件回调，回调参数 index 、alertAction 与 actionTitles 顺序一致
 @param controller AlertController 展示的父类控制器，如果 controller 为 nil，则显示在 keyWindow rootViewController 上
 */
+ (void)showAlertController:(NSArray *)actionTitles
                cancelTitle:(NSString *)cancelTitle
             preferredStyle:(UIAlertControllerStyle)style
               actionsBlock:(void (^)(int index, UIAlertAction *alertAction))actionsBlock
           inViewController:(UIViewController *)controller;

/*!
 显示 AlertController
 
 @param title title
 @param message  message
 @param actionTitles 操作事件 title 列表
 @param cancelTitle 取消 title
 @param confirmTitle 确认 title
 @param style    ActionSheet or Alert
 @param actionsBlock 操作事件回调，回调参数 index 、alertAction 与 actionTitles 顺序一致
 @param cancelBlock 取消按钮点击回调
 @param confirmBlock  确认按钮点击回调
 @param controller AlertController 展示的父类控制器，如果 controller 为 nil，则显示在 keyWindow rootViewController 上
 */
+ (void)showAlertController:(NSString *)title
                    message:(NSString *)message
               actionTitles:(NSArray *)actionTitles
                cancelTitle:(NSString *)cancelTitle
               confirmTitle:(NSString *)confirmTitle
             preferredStyle:(UIAlertControllerStyle)style
               actionsBlock:(void (^)(int index, UIAlertAction *alertAction))actionsBlock
                cancelBlock:(void (^)(void))cancelBlock
               confirmBlock:(void (^)(void))confirmBlock
           inViewController:(UIViewController *)controller;
@end
