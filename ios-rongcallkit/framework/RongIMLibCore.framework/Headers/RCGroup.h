/**
 * Copyright (c) 2014-2015, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */

//  RCGroup.h
//  Created by Heq.Shinoda on 14-9-6.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/// 群组信息类
@interface RCGroup : NSObject <NSCoding>

/// 群组 ID
@property (nonatomic, copy) NSString *groupId;

/// 群组名称
@property (nonatomic, copy) NSString *groupName;

/// 群组头像的 URL
@property (nonatomic, copy, nullable) NSString *portraitUri;

/// 群组信息附加字段
@property (nonatomic, copy, nullable) NSString *extra;

/// 群组信息的初始化方法
///
/// - Parameter groupId: 群组 ID
/// - Parameter groupName: 群组名称
/// - Parameter portraitUri: 群组头像的 URL
///
/// - Returns: 群组信息对象
- (instancetype)initWithGroupId:(NSString *)groupId
                      groupName:(NSString *)groupName
                    portraitUri:(nullable NSString *)portraitUri;

@end

NS_ASSUME_NONNULL_END
