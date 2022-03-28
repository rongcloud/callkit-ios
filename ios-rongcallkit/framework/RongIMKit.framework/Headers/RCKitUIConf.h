//
//  RCKitUIConf.h
//  RongIMKit
//
//  Created by Sin on 2020/6/23.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RCThemeDefine.h"

@interface RCKitUIConf : NSObject
#pragma mark 头像显示

/*!
 SDK中全局的导航按钮字体颜色

 @discussion 默认值为[UIColor whiteColor]
 */
@property (nonatomic, strong) UIColor *globalNavigationBarTintColor;

/*!
 SDK会话列表界面中显示的头像形状，矩形或者圆形

 @discussion 默认值为矩形，即RC_USER_AVATAR_RECTANGLE
 */
@property (nonatomic, assign) RCUserAvatarStyle globalConversationAvatarStyle;

/*!
 SDK会话列表界面中显示的头像大小，高度必须大于或者等于36

 @discussion 默认值为46*46
 */
@property (nonatomic, assign) CGSize globalConversationPortraitSize;

/*!
 SDK会话页面中显示的头像形状，矩形或者圆形

 @discussion 默认值为矩形，即RC_USER_AVATAR_RECTANGLE
 */
@property (nonatomic, assign) RCUserAvatarStyle globalMessageAvatarStyle;

/*!
 SDK会话页面中显示的头像大小

 @discussion 默认值为40*40
 */
@property (nonatomic, assign) CGSize globalMessagePortraitSize;

/*!
 SDK会话列表界面和会话页面的头像的圆角曲率半径

 @discussion 默认值为4，只有当头像形状设置为矩形时才会生效。
 参考RCIM的globalConversationAvatarStyle和globalMessageAvatarStyle。
 */
@property (nonatomic, assign) CGFloat portraitImageViewCornerRadius;

/*!
是否支持暗黑模式，默认值是NO，开启之后 UI 支持暗黑模式，可以跟随系统切换
*/
@property (nonatomic, assign) BOOL enableDarkMode;
@end

