//
//  RCMessageReadDetailViewConfig.h
//  RongIMKit
//
//  Created by Lang on 10/15/25.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/// 消息阅读状态详情页配置
@interface RCMessageReadDetailViewConfig : NSObject

/// Tab 高度（默认 42）
@property (nonatomic, assign) CGFloat tabHeight;

/// 分页大小（默认 100）支持范围为 [1, 100]。
@property (nonatomic, assign) NSInteger pageSize;

@end

NS_ASSUME_NONNULL_END

