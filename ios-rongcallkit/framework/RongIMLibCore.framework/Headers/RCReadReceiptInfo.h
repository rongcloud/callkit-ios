//
//  RCReadReceiptInfo.h
//  RongIMLib
//
//  Created by 杜立召 on 16/8/29.
//  Copyright © 2016年 RongCloud. All rights reserved.
//
#import "RCStatusDefine.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCReadReceiptInfo : NSObject

/*!
 是否需要回执消息
 */
@property (nonatomic, assign) BOOL isReceiptRequestMessage;

/**
 是否已经发送回执
 */
@property (nonatomic, assign) BOOL hasRespond;

/*!
 发送回执的用户 ID 列表
 */
@property (nonatomic, strong, nullable) NSMutableDictionary *userIdList;

@end

NS_ASSUME_NONNULL_END
