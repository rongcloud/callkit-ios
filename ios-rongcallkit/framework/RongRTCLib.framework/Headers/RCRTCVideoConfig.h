//
//  RCRTCVideoConfig.h
//  RongRTCLib
//
//  Created by RongCloud on 2020/2/13.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RCRTCVideoExtend.h"
#import "RCRTCVideoLayout.h"
NS_ASSUME_NONNULL_BEGIN

@interface RCRTCVideoConfig : NSObject

/*!
 视频大流配置
 */
@property (nonatomic, strong) RCRTCVideoLayout *videoLayout;

/*!
 视频小流配置
 */
@property (nonatomic, strong) RCRTCVideoLayout *tinyVideoLayout;

/*!
 视频扩展配置
 */
@property (nonatomic, strong) RCRTCVideoExtend *videoExtend;

/*!
 合流布局背景色
 */
@property (nonatomic, copy, readonly) NSString *backgroundColor;

/*!
 设置合流布局背景色
 
 @param red 取值范围: 0 ~ 255
 @param green 取值范围: 0 ~ 255
 @param blue 取值范围: 0 ~ 255
 @discussion
 此方法与 setBackgroundColor: 二选一使用, 效果相同
 如果两个方法都使用, 将以最后一次设置为准
 */
- (BOOL)setBackgroundColorWithRed:(NSUInteger)red green:(NSUInteger)green blue:(NSUInteger)blue;

/*!
 设置合流布局背景色
 
 @param backgroundColor 取值范围: 0x000000 ~ 0xffffff
 @discussion
 此方法与 setBackgroundColorWithRed:green:blue: 二选一使用, 效果相同
 如果两个方法都使用, 将以最后一次设置为准
 */
- (BOOL)setBackgroundColor:(NSUInteger)backgroundColor;

@end

NS_ASSUME_NONNULL_END
