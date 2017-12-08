//For Agora Only Begin
//
//  RCDVideoFrameObserver.h
//  RongCallKit
//
//  Created by litao on 16/5/16.
//  Copyright © 2016年 Rong Cloud. All rights reserved.
//

#ifndef RCDVideoFrameObserver_h
#define RCDVideoFrameObserver_h
#import <AgoraRtcEngineKit/IAgoraMediaEngine.h>
#include <RongCallLib/IVideoFrameObserver.h>
#import <UIKit/UIKit.h>
#include <stdio.h>

class RCDVideoFrameObserver : public agora::media::IVideoFrameObserver {
  public:
    static RCDVideoFrameObserver *sharedObserver();
    unsigned int m_width;
    unsigned int m_height;
    unsigned int m_yStride;
    unsigned int m_uStride;
    unsigned int m_vStride;

    unsigned char *m_yBuffer;
    unsigned char *m_uBuffer;
    unsigned char *m_vBuffer;

    RCDVideoFrameObserver();
    void setYUV(unsigned char *yBuffer, unsigned char *uBuffer, unsigned char *vBuffer, int width, int height);

    bool onCaptureVideoFrame(VideoFrame &videoFrame);
    bool onRenderVideoFrame(unsigned int uid, VideoFrame &videoFrame);

    virtual ~RCDVideoFrameObserver();
};
#endif /* RCDVideoFrameObserver_h */
//For Agora Only End
