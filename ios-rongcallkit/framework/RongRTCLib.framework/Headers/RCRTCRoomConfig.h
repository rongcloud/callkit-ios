//
//  RCRTCRoomConfig.h
//  RongRTCLib
//
//  Created by RongCloud on 2019/5/21.
//  Copyright © 2019 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RCRTCLibDefine.h"

NS_ASSUME_NONNULL_BEGIN

@interface RCRTCRoomConfig : NSObject

/*!
 语音识别源语言
 */
@property (nonatomic, copy) NSString *srcLanguageCode;

/*!
 加入房间场景, 默认值: RCRTCRoomTypeNormal
 */
@property (nonatomic, assign) RCRTCRoomType roomType;

/*!
 直播类型，仅在 RCRTCRoomType 为 RCRTCRoomTypeLive 时可用，选择当前为音频直播还是音视频直播, 默认值: RCRTCLiveTypeAudioVideo
 */
@property (nonatomic, assign) RCRTCLiveType liveType;

/*!
 直播角色类型，仅在 RCRTCRoomType 为 RCRTCRoomTypeLive 时可用，默认值: RCRTCLiveRoleTypeBroadcaster
  
 @discussion add from 5.1.0
 */
@property (nonatomic, assign) RCRTCLiveRoleType roleType;

/*!
 加入房间类型, 同一 UserID 多端加入房间时的处理类型
 */
@property (nonatomic, assign) RCRTCJoinRoomType joinType;

/*!
设置用户属性
 */
@property (nonatomic, copy, nullable) NSDictionary <NSString *, NSString *> *localUserDatas;

/*!
 离开房间是否停止混音和短音效，默认值：YES
 */
@property (nonatomic, assign) BOOL stopAudioMixer;

/*!
 请求超时时间，默认值：30s
 */
@property (nonatomic, assign) NSInteger timeout;

@end

NS_ASSUME_NONNULL_END
