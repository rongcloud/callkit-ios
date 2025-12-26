//
//  RCApplyFriendCellViewModel.h
//  RongIMKit
//
//  Created by RobinCui on 2024/8/23.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RongIMLibCore/RongIMLibCore.h>
#import "RCCellViewModelProtocol.h"
#import "RCBaseCellViewModel.h"
#import "RCListViewModelProtocol.h"

NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(NSInteger, RCFriendApplyCellStyle) {
    RCFriendApplyCellStyleNone, // 无样式
    RCFriendApplyCellStyleNormal, // 常规
    RCFriendApplyCellStyleFolder, // 折叠
    RCFriendApplyCellStyleExpand  // 展开
};


/// 好友申请列表 cellViewModel
/// - Since:5.12.0
@interface RCApplyFriendCellViewModel : RCBaseCellViewModel<RCCellViewModelProtocol>

/// 申请信息
@property (nonatomic, strong) RCFriendApplicationInfo *application;

/// 样式
@property (nonatomic, assign) RCFriendApplyCellStyle style;

/// 初始化
- (instancetype)initWithApplicationInfo:(RCFriendApplicationInfo *)application;

/// 接受申请
- (void)approveApplication;

/// 拒绝申请
- (void)rejectApplication;

/// 展开备注
- (void)expandRemark;

/// cell 高度
- (CGFloat)cellHeight;

/// 注册 cell
+ (void)registerCellForTableView:(UITableView *)tableView;


/// 根据备注内容的尺寸确定是否显示"展开按钮"
/// - Parameters:
///   - size: 当前size
///   - natureSize: 实际size
- (BOOL)shouldHideExpandButton:(CGSize)size natureSize:(CGSize)natureSize;
/// 绑定响应者
- (void)bindResponder:(UIViewController <RCListViewModelResponder>*)responder;

/// header 高度
/// - Parameters:
///   - tableView: tableView
///   - indexPath: indexPath
///   - Returns: action 列表
- (NSArray<UITableViewRowAction *> *)tableView:(UITableView *)tableView
                  editActionsForRowAtIndexPath:(NSIndexPath *)indexPath  
                                    completion:(void(^)(RCErrorCode errorCode))completion;
@end

NS_ASSUME_NONNULL_END
