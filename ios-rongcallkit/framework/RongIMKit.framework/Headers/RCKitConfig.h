//
//  RCKitConfig.h
//  RongIMKit
//
//  Created by Sin on 2020/6/23.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RCKitFontConf.h"
#import "RCKitMessageConf.h"
#import "RCKitUIConf.h"

#define RCKitConfigCenter [RCKitConfig defaultConfig]

/// IMKit 的全局配置按照模块进行划分
@interface RCKitConfig : NSObject

+ (instancetype)defaultConfig;

/// 消息配置
@property (nonatomic, strong) RCKitMessageConf *message;

/// UI 配置
@property (nonatomic, strong) RCKitUIConf *ui;

/// 字体配置
@property (nonatomic, strong) RCKitFontConf *font;
@end
