//
//  RongIMKitExtensionModel.h
//  RongIMKit
//
//  Created by 岑裕 on 16/7/2.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMKit/RongIMKit.h>

typedef void (^RCConversationPluginItemTapBlock)();

@protocol RongIMKitExtensionModel <NSObject>

+ (instancetype)loadRongExtensionModel;

- (void)destroyModel;

- (void)registerMessageCell:(RCConversationType)conversationType
                   targetId:(NSString *)targetId
                      block:(void (^)(NSString *reuserIdentifier, Class cellClass))registerBlock;

- (BOOL)didHoldMessageCellLayout:(RCConversationType)conversationType
                        targetId:(NSString *)targetId
                  messageContent:(RCMessageContent *)messageContent;

- (NSString *)getMessageCellReuseIdentifier:(RCConversationType)conversationType
                                   targetId:(NSString *)targetId
                             messageContent:(RCMessageContent *)messageContent;

- (CGSize)getMessageCellSize:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
              messageContent:(RCMessageContent *)messageContent
          collectionViewSize:(CGSize)collectionViewSize;

- (BOOL)isMessageCellPortraitDisplayed:(RCConversationType)conversationType
                              targetId:(NSString *)targetId
                        messageContent:(RCMessageContent *)messageContent;

- (BOOL)didHoldMessageCellTapEvent:(RCConversationType)conversationType
                          targetId:(NSString *)targetId
                    messageContent:(RCMessageContent *)messageContent;

- (void)didTapMessageCell:(RCConversationType)conversationType
                 targetId:(NSString *)targetId
           messageContent:(RCMessageContent *)messageContent;

- (void)registerConversationPlugin:(RCConversationType)conversationType
                          targetId:(NSString *)targetId
                             block:(void (^)(UIImage *image, NSString *title,
                                             RCConversationPluginItemTapBlock tapBlock))registerBlock;

- (BOOL)didHoldReceivedMessageForKitUpdate:(RCMessage *)message;

- (BOOL)didHoldReceivedMessageForForegroudAlert:(RCMessage *)message;

- (BOOL)didHoldReceivedMessageForBackgroudNotification:(RCMessage *)message;

@end
