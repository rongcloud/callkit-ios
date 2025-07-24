//
//  RCUserProfileViewModel.h
//  RongUserProfile
//
//  Created by zgh on 2024/8/19.
//

#import "RCProfileViewModel.h"

NS_ASSUME_NONNULL_BEGIN
/// 用户资料 ViewModel
/// - Since: 5.12.0
@interface RCUserProfileViewModel : RCProfileViewModel

/// 用户 Id
@property (nonatomic, copy, readonly) NSString *userId;

/// 所属群 Id
@property (nonatomic, copy, readonly) NSString *groupId;

/// 验证好友关系
@property (nonatomic, assign) BOOL verifyFriend;

/// 实例化
+ (RCProfileViewModel *)viewModelWithUserId:(NSString *)userId;

/// 展示群内成员昵称
- (void)showGroupMemberInfo:(NSString *)groupId;

@end

NS_ASSUME_NONNULL_END
