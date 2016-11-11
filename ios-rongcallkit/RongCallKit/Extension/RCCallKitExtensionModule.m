//
//  RCCallKitExtensionModule.m
//  RongCallKit
//
//  Created by 岑裕 on 16/7/2.
//  Copyright © 2016年 Rong Cloud. All rights reserved.
//

#import "RCCallKitExtensionModule.h"
#import "RCCallDetailMessageCell.h"
#import "RCCallTipMessageCell.h"
#import "RCCall.h"
#import "RCCallKitUtility.h"

@implementation RCCallKitExtensionModule


+ (instancetype)loadRongExtensionModule {
  [RCCall sharedRCCall];
  return [[RCCallKitExtensionModule alloc] init];
}

- (void)destroyModule {
  
}

- (NSArray<RCExtensionMessageCellInfo *> *)getMessageCellInfoList:(RCConversationType)conversationType
                                                         targetId:(NSString *)targetId {
  if (conversationType == ConversationType_PRIVATE) {
    RCExtensionMessageCellInfo *cellInfo = [RCExtensionMessageCellInfo new];
    cellInfo.messageContentClass = [RCCallSummaryMessage class];
    cellInfo.messageCellClass = [RCCallDetailMessageCell class];
    return @[cellInfo];
  } else if (conversationType == ConversationType_GROUP || conversationType == ConversationType_DISCUSSION) {
    RCExtensionMessageCellInfo *cellInfo = [RCExtensionMessageCellInfo new];
    cellInfo.messageContentClass = [RCCallSummaryMessage class];
    cellInfo.messageCellClass = [RCCallTipMessageCell class];
    return @[cellInfo];
  }
  return nil;
}


- (void)didTapMessageCell:(RCMessageModel *)messageModel {
  if ([messageModel.content isKindOfClass:[RCCallSummaryMessage class]]) {
    RCCallSummaryMessage *callMessage = (RCCallSummaryMessage *)messageModel.content;
    if (messageModel.conversationType == ConversationType_PRIVATE) {
      [[RCCall sharedRCCall] startSingleCall:messageModel.targetId mediaType:callMessage.mediaType];
    }
  }
}

- (NSArray<RCExtensionPluginItemInfo *> *)getPluginBoardItemInfoList:(RCConversationType)conversationType
                                                    targetId:(NSString *)targetId {
  NSMutableArray *itemList = [[NSMutableArray alloc] init];
  
  if ([[RCCall sharedRCCall] isAudioCallEnabled:conversationType]) {
    RCExtensionPluginItemInfo *audioItem = [[RCExtensionPluginItemInfo alloc] init];
    audioItem.image = [RCCallKitUtility imageFromVoIPBundle:@"voip/actionbar_audio_call_icon.png"];
    audioItem.title = NSLocalizedStringFromTable(@"VoIPAudioCall", @"RongCloudKit", nil);
    if (conversationType == ConversationType_PRIVATE) {
      audioItem.tapBlock = ^(){[[RCCall sharedRCCall] startSingleCall:targetId mediaType:RCCallMediaAudio];};
    } else if (conversationType == ConversationType_GROUP || conversationType == ConversationType_DISCUSSION) {
      audioItem.tapBlock = ^(){[[RCCall sharedRCCall] startMultiCall:conversationType targetId:targetId mediaType:RCCallMediaAudio];};
    }
    [itemList addObject:audioItem];
  }
  if ([[RCCall sharedRCCall] isVideoCallEnabled:conversationType]) {
    RCExtensionPluginItemInfo *videoItem = [[RCExtensionPluginItemInfo alloc] init];
    videoItem.image = [RCCallKitUtility imageFromVoIPBundle:@"voip/actionbar_video_call_icon.png"];
    videoItem.title = NSLocalizedStringFromTable(@"VoIPVideoCall", @"RongCloudKit", nil);
    videoItem.tapBlock = ^(){[[RCCall sharedRCCall] startSingleCall:targetId mediaType:RCCallMediaVideo];};
    if (conversationType == ConversationType_PRIVATE) {
      videoItem.tapBlock = ^(){[[RCCall sharedRCCall] startSingleCall:targetId mediaType:RCCallMediaVideo];};
    } else if (conversationType == ConversationType_GROUP || conversationType == ConversationType_DISCUSSION) {
      videoItem.tapBlock = ^(){[[RCCall sharedRCCall] startMultiCall:conversationType targetId:targetId mediaType:RCCallMediaVideo];};
    }
    [itemList addObject:videoItem];
  }
  return [itemList copy];
}

- (void)onMessageReceived:(RCMessage *)message {
  
}

- (BOOL)handleAlertForMessageReceived:(RCMessage *)message {
  if ([message.content isKindOfClass:[RCCallSummaryMessage class]]) {
    return YES;
  } else {
    return NO;
  }
}

- (BOOL)handleNotificationForMessageReceived:(RCMessage *)message from:(NSString *)fromName userInfo:(NSDictionary *)userInfo {
  if ([message.content isKindOfClass:[RCCallSummaryMessage class]]) {
    //Todo post call end notification here?
    return YES;
  } else {
    return NO;
  }
}
@end
