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
#import <RongIMKit/RCComplexTextMessageCell.h>
#import <RongIMKit/RCStreamMessageCell.h>

/// 工具类
#import <RongIMKit/RCKitUtility.h>
#import <RongIMKit/RCThemeDefine.h>
#import <RongIMKit/RCKitCommonDefine.h>
#import <RongIMKit/RCKitConfig.h>
#import <RongIMKit/RCKitFontConf.h>
#import <RongIMKit/RCKitMessageConf.h>
#import <RongIMKit/RCKitUIConf.h>
#import <RongIMKit/RCKitTranslationConfig.h>
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

#import <RongIMKit/RCBaseTableView.h>
#import <RongIMKit/RCBaseTableViewCell.h>
#import <RongIMKit/RCBaseCollectionView.h>
#import <RongIMKit/RCBaseCollectionViewCell.h>
#import <RongIMKit/RCBaseButton.h>
#import <RongIMKit/RCBaseImageView.h>
#import <RongIMKit/RCBaseNavigationController.h>
#import <RongIMKit/RCBaseView.h>
#import <RongIMKit/RCBaseLabel.h>

// 信息托管
#import <RongIMKit/RCUserInfo+RCExtented.h>
#import <RongIMKit/RCUserInfo+RCGroupMember.h>
#import <RongIMKit/RCGroup+RCExtented.h>

#import <RongIMKit/RCProfileViewController.h>
#import <RongIMKit/RCUserProfileViewModel.h>
#import <RongIMKit/RCProfileViewModel.h>
#import <RongIMKit/RCMyProfileViewModel.h>
#import <RongIMKit/RCProfileFooterViewModel.h>
#import <RongIMKit/RCGroupProfileViewModel.h>
#import <RongIMKit/RCButtonItem.h>
#import <RongIMKit/RCProfileCellViewModel.h>
#import <RongIMKit/RCProfileCommonCellViewModel.h>
#import <RongIMKit/RCGroupProfileMembersCellViewModel.h>
#import <RongIMKit/RCGroupMembersCollectionViewModel.h>
#import <RongIMKit/RCCollectionViewModelProtocol.h>

#import <RongIMKit/RCFriendListViewController.h>
#import <RongIMKit/RCFriendListViewModel.h>
#import <RongIMKit/RCNavigationItemsViewModel.h>
#import <RongIMKit/RCSearchBarViewModel.h>

#import <RongIMKit/RCListViewModelProtocol.h>
#import <RongIMKit/RCCellViewModelProtocol.h>

#import <RongIMKit/RCFriendListCellViewModel.h>
#import <RongIMKit/RCFriendListPermanentCellViewModel.h>

#import <RongIMKit/RCGroupCreateViewController.h>
#import <RongIMKit/RCGroupCreateViewModel.h>
#import <RongIMKit/RCSelectUserViewModel.h>
#import <RongIMKit/RCSelectUserCellViewModel.h>
#import <RongIMKit/RCSelectUserViewController.h>
#import <RongIMKit/RCGroupMemberListViewModel.h>
#import <RongIMKit/RCGroupMemberCellViewModel.h>
#import <RongIMKit/RCRemoveGroupMembersViewModel.h>
#import <RongIMKit/RCRemoveGroupMemberCellViewModel.h>
#import <RongIMKit/RCGroupMemberListViewController.h>
#import <RongIMKit/RCRemoveGroupMembersViewController.h>

#import <RongIMKit/RCBaseViewModel.h>
#import <RongIMKit/RCBaseCellViewModel.h>

#import <RongIMKit/RCApplyFriendListViewModel.h>
#import <RongIMKit/RCApplyFriendCellViewModel.h>
#import <RongIMKit/RCApplyFriendListViewController.h>
#import <RongIMKit/RCApplyFriendOperationCell.h>
#import <RongIMKit/RCApplyFriendCell.h>
#import <RongIMKit/RCApplyFriendListView.h>
#import <RongIMKit/RCApplyFriendSectionItem.h>
#import <RongIMKit/RCApplyNaviItemsViewModel.h>
#import <RongIMKit/RCFriendListView.h>

#import <RongIMKit/RCUserSearchView.h>

#import <RongIMKit/RCSearchUserProfileViewModel.h>
#import <RongIMKit/RCUserSearchViewModel.h>
#import <RongIMKit/RCUserSearchViewController.h>
#import <RongIMKit/RCApplyFriendAlertView.h>
#import <RongIMKit/RCViewModelAdapterCenter.h>
#import <RongIMKit/RCSearchFriendsViewController.h>

#import <RongIMKit/RCProfileSwitchCellViewModel.h>

#import <RongIMKit/RCUserProfileDefine.h>

#import <RongIMKit/RCGroupNoticeViewController.h>
#import <RongIMKit/RCGroupNoticeViewModel.h>

#import <RongIMKit/RCGroupNotificationViewModel.h>
#import <RongIMKit/RCGroupNotificationViewController.h>
#import <RongIMKit/RCGroupNotificationCell.h>
#import <RongIMKit/RCGroupNotificationCellViewModel.h>
#import <RongIMKit/RCMyGroupsViewController.h>
#import <RongIMKit/RCMyGroupsViewModel.h>
#import <RongIMKit/RCGroupInfoCellViewModel.h>
#import <RongIMKit/RCGroupListCell.h>
#import <RongIMKit/RCFriendListPermanentCell.h>

#import <RongIMKit/RCGroupFollowsViewController.h>
#import <RongIMKit/RCGroupFollowsViewModel.h>
#import <RongIMKit/RCSelectGroupMemberViewController.h>
#import <RongIMKit/RCSelectGroupMemberViewModel.h>
#import <RongIMKit/RCGroupManagementViewController.h>
#import <RongIMKit/RCGroupManagementViewModel.h>
#import <RongIMKit/RCGroupManagerListController.h>
#import <RongIMKit/RCGroupManagerListViewModel.h>
#import <RongIMKit/RCGroupTransferViewController.h>
#import <RongIMKit/RCGroupTransferViewModel.h>
#import <RongIMKit/RCSearchGroupsViewModel.h>
#import <RongIMKit/RCSearchGroupsViewController.h>
#import <RongIMKit/RCMyGroupsView.h>

// STT
#import <RongIMKit/RCSTTContentViewModel.h>

// RRS
#import <RongIMKit/RCMessageReadDetailViewController.h>
#import <RongIMKit/RCMessageReadDetailViewConfig.h>
#import <RongIMKit/RCMessageReadDetailViewModel.h>
#import <RongIMKit/RCMessageReadDetailCellViewModel.h>
#import <RongIMKit/RCMessageReadDetailView.h>
#import <RongIMKit/RCMessageReadDetailTabView.h>
#import <RongIMKit/RCMessageReadDetailDefine.h>

//New Skin
#import <RongIMKit/RCIMKitTheme.h>
#import <RongIMKit/RCIMKitThemeManager.h>
#import <RongIMKit/RCMenuItem.h>

#import <RongIMKit/RCOnlineStatusView.h>

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
#import "RCComplexTextMessageCell.h"
#import "RCStreamMessageCell.h"


/// 工具类
#import "RCKitUtility.h"
#import "RCThemeDefine.h"
#import "RCKitCommonDefine.h"
#import "RCKitConfig.h"
#import "RCKitFontConf.h"
#import "RCKitMessageConf.h"
#import "RCKitUIConf.h"
#import "RCKitTranslationConfig.h"
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

//view 基类
#import "RCBaseTableView.h"
#import "RCBaseTableViewCell.h"
#import "RCBaseCollectionView.h"
#import "RCBaseCollectionViewCell.h"
#import "RCBaseButton.h"
#import "RCBaseImageView.h"
#import "RCBaseNavigationController.h"
#import "RCBaseView.h"
#import "RCBaseLabel.h"

// 信息托管
#import "RCUserInfo+RCExtented.h"
#import "RCUserInfo+RCGroupMember.h"
#import "RCGroup+RCExtented.h"

#import "RCProfileViewController.h"
#import "RCUserProfileViewModel.h"
#import "RCProfileViewModel.h"
#import "RCMyProfileViewModel.h"
#import "RCProfileFooterViewModel.h"
#import "RCGroupProfileViewModel.h"
#import "RCButtonItem.h"
#import "RCProfileCellViewModel.h"
#import "RCProfileCommonCellViewModel.h"
#import "RCGroupProfileMembersCellViewModel.h"
#import "RCGroupMembersCollectionViewModel.h"
#import "RCCollectionViewModelProtocol.h"

#import "RCFriendListViewController.h"
#import "RCFriendListViewModel.h"
#import "RCNavigationItemsViewModel.h"
#import "RCSearchBarViewModel.h"

#import "RCListViewModelProtocol.h"
#import "RCCellViewModelProtocol.h"

#import "RCFriendListCellViewModel.h"
#import "RCFriendListPermanentCellViewModel.h"

#import "RCGroupCreateViewController.h"
#import "RCGroupCreateViewModel.h"
#import "RCSelectUserViewModel.h"
#import "RCSelectUserCellViewModel.h"
#import "RCSelectUserViewController.h"
#import "RCGroupMemberListViewModel.h"
#import "RCGroupMemberCellViewModel.h"
#import "RCRemoveGroupMembersViewModel.h"
#import "RCRemoveGroupMemberCellViewModel.h"
#import "RCGroupMemberListViewController.h"
#import "RCRemoveGroupMembersViewController.h"

#import "RCBaseViewModel.h"
#import "RCBaseCellViewModel.h"

#import "RCApplyFriendListViewModel.h"
#import "RCApplyFriendCellViewModel.h"
#import "RCApplyFriendListViewController.h"
#import "RCApplyFriendOperationCell.h"
#import "RCApplyFriendCell.h"
#import "RCApplyFriendListView.h"
#import "RCApplyFriendSectionItem.h"
#import "RCApplyNaviItemsViewModel.h"
#import "RCFriendListView.h"

#import "RCUserSearchView.h"

#import "RCSearchUserProfileViewModel.h"
#import "RCUserSearchViewModel.h"
#import "RCUserSearchViewController.h"
#import "RCApplyFriendAlertView.h"
#import "RCViewModelAdapterCenter.h"
#import "RCSearchFriendsViewController.h"

#import "RCProfileSwitchCellViewModel.h"

#import "RCUserProfileDefine.h"


#import "RCGroupNoticeViewController.h"
#import "RCGroupNoticeViewModel.h"

//2024-11-14
#import "RCGroupNotificationViewModel.h"
#import "RCGroupNotificationViewController.h"
#import "RCGroupNotificationCell.h"
#import "RCGroupNotificationCellViewModel.h"
#import "RCMyGroupsViewController.h"
#import "RCMyGroupsViewModel.h"
#import "RCGroupInfoCellViewModel.h"

#import "RCGroupListCell.h"
#import "RCFriendListPermanentCell.h"

#import "RCGroupFollowsViewController.h"
#import "RCGroupFollowsViewModel.h"
#import "RCSelectGroupMemberViewController.h"
#import "RCSelectGroupMemberViewModel.h"
#import "RCGroupManagementViewController.h"
#import "RCGroupManagementViewModel.h"
#import "RCGroupManagerListController.h"
#import "RCGroupManagerListViewModel.h"
#import "RCGroupTransferViewController.h"
#import "RCGroupTransferViewModel.h"
#import "RCSearchGroupsViewModel.h"
#import "RCSearchGroupsViewController.h"
#import "RCMyGroupsView.h"

// STT
#import "RCSTTContentViewModel.h"

// RRS
#import "RCMessageReadDetailViewController.h"
#import "RCMessageReadDetailViewConfig.h"
#import "RCMessageReadDetailViewModel.h"
#import "RCMessageReadDetailCellViewModel.h"
#import "RCMessageReadDetailView.h"
#import "RCMessageReadDetailTabView.h"
#import "RCMessageReadDetailDefine.h"

// New Skin
#import "RCIMKitTheme.h"
#import "RCIMKitThemeManager.h"
#import "RCMenuItem.h"

#import "RCOnlineStatusView.h"

#endif
