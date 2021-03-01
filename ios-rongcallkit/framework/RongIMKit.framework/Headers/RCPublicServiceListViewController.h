//
//  RCPublicServiceListViewController.h
//  RongIMKit
//
//  Created by litao on 15/4/20.
//  Copyright (c) 2015年 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RCBaseTableViewController.h"
/*!
 已关注公众服务账号列表的展示ViewController
 */
@interface RCPublicServiceListViewController : RCBaseTableViewController

@property (nonatomic, strong) NSMutableDictionary *allFriends;

@property (nonatomic, strong) NSArray *allKeys;

@end
