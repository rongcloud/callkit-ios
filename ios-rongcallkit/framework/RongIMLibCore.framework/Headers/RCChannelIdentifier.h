//
//  RCChannelIdentifier.h
//  RongIMLibCore
//
//  Created by RobinCui on 2023/1/3.
//  Copyright © 2023 RongCloud. All rights reserved.
//

//#import <RongIMLibCore/RongIMLibCore.h>
#import "RCConversationIdentifier.h"
NS_ASSUME_NONNULL_BEGIN
/*!
 @since 5.4.0
 */
@interface RCChannelIdentifier : RCConversationIdentifier
/*!
 channel ID
 */
@property (nonatomic, copy) NSString *channelId;

@end

NS_ASSUME_NONNULL_END
