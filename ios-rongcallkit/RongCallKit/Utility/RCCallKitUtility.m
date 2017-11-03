//
//  RCCallKitUtility.m
//  RongCallKit
//
//  Created by 岑裕 on 16/3/12.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCCallKitUtility.h"
#import "RCCall.h"

@implementation RCCallKitUtility

+ (NSString *)getReadableStringForTime:(long)sec {
    if (sec < 60 * 60) {
        return [NSString stringWithFormat:@"%02ld:%02ld", sec / 60, sec % 60];
    } else {
        return [NSString stringWithFormat:@"%02ld:%02ld:%02ld", sec / 60 / 60, (sec / 60) % 60, sec % 60];
    }
}

+ (UIImage *)getScaleImage:(UIImage *)image size:(CGSize)size {
    UIGraphicsBeginImageContext(size);
    if (size.height >= size.width) {
        [image drawInRect:CGRectMake((size.width - size.height) / 2, 0, size.height, size.height)];
    } else {
        [image drawInRect:CGRectMake(0, (size.height - size.width) / 2, size.width, size.width)];
    }

    UIImage *scaledImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return scaledImage;
}

+ (UIColor *)getScaleImageColor:(UIImage *)image size:(CGSize)size {
    return [UIColor colorWithPatternImage:[self getScaleImage:image size:size]];
}

+ (UIImage *)imageFromVoIPBundle:(NSString *)imageName {
    NSString *imagePath = [[[NSBundle mainBundle] pathForResource:@"RongCloud" ofType:@"bundle"]
        stringByAppendingPathComponent:imageName];

    UIImage *bundleImage = [UIImage imageWithContentsOfFile:imagePath];
    return bundleImage;
}

+ (UIImage *)getDefaultPortraitImage {
    return [RCKitUtility imageNamed:@"default_portrait_msg" ofBundle:@"RongCloud.bundle"];
}

+ (NSString *)getGeneralReadableString:(RCCallDisconnectReason)hangupReason {
    NSString *hangupReasonString = nil;
    switch (hangupReason) {
    case RCCallDisconnectReasonCancel:
        hangupReasonString = NSLocalizedStringFromTable(@"VoIPCallHasCancel", @"RongCloudKit", nil);
        break;
    case RCCallDisconnectReasonReject:
        hangupReasonString = NSLocalizedStringFromTable(@"VoIPCallHasReject", @"RongCloudKit", nil);
        break;
    case RCCallDisconnectReasonHangup:
        hangupReasonString = NSLocalizedStringFromTable(@"VoIPCallHasHangup", @"RongCloudKit", nil);
        break;
    case RCCallDisconnectReasonRemoteCancel:
        hangupReasonString = NSLocalizedStringFromTable(@"VoIPCallRemoteCancel", @"RongCloudKit", nil);
        break;
    case RCCallDisconnectReasonRemoteReject:
        hangupReasonString = NSLocalizedStringFromTable(@"VoIPCallRemoteReject", @"RongCloudKit", nil);
        break;
    case RCCallDisconnectReasonRemoteHangup:
        hangupReasonString = NSLocalizedStringFromTable(@"VoIPCallRemoteHangup", @"RongCloudKit", nil);
        break;
    case RCCallDisconnectReasonRemoteBusyLine:
        hangupReasonString = NSLocalizedStringFromTable(@"VoIPCallRemoteBusyLine", @"RongCloudKit", nil);
        break;
    case RCCallDisconnectReasonRemoteNoResponse:
        hangupReasonString = NSLocalizedStringFromTable(@"VoIPCallRemoteNoResponse", @"RongCloudKit", nil);
        break;
    case RCCallDisconnectReasonAcceptByOtherClient:
        hangupReasonString = NSLocalizedStringFromTable(@"VoIPCallAcceptByOtherClient", @"RongCloudKit", nil);
        break;

    default:
        break;
    }
    return hangupReasonString;
}

+ (NSString *)getReadableStringForMessageCell:(RCCallDisconnectReason)hangupReason {
    NSString *hangupReasonString = nil;
    switch (hangupReason) {
    case RCCallDisconnectReasonBusyLine:
        hangupReasonString = NSLocalizedStringFromTable(@"VoIPCallNoResponse", @"RongCloudKit", nil);
        break;
    case RCCallDisconnectReasonNoResponse:
        hangupReasonString = NSLocalizedStringFromTable(@"VoIPCallNoResponse", @"RongCloudKit", nil);
        break;
    case RCCallDisconnectReasonNetworkError:
        hangupReasonString = NSLocalizedStringFromTable(@"VoIPCallNoResponse", @"RongCloudKit", nil);
        break;
    case RCCallDisconnectReasonRemoteNetworkError:
        hangupReasonString = NSLocalizedStringFromTable(@"VoIPCallRemoteNoResponse", @"RongCloudKit", nil);
        break;
    case RCCallDisconnectReasonAddToBlackList:
        hangupReasonString = NSLocalizedStringFromTable(@"VoIPCallHasReject", @"RongCloudKit", nil);
        break;
    default:
        hangupReasonString = [self getGeneralReadableString:hangupReason];
        break;
    }
    return hangupReasonString;
}

+ (NSString *)getReadableStringForCallViewController:(RCCallDisconnectReason)hangupReason {
    NSString *hangupReasonString = nil;
    switch (hangupReason) {
    case RCCallDisconnectReasonNoResponse:
        hangupReasonString = NSLocalizedStringFromTable(@"VoIPCallNoResponse", @"RongCloudKit", nil);
        break;
    case RCCallDisconnectReasonNetworkError:
        hangupReasonString = NSLocalizedStringFromTable(@"VoIPCallLocalNetworkError", @"RongCloudKit", nil);
        break;
    case RCCallDisconnectReasonRemoteNetworkError:
        hangupReasonString = NSLocalizedStringFromTable(@"VoIPCallRemoteNetworkError", @"RongCloudKit", nil);
        break;
    case RCCallDisconnectReasonRemoteBusyLine:
        hangupReasonString = NSLocalizedStringFromTable(@"VoIPCallRemoteBusyLineAndShowAdvice", @"RongCloudKit", nil);
        break;
    case RCCallDisconnectReasonAddToBlackList:
        hangupReasonString = NSLocalizedStringFromTable(@"VoIP_Rejected_By_Blacklist", @"RongCloudKit", nil);
        break;
    default:
        hangupReasonString = [self getGeneralReadableString:hangupReason];
        break;
    }
    return hangupReasonString;
}

+ (BOOL)isLandscape {
    CGRect screenBounds = [UIScreen mainScreen].bounds;
    return screenBounds.size.width > screenBounds.size.height;
}

+ (void)setScreenForceOn {
    [[NSUserDefaults standardUserDefaults] setBool:[UIApplication sharedApplication].idleTimerDisabled
                                            forKey:@"RCCallIdleTimerDisabled"];
    [UIApplication sharedApplication].idleTimerDisabled = YES;
}

+ (void)clearScreenForceOnStatus {
    BOOL oldStatus = [[NSUserDefaults standardUserDefaults] boolForKey:@"RCCallIdleTimerDisabled"];
    [UIApplication sharedApplication].idleTimerDisabled = oldStatus;
}

@end
