//
//  RCCallTipMessageCell.h
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
 简略的通话摘要消息Cell
 */
@interface RCCallTipMessageCell : RCMessageBaseCell

/*!
 显示的内容Label
 */
@property (strong, nonatomic) RCTipLabel *messageLabel;

/*!
 设置当前消息Cell的数据模型

 @param model 消息Cell的数据模型
 */
- (void)setDataModel:(RCMessageModel *)model;

@end
