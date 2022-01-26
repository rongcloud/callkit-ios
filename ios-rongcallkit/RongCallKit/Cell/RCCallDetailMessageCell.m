//
//  RCCallDetailMessageCell.m
//  RongCallKit
//
//  Created by RongCloud on 16/3/20.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCCallDetailMessageCell.h"
#import "RCCall.h"
#import "RCCallKitUtility.h"

@implementation RCCallDetailMessageCell

+ (CGSize)sizeForMessageModel:(RCMessageModel *)model
      withCollectionViewWidth:(CGFloat)collectionViewWidth
         referenceExtraHeight:(CGFloat)extraHeight {
    //当为单聊时，需要显示头像，且内容区域高度小于头像高度，所以内容区域高度就是头像高度，然后加上上下10padding。
    CGFloat height = RCKitConfigCenter.ui.globalMessagePortraitSize.height;

    height += extraHeight;

    return CGSizeMake(collectionViewWidth, height);
}
- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        [self initialize];
    }
    return self;
}

- (id)initWithCoder:(NSCoder *)aDecoder {
    self = [super initWithCoder:aDecoder];
    if (self) {
        [self initialize];
    }
    return self;
}

- (void)initialize {
    [self showBubbleBackgroundView:YES];
    self.textLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    [self.textLabel setFont:[[RCKitConfig defaultConfig].font fontOfSecondLevel]];
    self.textLabel.numberOfLines = 0;
    [self.textLabel setLineBreakMode:NSLineBreakByWordWrapping];
    [self.textLabel setTextAlignment:NSTextAlignmentLeft];
    if (RC_IOS_SYSTEM_VERSION_LESS_THAN(@"7.0")) {
        [self.textLabel setBackgroundColor:[UIColor clearColor]];
    }
    [self.messageContentView addSubview:self.textLabel];

    self.mediaTypeIcon = [[UIImageView alloc] initWithFrame:CGRectZero];
    [self.messageContentView addSubview:self.mediaTypeIcon];
}

- (void)setDataModel:(RCMessageModel *)model {
    [super setDataModel:model];
    [self setAutoLayout];
}

- (void)setAutoLayout {
    RCCallSummaryMessage *callMessage = (RCCallSummaryMessage *)self.model.content;
    if (callMessage.duration > 1000) {
        self.textLabel.text =
            [NSString stringWithFormat:@"%@ %@", RCCallKitLocalizedString(@"VoIPCallTotalTime"),
                                       [RCCallKitUtility getReadableStringForTime:(long)(callMessage.duration / 1000)]];
    } else {
        self.textLabel.text = [RCCallKitUtility getReadableStringForMessageCell:callMessage.hangupReason];
    }

    if (callMessage.mediaType == RCCallMediaVideo && self.messageDirection == MessageDirection_RECEIVE) {
        self.mediaTypeIcon.image = [RCCallKitUtility imageFromVoIPBundle:@"voip/video_left.png"];
    } else if (callMessage.mediaType == RCCallMediaVideo && self.messageDirection == MessageDirection_SEND) {
        self.mediaTypeIcon.image = [RCCallKitUtility imageFromVoIPBundle:@"voip/video_right.png"];
    } else if (callMessage.mediaType == RCCallMediaAudio && self.messageDirection == MessageDirection_RECEIVE &&
               callMessage.duration > 0) {
        self.mediaTypeIcon.image = [RCCallKitUtility imageFromVoIPBundle:@"voip/audio_receiver_left.png"];
    } else if (callMessage.mediaType == RCCallMediaAudio && self.messageDirection == MessageDirection_RECEIVE &&
               callMessage.duration <= 0) {
        self.mediaTypeIcon.image = [RCCallKitUtility imageFromVoIPBundle:@"voip/audio_receiver_up_left.png"];
    } else if (callMessage.mediaType == RCCallMediaAudio && self.messageDirection == MessageDirection_SEND &&
               callMessage.duration > 0) {
        self.mediaTypeIcon.image = [RCCallKitUtility imageFromVoIPBundle:@"voip/audio_receiver_right.png"];
    } else if (callMessage.mediaType == RCCallMediaAudio && self.messageDirection == MessageDirection_SEND &&
               callMessage.duration <= 0) {
        self.mediaTypeIcon.image = [RCCallKitUtility imageFromVoIPBundle:@"voip/audio_receiver_up_right.png"];
    }

    CGSize __textSize = [RCKitUtility
        getTextDrawingSize:self.textLabel.text
                      font:self.textLabel.font
           constrainedSize:CGSizeMake(self.baseContentView.bounds.size.width -
                                          (10 + RCKitConfigCenter.ui.globalMessagePortraitSize.width + 10) * 2 -
                                          (14 + 20 + 7 + 10),
                                      8000)];
    __textSize = CGSizeMake(ceilf(__textSize.width), ceilf(__textSize.height));
    float maxWidth = self.baseContentView.bounds.size.width -
        (10 + RCKitConfigCenter.ui.globalMessagePortraitSize.width + 10) * 2 - 5 - (14 + 20 + 7 + 10);
    if (__textSize.width > maxWidth) {
        __textSize.width = maxWidth;
    }
    CGSize __labelSize = CGSizeMake(__textSize.width, __textSize.height + 5);

    CGFloat __bubbleWidth = __labelSize.width + (14 + 20 + 7 + 10) < 50 ? 50 : (__labelSize.width + (14 + 20 + 7 + 10));
    
    CGFloat __bubbleHeight = __labelSize.height + 5 + 5 < RCKitConfigCenter.ui.globalMessagePortraitSize.height ? RCKitConfigCenter.ui.globalMessagePortraitSize.height : (__labelSize.height + 5 + 5);

    CGSize __bubbleSize = CGSizeMake(__bubbleWidth, __bubbleHeight);

    self.messageContentView.contentSize = __bubbleSize;
    if (self.model.messageDirection == MessageDirection_SEND) {
        self.textLabel.frame =
            CGRectMake(10, (__bubbleHeight - __labelSize.height) / 2, __labelSize.width, __labelSize.height);
        self.mediaTypeIcon.frame = CGRectMake(CGRectGetMaxX(self.textLabel.frame) + 7, (__bubbleHeight - 20) / 2, 20, 20);
        [self.textLabel setTextColor:RCDYCOLOR(0x262626, 0x040A0F)];
    } else {
        self.mediaTypeIcon.frame = CGRectMake(10, (__bubbleHeight - 20) / 2, 20, 20);
        self.textLabel.frame =
            CGRectMake(CGRectGetMaxX(self.mediaTypeIcon.frame) + 7, (__bubbleHeight - __labelSize.height) / 2,
                       __labelSize.width, __labelSize.height);
        [self.textLabel setTextColor:[RCKitUtility generateDynamicColor:HEXCOLOR(0x262626)
                                                              darkColor:RCMASKCOLOR(0xffffff, 0.8)]];
    }
}
@end
