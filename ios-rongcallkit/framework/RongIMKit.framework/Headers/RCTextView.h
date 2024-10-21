//
//  RCTextView.h
//  RongExtensionKit
//
//  Created by Liv on 14/10/30.
//  Copyright (c) 2014年 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>

@class RCTextView;

@protocol RCTextViewDelegate <NSObject>

@optional
- (void)rctextView:(RCTextView *)textView textDidChange:(NSString *)text;

@end

/// 文本输入框的View
@interface RCTextView : UITextView

/*!
 是否关闭菜单

  默认值为NO。
 */
@property (nonatomic, assign) BOOL disableActionMenu;

@property (nonatomic, weak) id<RCTextViewDelegate> textChangeDelegate;

@end
