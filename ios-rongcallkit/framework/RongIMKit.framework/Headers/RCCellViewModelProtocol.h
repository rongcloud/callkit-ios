//
//  RCCellViewModelProtocol.h
//  RongUserProfile
//
//  Created by RobinCui on 2024/8/16.
//

#import <UIKit/UIKit.h>


NS_ASSUME_NONNULL_BEGIN
typedef void(^RCPermanentCellViewModelBlock)(UIViewController *);
/// cell 协议
@protocol RCCellViewModelProtocol <NSObject>
@optional

/// 返回 cell
///
/// - Parameters tableView: tableView
/// - Parameters indexPath: indexPath
/// - Returns: cell
- (UITableViewCell *)tableView:(UITableView *)tableView
         cellForRowAtIndexPath:(NSIndexPath *)indexPath;

/// cell 高度
///
/// - Parameters tableView: tableView
/// - Parameters indexPath: indexPath
/// - Returns: cell 高度
- (CGFloat)tableView:(nonnull UITableView *)tableView heightForRowAtIndexPath:(nonnull NSIndexPath *)indexPath;

/// 点击 cell
///
/// - Parameters vc: 当前VC
- (void)itemDidSelectedByViewController:(UIViewController *)vc;
@end

NS_ASSUME_NONNULL_END
