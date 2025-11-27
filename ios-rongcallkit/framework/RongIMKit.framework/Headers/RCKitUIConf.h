//
//  RCKitUIConf.h
//  RongIMKit
//
//  Created by Sin on 2020/6/23.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RCThemeDefine.h"
typedef NS_ENUM(NSInteger, RCKitInterfaceLayoutDirection) {
    RCKitInterfaceLayoutDirectionUnspecified,
    RCKitInterfaceLayoutDirectionLeftToRight,
    RCKitInterfaceLayoutDirectionRightToLeft,
};

@interface RCKitUIConf : NSObject
#pragma mark 头像显示

/// SDK中全局的导航按钮字体颜色
///
/// 默认值为[UIColor blackColor]
@property (nonatomic, strong) UIColor *globalNavigationBarTintColor;

/// SDK会话列表界面中显示的头像形状，矩形或者圆形
///
/// 默认值为矩形，即 `RC_USER_AVATAR_RECTANGLE`
@property (nonatomic, assign) RCUserAvatarStyle globalConversationAvatarStyle;

/// SDK会话列表界面中显示的头像大小，高度必须大于或者等于36
///
/// 默认值为 46*46
@property (nonatomic, assign) CGSize globalConversationPortraitSize;

/// SDK会话列表界面聚合会话的头像
///
/// 如果不设置此项会使用内置默认头像。
///
/// 字典 key value 说明：
/// - key:  聚合会话会话类型 `RCConversationType`
/// - value: 图片路径（支持本地路径或者远端url）
@property (nonatomic, strong) NSDictionary<NSNumber *, NSString *> *globalConversationCollectionAvatarDic;

/// SDK会话列表界面聚合会话的标题
///
/// 如果不设置此项会使用内置默认头像。
/// key: 聚合会话会话类型 RCConversationType
/// value: 聚合会话标题 NSString
@property (nonatomic, strong) NSDictionary<NSNumber *, NSString *> *globalConversationCollectionTitleDic;

/// SDK会话页面中显示的头像形状，矩形或者圆形
///
/// 默认值为矩形，即RC_USER_AVATAR_RECTANGLE
@property (nonatomic, assign) RCUserAvatarStyle globalMessageAvatarStyle;

/// SDK会话页面中显示的头像大小
///
/// 默认值为 40*40
@property (nonatomic, assign) CGSize globalMessagePortraitSize;

/// SDK会话列表界面和会话页面的头像的圆角曲率半径
///
/// 默认值为4，只有当头像形状设置为矩形时才会生效。
/// 参考RCIM的globalConversationAvatarStyle和globalMessageAvatarStyle。
@property (nonatomic, assign) CGFloat portraitImageViewCornerRadius;

/// 是否支持暗黑模式，默认值是NO，开启之后 UI 支持暗黑模式，可以跟随系统切换
/// 开启该属性后， 如果想控制 App 不随系统暗黑模式转变，请参考 https://support.rongcloud.cn/ks/MTE0Mg==
@property (nonatomic, assign) BOOL enableDarkMode;

/// SDK UI 布局方向
///
/// 默认值为 RCKitInterfaceLayoutDirectionUnspecified
@property (nonatomic, assign) RCKitInterfaceLayoutDirection layoutDirection;

/// 文件消息图标配置，key 是文件后缀（例如："png"、"pdf"），value 是本地文件路径
@property (nonatomic, copy, readonly) NSDictionary *fileSuffixDictionary;

/// 是否显示在线状态图标
///
/// 默认值为 NO 不显示在线状态图标
/// 开启之后，会在会话列表、会话页面、好友列表中显示在线状态图标
@property (nonatomic, assign) BOOL enableUserOnlineStatus;


/// 注册文件消息图标配置，根据文件后缀，自定义会话中文件消息展示的图标
/// - Parameter types: 文件图标字典，key 是文件后缀（例如："png"、"pdf"），value 是本地文件路径
/// 文件后缀不能带 “.”，支持的后缀可参考：https://support.rongcloud.cn/ks/NTE4
/// 如果文件路径为空或者路径下的文件不存在，会使用 RongCloud.bundle 中的默认图标。
/// 本地文件路径下的图片尺寸请参考 RongCloud.bundle 中对应的文件图标。
///
/// - Since: 5.3.4
- (BOOL)registerFileSuffixTypes:(NSDictionary<NSString *, NSString *> *)types;

@end

