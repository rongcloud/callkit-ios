//
//  RCCollectionViewModelProtocol.h
//  RongIMKit
//
//  Created by zgh on 2024/8/23.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol RCCollectionViewModelResponder <NSObject>

@optional

/// reload data
- (void)reloadCollectionViewData;

@end

/// RCCollectionViewModelProtocol
/// - Since: 5.12.0
@protocol RCCollectionViewModelProtocol <NSObject>

@optional

/// collectionView section count
- (NSInteger)numberOfSectionsInCollectionView;

/// collectionView section item count
- (NSInteger)numberOfItemsInSection:(NSInteger)section;

/// 返回 cell
///
/// - Parameters collectionView: collectionView
/// - Parameters indexPath: indexPath
- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath;

/// 配置内边距
///
/// - Parameters collectionView: collectionView
/// - Parameters collectionViewLayout: collectionViewLayout
/// - Parameters section: section
- (UIEdgeInsets)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout insetForSectionAtIndex:(NSInteger)section;

/// 点击 cell
///
/// - Parameters collectionView: collectionView
/// - Parameters indexPath: indexPath
- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath;


@end

NS_ASSUME_NONNULL_END
