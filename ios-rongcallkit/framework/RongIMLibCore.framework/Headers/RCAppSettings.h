//
//  RCAppSettings.h
//  RongIMLibCore
//
//  Created by shuai shao on 2025/6/9.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 当前 AppKey 对应的配置。
///
/// - Since: 5.22.0
@interface RCAppSettings : NSObject

/// 语音转文字功能是否开启。
- (BOOL)isSpeechToTextEnable;

@end

NS_ASSUME_NONNULL_END
