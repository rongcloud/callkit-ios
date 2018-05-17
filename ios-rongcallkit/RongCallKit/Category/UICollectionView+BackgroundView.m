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
    if (self.tag != 202)
        return NO;
    
    switch (count)
    {
        case 1:
            if (point.x > 270 && point.y > 85)
                return NO;
            else
                return YES;
        case 2:
            if (point.x > 190 && point.y > 85)
                return NO;
            else
                return YES;
        case 3:
            if (point.x > 110 && point.y > 85)
                return NO;
            else
                return YES;
        case 4:
            if (point.y > 85)
                return NO;
            else
                return YES;
        case 5:
            if (point.x < 270 && point.y < 85)
                return YES;
            else
                return NO;
        case 6:
            if (point.x < 190 && point.y < 85)
                return YES;
            else
                return NO;
        case 7:
            if (point.x < 110 && point.y < 85)
                return YES;
            else
                return NO;
        case 8:
            return NO;
        default:
            return NO;
    }
    return NO;
}

@end
