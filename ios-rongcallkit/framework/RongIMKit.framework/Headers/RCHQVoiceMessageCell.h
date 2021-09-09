//
//  RCHQVoiceMessageCell.h
//  RongIMKit
//
//  Created by Zhaoqianyu on 2019/5/20.
//  Copyright © 2019 RongCloud. All rights reserved.
//

#import "RongIMKit.h"

/*!
 语音消息Cell
 */
@interface RCHQVoiceMessageCell : RCMessageCell

/*!
 语音播放的View
 */
@property (nonatomic, strong) UIImageView *playVoiceView;

/*!
 显示是否已播放的View
 */
@property (nonatomic, strong) UIImageView *voiceUnreadTagView;

/*!
 显示语音时长的Label
 */
@property (nonatomic, strong) UILabel *voiceDurationLabel;

/*!
 播放语音
 */
- (void)playVoice;

/*!
 停止播放语音
 */
- (void)stopPlayingVoice;

@end
