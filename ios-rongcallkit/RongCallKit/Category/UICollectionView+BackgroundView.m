//
//  UICollectionView+BackgroundView.m
//  RongCallKit
//
//  Created by LiuLinhong on 2018/03/30.
//  Copyright © 2018年 Rong Cloud. All rights reserved.
//

#import "UICollectionView+BackgroundView.h"
#import <objc/runtime.h>

static NSString *key = @"UICollectionView_BackgroundView";

@implementation UICollectionView (BackgroundView)

- (UIView *)hitTest:(CGPoint)point withEvent:(UIEvent *)event
{
    if (self.tag != 202872) {
        return [super hitTest:point withEvent:event];
    }
    
    NSInteger userCellCount = [self.callVideoMultiCallViewController.subUserModelList count];
    UIView *touchView = self;
    if ([self pointInside:point withEvent:event] && self.alpha >= 0.01 && !self.hidden && self.isUserInteractionEnabled)
    {
        if ([self isTouchEnable:userCellCount withPoint:point])
        {
            return nil;
        }

        if ([self.subviews count] > 0)
        {
            for (NSInteger i = ([self.subviews count] - 1); i >= 0; --i)
            {
                UIView *subView = self.subviews[i];
                CGPoint subPoint = CGPointMake(point.x - subView.frame.origin.x,
                                               point.y - subView.frame.origin.y);
                UIView *subTouchView = [subView hitTest:subPoint withEvent:event];
                if (subTouchView)
                {
                    touchView = subTouchView;
                    break;
                }
            }
        }
    }
    else
    {
        touchView = nil;
    }

    return touchView;
}

- (BOOL)pointInside:(CGPoint)point withEvent:(UIEvent *)event
{
    return CGRectContainsPoint(self.bounds, point);
}

- (void)setCallVideoMultiCallViewController:(RCCallVideoMultiCallViewController *)vc
{
    objc_setAssociatedObject(self, (__bridge const void *)(key), vc, OBJC_ASSOCIATION_ASSIGN);
}

- (RCCallVideoMultiCallViewController *)callVideoMultiCallViewController
{
    return objc_getAssociatedObject(self, (__bridge const void *)(key));
}

- (BOOL)isTouchEnable:(NSInteger)count withPoint:(CGPoint)point
{
    if (self.tag != 202872)
        return NO;
    switch (count) {
        case 0:
            return YES;
        default:
        {
            if (point.x <= 10.0 + 84 * count) {
//                CGFloat nowWidth = 84.0 * count+ (10.0 * (count - 1)) + 20.0  ;
//                if (nowWidth < UIScreen.mainScreen.bounds.size.width) {
//                    if (point.x < UIScreen.mainScreen.bounds.size.width - nowWidth) {
//                        return YES;
//                    }else{
//                        return NO;
//                    }
//                }else{
//                    if (point.x < 20.0) {
//                        return YES;
//                    }else{
//                        return NO;
//                    }
//                }
                
                return NO;
            }else
                return YES;
        }
    }
    
    return NO;
}

@end
