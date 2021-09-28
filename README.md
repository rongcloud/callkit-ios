# callkit-ios
Open-source code of RongCloud VoIP Audio/Video UI. 融云音视频通话功能 UI 界面 SDK 开源代码。

从 V4.1.0 开始, RongCallKit 相关的国际化文字和图片资源文件由 RongCallKit 工程编译生成, 存放在 bin 文件夹下, 如果需要请在此处获取并添加在您的 App 工程中。

从 v5.1.9 开始，RongCallKit 支持以 pod 源码方式集成到项目里面，以下是集成说明：

# 一. 简介

## 1.目标说明

**为了让开发者可以通过 pod 进行 `framework` 和 `源码` 两种形式切换，融云 UI SDK 以 pod 方式开源**

**依赖现有的 `RongCloudIM` & `RongCloudRTC` & `RongCloudOpenSource` 三个 pod， 增加一个新的 pod 源码仓库 `RongCloudRTCOpenSource`**

**`RongCloudRTCOpenSource` 目前存在一个子库 `RongCallKit`**

RongCloudIM 和 RongCloudRTC 里面 SDK 都以 framework 形式存在

RongCloudOpenSource 和 RongCloudRTCOpenSource 里面 SDK 都以源码形式存在，主要包含各个 UI SDK 的源码

```
警告：
建议开发者参考我们各个 UI SDK 的源码实现，以继承方式，在子类中重写父类方法实现自定义相关功能
强烈不建议直接修改 SDK 源码，避免后续版本升级导致修改被重置
```

**·注：RongCloudRTCOpenSource 的发布时间为 RongCloudRTC 发布之后的一到两个工作日， 版本与 RongCloudRTC 一致**

## 2. 引入方式说明

支持 framework 和 源码 两种引入方式

如果需要在 framework 和 源码两种方式之间切换需要涉及 podfile 的声明 和 APP 项目的引入问题，可以参见下面的内容

> podfile

```
pod 'RongCloudRTCOpenSource/RongCallKit','x.x.x'    # RongCallKit
```

> 项目 import

```
#import <RongCallKit.h>
```

## 4. FAQ

> 找不到 RongCloudRTCOpenSource 怎么办？

终端执行 pod repo update 即可
