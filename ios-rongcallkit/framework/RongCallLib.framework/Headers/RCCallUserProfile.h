//
//  RCCallUserProfile.h
//  RongCallLib
//
//  Created by RongCloud on 16/2/29.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "RCCallCommonDefine.h"

/*!
 用户的通话状态
 */
@interface RCCallUserProfile : NSObject

/*!
 用户ID
 */
@property (nonatomic, strong) NSString *userId;

/*!
 用户的通话媒体连接ID
 */
@property (nonatomic, strong) NSString *mediaId;

/*!
 用户所使用的媒体类型
 */
@property (nonatomic, assign) RCCallMediaType mediaType;

/*!
 用户的通话状态
 */
@property (nonatomic, assign) RCCallStatus callStatus;

/*!
 用户的摄像头是否已经关闭
 */
@property (nonatomic, assign) BOOL cameraDisabled;

/*!
 用户的麦克风是否已经关闭
 */
@property (nonatomic, assign) BOOL micDisabled;

/*!
 收到通话呼入的时间

 @discussion 只有当前登录用户的呼入时间是准确的，其他用户的并不准确
 */
@property (nonatomic, assign) long long startTime;

/*!
 通话的接通时间
 */
@property (nonatomic, assign) long long connectedTime;

/*!
 通话的挂断时间
 */
@property (nonatomic, assign) long long endTime;

/*!
 用户的视频View
 */
@property (nonatomic, strong) UIView *videoView;

/*!
 音视频用户类型
 */
@property (nonatomic, assign) NSInteger blinkUserType DEPRECATED_MSG_ATTRIBUTE("即将废弃, 请使用 userType");

/*!
 音视频用户类型
*/
@property (nonatomic, assign) RCCallUserType userType;

/*!
 音频主叫接通前声音输出 Yes:外放 NO:听筒
 */
@property (nonatomic, assign) BOOL isSpeakerInAudioMode;

/*!
 用户标签
*/
@property (nonatomic, strong) NSString *tag;

/*!
 初始化用户的通话状态

 @param userId     用户ID
 @param mediaId    用户的通话媒体连接ID
 @param mediaType  用户所使用的媒体类型
 @param callStatus 用户的通话状态
 @param startTime  收到通话呼入的时间
 @discussion
 初始化用户的通话状态
 
 @remarks 通话设置
 @return 用户的通话状态对象
*/
- (instancetype)initWithUserId:(NSString *)userId
                       mediaId:(NSString *)mediaId
                     mediaType:(RCCallMediaType)mediaType
                    callStatus:(RCCallStatus)callStatus
                     startTime:(long long)startTime;

@end
