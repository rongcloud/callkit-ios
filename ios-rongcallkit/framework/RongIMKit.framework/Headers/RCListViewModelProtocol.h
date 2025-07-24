//
//  RCListViewModelProtocol.h
//  RongUserProfile
//
//  Created by RobinCui on 2024/8/16.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/// 列表响应器
/// - Since: 5.12.0
@protocol RCListViewModelResponder <NSObject>
@optional
/// 刷新列表
///
/// - Parameters isEmpty: 是否空
- (void)reloadData:(BOOL)isEmpty;

/// 刷新结束
///
/// - Parameters success: 是否成功
/// - Parameters tips: 提示信息
- (void)refreshingFinished:(BOOL)success withTips:(NSString *)tips;

/// 展示提示信息
///
/// - Parameters tips: 提示信息
- (void)showTips:(NSString *)tips;

/// 开始加载
- (void)startLoading;

/// 开始加载
- (void)endLoading;

/// 更新 item
///
/// - Parameters indexPath: indexPath
- (void)updateItem:(NSIndexPath *)indexPath;

/// 当前 VC
/// - Returns: ViewController
- (UIViewController *)currentViewController;

/// 更新 title
- (void)updateTitle:(NSString *)title;

/// 加载尾部视图
- (void)reloadFooterView;

@end

/// 列表协议
/// - Since: 5.12.0
@protocol RCListViewModelProtocol <NSObject>

@optional
/// 注册 cell
///
/// - Parameters tableView: tableView
- (void)registerCellForTableView:(UITableView *)tableView;

/// 点击 cell
///
/// - Parameters viewController: viewController
/// - Parameters tableView: tableView
/// - Parameters indexPath: indexPath
- (void)viewController:(UIViewController*)viewController
             tableView:(UITableView *)tableView
          didSelectRow:(NSIndexPath *)indexPath;

/// 返回 cell 高度
///
/// - Parameters tableView: tableView
/// - Parameters indexPath: indexPath
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath;

/// 分区数量
///
/// - Returns: 分区数量
- (NSInteger)numberOfSections;

/// 分区内Item数量
///
/// - Parameters section: section
/// - Returns: 分区数量
- (NSInteger)numberOfRowsInSection:(NSInteger)section;

/// 返回cell
///
/// - Parameters tableView: tableView
/// - Parameters indexPath: indexPath
/// - Returns: cell
- (UITableViewCell *)tableView:(UITableView *)tableView
         cellForRowAtIndexPath:(NSIndexPath *)indexPath;

/// 头部视图高度
///
/// - Parameters section: section
/// - Returns: 头部视图高度
- (CGFloat)heightForHeaderInSection:(NSInteger)section;

/// 头部视图
/// 
/// - Parameters tableView: tableView
/// - Parameters section: section
/// - Returns: 分区数量
- (nullable UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section;
@end

NS_ASSUME_NONNULL_END
