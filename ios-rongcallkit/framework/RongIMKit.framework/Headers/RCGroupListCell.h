//
//  RCGroupListCell.h
//  RongIMKit
//
//  Created by RobinCui on 2024/11/28.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCFriendListPermanentCell.h"

NS_ASSUME_NONNULL_BEGIN
UIKIT_EXTERN NSString  * const RCGroupListCellIdentifier;

@interface RCGroupListCell : RCFriendListPermanentCell
- (void)showPortrait:(NSString *)url;
@end

NS_ASSUME_NONNULL_END
