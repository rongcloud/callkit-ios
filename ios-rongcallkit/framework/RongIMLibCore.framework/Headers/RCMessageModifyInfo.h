//
//  RCMessageModifyInfo.h
//  RongIMLibCore
//
//  Created by shuai shao on 2025/7/17.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 修改消息内容的更新状态。
///
/// @since 5.26.0
typedef NS_ENUM(NSInteger, RCMessageModifyStatus) {
    /// 更新成功。
    RCMessageModifyStatusSuccess = 0,
    /// 更新中。
    RCMessageModifyStatusUpdating = 1,
    /// 更新失败。
    RCMessageModifyStatusFailed = 2,
};

@class RCMessageContent;

/// 消息内容修改信息。
///
/// @since 5.26.0
@interface RCMessageModifyInfo : NSObject

/// 消息修改时间，单位毫秒。
///
/// - Note: 默认为 0，如果大于 0，表示消息被修改过。如果多次修改，以最后一次修改时间为准。
@property (nonatomic, assign) long timestamp;

/// 消息修改的内容。
///
/// - Note: 当 `status` 为 `RCMessageModifyStatusUpdating` 和 `RCMessageModifyStatusFailed` 时有值。
@property (nonatomic, strong, nullable) RCMessageContent *content;

/// 消息修改的更新状态。
@property (nonatomic, assign) RCMessageModifyStatus status;

@end

NS_ASSUME_NONNULL_END
