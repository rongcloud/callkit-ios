//
//  RCProfileSwitchCellViewModel.h
//  RongIMKit
//
//  Created by zgh on 2024/9/2.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import "RCProfileCellViewModel.h"

NS_ASSUME_NONNULL_BEGIN
/// 资料页开关 cellViewModel
/// - Since: 5.12.0
@interface RCProfileSwitchCellViewModel : RCProfileCellViewModel

/// 名称
@property (nonatomic, copy) NSString *title;

/// 是否开启
@property (nonatomic, assign) BOOL switchOn;

/// 点击回调
@property (nonatomic, copy) void (^switchValueChanged)(BOOL on);

@end

NS_ASSUME_NONNULL_END
