//
//  RCGroupOperationErrorInfo.h
//  RongIMLibCore
//
//  Created by RongCloud on 2026/8/17.
//  Copyright © 2026 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class RCGroupMemberInfo;

/// 创建群组失败时的附加信息。
@interface RCCreateGroupErrorInfo : NSObject

/// 资料审核失败的字段。仅在对应错误码下返回。
@property (nonatomic, copy, readonly, nullable) NSArray<NSString *> *errorKeys;

/// 因加入群组数量超限而失败的用户信息。仅在对应错误码下返回。
@property (nonatomic, copy, readonly, nullable) NSArray<RCGroupMemberInfo *> *failedUserInfos;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/// 邀请用户加入群组失败时的附加信息。
@interface RCInviteUsersToGroupErrorInfo : NSObject

/// 因加入群组数量超限而失败的用户信息。仅在对应错误码下返回。
@property (nonatomic, copy, readonly, nullable) NSArray<RCGroupMemberInfo *> *failedUserInfos;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
