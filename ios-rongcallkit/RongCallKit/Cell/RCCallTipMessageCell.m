//
//  RCCallTipMessageCell.m
//  RongCallKit
//
//  Created by RongCloud on 16/3/20.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCCallTipMessageCell.h"
#import "RCCall.h"
#import "RCCallKitUtility.h"

@implementation RCCallTipMessageCell

+ (CGSize)sizeForMessageModel:(RCMessageModel *)model
      withCollectionViewWidth:(CGFloat)collectionViewWidth
         referenceExtraHeight:(CGFloat)extraHeight {
    CGFloat height = 23;

    height += extraHeight;

    return CGSizeMake(collectionViewWidth, height);
}

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        self.messageLabel = [RCTipLabel greyTipLabel];
        self.messageLabel.backgroundColor = [RCKitUtility generateDynamicColor:hex_rgb(0xc9c9c9)
                                                                     darkColor:hex_rgb(0x232323)];
        self.messageLabel.textColor = dynamic_color(0xffffff, 0x707070);
        [self.baseContentView addSubview:self.messageLabel];
        self.messageLabel.marginInsets = UIEdgeInsetsMake(0.5f, 0.5f, 0.5f, 0.5f);
    }
    return self;
}
- (id)initWithCoder:(NSCoder *)aDecoder {
    self = [super initWithCoder:aDecoder];
    if (self) {
        self.messageLabel = [RCTipLabel greyTipLabel];
        self.messageLabel.backgroundColor = [RCKitUtility generateDynamicColor:rgba(0, 0, 0, 0.1)
                                                                     darkColor:hex_rgb(0x232323)];
        self.messageLabel.textColor = dynamic_color(0xffffff, 0x707070);
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
            status = RCCallKitLocalizedString(@"VoIPCallHasEnd");
        } else if (message.hangupReason == RCCallDisconnectReasonReject ||
                   message.hangupReason == RCCallDisconnectReasonRemoteReject) {
            status = RCCallKitLocalizedString(@"VoIPCallHasReject");
        } else if (message.hangupReason == RCCallDisconnectReasonCancel) {
            status = RCCallKitLocalizedString(@"VoIPCallHasCancel");
        } else if (message.hangupReason == RCCallDisconnectReasonRemoteCancel) {
            status = RCCallKitLocalizedString(@"VoIPCallNoResponse");
        } else if (message.hangupReason == RCCallDisconnectReasonAcceptByOtherClient) {
            status = RCCallKitLocalizedString(@"VoIPCallAcceptByOtherClient");
        } else if (message.hangupReason == RCCallDisconnectReasonRemoteBusyLine) {
            status = RCCallKitLocalizedString(@"VoIPCallRemoteBusyLine");
        } else {
            status = RCCallKitLocalizedString(@"VoIPCallNoResponse");
        }
        // 多语言下英文和阿文 中间都有空格，中文没有空格。
        NSString *space = [self getSpaceWithLocalLanguage] ;
        
        if (message.mediaType == RCCallMediaAudio) {
            [self.messageLabel setText:[NSString stringWithFormat:@" %@%@%@ ", RCCallKitLocalizedString(@"VoIPAudioCall"),space
                                                                  ,status]
                   dataDetectorEnabled:NO];
        } else {
            [self.messageLabel setText:[NSString stringWithFormat:@" %@%@%@ ", RCCallKitLocalizedString(@"VoIPVideoCall"),space ,
                                                                  status]
                   dataDetectorEnabled:NO];
        }

        if (message.hangupReason == RCCallDisconnectReasonMediaServerClosed ||
            message.hangupReason == RCCallDisconnectReasonRemoteEngineUnsupported) {
            [self.messageLabel setText:RCCallKitLocalizedString(@"VoIPCallMediaServerClosed")];
        }
    }

    NSString *__text = self.messageLabel.text;

    CGSize __textSize = [RCKitUtility getTextDrawingSize:__text
                                                    font:[UIFont systemFontOfSize:14.f]
                                         constrainedSize:CGSizeMake(maxMessageLabelWidth, MAXFLOAT)];
    __textSize = CGSizeMake(ceilf(__textSize.width), ceilf(__textSize.height));
    CGSize __labelSize = CGSizeMake(__textSize.width + 5, __textSize.height + 6);

    self.messageLabel.frame = CGRectMake((self.baseContentView.bounds.size.width - __labelSize.width) / 2.0f, 0,
                                         __labelSize.width, __labelSize.height);
}

- (NSString *) getSpaceWithLocalLanguage {
    NSString * language = [NSLocale preferredLanguages].firstObject;
    if ([language hasPrefix:@"zh-Hans"]) {
        return @"";
    } else if([language hasPrefix:@"en"]) {
        return @" ";
    } else if([language hasPrefix:@"ar"]) {
        return @" ";
    }
    return @"";
}

@end
