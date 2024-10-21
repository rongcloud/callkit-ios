//
//  RCConversationStatusView.h
//  RongIMKit
//
//  Created by 岑裕 on 16/9/15.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCConversationModel.h"
#import <UIKit/UIKit.h>
#import "RCBaseImageView.h"
#import "RCBaseView.h"
@interface RCConversationStatusView : RCBaseView

@property (nonatomic, strong) RCBaseImageView *conversationNotificationStatusView;

@property (nonatomic, strong) RCBaseImageView *messageReadStatusView;

- (void)updateReadStatus:(RCConversationModel *)model;

- (void)updateNotificationStatus:(RCConversationModel *)model;

- (void)resetDefaultLayout:(RCConversationModel *)reuseModel;

@end
