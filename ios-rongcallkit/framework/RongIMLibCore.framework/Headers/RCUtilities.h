/**
 * Copyright (c) 2014-2015, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */

//  RCUtilities.h
//  Created by Heq.Shinoda on 14-5-15.

#ifndef __RCUtilities
#define __RCUtilities

#import "RCMessage.h"
#import <UIKit/UIKit.h>
@class CTTelephonyNetworkInfo;
/// 工具类
@interface RCUtilities : NSObject

/// 将 base64 编码的字符串解码并转换为 NSData 数据
///
/// - Parameter string: base64 编码的字符串
/// - Returns: 解码后的 NSData 数据
///
/// 此方法主要用于 iOS6 解码 base64。
+ (NSData *)dataWithBase64EncodedString:(NSString *)string;

/// 将 NSData 数据转化并编码为 base64 的字符串
///
/// - Parameter data: 未编码的 NSData 数据
/// - Returns: 编码后的 base64 字符串
///
/// 此方法主要用于 iOS6 编码 base64。
+ (NSString *)base64EncodedStringFrom:(NSData *)data;

/// scaleImage
///
/// - Parameter image: image
/// - Parameter scaleSize: scaleSize
///
/// - Returns: scaled image
+ (UIImage *)scaleImage:(UIImage *)image toScale:(float)scaleSize;

/// imageByScalingAndCropSize
///
/// - Parameter image: image
/// - Parameter targetSize: targetSize
///
/// - Returns: image
///
+ (UIImage *)imageByScalingAndCropSize:(UIImage *)image targetSize:(CGSize)targetSize;

///根据配置压缩图片
///
///如果设置了 `[RCCoreClient sharedCoreClient].imageCompressConfig` 就按照此设置进行压缩。如果没有设置，就按照 RCConfig.plis 文件中的配置进行压缩。
///
/// - Parameter image: 原图片
/// - Returns: 压缩后的图片
+ (UIImage *)generateThumbnailByConfig:(UIImage *)image;

/*!
 generate thumbnail from image

 - Parameter image: image
 - Parameter targetSize: targetSize

 - Returns: image
 */
+ (UIImage *)generateThumbnail:(UIImage *)image targetSize:(CGSize)targetSize;

/*!
 generate thumbnail from image

 - Parameter image: image
 - Parameter targetSize: targetSize
 - Parameter percent: percent

 - Returns: image
 */
+ (UIImage *)generateThumbnail:(UIImage *)image targetSize:(CGSize)targetSize percent:(CGFloat)percent;
/*!
 compressedImageWithMaxDataLength

 - Parameter image: image
 - Parameter maxDataLength: maxDataLength

 - Returns: NSData
 */
+ (NSData *)compressedImageWithMaxDataLength:(UIImage *)image maxDataLength:(CGFloat)maxDataLength;

/*!
 compressedImageAndScalingSize

 - Parameter image: image
 - Parameter targetSize: targetSize
 - Parameter maxDataLen: maxDataLen

 - Returns: image NSData
 */
+ (NSData *)compressedImageAndScalingSize:(UIImage *)image targetSize:(CGSize)targetSize maxDataLen:(CGFloat)maxDataLen;

/*!
 compressedImageAndScalingSize

 - Parameter image: image
 - Parameter targetSize: targetSize
 - Parameter percent: percent

 - Returns: image NSData
 */
+ (NSData *)compressedImageAndScalingSize:(UIImage *)image targetSize:(CGSize)targetSize percent:(CGFloat)percent;

/// compressedImage
///
/// - Parameter image: image
/// - Parameter percent: percent
///
/// - Returns: image NSData
+ (NSData *)compressedImage:(UIImage *)image percent:(CGFloat)percent;

/// 获取文字显示的尺寸
///
/// - Parameter text: 文字
/// - Parameter font: 字体
/// - Parameter constrainedSize: 文字显示的容器大小
///
/// - Returns: 文字显示的尺寸
///
/// 该方法在计算 iOS 7 以下系统显示的时候默认使用 NSLineBreakByTruncatingTail 模式。
+ (CGSize)getTextDrawingSize:(NSString *)text font:(UIFont *)font constrainedSize:(CGSize)constrainedSize;

/// 判断是否是本地路径
///
/// - Parameter path: 路径
///
/// - Returns: 是否是本地路径
///
+ (BOOL)isLocalPath:(NSString *)path;

/// 判断是否是网络地址
///
/// - Parameter url: 地址
///
/// - Returns: 是否是网络地址
+ (BOOL)isRemoteUrl:(NSString *)url;

/// 获取沙盒修正后的文件路径
///
/// - Parameter localPath: 本地路径
///
/// - Returns: 修正后的文件路径
+ (NSString *)getCorrectedFilePath:(NSString *)localPath;

/// 获取文件存储路径
+ (NSString *)getFileStoragePath;

/// excludeBackupKeyForURL
///
/// - Parameter storageURL: storageURL
///
/// - Returns: BOOL
+ (BOOL)excludeBackupKeyForURL:(NSURL *)storageURL;

/// 获取 App 的文件存放路径
///
/// - Returns: App 的文件存放路径
+ (NSString *)applicationDocumentsDirectory;

/*!
 获取融云 SDK 的文件存放路径

 - Returns: 融云 SDK 的文件存放路径
 */
+ (NSString *)rongDocumentsDirectory;

/// 获取融云 SDK 的缓存路径
///
/// - Returns: 融云 SDK 的缓存路径
+ (NSString *)rongImageCacheDirectory;

/// 获取当前系统时间
///
/// - Returns: 当前系统时间
+ (NSString *)currentSystemTime;

/// 获取当前运营商名称
///
/// - Returns: 当前运营商名称
+ (NSString *)currentCarrier;

+ (CTTelephonyNetworkInfo *)telephonyNetworkInfo;

///获取当前网络类型
///
/// - Returns: 当前网络类型
+ (NSString *)currentNetWork;

/// 获取当前网络类型
///
/// - Returns: 当前网络类型
+ (NSString *)currentNetworkType;

/// 获取系统版本
///
/// - Returns: 系统版本
+ (NSString *)currentSystemVersion;

/// 获取设备型号
///
/// - Returns: 设备型号
+ (NSString *)currentDeviceModel;

/// 获取非换行的字符串
///
/// - Parameter originalString: 原始的字符串
///
/// - Returns: 非换行的字符串
///
/// 所有换行符将被替换成单个空格
+ (NSString *)getNowrapString:(NSString *)originalString;


/// 判断一张照片是否是含透明像素的照片
///
/// - Parameter image: 原始照片
/// - Returns: 是否包含透明像素，YES 包含，NO 不包含
+ (BOOL)isOpaque:(UIImage *)image;

/// URL 编码
///
/// - Returns: 编码后的 URL
+ (NSString *)encodeURL:(NSString *)url;

+ (NSData *)compressImage:(UIImage *)sourceImage;

/// 检查字符串是否符合聊天室属性名称的格式
///
/// - Parameter key: 聊天室属性名称
/// - Returns: 是否符合聊天室属性名称的格式，YES 符合，NO 不符合
///
/// Key 支持大小写英文字母、数字、部分特殊符号 + = - _ 的组合方式
+ (BOOL)checkChatroomKey:(NSString *)key;

///生成 22 位的 UUID
///
///- Returns: 22 位的 UUID
+ (NSString *)get22bBitUUID;

///生成 UUID
///
///- Returns: UUID
+ (NSString *)getUUID;

///生成 DeviceId
///
///- Returns: DeviceId 连接改造使用的
+ (NSString *)getDeviceId:(NSString *)appKey;

/// 根据字符串生成 md5
/// - Parameter bateNum: MD5 位数
/// - Parameter isLowercaseStr: 是否生成小写字符串
/// - Returns: MD5
+ (NSString *)md5EncryptStr:(NSString *)str bateNum:(NSInteger)bateNum isLowercaseStr:(BOOL)isLowercaseStr;

///获取手机型号
///
///- Returns: 手机型号
+ (NSString *)iphoneType;

+ (void)setModuleName:(NSString *)moduleName version:(NSString *)version;

+ (NSDictionary *)getModuleVersionInfo;

/// 将字典或者数组转换成字符串，能去打印的换行 '\n' 以及空格
/// - Parameter objc: 必须是字典或者是数组
+ (NSString *)jsonFromObject:(id)objc;

@end

#endif
