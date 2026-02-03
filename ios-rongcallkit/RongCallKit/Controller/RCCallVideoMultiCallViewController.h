//
//  RCCallVideoMultiCallViewController.h
//  RongCallKit
//
//  Created by litao on 16/3/18.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCCallBaseViewController.h"
#import "RCCallVideoMultiCallViewController.h"

@class RCloudImageView;

/*!
 多人视频ViewController
 */
@interface RCCallVideoMultiCallViewController : RCCallBaseViewController

/*!
 通话呼入时，最上方显示的邀请者头像View
 */
@property (nonatomic, strong) RCloudImageView *inviterPortraitView;

/*!
 通话呼入时，最上方显示的邀请者头像View
 */
@property (nonatomic, strong) RCloudImageView *inviterPortraitBgView;

/*!
 通话呼入时，最上方显示的邀请者名字Label
 */
@property (nonatomic, strong) UILabel *inviterNameLabel;

/*!
 全屏的用户的名称Label
 */
@property (nonatomic, strong) UILabel *mainNameLabel;

/*!
 通话呼入时，用户列表说明的Label
 */
@property (nonatomic, strong) UILabel *userCollectionTitleLabel;

/*!
 用户视频列表的CollectionView
 */
@property (nonatomic, strong) UICollectionView *userCollectionView;

@property (nonatomic, strong) NSMutableArray *subUserModelList;

/*!
 用户视频列表CollectionView所使用的Layout

 @discussion
 默认使用的是RCVideoMultiCallUserCollectionLayout，您也可以自定义Layout。
 */
@property (nonatomic, strong) UICollectionViewLayout *userCollectionViewLayout;

@end
