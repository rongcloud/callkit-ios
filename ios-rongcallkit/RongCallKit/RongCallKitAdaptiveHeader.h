//
//  RongCallKitAdaptiveHeader.h
//
//  Created by Sin on 2021/1/21.
//  Copyright © 2021 RongCloud. All rights reserved.
//

#if __has_include("RongCloudOpenSource/RongIMKit.h")
#import "RongCloudOpenSource/RongIMKit.h"
#elif __has_include(<RongIMKit/RongIMKit.h>)
#import <RongIMKit/RongIMKit.h>
#else
#import "RongIMKit.h"
#endif
