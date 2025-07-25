//
//  RCUploadMediaStatusListener.h
//  RongIMLib
//
//  Created by litao on 15/8/28.
//  Copyright (c) 2015 年 RongCloud. All rights reserved.
//

#import "RCMessage.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
/*!
 媒体文件上传进度更新的 IMKit 监听

 此监听用于 IMKit 发送媒体文件消息（上传到指定服务器）。
 App 在上传媒体文件时，需要在监听中调用 updateBlock、successBlock 与 errorBlock，通知 IMKit
 SDK 当前上传媒体文件的进度和状态，SDK 会更新 UI。
 */
@interface RCUploadMediaStatusListener : NSObject

/*!
 上传的媒体文件消息的消息实体
 */
@property (nonatomic, strong, nullable) RCMessage *currentMessage;

/*!
 更新上传进度需要调用的 block [progress:当前上传的进度，0 <= progress < 100]
 */
@property (nonatomic, copy, nullable) void (^updateBlock)(int progress);

/*!
 上传成功需要调用的 block。
 content:上传成功之后，需要发送的消息内容。
 您可以使用 currentMessage，把其中content属性对应的 url 字段设置成您上传成功的网络 URL。
 请参考下面代码。

 升级说明：如果您之前使用了此接口，请参考下面代码把参数从 url 替换成 message。
 
 uploadPrepare:^(RCUploadMediaStatusListener *uploadListener) {

     if ([currentMessage.content isKindOfClass:[RCImageMessage class]]) {
        RCImageMessage *content = (RCImageMessage *)uploadListener.currentMessage.content;
        content.remoteUrl = remoteUrl;
        uploadListener.successBlock(content);
     } else if ([currentMessage.content isKindOfClass:[RCFileMessage class]]) {
        RCFileMessage *content = (RCFileMessage *)uploadListener.currentMessage.content;
        content.fileUrl = remoteUrl;
        uploadListener.successBlock(content);
     } else {
        //不做处理的，一定回调返回原消息内容，保障发送方法继续执行
        uploadListener.successBlock(uploadListener.currentMessage.content);
    }
 }
 
 */
@property (nonatomic, copy, nullable) void (^successBlock)(RCMessageContent *content);

/*!
 上传成功需要调用的 block [errorCode:上传失败的错误码，非 0 整数]
 */
@property (nonatomic, copy, nullable) void (^errorBlock)(RCErrorCode errorCode);

/*!
 上传取消需要调用的 block
 */
@property (nonatomic, copy, nullable) void (^cancelBlock)(void);

/*!
 初始化媒体文件上传进度更新的 IMKit 监听

 - Parameter message: 媒体文件消息的消息实体
 - Parameter progressBlock: 更新上传进度需要调用的 block
 - Parameter successBlock: 上传成功需要调用的 block
 - Parameter errorBlock: 上传失败需要调用的 block
 - Parameter cancelBlock: 上传取消需要调用的 block( 如果未实现，传 nil 即可)

 - Returns: 媒体文件上传进度更新的 IMKit 监听对象
 */
- (instancetype)initWithMessage:(RCMessage *)message
                 uploadProgress:(nullable void (^)(int progress))progressBlock
                  uploadSuccess:(nullable void (^)(RCMessageContent *content))successBlock
                    uploadError:(nullable void (^)(RCErrorCode errorCode))errorBlock
                   uploadCancel:(nullable void (^)(void))cancelBlock;

/*!
 取消当前上传

 如果您实现取消正在上传的媒体消息功能，则必须实现此回调。
 您需要在取消成功之后，调用 cancelBlock 通知 SDK，SDK 会自动更新 UI。
 */
- (void)cancelUpload;

@end

NS_ASSUME_NONNULL_END
