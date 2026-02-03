//
//  RCCallAISummaryMessageCell.h
//  RongCallKit
//
//  Created by RongCloud on 25/12/8.
//  Copyright © 2025年 RongCloud. All rights reserved.
//

#import "RCAdapteRongIMKitHeader.h"

/*!
 通话智能总结消息Cell
 */
@interface RCCallAISummaryMessageCell : RCMessageCell

/*!
 标题 Label - 显示"AI总结完成"
 */
@property (strong, nonatomic) UILabel *titleLabel;

/*!
 时间 Label - 显示"通话开始时间: xxx"
 */
@property (strong, nonatomic) UILabel *timeLabel;

/*!
 详情 Label - 显示"查看详情"
 */
@property (strong, nonatomic) UILabel *detailLabel;

/*!
 设置当前消息Cell的数据模型

 @param model 消息Cell的数据模型
 */
- (void)setDataModel:(RCMessageModel *)model;

@end
