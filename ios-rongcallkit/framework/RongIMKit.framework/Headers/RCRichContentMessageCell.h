//
//  RCRichContentMessageCell.h
//  RongIMKit
//
//  Created by xugang on 15/2/2.
//  Copyright (c) 2015年 RongCloud. All rights reserved.
//

#import "RCAttributedLabel.h"
#import "RCMessageCell.h"

/*!
 富文本（图文）消息Cell
 */
@interface RCRichContentMessageCell : RCMessageCell

/*!
 图片内容显示的View
 */
@property (nonatomic, strong) RCloudImageView *richContentImageView;

/*!
 文本内容显示的Label
 */
@property (nonatomic, strong) RCAttributedLabel *digestLabel;

/*!
 标题显示的Label
 */
@property (nonatomic, strong) RCAttributedLabel *titleLabel;

@end
