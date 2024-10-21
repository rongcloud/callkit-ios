//
//  RCPagingQueryResult.h
//  RongIMLibCore
//
//  Created by Lang on 2024/7/30.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCPagingQueryResult<T> : NSObject

/// 分页标识
/// - 获取第一页时传 nil，第二页传入 SDK 返回第一页数据时携带的 pageToken。
/// - 当 SDK 返回 `pageToken` 为空字符串时，表示没有更多数据了。
@property (nonatomic, copy, readonly) NSString *pageToken;

/// 查询结果总数
/// 如返回 -1 则表示此次查询不支持返回总数
/// - Note: 这个总数是所有分页数据的总和。
@property (nonatomic, assign, readonly) NSInteger totalCount;

/// 当前分页的数据
@property (nonatomic, copy, readonly) NSArray<T> *data;

@end

NS_ASSUME_NONNULL_END
