//
//  RCMessageReadDetailCellViewModel.h
//  RongIMKit
//
//  Created by Lang on 10/15/25.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RongIMLibCore.h>

NS_ASSUME_NONNULL_BEGIN

/// 已读回执详情用户 Cell ViewModel
/// - Since: 5.20.0
@interface RCMessageReadDetailCellViewModel : NSObject

/// 用户信息
@property (nonatomic, strong, readonly) RCUserInfo *userInfo;

/// 已读时间戳（0 表示未显示时间）
@property (nonatomic, assign, readonly) long long readTime;

/// 已读时间，经过格式化后的字符串
@property (nonatomic, copy, readonly) NSString *displayReadTime;

/// 单元格高度
@property (nonatomic, assign, readonly) CGFloat cellHeight;

/// 实例化 ViewModel
/// - Parameters userInfo: 用户信息
/// - Parameters readTime: 已读时间戳
/// - Parameters conversationType: 会话类型
/// - Parameters targetId: 目标 ID
- (instancetype)initWithUserInfo:(RCUserInfo *)userInfo
                        readTime:(long long)readTime;

@end

NS_ASSUME_NONNULL_END
