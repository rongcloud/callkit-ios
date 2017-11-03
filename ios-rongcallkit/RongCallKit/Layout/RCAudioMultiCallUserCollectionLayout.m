//
//  RCAudioMultiCallUserCollectionLayout.m
//  RongCallKit
//
//  Created by litao on 16/3/18.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCAudioMultiCallUserCollectionLayout.h"

@interface RCAudioMultiCallUserCollectionLayout ()
@property(nonatomic, strong) NSMutableArray *attributesArray;
@property(nonatomic, assign) CGFloat itemAreaWidth;
@property(nonatomic, assign) CGFloat itemWidth;
@end

@implementation RCAudioMultiCallUserCollectionLayout

- (instancetype)initWithItemMargin:(CGFloat)itemMargin buttomPadding:(CGFloat)buttomPadding {
    self = [super init];
    if (self) {
        self.itemMargin = itemMargin;
        self.buttomPadding = buttomPadding;
    }
    return self;
}

- (CGFloat)itemAreaWidth {
    if (!_itemAreaWidth) {
        CGRect frame = self.collectionView.bounds;
        _itemAreaWidth = MIN((frame.size.width / 4), (frame.size.height - self.buttomPadding) / 2);
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
        int topCount = (itemCount <= 4) ? itemCount : 4;

        CGFloat topY = (frame.size.height - self.buttomPadding) / 2 - self.itemAreaWidth +
                       (topCount == itemCount ? self.itemAreaWidth / 2 : 0);
        CGFloat leftX1 = (frame.size.width - self.itemAreaWidth * topCount) / 2;               // line1
        CGFloat leftX2 = (frame.size.width - self.itemAreaWidth * (itemCount - topCount)) / 2; // line2
        for (int i = 0; i < itemCount; i++) {
            UICollectionViewLayoutAttributes *attributes = [UICollectionViewLayoutAttributes
                layoutAttributesForCellWithIndexPath:[NSIndexPath indexPathForItem:i inSection:0]];
            if (i < topCount) {
                attributes.frame = CGRectMake(leftX1 + self.itemAreaWidth * i + self.itemMargin, topY + self.itemMargin,
                                              self.itemWidth, self.itemWidth);
            } else {
                attributes.frame =
                    CGRectMake(leftX2 + self.itemAreaWidth * (i - topCount) + self.itemMargin,
                               topY + self.itemMargin + self.itemWidth + self.itemMargin + self.itemMargin,
                               self.itemWidth, self.itemWidth);
            }
            [self.attributesArray addObject:attributes];
        }
    } else {
        int lines = (itemCount - 1) / 4 + 1;
        CGFloat topY = (frame.size.height - self.buttomPadding) / 2 - self.itemAreaWidth;
        for (int line = 0; line < lines; line++) {
            int maxCloumn = line < (lines - 1) ? 4 : (itemCount - (lines - 1) * 4);
            for (int cloumn = 0; cloumn < maxCloumn; cloumn++) {
                int index = line * 4 + cloumn;
                UICollectionViewLayoutAttributes *attributes = [UICollectionViewLayoutAttributes
                    layoutAttributesForCellWithIndexPath:[NSIndexPath indexPathForItem:index inSection:0]];
                attributes.frame =
                    CGRectMake((frame.size.width - self.itemAreaWidth * maxCloumn) / 2 + self.itemAreaWidth * cloumn +
                                   self.itemMargin,
                               topY + self.itemAreaWidth * line + self.itemMargin, self.itemWidth, self.itemWidth);
                [self.attributesArray addObject:attributes];
                NSLog(@"the index is %d", index);
                NSLog(@"frame is %f, %f, %f, %f", attributes.frame.origin.x, attributes.frame.origin.y,
                      attributes.frame.size.width, attributes.frame.size.height);
            }
        }
    }

    // let the flow layout calc the size.
    self.scrollDirection = UICollectionViewScrollDirectionVertical;

    [super prepareLayout];
}
- (CGSize)collectionViewContentSize {
    if ([self.collectionView numberOfItemsInSection:0] <= 8) {
        return [self collectionView].frame.size;
    } else {
        //        if (self.scrollDirection ==
        //        UICollectionViewScrollDirectionVertical) {
        int lines = ((int)[self.collectionView numberOfItemsInSection:0] - 1) / 4 + 1;
        CGFloat height =
            [self collectionView].frame.size.height + self.itemAreaWidth * (lines - 2) - self.buttomPadding;
        return CGSizeMake([self collectionView].frame.size.width, height);
    }
}
- (UICollectionViewLayoutAttributes *)layoutAttributesForItemAtIndexPath:(NSIndexPath *)path {
    //    if ([self.collectionView numberOfItemsInSection:0] <= 8) {
    UICollectionViewLayoutAttributes *attributes = [self.attributesArray objectAtIndex:[path row]];
    return attributes;
    //    } else {
    //        return [super layoutAttributesForItemAtIndexPath:path];
    //    }
}

- (NSArray *)layoutAttributesForElementsInRect:(CGRect)rect {
    //    if ([self.collectionView numberOfItemsInSection:0] <= 8) {
    NSMutableArray *attributes = [NSMutableArray array];
    for (NSInteger i = 0; i < [self.collectionView numberOfItemsInSection:0]; i++) {
        NSIndexPath *indexPath = [NSIndexPath indexPathForItem:i inSection:0];
        [attributes addObject:[self layoutAttributesForItemAtIndexPath:indexPath]];
    }
    return attributes;
    //    } else {
    //        return [super layoutAttributesForElementsInRect:rect];
    //    }
}
@end
