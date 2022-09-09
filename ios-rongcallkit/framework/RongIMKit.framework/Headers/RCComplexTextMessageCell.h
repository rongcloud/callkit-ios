//
//  RCComplexTextMessageCell.h
//  RongIMKit
//
//  Created by RobinCui on 2022/5/20.
//  Copyright © 2022 RongCloud. All rights reserved.
//

#import "RCMessageCell.h"

NS_ASSUME_NONNULL_BEGIN

extern NSString *const RCComplexTextMessageCellIdentifier;

/**
 *  复杂文本异步显示cell
 */

@interface RCComplexTextMessageCell : RCMessageCell

/**
 *  attributeDictionary
 */
@property (nonatomic, strong) NSDictionary *attributeDictionary;

/*!
 设置当前消息Cell的数据模型

 @param model 消息Cell的数据模型
 */
- (void)setDataModel:(RCMessageModel *)model;

@end

NS_ASSUME_NONNULL_END
