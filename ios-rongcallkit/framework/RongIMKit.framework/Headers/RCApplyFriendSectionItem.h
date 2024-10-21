//
//  RCApplyFriedSectionItem.h
//  RongIMKit
//
//  Created by RobinCui on 2024/8/26.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
typedef BOOL(^RCFriendApplyItemFilterBlock)(id _Nonnull obj, NSInteger start, NSInteger end, BOOL * _Nonnull stop);

typedef NSComparisonResult(^RCFriedApplyItemCompareBlock)(id _Nonnull obj1, id _Nonnull obj2);

NS_ASSUME_NONNULL_BEGIN

@interface RCApplyFriendSectionItem : NSObject

// 开始时间(毫秒)
@property (nonatomic, assign) NSInteger timeStart;

/// 截止时间(毫秒)
@property (nonatomic, assign) NSInteger timeEnd;

/// 标题
@property (nonatomic, copy) NSString *title;

- (instancetype)initWithFilterBlock:(RCFriendApplyItemFilterBlock _Nullable)filterBlock
                       compareBlock:(RCFriedApplyItemCompareBlock _Nullable)compareBlock;

- (NSArray *)filterAndSortItems:(NSArray *)items;
- (BOOL)isValidSectionItem;

@end

NS_ASSUME_NONNULL_END
