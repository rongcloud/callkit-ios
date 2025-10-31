//
//  RCReadReceiptProgressView.h
//  RongIMKit
//
//  Created by Lang on 2025/09/30.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/// 圆形已读进度视图，用于显示消息已读进度
/// 从12点钟方向顺时针填充，填充区域与边框之间有间距
@interface RCReadReceiptProgressView : UIView

/// 当前进度（0.0 ~ 1.0）
@property (nonatomic, assign) CGFloat progress;

/// 边框颜色（默认 #16D258 绿色）
@property (nonatomic, strong) UIColor *borderColor;

/// 填充颜色（默认与边框同色 #16D258）
@property (nonatomic, strong) UIColor *fillColor;

/// 内部边距（填充区域与圆形边框之间的间距，默认 2.0px）
@property (nonatomic, assign) CGFloat innerPadding;

/// 圆形边框线宽（默认 1.17px）
@property (nonatomic, assign) CGFloat borderWidth;

@end

NS_ASSUME_NONNULL_END
