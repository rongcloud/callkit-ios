//
//  RCGroupInfoCellViewModel.h
//  RongIMKit
//
//  Created by RobinCui on 2024/11/20.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RongIMLibCore/RongIMLibCore.h>
#import "RCCellViewModelProtocol.h"
#import "RCBaseCellViewModel.h"
#import "RCListViewModelProtocol.h"

NS_ASSUME_NONNULL_BEGIN

@interface RCGroupInfoCellViewModel : RCBaseCellViewModel
@property (nonatomic, strong) RCGroupInfo *groupInfo;

/// 初始化
/// - Parameters:
///   - groupInfo: 群组信息
///   - keyword: 高亮关键字
- (instancetype)initWithGroupInfo:(RCGroupInfo *)groupInfo
                          keyword:(NSString *)keyword;

/// 注册 cell
+ (void)registerCellForTableView:(UITableView *)tableView;

@end

NS_ASSUME_NONNULL_END
