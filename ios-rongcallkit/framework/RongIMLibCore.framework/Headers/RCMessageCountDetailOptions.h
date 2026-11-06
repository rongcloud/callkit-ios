//
//  RCMessageCountDetailOptions.h
//  RongIMLibCore
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 按本地自然日查询会话消息数量的时间范围。
@interface RCMessageCountDetailOptions : NSObject

/// 查询范围起点，Unix 毫秒时间戳，包含。允许为自然日内任意时刻。
@property (nonatomic, assign) long long startTime;

/// 查询范围终点，Unix 毫秒时间戳，不包含。必须大于 startTime，允许为自然日内任意时刻。
@property (nonatomic, assign) long long endTime;

@end

NS_ASSUME_NONNULL_END
