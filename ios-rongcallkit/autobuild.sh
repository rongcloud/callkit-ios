#!/bin/sh

#  bulid-imlib.sh
#  RongIMLib
#
#  Created by xugang on 4/8/15.
#  Copyright (c) 2015 RongCloud. All rights reserved.

configuration="Release"
DEV_FLAG=""
VER_FLAG=""
ENV_FLAG="pro"

for i in "$@"
do
PFLAG=`echo $i|cut -b1-2`
PPARAM=`echo $i|cut -b3-`
if [ $PFLAG == "-b" ]
then
DEV_FLAG=$PPARAM
elif [ $PFLAG == "-v" ]
then
VER_FLAG=$PPARAM
elif [ ${PFLAG} == "-d" ]
then
ENV_FLAG=$PPARAM
elif [ $PFLAG == "-o" ]
then
VOIP_FLAG=$PPARAM
elif [ $PFLAG == "-g" ]
then
VOIP_TYPE=$PPARAM
fi
done


sed -i ""  -e '/CFBundleShortVersionString/{n;s/[0-9]\.[0-9]\.[0-9]\{1,2\}/'"$VER_FLAG"'/; }' ./RongCallKit/Info.plist

if [ ${VOIP_TYPE} == "Blink" ]
then
sed -i '' -e '/For Agora Only Begin/,/For Agora Only End/d' ./RongCallKit/AudioObserver/RCDAudioFrameObserver.h
sed -i '' -e '/For Agora Only Begin/,/For Agora Only End/d' ./RongCallKit/AudioObserver/RCDAudioFrameObserver.mm
sed -i '' -e '/For Agora Only Begin/,/For Agora Only End/d' ./RongCallKit/VideoObserver/RCDVideoFrameObserver.h
sed -i '' -e '/For Agora Only Begin/,/For Agora Only End/d' ./RongCallKit/VideoObserver/RCDVideoFrameObserver.mm
fi

if [ ${DEV_FLAG} == "debug" ]
then
configuration="Debug"
else
configuration="Release"
fi

PROJECT_NAME="RongCallKit.xcodeproj"
targetName="RongCallKit"
TARGET_DECIVE="iphoneos"
TARGET_I386="iphonesimulator"

xcodebuild clean -configuration $configuration -sdk $TARGET_DECIVE
xcodebuild clean -configuration $configuration -sdk $TARGET_I386

echo "***开始Build ${targetName} Framework ${configuration}****"
echo "***开始build iphonesimulator文件***"
xcodebuild -project ${PROJECT_NAME} -target "$targetName" -configuration $configuration  -sdk $TARGET_I386 build
echo "***开始build iphoneos文件***"
xcodebuild -project ${PROJECT_NAME} -target "$targetName" -configuration $configuration  -sdk $TARGET_DECIVE build
echo "***完成Build ${targetName} Framework ${configuration}****"
