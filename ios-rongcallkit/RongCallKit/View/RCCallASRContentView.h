//
//  RCCallASRContentView.h
//  RongCallKit
//
//  Created by RongCloud on 25/9/6.
//  Copyright © 2025年 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "RCloudImageView.h"

@interface RCCallASRContentView : UIView

@property (nonatomic, strong, readonly) RCloudImageView *asrAvatarImageView;
@property (nonatomic, strong, readonly) UILabel *asrNameLabel;
@property (nonatomic, strong, readonly) UITextView *asrTextView;
@property (nonatomic, strong, readonly) UITextView *asrTranslationTextView;

@property (nonatomic, copy) NSString *userId;
@property (nonatomic, copy) NSString *msgId;
@property (nonatomic, assign) NSTimeInterval timeUTC;

- (instancetype)initWithDislayASRTextView:(BOOL)dislayASRTextView
             dislayASRTranslationTextView:(BOOL)displayASRTranslationTextView;

- (void)updateWithDislayASRTextView:(BOOL)dislayASRTextView
       dislayASRTranslationTextView:(BOOL)displayASRTranslationTextView;

- (void)resetContent;



@end
