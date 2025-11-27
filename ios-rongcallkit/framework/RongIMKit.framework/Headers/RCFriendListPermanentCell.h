//
//  RCFriendListPermanentCell.h
//  RongIMKit
//
//  Created by RobinCui on 2024/8/20.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseTableViewCell.h"
#import "RCOnlineStatusView.h"
UIKIT_EXTERN NSString * _Nullable const RCFriendListPermanentCellIdentifier;
@class RCloudImageView;

NS_ASSUME_NONNULL_BEGIN

@interface RCFriendListPermanentCell : RCBaseTableViewCell
/*!
消息发送者的用户头像
*/
@property (nonatomic, strong) RCloudImageView *portraitImageView;
@property (nonatomic, strong) UIStackView *contentStackView;
@property (nonatomic, strong) RCOnlineStatusView *onlineStatusView;
@property (nonatomic, strong) UILabel *labName;
- (void)showPortraitByImage:(UIImage *)image;
@end

NS_ASSUME_NONNULL_END
