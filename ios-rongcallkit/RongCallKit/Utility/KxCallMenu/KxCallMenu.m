//
//  KxCallMenu.m
//  KxCallMenu project
//  https://github.com/kolyvan/kxmenu/
//
//  Created by Kolyvan on 17.05.13.
//

/*
 Copyright (c) 2013 Konstantin Bukreev. All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 - Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 - Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
 Some ideas was taken from QBPopupMenu project by Katsuma Tanaka.
 https://github.com/questbeat/QBPopupMenu
*/

#import "KxCallMenu.h"
#import <QuartzCore/QuartzCore.h>
#pragma GCC diagnostic ignored "-Wundeclared-selector"
//#import "UIColor+RCEColor.h"
//#import "UIImage+RCEImage.h"

const CGFloat kCallArrowSize = 8.f;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

@interface KxCallMenuView : UIView
@end

@interface KxCallMenuOverlay : UIView
@end

@implementation KxCallMenuOverlay

// - (void) dealloc { NSLog(@"dealloc %@", self); }

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        self.backgroundColor = [UIColor clearColor];
        self.opaque = NO;
    }
    return self;
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    UIView *touched = [[touches anyObject] view];
    if (touched == self) {
        for (UIView *v in self.subviews) {
            if ([v isKindOfClass:[KxCallMenuView class]] && [v respondsToSelector:@selector(dismissMenu:)]) {
                [v performSelector:@selector(dismissMenu:) withObject:@(YES)];
            }
        }
    }
}

@end

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

@implementation KxCallMenuItem

+ (instancetype)menuItem:(NSString *)title image:(UIImage *)image target:(id)target action:(SEL)action {
    return [[KxCallMenuItem alloc] init:title image:image target:target action:action];
}

- (id)init:(NSString *)title image:(UIImage *)image target:(id)target action:(SEL)action {
    NSParameterAssert(title.length || image);

    self = [super init];
    if (self) {
        _title = title;
        _image = image;
        _target = target;
        _action = action;
    }
    return self;
}

- (BOOL)enabled {
    return _target != nil && _action != NULL;
}

- (void)performAction {
    __strong id target = self.target;

    if (target && [target respondsToSelector:_action]) {
        [target performSelectorOnMainThread:_action withObject:self waitUntilDone:YES];
    }
}

- (NSString *)description {
    return [NSString stringWithFormat:@"<%@ #%p %@>", [self class], self, _title];
}

@end

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

typedef enum {

    KxCallMenuViewArrowDirectionNone,
    KxCallMenuViewArrowDirectionUp,
    KxCallMenuViewArrowDirectionDown,
    KxCallMenuViewArrowDirectionLeft,
    KxCallMenuViewArrowDirectionRight,

} KxCallMenuViewArrowDirection;

@implementation KxCallMenuView {
    KxCallMenuViewArrowDirection _arrowDirection;
    CGFloat _arrowPosition;
    UIView *_contentView;
    NSArray *_menuItems;
}

- (id)init {
    self = [super initWithFrame:CGRectZero];
    if (self) {
        self.backgroundColor = [UIColor clearColor];
        self.opaque = YES;
        self.alpha = 0;

        self.layer.shadowOpacity = 0.3;
        self.layer.shadowOffset = CGSizeMake(0, 0);
        self.layer.shadowRadius = 5.0;
    }

    return self;
}

// - (void) dealloc { NSLog(@"dealloc %@", self); }

- (void)setupFrameInView:(UIView *)view fromRect:(CGRect)fromRect {
    const CGSize contentSize = _contentView.frame.size;

    const CGFloat outerWidth = view.bounds.size.width;
    const CGFloat outerHeight = view.bounds.size.height;

    const CGFloat rectX0 = fromRect.origin.x;
    const CGFloat rectX1 = fromRect.origin.x + fromRect.size.width;
    const CGFloat rectXM = fromRect.origin.x + fromRect.size.width * 0.5f;
    const CGFloat rectY0 = fromRect.origin.y;
    const CGFloat rectY1 = fromRect.origin.y + fromRect.size.height;
    const CGFloat rectYM = fromRect.origin.y + fromRect.size.height * 0.5f;
    ;

    const CGFloat widthPlusArrow = contentSize.width + kCallArrowSize;
    const CGFloat heightPlusArrow = contentSize.height + kCallArrowSize;
    const CGFloat widthHalf = contentSize.width * 0.5f;
    const CGFloat heightHalf = contentSize.height * 0.5f;

    const CGFloat kMargin = 5.f;

    if (heightPlusArrow < (outerHeight - rectY1)) {
        _arrowDirection = KxCallMenuViewArrowDirectionUp;
        CGPoint point = (CGPoint){rectXM - widthHalf, rectY1 + 16};

        if (point.x < kMargin) point.x = kMargin;

        if ((point.x + contentSize.width + kMargin) > outerWidth) point.x = outerWidth - contentSize.width - kMargin;

        _arrowPosition = rectXM - point.x;
        //_arrowPosition = MAX(16, MIN(_arrowPosition, contentSize.width - 16));
        _contentView.frame = (CGRect){0, kCallArrowSize, contentSize};

        self.frame = (CGRect){

            point, contentSize.width, contentSize.height + kCallArrowSize};

    } else if (heightPlusArrow < rectY0) {
        _arrowDirection = KxCallMenuViewArrowDirectionDown;
        CGPoint point = (CGPoint){rectXM - widthHalf, rectY0 - heightPlusArrow};

        if (point.x < kMargin) point.x = kMargin;

        if ((point.x + contentSize.width + kMargin) > outerWidth) point.x = outerWidth - contentSize.width - kMargin;

        _arrowPosition = rectXM - point.x;
        _contentView.frame = (CGRect){CGPointZero, contentSize};

        self.frame = (CGRect){

            point, contentSize.width, contentSize.height + kCallArrowSize};

    } else if (widthPlusArrow < (outerWidth - rectX1)) {
        _arrowDirection = KxCallMenuViewArrowDirectionLeft;
        CGPoint point = (CGPoint){rectX1, rectYM - heightHalf};

        if (point.y < kMargin) point.y = kMargin;

        if ((point.y + contentSize.height + kMargin) > outerHeight)
            point.y = outerHeight - contentSize.height - kMargin;

        _arrowPosition = rectYM - point.y;
        _contentView.frame = (CGRect){kCallArrowSize, 0, contentSize};

        self.frame = (CGRect){

            point, contentSize.width + kCallArrowSize, contentSize.height};

    } else if (widthPlusArrow < rectX0) {
        _arrowDirection = KxCallMenuViewArrowDirectionRight;
        CGPoint point = (CGPoint){rectX0 - widthPlusArrow, rectYM - heightHalf};

        if (point.y < kMargin) point.y = kMargin;

        if ((point.y + contentSize.height + 5) > outerHeight) point.y = outerHeight - contentSize.height - kMargin;

        _arrowPosition = rectYM - point.y;
        _contentView.frame = (CGRect){CGPointZero, contentSize};

        self.frame = (CGRect){

            point, contentSize.width + kCallArrowSize, contentSize.height};

    } else {
        _arrowDirection = KxCallMenuViewArrowDirectionNone;

        self.frame = (CGRect){

            (outerWidth - contentSize.width) * 0.5f,
            (outerHeight - contentSize.height) * 0.5f,
            contentSize,
        };
    }
}

- (void)showMenuInView:(UIView *)view fromRect:(CGRect)rect menuItems:(NSArray *)menuItems {
    _menuItems = menuItems;

    _contentView = [self mkContentView];
    [self addSubview:_contentView];

    [self setupFrameInView:view fromRect:rect];

    KxCallMenuOverlay *overlay = [[KxCallMenuOverlay alloc] initWithFrame:view.bounds];
    [overlay addSubview:self];
    [view addSubview:overlay];

    _contentView.hidden = YES;
    const CGRect toFrame = self.frame;
    self.frame = (CGRect){300, 64, 1, 1};

    [UIView animateWithDuration:0.2
        animations:^(void) {
            self.alpha = 1.0f;
            self.frame = toFrame;
        }
        completion:^(BOOL completed) {
            _contentView.hidden = NO;
        }];
}

- (void)dismissMenu:(BOOL)animated {
    if (self.superview) {
        if (animated) {
            _contentView.hidden = YES;
            const CGRect toFrame = (CGRect){self.arrowPoint, 1, 1};

            [UIView animateWithDuration:0.2
                animations:^(void) {
                    self.alpha = 0;
                    self.frame = toFrame;
                }
                completion:^(BOOL finished) {
                    if ([self.superview isKindOfClass:[KxCallMenuOverlay class]]) [self.superview removeFromSuperview];
                    [self removeFromSuperview];
                }];

        } else {
            if ([self.superview isKindOfClass:[KxCallMenuOverlay class]]) [self.superview removeFromSuperview];
            [self removeFromSuperview];
        }
    }
}

- (void)performAction:(id)sender {
    [self dismissMenu:YES];

    UIButton *button = (UIButton *)sender;
    KxCallMenuItem *menuItem = _menuItems[button.tag];
    [menuItem performAction];
}

- (UIView *)mkContentView {
    for (UIView *v in self.subviews) {
        [v removeFromSuperview];
    }

    if (!_menuItems.count) return nil;

    const CGFloat kMinMenuItemWidth = 32.f;
    const CGFloat kMarginX = 10.f;
    const CGFloat kMarginY = 5.f;

    UIFont *titleFont = [KxCallMenu titleFont];
    if (!titleFont) titleFont = [UIFont boldSystemFontOfSize:16];

    CGFloat maxImageWidth = 0;
    CGFloat maxItemHeight = 0;
    CGFloat maxItemWidth = 0;

    {
        const CGSize imageSize = CGSizeMake(20, 20);
        if (imageSize.width > maxImageWidth) maxImageWidth = imageSize.width;
    }

    for (KxCallMenuItem *menuItem in _menuItems) {
        //        const CGSize titleSize = [menuItem.title sizeWithFont:titleFont];
        const CGSize titleSize = [menuItem.title sizeWithAttributes:@{NSFontAttributeName : titleFont}];
        const CGSize imageSize = menuItem.image.size;

        const CGFloat itemHeight = MAX(titleSize.height, imageSize.height) + kMarginY * 2;
        const CGFloat itemWidth = (menuItem.image ? maxImageWidth + kMarginX : 0) + titleSize.width + kMarginX * 4 + 15;

        if (itemHeight > maxItemHeight) maxItemHeight = itemHeight;

        if (itemWidth > maxItemWidth) maxItemWidth = itemWidth;
    }

    maxItemWidth = MAX(maxItemWidth, kMinMenuItemWidth);
    maxItemHeight = 40;

    const CGFloat titleX = kMarginX * 2 + (maxImageWidth > 0 ? maxImageWidth + kMarginX : 0);
    const CGFloat titleWidth = maxItemWidth - titleX - kMarginX;

    UIImage *selectedImage = [KxCallMenuView selectedImage:(CGSize){maxItemWidth, maxItemHeight + 2}];
    UIImage *gradientLine = [KxCallMenuView gradientLine:(CGSize){maxItemWidth - kMarginX * 4, 1}];

    UIView *contentView = [[UIView alloc] initWithFrame:CGRectZero];
    contentView.autoresizingMask = UIViewAutoresizingNone;
    contentView.backgroundColor = [UIColor blackColor];
    contentView.opaque = NO;

    CGFloat itemY = kMarginY * 2;
    NSUInteger itemNum = 0;

    for (KxCallMenuItem *menuItem in _menuItems) {
        const CGRect itemFrame = (CGRect){0, itemY, maxItemWidth, maxItemHeight};

        UIView *itemView = [[UIView alloc] initWithFrame:itemFrame];
        itemView.autoresizingMask = UIViewAutoresizingNone;
        itemView.backgroundColor = [UIColor clearColor];
        itemView.opaque = NO;

        [contentView addSubview:itemView];

        if (menuItem.enabled) {
            UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
            button.tag = itemNum;
            button.frame = itemView.bounds;
            button.enabled = menuItem.enabled;
            button.backgroundColor = [UIColor clearColor];
            button.opaque = NO;
            button.autoresizingMask = UIViewAutoresizingNone;

            [button addTarget:self action:@selector(performAction:) forControlEvents:UIControlEventTouchUpInside];

            [button setBackgroundImage:selectedImage forState:UIControlStateHighlighted];

            [itemView addSubview:button];
        }

        if (menuItem.title.length) {
            CGRect titleFrame;

            if (!menuItem.enabled && !menuItem.image) {
                titleFrame =
                    (CGRect){kMarginX * 2, kMarginY, maxItemWidth - kMarginX * 4, maxItemHeight - kMarginY * 2};

            } else {
                titleFrame = (CGRect){titleX + 4, kMarginY + 3, titleWidth, maxItemHeight - kMarginY * 2};
            }

            UILabel *titleLabel = [[UILabel alloc] initWithFrame:titleFrame];
            titleLabel.text = menuItem.title;
            titleLabel.font = titleFont;
            titleLabel.textAlignment = menuItem.alignment;
            //设置字体颜色
            titleLabel.textColor = [UIColor whiteColor];
            //menuItem.foreColor ? menuItem.foreColor : [UIColor colorWithHexString:@"000000" alpha:1.0f];
            titleLabel.backgroundColor = [UIColor clearColor];
            titleLabel.autoresizingMask = UIViewAutoresizingNone;
            [itemView addSubview:titleLabel];
        }

        if (menuItem.image) {
            //            const CGRect imageFrame = {kMarginX * 2, kMarginY,
            //            maxImageWidth, maxItemHeight - kMarginY * 2};
            const CGRect imageFrame = {kMarginX * 2, kMarginY + 5, 25, 25};
            UIImageView *imageView = [[UIImageView alloc] initWithFrame:imageFrame];
            imageView.image = menuItem.image;
            imageView.clipsToBounds = YES;
            imageView.contentMode = UIViewContentModeScaleAspectFit;
            imageView.autoresizingMask = UIViewAutoresizingNone;
            [itemView addSubview:imageView];
        }

        if (itemNum < _menuItems.count - 1) {
            UIImageView *gradientView = [[UIImageView alloc] initWithImage:gradientLine];
            //隐藏分割线
            gradientView.hidden = YES;
            gradientView.frame = (CGRect){kMarginX * 2, maxItemHeight + 1, gradientLine.size};
            gradientView.contentMode = UIViewContentModeLeft;
            [itemView addSubview:gradientView];
            //每个itemView之间的间隔距离
            itemY += 5;
        }

        itemY += maxItemHeight;
        ++itemNum;
    }

    contentView.frame = (CGRect){0, 0, maxItemWidth, itemY + kMarginY * 2};
    contentView.layer.cornerRadius = 4.0;

    return contentView;
}

- (CGPoint)arrowPoint {
    CGPoint point;

    if (_arrowDirection == KxCallMenuViewArrowDirectionUp) {
        point = (CGPoint){CGRectGetMinX(self.frame) + _arrowPosition, CGRectGetMinY(self.frame)};

    } else if (_arrowDirection == KxCallMenuViewArrowDirectionDown) {
        point = (CGPoint){CGRectGetMinX(self.frame) + _arrowPosition, CGRectGetMaxY(self.frame)};

    } else if (_arrowDirection == KxCallMenuViewArrowDirectionLeft) {
        point = (CGPoint){CGRectGetMinX(self.frame), CGRectGetMinY(self.frame) + _arrowPosition};

    } else if (_arrowDirection == KxCallMenuViewArrowDirectionRight) {
        point = (CGPoint){CGRectGetMaxX(self.frame), CGRectGetMinY(self.frame) + _arrowPosition};

    } else {
        point = self.center;
    }

    return point;
}

+ (UIImage *)selectedImage:(CGSize)size {
    const CGFloat locations[] = {0, 1};
    const CGFloat components[] = {
        0.216, 0.471, 0.871, 0, 0.059, 0.353, 0.839, 0,
    };

    return [self gradientImageWithSize:size locations:locations components:components count:2];
}

+ (UIImage *)gradientLine:(CGSize)size {
    const CGFloat locations[5] = {0, 0.2, 0.5, 0.8, 1};

    const CGFloat R = 0.44f, G = 0.44f, B = 0.44f;

    const CGFloat components[20] = {R, G, B, 0.1, R, G, B, 0.4, R, G, B, 0.7, R, G, B, 0.4, R, G, B, 0.1};

    return [self gradientImageWithSize:size locations:locations components:components count:5];
    //    return [UIImage image:[UIImage imageNamed:@"line_x2"] byScalingToSize:size];
}

+ (UIImage *)gradientImageWithSize:(CGSize)size
                         locations:(const CGFloat[])locations
                        components:(const CGFloat[])components
                             count:(NSUInteger)count {
    UIGraphicsBeginImageContextWithOptions(size, NO, 0);
    CGContextRef context = UIGraphicsGetCurrentContext();

    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGGradientRef colorGradient = CGGradientCreateWithColorComponents(colorSpace, components, locations, 2);
    CGColorSpaceRelease(colorSpace);
    CGContextDrawLinearGradient(context, colorGradient, (CGPoint){0, 0}, (CGPoint){size.width, 0}, 0);
    CGGradientRelease(colorGradient);

    UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return image;
}

- (void)drawRect:(CGRect)rect {
    [self drawBackground:self.bounds inContext:UIGraphicsGetCurrentContext()];
}

- (void)drawBackground:(CGRect)frame inContext:(CGContextRef)context {
    CGFloat X0 = frame.origin.x;
    CGFloat X1 = frame.origin.x + frame.size.width;
    CGFloat Y0 = frame.origin.y;
    CGFloat Y1 = frame.origin.y + frame.size.height;

    // render arrow

    UIBezierPath *arrowPath = [UIBezierPath bezierPath];

    // fix the issue with gap of arrow's base if on the edge
    const CGFloat kEmbedFix = 3.f;

    if (_arrowDirection == KxCallMenuViewArrowDirectionUp) {
        const CGFloat arrowXM = 127;  //_arrowPosition;
        const CGFloat arrowX0 = arrowXM - kCallArrowSize;
        const CGFloat arrowX1 = arrowXM + kCallArrowSize;
        const CGFloat arrowY0 = Y0;
        const CGFloat arrowY1 = Y0 + kCallArrowSize + kEmbedFix;

        [arrowPath moveToPoint:(CGPoint){arrowXM, arrowY0}];
        [arrowPath addLineToPoint:(CGPoint){arrowX1, arrowY1}];
        [arrowPath addLineToPoint:(CGPoint){arrowX0, arrowY1}];
        [arrowPath addLineToPoint:(CGPoint){arrowXM, arrowY0}];

        [[[UIColor blackColor] colorWithAlphaComponent:1.0f] set];

        Y0 += kCallArrowSize;

    } else if (_arrowDirection == KxCallMenuViewArrowDirectionDown) {
        const CGFloat arrowXM = _arrowPosition;
        const CGFloat arrowX0 = arrowXM - kCallArrowSize;
        const CGFloat arrowX1 = arrowXM + kCallArrowSize;
        const CGFloat arrowY0 = Y1 - kCallArrowSize - kEmbedFix;
        const CGFloat arrowY1 = Y1;

        [arrowPath moveToPoint:(CGPoint){arrowXM, arrowY1}];
        [arrowPath addLineToPoint:(CGPoint){arrowX1, arrowY0}];
        [arrowPath addLineToPoint:(CGPoint){arrowX0, arrowY0}];
        [arrowPath addLineToPoint:(CGPoint){arrowXM, arrowY1}];

        [[[UIColor whiteColor] colorWithAlphaComponent:1.0f] set];

        Y1 -= kCallArrowSize;

    } else if (_arrowDirection == KxCallMenuViewArrowDirectionLeft) {
        const CGFloat arrowYM = _arrowPosition;
        const CGFloat arrowX0 = X0;
        const CGFloat arrowX1 = X0 + kCallArrowSize + kEmbedFix;
        const CGFloat arrowY0 = arrowYM - kCallArrowSize;
        ;
        const CGFloat arrowY1 = arrowYM + kCallArrowSize;

        [arrowPath moveToPoint:(CGPoint){arrowX0, arrowYM}];
        [arrowPath addLineToPoint:(CGPoint){arrowX1, arrowY0}];
        [arrowPath addLineToPoint:(CGPoint){arrowX1, arrowY1}];
        [arrowPath addLineToPoint:(CGPoint){arrowX0, arrowYM}];

        [[[UIColor whiteColor] colorWithAlphaComponent:1.0f] set];

        X0 += kCallArrowSize;

    } else if (_arrowDirection == KxCallMenuViewArrowDirectionRight) {
        const CGFloat arrowYM = _arrowPosition;
        const CGFloat arrowX0 = X1;
        const CGFloat arrowX1 = X1 - kCallArrowSize - kEmbedFix;
        const CGFloat arrowY0 = arrowYM - kCallArrowSize;
        ;
        const CGFloat arrowY1 = arrowYM + kCallArrowSize;

        [arrowPath moveToPoint:(CGPoint){arrowX0, arrowYM}];
        [arrowPath addLineToPoint:(CGPoint){arrowX1, arrowY0}];
        [arrowPath addLineToPoint:(CGPoint){arrowX1, arrowY1}];
        [arrowPath addLineToPoint:(CGPoint){arrowX0, arrowYM}];

        [[[UIColor whiteColor] colorWithAlphaComponent:1.0f] set];

        X1 -= kCallArrowSize;
    }

    [arrowPath fill];

    // render body

    const CGRect bodyFrame = {X0, Y0, X1 - X0, Y1 - Y0};

    UIBezierPath *borderPath = [UIBezierPath bezierPathWithRoundedRect:bodyFrame cornerRadius:3];

    //    const CGFloat locations[] = {0, 1};
    //    const CGFloat components[] = {
    //        R0, G0, B0, 1,
    //        R1, G1, B1, 0,
    //    };

    //    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    //    CGGradientRef gradient = CGGradientCreateWithColorComponents(colorSpace,
    //                                                                 components,
    //                                                                 locations,
    //                                                                 sizeof(locations)/sizeof(locations[0]));
    //    CGColorSpaceRelease(colorSpace);

    //    [borderPath addClip];

    //    CGPoint start, end;
    //
    //    if (_arrowDirection == KxMenuViewArrowDirectionLeft ||
    //        _arrowDirection == KxMenuViewArrowDirectionRight) {
    //
    //        start = (CGPoint){X0, Y0};
    //        end = (CGPoint){X1, Y0};
    //
    //    } else {
    //
    //        start = (CGPoint){X0, Y0};
    //        end = (CGPoint){X0, Y1};
    //    }
    [borderPath fill];

    //    CGContextDrawLinearGradient(context, gradient, start, end, 0);

    //    CGGradientRelease(gradient);
}

@end

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

static KxCallMenu *gMenu;
static UIColor *gTintColor;
static UIFont *gTitleFont;

@implementation KxCallMenu {
    KxCallMenuView *_menuView;
    BOOL _observing;
}

+ (instancetype)sharedMenu {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        gMenu = [[KxCallMenu alloc] init];
    });
    return gMenu;
}

- (id)init {
    NSAssert(!gMenu, @"singleton object");

    self = [super init];
    if (self) {
    }
    return self;
}

- (void)dealloc {
    if (_observing) {
        [[NSNotificationCenter defaultCenter] removeObserver:self];
    }
}

- (void)showMenuInView:(UIView *)view fromRect:(CGRect)rect menuItems:(NSArray *)menuItems {
    NSParameterAssert(view);
    NSParameterAssert(menuItems.count);

    if (_menuView) {
        [_menuView dismissMenu:NO];
        _menuView = nil;
    }

    if (!_observing) {
        _observing = YES;

        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(orientationWillChange:)
                                                     name:UIApplicationWillChangeStatusBarOrientationNotification
                                                   object:nil];
    }

    _menuView = [[KxCallMenuView alloc] init];
    [_menuView showMenuInView:view fromRect:rect menuItems:menuItems];
}

- (void)dismissMenu {
    if (_menuView) {
        [_menuView dismissMenu:NO];
        _menuView = nil;
    }

    if (_observing) {
        _observing = NO;
        [[NSNotificationCenter defaultCenter] removeObserver:self];
    }
}

- (void)orientationWillChange:(NSNotification *)n {
    [self dismissMenu];
}

+ (void)showMenuInView:(UIView *)view fromRect:(CGRect)rect menuItems:(NSArray *)menuItems {
    [[self sharedMenu] showMenuInView:view fromRect:rect menuItems:menuItems];
}

+ (void)dismissMenu {
    [[self sharedMenu] dismissMenu];
}

+ (UIColor *)tintColor {
    return gTintColor;
}

+ (void)setTintColor:(UIColor *)tintColor {
    if (tintColor != gTintColor) {
        gTintColor = tintColor;
    }
}

+ (UIFont *)titleFont {
    return gTitleFont;
}

+ (void)setTitleFont:(UIFont *)titleFont {
    if (titleFont != gTitleFont) {
        gTitleFont = titleFont;
    }
}

@end
