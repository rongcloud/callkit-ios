//
//  RCCallBaseViewController+Private.h
//  RongCallKit
//
//  Created by RongCloud on 25/12/5.
//  Copyright © 2025年 RongCloud. All rights reserved.
//

#import "RCCallBaseViewController.h"

@interface RCCallBaseViewController (Private)

- (instancetype)initWithIncomingCall:(RCCallSession *)callSession;
- (instancetype)initWithOutgoingCall:(RCConversationType)conversationType
                            targetId:(NSString *)targetId
                           mediaType:(RCCallMediaType)mediaType
                          userIdList:(NSArray *)userIdList;
- (instancetype)initWithOutgoingCrossCall:(RCConversationType)conversationType
                                 targetId:(NSString *)targetId
                                mediaType:(RCCallMediaType)mediaType
                               userIdList:(NSArray *)userIdList;
- (instancetype)initWithActiveCall:(RCCallSession *)callSession;

- (void)hangupButtonClicked;
- (void)inviteUserButtonClicked;

@end
