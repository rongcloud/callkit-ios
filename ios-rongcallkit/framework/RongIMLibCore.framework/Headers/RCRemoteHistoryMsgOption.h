//
//  RCRemoteHistoryMsgOption.h
//  RongIMLib
//
//  Created by Zhaoqianyu on 2019/7/31.
//  Copyright © 2019 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

/// 拉取顺序
typedef NS_ENUM(NSUInteger, RCRemoteHistoryOrder) {
    /// 降序
    RCRemoteHistoryOrderDesc = 0,
    /// 升序
    RCRemoteHistoryOrderAsc,
};

NS_ASSUME_NONNULL_BEGIN

/// RCIMClient - getRemoteHistoryMessage 接口对应的参数选项
@interface RCRemoteHistoryMsgOption : NSObject

/// 起始的消息发送时间戳，毫秒 默认 0
@property (nonatomic, assign) long long recordTime;

/// 需要获取的消息数量，1 < count <= 100 默认 0
@property (nonatomic, assign) NSInteger count;

/// 拉取顺序
///
/// RCRemoteHistoryOrderDesc：降序，结合传入的时间戳参数，获取比时间戳小（早）的消息；
/// RCRemoteHistoryOrderAsc：升序，结合传入的时间戳参数，获取比时间戳大的消息。
/// 默认降序。
@property (nonatomic, assign) RCRemoteHistoryOrder order;

/// 是否需要排重
/// YES: 拉取回来的消息全部返回
/// NO: 拉取回来的消息只返回本地数据库中不存在的
/// 默认 NO
@property (nonatomic, assign) BOOL includeLocalExistMessage;

@end

NS_ASSUME_NONNULL_END
