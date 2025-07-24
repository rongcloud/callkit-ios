//
//  RCReceivedStatusInfo.h
//  RongIMLibCore
//
//  Created by chinaspx on 2023/11/16.
//  Copyright © 2023 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCReceivedStatusInfo : NSObject

/// 是否已读
@property (nonatomic, assign, readonly) BOOL isRead;
/// 是否已听，仅用于语音消息
@property (nonatomic, assign, readonly) BOOL isListened;
/// 是否已下载
@property (nonatomic, assign, readonly) BOOL isDownloaded;

/// 该消息已被同时在线或之前登录的其他设备接收。只要任何其他设备先收到该消息，当前设备该状态值就会为 YES。
@property (nonatomic, assign, readonly) BOOL isRetrieved;


/// 默认构造
/// - Parameter receivedStatus: DB 读取的状态值；传 0 表示 未读。
///
/// 构造未读状态，代码如下：
/// RCReceivedStatusInfo *statusInfo = [[RCReceivedStatusInfo alloc] initWithReceivedStatus:0];
///
/// 构造已读状态，代码如下：
/// RCReceivedStatusInfo *statusInfo = [[RCReceivedStatusInfo alloc] initWithReceivedStatus:0];
/// [statusInfo markAsRead];
///
- (instancetype)initWithReceivedStatus:(NSUInteger)receivedStatus NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)new NS_UNAVAILABLE;

/// 标记为已读
- (void)markAsRead;

/// 标记为已听
- (void)markAsListened;

/// 标记为已下载
- (void)markAsDownloaded;

/// 标记为被其他登录的多端收取过的
- (void)markAsRetrieved;

@end

NS_ASSUME_NONNULL_END
