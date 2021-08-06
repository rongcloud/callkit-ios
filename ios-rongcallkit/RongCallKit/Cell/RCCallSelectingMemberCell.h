//
//  RCCallSelectingMemberCell.h
//  RongCallKit
//
//  Created by RongCloud on 16/3/15.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "RCloudImageView.h"

/*!
 选择通话成员界面的成员Cell
 */
@interface RCCallSelectingMemberCell : UITableViewCell

/*!
 标识选中状态的View
 */
@property (nonatomic, strong) UIImageView *selectedImageView;

/*!
 用户头像
 */
@property (nonatomic, strong) RCloudImageView *headerImageView;

/*!
 用户名称Label
 */
@property (nonatomic, strong) UILabel *nameLabel;

@end
