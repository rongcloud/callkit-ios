//
//  RCAndroidConfig.h
//  RongIMLib
//
//  Created by 孙浩 on 2020/9/17.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 华为推送消息级别
typedef NSString *RCImportanceHw NS_STRING_ENUM;

/// 华为推送消息级别 NORMAL
FOUNDATION_EXPORT RCImportanceHw const RCImportanceHwNormal;

/// 华为推送消息级别 LOW
FOUNDATION_EXPORT RCImportanceHw const RCImportanceHwLow;

/// 荣耀推送消息级别
typedef NSString *RCImportanceHonor NS_STRING_ENUM;

/// 荣耀推送消息级别 NORMAL
FOUNDATION_EXPORT RCImportanceHonor const RCImportanceHonorNormal;

/// 荣耀推送消息级别 LOW
FOUNDATION_EXPORT RCImportanceHonor const RCImportanceHonorLow;


@interface RCAndroidConfig : NSObject

/// Android 平台 Push 唯一标识
///
/// 目前支持小米、华为推送平台，默认开发者不需要进行设置，当消息产生推送时，消息的 messageUId 作为 notificationId 使用。
@property (nonatomic, copy) NSString *notificationId;

#pragma mark - 小米

/// 小米的渠道 ID
///
/// 该条消息针对小米使用的推送渠道，如开发者集成了小米推送，需要指定 channelId 时，可向 Android 端研发人员获取，channelId 由开发者自行创建。
@property (nonatomic, copy, nullable) NSString *channelIdMi;

/// 小米 Large icon 链接
///
/// Large icon 可以出现在大图版和多字版消息中，显示在右边。国内版仅 MIUI12 以上版本支持，以下版本均不支持；国际版支持。图片要求：大小 120 * 120px，格式为 png 或者 jpg 格式。
@property (nonatomic, copy, nullable)
    NSString *miLargeIconUrl __deprecated_msg("由于小米官方已停止支持该能力，该字段/方法已失效");
#pragma mark - 华为

/// 华为的渠道 ID
///
/// 该条消息针对华为使用的推送渠道，如开发者集成了华为推送，需要指定 channelId 时，可向 Android 端研发人员获取，channelId 由开发者自行创建。
@property (nonatomic, copy, nullable) NSString *channelIdHW;

////// 华为推送消息级别
@property (nonatomic, copy, nullable) RCImportanceHw importanceHW;

/// 华为通知栏消息右侧大图标 URL
///
/// 如果不设置，则不展示通知栏右侧图标，URL 使用的协议必须是 HTTPS 协议。
/// 图标文件须小于 512KB，图标建议规格大小：40dp x 40dp，弧角大小为 8dp，超出建议规格大小的图标会存在图片压缩或显示不全的情况。
@property (nonatomic, copy, nullable) NSString *hwImageUrl;

/// 华为推送消息分类：
/// - 社交通讯：即时通讯 [IM],音频、视频通话 [VOIP]
/// - 服务提醒：订阅 [SUBSCRIPTION],出行 [TRAVEL],健康 [HEALTH],工作事项提醒 [WORK],帐号动态 [ACCOUNT],订单&物流 [EXPRESS],财务 [FINANCE],系统提示 [SYSTEM_REMINDER],邮件 [MAIL]
/// - 资讯营销类：内容资讯/新闻/财经动态/生活资讯/社交动态/调研/其他 [MARKETING]
/// - 营销活动：产品促销/功能推荐/运营活动/MARKETING
///
/// 更多信息请参考华为消息分类标准文档：https://developer.huawei.com/consumer/cn/doc/development/HMSCore-Guides/message-classification-0000001149358835
///
/// 默认值为 null，如果为 null，则以服务配置为准
///
/// - Since: 5.4.0
@property (nonatomic, copy, nullable) NSString *categoryHW;

#pragma mark - Honor

/// 荣耀推送消息级别
@property (nonatomic, copy, nullable) RCImportanceHonor importanceHonor;

/// 荣耀通知栏消息右侧大图标 URL
@property (nonatomic, copy, nullable) NSString *imageUrlHonor;

#pragma mark - OPPO

/// OPPO 的渠道 ID
///
/// 该条消息针对 OPPO 使用的推送渠道，如开发者集成了 OPPO 推送，需要指定 channelId 时，可向 Android 端研发人员获取，channelId 由开发者自行创建。
@property (nonatomic, copy, nullable) NSString *channelIdOPPO;


#pragma mark - VIVO

/// VIVO 推送通道类型
/// 开发者集成了 VIVO 推送，需要指定推送类型时，可进行设置。
/// 目前可选值 "0"(运营消息) 和  "1"(系统消息)
@property (nonatomic, copy, nullable) NSString *typeVivo;

/// Vivo 推送消息分类
///
/// 系统消息分类
/// 即时消息 [IM],账号与资产 [ACCOUNT],日程待办 [TODO],设备信息 [DEVICE_REMINDER],订单与物流 [ORDER],订阅提醒 [SUBSCRIPTION]
/// 运营消息分类
/// 新闻 [NEWS],内容推荐 [CONTENT],运营活动 [MARKETING],社交动态 [SOCIAL]
/// 更多信息请参考 Vivo 消息分类标准文档：https://dev.vivo.com.cn/documentCenter/doc/359
///
/// 默认值为 null，如果为 null，则以服务配置为准
///
/// - Since: 5.4.2
@property (nonatomic, copy, nullable) NSString *categoryVivo;

#pragma mark - FCM

/// FCM 通知的频道 ID
///
/// 该应用程序必须使用此频道 ID 创建一个频道，然后才能收到带有该频道 ID 的任何通知。如果您未在请求中发送此频道 ID，或者如果应用尚未创建提供的频道 ID，则 FCM 使用应用清单中指定的频道 ID。
@property (nonatomic, copy, nullable) NSString *fcmChannelId;

/// FCM 通知类型推送时所使用的分组 id
@property (nonatomic, copy, nullable) NSString *fcmCollapseKey;

/// FCM 通知类型的推送所使用的通知图片 url
@property (nonatomic, copy, nullable) NSString *fcmImageUrl;

@end

NS_ASSUME_NONNULL_END
