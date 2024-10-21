//
//  RCContentView.h
//  RongIMKit
//
//  Created by xugang on 3/31/15.
//  Copyright (c) 2015 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RCBaseView.h"
/// 消息内容的View
@interface RCContentView : RCBaseView

@property (nonatomic, assign) CGSize contentSize;

/*!
 注册Frame发生变化的回调

 - Parameter eventBlock: Frame发生变化的回调
 */
- (void)registerFrameChangedEvent:(void (^)(CGRect frame))eventBlock;

/*!
 注册Size发生变化的回调

 - Parameter eventBlock: Size 发生变化的回调
 */
- (void)registerSizeChangedEvent:(void (^)(CGSize contentSize))eventBlock;
@end
