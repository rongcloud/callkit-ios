//
//  RCRTCCryptoDelegate.h
//  RongRTCLib
//
//  Created by RongCloud on 2020/7/28.
//  Copyright © 2020 RongCloud. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

/*!
自定义加密代理
*/
@protocol RCRTCCustomizedEncryptorDelegate <NSObject>

/*!
加密回调

@param payloadData 需要加密的数据起始地址
@param payloadSize 需要加密的数据的大小
@param encryptedFrame 加密后数据起始地址
@param bytesWritten 加密后数据的大小
@param mediastreamId 当前解密的音视频流名称
@param mediatype 媒体类型，0为"audio" 1为"video"

@discussion
如果使用自定义加密需要实现该方法进行加密操作。

@remarks 加解密配置

*/
- (int)EncryptPayloadData:(const uint8_t *)payloadData
              payloadSize:(size_t)payloadSize
           encryptedFrame:(uint8_t *)encryptedFrame
             bytesWritten:(size_t *)bytesWritten
            mediastreamId:(NSString *)mediastreamId
                mediaType:(int)mediatype;

/*!
加密后数据大小

@param frameSize 加密前数据的大小
@param mediastreamId 当前解密的音视频流名称
@param mediatype 媒体类型，0为"audio" 1为"video"

@discussion
如果使用自定义加密需要根据自己的加密算法返回加密后数据的大小，SDK 会根据返回加密后数据的大小进行内存申请

@remarks 加解密配置

*/
- (size_t)GetMaxCiphertextByteSize:(size_t)frameSize mediastreamId:(NSString *)mediastreamId mediaType:(int)mediatype;

@end

/*!
自定义解密代理
*/
@protocol RCRTCCustomizedDecryptorDelegate <NSObject>

/*!
解密回调

@param encryptedFrame 需要解密的数据起始地址
@param encryptedFrameSize 需要解密的数据的大小
@param frame 解密后数据起始地址
@param bytesWritten 解密后数据的大小
@param mediastreamId 当前解密的音视频流名称
@param mediatype 媒体类型，0为"audio" 1为"video"

@discussion
如果使用自定义解密需要实现该方法进行解密操作。

@remarks 加解密配置

*/
- (int)DecryptFrame:(const uint8_t *)encryptedFrame
          frameSize:(size_t)encryptedFrameSize
              frame:(uint8_t *)frame
       bytesWritten:(size_t *)bytesWritten
      mediastreamId:(NSString *)mediastreamId
          mediaType:(int)mediatype;

/*!
解密后数据大小

@param frameSize 解密前数据的大小
@param mediastreamId 当前解密的音视频流名称
@param mediatype 媒体类型，0为"audio" 1为"video"

@discussion
如果使用自定义解密需要根据自己的解密算法返回解密后数据的大小，SDK 会根据返回解密后数据的大小进行内存申请

@remarks 加解密配置

*/
- (size_t)GetMaxPlaintextByteSize:(size_t)frameSize mediastreamId:(NSString *)mediastreamId mediaType:(int)mediatype;

@end

NS_ASSUME_NONNULL_END
