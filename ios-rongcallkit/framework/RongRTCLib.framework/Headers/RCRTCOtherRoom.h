//
//  RCRTCOtherRoom.h
//  RongRTCLib
//
//  Created by RongCloud on 2020/8/3.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RCRTCBaseRoom.h"
#import "RCRTCOtherRoomEventDelegate.h"

NS_ASSUME_NONNULL_BEGIN

@interface RCRTCOtherRoom : RCRTCBaseRoom

/*!
 副房间代理
 */
@property (nonatomic, weak, nullable) id<RCRTCOtherRoomEventDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
