//
//  RCGroupProfileMembersCellViewModel.h
//  RongIMKit
//
//  Created by zgh on 2024/8/23.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCProfileCellViewModel.h"
#import "RCGroupMembersCollectionViewModel.h"
NS_ASSUME_NONNULL_BEGIN
/// 群资料页成员展示 cellViewModel
/// - Since: 5.12.0
@interface RCGroupProfileMembersCellViewModel : RCProfileCellViewModel

/// 代理
@property (nonatomic, weak) id<RCGroupMembersCollectionViewModelDelegate> delegate;

/// 实例化 RCGroupProfileMembersCellViewModel
///
/// - Parameters showItemCount: 展示数量
- (instancetype)initWithItemCount:(NSInteger)showItemCount;

// 配置成员展示 viewModel
- (void)configViewModel:(RCGroupMembersCollectionViewModel *)viewModel;

@end

NS_ASSUME_NONNULL_END
