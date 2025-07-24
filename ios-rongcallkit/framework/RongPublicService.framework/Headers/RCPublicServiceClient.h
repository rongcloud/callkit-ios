//
//  RCPublicServiceClient.h
//  RongPublicService
//
//  Created by 张改红 on 2020/9/10.
//  Copyright © 2020 张改红。All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RCPublicServiceProfile.h"

NS_ASSUME_NONNULL_BEGIN

@interface RCPublicServiceClient : NSObject

+ (instancetype)sharedPublicServiceClient;

/*!
 查找公众服务账号

 - Parameter searchType: 查找匹配方式
 - Parameter searchKey: 查找关键字
 - Parameter successBlock: 查找成功的回调
 [accounts:查找到的公众服务账号信息 RCPublicServiceProfile 的数组]
 - Parameter errorBlock: 查找失败的回调 [status:失败的错误码]

 - Remark: 公众号
 */
- (void)searchPublicService:(RCSearchType)searchType
                  searchKey:(NSString *)searchKey
                    success:(nullable void (^)(NSArray<RCPublicServiceProfile *> *accounts))successBlock
                      error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 按类型查找公众服务账号

 - Parameter publicServiceType: 公众服务账号的类型
 - Parameter searchType: 查找匹配方式
 - Parameter searchKey: 查找关键字
 - Parameter successBlock: 查找成功的回调
 [accounts:查找到的公众服务账号信息 RCPublicServiceProfile 的数组]
 - Parameter errorBlock: 查找失败的回调 [status:失败的错误码]

 - Remark: 公众号
 */
- (void)searchPublicServiceByType:(RCPublicServiceType)publicServiceType
                       searchType:(RCSearchType)searchType
                        searchKey:(NSString *)searchKey
                          success:(nullable void (^)(NSArray<RCPublicServiceProfile *> *accounts))successBlock
                            error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 关注公众服务账号

 - Parameter publicServiceType: 公众服务账号的类型
 - Parameter publicServiceId: 公众服务的账号 ID
 - Parameter successBlock: 关注成功的回调
 - Parameter errorBlock: 关注失败的回调 [status:失败的错误码]

 - Remark: 公众号
 */
- (void)subscribePublicService:(RCPublicServiceType)publicServiceType
               publicServiceId:(NSString *)publicServiceId
                       success:(nullable void (^)(void))successBlock
                         error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 取消关注公众服务账号

 - Parameter publicServiceType: 公众服务账号的类型
 - Parameter publicServiceId: 公众服务的账号 ID
 - Parameter successBlock: 取消关注成功的回调
 - Parameter errorBlock: 取消关注失败的回调 [status:失败的错误码]

 - Remark: 公众号
 */
- (void)unsubscribePublicService:(RCPublicServiceType)publicServiceType
                 publicServiceId:(NSString *)publicServiceId
                         success:(nullable void (^)(void))successBlock
                           error:(nullable void (^)(RCErrorCode status))errorBlock;

/*!
 查询已关注的公众服务账号

 - Returns: 公众服务信息 RCPublicServiceProfile 列表

 - Remark: 公众号
 */
- (nullable NSArray<RCPublicServiceProfile *> *)getPublicServiceList;

/*!
 获取公众服务账号信息

 - Parameter publicServiceType: 公众服务账号的类型
 - Parameter publicServiceId: 公众服务的账号 ID
 - Returns: 公众服务账号的信息

 - Note: 此方法会从本地缓存中获取公众服务账号信息

 - Remark: 公众号
 */
- (nullable RCPublicServiceProfile *)getPublicServiceProfile:(RCPublicServiceType)publicServiceType
                                             publicServiceId:(NSString *)publicServiceId;

/*!
 获取公众服务账号信息

 - Parameter targetId: 公众服务的账号 ID
 - Parameter type: 公众服务账号的类型
 - Parameter onSuccess: 获取成功的回调
 [serviceProfile:获取到的公众账号信息]
 - Parameter onError: 获取失败的回调 [error:失败的错误码]

 - Note: 此方法会从服务器获取公众服务账号信息

 - Remark: 公众号
 */
- (void)getPublicServiceProfile:(NSString *)targetId
               conversationType:(RCConversationType)type
                      onSuccess:(nullable void (^)(RCPublicServiceProfile *serviceProfile))onSuccess
                        onError:(nullable void (^)(RCErrorCode errorCode))onError;

/*!
 接口已废弃，请参考 IMKit 开源代码中的 RCPublicServiceWebViewController.h/.m
 获取公众服务使用的 WebView Controller

 - Parameter URLString: 准备打开的 URL
 - Returns: 公众服务使用的 WebView Controller

 - Note: 如果您选在用 WebView 打开 URL 连接，则您需要在 App 的 Info.plist 的 NSAppTransportSecurity 中增加
 NSAllowsArbitraryLoadsInWebContent 和 NSAllowsArbitraryLoads 字段，并在苹果审核的时候提供额外的说明。
 更多内容可以参考：https://developer.apple.com/library/content/documentation/General/Reference/InfoPlistKeyReference/Articles/CocoaKeys.html#//apple_ref/doc/uid/TP40009251-SW55

 - Remark: 公众号
 */
- (nullable UIViewController *)getPublicServiceWebViewController:(NSString *)URLString
    __deprecated_msg("has been deprecated");

@end

NS_ASSUME_NONNULL_END
