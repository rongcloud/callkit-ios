//
//  RCDVideoFrameObserver.h
//  RongCallLib
//
//  Created by litao on 16/5/16.
//  Copyright © 2016年 Rong Cloud. All rights reserved.
//

#ifndef RCDVideoFrameObserver_hpp
#define RCDVideoFrameObserver_hpp
#include <RongCallLib/IVideoFrameObserver.h>
#import <UIKit/UIKit.h>
#include <stdio.h>
#import <AgoraRtcEngineKit/IAgoraMediaEngine.h>

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
  void setYUV(unsigned char *yBuffer, unsigned char *uBuffer,
              unsigned char *vBuffer, int width, int height);
  
  bool onCaptureVideoFrame(VideoFrame& videoFrame) ;
  bool onRenderVideoFrame(unsigned int uid, VideoFrame& videoFrame) ;
  
  virtual ~RCDVideoFrameObserver();
};
#endif /* RCDVideoFrameObserver_hpp */
