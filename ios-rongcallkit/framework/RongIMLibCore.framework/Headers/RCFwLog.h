//
//  RCFwLog.h
//  MacLogTest
//
//  Created by ZhangLei on 26/02/2018.
//  Copyright © 2018 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#define __FILE_STRING__ [NSString stringWithUTF8String:__FILE__]
#define __GET_FILENAME__ \
    [__FILE_STRING__ substringFromIndex:[__FILE_STRING__ rangeOfString:@"/" options:NSBackwardsSearch].location + 1]
#define RCLogS(k, ...) \
    [[RCFwLog getInstance] write:RC_Level_S type:RC_Type_DEB tag:__GET_FILENAME__ keys:k, ##__VA_ARGS__]
#define RCLogR(k, ...) \
    [[RCFwLog getInstance] write:RC_Level_R type:RC_Type_DEB tag:__GET_FILENAME__ keys:k, ##__VA_ARGS__]
#define RCLogF(k, ...) \
    [[RCFwLog getInstance] write:RC_Level_F type:RC_Type_DEB tag:__GET_FILENAME__ keys:k, ##__VA_ARGS__]
#define RCLogE(k, ...) \
    [[RCFwLog getInstance] write:RC_Level_E type:RC_Type_DEB tag:__GET_FILENAME__ keys:k, ##__VA_ARGS__]
#define RCLogW(k, ...) \
    [[RCFwLog getInstance] write:RC_Level_W type:RC_Type_DEB tag:__GET_FILENAME__ keys:k, ##__VA_ARGS__]
#define RCLogI(k, ...) \
    [[RCFwLog getInstance] write:RC_Level_I type:RC_Type_DEB tag:__GET_FILENAME__ keys:k, ##__VA_ARGS__]
#define RCLogD(k, ...) \
    [[RCFwLog getInstance] write:RC_Level_D type:RC_Type_DEB tag:__GET_FILENAME__ keys:k, ##__VA_ARGS__]
#define RCLogV(k, ...) \
    [[RCFwLog getInstance] write:RC_Level_V type:RC_Type_DEB tag:__GET_FILENAME__ keys:k, ##__VA_ARGS__]

#define FwLogS(p, t, k, ...) [[RCFwLog getInstance] write:RC_Level_S type:p tag:t keys:k, ##__VA_ARGS__]
#define FwLogR(p, t, k, ...) [[RCFwLog getInstance] write:RC_Level_R type:p tag:t keys:k, ##__VA_ARGS__]
#define FwLogF(p, t, k, ...) [[RCFwLog getInstance] write:RC_Level_F type:p tag:t keys:k, ##__VA_ARGS__]
#define FwLogE(p, t, k, ...) [[RCFwLog getInstance] write:RC_Level_E type:p tag:t keys:k, ##__VA_ARGS__]
#define FwLogW(p, t, k, ...) [[RCFwLog getInstance] write:RC_Level_W type:p tag:t keys:k, ##__VA_ARGS__]
#define FwLogI(p, t, k, ...) [[RCFwLog getInstance] write:RC_Level_I type:p tag:t keys:k, ##__VA_ARGS__]
#define FwLogD(p, t, k, ...) [[RCFwLog getInstance] write:RC_Level_D type:p tag:t keys:k, ##__VA_ARGS__]

typedef NS_ENUM(NSInteger, RCFwLogLevel) {
    RC_Level_S = -2,  //Statistics
    RC_Level_R = -1,  //Record
    RC_Level_N = 0,   //None
    RC_Level_F = 1,   //Fatal
    RC_Level_E = 2,   //Error
    RC_Level_W = 3,   //Warn
    RC_Level_I = 4,   //Info
    RC_Level_D = 5,   //Debug
    RC_Level_V = 6    //Verbose
};

typedef NS_OPTIONS(NSUInteger, RCLogType) {
    RC_Type_APP = 1 << 0,  // User interface.
    RC_Type_PTC = 1 << 1,  // Protocol.
    RC_Type_ENV = 1 << 2,
    RC_Type_DET = 1 << 3,
    RC_Type_CON = 1 << 4,
    RC_Type_RCO = 1 << 5,
    RC_Type_CRM = 1 << 6,
    RC_Type_MSG = 1 << 7,  // Message.
    RC_Type_MED = 1 << 8,  // Media file.
    RC_Type_LOG = 1 << 9,
    RC_Type_DEB = 1 << 10,  // Debug log.
    RC_Type_CRS = 1 << 11,  // Crash stack.
    RC_Type_RTC = 1 << 12   // RTC.
};

NS_ASSUME_NONNULL_BEGIN

@interface RCFwLog : NSObject

// should be call init first, otherwise getInstance will return nil.
+ (void)init:(NSString *)appKey sdkVer:(NSString *)sdkVer;
+ (instancetype)getInstance;

+ (void)setLogMonitor:(NSInteger)value;
+ (void)setToken:(NSString *)token;
+ (void)setUserId:(NSString *)userId;
+ (void)setLogListener:(void (^)(NSString *log))logBlock;
+ (void)setConsoleLogLevel:(RCFwLogLevel)level;
/// 网络状态 100% lost 时，此方法会阻塞 30s，切记不要在主线程直接调用
+ (nullable NSString *)getIpWithHost:(NSString *)hostName;
/// 异步获取 ip 地址，内部有切线程处理，子线程执行，主线程回调 callback
+ (void)getIpWithHost:(NSString *)hostName callback:(void (^)(NSString *_Nullable ipString))callback;
+ (void)setRcDebugLogLevel:(NSInteger)rcDebugLogLevel;
+ (void)setRcDebugLogMaxSize:(long long)rcDebugLogMaxSize;
+ (void)startRealTimelog __deprecated_msg("has been deprecated");
- (void)uploadLog:(nullable void (^)(int code))errorBlock __deprecated_msg("has been deprecated");
- (void)uploadDebugLog __deprecated_msg("has been deprecated");
- (void)write:(RCFwLogLevel)level
         type:(RCLogType)type
          tag:(NSString *)tag
         keys:(NSString *)keys, ... NS_FORMAT_FUNCTION(4, 5);

- (void)write:(RCFwLogLevel)level type:(RCLogType)type tag:(NSString *)tag keys:(NSArray *)keys values:(NSArray *)vals;
@end

NS_ASSUME_NONNULL_END
