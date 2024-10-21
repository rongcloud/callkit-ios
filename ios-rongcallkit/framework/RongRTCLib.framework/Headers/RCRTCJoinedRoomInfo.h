//
//  RCRTCJoinedRoomInfo.h
//  RongRTCLib
//
//  Created by RongCloud on 2021/8/13.
//  Copyright © 2021 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 已经加入房间信息
 */
@interface RCRTCJoinedRoomInfo : NSObject

/*!
 设备ID
 */
@property (nonatomic, strong) NSString *deviceId;

/*!
 房间号
 */
@property (nonatomic, strong) NSString *roomId;

/*!
 房间加入时间 (毫秒)
 */
@property (nonatomic, assign) long long joinTime;

@end

NS_ASSUME_NONNULL_END
