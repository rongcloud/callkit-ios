//
//  RCGetGroupMembersOption.h
//  RongIMLibCore
//
//  Created by huan xu on 2025/9/3.
//  Copyright © 2025 RongCloud. All rights reserved.
//
/// - Since 5.28.0
#import <RongIMLibCore/RongIMLibCore.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, RCFilterRobotType) {
    /// 获取所有成员
    RCFilterRobotTypeAll = 0,
    /// 不包含机器人的用户列表
    RCFilterRobotTypeExclueRobot = 1,
    /// 只包含机器人的列表
    RCFilterRobotTypeRobotOnly = 2,
};

@interface RCGetGroupMembersOption : RCPagingQueryOption

@property (nonatomic, assign)RCFilterRobotType filterRobotType;

@end

NS_ASSUME_NONNULL_END
