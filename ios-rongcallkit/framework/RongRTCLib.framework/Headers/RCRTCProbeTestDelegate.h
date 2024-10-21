//
//  RCRTCProbeTestDelegate.h
//  RongRTCLib
//
//  Created by RongCloud on 2021/12/16.
//  Copyright © 2021 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class RCRTCProbeStatusForm;

/// Add from 5.1.17
@protocol RCRTCProbeTestDelegate <NSObject>

/*!
 汇报探测状态数据
 */
- (void)didReportProbeForms:(NSArray <RCRTCProbeStatusForm *>*)forms;

/*!
 探测完成
 */
- (void)didRTCProbeComplete;

/*!
 探测中断
 */
- (void)didRTCProbeInterrput:(RCRTCCode)errorCode;

@end

NS_ASSUME_NONNULL_END

