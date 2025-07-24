//
//  RCReadReceiptUsersOption.h
//  RongIMLibCore
//
//  Created by shuai shao on 2025/4/15.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCStatusDefine.h>

NS_ASSUME_NONNULL_BEGIN

/// 已读回执状态。
typedef NS_ENUM(NSInteger, RCReadReceiptStatus) {
    RCReadReceiptStatusResponse = 0,
    RCReadReceiptStatusUnResponse,
};

/// 已读回执查询条件。
///
/// - Since: 5.20.0
@interface RCReadReceiptUsersOption : NSObject

/// 分页 Token，为空时，会从第一页开始获取。
@property (nonatomic, copy, nullable) NSString *pageToken;

/// 分页数量，范围为 [1, 100]。
@property (nonatomic, assign) NSInteger pageCount;

/// 排序，默认按已读时间倒序排序。
@property (nonatomic, assign) RCOrder order;

/// 已读回执状态。
@property (nonatomic, assign) RCReadReceiptStatus readReceiptStatus;

@end

NS_ASSUME_NONNULL_END
