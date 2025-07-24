//
//  RCUltraGroupChannelChangeInfo.h
//  RongIMLibCore
//
//  Created by RobinCui on 2022/6/15.
//  Copyright © 2022 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCStatusDefine.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCUltraGroupChannelChangeInfo : NSObject

/// 超级群 id
@property (nonatomic, copy) NSString *targetId;

/// 超级群频道 id
@property (nonatomic, copy) NSString *channelId;

/// 时间
@property (nonatomic, assign) long long time;

@end


@interface RCUltraGroupChannelChangeTypeInfo : NSObject

/// 超级群变更基础信息
@property (nonatomic, strong) RCUltraGroupChannelChangeInfo *changeInfo;

/// 对应频道具体的变更信息
@property (nonatomic, assign) RCUltraGroupChannelChangeType changeType;

@end


@interface RCUltraGroupChannelUserKickedInfo : NSObject

/// 超级群变更基础信息
@property (nonatomic, strong) RCUltraGroupChannelChangeInfo *changeInfo;

/// 当前私有频道被踢的用户 id，可能是当前用户，也可能是其他人
@property (nonatomic, copy) NSString *userId;
/// 频道类型
@property (nonatomic, assign) RCUltraGroupChannelType channelType;

@end


@interface RCUltraGroupChannelDisbandedInfo : NSObject

/// 超级群变更基础信息
@property (nonatomic, strong) RCUltraGroupChannelChangeInfo *changeInfo;
/// 频道类型
@property (nonatomic, assign) RCUltraGroupChannelType channelType;

@end

NS_ASSUME_NONNULL_END
