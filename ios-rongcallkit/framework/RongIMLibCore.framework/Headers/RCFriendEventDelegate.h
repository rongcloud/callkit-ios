//
//  RCFriendEventDelegate.h
//  RongIMLibCore
//
//  Created by Lang on 2024/8/23.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCFriendEnum.h>

NS_ASSUME_NONNULL_BEGIN

@protocol RCFriendEventDelegate <NSObject>

@optional

/// 添加好友回调
/// - Parameter userId: 用户 ID
/// - Parameter name: 用户名
/// - Parameter portraitUri: 用户头像
/// - Parameter directionType: 好友方向类型
/// - Parameter operationTime: 操作时间
- (void)onFriendAdd:(NSString *)userId
               name:(NSString *)name
        portraitUri:(NSString *)portraitUri
      directionType:(RCDirectionType)directionType
      operationTime:(long long)operationTime;

/// 删除好友回调
/// - Parameter userIds: 用户列表
/// - Parameter directionType: 好友方向类型
/// - Parameter operationTime: 操作时间
- (void)onFriendDelete:(NSArray<NSString *> *)userIds
         directionType:(RCDirectionType)directionType
         operationTime:(long long)operationTime;

/// 好友申请状态变更回调
/// - Parameter userId: 用户 ID
/// - Parameter applicationType: 请求类型
/// - Parameter applicationStatus: 状态类型
/// - Parameter directionType: 好友方向类型
/// - Parameter operationTime: 操作时间
/// - Parameter extra: 备注内容
- (void)onFriendApplicationStatusChanged:(NSString *)userId
                         applicationType:(RCFriendApplicationType)applicationType
                       applicationStatus:(RCFriendApplicationStatus)applicationStatus
                           directionType:(RCDirectionType)directionType
                           operationTime:(long long)operationTime
                                   extra:(nullable NSString *)extra;

/// 清空好友的回调
/// 此操作只能由服务端发起
/// - Parameter operationTime: 操作时间
- (void)onFriendCleared:(long long)operationTime;

/// 好友信息变更多端回调事件
/// - Parameter userId: 用户 ID
/// - Parameter remark: 好友备注
/// - Parameter extProfile: 扩展信息
/// - Parameter operationTime: 操作时间
- (void)onFriendInfoChangedSync:(NSString *)userId
                         remark:(nullable NSString *)remark
                     extProfile:(nullable NSDictionary<NSString *, NSString *> *)extProfile
                  operationTime:(long long)operationTime;

@end

NS_ASSUME_NONNULL_END
