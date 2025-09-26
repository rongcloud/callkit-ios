//
//  RCCallASRConfigController.h
//  RongCallKit
//
//  Created by RongCloud on 25/9/5.
//  Copyright © 2025年 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface RCCallASRConfigController : UIViewController

/*!
 翻译目标语言码
 */
@property (nonatomic, copy) NSString *destLangCode;

/*!
 UI 是否显示双语言
 */
@property (nonatomic, assign) BOOL displayDualLangUI;

/*!
 设置回调
 */
@property (nonatomic, copy) void(^configCallback)(NSString *destLangCode, BOOL displayDualLangUI);

/*!
 初始化
 */
- (instancetype)init;

@end

