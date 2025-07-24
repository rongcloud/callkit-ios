//
//  RCSTTContentViewModel.h
//  RongIMKit
//
//  Created by RobinCui on 2025/5/27.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import "RCBaseViewModel.h"
#import <RongIMLibCore/RongIMLibCore.h>
#import "RCMessageModel.h"
NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, RCSTTContentStatus) {
    RCSTTContentStatusHide, // 隐藏状态
    RCSTTContentStatusText, // 文本状态
    RCSTTContentStatusFailed, // 失败状态
    RCSTTContentStatusLoading // 加载状态
};
@class RCSTTContentViewModel;
@protocol RCSTTContentViewModelDelegate <NSObject>

/// 更新布局
- (void)sttViewModelUpdateSTTContentViewLayout:(RCSTTContentViewModel *)viewModel;

/// 修改STT 状态
/// - Parameter viewModel: VM
/// - Parameter status: 状态
- (void)sttViewModel:(RCSTTContentViewModel *)viewModel
        changeStatus:(RCSTTContentStatus)status;

/// 显示文本
/// - Parameter viewModel: VM
/// - Parameter text: 文本
/// - Parameter size: 文本size
/// - Parameter animation: 是否启用动画
- (void)sttViewModel:(RCSTTContentViewModel *)viewModel
        displayText:(NSString *)text
               size:(CGSize)size
          animation:(BOOL)animation;

/// 转文本结束回调
/// - Parameter viewModel: VM
/// - Parameter result: 是否成功
- (void)sttViewModel:(RCSTTContentViewModel *)viewModel speechToTextFinished:(BOOL)result;
@end

@interface RCSTTContentViewModel : RCBaseViewModel

/// 视图代理
@property (nonatomic, weak) id<RCSTTContentViewModelDelegate> delegate;

@property (nonatomic, weak) RCMessageModel *model;


/// 配置STT
/// - Parameter model: 消息模型
+ (void)configureSTTIfNeeded:(RCMessageModel *)model;
/// 初始化
/// - Parameter info: stt
- (instancetype)initWithSTTInfo:(RCSpeechToTextInfo *)info;

/// 刷新视图状态
- (void)refreshStatus;

/// 语音转文本
/// - Parameter completion: 可见性回调
- (void)convertAndDisplaySpeedToText:(void(^)(RCErrorCode code))completion;

/// 隐藏stt
- (void)hideSpeedToText;

/// stt高度
- (CGFloat)speedToTextContentHeight;

/// 是否正在转换
- (BOOL)isConverting;

/// 是否可见
- (BOOL)isSTTVisible;

/// STT
- (RCSpeechToTextInfo *)messageSTTInfo;
@end

NS_ASSUME_NONNULL_END
