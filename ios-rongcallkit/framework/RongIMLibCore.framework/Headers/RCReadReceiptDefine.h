//
//  RCReadReceiptDefine.h
//  RongIMLibCore
//
//  Created by shuai shao on 2025/4/27.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongIMLibCore/RCStatusDefine.h>

NS_ASSUME_NONNULL_BEGIN

@class RCReadReceiptUser;
@class RCReadReceiptInfoV5;
@class RCReadReceiptUsersResult;
@class RCReadReceiptUsersOption;

typedef void (^RCMessageReadDetailCompletion)(RCReadReceiptUsersResult *_Nullable result, RCErrorCode code);

typedef void (^RCReadReceiptInfoListCompletion)(NSArray<RCReadReceiptInfoV5 *> *_Nullable infoList, RCErrorCode code);

NS_ASSUME_NONNULL_END
