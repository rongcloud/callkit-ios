//
//  RCArButton.m
//  RongCallKit
//
//  Created by Rong Cloud on 2021/1/11.
//  Copyright © 2021 Rong Cloud. All rights reserved.
//

#import "RCCallTextButton.h"
#import "RCCallKitUtility.h"
#import "RongCallKitAdaptiveHeader.h"

@interface RCCallTextButton ()
@property (nonatomic, strong) NSMutableDictionary *stateMap;
@property (nonatomic, strong) UILabel *tLabel;
@end

@implementation RCCallTextButton

- (void)layoutSubviews {
    [super layoutSubviews];

    if (self.tLabel.text.length > 0) {
        [self.tLabel sizeToFit];

        CGSize size = self.tLabel.bounds.size;

        self.tLabel.center = CGPointMake(self.bounds.size.width / 2.0,
                                         self.bounds.size.height + size.height / 2.0 + RCCallInsideMiniMargin);
    }
}

- (void)setTitle:(NSString *)title forState:(UIControlState)state {
    [super setTitle:nil forState:state];

    self.tLabel.text = title;
    if ([RCKitUtility isRTL]) {
        self.tLabel.textAlignment = NSTextAlignmentRight;
    } else {
        self.tLabel.textAlignment = NSTextAlignmentLeft;
    }
    //映射state文本
    [self.stateMap setValue:title forKey:[self mapStateKey:state]];
}

- (void)setSelected:(BOOL)selected {
    [super setSelected:selected];

    NSString *key = [self mapStateKey:self.state];

    if (self.stateMap && [self.stateMap.allKeys containsObject:key]) {
        self.tLabel.text = self.stateMap[key];
        self.tLabel.frame = CGRectMake(0, self.bounds.size.height, self.bounds.size.width * 2, 26);
    }
}

- (void)setEnabled:(BOOL)enabled {
    NSString *key = [self mapStateKey:self.state];

    if (self.stateMap && [self.stateMap.allKeys containsObject:key]) {
        self.tLabel.text = self.stateMap[key];
        self.tLabel.frame = CGRectMake(0, self.bounds.size.height, self.bounds.size.width * 2, 26);
    }
}

- (void)setHighlighted:(BOOL)highlighted {
    NSString *key = [self mapStateKey:self.state];

    if (self.stateMap && [self.stateMap.allKeys containsObject:key]) {
        self.tLabel.text = self.stateMap[key];
        self.tLabel.frame = CGRectMake(0, self.bounds.size.height, self.bounds.size.width * 2, 26);
    }
}

- (NSString *)mapStateKey:(UIControlState)state {
    switch (state) {
        case UIControlStateHighlighted:
            return @"Highlighted";
        case UIControlStateDisabled:
            return @"Disabled";
        case UIControlStateSelected:
            return @"Selected";
        default:
            break;
    }
    return @"normal";
}

- (UILabel *)tLabel {
    if (!_tLabel) {
        _tLabel =
            [[UILabel alloc] initWithFrame:CGRectMake(0, self.bounds.size.height, self.bounds.size.width * 2, 26)];
        _tLabel.numberOfLines = 2;
        [_tLabel setFont:[UIFont fontWithName:@"PingFangSC-Regular" size:13]];
        _tLabel.textColor = [UIColor whiteColor];
        [self addSubview:_tLabel];
    }
    return _tLabel;
}

- (NSMutableDictionary *)stateMap {
    if (!_stateMap) {
        _stateMap = [NSMutableDictionary new];
    }
    return _stateMap;
}

@end
