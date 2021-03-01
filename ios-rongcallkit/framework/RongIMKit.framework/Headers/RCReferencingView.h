//
//  RCReferencingView.h
//  RongIMKit
//
//  Created by 张改红 on 2020/2/27.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RCMessageModel.h"
@class RCReferencingView;

@protocol RCReferencingViewDelegate <NSObject>
@optional
- (void)didTapReferencingView:(RCMessageModel *)messageModel;

- (void)dismissReferencingView:(RCReferencingView *)referencingView;

@end

@interface RCReferencingView : UIView

/*!
 关闭引用 button
*/
@property (nonatomic, strong) UIButton *dismissButton;

/*!
 被引用消息发送者名称
*/
@property (nonatomic, strong) UILabel *nameLabel;

/*!
 被引用消息内容文本 label
 */
@property (nonatomic, strong) UILabel *textLabel;

/*!
 被引用消息体
 */
@property (nonatomic, strong) RCMessageModel *referModel;
/*!
 引用代理
 */
@property (nonatomic, weak) id<RCReferencingViewDelegate> delegate;
/*!
 初始化引用 View
 */
- (instancetype)initWithModel:(RCMessageModel *)model inView:(UIView *)view;

/*!
 当前 view 的 Y 值
*/
- (void)setOffsetY:(CGFloat)offsetY;
@end
