//
//  RCMessageCountDetail.h
//  RongIMLibCore
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 某个本地自然日内的消息数量。
@interface RCMessageCountDetail : NSObject

/// 协议栈查询时系统时区对应日期零点的 Unix 毫秒时间戳。
@property (nonatomic, assign) long long dateMs;

/// 该日期内的本地消息数量。
@property (nonatomic, assign) NSInteger messageCount;

@end

NS_ASSUME_NONNULL_END
