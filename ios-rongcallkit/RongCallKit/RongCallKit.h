//
//  RongCallKit.h
//  RongCallKit
//
//  Created by litao on 16/4/25.
//  Copyright © 2016年 Rong Cloud. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for RongCallKit.
FOUNDATION_EXPORT double RongCallKitVersionNumber;

//! Project version string for RongCallKit.
FOUNDATION_EXPORT const unsigned char RongCallKitVersionString[];

// In this header, you should import all the public headers of your framework
// using statements like #import <RongCallKit/PublicHeader.h>

#if __has_include(<RongCallKit/RCCall.h>)

#import <RongCallKit/RCCall.h>
#import <RongCallKit/RCCallAudioMultiCallViewController.h>
#import <RongCallKit/RCCallBaseViewController.h>
#import <RongCallKit/RCCallDetailMessageCell.h>
#import <RongCallKit/RCCallFloatingBoard.h>
#import <RongCallKit/RCCallMultiCallUserCell.h>
#import <RongCallKit/RCCallSelectMemberViewController.h>
#import <RongCallKit/RCCallSingleCallViewController.h>
#import <RongCallKit/RCCallTipMessageCell.h>
#import <RongCallKit/RCCallUserCallInfoModel.h>
#import <RongCallKit/RCCallVideoMultiCallViewController.h>

#else

#import "RCCall.h"
#import "RCCallAudioMultiCallViewController.h"
#import "RCCallBaseViewController.h"
#import "RCCallDetailMessageCell.h"
#import "RCCallFloatingBoard.h"
#import "RCCallMultiCallUserCell.h"
#import "RCCallSelectMemberViewController.h"
#import "RCCallSingleCallViewController.h"
#import "RCCallTipMessageCell.h"
#import "RCCallUserCallInfoModel.h"
#import "RCCallVideoMultiCallViewController.h"

#endif
