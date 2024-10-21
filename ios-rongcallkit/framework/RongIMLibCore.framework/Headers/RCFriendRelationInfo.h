//
//  RCFriendRelationInfo.h
//  RongIMLibCore
//
//  Created by Lang on 2024/8/12.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCFriendEnum.h>

NS_ASSUME_NONNULL_BEGIN

/// 好友关系结果
@interface RCFriendRelationInfo : NSObject

/// 用户 ID
@property (nonatomic, copy) NSString *userId;

/// 好友关系
@property (nonatomic, assign) RCFriendRelationType relationType;

@end

NS_ASSUME_NONNULL_END
