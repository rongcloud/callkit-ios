//
//  RCRobotInfo.h
//  RongIMLibCore
//
//  Created by huan xu on 2025/9/3.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
///- Since 5.32.0
@interface RCRobotInfo : NSObject
/// 机器人 ID
@property (nonatomic, copy)NSString *robotId;
/// 机器人名称
@property (nonatomic, copy)NSString *name;
/// 机器人头像
@property (nonatomic, copy)NSString *portraitUri;
/// 机器人类型
@property (nonatomic, copy)NSString *robotType;
/// 机器人 metadata
@property (nonatomic, copy)NSDictionary *metadata;
/// 创建时间
@property (nonatomic, assign)long long createTime;
/// 最后一次更新时间
@property (nonatomic, assign)long long updateTime;

@end

NS_ASSUME_NONNULL_END
