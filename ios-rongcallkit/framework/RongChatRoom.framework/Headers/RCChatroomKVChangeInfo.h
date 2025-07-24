//
//  RCChatroomKVChangeInfo.h
//  RongChatRoom
//
//  Created by shuai shao on 2025/4/21.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCChatroomKVChangeInfo : NSObject

/// 房间 ID。
@property (nonatomic, copy, readonly) NSString *roomId;

/// 发生变化的 Key。
@property (nonatomic, copy, readonly) NSString *key;

/// 发生变化后的 Value。
@property (nonatomic, copy, readonly, nullable) NSString *value;

/// 是否是删除。
@property (nonatomic, assign, readonly) BOOL isDelete;

@end

NS_ASSUME_NONNULL_END
