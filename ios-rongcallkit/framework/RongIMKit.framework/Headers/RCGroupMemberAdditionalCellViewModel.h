//
//  RCGroupMemberAdditionalCellViewModel.h
//  RongIMKit
//
//  Created by RobinCui on 2025/11/11.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import "RCBaseCellViewModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface RCGroupMemberAdditionalCellViewModel : RCBaseCellViewModel
@property (nonatomic, copy) NSString *title;
@property (nonatomic, strong) UIImage *portrait;
- (instancetype)initWithTitle:(NSString *)title
                     portrait:(UIImage *)portrait;

+ (void)registerCellForTableView:(UITableView *)tableView;
@end

NS_ASSUME_NONNULL_END
