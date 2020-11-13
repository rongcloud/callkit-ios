//
//  RCMessagePushConfig.h
//  RongIMLib
//
//  Created by 孙浩 on 2020/9/15.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RCiOSConfig.h"
#import "RCAndroidConfig.h"

NS_ASSUME_NONNULL_BEGIN

@interface RCMessagePushConfig : NSObject

/*!
 推送标题
 如果没有设置，会使用下面的默认标题显示规则
 默认标题显示规则：
    内置消息：单聊通知标题显示为发送者名称，群聊通知标题显示为群名称。
    自定义消息：默认不显示标题。
 */
@property (nonatomic, copy) NSString *pushTitle;

/*!
 推送内容
 优先使用 MessagePushConfig 的 pushContent，如果没有，则使用 sendMessage 或者 sendMediaMessage 的 pushContent。
 */
@property (nonatomic, copy) NSString *pushContent;

/*!
 远程推送附加信息
 优先使用 MessagePushConfig 的 pushData，如果没有，则使用 sendMessage 或者 sendMediaMessage 的 pushData。
 */
@property (nonatomic, copy) NSString *pushData;

/*!
 是否强制显示通知详情
 当目标用户通过 RCPushProfile 中的 - (void)updateShowPushContentStatus:(BOOL)isShowPushContent success:(void (^)(void))successBlock error:(void (^)(RCErrorCode status))errorBlock; 设置推送不显示消息详情时，可通过此参数，强制设置该条消息显示推送详情。
 */
@property (nonatomic, assign) BOOL forceShowDetailContent;

/*!
 iOS 平台相关配置
 */
@property (nonatomic, strong) RCiOSConfig *iOSConfig;

/*!
 Android 平台相关配置
 */
@property (nonatomic, strong) RCAndroidConfig *androidConfig;

/*!
 将数组转成 messagePushConfig 的 iOSConfig 和 AndroidConfig
 */
- (instancetype)arrayToConfig:(NSArray *)array;

/*!
 将 iOSConfig 和  AndroidConfig 转成数组
 */
- (NSArray *)encodeIOSAndAndroidConfig;

@end

NS_ASSUME_NONNULL_END
