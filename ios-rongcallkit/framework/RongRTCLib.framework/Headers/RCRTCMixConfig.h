//
//  RCRTCMixConfig.h
//  RongRTCLib
//
//  Created by RongCloud on 2020/2/13.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RCRTCCustomLayout.h"
#import "RCRTCCustomMixAudio.h"
#import "RCRTCMediaConfig.h"
#import "RCRTCStream.h"
NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, RCRTCMixLayoutMode) {
    /*!
     自定义布局
     */
    RCRTCMixLayoutModeCustom = 1,
    /*!
     悬浮布局
    */
    RCRTCMixLayoutModeSuspension = 2,
    /*!
     自适应布局
    */
    RCRTCMixLayoutModeAdaptive = 3
};

typedef NS_ENUM(NSInteger, RCRTCMixMediaType) {
    /*!
     音频
     */
    RCRTCMixMediaType_Audio = 1,
    /*!
     视频
    */
    RCRTCMixMediaType_Video = 2,
    /*!
     音视频
    */
    RCRTCMixMediaType_AV = 3
};

@interface RCRTCMixConfig : NSObject

/*!
 合流服务版本，不支持修改
 
 @discussion
 从 5.1.1 版本，version 变更为 2
 */
@property (nonatomic, assign, readonly) NSInteger version;

/*!
 合流布局模式

 1：自定义布局，需要设置 customLayouts   2：悬浮布局  3：自适应布局
 */
@property (nonatomic, assign) RCRTCMixLayoutMode layoutMode;

/**
 mode 为 2 或者 3 时可用，作用将此 stream 置顶，必须为视频流
 */
@property (nonatomic, strong, nullable) RCRTCStream *hostVideoStream;

/*!
 自定义模式开关
 
 @discussion
 1. version == 1 时，customMode 字段不传， 保持上次逻辑不变，上次是按需订阅，就按需订阅。
 2. version == 2 时，customMode == YES，按自定义视频布局列表 customLayouts，自定义混音音频列表 customMixAudios 来筛选。
   2.1 当 customLayouts == nil，按之前逻辑通过设置 layoutMode 控制合流；
   2.2 当 customLayouts != nil，且 customLayouts.count == 0，所有视频流都不合流；
   2.3 当 customLayouts != nil，且 customLayouts.count != 0，layoutMode == 2 || layoutMode == 3，按 customLayouts 列表指定的视频流进行合流，但里面的 x，y，width，height 不会生效；
   2.4  当 customLayouts != nil，且 customLayouts.count != 0，layoutMode == 1，按 customLayouts 列表指定的视频流进行合流，并且按照设置的 x，y，width，height 进行布局；
   2.5 当 customMixAudios == nil，可参与合流的音频流和之前保持一致；
   2.6 当 customMixAudios != nil，且 customMixAudios.count == 0，所有音频流都不合流；
   2.7 当 customMixAudios != nil，且 customMixAudios.count != 0，按照 customMixAudios 列表指定的音频流进行合流；
 3. version == 2 时，customMode == NO，取消之前设置过的参数筛选配置
 Added from 5.1.1
 */
@property (nonatomic, assign) BOOL customMode;

/*!
 自定义视频流列表，SDK 根据输入视频流列表中的流进行混流，效果为设置其他人的窗口排版
 */
@property (nonatomic, strong) NSMutableArray<RCRTCCustomLayout *> *customLayouts;

/*!
 自定义音频流列表，SDK 根据输入音频流列表中的流进行混流
 
 @discussion
 Added from 5.1.1
 */
@property (nonatomic, strong) NSMutableArray<RCRTCCustomMixAudio *> *customMixAudios;

/*!
 合流音视频配置，包括音频和视频
 */
@property (nonatomic, strong) RCRTCMediaConfig *mediaConfig;

/*!
 设置 MCU 混流配置

 @param mixVideos 视频输入混流列表，为 nil 代表视频全混流，为空数组代表视频全不混流，否则按输入列表进行混流
 @param mixAudios 音频输入混流列表，为 nil 代表音频全混流，为空数组代表音频全不混流，否则按输入列表进行混流
 @discussion
 通过传入音频、视频混流列表，设置 MCU 的音视频混流

 @remarks RCRTCMixConfig：混流操作
 Added from 5.1.3
 */
- (void)setMixInputFilterByStreams:(nullable NSArray<RCRTCCustomLayout *> *)mixVideos
                         mixAudios:(nullable NSArray<RCRTCCustomMixAudio *> *)mixAudios;

/*!
 设置 MCU 混流配置

 @param roomIds 混流房间列表
 @param mixMediaType 混流媒体类型
 @param isAppend 是否为增量混流，YES 为增量混流，NO 为全量覆盖混流
 @discussion
 通过传入混流房间列表，设置 MCU 的音视频混流

 @remarks RCRTCMixConfig：混流操作
 Added from 5.1.3
 */
- (void)setMixInputFilterByRoomIds:(nullable NSArray<NSString *> *)roomIds
                      mixMediaType:(RCRTCMixMediaType)mixMediaType
                          isAppend:(BOOL)isAppend;

@end

NS_ASSUME_NONNULL_END
