//
//  RCCallKitExtensionModel.m
//  RongCallKit
//
//  Created by 岑裕 on 16/7/2.
//  Copyright © 2016年 Rong Cloud. All rights reserved.
//

#import "RCCallKitExtensionModel.h"
#import "RCCallDetailMessageCell.h"
#import "RCCallTipMessageCell.h"
#import "RCCall.h"
#import "RCCallKitUtility.h"

static NSString *const rcVoIPCallSummaryMessageCellIndentifier = @"rcVoIPCallSummaryMessageCellIndentifier";

@implementation RCCallKitExtensionModel

+ (instancetype)loadRongExtensionModel {
    [RCCall sharedRCCall];
    return [[RCCallKitExtensionModel alloc] init];
}

- (void)destroyModel {
    
}

- (void)registerMessageCell:(RCConversationType)conversationType
                   targetId:(NSString *)targetId
                      block:(void (^)(NSString *reuserIdentifier, Class cellClass))registerBlock {
    if (conversationType == ConversationType_PRIVATE) {
        registerBlock(rcVoIPCallSummaryMessageCellIndentifier, [RCCallDetailMessageCell class]);
    } else if (conversationType == ConversationType_GROUP || conversationType == ConversationType_DISCUSSION) {
        registerBlock(rcVoIPCallSummaryMessageCellIndentifier, [RCCallTipMessageCell class]);
    }
}

- (BOOL)didHoldMessageCellLayout:(RCConversationType)conversationType
                        targetId:(NSString *)targetId
                  messageContent:(RCMessageContent *)messageContent {
    if ([messageContent isKindOfClass:[RCCallSummaryMessage class]]) {
        return YES;
    } else {
        return NO;
    }
}

- (NSString *)getMessageCellReuseIdentifier:(RCConversationType)conversationType
                                   targetId:(NSString *)targetId
                             messageContent:(RCMessageContent *)messageContent {
    if ([messageContent isKindOfClass:[RCCallSummaryMessage class]]) {
        return rcVoIPCallSummaryMessageCellIndentifier;
    } else {
        return nil;
    }
}

- (CGSize)getMessageCellSize:(RCConversationType)conversationType
                    targetId:(NSString *)targetId
              messageContent:(RCMessageContent *)messageContent
          collectionViewSize:(CGSize)collectionViewSize {
    if ([messageContent isKindOfClass:[RCCallSummaryMessage class]]) {
        //todo
        if (conversationType == ConversationType_PRIVATE) {
            return CGSizeMake(collectionViewSize.width, 10 + [RCIM sharedRCIM].globalMessagePortraitSize.height + 10);
        } else if (conversationType == ConversationType_GROUP || conversationType == ConversationType_DISCUSSION) {
            return CGSizeMake(collectionViewSize.width, 10 + 12.5 + 5 + 10);
        }
    }
    return CGSizeMake(0, 0);
}

- (BOOL)isMessageCellPortraitDisplayed:(RCConversationType)conversationType
                              targetId:(NSString *)targetId
                        messageContent:(RCMessageContent *)messageContent {
  if ([messageContent isKindOfClass:[RCCallSummaryMessage class]]) {
    if (conversationType == ConversationType_PRIVATE) {
      return YES;
    } else if (conversationType == ConversationType_GROUP || conversationType == ConversationType_DISCUSSION) {
      return NO;
    }
  }
  return NO;
}

- (BOOL)didHoldMessageCellTapEvent:(RCConversationType)conversationType
                          targetId:(NSString *)targetId
                    messageContent:(RCMessageContent *)messageContent {
    if ([messageContent isKindOfClass:[RCCallSummaryMessage class]]) {
        return YES;
    } else {
        return NO;
    }
}

- (void)didTapMessageCell:(RCConversationType)conversationType
                 targetId:(NSString *)targetId
           messageContent:(RCMessageContent *)messageContent {
    if ([messageContent isKindOfClass:[RCCallSummaryMessage class]]) {
        RCCallSummaryMessage *callMessage = (RCCallSummaryMessage *)messageContent;
        if (conversationType == ConversationType_PRIVATE) {
            [[RCCall sharedRCCall] startSingleCall:targetId mediaType:callMessage.mediaType];
        }
    }
}

- (void)registerConversationPlugin:(RCConversationType)conversationType
                          targetId:(NSString *)targetId
                             block:(void (^)(UIImage *image, NSString *title, RCConversationPluginItemTapBlock tapBlock))registerBlock {
    if (conversationType == ConversationType_PRIVATE) {
        registerBlock([RCCallKitUtility imageFromVoIPBundle:@"voip/actionbar_audio_call_icon.png"],
                      NSLocalizedStringFromTable(@"VoIPAudioCall", @"RongCloudKit", nil),
                      ^(){[[RCCall sharedRCCall] startSingleCall:targetId mediaType:RCCallMediaAudio];});
        
        registerBlock([RCCallKitUtility imageFromVoIPBundle:@"voip/actionbar_video_call_icon.png"],
                      NSLocalizedStringFromTable(@"VoIPVideoCall", @"RongCloudKit", nil),
                      ^(){[[RCCall sharedRCCall] startSingleCall:targetId mediaType:RCCallMediaVideo];});
    } else if (conversationType == ConversationType_GROUP || conversationType == ConversationType_DISCUSSION) {
        registerBlock([RCCallKitUtility imageFromVoIPBundle:@"voip/actionbar_audio_call_icon.png"],
                      NSLocalizedStringFromTable(@"VoIPAudioCall", @"RongCloudKit", nil),
                      ^(){[[RCCall sharedRCCall] startMultiCall:conversationType targetId:targetId mediaType:RCCallMediaAudio];});
        
        registerBlock([RCCallKitUtility imageFromVoIPBundle:@"voip/actionbar_video_call_icon.png"],
                      NSLocalizedStringFromTable(@"VoIPVideoCall", @"RongCloudKit", nil),
                      ^(){[[RCCall sharedRCCall] startMultiCall:conversationType targetId:targetId mediaType:RCCallMediaVideo];});
    }
}


- (BOOL)didHoldReceivedMessageForKitUpdate:(RCMessage *)message {
    if ([message.content isKindOfClass:[RCCallSummaryMessage class]]) {
        return NO;
    } else if ([message.objectName isEqualToString:@"RC:VoipAcceptMsg"] ||
               [message.objectName isEqualToString:@"RC:VoipCallMsg"] ||
               [message.objectName isEqualToString:@"RC:VoipFinishMsg"]) {
        return YES;
    } else {
        return NO;
    }
}

- (BOOL)didHoldReceivedMessageForForegroudAlert:(RCMessage *)message {
    if ([message.content isKindOfClass:[RCCallSummaryMessage class]]) {
        return YES;
    } else if ([message.objectName isEqualToString:@"RC:VoipAcceptMsg"] ||
               [message.objectName isEqualToString:@"RC:VoipCallMsg"] ||
               [message.objectName isEqualToString:@"RC:VoipFinishMsg"]) {
        return YES;
    } else {
        return NO;
    }
}

- (BOOL)didHoldReceivedMessageForBackgroudNotification:(RCMessage *)message {
    if ([message.content isKindOfClass:[RCCallSummaryMessage class]]) {
        return YES;
    } else if ([message.objectName isEqualToString:@"RC:VoipAcceptMsg"] ||
               [message.objectName isEqualToString:@"RC:VoipCallMsg"] ||
               [message.objectName isEqualToString:@"RC:VoipFinishMsg"]) {
        return YES;
    } else {
        return NO;
    }
}

@end
