//
//  RCRecallMessageOption.h
//  RongIMLibCore
//
//  Created by chinaspx on 2025/2/27.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// - Since: 5.16.0
@interface RCRecallMessageOption : NSObject

/// 是否删除本地消息，并移除远端消息记录，默认值 NO
@property (nonatomic, assign) BOOL isDelete;

/// 是否是管理员操作，默认值 NO
/// 用于融云 IMKit 展示需求，或业务其他需求，为透传字段，无实际管理作用
@property (nonatomic, assign) BOOL isAdmin;

/// 是否关闭远程推送和本地通知，默认值 NO
/// 设置为 YES 禁用该条消息的远程推送和本地通知
@property (nonatomic, assign) BOOL disableNotification;

@end

NS_ASSUME_NONNULL_END
