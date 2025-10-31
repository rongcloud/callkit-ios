//
//  RCMessageReadDetailTabView.h
//  RongIMKit
//
//  Created by Lang on 10/15/25.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import "RCBaseView.h"
#import "RCMessageReadDetailDefine.h"

NS_ASSUME_NONNULL_BEGIN

@class RCMessageReadDetailTabView;

@protocol RCReadReceiptDetailTabViewDelegate <NSObject>

/// Tab 切换回调
- (void)tabView:(RCMessageReadDetailTabView *)tabView didSelectTabAtIndex:(RCMessageReadDetailTabType)tabType;

@end

/// Tab 切换视图
@interface RCMessageReadDetailTabView : RCBaseView

@property (nonatomic, weak) id<RCReadReceiptDetailTabViewDelegate> delegate;

@property (nonatomic, strong) UIButton *readButton;
@property (nonatomic, strong) UIButton *unreadButton;
@property (nonatomic, strong) UIView *indicatorView;
@property (nonatomic, strong) UIView *separatorLine;

@property (nonatomic, strong) UIColor *selectedColor;
@property (nonatomic, strong) UIColor *unselectedColor;

/// 设置颜色
/// @param selectedColor 选中颜色
/// @param unselectedColor 未选中颜色
- (void)setupSelectedColor:(UIColor *)selectedColor unselectedColor:(UIColor *)unselectedColor;

/// 设置数量
/// @param readCount 已读数量
/// @param unreadCount 未读数量
- (void)setupReadCount:(NSInteger)readCount unreadCount:(NSInteger)unreadCount;

/// 选中指定 Tab
- (void)selectTabAtIndex:(RCMessageReadDetailTabType)tabType;

@end

NS_ASSUME_NONNULL_END

