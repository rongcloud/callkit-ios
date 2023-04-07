//
//  RCCallKitExtensionModule.m
//  RongCallKit
//
//  Created by RongCloud on 16/7/2.
//  Copyright © 2016年 Rong Cloud. All rights reserved.
//

#import "RCCallKitExtensionModule.h"
#import "RCCall.h"
#import "RCCallDetailMessageCell.h"
#import "RCCallKitUtility.h"
#import "RCCallTipMessageCell.h"

// appkey 默认长度
static NSInteger kAppkeyLength = 13;

@implementation RCCallKitExtensionModule

/*!
 CallKit 插件生成方法

 @warning IMKit会通过这个方法生成并加载CallKit，强烈建议不要删除其中的逻辑，否则肯能导致CallKit功能不正常。
 */
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
        return @[ cellInfo ];
    } else if (conversationType == ConversationType_GROUP || conversationType == ConversationType_DISCUSSION) {
        RCExtensionMessageCellInfo *cellInfo = [RCExtensionMessageCellInfo new];
        cellInfo.messageContentClass = [RCCallSummaryMessage class];
        cellInfo.messageCellClass = [RCCallTipMessageCell class];
        return @[ cellInfo ];
    }
    return nil;
}

- (void)didTapMessageCell:(RCMessageModel *)messageModel {
    if (![self cheackConnectionStatus]){
        return;
    }
    if ([messageModel.content isKindOfClass:[RCCallSummaryMessage class]]) {
        RCCallSummaryMessage *callMessage = (RCCallSummaryMessage *)messageModel.content;
        //  其他端接听显示的消息不可点击
        if (messageModel.conversationType == ConversationType_PRIVATE &&
            callMessage.hangupReason != RCCallDisconnectReasonAcceptByOtherClient) {
            [self startSingleCall:messageModel.targetId mediaType:callMessage.mediaType];
        }
    }
}

- (NSArray<RCExtensionPluginItemInfo *> *)getPluginBoardItemInfoList:(RCConversationType)conversationType
                                                            targetId:(NSString *)targetId {
    NSMutableArray *itemList = [[NSMutableArray alloc] init];
    if ([targetId isEqualToString:[RCCoreClient sharedCoreClient].currentUserInfo.userId]) {
        return itemList;
    }

    if ([[RCCall sharedRCCall] isAudioCallEnabled:conversationType]) {
        RCExtensionPluginItemInfo *audioItem = [[RCExtensionPluginItemInfo alloc] init];

        audioItem.normalImage = [RCCallKitUtility imageFromVoIPBundle:@"voip/plugin_item_audio.png"];
        audioItem.highlightedImage = [RCCallKitUtility imageFromVoIPBundle:@"voip/plugin_item_audio_highlighted.png"];
        audioItem.title = RCCallKitLocalizedString(@"VoIPAudioCall");

        if (conversationType == ConversationType_PRIVATE) {
            audioItem.tapBlock = ^(RCChatSessionInputBarControl *chatSessionInputBar) {
                if (![self cheackConnectionStatus]){
                    return;
                }
                [self startSingleCall:targetId mediaType:RCCallMediaAudio];
            };
        } else if (conversationType == ConversationType_GROUP || conversationType == ConversationType_DISCUSSION) {
            audioItem.tapBlock = ^(RCChatSessionInputBarControl *chatSessionInputBar) {
                if (![self cheackConnectionStatus]){
                    return;
                }
                [[RCCall sharedRCCall] startMultiCall:conversationType targetId:targetId mediaType:RCCallMediaAudio];
            };
        }
        audioItem.tag = PLUGIN_BOARD_ITEM_VOIP_TAG;
        [itemList addObject:audioItem];
    }
    if ([[RCCall sharedRCCall] isVideoCallEnabled:conversationType]) {
        RCExtensionPluginItemInfo *videoItem = [[RCExtensionPluginItemInfo alloc] init];

        videoItem.normalImage = [RCCallKitUtility imageFromVoIPBundle:@"voip/plugin_item_video.png"];
        videoItem.highlightedImage = [RCCallKitUtility imageFromVoIPBundle:@"voip/plugin_item_video_highlighted.png"];
        videoItem.title = RCCallKitLocalizedString(@"VoIPVideoCall");

        videoItem.tapBlock = ^(RCChatSessionInputBarControl *chatSessionInputBar) {
            [self startSingleCall:targetId mediaType:RCCallMediaVideo];
        };
        if (conversationType == ConversationType_PRIVATE) {
            videoItem.tapBlock = ^(RCChatSessionInputBarControl *chatSessionInputBar) {
                if (![self cheackConnectionStatus]){
                    return;
                }
                [self startSingleCall:targetId mediaType:RCCallMediaVideo];
            };
        } else if (conversationType == ConversationType_GROUP || conversationType == ConversationType_DISCUSSION) {
            videoItem.tapBlock = ^(RCChatSessionInputBarControl *chatSessionInputBar) {
                if (![self cheackConnectionStatus]){
                    return;
                }
                [[RCCall sharedRCCall] startMultiCall:conversationType targetId:targetId mediaType:RCCallMediaVideo];
            };
        }
        videoItem.tag = PLUGIN_BOARD_ITEM_VIDEO_VOIP_TAG;
        [itemList addObject:videoItem];
    }
    return itemList;
}

- (void)startSingleCall:(NSString *)targetId mediaType:(RCCallMediaType)mediaType {
    if ([self isCrossCallWithCheckString:targetId]) {
        [[RCCall sharedRCCall] startSingleCrossCall:targetId mediaType:mediaType];
    } else {
        [[RCCall sharedRCCall] startSingleCall:targetId mediaType:mediaType];
    }
}

- (BOOL)isCrossCallWithCheckString:(NSString *)targetId {
    if ([targetId containsString:@"_"]) {
        NSArray *targetIds = [targetId componentsSeparatedByString:@"_"];
        if (targetIds.count > 1) {
            NSString *tAppkey = targetIds[0];
            if (tAppkey.length == kAppkeyLength) {
                return YES;
            }
        }
    }
    return NO;
}

- (void)onMessageReceived:(RCMessage *)message {
}

- (BOOL)handleAlertForMessageReceived:(RCMessage *)message {
    if ([message.content isKindOfClass:[RCCallSummaryMessage class]]) {
        return YES;
    } else if ([RCCall sharedRCCall].currentCallSession.callStatus == RCCallActive) {
        return YES;
    } else {
        return NO;
    }
}

- (BOOL)handleNotificationForMessageReceived:(RCMessage *)message
                                        from:(NSString *)fromName
                                    userInfo:(NSDictionary *)userInfo {
    if ([message.content isKindOfClass:[RCCallSummaryMessage class]]) {
        // Todo post call end notification here?
        return YES;
    } else {
        return NO;
    }
}

- (BOOL)isAudioHolding {
    if ([RCCall sharedRCCall].currentCallSession) {
        return YES;
    } else {
        return NO;
    }
}

- (BOOL)isCameraHolding {
    if ([RCCall sharedRCCall].currentCallSession &&
        [RCCall sharedRCCall].currentCallSession.mediaType == RCCallMediaVideo) {
        return YES;
    } else {
        return NO;
    }
}

- (BOOL)cheackConnectionStatus {
    if ([[RCIM sharedRCIM] getConnectionStatus] == 0){
        return YES;
    }
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:nil message:RCCallKitLocalizedString(@"voip_network_bad_laterTry") preferredStyle:UIAlertControllerStyleAlert];
    UIViewController *rootVC = [RCKitUtility getKeyWindow].rootViewController;
    [rootVC presentViewController:alertController animated:YES completion:nil];
    [alertController dismissViewControllerAnimated:YES completion:nil];
    return NO;
}
@end
