//
//  RCDownloadInfo.h
//  RongIMLibCore
//
//  Created by Lang on 2024/1/30.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 文件下载信息
@interface RCDownloadInfo : NSObject

/// 文件总大小
@property (nonatomic, assign) long totalLength;

/// 文件当前下载的大小
@property (nonatomic, assign) long currentLength;

/// 文档当前的下载进度 0 - 100
@property (nonatomic, assign) int currentProgress;

@end

NS_ASSUME_NONNULL_END
