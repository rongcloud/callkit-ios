//
//  RCHQVoiceMessage.h
//  RongIMLib
//
//  Created by Zhaoqianyu on 2019/5/16.
//  Copyright © 2019 RongCloud. All rights reserved.
//

#import <RongIMLibCore/RongIMLibCore.h>

/// 高清语音消息类型名
#define RCHQVoiceMessageTypeIdentifier @"RC:HQVCMsg"

NS_ASSUME_NONNULL_BEGIN

/// 高清语音消息类
///
/// 高清语音消息类，此消息会进行存储并计入未读消息数。
///
/// - Remark: 内容类消息
@interface RCHQVoiceMessage : RCMediaMessageContent <NSCoding>

/// 语音消息的时长，以秒为单位
@property (nonatomic, assign) long duration;

/// 初始化高清语音消息
///
/// - Parameter localPath: 语音的本地路径
/// - Parameter duration: 语音时长，以秒为单位
/// - Returns: 语音消息对象
+ (instancetype)messageWithPath:(NSString *)localPath duration:(long)duration;

@end

@class RCSpeechToTextInfo;

/// 语音转文本。
///
/// - Since: 5.22.0
@interface RCHQVoiceMessage (STT)

/// 语音转文本信息。
@property (nonatomic, readonly, strong, nullable) RCSpeechToTextInfo *sttInfo;

/// 声道数量 [仅单声道支持 STT 功能]。
@property (nonatomic, readonly, assign) NSUInteger numberOfChannels;

/// 采样率 [仅 8000, 16000 支持 STT 功能]。
@property (nonatomic, readonly, assign) NSUInteger sampleRate;

/// 编码格式。
@property (nonatomic, readonly, copy, nullable) NSString *format;

@end

NS_ASSUME_NONNULL_END
