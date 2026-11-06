//
//  RCMessageTool.h
//  RongIMKit
//
//  Created by 张改红 on 2020/6/11.
//  Copyright © 2020 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "RCMessageModel.h"

#define DestructBackGroundWidth 132
#define DestructBackGroundHeight 132

@interface RCMessageCellTool : NSObject
+ (UIImage *)getDefaultMessageCellBackgroundImage:(RCMessageModel *)model;
+ (CGFloat)getMessageContentViewMaxWidth;
/// 根据消息所在容器宽度计算气泡最大宽度，供内部测量链路使用。
+ (CGFloat)getMessageContentViewMaxWidthWithContainerWidth:(CGFloat)containerWidth;
+ (CGSize)getThumbnailImageSize:(UIImage *)image;
+ (NSDictionary *)getTextLinkOrPhoneNumberAttributeDictionary:(RCMessageDirection)msgDirection;
+ (UIImage *)translationTextBackgroundImage;
@end

