//
//  RCGroupApplicationInfo.h
//  RongIMLibCore
//
//  Created by Lang on 2024/8/22.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCGroupEnum.h>
@class RCGroupMemberInfo;


NS_ASSUME_NONNULL_BEGIN

/// 群申请事件
@interface RCGroupApplicationInfo : NSObject

/// 群组 ID
@property (nonatomic, copy) NSString *groupId;

/// 入群者信息
@property (nonatomic, strong) RCGroupMemberInfo *joinMemberInfo;

/// 邀请者信息
@property (nonatomic, strong, nullable) RCGroupMemberInfo *inviterInfo;

/// 操作人信息
@property (nonatomic, strong, nullable) RCGroupMemberInfo *operatorInfo;

/// 群申请状态
@property (nonatomic, assign) RCGroupApplicationStatus status;

/// 群申请方向
@property (nonatomic, assign) RCGroupApplicationDirection direction;

/// 群申请类型
@property (nonatomic, assign) RCGroupApplicationType type;

/// 操作时间
@property (nonatomic, assign) long long operationTime;

/// 原因
@property (nonatomic, copy, nullable) NSString *reason;

@end

NS_ASSUME_NONNULL_END
