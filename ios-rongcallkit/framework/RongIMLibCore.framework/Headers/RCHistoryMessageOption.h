//
//  RCHistoryMessageOption.h
//  RongIMLibCore
//
//  Created by 张改红 on 2021/4/20.
//  Copyright © 2021 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

/// 拉取顺序
typedef NS_ENUM(NSUInteger, RCHistoryMessageOrder) {
    /// 降序
    RCHistoryMessageOrderDesc = 0,
    /// 升序
    RCHistoryMessageOrderAsc,
};

@interface RCHistoryMessageOption : NSObject

/// 起始的消息发送时间戳，毫秒。
/// 默认 0
@property (nonatomic, assign) long long recordTime;

/// 需要获取的消息数量，1 < count <= 100
/// 默认 0
@property (nonatomic, assign) NSInteger count;

/// 拉取顺序
///
/// - RCHistoryMessageOrderDesc：降序，结合传入的时间戳参数，获取 recordtime 之前的消息
/// - RCHistoryMessageOrderAsc：升序，结合传入的时间戳参数，获取 recordtime 之后的消息
/// 默认降序
@property (nonatomic, assign) RCHistoryMessageOrder order;
@end
