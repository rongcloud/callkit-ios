//
//  RCContentView.h
//  RongIMKit
//
//  Created by xugang on 3/31/15.
//  Copyright (c) 2015 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>

/*!
 消息内容的View
 */
@interface RCContentView : UIView

@property (nonatomic, assign) CGSize contentSize;

/*!
 注册Frame发生变化的回调

 @param eventBlock Frame发生变化的回调
 */
- (void)registerFrameChangedEvent:(void (^)(CGRect frame))eventBlock;

/*!
 注册Size发生变化的回调

 @param eventBlock Size 发生变化的回调
 */
- (void)registerSizeChangedEvent:(void (^)(CGSize contentSize))eventBlock;
@end
