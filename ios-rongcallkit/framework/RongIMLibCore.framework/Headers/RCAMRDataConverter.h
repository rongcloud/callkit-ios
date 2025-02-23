/**
 * Copyright (c) 2014-2015, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */

//  RCAMRDataConverter.h
//  Created by Heq.Shinoda on 14-6-17.

#ifndef __RCAMRDataConverter
#define __RCAMRDataConverter

#import <Foundation/Foundation.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

NS_ASSUME_NONNULL_BEGIN
/*!
 AMR 格式与 WAV 格式音频转换工具类
 */
@interface RCAMRDataConverter : NSObject

/*!
 获取 AMR 格式与 WAV 格式音频转换工具类单例

 - Returns: AMR 格式与 WAV 格式音频转换工具类单例
 */
+ (RCAMRDataConverter *)sharedAMRDataConverter;

/*!
 将 AMR 格式的音频数据转化为 WAV 格式的音频数据

 - Parameter data: AMR 格式的音频数据，可以是 AMR-NB 或者 AMR-WB 格式
 - Returns: WAV 格式的音频数据
 */
- (nullable NSData *)decodeAMRToWAVE:(NSData *)data;

/*!
 将 AMR 格式的音频数据转化为 WAV 格式的音频数据

 - Parameter data: AMR格式的音频数据，必须是 AMR-NB 的格式
 - Returns: WAV格式的音频数据
 */
- (nullable NSData *)decodeAMRToWAVEWithoutHeader:(NSData *)data;

/*!
 将 WAV 格式的音频数据转化为 AMR 格式的音频数据（8KHz/16KHz 采样）

 - Parameter data: WAV 格式的音频数据
 - Returns: AMR-NB/AMR-WB 格式的音频数据
 如果采样率为 8KHz 则返回 AMR-NB 格式数据，如果采样率为 16KHz 则返回 AMR-WB 格式数据。
 */
- (nullable NSData *)encodeWAVEToAMR:(NSData *)data;

@end

SEC_ASSUME_NONNULL_END
#endif
