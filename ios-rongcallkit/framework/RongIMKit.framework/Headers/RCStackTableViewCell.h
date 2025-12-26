//
//  RCStackTableViewCell.h
//  RongIMKit
//
//  Created by RobinCui on 2025/12/10.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import "RCPaddingTableViewCell.h"

NS_ASSUME_NONNULL_BEGIN

@interface RCStackTableViewCell : RCPaddingTableViewCell
@property (nonatomic, strong) UIStackView *contentStackView;

@end

NS_ASSUME_NONNULL_END
