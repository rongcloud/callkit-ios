//
//  RCGroupNotificationCellViewModel.h
//  RongIMKit
//
//  Created by RobinCui on 2024/11/14.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RongIMLibCore/RongIMLibCore.h>
#import "RCCellViewModelProtocol.h"
#import "RCBaseCellViewModel.h"
#import "RCListViewModelProtocol.h"

NS_ASSUME_NONNULL_BEGIN

@interface RCGroupNotificationCellViewModel : RCBaseCellViewModel
/// 申请信息
@property (nonatomic, strong) RCGroupApplicationInfo *application;
/// 初始化
- (instancetype)initWithApplicationInfo:(RCGroupApplicationInfo *)application;

/// 注册 cell
+ (void)registerCellForTableView:(UITableView *)tableView;

/// 绑定响应者
- (void)bindResponder:(UIViewController <RCListViewModelResponder>*)responder;

/// 接受申请
- (void)approveApplication;

/// 拒绝申请
- (void)rejectApplication;
@end

NS_ASSUME_NONNULL_END
