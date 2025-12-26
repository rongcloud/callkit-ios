//
//  RCSearchBarListView.h
//  RongIMKit
//
//  Created by RobinCui on 2025/11/18.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import "RCBaseView.h"

NS_ASSUME_NONNULL_BEGIN

@interface RCSearchBarListView : RCBaseView
@property (nonatomic, strong) UITableView *tableView;
@property (nonatomic, strong) UIView *searchBar;
@property (nonatomic, strong) UIStackView *contentStackView;
@property (nonatomic, strong) UILabel *labEmpty;

- (void)configureSearchBar:(UIView *)bar;
@end

NS_ASSUME_NONNULL_END
