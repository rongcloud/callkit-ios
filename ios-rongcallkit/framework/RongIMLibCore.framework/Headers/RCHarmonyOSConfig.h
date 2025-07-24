//
//  RCHarmonyOSConfig.h
//  RongIMLibCore
//
//  Created by RobinCui on 2024/7/4.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCHarmonyOSConfig : NSObject

/// HarmonyOS 通知栏消息右侧大图标 URL
///
///通知栏右侧图片，格式支持 png、jpg、jpeg、heif、gif、bmp，图片长*宽<25000 像素，图片不满足要求的情况下，终端不能显示通知消息。
@property (nonatomic, copy, nullable) NSString *imageUrl;

/// HarmonyOS 推送消息分类：
/// - 社交通讯：消息自分类标识，默认为空。category 取值必须为大写字母
/// 参考：https://developer.huawei.com/consumer/cn/doc/HMSCore-Guides/message-classification-0000001149358835

/// 默认值为 null，如果为 null，则以服务配置为准
///
@property (nonatomic, copy, nullable) NSString *category;
@end

NS_ASSUME_NONNULL_END
