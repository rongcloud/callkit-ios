//
//  RCAudioMultiCallUserCollectionLayout.h
//  RongCallKit
//
//  Created by litao on 16/3/18.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface RCAudioMultiCallUserCollectionLayout : UICollectionViewFlowLayout

@property(nonatomic, assign) CGFloat itemMargin;
@property(nonatomic, assign) CGFloat buttomPadding;

- (instancetype)initWithItemMargin:(CGFloat)itemMargin buttomPadding:(CGFloat)buttomPadding;

@end
