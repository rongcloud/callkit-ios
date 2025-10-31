//
//  RCIMKitTheme.h
//  RongIMKit
//
//  Created by RobinCui on 2025/9/17.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/// 自定义主题类
/// 用于加载和管理自定义主题资源,包括颜色和图片配置
@interface RCIMKitTheme : NSObject

#pragma mark - Properties

/// 主题名称
@property (nonatomic, copy) NSString *name;

/// 颜色字典
/// Key: 颜色标识符, Value: 十六进制颜色值(格式: #RRGGBB 或 #RRGGBBAA)
@property (nonatomic, readonly, copy) NSDictionary<NSString *, NSString *> *colors;

/// 图片字典
/// Key: 图片标识符, Value: 图片文件名(相对于 resourcePath)
@property (nonatomic, readonly, copy) NSDictionary<NSString *, NSString *> *images;

/// 资源路径
/// 主题资源文件夹的绝对路径,包含图片等资源文件
@property (nonatomic, readonly, copy) NSString *resourcePath;

/// 主题配置文件路径
/// plist 文件的绝对路径,包含主题的完整配置信息
/// 配置文件格式:
/// @code
/// {
///     "name": "主题名称",
///     "colors": {
///         "color_key": "#RRGGBB"
///     },
///     "images": {
///         "image_key": "image_filename.png"
///     }
/// }
/// @endcode
@property (nonatomic, readonly, copy) NSString *plistPath;

#pragma mark - Initialization

/// 使用主题路径初始化主题对象
/// @param path 主题文件夹路径,该文件夹应包含:
///             - theme.plist: 主题配置文件
///             - resources/: 资源文件夹(包含图片等资源)
/// @return 主题对象实例,如果路径无效或配置文件格式错误则返回配置不完整的实例
- (instancetype)initWithThemePath:(NSString *)path;

#pragma mark - Public Methods

/// 获取动态颜色
/// 优先从主题配置中获取颜色,如果主题中未配置则使用默认颜色
/// @param colorKey 颜色标识符,用于在主题配置中查找对应的颜色值
/// @param hex 默认颜色值(十六进制格式,如: #RRGGBB 或 0xRRGGBB)
/// @return 颜色对象,如果参数无效则返回 nil
- (UIColor * _Nullable)dynamicColor:(NSString *)colorKey
                       defaultColor:(NSString *)hex;

/// 获取动态图片
/// 优先从主题配置中获取图片,如果主题中未配置则使用默认图片
/// @param imageKey 图片标识符,用于在主题配置中查找对应的图片文件名
/// @param defaultImage 默认图片,当主题中未配置或加载失败时使用
/// @return 图片对象,如果主题中未配置则返回默认图片
- (UIImage * _Nullable)dynamicImage:(NSString *)imageKey
                       defaultImage:(UIImage * _Nullable)defaultImage;

@end

NS_ASSUME_NONNULL_END
