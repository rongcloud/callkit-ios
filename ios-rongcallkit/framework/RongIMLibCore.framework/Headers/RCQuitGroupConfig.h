//
//  RCQuitGroupConfig.h
//  RongIMLibCore
//
//  Created by Lang on 2024/7/19.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCQuitGroupConfig : NSObject

/// 是否移除群成员禁言状态，默认为移除
@property (nonatomic, assign) BOOL removeMuteStatus;

/// 是否移除群成员白名单，默认为移除
@property (nonatomic, assign) BOOL removeWhiteList;

/// 是否移除特别关注群成员，默认为移除
@property (nonatomic, assign) BOOL removeFollow;

@end

NS_ASSUME_NONNULL_END
