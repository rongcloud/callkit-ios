//
//  RCCallMultiCallUserCell.m
//  RongCallKit
//
//  Created by litao on 16/3/22.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCCallMultiCallUserCell.h"
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
    self.headerImageView.autoresizingMask =
        UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth;
    self.headerImageView.contentMode = UIViewContentModeScaleAspectFill;
    self.headerImageView.clipsToBounds = YES;

    // add a white frame around the image
    self.headerImageView.layer.borderWidth = 1;
    self.headerImageView.layer.borderColor = [UIColor whiteColor].CGColor;
    self.headerImageView.layer.cornerRadius = 4;
    self.headerImageView.layer.masksToBounds = YES;
    // Define how the edges of the layer are rasterized for each of the four
    // edges
    // (left, right, bottom, top) if the corresponding bit is set the edge will
    // be antialiased
    //
    self.headerImageView.layer.edgeAntialiasingMask =
        kCALayerLeftEdge | kCALayerRightEdge | kCALayerBottomEdge |
        kCALayerTopEdge;
    [self.headerImageView
        setPlaceholderImage:[RCKitUtility imageNamed:@"default_portrait_msg"
                                            ofBundle:@"RongCloud.bundle"]];
    self.headerImageView.hidden = YES;
    [[self contentView] addSubview:self.headerImageView];

    self.nameLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    self.nameLabel.textColor = [UIColor whiteColor];
    self.nameLabel.textAlignment = NSTextAlignmentCenter;
    self.nameLabel.backgroundColor = [UIColor clearColor];
    self.nameLabel.font = [UIFont systemFontOfSize:16];
    self.nameLabel.hidden = YES;
    [[self contentView] addSubview:self.nameLabel];

    self.statusLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    self.statusLabel.textColor = [UIColor whiteColor];
    self.statusLabel.textAlignment = NSTextAlignmentCenter;
    self.statusLabel.backgroundColor = [UIColor clearColor];
    self.statusLabel.font = [UIFont systemFontOfSize:16];
    self.statusLabel.hidden = YES;
    [[self contentView] addSubview:self.statusLabel];

    self.contentView.backgroundColor = [UIColor clearColor];
  }
  return self;
}

- (void)setModel:(RCCallUserCallInfoModel *)model
          status:(RCCallStatus)callStatus {
  _model = model;
  self.callStatus = callStatus;

  CGFloat nameLabelHeight = 15;
  CGFloat insideMargin = 1;

  if (callStatus == RCCallIncoming || callStatus == RCCallRinging ||
      model.profile.mediaType == RCCallMediaVideo) {
    nameLabelHeight = 0;
    insideMargin = 0;
  }
  [self resetLayout:nameLabelHeight insideMargin:insideMargin];

  [self.headerImageView
      setImageURL:[NSURL URLWithString:model.userInfo.portraitUri]];
  [self.nameLabel setText:model.userInfo.name];
  self.statusLabel.text = [self getStatusTips];
}

- (void)resetLayout:(CGFloat)nameLabelHeight
       insideMargin:(CGFloat)insideMargin {
  CGFloat minLength =
      MIN(self.bounds.size.width,
          self.bounds.size.height - nameLabelHeight - insideMargin);

  self.headerImageView.frame = CGRectMake(
      (self.bounds.size.width - minLength) / 2, 0, minLength, minLength);
  self.headerImageView.hidden = NO;

  self.nameLabel.frame =
      CGRectMake(0, self.bounds.size.height - nameLabelHeight,
                 self.bounds.size.width, nameLabelHeight);
  if (nameLabelHeight > 0) {
    self.nameLabel.hidden = NO;
  } else {
    self.nameLabel.hidden = YES;
  }

  self.statusLabel.frame =
      CGRectMake(0, (self.headerImageView.frame.size.width - 30) / 2,
                 self.bounds.size.width, 30);
  self.statusLabel.hidden = NO;
}

- (NSString *)getStatusTips {
  NSString *tips = nil;

  switch (self.model.profile.callStatus) {
  case RCCallIncoming:
  case RCCallRinging:
    if (self.callStatus == RCCallIncoming) {
      break;
    }
  case RCCallDialing:
    tips = NSLocalizedStringFromTable(@"VoIPMultiCallRemoteConnecting",
                                      @"RongCloudKit", nil);
    break;
  case RCCallActive:
    tips = @"";
    break;
  case RCCallHangup:
    tips = NSLocalizedStringFromTable(@"VoIPMultiCallRemoteQuit",
                                      @"RongCloudKit", nil);
    break;

  default:
    tips = @"";
    break;
  }

  return tips;
}

@end
