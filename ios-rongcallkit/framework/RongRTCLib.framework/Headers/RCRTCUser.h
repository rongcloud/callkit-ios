//
//  RCRTCStream.h
//  RongRTCLib
//
//  Created by RongCloud on 2019/1/2.
//  Copyright © 2019 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RCRTCLibDefine.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 列席会议的成员信息
 */
@interface RCRTCUser : NSObject

/*!
 请勿调用初始化方法
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
 请勿调用初始化方法
 */
- (instancetype)new NS_UNAVAILABLE;

/*!
 用户 ID
 */
@property (nonatomic, copy, readonly) NSString *userId;

/*!
 用户扩展信息
 */
@property (nonatomic, copy, readonly, nullable) NSString *extra;

@end

NS_ASSUME_NONNULL_END
