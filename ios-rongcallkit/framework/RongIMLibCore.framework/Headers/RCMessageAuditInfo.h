//
//  RCMessageAuditInfo.h
//  RongIMLibCore
//
//  Created by Lang on 2023/11/27.
//  Copyright © 2023 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RCStatusDefine.h"

NS_ASSUME_NONNULL_BEGIN

/// 消息审核配置
@interface RCMessageAuditInfo : NSObject

/// 是否送审（消息回调是否送给三方审核）
@property (nonatomic, assign) RCMessageAuditType auditType;

/// 项目标识
@property (nonatomic, copy) NSString *project;

/// 审核策略
@property (nonatomic, copy) NSString *strategy;

@end

NS_ASSUME_NONNULL_END
