//
//  RCMessageReadDetailViewModel.h
//  RongIMKit
//
//  Created by Lang on 10/15/25.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RongIMLibCore.h>
#import "RCMessageReadDetailViewConfig.h"
#import "RCMessageModel.h"
#import "RCMessageReadDetailCellViewModel.h"
#import "RCMessageReadDetailDefine.h"

NS_ASSUME_NONNULL_BEGIN

/// 已读回执详情 ViewModel 响应器
/// - Since: 5.20.0
@protocol RCMessageReadDetailViewModelResponder <NSObject>

@optional

/// 刷新列表
/// - Parameters isEmpty: 是否为空
/// - Parameters tabType: Tab 类型
- (void)updateUserListForTabType:(RCMessageReadDetailTabType)tabType
                         isEmpty:(BOOL)isEmpty
                     hasMoreData:(BOOL)hasMoreData;

/// 当前 ViewController
/// - Returns: 当前 ViewController
- (UIViewController *)currentViewController;

/// 更新 Tab 已读/未读数量
/// - Parameters readCount: 已读数量
/// - Parameters unreadCount: 未读数量
- (void)updateTabViewWithReadCount:(NSInteger)readCount unreadCount:(NSInteger)unreadCount;

@end

/// 已读回执详情列表 ViewModel
/// - Since: 5.20.0
@interface RCMessageReadDetailViewModel : NSObject

/// 响应器
@property (nonatomic, weak) id<RCMessageReadDetailViewModelResponder> responder;

/// 消息模型
@property (nonatomic, strong, readonly) RCMessageModel *messageModel;

/// 配置
@property (nonatomic, strong, readonly) RCMessageReadDetailViewConfig *config;

/// 当前 Tab 类型
@property (nonatomic, assign, readonly) RCMessageReadDetailTabType currentTabType;

/// 已读用户列表
@property (nonatomic, strong, readonly) NSMutableArray<RCMessageReadDetailCellViewModel *> *readUserList;

/// 未读用户列表
@property (nonatomic, strong, readonly) NSMutableArray<RCMessageReadDetailCellViewModel *> *unreadUserList;

/// 初始化 ViewModel
/// - Parameters messageModel: 消息模型
/// - Parameters config: 配置
- (instancetype)initWithMessageModel:(RCMessageModel *)messageModel
                              config:(nullable RCMessageReadDetailViewConfig *)config;

/// 绑定响应器
/// - Parameters responder: 响应器
- (void)bindResponder:(id<RCMessageReadDetailViewModelResponder>)responder;

/// 切换 Tab
/// - Parameters tabType: Tab 类型
- (void)switchTabToType:(RCMessageReadDetailTabType)tabType;

/// 获取数据
- (void)loadData;

/// 分页获取更多数据
- (void)loadMoreData;

/// 获取指定 Tab 的 Section 数
/// - Parameters:
///   - tabType: Tab 类型
/// - Returns: Section 数
- (NSInteger)numberOfSectionsForTabType:(RCMessageReadDetailTabType)tabType;

/// 获取指定 Tab 的行数
/// - Parameters:
///   - tabType: Tab 类型
///   - section: Section 索引
/// - Returns: 行数
- (NSInteger)numberOfRowsForTabType:(RCMessageReadDetailTabType)tabType inSection:(NSInteger)section;

/// 获取指定 Tab 和索引的 CellViewModel
/// - Parameters:
///   - tabType: Tab 类型
///   - index: 索引
/// - Returns: CellViewModel，如果索引越界返回 nil
- (RCMessageReadDetailCellViewModel *)cellViewModelForTabType:(RCMessageReadDetailTabType)tabType atIndex:(NSInteger)index;

/// 获取指定 Tab 和索引的 Cell 高度
/// - Parameters:
///   - tabType: Tab 类型
///   - index: 索引
/// - Returns: Cell 高度，如果索引越界返回 0
- (CGFloat)cellHeightForTabType:(RCMessageReadDetailTabType)tabType atIndex:(NSInteger)index;

@end

NS_ASSUME_NONNULL_END
