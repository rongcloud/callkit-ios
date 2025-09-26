//
//  RCEditedMessageDraft.h
//  RongIMLibCore
//
//  Created by huan xu on 2025/9/8.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/// - Since 5.28.0
@interface RCEditedMessageDraft : NSObject
/// 消息唯一标识(必填参数)
@property (nonatomic, copy) NSString *messageUId;
/// 草稿内容(可选参数)
@property (nonatomic, copy, nullable) NSString *content;
@end

NS_ASSUME_NONNULL_END
