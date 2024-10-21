//
//  RCUserInfo+RCGroupMember.h
//  RongIMKit
//
//  Created by zgh on 2024/8/29.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <RongIMLibCore/RongIMLibCore.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCUserInfo (RCGroupMember)
/// 群成员信息
/// - Since: 5.12.0
@property (nonatomic, strong) RCGroupMemberInfo *rc_member;

@end

NS_ASSUME_NONNULL_END
