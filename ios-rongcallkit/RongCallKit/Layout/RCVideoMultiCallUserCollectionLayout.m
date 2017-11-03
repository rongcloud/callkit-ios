//
//  RCVideoMultiCallUserCollectionLayout.m
//  RongCallKit
//
//  Created by litao on 16/3/22.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCVideoMultiCallUserCollectionLayout.h"

@interface RCVideoMultiCallUserCollectionLayout ()
@property(nonatomic, strong) NSMutableArray *attributesArray;
@property(nonatomic, assign) CGFloat itemAreaWidth;
@property(nonatomic, assign) CGFloat itemWidth;
@end

@implementation RCVideoMultiCallUserCollectionLayout

- (instancetype)initWithItemMargin:(CGFloat)itemMargin {
    self = [super init];
    if (self) {
        self.itemMargin = itemMargin;
    }
    return self;
}

- (CGFloat)itemAreaWidth {
    if (!_itemAreaWidth) {
        CGRect frame = self.collectionView.bounds;
        _itemAreaWidth = MIN((frame.size.width / 4), frame.size.height / 2);
    }
    return _itemAreaWidth;
}
- (CGFloat)itemWidth {
    if (!_itemWidth) {
        _itemWidth = self.itemAreaWidth - self.itemMargin - self.itemMargin;
    }
    return _itemWidth;
}
- (void)prepareLayout {
    int itemCount = (int)[self.collectionView numberOfItemsInSection:0];
    if (itemCount == 0) {
        [super prepareLayout];
        return;
    }

    CGRect frame = self.collectionView.bounds;

    self.attributesArray = [[NSMutableArray alloc] init];
    if (itemCount <= 8) {
        CGFloat topY = frame.size.height / 2;
        CGFloat leftMargin = (frame.size.width - self.itemAreaWidth * 4) / 2;
        for (int i = 0; i < itemCount; i++) {
            UICollectionViewLayoutAttributes *attributes = [UICollectionViewLayoutAttributes
                layoutAttributesForCellWithIndexPath:[NSIndexPath indexPathForItem:i inSection:0]];
            if (i < 4) {
                attributes.frame = CGRectMake(leftMargin + (3 - i) * self.itemAreaWidth + self.itemMargin,
                                              topY + self.itemMargin, self.itemWidth, self.itemWidth);
            } else {
                attributes.frame =
                    CGRectMake(leftMargin + (7 - i) * self.itemAreaWidth + self.itemMargin,
                               topY - self.itemAreaWidth + self.itemMargin, self.itemWidth, self.itemWidth);
            }
            [self.attributesArray addObject:attributes];
        }
    }

    [super prepareLayout];
}
- (CGSize)collectionViewContentSize {
    return [self collectionView].frame.size;
}

- (UICollectionViewLayoutAttributes *)layoutAttributesForItemAtIndexPath:(NSIndexPath *)path {
    UICollectionViewLayoutAttributes *attributes = [self.attributesArray objectAtIndex:[path row]];
    return attributes;
}

- (NSArray *)layoutAttributesForElementsInRect:(CGRect)rect {
    NSMutableArray *attributes = [NSMutableArray array];
    for (NSInteger i = 0; i < [self.collectionView numberOfItemsInSection:0]; i++) {
        NSIndexPath *indexPath = [NSIndexPath indexPathForItem:i inSection:0];
        [attributes addObject:[self layoutAttributesForItemAtIndexPath:indexPath]];
    }
    return attributes;
}
@end