//
//  RCRTCRemoteUser.h
//  RongRTCLib
//
//  Created by RongCloud on 2019/1/9.
//  Copyright © 2019 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RCRTCInputStream.h"
#import "RCRTCUser.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 音视频远端用户
 */
@interface RCRTCRemoteUser : RCRTCUser

/*!
 获取该远端用户发布的所有音视频流
 */
@property (nonatomic, copy, readonly) NSArray<RCRTCInputStream *> *remoteStreams;

/*!
 将一个视频流切换成小码率视频流
 
 @param streams 要切换的流
 @param completion 切换是否成功
 @discussion
 将一个视频流切换成小码率视频流
 
 @remarks 资源管理
 */
- (void)switchToTinyStream:(nullable NSArray<RCRTCInputStream *> *)streams
                completion:(nullable RCRTCOperationCallback)completion;

/*!
 将一个视频流切换成正常码率视频流
 
 @param streams 要切换的视频流
 @param completion 切换是否成功
 @discussion
 将一个视频流切换成正常码率视频流
 
 @remarks 资源管理
 */
- (void)switchToNormalStream:(nullable NSArray<RCRTCInputStream *> *)streams
                  completion:(nullable RCRTCOperationCallback)completion;

@end

NS_ASSUME_NONNULL_END
