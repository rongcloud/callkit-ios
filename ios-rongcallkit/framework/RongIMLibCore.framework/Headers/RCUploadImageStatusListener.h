//
//  RCUploadImageStatusListener.h
//  RongIMLib
//
//  Created by litao on 15/8/28.
//  Copyright (c) 2015 年 RongCloud. All rights reserved.
//

#import "RCMessage.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/*!
 图片上传进度更新的IMKit监听

 此监听用于 IMKit 发送图片消息（上传到指定服务器）。
 App 在上传图片时，需要在监听中调用 updateBlock、successBlock 与 errorBlock，通知 IMKit
 SDK 当前上传图片的进度和状态，SDK 会更新 UI。
 */
@interface RCUploadImageStatusListener : NSObject

/*!
 上传的图片消息的消息实体
 */
@property (nonatomic, strong, nullable) RCMessage *currentMessage;

/*!
 更新上传进度需要调用的 block [progress:当前上传的进度，0 <= progress < 100]
 */
@property (nonatomic, copy, nullable) void (^updateBlock)(int progress);

/*!
 上传成功需要调用的 block [imageUrl:图片的网络 URL]
 */
@property (nonatomic, copy, nullable) void (^successBlock)(NSString *imageUrl);

/*!
 上传成功需要调用的 block [errorCode:上传失败的错误码，非 0 整数]
 */
@property (nonatomic, copy, nullable) void (^errorBlock)(RCErrorCode errorCode);

/*!
 初始化图片上传进度更新的IMKit监听

 - Parameter message: 图片消息的消息实体
 - Parameter progressBlock: 更新上传进度需要调用的 block
 - Parameter successBlock: 上传成功需要调用的 block
 - Parameter errorBlock: 上传失败需要调用的 block

 - Returns: 图片上传进度更新的 IMKit 监听对象
 */
- (instancetype)initWithMessage:(RCMessage *)message
                 uploadProgress:(nullable void (^)(int progress))progressBlock
                  uploadSuccess:(nullable void (^)(NSString *imageUrl))successBlock
                    uploadError:(nullable void (^)(RCErrorCode errorCode))errorBlock;

@end

NS_ASSUME_NONNULL_END
