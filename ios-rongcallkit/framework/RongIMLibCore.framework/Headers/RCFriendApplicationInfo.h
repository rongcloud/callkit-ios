//
//  RCFriendApplicationInfo.h
//  RongIMLibCore
//
//  Created by Lang on 2024/8/12.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCFriendEnum.h>

NS_ASSUME_NONNULL_BEGIN

/// 好友申请信息
@interface RCFriendApplicationInfo : NSObject

/// 申请用户 ID
@property (nonatomic, copy) NSString *userId;

/// 申请用户名
@property (nonatomic, copy) NSString *name;

/// 申请用户头像
@property (nonatomic, copy) NSString *portraitUri;

/// 请求类型：发送的好友请求、接收的好友请求
@property (nonatomic, assign) RCFriendApplicationType applicationType;

/// 状态类型：申请添加好友、已同意、已拒绝、已过期
@property (nonatomic, assign) RCFriendApplicationStatus applicationStatus;

/// 操作时间
@property (nonatomic, assign) long long operationTime;

/// 备注内容
@property (nonatomic, copy) NSString *extra;

@end

NS_ASSUME_NONNULL_END
