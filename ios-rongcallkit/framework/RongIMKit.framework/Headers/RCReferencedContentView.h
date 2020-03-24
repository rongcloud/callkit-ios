//
//  RCReferencedContentView.h
//  RongIMKit
//
//  Created by 张改红 on 2020/2/27.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RCMessageModel.h"
#import "RCAttributedLabel.h"
#define TextFont 14
@protocol RCReferencedContentViewDelegate <NSObject>
@optional

- (void)didTapReferencedContentView:(RCMessageModel *)message;

- (void)attributedLabel:(RCAttributedLabel *)label didSelectLinkWithURL:(NSURL *)url;

- (void)attributedLabel:(RCAttributedLabel *)label didSelectLinkWithPhoneNumber:(NSString *)phoneNumber;
@end
@interface RCReferencedContentView : UIView
/*!
 被引用消息显示左边线
 */
@property (nonatomic, strong) UIView *leftLimitLine;

/*!
 被引用消息显示底部边线
 */
@property (nonatomic, strong) UIView *bottomLimitLine;

/*!
 被引用消息发送者名称
*/
@property (nonatomic, strong) UILabel *nameLabel;

/*!
 被引用消息内容文本 label
 */
@property (nonatomic, strong) RCAttributedLabel *textLabel;

/*!
 被引用图片消息显示的 View
*/
@property (nonatomic, strong) UIImageView *msgImageView;
@property (nonatomic, weak) id<RCReferencedContentViewDelegate> delegate;
- (void)setMessage:(RCMessageModel *)message contentSize:(CGSize)contentSize;
@end
