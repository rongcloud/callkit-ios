//
//  RCCallAISummaryMessage.m
//  RongCallKit
//
//  Created by RongCloud on 25/12/8.
//  Copyright © 2025年 RongCloud. All rights reserved.
//

#import "RCCallAISummaryMessage.h"
#import "RCCallKitUtility.h"

@implementation RCCallAISummaryMessage

///初始化
- (instancetype)initWithTaskId:(NSString *)taskId
                        callId:(NSString *)callId
                     startTime:(NSTimeInterval)startTime {
    self = [super init];
    if (self) {
        self.taskId = taskId;
        self.callId = callId;
        self.startTime = startTime;
    }
    return self;
}

///消息是否存储，是否计入未读数
+ (RCMessagePersistent)persistentFlag {
    return MessagePersistent_ISCOUNTED;
}

///将消息内容编码成json
- (NSData *)encode {
    NSMutableDictionary *dataDict = [NSMutableDictionary dictionary];
    if (self.taskId) {
        [dataDict setObject:self.taskId forKey:@"taskId"];
    }
    if (self.callId) {
        [dataDict setObject:self.callId forKey:@"callId"];
    }
    [dataDict setObject:@(self.startTime) forKey:@"startTime"];
    return [NSJSONSerialization dataWithJSONObject:dataDict options:kNilOptions error:nil];
}

///将json解码生成消息内容
- (void)decodeWithData:(NSData *)data {
    if (data) {
        NSError *error = nil;
        NSDictionary *dictionary = [NSJSONSerialization JSONObjectWithData:data options:kNilOptions error:&error];

        if (!error && dictionary) {
            self.taskId = [dictionary objectForKey:@"taskId"];
            self.callId = [dictionary objectForKey:@"callId"];
            self.startTime = [[dictionary objectForKey:@"startTime"] doubleValue];
        }
    }
}

///消息的类型名
+ (NSString *)getObjectName {
    return RCCallAISummaryMessageTypeIdentifier;
}

///内容摘要
- (NSString *)conversationDigest {
    return RCCallKitLocalizedString(@"ai_summary_completed");
}

- (NSString *)description {
    NSDictionary *dic = @{
        @"taskId":self.taskId ?: @"",
        @"callId":self.callId ?: @""
    };
    return [NSString stringWithFormat:@"%@",dic];
}

@end
