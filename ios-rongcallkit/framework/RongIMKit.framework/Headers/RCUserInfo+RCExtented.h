//
//  RCUserInfo+RCExtented.h
//  RongIMKit
//
//  Created by zgh on 2024/8/29.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <RongIMLibCore/RongIMLibCore.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCUserInfo (RCExtented)

/// 用户资料
/// - Since: 5.12.0
@property (nonatomic, strong) RCUserProfile *rc_profile;

/// 好友资料
/// - Since: 5.12.0
@property (nonatomic, strong) RCFriendInfo *rc_friendInfo;

@end

NS_ASSUME_NONNULL_END
