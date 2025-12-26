//
//  RCSizeCalculateLabel.h
//  RongIMKit
//
//  Created by RobinCui on 2025/11/14.
//  Copyright © 2025 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
@protocol RCSizeCalculateLabelDelegate <NSObject>

- (void)labelLayoutFinished:(UILabel *)label
                 natureSize:(CGSize)natureSize;

@end
@interface RCSizeCalculateLabel : UILabel
@property (nonatomic, weak) id<RCSizeCalculateLabelDelegate> delegate;
@end

NS_ASSUME_NONNULL_END
