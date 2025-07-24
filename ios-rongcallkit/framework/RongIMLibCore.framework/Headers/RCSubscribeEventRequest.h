//
//  RCSubscribeEventRequest.h
//  RongIMLibCore
//
//  Created by chinaspx on 2024/2/22.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCSubscribeEvent.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCSubscribeEventRequest : NSObject
/// 订阅类型
@property (nonatomic, assign) RCSubscribeType subscribeType;
/// 订阅有效时长，单位秒 [60s ~ 30 天]
/// 订阅接口请求时必传，其余接口不使用此字段
@property (nonatomic, assign) NSInteger expiry;
/// 订阅的用户列表
@property (nonatomic, strong) NSArray<NSString *> *userIds;
@end

NS_ASSUME_NONNULL_END
