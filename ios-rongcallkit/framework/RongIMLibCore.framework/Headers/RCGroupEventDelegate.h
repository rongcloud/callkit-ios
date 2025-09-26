//
//  RCGroupEventDelegate.h
//  RongIMLibCore
//
//  Created by Lang on 2024/7/22.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <RongIMLibCore/RCGroupEnum.h>
#import <RongIMLibCore/RCGroupInfo.h>
@class RCGroupMemberInfo;
@class RCGroupApplicationInfo;


NS_ASSUME_NONNULL_BEGIN

@protocol RCGroupEventDelegate <NSObject>

@optional

/// 群组操作回调
/// - Parameter groupId: 群组 ID
/// - Parameter operatorInfo: 操作者信息。服务端 api 操作踢出时为空。
/// - Parameter groupInfo: 群组信息，仅在操作类型为创建群组时有效。
/// - Parameter operation: 操作类型
/// - Parameter memberInfos: 目标用户信息列表
/// - Parameter operationTime: 操作时间
/// - Warning 在该回调中，`groupInfo` 的 `remark`、`role`、`joinedTime` 字段不会返回有效值，它们可能为空或为默认值。
/// 如需获取这些字段，请通过` -[RCCoreClient getGroupsInfo:success:error:]` 接口查询。
- (void)onGroupOperation:(NSString *)groupId
            operatorInfo:(nullable RCGroupMemberInfo *)operatorInfo
               groupInfo:(nullable RCGroupInfo *)groupInfo
               operation:(RCGroupOperation)operation
             memberInfos:(NSArray<RCGroupMemberInfo *> *)memberInfos
           operationTime:(long long)operationTime;

/// 群组资料变更回调
/// - Parameter operatorInfo: 操作者信息
/// - Parameter groupInfo: 群组信息，只有包含在 updateKeys 中的属性值有效
/// - Parameter updateKeys: 群组信息内容有变更的属性
/// - Parameter operationTime: 操作时间
- (void)onGroupInfoChanged:(RCGroupMemberInfo *)operatorInfo
                 groupInfo:(RCGroupInfo *)groupInfo
                updateKeys:(NSArray<RCGroupInfoKeys> *)updateKeys
             operationTime:(long long)operationTime
    __deprecated_msg(
        "Use [RCGroupEventDelegate onGroupInfoChanged:fullGroupInfo:changedGroupInfo:operationTime:] instead");

/// 群组资料变更回调
/// - Parameter operatorInfo: 操作者信息
/// - Parameter fullGroupInfo: 全量群组信息
/// - Parameter changedGroupInfo: 内容有变更的群组信息
/// - Parameter operationTime: 操作时间
- (void)onGroupInfoChanged:(RCGroupMemberInfo *)operatorInfo
             fullGroupInfo:(RCGroupInfo *)fullGroupInfo
          changedGroupInfo:(RCGroupInfo *)changedGroupInfo
             operationTime:(long long)operationTime
    __deprecated_msg(
        "Use [RCGroupEventDelegate onGroupInfoChanged:fullGroupInfo:changedProperties:operationTime:] instead");

/// 群组资料变更回调
/// - Parameter operatorInfo: 操作者信息
/// - Parameter fullGroupInfo: 全量群组信息
/// - Parameter properties: 群组信息有变更的属性
/// - Parameter operationTime: 操作时间
/// - Since: 5.22.0
/// - Warning 在该回调中，`fullGroupInfo` 的 `remark`、`role`、`joinedTime` 字段不会返回有效值，它们可能为空或为默认值。
/// 如需获取这些字段，请通过` -[RCCoreClient getGroupsInfo:success:error:]` 接口查询。
- (void)onGroupInfoChanged:(RCGroupMemberInfo *)operatorInfo
             fullGroupInfo:(RCGroupInfo *)fullGroupInfo
         changedProperties:(NSArray<NSString *> *)properties
             operationTime:(long long)operationTime;

/// 群成员资料变更回调
/// - Parameter groupId: 群组 ID
/// - Parameter operatorInfo: 操作人成员资料
/// - Parameter memberInfo: 有变更的群成员资料
/// - Parameter operationTime: 操作时间
- (void)onGroupMemberInfoChanged:(NSString *)groupId
                    operatorInfo:(RCGroupMemberInfo *)operatorInfo
                      memberInfo:(RCGroupMemberInfo *)memberInfo
                   operationTime:(long long)operationTime;

/// 群申请事件回调
/// 包含以下事件：
/// - 用户申请加入群组的**申请**或**结果**
/// - 邀请加入群组的**申请**或**结果**
- (void)onGroupApplicationEvent:(RCGroupApplicationInfo *)event;

/// 群备注名更新多端同步回调事件
/// - Parameter groupId: 群组 ID
/// - Parameter operationType: 操作类型，添加或移除
/// - Parameter groupRemark: 群备注名
/// - Parameter operationTime: 操作时间
- (void)onGroupRemarkChangedSync:(NSString *)groupId
                   operationType:(RCGroupOperationType)operationType
                     groupRemark:(NSString *)groupRemark
                   operationTime:(long long)operationTime;

/// 群成员特别关注变更多端同步回调事件
/// - Parameter groupId: 群组 ID
/// - Parameter operationType: 操作类型，添加或移除
/// - Parameter userIds: 用户 ID 列表
/// - Parameter operationTime: 操作时间
- (void)onGroupFollowsChangedSync:(NSString *)groupId
                    operationType:(RCGroupOperationType)operationType
                          userIds:(NSArray<NSString *> *)userIds
                    operationTime:(long long)operationTime;

@end

NS_ASSUME_NONNULL_END
