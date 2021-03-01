//
//  RCKitCommonDefine.h
//
//  Created by 岑裕 on 2016/10/12.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCKitUtility.h"

#ifndef RCKitCommonDefine_h
#define RCKitCommonDefine_h

#define RCLocalizedString(key) NSLocalizedStringFromTable(key, @"RongCloudKit", nil)
#define RCResourceImage(value) [RCKitUtility imageNamed:(value) ofBundle:@"RongCloud.bundle"]
#define RCResourceColor(key, colorStr) [RCKitUtility color:(key) originalColor:(colorStr)]

#pragma mark - Screen Size
#define SCREEN_HEIGHT [[UIScreen mainScreen] bounds].size.height
#define SCREEN_WIDTH [[UIScreen mainScreen] bounds].size.width
#define SCREEN_SCALE ([UIScreen mainScreen].scale)

#pragma mark - Dispatch Main Async
#ifndef dispatch_main_async_safe
#define dispatch_main_async_safe(block)                                                                                \
    if ([NSThread isMainThread]) {                                                                                     \
        block();                                                                                                       \
    } else {                                                                                                           \
        dispatch_async(dispatch_get_main_queue(), block);                                                              \
    }
#endif

#pragma mark - Color

#define RGBCOLOR(r, g, b) [UIColor colorWithRed:(r) / 255.0f green:(g) / 255.0f blue:(b) / 255.0f alpha:1]

#define HEXCOLOR(rgbValue)                                                                                             \
[UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16)) / 255.0                                               \
                green:((float)((rgbValue & 0xFF00) >> 8)) / 255.0                                                  \
                 blue:((float)(rgbValue & 0xFF)) / 255.0                                                           \
                alpha:1.0]

#define RCMASKCOLOR(rgbValue,alphaValue)                                                                                             \
[UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16)) / 255.0                                               \
                green:((float)((rgbValue & 0xFF00) >> 8)) / 255.0                                                  \
                 blue:((float)(rgbValue & 0xFF)) / 255.0                                                           \
                alpha:alphaValue]

#define RCDYCOLOR(lrgbValue, drgbValue)                                                                                \
    [RCKitUtility generateDynamicColor:HEXCOLOR(lrgbValue) darkColor:HEXCOLOR(drgbValue)]

#pragma mark - System Version

#define RC_IOS_SYSTEM_VERSION_GREATER_THAN(v)                                                                          \
    ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedDescending)
#define RC_IOS_SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(v)                                                              \
    ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)
#define RC_IOS_SYSTEM_VERSION_LESS_THAN(v)                                                                             \
    ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedAscending)

#pragma mark - device
#define ISX [RCKitUtility getWindowSafeAreaInsets].top >= 10

#endif /* RCKitCommonDefine_h */
