//
//  RCCallDetailMessageCell.m
//  RongCallKit
//
//  Created by 岑裕 on 16/3/20.
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
    CGFloat height = [RCIM sharedRCIM].globalMessagePortraitSize.height;

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
    self.bubbleBackgroundView = [[UIImageView alloc] initWithFrame:CGRectZero];
    [self.messageContentView addSubview:self.bubbleBackgroundView];
    self.bubbleBackgroundView.userInteractionEnabled = YES;
    UILongPressGestureRecognizer *longPress =
        [[UILongPressGestureRecognizer alloc] initWithTarget:self action:@selector(longPressed:)];
    [self.bubbleBackgroundView addGestureRecognizer:longPress];

    self.textLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    [self.textLabel setFont:[UIFont systemFontOfSize:15]];
    self.textLabel.numberOfLines = 0;
    [self.textLabel setLineBreakMode:NSLineBreakByWordWrapping];
    [self.textLabel setTextAlignment:NSTextAlignmentLeft];
    if (RC_IOS_SYSTEM_VERSION_LESS_THAN(@"7.0")) {
        [self.textLabel setBackgroundColor:[UIColor clearColor]];
    }
    UITapGestureRecognizer *textMessageTap =
        [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(tapTextMessage:)];
    textMessageTap.numberOfTapsRequired = 1;
    textMessageTap.numberOfTouchesRequired = 1;
    [self.textLabel addGestureRecognizer:textMessageTap];
    self.textLabel.userInteractionEnabled = YES;
    [self.bubbleBackgroundView addSubview:self.textLabel];

    self.mediaTypeIcon = [[UIImageView alloc] initWithFrame:CGRectZero];
    UITapGestureRecognizer *mediaTypeIconTap =
        [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(tapMediaTypeIcon:)];
    mediaTypeIconTap.numberOfTapsRequired = 1;
    mediaTypeIconTap.numberOfTouchesRequired = 1;
    [self.mediaTypeIcon addGestureRecognizer:mediaTypeIconTap];
    self.mediaTypeIcon.userInteractionEnabled = YES;
    [self.bubbleBackgroundView addSubview:self.mediaTypeIcon];
}

- (void)tapTextMessage:(UIGestureRecognizer *)gestureRecognizer {
    if ([self.delegate respondsToSelector:@selector(didTapMessageCell:)]) {
        [self.delegate didTapMessageCell:self.model];
    }
}

- (void)tapMediaTypeIcon:(UIGestureRecognizer *)gestureRecognizer {
    if ([self.delegate respondsToSelector:@selector(didTapMessageCell:)]) {
        [self.delegate didTapMessageCell:self.model];
    }
}

- (void)setDataModel:(RCMessageModel *)model {
    [super setDataModel:model];

    [self setAutoLayout];
}

- (void)setAutoLayout {    
    RCCallSummaryMessage *callMessage = (RCCallSummaryMessage *)self.model.content;
    if (callMessage.duration > 0) {
        self.textLabel.text =
            [NSString stringWithFormat:@"%@ %@", NSLocalizedStringFromTable(@"VoIPCallTotalTime", @"RongCloudKit", nil),
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
                      font:[UIFont systemFontOfSize:15]
           constrainedSize:CGSizeMake(self.baseContentView.bounds.size.width -
                                          (10 + [RCIM sharedRCIM].globalMessagePortraitSize.width + 10) * 2 - (14 + 20 + 7 + 10),
                                      8000)];
    __textSize = CGSizeMake(ceilf(__textSize.width), ceilf(__textSize.height));
    float maxWidth = self.baseContentView.bounds.size.width -
                     (10 + [RCIM sharedRCIM].globalMessagePortraitSize.width + 10) * 2 - 5 - (14 + 20 + 7 + 10);
    if (__textSize.width > maxWidth) {
        __textSize.width = maxWidth;
    }
    CGSize __labelSize = CGSizeMake(__textSize.width, __textSize.height + 5);

    CGFloat __bubbleWidth = __labelSize.width + (14 + 20 + 7 + 10) < 50 ? 50 : (__labelSize.width + (14 + 20 + 7 + 10));
    CGFloat __bubbleHeight = __labelSize.height + 5 + 5 < 40 ? 40 : (__labelSize.height + 5 + 5);

    CGSize __bubbleSize = CGSizeMake(__bubbleWidth, __bubbleHeight);

    CGRect messageContentViewRect = self.messageContentView.frame;

    //拉伸图片
    // CGFloat top, CGFloat left, CGFloat bottom, CGFloat right
    if (MessageDirection_RECEIVE == self.messageDirection) {
        messageContentViewRect.size.width = __bubbleSize.width;
        messageContentViewRect.size.height = __bubbleSize.height;
        self.messageContentView.frame = messageContentViewRect;

        self.bubbleBackgroundView.frame = CGRectMake(0, 0, __bubbleSize.width, __bubbleSize.height);

        self.mediaTypeIcon.frame = CGRectMake(14, 10, 20, 20);
        self.textLabel.textColor = dynamic_color(0x262626, 0xe0e0e0);
        self.textLabel.frame =
            CGRectMake(CGRectGetMaxX(self.mediaTypeIcon.frame) + 7, __bubbleHeight / 2 - __labelSize.height / 2,
                       __labelSize.width, __labelSize.height);
        self.bubbleBackgroundView.image = [RCKitUtility imageNamed:@"chat_from_bg_normal" ofBundle:@"RongCloud.bundle"];
        UIImage *image = self.bubbleBackgroundView.image;
        self.bubbleBackgroundView.image = [self.bubbleBackgroundView.image
            resizableImageWithCapInsets:UIEdgeInsetsMake(image.size.height * 0.8, image.size.width * 0.8,
                                                         image.size.height * 0.2, image.size.width * 0.2)];
    } else {
        messageContentViewRect.size.width = __bubbleSize.width;
        messageContentViewRect.size.height = __bubbleSize.height;
        messageContentViewRect.origin.x =
            self.baseContentView.bounds.size.width -
            (messageContentViewRect.size.width + 6 + [RCIM sharedRCIM].globalMessagePortraitSize.width + 10);
        self.messageContentView.frame = messageContentViewRect;

        self.bubbleBackgroundView.frame = CGRectMake(0, 0, __bubbleSize.width, __bubbleSize.height);
        self.textLabel.textColor = dynamic_color(0x3f81bc,0xe0e0e0);
        self.textLabel.frame = CGRectMake(10, 20 - __labelSize.height / 2, __labelSize.width, __labelSize.height);
        self.mediaTypeIcon.frame = CGRectMake(CGRectGetMaxX(self.textLabel.frame) + 7, 10, 20, 20);
        self.bubbleBackgroundView.image = [RCKitUtility imageNamed:@"chat_to_bg_normal" ofBundle:@"RongCloud.bundle"];
        UIImage *image = self.bubbleBackgroundView.image;
        CGRect statusFrame = self.statusContentView.frame;
        statusFrame.origin.x = statusFrame.origin.x + 5;
        [self.statusContentView setFrame:statusFrame];
        self.bubbleBackgroundView.image = [self.bubbleBackgroundView.image
            resizableImageWithCapInsets:UIEdgeInsetsMake(image.size.height * 0.8, image.size.width * 0.2,
                                                         image.size.height * 0.2, image.size.width * 0.8)];
    }
    // self.bubbleBackgroundView.image = image;
}

- (void)longPressed:(id)sender {
    UILongPressGestureRecognizer *press = (UILongPressGestureRecognizer *)sender;
    if (press.state == UIGestureRecognizerStateEnded) {
        return;
    } else if (press.state == UIGestureRecognizerStateBegan) {
        [self.delegate didLongTouchMessageCell:self.model inView:self.bubbleBackgroundView];
    }
}

@end
