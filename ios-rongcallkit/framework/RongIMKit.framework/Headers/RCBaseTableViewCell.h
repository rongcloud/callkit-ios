//
//  RCBaseTableViewCell.h
//  RongIMKit
//
//  Created by zgh on 2023/1/31.
//  Copyright © 2023 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
/// - Since: 5.4.0
@interface RCBaseTableViewCell : UITableViewCell

- (void)setupView;

/// 设置约束布局
- (void)setupConstraints;

@end

NS_ASSUME_NONNULL_END
