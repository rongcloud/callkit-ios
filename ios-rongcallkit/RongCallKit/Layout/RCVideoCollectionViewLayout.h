//
//  RCVideoCollectionViewLayout.h
//  RongCallKit
//
//  Created by Vicky on 2018/5/29.
//  Copyright © 2018年 Rong Cloud. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface RCVideoCollectionViewLayout : UICollectionViewFlowLayout

@property (nonatomic, assign) CGSize customItemSize;
@property (nonatomic, assign) UIEdgeInsets collectionViewContentInset;
@property (nonatomic, assign) CGFloat collectionViewWidth;

@end
