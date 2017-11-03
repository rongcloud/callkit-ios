//
//  RCCallMultiCallUserCell.m
//  RongCallKit
//
//  Created by litao on 16/3/22.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCCallMultiCallUserCell.h"
#import "RCCallKitUtility.h"
#import "RCloudImageView.h"
#import <RongIMKit/RongIMKit.h>

@interface RCCallMultiCallUserCell ()

@property(nonatomic, strong) RCCallUserCallInfoModel *model;
@property(nonatomic, assign) RCCallStatus callStatus;
@end

@implementation RCCallMultiCallUserCell

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // create our image view so that is matches the height and width of this
        // cell
        self.headerImageView = [[RCloudImageView alloc] initWithFrame:CGRectZero];
        self.headerImageView.autoresizingMask = UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth;
        self.headerImageView.contentMode = UIViewContentModeScaleAspectFill;
        self.headerImageView.clipsToBounds = YES;

        // add a white frame around the image
        self.headerImageView.layer.borderWidth = 1;
        self.headerImageView.layer.borderColor = [UIColor whiteColor].CGColor;
        self.headerImageView.layer.cornerRadius = 4;
        self.headerImageView.layer.masksToBounds = YES;
        self.headerImageView.backgroundColor = [[UIColor clearColor] colorWithAlphaComponent:1.0];
        // Define how the edges of the layer are rasterized for each of the four
        // edges
        // (left, right, bottom, top) if the corresponding bit is set the edge will
        // be antialiased
        //
        self.headerImageView.layer.edgeAntialiasingMask =
            kCALayerLeftEdge | kCALayerRightEdge | kCALayerBottomEdge | kCALayerTopEdge;
        [self.headerImageView
            setPlaceholderImage:[RCKitUtility imageNamed:@"default_portrait_msg" ofBundle:@"RongCloud.bundle"]];
        self.headerImageView.hidden = YES;
        [[self contentView] addSubview:self.headerImageView];

        self.nameLabel = [[UILabel alloc] initWithFrame:CGRectZero];
        self.nameLabel.textColor = [UIColor whiteColor];
        self.nameLabel.textAlignment = NSTextAlignmentCenter;
        self.nameLabel.backgroundColor = [UIColor clearColor];
        self.nameLabel.font = [UIFont systemFontOfSize:14];
        self.nameLabel.hidden = YES;
        [[self contentView] addSubview:self.nameLabel];
        self.statusView = [[UIImageView alloc] initWithFrame:CGRectZero];
        self.statusView.hidden = YES;
        [[self contentView] addSubview:self.statusView];

        self.contentView.backgroundColor = [UIColor clearColor];
    }
    return self;
}

- (void)setModel:(RCCallUserCallInfoModel *)model status:(RCCallStatus)callStatus {
    _model = model;
    self.callStatus = callStatus;

    CGFloat nameLabelHeight = 16;
    CGFloat insideMargin = 5;

    if (callStatus == RCCallIncoming || callStatus == RCCallRinging || model.profile.mediaType == RCCallMediaVideo) {
        nameLabelHeight = 0;
        insideMargin = 0;
    }
    [self resetLayout:nameLabelHeight insideMargin:insideMargin];

    [self.headerImageView setImageURL:[NSURL URLWithString:model.userInfo.portraitUri]];
    [self.nameLabel setText:model.userInfo.name];
    if (model.profile.callStatus == RCCallRinging || model.profile.callStatus == RCCallDialing ||
        model.profile.callStatus == RCCallIncoming) {
        self.statusView.image = [RCCallKitUtility imageFromVoIPBundle:@"voip/voip_connecting"];
        self.headerImageView.alpha = 0.5;
    } else {
        self.statusView.image = nil;
        self.statusView.hidden = YES;
        self.headerImageView.alpha = 1.0;
    }
}

- (void)resetLayout:(CGFloat)nameLabelHeight insideMargin:(CGFloat)insideMargin {
    CGFloat minLength = MIN(self.bounds.size.width, self.bounds.size.height - nameLabelHeight - insideMargin);

    self.headerImageView.frame = CGRectMake((self.bounds.size.width - minLength) / 2, 0, minLength, minLength);
    self.headerImageView.hidden = NO;

    self.nameLabel.frame =
        CGRectMake(0, self.bounds.size.height - nameLabelHeight, self.bounds.size.width, nameLabelHeight);
    if (nameLabelHeight > 0) {
        self.nameLabel.hidden = NO;
    } else {
        self.nameLabel.hidden = YES;
    }

    self.statusView.frame =
        CGRectMake((self.bounds.size.width - 17) / 2, (self.headerImageView.frame.size.width - 4) / 2, 17, 4);
    self.statusView.hidden = NO;
}

@end
