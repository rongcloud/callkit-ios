//
//  RCUserProfileTextCellViewModel.h
//  RongUserProfile
//
//  Created by zgh on 2024/8/16.
//

#import "RCProfileCellViewModel.h"
#import <UIKit/UIKit.h>
#import <RongIMLibCore/RongIMLibCore.h>
NS_ASSUME_NONNULL_BEGIN
/// cell 类型
typedef NS_ENUM(NSUInteger, RCUProfileCellType) {
    /// 图片 cell
    RCUProfileCellTypeImage,
    /// 文本 cell
    RCUProfileCellTypeText,
};

/// 资料页通用 cellViewModel
/// - Since: 5.12.0
@interface RCProfileCommonCellViewModel : RCProfileCellViewModel

/// 标题
@property (nonatomic, copy) NSString *title;

/// 详情
@property (nonatomic, copy, nullable) NSString *detail;

/// 会话类型
@property (nonatomic, assign) RCConversationType conversationType;

/// 隐藏箭头
@property (nonatomic, assign) BOOL hiddenArrow;

/// 隐藏分割线
@property (nonatomic, assign) BOOL hiddenSeparatorLine;

/// cell 类型
@property (nonatomic, assign) RCUProfileCellType type;

/// 注册 cell
+ (void)registerCellForTableView:(UITableView *)tableView;

/// 实例化 RCProfileCommonCellViewModel
///
/// - Parameters type: cell 类型
/// - Parameters title: 标题
/// - Parameters detail: 详情
- (instancetype)initWithCellType:(RCUProfileCellType)type
                           title:(NSString *)title
                          detail:(nullable NSString *)detail;
@end

NS_ASSUME_NONNULL_END
