//
//  RCSpeechToTextInfo.h
//  RongIMLibCore
//
//  Created by RobinCui on 2025/5/27.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 转换状态。
///
/// - Since: 5.22.0
typedef NS_ENUM(NSInteger, RCSpeechToTextStatus) {
    /// 未转换。
    RCSpeechToTextStatusNotConverted = 0,
    /// 转换中。
    RCSpeechToTextStatusConverting = 1,
    /// 转换成功。
    RCSpeechToTextStatusSuccess = 2,
    /// 转换失败。
    RCSpeechToTextStatusFailed = 3,
};

/// 语音转文本信息。
///
/// - Since: 5.22.0
@interface RCSpeechToTextInfo : NSObject

/// 转换状态。
@property (nonatomic, assign) RCSpeechToTextStatus status;

/// 转换的文本内容。
@property (nonatomic, copy, nullable) NSString *text;

/// 是否可见，默认 NO。
@property (nonatomic, assign) BOOL isVisible;

@end

NS_ASSUME_NONNULL_END
