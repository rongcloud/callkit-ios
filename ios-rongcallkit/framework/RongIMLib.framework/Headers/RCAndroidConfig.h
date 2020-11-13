//
//  RCAndroidConfig.h
//  RongIMLib
//
//  Created by 孙浩 on 2020/9/17.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCAndroidConfig : NSObject

/*!
 Android 平台 Push 唯一标识
 目前支持小米、华为推送平台，默认开发者不需要进行设置，当消息产生推送时，消息的 messageUId 作为 notificationId 使用。
 */
@property (nonatomic, copy) NSString *notificationId;

/*!
 小米的渠道 ID
 该条消息针对小米使用的推送渠道，如开发者集成了小米推送，需要指定 channelId 时，可向 Android 端研发人员获取，channelId 由开发者自行创建。
 */
@property (nonatomic, copy) NSString *channelIdMi;

/*!
 华为的渠道 ID
 该条消息针对华为使用的推送渠道，如开发者集成了华为推送，需要指定 channelId 时，可向 Android 端研发人员获取，channelId 由开发者自行创建。
 */
@property (nonatomic, copy) NSString *channelIdHW;

/*!
 OPPO 的渠道 ID
 该条消息针对 OPPO 使用的推送渠道，如开发者集成了 OPPO 推送，需要指定 channelId 时，可向 Android 端研发人员获取，channelId 由开发者自行创建。
 */
@property (nonatomic, copy) NSString *channelIdOPPO;

/*!
 VIVO 推送通道类型
 开发者集成了 VIVO 推送，需要指定推送类型时，可进行设置。
 目前可选值 "0"(运营消息) 和  "1"(系统消息)
 */
@property (nonatomic, copy) NSString *typeVivo;

@end

NS_ASSUME_NONNULL_END
