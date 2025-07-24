//
//  RCGroupFollowsViewModel.h
//  RongIMKit
//
//  Created by zgh on 2024/11/20.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseViewModel.h"
#import "RCListViewModelProtocol.h"

NS_ASSUME_NONNULL_BEGIN
/// 群特别关注 viewModel
/// - Since: 5.12.2
@interface RCGroupFollowsViewModel : RCBaseViewModel<RCListViewModelProtocol>
/// 实例化 RCGroupFollowsViewModel
///
/// - Parameters groupId: 群主 Id
+ (instancetype)viewModelWithGroupId:(NSString *)groupId;

/// 绑定响应器
- (void)bindResponder:(id<RCListViewModelResponder>)responder;

/// 获取群特别关注列表
- (void)fetchGroupFollows;

@end

NS_ASSUME_NONNULL_END
