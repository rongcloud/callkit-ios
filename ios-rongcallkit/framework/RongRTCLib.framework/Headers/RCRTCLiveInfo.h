//
//  RCRTCLiveInfo.h
//  RongRTCLib
//
//  Created by RongCloud on 2019/8/22.
//  Copyright © 2019 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "RCRTCLibDefine.h"
#import "RCRTCMixConfig.h"

NS_ASSUME_NONNULL_BEGIN

@interface RCRTCLiveInfo : NSObject

/**
 当前的直播地址(已废弃)
 @discussion 新版观众加房间,直接可以拿到直播合流, 单个主播流,使用常规方式订阅即可
 @deprecated from 5.1.0
 */
@property (nonatomic, copy, readonly)
    NSString *liveUrl DEPRECATED_MSG_ATTRIBUTE("audience can join room on 5.1.0 version");

/*!
 设置是否开启内置CDN
 
 @param enable YES开启，NO关闭,  默认是NO
 @param completion 动作的回调
 @remarks 资源管理
 */
- (void)enableInnerCDN:(BOOL)enable completion:(nullable void (^)(BOOL isSuccess, RCRTCCode code))completion;

/*!
 设置混流布局配置
 
 @param config 混流布局配置
 @param completion 动作的回调
 @discussion
 设置混流布局配置
 
 @remarks 资源管理
 */
- (void)setMixStreamConfig:(RCRTCMixConfig *)config
                completion:(nullable void (^)(BOOL isSuccess, RCRTCCode code))completion
    DEPRECATED_MSG_ATTRIBUTE("use setMixConfig:completion: API instead");

/*!
 设置混流布局配置
 
 @param config 混流布局配置
 @param completion 动作的回调
 @discussion
 设置混流布局配置
 
 @remarks 资源管理
 */
- (void)setMixConfig:(RCRTCMixConfig *)config completion:(nullable void (^)(BOOL isSuccess, RCRTCCode code))completion;

/*!
 添加一个 CDN 直播推流地址
 
 @param url 推流地址
 @param completion 回调
 */
- (void)addPublishStreamUrl:(NSString *)url
                 completion:(nullable void (^)(BOOL isSuccess, RCRTCCode code, NSArray * _Nullable array))completion;

/*!
 删除一个 CDN 直播推流地址
 
 @param url 要删除的推流地址
 @param completion 回调
 */
- (void)removePublishStreamUrl:(NSString *)url
                    completion:(nullable void (^)(BOOL isSuccess, RCRTCCode code, NSArray * _Nullable array))completion;

@end

NS_ASSUME_NONNULL_END
