//
//  RCRTCProbeStatusForm.h
//  RongRTCLib
//
//  Created by RongCloud on 2021/12/21.
//  Copyright © 2021 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, RCRTCProbeQualityLevel) {
    RCRTCProbeQualityLevel_Excellent,
    RCRTCProbeQualityLevel_Good,
    RCRTCProbeQualityLevel_Pool,
    RCRTCProbeQualityLevel_Bad,
    RCRTCProbeQualityLevel_VeryBad,
    RCRTCProbeQualityLevel_Down,
};

typedef NS_ENUM(NSInteger, RCRTCStreamDirection) {
    RCRTCStreamDirection_UpLink   = 1,
    RCRTCStreamDirection_DownLink = 2,
};

@class RCRTCBaseStat;
/// Add from 5.1.17
@interface RCRTCProbeStatusForm : NSObject

@property (nonatomic, readonly) RCRTCProbeQualityLevel qualityLevel;

@property (nonatomic, readonly) RCRTCStreamDirection direction;

@property (nonatomic, readonly) RCRTCBaseStat *stat;

@end

NS_ASSUME_NONNULL_END
