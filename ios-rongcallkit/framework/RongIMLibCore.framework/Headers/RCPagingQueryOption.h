//
//  RCPagingQueryOption.h
//  RongIMLibCore
//
//  Created by Lang on 2024/7/19.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCPagingQueryOption : NSObject

/// 分页标识，获取第一页时传 nil，第二页传入 SDK 返回第一页数据时携带的 pageToken
@property (nonatomic, copy, nullable) NSString *pageToken;

/// 每页条数，以具体接口标注的数量为准。
@property (nonatomic, assign) NSUInteger count;

/// 是否正序查询，默认为 NO 倒序返回，设置 YES 为 正序返回
@property (nonatomic, assign) BOOL order;

@end

NS_ASSUME_NONNULL_END
