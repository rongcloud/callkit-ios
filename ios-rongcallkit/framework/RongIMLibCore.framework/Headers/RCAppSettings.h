//
//  RCAppSettings.h
//  RongIMLibCore
//
//  Created by shuai shao on 2025/6/9.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCStatusDefine.h>

NS_ASSUME_NONNULL_BEGIN

/// 当前 AppKey 对应的配置。
///
/// - Since: 5.22.0
@interface RCAppSettings : NSObject

/// 语音转文字功能是否开启。
@property (nonatomic, readonly, assign) BOOL isSpeechToTextEnable;

/// 消息可编辑的有效时间，单位：分钟。
///
/// - Since: 5.26.0
@property (nonatomic, readonly, assign) NSInteger messageModifiableMinutes;

/// 已读回执版本
///
/// - Since: 5.30.0
@property (nonatomic, readonly, assign) RCMessageReadReceiptVersion readReceiptVersion;

/// 用户托管功能是否开启
///
/// - Since: 5.32.0
@property (nonatomic, readonly, assign) BOOL isUserProfileEnable;

/// 在线状态订阅功能是否开启
///
/// - Since: 5.32.0
@property (nonatomic, readonly, assign) BOOL isOnlineStatusSubscribeEnable;

//// 好友在线状态变更通知功能是否开启
///
/// - Since: 5.32.0
@property (nonatomic, readonly, assign) BOOL isFriendOnlineStatusSubscribeEnable;

@end

NS_ASSUME_NONNULL_END
