//
//  RCMessageReadDetailView.h
//  RongIMKit
//
//  Created by Lang on 10/15/25.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RCMessageReadDetailTabView.h"

NS_ASSUME_NONNULL_BEGIN

@class RCMessageReadDetailView;
@class RCMessageModel;

/// 消息阅读状态详情页视图代理协议
@protocol RCMessageReadDetailViewDelegate <NSObject>

@optional

/// 用户切换了 Tab
/// - Parameters:
///   - view: 当前视图
///   - tabType: 切换到的 Tab 类型
- (void)readReceiptUserListView:(RCMessageReadDetailView *)view 
                 didSwitchToTab:(RCMessageReadDetailTabType)tabType;

/// 需要加载更多数据
/// - Parameters:
///   - view: 当前视图
///   - tabType: 当前 Tab 类型
- (void)readReceiptUserListView:(RCMessageReadDetailView *)view 
          needLoadMoreForTabType:(RCMessageReadDetailTabType)tabType;

@end

/// 消息阅读状态详情页视图
@interface RCMessageReadDetailView : UIView

/// 代理
@property (nonatomic, weak) id<RCMessageReadDetailViewDelegate> delegate;

/// 已读、未读切换按钮视图
@property (nonatomic, strong, readonly) RCMessageReadDetailTabView *tabView;

/// 已读列表视图
@property (nonatomic, strong, readonly) UITableView *readTableView;

/// 未读列表视图
@property (nonatomic, strong, readonly) UITableView *unreadTableView;

/// 初始化
/// - Parameters:
///   - frame: 视图大小
///   - tabHeight: Tab 高度
- (instancetype)initWithFrame:(CGRect)frame tabHeight:(CGFloat)tabHeight;

/// 设置 Tab 的已读/未读数量
/// - Parameters:
///   - readCount: 已读数量
///   - unreadCount: 未读数量
- (void)setupReadCount:(NSInteger)readCount unreadCount:(NSInteger)unreadCount;

/// 切换 Tab 显示
/// - Parameters:
///   - tabType: Tab 类型
///   - isEmpty: 当前列表是否为空
- (void)switchToTabType:(RCMessageReadDetailTabType)tabType isEmpty:(BOOL)isEmpty;

/// 更新空视图文字
/// - Parameter text: 文字内容
- (void)updateEmptyViewText:(NSString *)text;

/// 刷新指定 Tab 的列表数据
/// - Parameters:
///   - tabType: Tab 类型
///   - hasMoreData: 是否还有更多数据
- (void)reloadDataForTabType:(RCMessageReadDetailTabType)tabType hasMoreData:(BOOL)hasMoreData;

/// 根据 tableView 获取对应的 Tab 类型
/// - Parameter tableView: UITableView 实例
/// - Returns: Tab 类型
- (RCMessageReadDetailTabType)tabTypeForTableView:(UITableView *)tableView;

@end

NS_ASSUME_NONNULL_END

