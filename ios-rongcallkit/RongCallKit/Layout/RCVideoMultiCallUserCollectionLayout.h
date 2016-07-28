//
//  RCVideoMultiCallUserCollectionLayout.h
//  RongCallKit
//
//  Created by litao on 16/3/22.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface RCVideoMultiCallUserCollectionLayout : UICollectionViewLayout

@property(nonatomic, assign) CGFloat itemMargin;

- (instancetype)initWithItemMargin:(CGFloat)itemMargin;

@end
