//
//  RCCallDetailMessageCell.h
//  RongCallKit
//
//  Created by RongCloud on 16/3/20.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#if __has_include(<RongIMKit/RongIMKit.h>)

#import <RongIMKit/RongIMKit.h>

#else

#import "RongIMKit.h"

#endif

/*!
 通话摘要的消息Cell
 */
@interface RCCallDetailMessageCell : RCMessageCell

/*!
 消息文本的Label
 */
@property (strong, nonatomic) UILabel *textLabel;

/*!
 标识媒体类型的Icon
 */
@property (strong, nonatomic) UIImageView *mediaTypeIcon;

/*!
 设置当前消息Cell的数据模型

 @param model 消息Cell的数据模型
 */
- (void)setDataModel:(RCMessageModel *)model;

@end
