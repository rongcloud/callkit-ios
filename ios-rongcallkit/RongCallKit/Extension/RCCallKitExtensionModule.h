//
//  RCCallKitExtensionModule.h
//  RongCallKit
//
//  Created by RongCloud on 16/7/2.
//  Copyright © 2016年 Rong Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RongCallLib/RongCallLib.h>
#import "RongCallKitAdaptiveHeader.h"

/*!
 CallKit 插件类

 @discussion IMKit会通过这个类将CallKit加载起来。
 */
@interface RCCallKitExtensionModule : NSObject <RongIMKitExtensionModule>

@end
