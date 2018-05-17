//
//  WhiteBoardWebView.m
//  BlinkTalk
//
//  Created by LiuLinhong on 2017/01/13.
//  Copyright © 2017年 BridgeMind. All rights reserved.
//

#import "WhiteBoardWebView.h"

@implementation WhiteBoardWebView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        self.contentScaleFactor = 1.0;
        self.opaque = NO;
        self.scrollView.scrollEnabled = YES;
        self.backgroundColor = [UIColor colorWithRed:1 green:1 blue:1 alpha:0.15];
        self.navigationDelegate = self;
        
//        for (UIView* subView in [self subviews])
//        {
//            if ([subView isKindOfClass:[UIScrollView class]])
//            {
//                for (UIView* shadowView in [subView subviews])
//                {
//                    if ([shadowView isKindOfClass:[UIImageView class]])
//                        [shadowView setHidden:YES];
//                }
//            }
//        }
//        [self setDataDetectorTypes:UIDataDetectorTypeNone];
    }
    
    return self;
}


- (void)setHtml:(NSString *)html
{
    self.html = html;
    [self createWebViewContent];
}

- (void)createWebViewContent
{
    NSString *bundlePath = [[NSBundle mainBundle] bundlePath];
    NSURL *bundleBaseURL = [NSURL fileURLWithPath: bundlePath];
    [self loadHTMLString:_html baseURL:bundleBaseURL];
}

#pragma mark - WKNavigationDelegate
- (void)webView:(WKWebView *)webView didReceiveAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge completionHandler:(void (^)(NSURLSessionAuthChallengeDisposition disposition, NSURLCredential * _Nullable credential))completionHandler{
    
    if ([challenge.protectionSpace.authenticationMethod isEqualToString:NSURLAuthenticationMethodServerTrust]) {
        
        NSURLCredential *card = [[NSURLCredential alloc]initWithTrust:challenge.protectionSpace.serverTrust];
        
        completionHandler(NSURLSessionAuthChallengeUseCredential,card);
        
    }
}

@end
