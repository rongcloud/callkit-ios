//
//  RCRTCStatusReportDelegate.h
//  RongRTCLib
//
//  Created by RongCloud on 2019/6/12.
//  Copyright © 2019 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class RCRTCStatusForm;
@class RCRTCLiveAudioStatus;

@protocol RCRTCStatusReportDelegate <NSObject>

/*!
 汇报 SDK 状态数据

 @param form 状态表单对象
 @discussion
 汇报 SDK 状态数据
 
 @remarks 代理
 */
- (void)didReportStatusForm:(RCRTCStatusForm *)form;

@optional
/*!
 汇报直播音频合流音声状态

 @param audioStatus 音频流声音状态
 @discussion
 当前用户订阅了直播音频合流，汇报合流声音状态，例如当前音频合流有 A B C 三个主播的声音，
 此时 A 在发声，audioStatus 数组里面就会上报 A 的 audioLevel [0 ~ 9]
 
 
 @remarks 代理
 */
- (void)didReportLiveAudioStatus:(NSArray <RCRTCLiveAudioStatus *>*)audioStatus;

@end

NS_ASSUME_NONNULL_END
