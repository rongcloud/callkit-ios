//
//  RCRTCVideoLayout.h
//  RongRTCLib
//
//  Created by RongCloud on 2020/2/13.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCRTCVideoLayout : NSObject

/*!
 输出视频合流宽度
 */
@property (nonatomic, assign) NSInteger width;

/*!
 输出视频合流高度
 */
@property (nonatomic, assign) NSInteger height;

/*!
 输出视频合流帧率
 */
@property (nonatomic, assign) NSInteger fps;

/*!
 输出视频合流码率
 */
@property (nonatomic, assign) NSInteger bitrate;

@end

NS_ASSUME_NONNULL_END
