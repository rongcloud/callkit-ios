//
//  RongIMKit.h
//  RongIMKit
//
//  Created by xugang on 15/1/13.
//  Copyright (c) 2015年 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>

#if __has_include(<RongIMKit/RongIMKit.h>)

/// IMKit核心类
#import <RongIMKit/RCIM.h>
#import <RongIMKit/RCIM+Deprecated.h>

/// 会话列表相关类
#import <RongIMKit/RCConversationListViewController.h>
#import <RongIMKit/RCPublicServiceListViewController.h>

/// 会话页面相关类
#import <RongIMKit/RCConversationViewController.h>
#import <RongIMKit/RCImageSlideController.h>
#import <RongIMKit/RCLocationPickerViewController.h>
#import <RongIMKit/RCLocationViewController.h>
#import <RongIMKit/RCPublicServiceSearchViewController.h>

/// 会话列表Cell相关类
#import <RongIMKit/RCConversationBaseCell.h>
#import <RongIMKit/RCConversationCell.h>
#import <RongIMKit/RCConversationModel.h>

/// 消息Cell相关类
#import <RongIMKit/RCFileMessageCell.h>
#import <RongIMKit/RCImageMessageCell.h>
#import <RongIMKit/RCGIFMessageCell.h>
#import <RongIMKit/RCImageMessageProgressView.h>
#import <RongIMKit/RCLocationMessageCell.h>
#import <RongIMKit/RCMessageBaseCell.h>
#import <RongIMKit/RCMessageCell.h>
#import <RongIMKit/RCMessageCellDelegate.h>
#import <RongIMKit/RCMessageCellNotificationModel.h>
#import <RongIMKit/RCMessageModel.h>
#import <RongIMKit/RCRichContentMessageCell.h>
#import <RongIMKit/RCTextMessageCell.h>
#import <RongIMKit/RCTipMessageCell.h>
#import <RongIMKit/RCUnknownMessageCell.h>
#import <RongIMKit/RCVoiceMessageCell.h>
#import <RongIMKit/RCReferenceMessageCell.h>
#import <RongIMKit/RCReferencedContentView.h>
#import <RongIMKit/RCReferencingView.h>
#import <RongIMKit/RCMessageCellTool.h>
#import <RongIMKit/RCHQVoiceMessageCell.h>

/// 工具类
#import <RongIMKit/RCKitUtility.h>
#import <RongIMKit/RCThemeDefine.h>
#import <RongIMKit/RCKitCommonDefine.h>
#import <RongIMKit/RCKitConfig.h>
#import <RongIMKit/RCKitFontConf.h>
#import <RongIMKit/RCKitMessageConf.h>
#import <RongIMKit/RCKitUIConf.h>

/// 其他
#import <RongIMKit/RCAttributedLabel.h>
#import <RongIMKit/RCBaseViewController.h>
#import <RongIMKit/RCContentView.h>
#import <RongIMKit/RCEmoticonTabSource.h>
#import <RongIMKit/RCMessageBubbleTipView.h>
#import <RongIMKit/RCPublicServiceProfileViewController.h>
#import <RongIMKit/RCTextView.h>
#import <RongIMKit/RCTipLabel.h>
#import <RongIMKit/RongIMKitExtensionModule.h>
#import <RongIMKit/RCAlertView.h>
#import <RongIMKit/RCActionSheetView.h>

#else
/// IMKit核心类
#import "RCIM.h"
#import "RCIM+Deprecated.h"

/// 会话列表相关类
#import "RCConversationListViewController.h"
#import "RCPublicServiceListViewController.h"

/// 会话页面相关类
#import "RCConversationViewController.h"
#import "RCImageSlideController.h"
#import "RCLocationPickerViewController.h"
#import "RCLocationViewController.h"
#import "RCPublicServiceSearchViewController.h"

/// 会话列表Cell相关类
#import "RCConversationBaseCell.h"
#import "RCConversationCell.h"
#import "RCConversationModel.h"

/// 消息Cell相关类
#import "RCFileMessageCell.h"
#import "RCImageMessageCell.h"
#import "RCGIFMessageCell.h"
#import "RCImageMessageProgressView.h"
#import "RCLocationMessageCell.h"
#import "RCMessageBaseCell.h"
#import "RCMessageCell.h"
#import "RCMessageCellDelegate.h"
#import "RCMessageCellNotificationModel.h"
#import "RCMessageModel.h"
#import "RCRichContentMessageCell.h"
#import "RCTextMessageCell.h"
#import "RCTipMessageCell.h"
#import "RCUnknownMessageCell.h"
#import "RCVoiceMessageCell.h"
#import "RCReferenceMessageCell.h"
#import "RCReferencedContentView.h"
#import "RCReferencingView.h"
#import "RCMessageCellTool.h"
#import "RCHQVoiceMessageCell.h"

/// 工具类
#import "RCKitUtility.h"
#import "RCThemeDefine.h"
#import "RCKitCommonDefine.h"
#import "RCKitConfig.h"
#import "RCKitFontConf.h"
#import "RCKitMessageConf.h"
#import "RCKitUIConf.h"

/// 其他
#import "RCAttributedLabel.h"
#import "RCBaseViewController.h"
#import "RCContentView.h"
#import "RCEmoticonTabSource.h"
#import "RCMessageBubbleTipView.h"
#import "RCPublicServiceProfileViewController.h"
#import "RCTextView.h"
#import "RCTipLabel.h"
#import "RongIMKitExtensionModule.h"
#import "RCAlertView.h"
#import "RCActionSheetView.h"
#endif
