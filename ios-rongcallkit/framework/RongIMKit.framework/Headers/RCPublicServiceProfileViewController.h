//
//  RCPublicServiceProfileViewController.h
//  HelloIos
//
//  Created by litao on 15/4/10.
//  Copyright (c) 2015年 litao. All rights reserved.
//

#import "RCThemeDefine.h"
#import <RongIMLib/RongIMLib.h>
#import <UIKit/UIKit.h>
#import "RCBaseTableViewController.h"
@class RCPublicServiceProfile;
/*!
 公众服务账号信息中的URL点击回调
 */
@protocol RCPublicServiceProfileViewUrlDelegate

/*!
 点击公众服务账号信息的URL回调

 @param url 点击的URL
 */
- (void)gotoUrl:(NSString *)url;

@end

/*!
 公众服务账号信息的ViewController
 */
@interface RCPublicServiceProfileViewController : RCBaseTableViewController

/*!
 公众服务账号信息
 */
@property (nonatomic, strong) RCPublicServiceProfile *serviceProfile;

/*!
 头像显示的形状
 */
@property (nonatomic) RCUserAvatarStyle portraitStyle;

/*!
 当前界面的是否源于聊天会话页面
 */
@property (nonatomic) BOOL fromConversation;

@end
