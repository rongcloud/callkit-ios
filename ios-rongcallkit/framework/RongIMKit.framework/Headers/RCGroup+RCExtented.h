//
//  RCGroup+RCExtented.h
//  RongIMKit
//
//  Created by zgh on 2024/8/29.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <RongIMLibCore/RongIMLibCore.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCGroup (RCExtented)

/// 群组资料
/// - Since: 5.12.0
@property (nonatomic, strong) RCGroupInfo *rc_group;

@end

NS_ASSUME_NONNULL_END
