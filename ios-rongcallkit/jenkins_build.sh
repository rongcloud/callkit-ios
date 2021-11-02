#!/bin/sh -e

#  bulid-imlib.sh
#  RongIMLib
#
#  Created by RongCloud on 4/8/15.
#  Copyright (c) 2015 RongCloud. All rights reserved.

#  sh jenkins_build.sh -version 3.2.1 -configuration Release -build-simulator-architecture true

#失败之后立即退出
trap exit ERR

CONFIGURATION="Release"
VERSION="0.0.0.1"
BUILD_SIMULATOR_ARCHITECTURE="false"
ENABLE_IOS_CALLKIT="false"
PROJECT_NAME="RongCallKit.xcodeproj"
TARGET_NAME="RongCallKit"
COMMIT_ID=`git rev-parse --short HEAD`
CURRENT_DATE=$(date +%Y%m%d%H%M)

# `$#` 表示参数个数
# `$@` 表示字符串形式的参数列表
for((options_index = 1; options_index < $#; options_index=$[$options_index+2])) do
    params_index=$[$options_index+1]
    OPTION=`echo $@|cut -d ' ' -f ${options_index}`
    PARAMETER=`echo $@|cut -d ' ' -f ${params_index}`
    if [ $OPTION == "-version" ]; then
        VERSION=$PARAMETER
    elif [ $OPTION == "-configuration" ]; then
        CONFIGURATION=$PARAMETER
    elif [ $OPTION == "-build-simulator-architecture" ]; then
        BUILD_SIMULATOR_ARCHITECTURE=$PARAMETER
    elif [ $OPTION == "-enable-ios-callkit" ]; then
        ENABLE_IOS_CALLKIT=$PARAMETER
    fi
done

# 如果 framework 目录不存在，说明没有 copy 所以来的 SDK
if [ ! -d "framework" ]; then
    sh before_build.sh
fi

Version_Array=(${VERSION//./ })
Short_Version=${Version_Array[0]}.${Version_Array[1]}.${Version_Array[2]}
echo "Short_Version:${Short_Version}"

INFO_PLIST="./RongCallKit/Info.plist"
Original_Bundle_Short_Version=$(/usr/libexec/PlistBuddy -c "Print CFBundleShortVersionString" $INFO_PLIST)
sed -i ""  -e '/CFBundleShortVersionString/{n;s/'${Original_Bundle_Short_Version}'/'"$Short_Version"'/; }' $INFO_PLIST

Original_RCVersion=$(/usr/libexec/PlistBuddy -c "Print RCVersion" $INFO_PLIST)
sed -i ""  -e '/RCVersion/{n;s/'${Original_RCVersion}'/'"$VERSION"'/; }' $INFO_PLIST

Original_RCCommitId=$(/usr/libexec/PlistBuddy -c "Print RCCommitId" $INFO_PLIST)
sed -i ""  -e '/RCCommitId/{n;s/'${Original_RCCommitId}'/'"$COMMIT_ID"'/; }' $INFO_PLIST

Original_RCDate=$(/usr/libexec/PlistBuddy -c "Print RCDate" $INFO_PLIST)
sed -i ""  -e '/RCDate/{n;s/'${Original_RCDate}'/'"$CURRENT_DATE"'/; }' $INFO_PLIST

sed -i '' -e "s?__RongCallKit__Commit__Unknown?${COMMIT_ID}?g" ./RongCallKit/RCCall.mm
sed -i '' -e "s?__RongCallKit__Time__Unknown?${CURRENT_DATE}?g" ./RongCallKit/RCCall.mm
sed -i '' -e "s?__RongCallKit__Version__Unknown?${VERSION}?g" ./RongCallKit/RCCall.mm

if [ ${ENABLE_IOS_CALLKIT} = "true" ]; then
     sed -i '' -e "s/PUBLIC 1/PUBLIC 0/g" ./RongCallKit/RCCXCall.h
fi

# clean project
xcodebuild clean -configuration $CONFIGURATION -sdk iphoneos
xcodebuild clean -configuration $CONFIGURATION -sdk iphonesimulator


if [ $BUILD_SIMULATOR_ARCHITECTURE == "true" ]; then
xcodebuild -project ${PROJECT_NAME} -target "$TARGET_NAME" -configuration $CONFIGURATION  -sdk iphonesimulator build -allowProvisioningUpdates
fi

xcodebuild -project ${PROJECT_NAME} -target "$TARGET_NAME" -configuration $CONFIGURATION  -sdk iphoneos build -allowProvisioningUpdates
echo "*** Build Target ${TARGET_NAME} complete ****"

rm -rf build

PRODUCT_INFO=`ls -l bin/*.*`
echo "\033[41;42m $PRODUCT_INFO \033[0m"
