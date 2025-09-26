//
//  RCMentionedStringRangeInfo.h
//  RongExtensionKit
//
//  Created by 杜立召 on 16/7/13.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RCMentionedStringRangeInfo : NSObject <NSCoding>

/// @用户Id
@property (nonatomic, strong) NSString *userId;

/// 文本消息的内容
@property (nonatomic, strong) NSString *content;

/// 文本消息的range
@property (nonatomic, assign) NSRange range;

- (NSString *)encodeToString;

- (instancetype)initWithDecodeString:(NSString *)mentionedInfoString;

@end
