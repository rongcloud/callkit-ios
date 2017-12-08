//For Agora Only Begin
//
//  RCDAudioFrameObserver.mm
//  RongCallKit
//
//  Created by litao on 16/9/12.
//  Copyright © 2016年 Rong Cloud. All rights reserved.
//

#include "RCDAudioFrameObserver.h"

RCDAudioFrameObserver *RCDAudioFrameObserver::sharedObserver() {
    static RCDAudioFrameObserver sharedObserver;
    return &sharedObserver;
}

bool RCDAudioFrameObserver::onRecordAudioFrame(agora::media::IAudioFrameObserver::AudioFrame &audioFrame) {
    return true;
}
bool RCDAudioFrameObserver::onPlaybackAudioFrame(agora::media::IAudioFrameObserver::AudioFrame &audioFrame) {
    return true;
}
bool RCDAudioFrameObserver::onMixedAudioFrame(agora::media::IAudioFrameObserver::AudioFrame &audioFrame) {
    return true;
}
bool RCDAudioFrameObserver::onPlaybackAudioFrameBeforeMixing(
    unsigned int uid, agora::media::IAudioFrameObserver::AudioFrame &audioFrame) {
    NSString *userId = rcGetUserIdFromAgoraUID(uid);
    NSLog(@"the user id is %@", userId);
    return true;
}
//For Agora Only End
