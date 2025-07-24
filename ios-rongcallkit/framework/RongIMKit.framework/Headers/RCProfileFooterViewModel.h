//
//  RCProfileFooterViewModel.h
//  RongIMKit
//
//  Created by zgh on 2024/8/22.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RCBaseViewModel.h"
#import "RCButtonItem.h"
@class RCProfileFooterViewModel;
NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, RCProfileFooterViewType) {
    RCProfileFooterViewTypeAddFriend,
    RCProfileFooterViewTypeChat,
    RCProfileFooterViewTypeGroupOwner,
    RCProfileFooterViewTypeGroupMember
};

@protocol RCProfileFooterViewModelDelegate <NSObject>

@optional

/// 即将加载数据源
///
/// - Parameters viewModel: viewModel
/// - Parameters  profileList: 当前数据源
/// - Returns: App处理后的数据源
///
///   - Since: 5.12.0
- (nullable NSArray <RCButtonItem *> *)profileFooterViewModel:(RCProfileFooterViewModel *)viewModel
                                     willLoadButtonItemsViewModels:(NSArray <RCButtonItem *> *)models;

@end

/// 资料页 footerViewModel
/// - Since: 5.12.0
@interface RCProfileFooterViewModel : RCBaseViewModel

@property (nonatomic, weak, readonly) UIViewController *responder;

/// 代理
@property (nonatomic, weak) id<RCProfileFooterViewModelDelegate> delegate;

/// footer type
@property (nonatomic, assign, readonly) RCProfileFooterViewType type;

/// 目标 Id
@property (nonatomic, copy, readonly) NSString *targetId;

/// 是否验证好友
@property (nonatomic, assign) BOOL verifyFriend;

/// 实例化 RCProfileFooterViewModel
///
/// - Parameters responder: 当前 VC
/// - Parameters type: footer type
/// - Parameters targetId: 目标 Id
- (instancetype)initWithResponder:(UIViewController *)responder
                             type:(RCProfileFooterViewType)type
                         targetId:(NSString *)targetId;

/// 加载 view
///
/// - Returns: view
- (UIView *)loadView;

@end

NS_ASSUME_NONNULL_END
