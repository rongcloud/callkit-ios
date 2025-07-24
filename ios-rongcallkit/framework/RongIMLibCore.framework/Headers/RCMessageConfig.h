//
//  RCMessageConfig.h
//  RongIMLib
//
//  Created by 孙浩 on 2020/6/29.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCMessageConfig : NSObject

/// 是否关闭远程推送和本地通知，默认值 NO
/// 设置为 YES 禁用该条消息的远程推送和本地通知
@property (nonatomic, assign) BOOL disableNotification;

@end

NS_ASSUME_NONNULL_END
