//
//  RCGroupReadReceiptInfoV2.h
//  RongIMLibCore
//
//  Created by 张改红 on 2021/3/9.
//  Copyright © 2021 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class RCGroupMessageReaderV2;


@interface RCReadReceiptInfoV4 : NSObject

/// 是否已经发送回执
@property (nonatomic, assign) BOOL hasRespond;

/// 发送回执的用户 ID 列表
@property (nonatomic, strong, nullable) NSArray<RCGroupMessageReaderV2 *> *readerList;

/// 已读人数
@property (nonatomic, assign) int readCount;

/// 群内总人数
@property (nonatomic, assign) int totalCount;


@end

@interface RCGroupReadReceiptInfoV2 : RCReadReceiptInfoV4
@end
NS_ASSUME_NONNULL_END
