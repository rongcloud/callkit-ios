//
//  RCAdapterCenter.h
//  RongIMKit
//
//  Created by zgh on 2024/9/3.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// viewModel 适配中心
/// - Since: 5.12.0
@interface RCViewModelAdapterCenter : NSObject

/// 注册代理给某个类
/// 
/// - Parameter delegate:           代理对象
/// - Parameter cls:    类
/// - Returns: 是否成功
+ (BOOL)registerDelegate:(id _Nullable)delegate forViewModelClass:(Class)cls;

/// 移除类代理
///
/// - Parameter cls:    类
/// - Returns: 是否成功
+ (BOOL)removeDelegateForViewModelClass:(Class)cls;

/// 获取类代理
///
/// - Parameter cls:    类
+ (id)delegateForViewModelClass:(Class)cls;

@end

NS_ASSUME_NONNULL_END
