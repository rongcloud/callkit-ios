//
//  RCPluginBoardView.h
//  RongExtensionKit
//
//  Created by Liv on 15/3/15.
//  Copyright (c) 2015年 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RCBaseCollectionView.h"
@protocol RCPluginBoardViewDelegate;

/*!
 输入扩展功能板的View
 */
@interface RCPluginBoardView : UIView

/*!
 当前所有的扩展项
 */
@property (nonatomic, strong) NSMutableArray *allItems;

/*!
 展示所有的功能按钮
 */
@property (nonatomic, strong) RCBaseCollectionView *contentView;

/*!
 扩展view ，此视图会覆盖加号区域其他视图，默认隐藏
 */
@property (nonatomic, strong) UIView *extensionView;

/*!
 扩展功能板的点击回调
 */
@property (nonatomic, weak) id<RCPluginBoardViewDelegate> pluginBoardDelegate;

/*!
 向扩展功能板中插入扩展项

 - Parameter normalImage: 扩展项的展示图片
 - Parameter highlightedImage: 扩展项的触摸高亮图片
 - Parameter title: 扩展项的展示标题
 - Parameter index: 需要添加到的索引值
 - Parameter tag:   扩展项的唯一标识符

  您以在RCConversationViewController的viewdidload后，添加自定义的扩展项。
 SDK默认的扩展项的唯一标识符为1XXX，我们建议您在自定义扩展功能时不要选用1XXX，以免与SDK预留的扩展项唯一标识符重复。
 */
- (void)insertItem:(UIImage *)normalImage highlightedImage:(UIImage *)highlightedImage title:(NSString *)title atIndex:(NSInteger)index tag:(NSInteger)tag;

/*!
 添加扩展项到扩展功能板，并在显示为最后一项

 - Parameter normalImage: 扩展项的展示图片
 - Parameter highlightedImage: 扩展项的触摸高亮图片
 - Parameter title: 扩展项的展示标题
 - Parameter tag:   扩展项的唯一标识符

  您以在RCConversationViewController的viewdidload后，添加自定义的扩展项。
 SDK默认的扩展项的唯一标识符为1XXX，我们建议您在自定义扩展功能时不要选用1XXX，以免与SDK预留的扩展项唯一标识符重复。
 */
- (void)insertItem:(UIImage *)normalImage highlightedImage:(UIImage *)highlightedImage title:(NSString *)title tag:(NSInteger)tag;

/*!
 更新指定扩展项

 - Parameter index: 扩展项的索引值
 - Parameter normalImage: 扩展项的展示图片
 - Parameter highlightedImage: 扩展项的触摸高亮图片
 - Parameter title: 扩展项的展示标题
 */
- (void)updateItemAtIndex:(NSInteger)index normalImage:(UIImage *)normalImage highlightedImage:(UIImage *)highlightedImage title:(NSString *)title;

/*!
 更新指定扩展项

 - Parameter tag:   扩展项的唯一标识符
 - Parameter normalImage: 扩展项的展示图片
 - Parameter highlightedImage: 扩展项的触摸高亮图片
 - Parameter title: 扩展项的展示标题
 */
- (void)updateItemWithTag:(NSInteger)tag normalImage:(UIImage *)normalImage highlightedImage:(UIImage *)highlightedImage title:(NSString *)title;

/*!
 删除扩展功能板中的指定扩展项

 - Parameter index: 指定扩展项的索引值
 */
- (void)removeItemAtIndex:(NSInteger)index;

/*!
 删除扩展功能板中的指定扩展项

 - Parameter tag: 指定扩展项的唯一标识符
 */
- (void)removeItemWithTag:(NSInteger)tag;

/*!
 删除扩展功能板中的所有扩展项
 */
- (void)removeAllItems;
@end

/*!
 扩展功能板的点击回调
 */
@protocol RCPluginBoardViewDelegate <NSObject>

/*!
 点击扩展功能板中的扩展项的回调

 - Parameter pluginBoardView: 当前扩展功能板
 - Parameter tag:             点击的扩展项的唯一标识符
 */
- (void)pluginBoardView:(RCPluginBoardView *)pluginBoardView clickedItemWithTag:(NSInteger)tag;

@end
