//
//  RCRTCVideoView.h
//  RongRTCLib
//
//  Created by RongCloud on 2021/4/19.
//  Copyright © 2021 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RCRTCLibDefine.h"
#import "RCRTCDrawer.h"

@protocol RCRTCVideoViewEventDelegate;

NS_ASSUME_NONNULL_BEGIN

/*!
 视图渲染类
 
 @discussion add from 5.1.10
 */
@interface RCRTCVideoView : UIView <RCRTCDrawer>

/*!
 修改 Frame 时，是否使用动画，默认：YES
 */
@property (nonatomic, assign) BOOL frameAnimated;

/*!
 是否做镜像翻转，只做视图翻转，默认： YES
 */
@property (nonatomic, assign) BOOL isPreviewMirror;

/*!
 视频填充方式
 */
@property (nonatomic, assign) RCRTCVideoFillMode fillMode;

/*!
 视频 view 代理
 */
@property (nonatomic, weak, nullable) id<RCRTCVideoViewEventDelegate> delegate;

/*!
 是否隐藏视图
    
 @param isHidden 是否隐藏，YES 隐藏  NO 不隐藏
 @discussion
 隐藏视图
 
 @remarks 视频配置
 */
- (void)setHidden:(BOOL)isHidden;

/*!
 刷新渲染视图 View
 
 @discussion
 刷新渲染视图 View
 
 @remarks 视频配置
 */
- (void)flushVideoView;

@end

NS_ASSUME_NONNULL_END
