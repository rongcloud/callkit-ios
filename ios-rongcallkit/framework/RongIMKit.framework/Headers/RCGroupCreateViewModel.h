//
//  RCGroupCreateViewModel.h
//  RongIMKit
//
//  Created by zgh on 2024/8/22.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RCBaseViewModel.h"
#import <RongIMLibCore/RongIMLibCore.h>

NS_ASSUME_NONNULL_BEGIN
/// 创建群组代理
@protocol RCGroupCreateViewModelDelegate <NSObject>
///配置 groupID
///
/// - Returns: 群 Id
///
/// - Since: 5.12.0
- (NSString *)generateGroupId;

@optional

/// 头像点击回调
///
/// - Parameter inViewController:    当前 VC
/// - Parameter resultBlock:         上传头像后的回调【resultBlock：头像 url】
///
///  - Since: 5.12.0
- (void)groupPortraitDidClick:(UIViewController *)inViewController
                  resultBlock:(void(^)(NSString *portraitUrl))resultBlock;

/// 创建群组成功回调
///
/// - Parameter groupId:    群 id
/// - Parameter processCode: 当群组的`inviteHandlePermission` 为被邀请人需要同意才能进群时，`processCode` 返回 `RC_GROUP_NEED_INVITEE_ACCEPT` ( 25427 )，表示需要被邀请人同意后才能进入群组。当群组的 `inviteHandlePermission` 为不需被邀请人同意时，`processCode` 返回 RC_SUCCESS ( 0 )，被邀请人会直接加入群组。
/// - Parameter inViewController:    当前 VC
/// - Returns: App是否处理[YES : SDK不再处理, NO: SDK处理]
///
///  - Since: 5.12.0
- (BOOL)groupCreateDidSuccess:(RCGroupInfo *)group
                  processCode:(RCErrorCode)processCode
             inViewController:(UIViewController *)inViewController;


@end

@protocol RCGroupCreateViewModelResponder <NSObject>

/// 头像更新回调(通知 UI 更新)
///
/// - Parameter portraitUri: 头像 url
///
///  - Since: 5.12.0
- (void)groupPortraitDidUpdate:(NSString *)portraitUri;

@end

/// 创建群组 viewModel
/// - Since: 5.12.0
@interface RCGroupCreateViewModel : RCBaseViewModel

/// 代理
@property (nonatomic, weak) id<RCGroupCreateViewModelDelegate> delegate;

/// 响应器
@property (nonatomic, weak) id<RCGroupCreateViewModelResponder> responder;

/// 群名称长度限制
@property (nonatomic, assign, readonly) NSInteger groupNameLimit;

/// 生成创建群组实例
///
/// - Parameter inviteeUserIds: 邀请创建群组的用户列表
+ (instancetype)viewModelWithInviteeUserIds:(NSArray <NSString *>*)inviteeUserIds;

/// 创建群组
///
/// - Parameter groupName:           群组名称
/// - Parameter inViewController:    当前 VC
- (void)createGroup:(NSString *)groupName
   inViewController:(UIViewController *)viewController;

/// 头像点击事件
- (void)portraitImageViewDidClick:(UIViewController *)inViewController;;

@end

NS_ASSUME_NONNULL_END
