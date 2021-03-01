//
//  RCImageSlideController.h
//  RongIMKit
//
//  Created by liulin on 16/5/18.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCBaseViewController.h"
#import "RCImageMessageProgressView.h"
#import <UIKit/UIKit.h>
@class RCMessageModel;

@interface RCImageSlideController : RCBaseViewController

/*!
 图片预览初始化的数据模型
 */
@property (nonatomic, strong) RCMessageModel *messageModel;

/*!
 当前预览的图片消息
 */
@property (nonatomic, strong) RCImageMessage *currentPreviewImage;

/*!
 是否只预览当前图片消息，默认为 NO，支持当前会话图片消息滑动预览，如果设置为 YES， 只预览当前图片消息
 */
@property (nonatomic, assign) BOOL onlyPreviewCurrentMessage;

/**
 长按图片内容的回调

 @param sender 长按手势

 @discussion 如需使用SDK的长按图片内容处理，请调用父类方法 [super longPressed:sender];
 */
- (void)longPressed:(id)sender;

@end
