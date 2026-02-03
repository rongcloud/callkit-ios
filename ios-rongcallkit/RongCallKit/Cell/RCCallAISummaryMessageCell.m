//
//  RCCallAISummaryMessageCell.m
//  RongCallKit
//
//  Created by RongCloud on 25/12/8.
//  Copyright © 2025年 RongCloud. All rights reserved.
//

#import "RCCallAISummaryMessageCell.h"
#import "RCCallKitUtility.h"
#import "RCCallAISummaryMessage.h"

@implementation RCCallAISummaryMessageCell

+ (CGSize)sizeForMessageModel:(RCMessageModel *)model
      withCollectionViewWidth:(CGFloat)collectionViewWidth
         referenceExtraHeight:(CGFloat)extraHeight {
    CGFloat height = 120;
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
    
    // 标题 Label - 显示"AI总结完成"
    self.titleLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    [self.titleLabel setFont:[UIFont boldSystemFontOfSize:17]];
    self.titleLabel.numberOfLines = 1;
    [self.messageContentView addSubview:self.titleLabel];
    
    // 时间 Label - 显示"通话开始时间: xxx"
    self.timeLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    [self.timeLabel setFont:[UIFont systemFontOfSize:17]];
    self.timeLabel.numberOfLines = 0;
    [self.messageContentView addSubview:self.timeLabel];
    
    // 详情 Label - 显示"查看详情"，按钮样式
    self.detailLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    [self.detailLabel setFont:[UIFont systemFontOfSize:17]];
    self.detailLabel.numberOfLines = 1;
    [self.detailLabel setTextAlignment:NSTextAlignmentCenter];
    self.detailLabel.backgroundColor = [UIColor whiteColor];
    self.detailLabel.layer.cornerRadius = 4;
    self.detailLabel.layer.masksToBounds = YES;
    [self.messageContentView addSubview:self.detailLabel];
}

- (void)setDataModel:(RCMessageModel *)model {
    [super setDataModel:model];
    [self setAutoLayout];
}

- (void)setAutoLayout {
    RCCallAISummaryMessage *message = (RCCallAISummaryMessage *)self.model.content;
    
    // 格式化通话开始时间
    NSString *startTimeString = [self formatTimeInterval:message.startTime];
    
    // 设置三个 Label 的文本内容
    NSString *titleText = RCCallKitLocalizedString(@"ai_summary_completed");
    NSString *timeText = [NSString stringWithFormat:@"%@%@", RCCallKitLocalizedString(@"call_start_time"), startTimeString];
    NSString *detailText = RCCallKitLocalizedString(@"show_summary_detail");
    
    self.titleLabel.text = titleText;
    self.timeLabel.text = timeText;
    self.detailLabel.text = detailText;
    
    // 计算最大文本宽度
    CGFloat maxTextWidth = self.baseContentView.bounds.size.width -
                           (10 + RCKitConfigCenter.ui.globalMessagePortraitSize.width + 10) * 2 -
                           (12 + 12);
    
    // 计算各个 Label 的大小
    CGSize titleSize = [titleText boundingRectWithSize:CGSizeMake(maxTextWidth, CGFLOAT_MAX)
                                               options:NSStringDrawingUsesLineFragmentOrigin | NSStringDrawingUsesFontLeading
                                            attributes:@{NSFontAttributeName: self.titleLabel.font}
                                               context:nil].size;
    CGSize timeSize = [timeText boundingRectWithSize:CGSizeMake(maxTextWidth, CGFLOAT_MAX)
                                             options:NSStringDrawingUsesLineFragmentOrigin | NSStringDrawingUsesFontLeading
                                          attributes:@{NSFontAttributeName: self.timeLabel.font}
                                             context:nil].size;
    CGSize detailSize = [self.detailLabel.text boundingRectWithSize:CGSizeMake(maxTextWidth, CGFLOAT_MAX)
                                                 options:NSStringDrawingUsesLineFragmentOrigin | NSStringDrawingUsesFontLeading
                                              attributes:@{NSFontAttributeName: self.detailLabel.font}
                                                 context:nil].size;
    
    titleSize = CGSizeMake(ceilf(titleSize.width), ceilf(titleSize.height));
    timeSize = CGSizeMake(ceilf(timeSize.width), ceilf(timeSize.height));
    detailSize = CGSizeMake(ceilf(detailSize.width) + 16, ceilf(detailSize.height) + 8);
    
    // 计算最大宽度
    CGFloat maxLabelWidth = MAX(MAX(titleSize.width, timeSize.width), detailSize.width);
    float maxWidth = self.baseContentView.bounds.size.width -
        (10 + RCKitConfigCenter.ui.globalMessagePortraitSize.width + 10) * 2 - 5 - (12 + 12);
    if (maxLabelWidth > maxWidth) {
        maxLabelWidth = maxWidth;
    }
    
    // 行间距
    CGFloat titleTimeSpacing = 8;
    CGFloat timeDetailSpacing = 12;
    
    // 计算气泡大小
    CGFloat totalHeight = titleSize.height + titleTimeSpacing + timeSize.height + timeDetailSpacing + detailSize.height;
    CGFloat __bubbleWidth = maxLabelWidth + (12 + 12) < 50 ? 50 : (maxLabelWidth + (12 + 12));
    CGFloat __bubbleHeight = totalHeight + 12 + 12;
    CGSize __bubbleSize = CGSizeMake(__bubbleWidth, __bubbleHeight);
    
    self.messageContentView.contentSize = __bubbleSize;
    
    // 设置各个 Label 的 frame
    CGFloat currentY = 12;
    self.titleLabel.frame = CGRectMake(12, currentY, maxLabelWidth, titleSize.height);
    currentY += titleSize.height + titleTimeSpacing;
    
    self.timeLabel.frame = CGRectMake(12, currentY, maxLabelWidth, timeSize.height);
    currentY += timeSize.height + timeDetailSpacing;
    
    self.detailLabel.frame = CGRectMake(12, currentY, detailSize.width, detailSize.height);
    
    // 设置文本颜色
    UIColor *textColor = RCDYCOLOR(0x262626, 0x040A0F);
    [self.titleLabel setTextColor:textColor];
    [self.timeLabel setTextColor:textColor];
    [self.detailLabel setTextColor:textColor];
}

#pragma mark - Helper

/// 格式化时间戳为可读字符串
- (NSString *)formatTimeInterval:(NSTimeInterval)timeInterval {
    if (timeInterval <= 0) {
        return @"--";
    }
    
    NSDate *date = [NSDate dateWithTimeIntervalSince1970:timeInterval / 1000.0];  // 毫秒时间戳
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    formatter.dateFormat = @"HH:mm:ss";
    return [formatter stringFromDate:date];
}

@end
