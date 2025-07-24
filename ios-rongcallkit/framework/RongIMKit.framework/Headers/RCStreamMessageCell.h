//
//  RCStreamMessageCellCollectionViewCell.h
//  SealTalk
//
//  Created by zgh on 2025/2/20.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import "RCMessageCell.h"
#import "RCReferencedContentView.h"

NS_ASSUME_NONNULL_BEGIN

extern NSString *const RCStreamMessageCellUpdateEndNotification;

@interface RCStreamMessageCell : RCMessageCell

@property (nonatomic, weak) UICollectionView *hostView;

/// 引用内容展示的容器
@property (nonatomic, strong) RCReferencedContentView *referencedContentView;

@end

NS_ASSUME_NONNULL_END
