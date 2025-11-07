//
//  RongCallKitSwiftAdaptiveHeader.h
//
//  Created by Sin on 2025/10/9.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#if __has_include("RongCloudRTCOpenSource/RongCloudRTCOpenSource-Swift.h")
#import "RongCloudRTCOpenSource/RongCloudRTCOpenSource-Swift.h"
#elif __has_include("RongCloudRTCOpenSource-Swift.h")
#import "RongCloudRTCOpenSource-Swift.h"
#elif __has_include("RongCallKit/RongCallKit-Swift.h")
#import "RongCallKit/RongCallKit-Swift.h"
#else
#import "RongCallKit-Swift.h"
#endif
