//
//  RCEmoticonTabSource.h
//  RongExtensionKit
//
//  Created by litao on 16/9/13.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>

/// 自定义表情view数据源代理
@protocol RCEmoticonTabSource <NSObject>

/*!
 表情tab的标识符
 - Returns: 表情tab的标识符，请勿重复
 */
- (NSString *)identify;

/*!
 表情tab的图标
 - Returns: 表情tab的图标
 */
- (UIImage *)image;

/*!
 表情tab的页数
 - Returns: 表情tab的页数
 */
- (int)pageCount;
/*!
 表情tab的index页的表情View

 - Returns: 表情tab的index页的表情View
  返回的 view 大小必须等于 contentViewSize （宽度 = 屏幕宽度，高度 = 186）
 */
- (UIView *)loadEmoticonView:(NSString *)identify index:(int)index;
@end
