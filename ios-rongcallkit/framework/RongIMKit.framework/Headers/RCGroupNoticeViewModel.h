//
//  RCGroupNoticeViewModel.h
//  RongIMKit
//
//  Created by zgh on 2024/8/28.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseViewModel.h"
#import <RongIMLibCore/RongIMLibCore.h>

NS_ASSUME_NONNULL_BEGIN
@class RCGroupNoticeViewModel;
/// 群公告代理
@protocol RCGroupNoticeViewModelDelegate <NSObject>

@optional

/// 群公告将要更改
///
/// - Parameter updatedGroup: 更新后的群信息
/// - Parameter viewModel: RCGroupNoticeViewModel
/// - Parameter inViewController:    当前 VC
/// - Returns: App是否处理[YES : SDK不再处理, NO: SDK处理]
///
///  - Since: 5.12.2
- (BOOL)groupNoticeWillUpdate:(RCGroupInfo *)updatedGroup
                    viewModel:(RCGroupNoticeViewModel *)viewModel
             inViewController:(UIViewController *)inViewController;

/// 群公告已经更改
///
/// - Parameter updatedGroup: 更新后的群信息
/// - Parameter viewModel: RCGroupNoticeViewModel
/// - Parameter inViewController:    当前 VC
/// - Returns: App是否处理[YES : SDK不再处理, NO: SDK处理]
///
///  - Since: 5.12.2
- (BOOL)groupNoticeDidUpdate:(RCGroupInfo *)updatedGroup
                 viewModel:(RCGroupNoticeViewModel *)viewModel
          inViewController:(UIViewController *)inViewController;

@end

/// 群公告 viewModel
@interface RCGroupNoticeViewModel : RCBaseViewModel

/// 代理
@property (nonatomic, weak) id<RCGroupNoticeViewModelDelegate> delegate;

/// 群信息
@property (nonatomic, strong, readonly) RCGroupInfo *group;

/// 是否可编辑
@property (nonatomic, assign, readonly) BOOL canEdit;

/// 群公告长度限制，默认 1024
@property (nonatomic, assign, readonly) NSInteger limit;

/// 初始化
///
/// - Parameter group: 群信息
- (instancetype)initWithGroup:(RCGroupInfo *)group;

/// 更新群公告
///
/// - Parameter notice: 公告
/// - Parameter viewController: 当前 VC
- (void)updateNotice:(NSString *)notice inViewController:(UIViewController *)viewController;

/// 提示信息
///
/// - Returns: 提示内容
- (NSString *)tip;

@end

NS_ASSUME_NONNULL_END
