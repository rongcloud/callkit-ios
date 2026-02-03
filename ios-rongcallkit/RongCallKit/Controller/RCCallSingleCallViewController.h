//
//  RCCallSingleCallViewController.h
//  RongCallKit
//
//  Created by RongCloud on 16/3/21.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCCallBaseViewController.h"
@class RCloudImageView;

/*!
 单人音视频ViewController
 */
@interface RCCallSingleCallViewController : RCCallBaseViewController

/*!
 对端的头像View
 */
@property (nonatomic, strong) RCloudImageView *remotePortraitView;

/*!
 显示在大屏幕背景的对端头像View
 */
@property (nonatomic, strong) RCloudImageView *remotePortraitBgView;

/*!
 对端的名字Label
 */
@property (nonatomic, strong) UILabel *remoteNameLabel;

/*!
 用户状态的view
 */
@property (nonatomic, strong) UIImageView *statusView;

/*!
 全屏的视频View
 */
@property (nonatomic, strong) UIView *mainVideoView;

/*!
 通话接通后，界面右上角的视频View
 */
@property (nonatomic, strong) UIView *subVideoView;

@end
