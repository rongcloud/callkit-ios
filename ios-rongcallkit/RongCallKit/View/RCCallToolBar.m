//
//  RCCallToolBar.m
//  RongCallKit
//
//  Created by Vicky on 2018/5/23.
//  Copyright © 2018年 Rong Cloud. All rights reserved.
//

#import "RCCallToolBar.h"
#import "RCCallKitUtility.h"
@interface RCCallToolBar ()
{
    RCCallToolBarConfirmBlock callBackBlock;
}
@end

@implementation RCCallToolBar

- (instancetype)initWithFrame:(CGRect)frame withBlock:(RCCallToolBarConfirmBlock) block
{
    if (self = [super initWithFrame:frame]) {
        callBackBlock = block;
        [self configUI];
    }
    return self;
}

- (UILabel *)numberLabel
{
    if (!_numberLabel) {
        _numberLabel = [[UILabel alloc] init];
        _numberLabel.textAlignment = NSTextAlignmentLeft;
        _numberLabel.textColor = [UIColor colorWithRed:168/255.0 green:168/255.0 blue:168/255.0 alpha:1/1.0];
    }
    return _numberLabel;
}

- (UIButton *)confirmButton
{
    if (!_confirmButton) {
        _confirmButton = [[UIButton alloc] initWithFrame:CGRectMake(UIScreen.mainScreen.bounds.size.width - 80, 17, 80.0, 30.0)];
        [_confirmButton setTitle:NSLocalizedStringFromTable(@"OK", @"RongCloudKit", nil) forState:UIControlStateNormal];
        [_confirmButton setTitleColor:dynamic_color(0x3A91F3, 0x007acc) forState:(UIControlStateNormal)];
        [_confirmButton setTitleColor:dynamic_color(0xA8A8A8,0x666666) forState:(UIControlStateDisabled)];
        _confirmButton.enabled = NO;
        [_confirmButton addTarget:self
                            action:@selector(confirmButtonClicked)
                  forControlEvents:UIControlEventTouchUpInside];
    }
    return _confirmButton;
}

- (void)confirmButtonClicked
{
    callBackBlock();
}


- (void)configUI
{
    self.backgroundColor = dynamic_color(0xffffff,0x1a1a1a);
    self.numberLabel.frame = CGRectMake(15.0, (self.frame.size.height - 30.0) / 2, UIScreen.mainScreen.bounds.size.width/2, 30.0);
    self.numberLabel.textColor = [UIColor colorWithRed:58/255.0 green:145/255.0 blue:243/255.0 alpha:1/1.0];
    self.confirmButton.frame = CGRectMake(UIScreen.mainScreen.bounds.size.width - 80, (self.frame.size.height - 30.0) / 2, 80.0, 30.0);
    
    [self addSubview:self.confirmButton];
    [self addSubview:self.numberLabel];
 
    self.confirmButton.enabled = NO;
    
}


@end
