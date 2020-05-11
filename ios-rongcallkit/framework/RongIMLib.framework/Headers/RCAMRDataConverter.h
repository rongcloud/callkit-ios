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

#include "interf_dec.h"
#include "interf_enc.h"
#import <Foundation/Foundation.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!
 AMR 格式与 WAV 格式音频转换工具类
 */
@interface RCAMRDataConverter : NSObject

/*!
 获取 AMR 格式与 WAV 格式音频转换工具类单例

 @return AMR 格式与 WAV 格式音频转换工具类单例
 */
+ (RCAMRDataConverter *)sharedAMRDataConverter;

/*!
 将 AMR 格式的音频数据转化为 WAV 格式的音频数据

 @param data    AMR 格式的音频数据，可以是 AMR-NB 或者 AMR-WB 格式
 @return        WAV 格式的音频数据
 */
- (NSData *)decodeAMRToWAVE:(NSData *)data;

/*!
 将 AMR 格式的音频数据转化为 WAV 格式的音频数据

 @param data    AMR格式的音频数据，必须是 AMR-NB 的格式
 @return        WAV格式的音频数据
 */
- (NSData *)decodeAMRToWAVEWithoutHeader:(NSData *)data;

/*!
 将 WAV 格式的音频数据转化为 AMR 格式的音频数据（8KHz 采样）

 @param data            WAV 格式的音频数据
 @param nChannels       声道数
 @param nBitsPerSample  采样位数（精度）
 @return                AMR-NB 格式的音频数据

 @discussion
 此方法为工具类方法，您可以使用此方法将任意 WAV 音频转换为 AMR-NB 格式的音频。

 @warning
 如果您想和 SDK 自带的语音消息保持一致和互通，考虑到跨平台和传输的原因，SDK 对于 WAV 音频有所限制.
 具体可以参考 RCVoiceMessage 中的音频参数说明(nChannels 为1，nBitsPerSample 为16)。
 */
- (NSData *)encodeWAVEToAMR:(NSData *)data
                    channel:(int)nChannels
             nBitsPerSample:(int)nBitsPerSample __deprecated_msg("已废弃，请勿使用。");

/*!
 将 WAV 格式的音频数据转化为 AMR 格式的音频数据（8KHz/16KHz 采样）

 @param data            WAV 格式的音频数据
 @return                AMR-NB/AMR-WB 格式的音频数据
 @discussion 如果采样率为 8KHz 则返回 AMR-NB 格式数据，如果采样率为 16KHz 则返回 AMR-WB 格式数据。
 */
- (NSData *)encodeWAVEToAMR:(NSData *)data;

@end

#endif
