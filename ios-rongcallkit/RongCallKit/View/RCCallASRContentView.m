//
//  RCCallASRContentView.m
//  RongCallKit
//
//  Created by RongCloud on 25/9/6.
//  Copyright © 2025年 RongCloud. All rights reserved.
//

#import "RCCallASRContentView.h"
#import "RCCallKitUtility.h"
@interface RCCallASRContentView ()

@property (nonatomic, strong) RCloudImageView *asrAvatarImageView;
@property (nonatomic, strong) UILabel *asrNameLabel;
@property (nonatomic, strong) UITextView *asrTextView;
@property (nonatomic, strong) UITextView *asrTranslationTextView;
@property (nonatomic, strong) NSMutableArray<NSLayoutConstraint *> *constraints;

@end

@implementation RCCallASRContentView


- (instancetype)initWithDislayASRTextView:(BOOL)dislayASRTextView
             dislayASRTranslationTextView:(BOOL)displayASRTranslationTextView {
    if (self = [super init]) {
        [self updateWithDislayASRTextView:dislayASRTextView dislayASRTranslationTextView:displayASRTranslationTextView];
    }
    return self;
}

- (void)updateWithDislayASRTextView:(BOOL)dislayASRTextView
       dislayASRTranslationTextView:(BOOL)displayASRTranslationTextView {
    self.translatesAutoresizingMaskIntoConstraints = NO;
    if (self.constraints.count) {
        [NSLayoutConstraint deactivateConstraints:self.constraints];
    }
    self.constraints = [NSMutableArray<NSLayoutConstraint *> new];
    
    // 头像和名称标签约束（始终显示）
    [self.constraints addObjectsFromArray:@[
        [self.asrAvatarImageView.leadingAnchor constraintEqualToAnchor:self.leadingAnchor constant:0],
        [self.asrAvatarImageView.topAnchor constraintEqualToAnchor:self.topAnchor constant:0],
        [self.asrAvatarImageView.widthAnchor constraintEqualToConstant:40],
        [self.asrAvatarImageView.heightAnchor constraintEqualToConstant:40],
    
        [self.asrNameLabel.leadingAnchor constraintEqualToAnchor:_asrAvatarImageView.trailingAnchor constant:8],
        [self.asrNameLabel.centerYAnchor constraintEqualToAnchor:_asrAvatarImageView.centerYAnchor],
        [self.asrNameLabel.widthAnchor constraintEqualToConstant:80],
        [self.asrNameLabel.heightAnchor constraintEqualToConstant:21],
    ]];
    
    // 根据参数决定是否显示文本视图
    self.asrTextView.hidden = !dislayASRTextView;
    self.asrTranslationTextView.hidden = !displayASRTranslationTextView;
    
    // 添加子视图
    [self addSubview:self.asrAvatarImageView];
    [self addSubview:self.asrNameLabel];
    [self addSubview:self.asrTextView];
    [self addSubview:self.asrTranslationTextView];
    
    // 动态设置文本视图约束
    UIView *previousView = self.asrAvatarImageView;
    CGFloat currentTop = 40; // 头像高度
    
    if (dislayASRTextView) {
        [self.constraints addObjectsFromArray:@[
            [self.asrTextView.leadingAnchor constraintEqualToAnchor:self.leadingAnchor constant:0],
            [self.asrTextView.topAnchor constraintEqualToAnchor:previousView.bottomAnchor constant:6],
            [self.asrTextView.trailingAnchor constraintEqualToAnchor:self.trailingAnchor constant:0],
            [self.asrTextView.heightAnchor constraintEqualToConstant:30],
        ]];
        previousView = self.asrTextView;
        currentTop += 36; // 文本视图高度 + 间距
    }
    
    if (displayASRTranslationTextView) {
        [self.constraints addObjectsFromArray:@[
            [self.asrTranslationTextView.leadingAnchor constraintEqualToAnchor:self.leadingAnchor constant:0],
            [self.asrTranslationTextView.topAnchor constraintEqualToAnchor:previousView.bottomAnchor constant:6],
            [self.asrTranslationTextView.trailingAnchor constraintEqualToAnchor:self.trailingAnchor constant:0],
            [self.asrTranslationTextView.heightAnchor constraintEqualToConstant:30],
        ]];
        currentTop += 36; // 翻译文本视图高度 + 间距
    }
    // 设置总高度约束
    [self.constraints addObject:[self.heightAnchor constraintEqualToConstant:currentTop]];
    
    // 激活所有约束
    [NSLayoutConstraint activateConstraints:self.constraints];
    
    [self setNeedsLayout];
    [self layoutIfNeeded];
}

- (void)resetContent {
    [_asrAvatarImageView setPlaceholderImage:nil];
    _asrNameLabel.text = @"";
    _asrTextView.text = @"";
    _asrTranslationTextView.text = @"";
    _userId = @"";
    _msgId = @"";
    _timeUTC = 0;
}

- (RCloudImageView *)asrAvatarImageView {
    if (!_asrAvatarImageView) {
        _asrAvatarImageView = [[RCloudImageView alloc] init];
        _asrAvatarImageView.layer.masksToBounds = YES;
        if (RCKitConfigCenter.ui.globalConversationAvatarStyle == RC_USER_AVATAR_CYCLE &&
            RCKitConfigCenter.ui.globalMessageAvatarStyle == RC_USER_AVATAR_CYCLE) {
            _asrAvatarImageView.layer.cornerRadius = 20.f;
        } else {
            _asrAvatarImageView.layer.cornerRadius = 4.f;
        }
        _asrAvatarImageView.translatesAutoresizingMaskIntoConstraints = NO;
    }
    return _asrAvatarImageView;
}

- (UILabel *)asrNameLabel {
    if (!_asrNameLabel) {
        _asrNameLabel = [[UILabel alloc] init];
        _asrNameLabel.translatesAutoresizingMaskIntoConstraints = NO;
        _asrNameLabel.font = [UIFont systemFontOfSize:12];
        _asrNameLabel.textColor = [UIColor blackColor];
        _asrNameLabel.lineBreakMode = NSLineBreakByTruncatingTail;
    }
    return _asrNameLabel;
}

- (UITextView *)asrTextView {
    if (!_asrTextView) {
        _asrTextView = [[UITextView alloc] init];
        _asrTextView.translatesAutoresizingMaskIntoConstraints = NO;
        _asrTextView.textContainer.lineFragmentPadding = 0;
        _asrTextView.textContainerInset = UIEdgeInsetsMake(0, 0, 0, 0);
        _asrTextView.layer.borderWidth = 0;
        _asrTextView.showsVerticalScrollIndicator = NO;
        _asrTextView.showsHorizontalScrollIndicator = NO;
        _asrTextView.userInteractionEnabled = NO;
        _asrTextView.backgroundColor = [UIColor clearColor];
        _asrTextView.font = [UIFont systemFontOfSize:12];
        _asrTextView.textColor = [UIColor blackColor];
    }
    return _asrTextView;
}

- (UITextView *)asrTranslationTextView {
    if (!_asrTranslationTextView) {
        _asrTranslationTextView = [[UITextView alloc] init];
        _asrTranslationTextView.translatesAutoresizingMaskIntoConstraints = NO;
        _asrTranslationTextView.textContainer.lineFragmentPadding = 0;
        _asrTranslationTextView.textContainerInset = UIEdgeInsetsMake(0, 0, 0, 0);
        _asrTranslationTextView.layer.borderWidth = 0;
        _asrTranslationTextView.showsVerticalScrollIndicator = NO;
        _asrTranslationTextView.showsHorizontalScrollIndicator = NO;
        _asrTranslationTextView.userInteractionEnabled = NO;
        _asrTranslationTextView.backgroundColor = [UIColor clearColor];
        _asrTranslationTextView.font = [UIFont systemFontOfSize:12];
        _asrTranslationTextView.textColor = [UIColor blackColor];
        
    }
    return _asrTranslationTextView;
}

@end
