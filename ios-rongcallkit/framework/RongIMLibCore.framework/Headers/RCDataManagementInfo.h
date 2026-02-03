//
//  RCDataManagementInfo.h
//  RongIMLibCore
//
//  Created by Lang on 1/20/26.
//  Copyright © 2026 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCDataManagementInfo : NSObject <NSCoding>

/// 会话显示的名称
///
/// 单聊、系统会话类型时，显示规则优先级：好友备注名 > 用户名
/// 群聊会话类型时，显示为群组名称
///
/// - Warning: 开启用户托管功能后，此字段才可生效
@property (nonatomic, copy, nullable) NSString *name;


/// 会话头像
///
/// 单聊、系统会话类型时，显示为目标用户头像
/// 群聊会话类型时，显示为群组头像
///
/// - Warning: 开启用户托管功能后，此字段才可生效
@property (nonatomic, copy, nullable) NSString *portraitUri;

@end

NS_ASSUME_NONNULL_END
