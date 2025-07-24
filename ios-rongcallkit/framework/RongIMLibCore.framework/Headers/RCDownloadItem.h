//
//  RCEDownloadItem.h
//  RongEnterpriseApp
//
//  Created by zhaobingdong on 2018/5/15.
//  Copyright © 2018 年 rongcloud. All rights reserved.
//
///
/// - Warning: 此类不支持异步拦截下载 [RCDownloadInterceptor onDownloadRequest:withRequestHandler:]
/// - Warning: Since 5.8.0 开始支持同步拦截下载 [RCDownloadInterceptor onDownloadRequest:]
///

#import <Foundation/Foundation.h>

/**
 下载状态枚举

 - RCDownloadItemStateWaiting: 等待
 - RCDownloadItemStateChecking: 正在检测是否支持 Range
 - RCDownloadItemStateRunning: 正在下载
 - RCDownloadItemStateSuspended: 暂停
 - RCDownloadItemStateCanceled: 已取消
 - RCDownloadItemStateCompleted: 完成
 - RCDownloadItemStateFailed: 失败
 */
typedef NS_ENUM(NSInteger, RCDownloadItemState) {
    RCDownloadItemStateWaiting = 0,
    RCDownloadItemStateChecking,
    RCDownloadItemStateRunning,
    RCDownloadItemStateSuspended,
    RCDownloadItemStateCanceled,
    RCDownloadItemStateCompleted,
    RCDownloadItemStateFailed
};

NS_ASSUME_NONNULL_BEGIN
@class RCDownloadItem;
@protocol RCDownloadItemDelegate <NSObject>

/**
 下载任务状态变化时调用

 - Parameter item: 下载任务对象
 - Parameter state: 状态
 */
- (void)downloadItem:(RCDownloadItem *)item state:(RCDownloadItemState)state;

/**
 下载进度上报时调用

 - Parameter item: 下载任务
 - Parameter progress: 下载进度
 */
- (void)downloadItem:(RCDownloadItem *)item progress:(float)progress;

/**
 任务结束时调用

 - Parameter item: 下载任务
 - Parameter error: 错误信息对象，成功时为 nil
 - Parameter path: 下载完成后文件的路径，此路径为相对路径，相对于沙盒根目录 NSHomeDirectory
 */
- (void)downloadItem:(RCDownloadItem *)item
    didCompleteWithError:(nullable NSError *)error
                filePath:(nullable NSString *)path;
@end

__deprecated_msg("Use [RCCoreClient getDownloadInfo:] instead")
    ///
    /// - Warning: 此类不支持异步拦截下载 [RCDownloadInterceptor onDownloadRequest:withRequestHandler:]
    /// - Warning: Since 5.8.0 开始支持同步拦截下载 [RCDownloadInterceptor onDownloadRequest:]
    ///
    @interface RCDownloadItem : NSObject

/// 下载状态
@property (nonatomic, assign, readonly)
    RCDownloadItemState state __deprecated_msg("Use [RCDownloadInfo getDownloadInfo:] instead");

/// 文件总大小 单位字节
@property (nonatomic, assign, readonly)
    long long totalLength __deprecated_msg("Use [RCDownloadInfo totalLength] instead");

/// 文件当前的大小
@property (nonatomic, assign, readonly)
    long long currentLength __deprecated_msg("Use [RCDownloadInfo totalLength] currentLength");

/// 文件对应的网络 URL
@property (nonatomic, strong, readonly, nullable) NSURL *URL;

/// 标识是否可恢复下载。YES 表示可恢复，支持 Range。NO 表示不支持 Range。
@property (nonatomic, assign, readonly) BOOL resumable;

/// 下载任务的标识符
@property (nonatomic, copy, readonly, nullable) NSString *identify;

/// 下载任务的代理对象
@property (nonatomic, weak, nullable) id<RCDownloadItemDelegate> delegate;

+ (instancetype)new NS_UNAVAILABLE;

/// 开始下载
- (void)
    downLoad __deprecated_msg("Use [RCCoreClient downloadMediaFile:mediaUrl:progress:success:error:cancel:] instead");

/// 暂停下载
- (void)suspend __deprecated_msg("Use [RCCoreClient pauseDownloadMediaUrl:successBlock:errorBlock:] instead");

/// 恢复下载
- (void)resume __deprecated_msg("Use [RCCoreClient downloadMediaFile:mediaUrl:progress:success:error:cancel:] instead");

/// 取消下载
- (void)cancel __deprecated_msg("Use [RCCoreClient cancelDownloadMediaUrl:successBlock:errorBlock:] instead");

@end
NS_ASSUME_NONNULL_END
