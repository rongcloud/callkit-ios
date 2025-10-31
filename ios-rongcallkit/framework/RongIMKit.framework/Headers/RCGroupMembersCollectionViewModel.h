//
//  RCGroupMembersCollectionViewModel.h
//  RongIMKit
//
//  Created by zgh on 2024/8/23.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseViewModel.h"
#import <RongIMLibCore/RongIMLibCore.h>
#import "RCCollectionViewModelProtocol.h"

NS_ASSUME_NONNULL_BEGIN

#define RCGroupMembersCollectionViewModelItemWidth 64
#define RCGroupMembersCollectionViewModelItemHeight 70
#define RCGroupMembersCollectionViewModelLineSpace 12
#define RCGroupMembersCollectionViewModelPortraitLineCount 5

@class RCGroupMembersCollectionViewModel;
@protocol RCGroupMembersCollectionViewModelDelegate <NSObject>

@optional
/// 点击群成员头像
///
/// - Parameters viewModel: viewModel
/// - Parameters viewController: 当前 VC
/// - Parameters member: 成员信息
/// - Returns: App是否处理[YES : SDK不再处理, NO: SDK处理]
///
/// - Since: 5.12.0
- (BOOL)groupMembersCollectionViewModel:(RCGroupMembersCollectionViewModel *)viewModel
                         viewController:(UIViewController*)viewController
                        didSelectMember:(RCGroupMemberInfo *)member;

/// 点击添加
///
/// - Parameters viewModel: viewModel
/// - Parameters viewController: 当前 VC
/// - Returns: App是否处理[YES : SDK不再处理, NO: SDK处理]
///
/// - Since: 5.12.0
- (BOOL)groupMembersCollectionViewModel:(RCGroupMembersCollectionViewModel *)viewModel
                           didSelectAdd:(UIViewController*)viewController;

/// 点击移除
///
/// - Parameters viewModel: viewModel
/// - Parameters viewController: 当前 VC
/// - Returns: App是否处理[YES : SDK不再处理, NO: SDK处理]
///
/// - Since: 5.12.0
- (BOOL)groupMembersCollectionViewModel:(RCGroupMembersCollectionViewModel *)viewModel
                        didSelectRemove:(UIViewController*)viewController;

/// 添加群成员
///
/// - Parameters viewModel: viewModel
/// - Parameters viewController: 当前 VC
/// - Returns: App是否处理[YES : SDK不再处理, NO: SDK处理]
///
/// - Since: 5.12.0
- (BOOL)groupMembersCollectionViewModel:(RCGroupMembersCollectionViewModel *)viewModel
                         didInviteUsers:(NSArray<NSString *> *)userIds
                            processCode:(RCErrorCode)processCode
                         viewController:(UIViewController*)viewController;
@end

/// 群资料页成员展示 ViewModel
/// - Since: 5.12.0
@interface RCGroupMembersCollectionViewModel : RCBaseViewModel<RCCollectionViewModelProtocol>

/// 代理
@property (nonatomic, weak) id<RCGroupMembersCollectionViewModelDelegate> delegate;

/// 代理
@property (nonatomic, weak) id<RCCollectionViewModelResponder> responder;

/// 群id
@property (nonatomic, copy, readonly) NSString *groupId;

/// 数据源
@property (nonatomic, strong, readonly) NSArray <RCGroupMemberInfo *> *members;

/// 是否允许添加成员
@property (nonatomic, assign, readonly) BOOL allowAdd;

/// 是否允许移除成员
@property (nonatomic, assign, readonly) BOOL allowRemove;

/// 实例化 RCGroupProfileMembersCellViewModel
///
/// - Parameters groupId: 群 Id
/// - Parameters members: 数据源
/// - Parameters allowAdd: 是否允许添加成员
/// - Parameters allowRemove: 是否允许移除成员
/// - Parameters responder: 当前 VC
+ (instancetype)viewModelWithGroupId:(NSString *)groupId
                             members:(NSArray <RCGroupMemberInfo *> *)members
                            allowAdd:(BOOL)allowAdd
                         allowRemove:(BOOL)allowRemove
                    inViewController:(UIViewController *)inViewController;

+ (void)registerCollectionViewCell:(UICollectionView *)collectionView;

@end

NS_ASSUME_NONNULL_END
