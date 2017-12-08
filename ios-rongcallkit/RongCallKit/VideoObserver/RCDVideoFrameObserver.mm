//For Agora Only Begin
//
//  RCDVideoFrameObserver.mm
//  RongCallKit
//
//  Created by litao on 16/5/16.
//  Copyright © 2016年 Rong Cloud. All rights reserved.
//

#include "RCDVideoFrameObserver.h"

static NSLock *s_lock;
RCDVideoFrameObserver *RCDVideoFrameObserver::sharedObserver() {
    static RCDVideoFrameObserver sharedObserver;
    return &sharedObserver;
}

RCDVideoFrameObserver::RCDVideoFrameObserver() {
    m_width = 0;
    m_height = 0;
    m_yStride = 0;
    m_uStride = 0;
    m_vStride = 0;

    m_yBuffer = NULL;
    m_uBuffer = NULL;
    m_vBuffer = NULL;
    s_lock = [[NSLock alloc] init];
}

RCDVideoFrameObserver::~RCDVideoFrameObserver() {
    if (m_yBuffer) {
        delete[] m_yBuffer;
    }
    if (m_uBuffer) {
        delete[] m_uBuffer;
    }
    if (m_vBuffer) {
        delete[] m_vBuffer;
    }
    s_lock = nil;
}

bool RCDVideoFrameObserver::onCaptureVideoFrame(agora::media::IVideoFrameObserver::VideoFrame &videoFrame) {
    if (!m_width) { //没有初始化内存，在这里初始化内存
        m_height = videoFrame.height;
        m_yStride = videoFrame.yStride;
        m_uStride = videoFrame.uStride;
        m_vStride = videoFrame.vStride;

        m_yBuffer = new unsigned char[m_yStride * m_height];
        m_uBuffer = new unsigned char[m_height * m_uStride * m_uStride / m_yStride];
        m_vBuffer = new unsigned char[m_height * m_vStride * m_vStride / m_yStride];
        memset(m_yBuffer, 0, m_yStride * m_height);
        memset(m_uBuffer, 0, m_height * m_uStride * m_uStride / m_yStride);
        memset(m_vBuffer, 0, m_height * m_vStride * m_vStride / m_yStride);

        m_width = videoFrame.width;

        //画一个十字
        for (int i = videoFrame.height / 2 - 2; i < videoFrame.height / 2 + 3; i++) {
            for (int j = 0; j < videoFrame.width; j++) {
                *(m_yBuffer + i * videoFrame.yStride + j) = 150;
            }
        }

        for (int i = 0; i < videoFrame.height; i++) {
            for (int j = videoFrame.width / 2 - 2; j < videoFrame.width / 2 + 3; j++) {
                *(m_yBuffer + i * videoFrame.yStride + j) = 50;
            }
        }

    } else { // copy内存到媒体engine中
        [s_lock lock];
        unsigned char *y = (unsigned char *)(videoFrame.yBuffer);
        unsigned char *u = (unsigned char *)(videoFrame.uBuffer);
        unsigned char *v = (unsigned char *)(videoFrame.vBuffer);
        memcpy(y, m_yBuffer, m_yStride * m_height);
        memcpy(u, m_uBuffer, m_height * m_uStride * m_uStride / m_yStride);
        memcpy(v, m_vBuffer, m_height * m_uStride * m_uStride / m_yStride);
        [s_lock unlock];
    }
    return true;
}
bool RCDVideoFrameObserver::onRenderVideoFrame(unsigned int uid,
                                               agora::media::IVideoFrameObserver::VideoFrame &videoFrame) {
    NSString *userId = rcGetUserIdFromAgoraUID(uid);
    NSLog(@"the user id is %@", userId);
    return true;
}
void RCDVideoFrameObserver::setYUV(unsigned char *yBuffer, unsigned char *uBuffer, unsigned char *vBuffer, int width,
                                   int height) {
    if (m_width) {
        [s_lock lock];
        for (int i = 0; i < height; i++) {
            if (i >= m_height) {
                break;
            }
            for (int j = 0; j < width; j++) {
                if (j >= m_width) {
                    break;
                }
                *(m_yBuffer + i * m_yStride + j) = *(yBuffer + i * width + j);

                if (j < m_width * m_uStride / m_yStride) {
                    *(m_uBuffer + i * (m_uStride * m_uStride / m_yStride) + j) =
                        *(uBuffer + i * (m_uStride * m_uStride / m_yStride) + j);
                }

                if (j < m_width * m_vStride / m_yStride) {
                    *(m_vBuffer + i * (m_vStride * m_vStride / m_yStride) + j) =
                        *(vBuffer + i * (m_vStride * m_vStride / m_yStride) + j);
                }
            }
        }
        [s_lock unlock];
    }
}
//For Agora Only End
