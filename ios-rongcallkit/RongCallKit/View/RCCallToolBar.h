//
//  RCCallToolBar.h
//  RongCallKit
//
//  Created by Vicky on 2018/5/23.
//  Copyright © 2018年 Rong Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef void (^RCCallToolBarConfirmBlock)();

@interface RCCallToolBar : UIView

@property (nonatomic, strong) UILabel *numberLabel;

@property (nonatomic, strong) UIButton *confirmButton;

- (instancetype)initWithFrame:(CGRect)frame withBlock:(RCCallToolBarConfirmBlock)block;

@end
