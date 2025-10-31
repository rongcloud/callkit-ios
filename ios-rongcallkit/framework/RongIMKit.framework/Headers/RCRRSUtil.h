//
//  RCRRSUtil.h
//  RongIMKit
//
//  Created by Lang on 10/15/25.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RongIMLibCore.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCRRSUtil : NSObject

/// 从 RCReadReceiptResponseV5 创建 RCReadReceiptInfoV5
+ (RCReadReceiptInfoV5 *)infoFromResponse:(RCReadReceiptResponseV5 *)response;

+ (BOOL)isSupportReadReceiptV5;

@end

NS_ASSUME_NONNULL_END
