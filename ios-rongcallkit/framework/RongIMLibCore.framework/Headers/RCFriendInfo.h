//
//  RCFriendInfo.h
//  RongIMLibCore
//
//  Created by Lang on 2024/8/12.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCFriendEnum.h>

NS_ASSUME_NONNULL_BEGIN

/// 好友信息
@interface RCFriendInfo : NSObject

/// 用户 id
@property (nonatomic, copy) NSString *userId;

/// 用户名
@property (nonatomic, copy) NSString *name;

/// 用户头像
@property (nonatomic, copy) NSString *portraitUri;

/// 好友备注
@property (nonatomic, copy) NSString *remark;

/// 好友扩展信息
@property (nonatomic, copy) NSDictionary<NSString *, NSString *> *extProfile;

/// 好友添加时间
@property (nonatomic, assign) long long addTime;

/// 好友方向类型
@property (nonatomic, assign) RCDirectionType directionType;

@end

NS_ASSUME_NONNULL_END
