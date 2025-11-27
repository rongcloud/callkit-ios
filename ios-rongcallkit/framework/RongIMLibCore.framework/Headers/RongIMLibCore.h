/**
 * Copyright (c) 2014-2015, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */

//  RongIMLibCore.h
//  Created by xugang on 14/12/11.

#import <UIKit/UIKit.h>

//! Project version number for RongIMLibCore.
FOUNDATION_EXPORT double RongIMLibCoreVersionNumber;

//! Project version string for RongIMLibCore.
FOUNDATION_EXPORT const unsigned char RongIMLibCoreVersionString[];

/// IMLib 核心类
#import <RongIMLibCore/RCCoreClient.h>
#import <RongIMLibCore/RCChannelClient.h>
#import <RongIMLibCore/RCCoreClient+Deprecated.h>
#import <RongIMLibCore/RCChannelClient+Deprecated.h>
#import <RongIMLibCore/RCConversationChannelProtocol.h>
#import <RongIMLibCore/RCUserGroupStatusDelegate.h>
#import <RongIMLibCore/RCStatusDefine.h>
#import <RongIMLibCore/RCErrorCode.h>
#import <RongIMLibCore/RCAppSettings.h>

/// 会话相关类
#import <RongIMLibCore/RCConversation.h>
#import <RongIMLibCore/RCGroup.h>
#import <RongIMLibCore/RCUserTypingStatus.h>
/// 消息相关类
#import <RongIMLibCore/RCCommandMessage.h>
#import <RongIMLibCore/RCCommandNotificationMessage.h>
#import <RongIMLibCore/RCContactNotificationMessage.h>
#import <RongIMLibCore/RCGroupNotificationMessage.h>
#import <RongIMLibCore/RCImageMessage.h>
#import <RongIMLibCore/RCGIFMessage.h>
#import <RongIMLibCore/RCInformationNotificationMessage.h>
#import <RongIMLibCore/RCMessage.h>
#import <RongIMLibCore/RCMessage+RCDeprecated.h>
#import <RongIMLibCore/RCMessageContent.h>
#import <RongIMLibCore/RCMediaMessageContent.h>
#import <RongIMLibCore/RCProfileNotificationMessage.h>
#import <RongIMLibCore/RCRecallNotificationMessage.h>
#import <RongIMLibCore/RCRichContentMessage.h>
#import <RongIMLibCore/RCTextMessage.h>
#import <RongIMLibCore/RCUnknownMessage.h>
#import <RongIMLibCore/RCVoiceMessage.h>
#import <RongIMLibCore/RCHQVoiceMessage.h>
#import <RongIMLibCore/RCSightMessage.h>
#import <RongIMLibCore/RCReferenceMessage.h>
#import <RongIMLibCore/RCCombineMessage.h>
#import <RongIMLibCore/RCCombineV2Message.h>
#import <RongIMLibCore/RCMessageConfig.h>
#import <RongIMLibCore/RCMessagePushConfig.h>
#import <RongIMLibCore/RCiOSConfig.h>
#import <RongIMLibCore/RCAndroidConfig.h>
#import <RongIMLibCore/RCHarmonyOSConfig.h>
#import <RongIMLibCore/RCTagInfo.h>
#import <RongIMLibCore/RCConversationIdentifier.h>
#import <RongIMLibCore/RCChannelIdentifier.h>
#import <RongIMLibCore/RCMessageIdentifier.h>
#import <RongIMLibCore/RCMessageResult.h>
#import <RongIMLibCore/RCMessageModifyInfo.h>
#import <RongIMLibCore/RCModifyMessageParams.h>
#import <RongIMLibCore/RCRefreshReferenceMessageParams.h>

#import <RongIMLibCore/RCConversationTagInfo.h>
#import <RongIMLibCore/RCTagProtocol.h>
#import <RongIMLibCore/RCBlockedMessageInfo.h>
#import <RongIMLibCore/RCUltraGroupTypingStatusInfo.h>
#import <RongIMLibCore/RCMessageDigestInfo.h>
#import <RongIMLibCore/RCReceivedStatusInfo.h>
#import <RongIMLibCore/RCNotificationQuietHoursSetting.h>

/// 工具类
#import <RongIMLibCore/RCAMRDataConverter.h>
#import <RongIMLibCore/RCTSMutableDictionary.h>
#import <RongIMLibCore/RCUtilities.h>
//#import <RongIMLibCore/interf_dec.h>
//#import <RongIMLibCore/interf_enc.h>

/// 其他
#import <RongIMLibCore/RCStatusMessage.h>
#import <RongIMLibCore/RCUploadImageStatusListener.h>
#import <RongIMLibCore/RCUploadMediaStatusListener.h>
#import <RongIMLibCore/RCUserInfo.h>
#import <RongIMLibCore/RCRemoteHistoryMsgOption.h>
#import <RongIMLibCore/RCHistoryMessageOption.h>
#import <RongIMLibCore/RCInitOption.h>
#import <RongIMLibCore/RCClearMessageOption.h>
#import <RongIMLibCore/RCLocalConfiguration.h>
#import <RongIMLibCore/RCConversationTopOption.h>
#import <RongIMLibCore/RCConversationFilterOption.h>
#import <RongIMLibCore/RCConversationBatchDeletionParams.h>
#import <RongIMLibCore/RCRobotInfo.h>
#import <RongIMLibCore/RCGetGroupMembersOption.h>
#import <RongIMLibCore/RCConversationsContainingRobotsOption.h>
#import <RongIMLibCore/RCGetUnreadMentionMeConversationListParams.h>

#import <RongIMLibCore/RCFileMessage.h>
#import <RongIMLibCore/RCFileUtility.h>
#import <RongIMLibCore/RCUserOnlineStatusInfo.h>
#import <RongIMLibCore/RCSubscribeUserOnlineStatus.h>
#import <RongIMLibCore/RCPlatformOnlineStatus.h>
#import <RongIMLibCore/RCEditedMessageDraft.h>

// 已读回执
#import <RongIMLibCore/RCReadReceiptInfo.h>
#import <RongIMLibCore/RCConversationStatusInfo.h>
#import <RongIMLibCore/RCGroupMessageReaderV2.h>
#import <RongIMLibCore/RCGroupReadReceiptV2Manager.h>
#import <RongIMLibCore/RCGroupReadReceiptV2Protocol.h>
#import <RongIMLibCore/RCGroupReadReceiptInfoV2.h>
#import <RongIMLibCore/RCConversationUnreadInfo.h>
#import <RongIMLibCore/RCReadReceiptMessage.h>
#import <RongIMLibCore/RCSyncReadStatusMessage.h>
#import <RongIMLibCore/RCReadReceiptUser.h>
#import <RongIMLibCore/RCReadReceiptInfoV5.h>
#import <RongIMLibCore/RCReadReceiptUsersOption.h>
#import <RongIMLibCore/RCReadReceiptUsersResult.h>
#import <RongIMLibCore/RCReadReceiptResponseV5.h>
#import <RongIMLibCore/RCReadReceiptDefine.h>

// log
#import <RongIMLibCore/RCFwLog.h>

// Download
#import <RongIMLibCore/RCDownloadItem.h>
#import <RongIMLibCore/RCResumableDownloader.h>

// Socks proxy
#import <RongIMLibCore/RCIMProxy.h>

// Subscribe Event
#import <RongIMLibCore/RCSubscribeEvent.h>
#import <RongIMLibCore/RCSubscribeInfoEvent.h>
#import <RongIMLibCore/RCSubscribeEventRequest.h>
#import <RongIMLibCore/RCSubscribeEventDelegate.h>

// User Manager
#import <RongIMLibCore/RCUserProfile.h>

// Group
#import <RongIMLibCore/RCGroupInfo.h>
#import <RongIMLibCore/RCGroupMemberInfo.h>
#import <RongIMLibCore/RCFollowInfo.h>
#import <RongIMLibCore/RCGroupApplicationInfo.h>

// Friend
#import <RongIMLibCore/RCFriendInfo.h>
#import <RongIMLibCore/RCFriendRelationInfo.h>

// Stream Message
#import <RongIMLibCore/RCStreamMessage.h>
#import <RongIMLibCore/RCStreamMessageRequestParams.h>

// Search Message
#import <RongIMLibCore/RCSearchMessageParams.h>

// Speech To Text
#import <RongIMLibCore/RCSpeechToTextInfo.h>
#import <RongIMLibCore/RCSpeechToTextDelegate.h>

// Translation
#import <RongIMLibCore/RCTranslationDelegate.h>
#import <RongIMLibCore/RCTranslateParams.h>
#import <RongIMLibCore/RCTranslateResult.h>
