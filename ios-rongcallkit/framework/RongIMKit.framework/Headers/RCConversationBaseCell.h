//
//  RCConversationBaseCell.h
//  RongIMKit
//
//  Created by xugang on 15/1/24.
//  Copyright (c) 2015年 RongCloud. All rights reserved.
//

#import "RCConversationModel.h"
#import <UIKit/UIKit.h>
#import "RCBaseTableViewCell.h"
/// 会话Cell基类
@interface RCConversationBaseCell : RCBaseTableViewCell

/// 会话Cell的数据模型
@property (nonatomic, strong) RCConversationModel *model;

/*!
 设置会话Cell的数据模型

 - Parameter model: 会话Cell的数据模型
 */
- (void)setDataModel:(RCConversationModel *)model;

@end
