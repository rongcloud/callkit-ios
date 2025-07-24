//
//  RCFriendApplyAlertView.h
//  RongIMKit
//
//  Created by RobinCui on 2024/8/30.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCBaseView.h"
#import "RCTextView.h"
NS_ASSUME_NONNULL_BEGIN

typedef void(^RCApplyFriendAlertBlock)(NSString *);
/// 申请好友弹窗
/// - Since: 5.12.0
@interface RCApplyFriendAlertView : RCBaseView

/// 展示申请好友弹窗
/// - Parameters title: 标题
/// - Parameters placeholder: 占位字符
/// - Parameters completion: 结果回调
+ (void)showAlert:(NSString *)title
      placeholder:(NSString *)placeholder
       completion:(RCApplyFriendAlertBlock)completion;

/// 展示申请好友弹窗
/// - Parameters title: 标题
/// - Parameters placeholder: 占位字符
/// - Parameters limit: 字符长度限制
/// - Parameters completion: 结果回调
+ (void)showAlert:(NSString *)title
      placeholder:(NSString *)placeholder
      lengthLimit:(NSInteger)limit
       completion:(RCApplyFriendAlertBlock)completion;
@end

NS_ASSUME_NONNULL_END
