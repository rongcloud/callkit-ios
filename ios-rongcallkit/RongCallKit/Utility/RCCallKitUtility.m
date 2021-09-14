//
//  RCCallKitUtility.m
//  RongCallKit
//
//  Created by RongCloud on 16/3/12.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCCallKitUtility.h"
#import "RCCall.h"
#import <AVFoundation/AVFoundation.h>

UIColor* rgb(CGFloat red, CGFloat green, CGFloat blue) {
    return [UIColor colorWithRed:red / 255.0f green:green / 255.0f blue:blue / 255.0f alpha:1];
}

UIColor* rgba(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha) {
    return [UIColor colorWithRed:red / 255.0f green:green / 255.0f blue:blue / 255.0f alpha:alpha];
}

UIColor* hex_rgb(NSInteger hex_value) {
    return [UIColor colorWithRed:((float)((hex_value & 0xFF0000) >> 16)) / 255.0
                           green:((float)((hex_value & 0xFF00) >> 8)) / 255.0
                            blue:((float)(hex_value & 0xFF)) / 255.0
                           alpha:1.0];
}

UIColor* dynamic_color(NSInteger light_hex_value, NSInteger dark_hex_value) {
    return [RCKitUtility generateDynamicColor:hex_rgb(light_hex_value)
                                    darkColor:hex_rgb(dark_hex_value)];
}


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
    return [RCKitUtility imageNamed:imageName ofBundle:@"RongCallKit.bundle"];
}


+ (UIImage *)getDefaultPortraitImage {
    return [self imageFromVoIPBundle:@"default_portrait_msg"];
}

+ (NSString *)getGeneralReadableString:(RCCallDisconnectReason)hangupReason {
    NSString *hangupReasonString = nil;
    switch (hangupReason) {
        case RCCallDisconnectReasonCancel:
            hangupReasonString = RCCallKitLocalizedString(@"VoIPCallHasCancel" );
            break;
        case RCCallDisconnectReasonReject:
            hangupReasonString = RCCallKitLocalizedString(@"VoIPCallHasReject" );
            break;
        case RCCallDisconnectReasonHangup:
            hangupReasonString = RCCallKitLocalizedString(@"VoIPCallHasHangup" );
            break;
        case RCCallDisconnectReasonRemoteCancel:
            hangupReasonString = RCCallKitLocalizedString(@"VoIPCallRemoteCancel" );
            break;
        case RCCallDisconnectReasonRemoteReject:
            hangupReasonString = RCCallKitLocalizedString(@"VoIPCallRemoteReject" );
            break;
        case RCCallDisconnectReasonRemoteHangup:
            hangupReasonString = RCCallKitLocalizedString(@"VoIPCallRemoteHangup" );
            break;
        case RCCallDisconnectReasonRemoteBusyLine:
            hangupReasonString = RCCallKitLocalizedString(@"VoIPCallRemoteBusyLine" );
            break;
        case RCCallDisconnectReasonRemoteNoResponse:
            hangupReasonString = RCCallKitLocalizedString(@"VoIPCallRemoteNoResponse" );
            break;
        case RCCallDisconnectReasonAcceptByOtherClient:
            hangupReasonString = RCCallKitLocalizedString(@"VoIPCallAcceptByOtherClient" );
            break;
        case RCCallDisconnectReasonKickedByServer:
            hangupReasonString = RCCallKitLocalizedString(@"VoIPCallKickedByServer" );
            break;
        case RCCallDisconnectReasonMediaServerClosed:
        case RCCallDisconnectReasonRemoteEngineUnsupported:
            hangupReasonString = RCCallKitLocalizedString(@"VoIPCallMediaServerClosed" );
            break;
        default:
            break;
    }
    return hangupReasonString;
}

+ (NSString *)getReadableStringForMessageCell:(RCCallDisconnectReason)hangupReason {
    NSString *hangupReasonString = nil;
    if (hangupReason <= 0) {
        hangupReason = 1;
    }
    switch (hangupReason) {
        case RCCallDisconnectReasonBusyLine:
            hangupReasonString = RCCallKitLocalizedString(@"VoIPCallNoResponse" );
            break;
        case RCCallDisconnectReasonNoResponse:
            hangupReasonString = RCCallKitLocalizedString(@"VoIPCallNoResponse" );
            break;
        case RCCallDisconnectReasonNetworkError:
            hangupReasonString = RCCallKitLocalizedString(@"VoIPCallLocalNetworkError" );
            break;
        case RCCallDisconnectReasonRemoteNetworkError:
            hangupReasonString = RCCallKitLocalizedString(@"VoIPCallRemoteNetworkError" );
            break;
        case RCCallDisconnectReasonAddToBlackList:
            hangupReasonString = RCCallKitLocalizedString(@"VoIPCallHasReject" );
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
            hangupReasonString = RCCallKitLocalizedString(@"VoIPCallNoResponse" );
            break;
        case RCCallDisconnectReasonNetworkError:
            hangupReasonString = RCCallKitLocalizedString(@"VoIPCallLocalNetworkError" );
            break;
        case RCCallDisconnectReasonRemoteNetworkError:
            hangupReasonString = RCCallKitLocalizedString(@"VoIPCallRemoteNetworkError" );
            break;
        case RCCallDisconnectReasonRemoteBusyLine:
            hangupReasonString = RCCallKitLocalizedString(@"VoIPCallRemoteBusyLineAndShowAdvice" );
            break;
        case RCCallDisconnectReasonAddToBlackList:
            hangupReasonString = RCCallKitLocalizedString(@"VoIP_Rejected_By_Blacklist" );
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


+ (void)checkSystemPermission:(RCCallMediaType)mediaType success:(void (^)(void))successBlock error:(void (^)(void))errorBlock{
    if (mediaType == RCCallMediaVideo) {
        [self checkCapturePermission:^(BOOL granted) {
            if (granted) {
                [self checkRecordPermission:^() {
                    successBlock();
                } error:errorBlock];
            }
        } error:errorBlock];
        
    } else if (mediaType == RCCallMediaAudio) {
        [self checkRecordPermission:^() {
            successBlock();
        } error:errorBlock];
    }
}

+ (void)checkRecordPermission:(void (^)(void))successBlock error:(void (^)(void))errorBlock{
    if ([[AVAudioSession sharedInstance] respondsToSelector:@selector(requestRecordPermission:)]) {
        [[AVAudioSession sharedInstance] requestRecordPermission:^(BOOL granted) {
            dispatch_async(dispatch_get_main_queue(), ^{
                if (granted) {
                    successBlock();
                } else {
                    [self
                     loadErrorAlertWithConfirm:RCCallKitLocalizedString(@"AccessRightTitle" )
                     message:RCCallKitLocalizedString(@"speakerAccessRight")];
                    if(errorBlock){
                        errorBlock();
                    }
                }
            });
        }];
    }
}

+ (void)checkCapturePermission:(void (^)(BOOL granted))complete error:(void (^)(void))errorBlock{
    AVAuthorizationStatus authStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];
    
    if (authStatus == AVAuthorizationStatusDenied || authStatus == AVAuthorizationStatusRestricted) {
        [self loadErrorAlertWithConfirm:RCCallKitLocalizedString(@"AccessRightTitle" )
                                message:RCCallKitLocalizedString(@"cameraAccessRight" )];
        complete(NO);
        dispatch_async(dispatch_get_main_queue(), ^{
            errorBlock();
          });
    } else if (authStatus == AVAuthorizationStatusNotDetermined) {
        [AVCaptureDevice
         requestAccessForMediaType:AVMediaTypeVideo
         completionHandler:^(BOOL granted) {
            if (!granted) {
                [self loadErrorAlertWithConfirm:RCCallKitLocalizedString(@"AccessRightTitle")message:RCCallKitLocalizedString(@"cameraAccessRight")];
                dispatch_async(dispatch_get_main_queue(), ^{
                    errorBlock();
                  });
            }
            complete(granted);
        }];
    } else {
        complete(YES);
    }
}
+ (void)loadErrorAlertWithConfirm:(NSString *)title message:(NSString *)message {
    dispatch_async(dispatch_get_main_queue(), ^{
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:title
                                                        message:message
                                                       delegate:nil
                                              cancelButtonTitle:RCCallKitLocalizedString(@"OK" )
                                              otherButtonTitles:nil];
        alert.tag = 1002;
        [alert show];
    });
}

+ (NSInteger)compareVersion:(NSString *)version1 toVersion:(NSString *)version2
{
    NSArray *list1 = [version1 componentsSeparatedByString:@"."];
    NSArray *list2 = [version2 componentsSeparatedByString:@"."];
    for (int i = 0; i < list1.count || i < list2.count; i++)
    {
        NSInteger a = 0, b = 0;
        if (i < list1.count) {
            a = [list1[i] integerValue];
        }
        if (i < list2.count) {
            b = [list2[i] integerValue];
        }
        if (a > b) {
            return 1;//version1大于version2
        } else if (a < b) {
            return -1;//version1小于version2
        }
    }
    return 0;//version1等于version2
    
}

+ (NSBundle *)callKitBundle{
//    NSString *bundlePath = [NSBundle mainBundle].resourcePath;
//    NSString *privateFrameworksPath = [[NSBundle mainBundle].privateFrameworksPath stringByAppendingPathComponent:@"RongCallKit.framework"];
    //注意:podfile 文件里面使用 user_framework 时 bundle 路径会改变,以下方法做了适配
//    BOOL user_framework = [[NSFileManager defaultManager] fileExistsAtPath:privateFrameworksPath];
//    if (user_framework) {
//        bundlePath = privateFrameworksPath;
//    }
//    return [NSBundle bundleWithPath:bundlePath];
    return [NSBundle mainBundle];
}



@end
