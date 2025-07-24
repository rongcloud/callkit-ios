/**
 * Copyright (c) 2014-2015, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */

//  RCMessageContent.h
//  Created by Heq.Shinoda on 14-6-13.

#ifndef __RCMessageContent
#define __RCMessageContent

#import <RongIMLibCore/RCMentionedInfo.h>
#import <RongIMLibCore/RCStatusDefine.h>
#import <RongIMLibCore/RCUserInfo.h>
#import <RongIMLibCore/RCMessageAuditInfo.h>

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 消息内容的编解码协议
/// 用于标识消息内容的类型，进行消息的编码和解码。
/// 所有自定义消息必须实现此协议，否则将无法正常传输和使用。
@protocol RCMessageCoding <NSObject>
@required

/// 将消息内容序列化，编码成为可传输的 json 数据

///
/// 消息内容通过此方法，将消息中的所有数据，编码成为 json 数据，返回的 json 数据将用于网络传输。
- (nullable NSData *)encode;

/// 将 json 数据的内容反序列化，解码生成可用的消息内容
///
/// - Parameter data: 消息中的原始 json 数据
///
/// 网络传输的 json 数据，会通过此方法解码，获取消息内容中的所有数据，生成有效的消息内容。
- (void)decodeWithData:(NSData *)data;

/// 返回消息的类型名
///
/// - Returns: 消息的类型名
///
/// 您定义的消息类型名，需要在各个平台上保持一致，以保证消息互通。
/// - Warning: 请勿使用 @ "RC:"开头的类型名，以免和 SDK 默认的消息名称冲突
+ (NSString *)getObjectName;

/// 返回可搜索的关键内容列表
///
/// - Returns: 返回可搜索的关键内容列表
///
/// 这里返回的关键内容列表将用于消息搜索，自定义消息必须要实现此接口才能进行搜索。
- (nullable NSArray<NSString *> *)getSearchableWords;

@end

/// 消息内容的存储协议
///
/// 用于确定消息内容的存储策略。
/// 所有自定义消息必须实现此协议，否则将无法正常存储和使用。
@protocol RCMessagePersistentCompatible <NSObject>
@required

/// 返回消息的存储策略
///
/// - Returns: 消息的存储策略
///
/// 指明此消息类型在本地是否存储、是否计入未读消息数。
+ (RCMessagePersistent)persistentFlag;
@end

/// 消息内容摘要的协议
///
/// 用于在会话列表和本地通知中显示消息的摘要。
@protocol RCMessageContentView
@optional

/// 返回在会话列表和本地通知中显示的消息内容摘要
///
/// - Returns: 会话列表和本地通知中显示的消息内容摘要
///
/// 如果您使用 IMKit，当会话的最后一条消息为自定义消息时，需要通过此方法获取在会话列表展现的内容摘要；
/// 当 App 在后台收到消息时，需要通过此方法获取在本地通知中展现的内容摘要。
- (nullable NSString *)conversationDigest;

@end


/// 消息内容的基类
///
/// 此类为消息实体类 RCMessage 中的消息内容 content 的基类。
/// 所有的消息内容均为此类的子类，包括 SDK 自带的消息（如 RCTextMessage、RCImageMessage 等）和用户自定义的消息。
/// 所有的自定义消息必须继承此类，并实现 RCMessageCoding 和 RCMessagePersistentCompatible、RCMessageContentView 协议。
@interface RCMessageContent : NSObject <RCMessageCoding, RCMessagePersistentCompatible, RCMessageContentView>

/// 消息内容中携带的发送者的用户信息
///
/// 如果您使用 IMKit，可以通过 RCIM 的 enableMessageAttachUserInfo 属性设置在每次发送消息中携带发送者的用户信息。
@property (nonatomic, strong, nullable) RCUserInfo *senderUserInfo;

/// 消息中的 @ 提醒信息
@property (nonatomic, strong, nullable) RCMentionedInfo *mentionedInfo;

/// 消息的审核配置
@property (nonatomic, strong, nullable) RCMessageAuditInfo *auditInfo;

/// 设置焚烧时间
///
/// 默认是 0，0 代表该消息非阅后即焚消息。
@property (nonatomic, assign) NSUInteger destructDuration;

/// 消息的附加信息
///
/// 请确保传入的是 NSString 类型的数据
@property (nonatomic, copy, nullable) NSString *extra;

/// 将用户信息编码到字典中
///
/// - Parameter userInfo: 要编码的用户信息
/// - Returns: 存有用户信息的 Dictionary
- (NSDictionary *)encodeUserInfo:(RCUserInfo *)userInfo;

/// 将消息内容中携带的用户信息解码
///
/// - Parameter dictionary: 用户信息的 Dictionary
- (void)decodeUserInfo:(NSDictionary *)dictionary;

/// 将 @ 提醒信息编码到字典中
///
/// - Parameter mentionedInfo: 要编码的@信息
/// - Returns: 存有@信息的 Dictionary
- (NSDictionary *)encodeMentionedInfo:(RCMentionedInfo *)mentionedInfo;

/// 将消息内容中携带的 @ 提醒信息解码
///
/// - Parameter dictionary: @提醒信息的 Dictionary
- (void)decodeMentionedInfo:(NSDictionary *)dictionary;


/// 将基类信息编码到字典中，推荐使用此方法
///
/// - Returns: 存有基类信息的 Dictionary
///
/// 自定义消息在重写 - (nullable NSData *)encode 方法 可直接调用此方法完成基类属性的编码
///
/// 此方法内部调用了 encodeMentionedInfo: 和 encodeUserInfo: 方法
///
///```objc
/// - (NSData *)encode {
///     NSMutableDictionary *dataDict = [self encodeBaseData];
///     NSString *textContent = self.content ?: @"";
///     [dataDict rclib_setObject:textContent forKey:@"content"];
///     NSData *data = [NSJSONSerialization dataWithJSONObject:dataDict options:kNilOptions error:nil];
///     return data;
/// }
/// ```
/// - Since: 5.4.0
- (NSMutableDictionary *)encodeBaseData;


/// 将消息内容中携带的基类信息解码，推荐使用此方法
///
/// - Parameter dictionary: 存有基类信息的 Dictionary
///
/// 自定义消息在重写 - (void)decodeWithData:(NSData *)data 方法 可直接调用此方法完成基类属性的解码
///
/// 此方法内部调用了 decodeMentionedInfo: 和 decodeUserInfo: 方法
///
///```objc
/// - (void)decodeWithData:(NSData *)data {
///     NSDictionary *jsonDic = [[self class] dictionaryFromJsonData:data];
///     if (!jsonDic) {
///         // 解析失败保存原数据
///         self.rawJSONData = data;
///         return;
///     }
///     // 基类负责解析基类属性
///     [self decodeBaseData:jsonDic];
///
///     //子类只解析子类属性
///     self.content = [jsonDic rclib_mix_stringForKey:@"content"];
/// }
/// ```
/// - Since: 5.4.0
- (void)decodeBaseData:(NSDictionary *)dictionary;

/// 消息内容的原始 json 数据
///
/// 此字段存放消息内容中未编码的 json 数据。
/// SDK 内置的消息，如果消息解码失败，默认会将消息的内容存放到此字段；如果编码和解码正常，此字段会置为 nil。
@property (nonatomic, strong, nullable, setter=setRawJSONData:) NSData *rawJSONData;


#pragma mark - json tools

/// 消息基类提供的安全校验方法 JSON->Map
/// @param jsonData json 二进制数据
/// @return 非字典，返回 nil
/// - Since: 5.4.0
+ (nullable NSDictionary *)dictionaryFromJsonData:(NSData *)jsonData;

/// 消息基类提供的安全校验方法 JSON->Array
/// - Parameter jsonData: json 二进制数据
/// - Returns: 非数组，返回 nil
/// - Since: 5.4.0
+ (nullable NSArray *)arrayFromJsonData:(NSData *)jsonData;


@end

NS_ASSUME_NONNULL_END

#endif
