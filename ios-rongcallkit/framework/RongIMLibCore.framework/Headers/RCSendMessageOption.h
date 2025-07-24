//
//  RCSendMessageOption.h
//  RongIMLib
//
//  Created by liyan on 2019/4/29.
//  Copyright © 2019 年 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCSendMessageOption : NSObject

/// 发送的消息，是否走 VOIP 推送
///
/// 该属性主要用于音视频通话场景。
/// - Warning: 由于苹果审核机制，需要区分国内和国外，请务必认真阅读文档：https://doc.rongcloud.cn/call/IOS/5.X/callkit/push
@property (nonatomic, assign) BOOL isVoIPPush;

@end

NS_ASSUME_NONNULL_END
