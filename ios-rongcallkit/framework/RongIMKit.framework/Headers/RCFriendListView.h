//
//  RCUFriendListView.h
//  RongUserProfile
//
//  Created by RobinCui on 2024/8/16.
//

#import "RCBaseView.h"

NS_ASSUME_NONNULL_BEGIN

@interface RCFriendListView : RCBaseView
@property (nonatomic, strong) UITableView *tableView;
@property (nonatomic, strong) UIView *searchBar;
@property (nonatomic, strong) UILabel *labEmpty;
- (void)configureSearchBar:(UIView *)bar;
@end

NS_ASSUME_NONNULL_END
