//
//  RCVideoCollectionViewLayout.m
//  RongCallKit
//
//  Created by Vicky on 2018/5/29.
//  Copyright © 2018年 Rong Cloud. All rights reserved.
//

#import "RCVideoCollectionViewLayout.h"
@interface RCVideoCollectionViewLayout ()
@property (nonatomic, strong) NSMutableArray *attributesArray;
@property (nonatomic, assign) CGFloat itemAreaWidth;
@property (nonatomic, assign) CGFloat itemWidth;

@end

@implementation RCVideoCollectionViewLayout

//- (void)prepareLayout {
//    int itemCount = (int)[self.collectionView numberOfItemsInSection:0];
//    if (itemCount == 0) {
//        [super prepareLayout];
//        return;
//    }
//
//    NSMutableArray *attributesArrays = [NSMutableArray array];
//    CGFloat nowWidth = self.itemSize.width * [self.collectionView numberOfItemsInSection:0]+ (self.minimumInteritemSpacing * ([self.collectionView numberOfItemsInSection:0] - 1)) + _collectionViewContentInset.left  ;
//    for (NSInteger i = 0; i < [self.collectionView numberOfItemsInSection:0]; i++) {
//        //        NSIndexPath *indexPath = [NSIndexPath indexPathForItem:i inSection:0];
//        UICollectionViewLayoutAttributes *attribute = [UICollectionViewLayoutAttributes
//                                                        layoutAttributesForCellWithIndexPath:[NSIndexPath indexPathForItem:i inSection:0]];
//
//        attributes.frame = CGRectMake(nowWidth - self.itemSize.width,
//                                      _collectionViewContentInset.top, self.customItemSize.width, self.customItemSize.height);
//
//        [self.attributesArray addObject:attribute];
//        nowWidth = nowWidth - attribute.frame.size.width - self.minimumInteritemSpacing;
////        [attributes addObject:[self layoutAttributesForItemAtIndexPath:indexPath]];
//    }
//
////
////    CGRect frame = self.collectionView.bounds;
////    self.customItemSize = self.itemSize;
////
////    self.attributesArray = [[NSMutableArray alloc] init];
////    if (itemCount <= 8) {
////        CGFloat totalWidth = (self.itemSize.width + self.minimumInteritemSpacing) * itemCount;
//////        if (totalWidth < _collectionViewWidth) {
////            totalWidth = _collectionViewWidth;
//////        }
////        CGFloat nowWidth = self.collectionView.frame.size.width - _collectionViewContentInset.right + self.collectionView.contentOffset.x;
////
////
////
////        for (int i = 0; i < itemCount; i++) {
////            UICollectionViewLayoutAttributes *attributes = [UICollectionViewLayoutAttributes
////                                                            layoutAttributesForCellWithIndexPath:[NSIndexPath indexPathForItem:i inSection:0]];
////            attributes.frame = CGRectMake(nowWidth - (i + 1) * (_customItemSize.width) - (i) * self.minimumInteritemSpacing ,
////                                          _collectionViewContentInset.top, self.customItemSize.width, self.customItemSize.height);
////
//////            attributes.frame = CGRectMake(_collectionViewWidth - _contentInset.right - i * (self.minimumInteritemSpacing) - _customItemSize.width * (i + 1),
//////                                         _contentInset.top, self.customItemSize.width, self.customItemSize.height);
////
////            [self.attributesArray addObject:attributes];
////        }
//////        for (int i = itemCount-1; i >= 0; i--) {
//////            UICollectionViewLayoutAttributes *attributes = [UICollectionViewLayoutAttributes
//////                                                            layoutAttributesForCellWithIndexPath:[NSIndexPath indexPathForItem:i inSection:0]];
//////            attributes.frame = CGRectMake(_contentInset.left + i * (self.minimumInteritemSpacing + _customItemSize.width) * (i),
//////                                          _contentInset.top, self.customItemSize.width, self.customItemSize.height);
//////
//////            [self.attributesArray addObject:attributes];
//////        }
////
////    }
////
//    [super prepareLayout];
//}
- (CGSize)collectionViewContentSize {
    return CGSizeMake(self.itemSize.width * [self.collectionView numberOfItemsInSection:0] +
                          (self.minimumInteritemSpacing * ([self.collectionView numberOfItemsInSection:0] - 1)) +
                          _collectionViewContentInset.left + _collectionViewContentInset.right,
                      0);
}

- (UICollectionViewLayoutAttributes *)layoutAttributesForItemAtIndexPath:(NSIndexPath *)path {
    UICollectionViewLayoutAttributes *attributes = [self.attributesArray objectAtIndex:[path row]];
    return attributes;
}

- (NSArray *)layoutAttributesForElementsInRect:(CGRect)rect {
    NSArray *layoutAttributes_t = [super layoutAttributesForElementsInRect:rect];
    NSArray *layoutAttributes = [[NSArray alloc] initWithArray:layoutAttributes_t copyItems:YES];

    NSMutableArray *attributesArrays = [NSMutableArray array];
    CGFloat nowWidth = self.itemSize.width * [self.collectionView numberOfItemsInSection:0] +
        (self.minimumInteritemSpacing * ([self.collectionView numberOfItemsInSection:0] - 1)) +
        _collectionViewContentInset.left;
    //    self.collectionView.contentOffset = CGPointMake(self.collectionView.frame.size.width, 0);
    if (nowWidth < self.collectionView.frame.size.width - _collectionViewContentInset.left) {
        nowWidth = self.collectionView.frame.size.width - _collectionViewContentInset.left;
    }
    for (NSInteger i = 0; i < layoutAttributes.count; i++) {
        //        NSIndexPath *indexPath = [NSIndexPath indexPathForItem:i inSection:0];
        UICollectionViewLayoutAttributes *attribute = [layoutAttributes objectAtIndex:i];
        CGRect nowFrame = attribute.frame;
        nowFrame.origin.x = nowWidth - attribute.frame.size.width;
        attribute.frame = nowFrame;
        [attributesArrays addObject:attribute];
        nowWidth = nowWidth - attribute.frame.size.width - self.minimumInteritemSpacing;
        //        [attributes addObject:[self layoutAttributesForItemAtIndexPath:indexPath]];
    }
    self.attributesArray = attributesArrays;
    return attributesArrays;
}

@end
