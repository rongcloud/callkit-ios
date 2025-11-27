//
//  RCOnlineStatusView.h
//  RongIMKit
//
//  Created by Lang on 11/7/25.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import "RCBaseView.h"

NS_ASSUME_NONNULL_BEGIN

/// 在线状态指示器视图
///
/// - Note:
///     - 显示为 6x6 的圆形指示器
///     - 在线：绿色圆点
///     - 离线：灰色圆点
///     - 默认隐藏状态
///
@interface RCOnlineStatusView : RCBaseView

// isOnline: YES：在线（绿色），NO：离线（灰色）
@property (nonatomic, assign, getter=isOnline) BOOL online;

/// 重置状态（隐藏并清除颜色）
- (void)reset;

@end

NS_ASSUME_NONNULL_END

