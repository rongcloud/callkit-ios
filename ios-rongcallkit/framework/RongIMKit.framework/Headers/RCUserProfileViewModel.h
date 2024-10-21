//
//  RCUserProfileViewModel.h
//  RongUserProfile
//
//  Created by zgh on 2024/8/19.
//

#import <RongIMKit/RCProfileViewModel.h>

NS_ASSUME_NONNULL_BEGIN
/// 用户资料 ViewModel
/// - Since: 5.12.0
@interface RCUserProfileViewModel : RCProfileViewModel

/// 用户 Id
@property (nonatomic, copy, readonly) NSString *userId;

/// 验证好友关系
@property (nonatomic, assign) BOOL verifyFriend;

/// 实例化
+ (RCProfileViewModel *)viewModelWithUserId:(NSString *)userId;

@end

NS_ASSUME_NONNULL_END
