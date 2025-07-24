//
//  RCGroupProfileViewModel.h
//  RongIMKit
//
//  Created by zgh on 2024/8/23.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCProfileViewModel.h"

NS_ASSUME_NONNULL_BEGIN
/// 群组资料 ViewModel
/// - Since: 5.12.0
@interface RCGroupProfileViewModel : RCProfileViewModel

/// 群 Id
@property (nonatomic, copy, readonly) NSString *groupId;

/// 最多显示群成员个数，默认为 30, 设置 displayMaxMemberCount 需要不小于 5 个，不大于 50
@property (nonatomic, assign, setter=setDisplayMaxMemberCount:) NSInteger displayMaxMemberCount;

/// 实例化 RCGroupProfileViewModel
///
/// - Parameters groupId: 群 Id
+ (instancetype)viewModelWithGroupId:(NSString *)groupId;

@end

NS_ASSUME_NONNULL_END
