//
//  RCPaddingTableViewCell.h
//  RongIMKit
//
//  Created by RobinCui on 2025/11/11.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import "RCBaseTableViewCell.h"
extern NSInteger const RCUserManagementPadding;
extern NSInteger const RCUserManagementImageCellLineLeading;
extern NSInteger const RCUserManagementImageCellLineTrailing;

NS_ASSUME_NONNULL_BEGIN

@interface RCPaddingTableViewCell : RCBaseTableViewCell
@property (nonatomic, strong) UIView *lineView;
@property (nonatomic, strong) UIView *paddingContainerView;
@property (nonatomic, assign) BOOL hideSeparatorLine;
- (void)updateLineViewConstraints:(NSInteger)leading
                         trailing:(NSInteger)trailing;

- (void)updatePaddingContainer:(NSInteger)leading
                      trailing:(NSInteger)trailing;
@end

NS_ASSUME_NONNULL_END
