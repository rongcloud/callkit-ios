//
//  RCRTCConfig.h
//  RongRTCLib
//
//  Created by RongCloud on 2020/8/12.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RCRTCProxy.h"

NS_ASSUME_NONNULL_BEGIN

@interface RCRTCConfig : NSObject

/*!
  默认 YES：断网后一直保持重连； NO：如果音视频房间在超时时间（超时时间管理后台可以配置，默认值 60s）内没有连上网络，SDK 会自动退出音视频房间，这个时间是一个粗略值，不保证精确，有 5s 左右的误差
 */
@property (nonatomic, assign) BOOL isEnableAutoReconnect;

/*!
  设置房间统计信息的回调间隔
  单位毫秒, 默认1000ms(1s)。 注意 interval 值太小会影响 SDK 性能，如果小于 100 配置无法生效
 */
@property (nonatomic, assign) NSUInteger statusReportInterval;

/*!
  默认 NO：是否开启媒体流加密功能（SRTP）
  特别注意：开启该功能会对性能和用户体验有一定影响，如果没有该需求请不要打开。
 */
@property (nonatomic, assign) BOOL enableSRTP;

/*!
  默认 YES：是否可以和其它后台 App 进行混音
  特别注意：如果该属性设置为 NO，切换到其它 App 操作麦克风或者扬声器时，会导致自己 App 麦克风采集和播放被打断。
 */
@property (nonatomic, assign) BOOL enableMixWithOthers;

/*!
  默认 NO：使用BaseLine进行视频编码； YES：使用HighProfile进行视频编码
 */
@property (nonatomic, assign) BOOL enableHardwareEncoderHighProfile;

/*!
  默认 YES：Debug模式下检测IMSDK和RTCSDK版本号是否一致
 */
@property (nonatomic, assign) BOOL enableVersionMismatch;

/*!
  默认 YES：是否支持立体声
 */
@property (nonatomic, assign) BOOL enableStereo;

/*!
 设置代理服务地址
 默认: 无
 */
@property (nonatomic, strong) RCRTCProxy *proxy;

/*!
  默认 YES：观众是否支持 PlayAndRecord 模式，该设置只对观众身份生效
  YES：AudioSession Category 为 AVAudioSessionCategoryPlayAndRecord，可以进行听筒/扬声器切换；
  NO：AudioSession Category 为 AVAudioSessionCategoryPlayback。
 */
@property (nonatomic, assign) BOOL enablePlayAndRecord;

@end

NS_ASSUME_NONNULL_END
