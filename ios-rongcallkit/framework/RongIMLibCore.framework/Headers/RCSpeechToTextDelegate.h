//
//  RCSpeechToTextDelegate.h
//  RongIMLibCore
//
//  Created by shaoshuai on 2025/5/27.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCErrorCode.h>

NS_ASSUME_NONNULL_BEGIN

@class RCSpeechToTextInfo;

@protocol RCSpeechToTextDelegate <NSObject>

/// 语音转文本完成。
///
/// - Parameters:
///   - info: 语音转文本信息。
///   - messageUId: 消息对应的唯一 ID。
///   - code: 错误码。
///
/// - Since: 5.22.0
- (void)speechToTextDidComplete:(RCSpeechToTextInfo* _Nullable)info
                     messageUId:(NSString*)messageUId
                           code:(RCErrorCode)code;

@end

NS_ASSUME_NONNULL_END
