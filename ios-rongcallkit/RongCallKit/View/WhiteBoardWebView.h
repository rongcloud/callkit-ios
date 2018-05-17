//
//  WhiteBoardWebView.h
//  BlinkTalk
//
//  Created by LiuLinhong on 2017/01/13.
//  Copyright © 2017年 BridgeMind. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WebKit/WebKit.h>

@interface WhiteBoardWebView : WKWebView <WKNavigationDelegate>

@property (nonatomic, strong) NSString *html;

@end
