//
//  RCReferenceMessageCell.h
//  RongIMKit
//
//  Created by 张改红 on 2020/2/27.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <RongIMKit/RongIMKit.h>
#import "RCAttributedLabel.h"
#import "RCReferencedContentView.h"
NS_ASSUME_NONNULL_BEGIN

@interface RCReferenceMessageCell : RCMessageCell
/*!
 引用内容展示的容器
 */
@property (nonatomic, strong) RCReferencedContentView *referencedContentView;

/*!
 文本内容的Label
 */
@property (nonatomic, strong) RCAttributedLabel *contentLabel;

@end

NS_ASSUME_NONNULL_END
