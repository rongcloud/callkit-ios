//
//  RCRTCVideoSourceInterface.h
//  RongRTCLib
//
//  Created by RongCloud on 2020/6/4.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol RCRTCVideoObserverInterface;

NS_ASSUME_NONNULL_BEGIN

/**
 视频数据源接口
 */
@protocol RCRTCVideoSourceInterface <NSObject>

/**
 视频流接口，RCRTCVideoOutputStream 实现了该接口，使用者可以通过 write 方法往视频输出流里写入视频数据
 */
@property (nonatomic, weak, nullable) id<RCRTCVideoObserverInterface> observer;

/*!
 初始化回调
 
 @discussion
 调用 RCRTCVideoOutputStream 中 setVideoSource 方法成功，SDK 会通过 didInit 进行回调通知，接口实现类可以进行视频数据源的初始化工作
 
 @remarks 资源管理
 */
- (void)didInit;

/*!
 开始回调
 
 @discussion
 发布 RCRTCVideoOutputStream 成功，SDK 会通过 didStart 进行回调通知，接口实现类可以进行视频数据采集
 
 @remarks 资源管理
 */
- (void)didStart;

/*!
 停止回调
 
 @discussion
 取消发布 RCRTCVideoOutputStream，SDK 会通过 didStop 进行回调通知，接口实现类可以停止视频数据采集
 
 @remarks 资源管理
 */
- (void)didStop;

@end

NS_ASSUME_NONNULL_END
