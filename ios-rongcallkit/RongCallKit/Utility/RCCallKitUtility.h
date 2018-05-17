//
//  RCCallKitUtility.h
//  RongCallKit
//
//  Created by 岑裕 on 16/3/12.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongCallLib/RongCallLib.h>
#import <RongIMKit/RongIMKit.h>
#import <UIKit/UIKit.h>

#define RongVoIPUIColorFromRGB(rgbValue)                                                                               \
    [UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16)) / 255.0                                               \
                    green:((float)((rgbValue & 0x00FF00) >> 8)) / 255.0                                                \
                     blue:((float)((rgbValue & 0x0000FF) >> 0)) / 255.0                                                \
                    alpha:1.0]

#define RC_IOS_SYSTEM_VERSION_LESS_THAN(v)                                                                             \
    ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedAscending)

#define RCCallHeaderLength 80.0f
#define RCCallButtonLength 64.0f
#define RCCallLabelHeight 25.0f
#define RCCallVerticalMargin 32.0f
#define RCCallHorizontalMargin 25.0f
#define RCCallInsideMargin 5.0f

#define RCCallTopGGradientHeight 100
#define RCCallBottomGradientHeight (([UIScreen mainScreen].bounds.size.height == 812) ? 242.0f : 208.0f)
//  判断是否为iphoneX，是iphoneX，底部按钮整体上移34
#define RCCallExtraSpace (([UIScreen mainScreen].bounds.size.height == 812) ? 34.0f : 0.0f)
// iphoneX顶部额外加上statusbar的30（实际刘海的高度）
#define RCCallStatusBarHeight (([UIScreen mainScreen].bounds.size.height == 812) ? 30.0f : 0.0f)
@interface RCCallKitUtility : NSObject

+ (NSString *)getReadableStringForTime:(long)sec;

+ (UIImage *)getScaleImage:(UIImage *)image size:(CGSize)size;

+ (UIColor *)getScaleImageColor:(UIImage *)image size:(CGSize)size;

+ (UIImage *)imageFromVoIPBundle:(NSString *)imageName;

+ (UIImage *)getDefaultPortraitImage;

+ (NSString *)getReadableStringForMessageCell:(RCCallDisconnectReason)hangupReason;

+ (NSString *)getReadableStringForCallViewController:(RCCallDisconnectReason)hangupReason;

+ (BOOL)isLandscape;

+ (void)setScreenForceOn;
+ (void)clearScreenForceOnStatus;

@end
