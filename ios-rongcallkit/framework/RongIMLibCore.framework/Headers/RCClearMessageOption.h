//
//  RCClearMessageOption.h
//  RongIMLibCore
//
//  Created by chinaspx on 2023/9/18.
//  Copyright © 2023 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCStatusDefine.h>

NS_ASSUME_NONNULL_BEGIN

/// - Since: 5.6.7
@interface RCClearMessageOption : NSObject

/// 会话类型
@property (nonatomic, assign) RCConversationType type;
/// 会话 ID
@property (nonatomic, copy) NSString *targetId;
/// channel ID
@property (nonatomic, copy) NSString *channelId;
/// timestamp 时间戳（毫秒）
@property (nonatomic, assign) long long timestamp;

@end

NS_ASSUME_NONNULL_END
