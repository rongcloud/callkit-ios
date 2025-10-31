//
//  RCMessageReadDetailViewController.h
//  RongIMKit
//
//  Created by Lang on 10/15/25.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RCBaseViewController.h"
#import "RCMessageReadDetailViewModel.h"

NS_ASSUME_NONNULL_BEGIN

@class RCMessageReadDetailViewController;

/// 消息阅读状态详情页数据源协议
/// - Since: 5.30.0
@protocol RCMessageReadDetailViewControllerDataSource <NSObject>

@optional

/// 获取头部视图
/// - Parameters:
///   - viewController: 当前视图控制器
///   - messageModel: 消息模型
/// - Returns: 头部视图，返回 nil 则不显示头部视图
- (UIView *)viewController:(RCMessageReadDetailViewController *)viewController 
     headerViewWithMessage:(RCMessageModel *)messageModel;

@end

/// 消息阅读状态详情页面
/// - Since: 5.30.0
@interface RCMessageReadDetailViewController : RCBaseViewController

/// 数据源
@property (nonatomic, weak) id<RCMessageReadDetailViewControllerDataSource> dataSource;

/// 初始化
/// - Parameters viewModel: 模型
- (instancetype)initWithViewModel:(RCMessageReadDetailViewModel *)viewModel;

@end

NS_ASSUME_NONNULL_END
