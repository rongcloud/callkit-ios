//
//  RCExtensionKitDefine.h
//  RongIMKit
//
//  Created by 张改红 on 2020/5/26.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#ifndef RCExtensionKitDefine_h
#define RCExtensionKitDefine_h

/*!
 输入工具栏的显示布局
 */
typedef NS_ENUM(NSInteger, RCChatSessionInputBarControlStyle) {
    /*!
     切换-输入框-扩展
     */
    RC_CHAT_INPUT_BAR_STYLE_SWITCH_CONTAINER_EXTENTION = 0,
    /*!
     扩展-输入框-切换
     */
    RC_CHAT_INPUT_BAR_STYLE_EXTENTION_CONTAINER_SWITCH = 1,
    /*!
     输入框-切换-扩展
     */
    RC_CHAT_INPUT_BAR_STYLE_CONTAINER_SWITCH_EXTENTION = 2,
    /*!
     输入框-扩展-切换
     */
    RC_CHAT_INPUT_BAR_STYLE_CONTAINER_EXTENTION_SWITCH = 3,
    /*!
     切换-输入框
     */
    RC_CHAT_INPUT_BAR_STYLE_SWITCH_CONTAINER = 4,
    /*!
     输入框-切换
     */
    RC_CHAT_INPUT_BAR_STYLE_CONTAINER_SWITCH = 5,
    /*!
     扩展-输入框
     */
    RC_CHAT_INPUT_BAR_STYLE_EXTENTION_CONTAINER = 6,
    /*!
     输入框-扩展
     */
    RC_CHAT_INPUT_BAR_STYLE_CONTAINER_EXTENTION = 7,
    /*!
     输入框
     */
    RC_CHAT_INPUT_BAR_STYLE_CONTAINER = 8,
};

/*!
 输入工具栏的菜单类型
 */
typedef NS_ENUM(NSInteger, RCChatSessionInputBarControlType) {
    /*!
     默认类型，非公众服务
     */
    RCChatSessionInputBarControlDefaultType = 0,
    /*!
     公众服务
     */
    RCChatSessionInputBarControlPubType = 1,

    /*!
     客服机器人
     */
    RCChatSessionInputBarControlCSRobotType = 2,

    /*!
     客服机器人
     */
    RCChatSessionInputBarControlNoAvailableType = 3
};

/*!
 输入工具栏的输入模式
 */
typedef NS_ENUM(NSInteger, RCChatSessionInputBarInputType) {
    /*!
     文本输入模式
     */
    RCChatSessionInputBarInputText = 0,
    /*!
     语音输入模式
     */
    RCChatSessionInputBarInputVoice = 1,
    /*!
     扩展输入模式
     */
    RCChatSessionInputBarInputExtention = 2,
    /*!
     阅后即焚输入模式
     */
    RCChatSessionInputBarInputDestructMode = 3
};

/*!
 输入工具栏的输入模式
 */
typedef NS_ENUM(NSInteger, KBottomBarStatus) {
    /*!
     初始状态
     */
    KBottomBarDefaultStatus = 0,
    /*!
     文本输入状态
     */
    KBottomBarKeyboardStatus,
    /*!
     功能板输入状态
     */
    KBottomBarPluginStatus,
    /*!
     表情输入状态
     */
    KBottomBarEmojiStatus,
    /*!
     语音消息输入状态
     */
    KBottomBarRecordStatus,
    /*!
     常用语输入状态
     */
    KBottomBarCommonPhrasesStatus,
    /*!
     阅后即焚输入状态
     */
    KBottomBarDestructStatus,
};

#endif /* RCExtensionKitDefine_h */
