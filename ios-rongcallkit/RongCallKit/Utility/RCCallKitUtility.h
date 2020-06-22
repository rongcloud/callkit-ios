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

UIColor* rgb(CGFloat red, CGFloat green, CGFloat blue);
UIColor* rgba(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha);
UIColor* hex_rgb(NSInteger hex_value);
UIColor* dynamic_color(NSInteger light_hex_value, NSInteger dark_hex_value);

#define RongVoIPUIColorFromRGB(rgbValue)                                                                               \
    [UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16)) / 255.0                                               \
                    green:((float)((rgbValue & 0x00FF00) >> 8)) / 255.0                                                \
                     blue:((float)((rgbValue & 0x0000FF) >> 0)) / 255.0                                                \
                    alpha:1.0]

#define RC_IOS_SYSTEM_VERSION_LESS_THAN(v)                                                                             \
    ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedAscending)

#define RCCallHeaderLength 90.0f
#define RCCallButtonLength 65.0f
#define RCCallMiniButtonLength 28.0f
#define RCCallMiniButtonTopMargin 29.0f
#define RCCallCustomButtonLength 60.0f
#define RCCallLabelHeight 25.0f
#define RCCallNameLabelWidth 148.0f
#define RCCallMiniLabelHeight 18.0f
#define RCCallTimeLabelHeight 14.0f
#define RCCallVerticalMargin 32.0f
#define RCCallHorizontalMargin 15.f
#define RCCallHorizontalMiddleMargin 44.5f
#define RCCallHorizontalBigMargin 72.5f
#define RCCallInsideMargin 7.75f
#define RCCallTimeTopMargin 12.0f
#define RCCallInsideMiniMargin 6.5f
#define RCCallTopMargin 15.0f
#define RCCallTipsLabelTopMargin 56.5f
#define RCCallButtonInsideMargin 4.0f
#define RCCallButtonHorizontalMargin 44.5f
#define RCCallButtonBottomMargin 29.5f
#define RCCallCollectionCellWidth 55.0f

#define RCCallTopGGradientHeight 100
#define BOTTOMSAFEAREA (([RCCallKitUtility compareVersion:[UIDevice currentDevice].systemVersion toVersion:@"11.0"] >= 0) ? [UIApplication sharedApplication].keyWindow.safeAreaInsets.bottom : UIEdgeInsetsZero.bottom)
#define RCCallBottomGradientHeight (BOTTOMSAFEAREA > 0 ? 242.0f : 208.0f)
//  判断是否为iphoneX，是iphoneX，底部按钮整体上移34
#define RCCallExtraSpace BOTTOMSAFEAREA
// iphoneX顶部额外加上statusbar的30（实际刘海的高度）
#define RCCallStatusBarHeight (BOTTOMSAFEAREA > 0 ? 30.0f : 0.0f)
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
+ (void)checkSystemPermission:(RCCallMediaType)mediaType success:(void (^)(void))successBlock error:(void (^)(void))errorBlock;
+ (NSInteger)compareVersion:(NSString *)version1 toVersion:(NSString *)version2;

@end
