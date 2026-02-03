//
//  RCCallAudioMultiCallViewController.h
//  RongCallKit
//
//  Created by RongCloud on 16/3/18.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCCallBaseViewController.h"
@class RCloudImageView;

/*!
 多人音频ViewController
 */
@interface RCCallAudioMultiCallViewController : RCCallBaseViewController

/*!
 通话呼入时，最上方显示的邀请者头像View
 */
@property (nonatomic, strong) RCloudImageView *inviterPortraitView;

/*!
 通话呼入时，大屏幕背景显示的邀请者头像View
 */
@property (nonatomic, strong) RCloudImageView *inviterPortraitBgView;

/*!
 通话呼入时，最上方显示的邀请者名字Label
 */
@property (nonatomic, strong) UILabel *inviterNameLabel;

/*!
 通话呼入时，用户列表说明的Label
 */
@property (nonatomic, strong) UILabel *userCollectionTitleLabel;

/*!
 用户头像列表的CollectionView
 */
@property (nonatomic, strong) UICollectionView *userCollectionView;

/*!
 用户头像列表CollectionView所使用的Layout

 @discussion
 默认使用的是RCAudioMultiCallUserCollectionLayout，您也可以自定义Layout。
 */
@property (nonatomic, strong) UICollectionViewLayout *userCollectionViewLayout;

@end
