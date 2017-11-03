//
//  RCCallTipMessageCell.m
//  RongCallKit
//
//  Created by 岑裕 on 16/3/20.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCCallTipMessageCell.h"
#import "RCCall.h"

@implementation RCCallTipMessageCell

+ (CGSize)sizeForMessageModel:(RCMessageModel *)model
      withCollectionViewWidth:(CGFloat)collectionViewWidth
         referenceExtraHeight:(CGFloat)extraHeight {
    CGFloat height = 17.5;

    height += extraHeight;

    return CGSizeMake(collectionViewWidth, height);
}

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        self.messageLabel = [RCTipLabel greyTipLabel];
        [self.baseContentView addSubview:self.messageLabel];
        self.messageLabel.marginInsets = UIEdgeInsetsMake(0.5f, 0.5f, 0.5f, 0.5f);
    }
    return self;
}
- (id)initWithCoder:(NSCoder *)aDecoder {
    self = [super initWithCoder:aDecoder];
    if (self) {
        self.messageLabel = [RCTipLabel greyTipLabel];
        [self.baseContentView addSubview:self.messageLabel];
        self.messageLabel.marginInsets = UIEdgeInsetsMake(0.5f, 0.5f, 0.5f, 0.5f);
    }
    return self;
}
- (void)setDataModel:(RCMessageModel *)model {
    [super setDataModel:model];

    // RCMessageContent *content = model.content;

    CGFloat maxMessageLabelWidth = self.baseContentView.bounds.size.width - 30 * 2;

    if ([model.content isMemberOfClass:[RCCallSummaryMessage class]]) {
        RCCallSummaryMessage *message = (RCCallSummaryMessage *)model.content;

        NSString *status = nil;
        if (message.connectedTime > 0) {
            status = NSLocalizedStringFromTable(@"VoIPCallHasEnd", @"RongCloudKit", nil);
        } else if (message.hangupReason == RCCallDisconnectReasonReject ||
                   message.hangupReason == RCCallDisconnectReasonRemoteReject) {
            status = NSLocalizedStringFromTable(@"VoIPCallHasReject", @"RongCloudKit", nil);
        } else if (message.hangupReason == RCCallDisconnectReasonCancel) {
            status = NSLocalizedStringFromTable(@"VoIPCallHasCancel", @"RongCloudKit", nil);
        } else if (message.hangupReason == RCCallDisconnectReasonRemoteCancel) {
            status = NSLocalizedStringFromTable(@"VoIPCallNoResponse", @"RongCloudKit", nil);
        } else {
            status = NSLocalizedStringFromTable(@"VoIPCallNoResponse", @"RongCloudKit", nil);
        }

        if (message.mediaType == RCCallMediaAudio) {
            [self.messageLabel setText:[NSString stringWithFormat:@" %@ %@ ",
                                                                  NSLocalizedStringFromTable(@"VoIPAudioCall",
                                                                                             @"RongCloudKit", nil),
                                                                  status]
                   dataDetectorEnabled:NO];
        } else {
            [self.messageLabel setText:[NSString stringWithFormat:@" %@ %@ ",
                                                                  NSLocalizedStringFromTable(@"VoIPVideoCall",
                                                                                             @"RongCloudKit", nil),
                                                                  status]
                   dataDetectorEnabled:NO];
        }
    }

    NSString *__text = self.messageLabel.text;

    CGSize __textSize = [RCKitUtility getTextDrawingSize:__text
                                                    font:[UIFont systemFontOfSize:14.f]
                                         constrainedSize:CGSizeMake(maxMessageLabelWidth, MAXFLOAT)];
    __textSize = CGSizeMake(ceilf(__textSize.width), ceilf(__textSize.height));
    CGSize __labelSize = CGSizeMake(__textSize.width + 5, __textSize.height + 6);

    self.messageLabel.frame = CGRectMake((self.baseContentView.bounds.size.width - __labelSize.width) / 2.0f, 10,
                                         __labelSize.width, __labelSize.height);
}

@end
