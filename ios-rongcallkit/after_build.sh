#!/bin/sh

pwd

BIN_DIR="bin"
if [ ! -d "$BIN_DIR" ]; then
mkdir -p "$BIN_DIR"
fi

BIN_DIR_TMP="bin_tmp"
if [ ! -d "$BIN_DIR_TMP" ]; then
mkdir -p "$BIN_DIR_TMP"
fi

#[ -d "framework" ] && rm -rf framework

cp -af ./${TARGET_NAME}/Resources/en.lproj ${BIN_DIR}/
cp -af ./${TARGET_NAME}/Resources/zh-Hans.lproj ${BIN_DIR}/
cp -af ./${TARGET_NAME}/Resources/ar.lproj ${BIN_DIR}/
cp -af ./${TARGET_NAME}/Resources/${TARGET_NAME}.bundle ${BIN_DIR}/


if [ ! -d "$BIN_DIR_TMP/${PLATFORM_NAME}.sdk" ]; then
    mkdir -p "$BIN_DIR_TMP/${PLATFORM_NAME}.sdk"
fi

cp -af ${BUILT_PRODUCTS_DIR}/${TARGET_NAME}.framework/ ${BIN_DIR}/${TARGET_NAME}.framework
cp -af ${BUILT_PRODUCTS_DIR}/${TARGET_NAME}.framework/ ${BIN_DIR_TMP}/${PLATFORM_NAME}.sdk/${TARGET_NAME}.framework
lipo -create $BIN_DIR_TMP/*.sdk/${TARGET_NAME}.framework/${TARGET_NAME} -output ${BIN_DIR}/${TARGET_NAME}.framework/${TARGET_NAME}

# 给 SDK 签名
#codesign -fs - ${BIN_DIR}/${TARGET_NAME}.framework
## 打印签名信息
#codesign -dvvv ${BIN_DIR}/${TARGET_NAME}.framework

# xcframework 生成
echo "------${TARGET_NAME} xcframework build begin ----------------"

IOS_PATH=${BIN_DIR_TMP}/iphoneos.sdk/${TARGET_NAME}.framework
SIMULATOR_PATH=${BIN_DIR_TMP}/iphonesimulator.sdk/${TARGET_NAME}.framework

# 如果 xcframework 已经存在，那么就删除了，生成新的 xcframework
XCFRAMEWORK_DIR="xcframework"
if [ -d $XCFRAMEWORK_DIR ]; then
    rm -rf $XCFRAMEWORK_DIR
fi

# xcframework
FRAMEWORK_CMD=""
if [ -e ${IOS_PATH} ]; then
    FRAMEWORK_CMD="-framework ${IOS_PATH}"
fi
echo "${FRAMEWORK_CMD}"
if [ -e ${SIMULATOR_PATH} ]; then
    FRAMEWORK_CMD="${FRAMEWORK_CMD} -framework ${SIMULATOR_PATH}"
fi

echo "${FRAMEWORK_CMD}"
if [ ${FRAMEWORK_CMD} = ""]; then
    exit 0
fi

echo "▸ build xcframework"
xcodebuild -create-xcframework \
    $FRAMEWORK_CMD \
    -output "${XCFRAMEWORK_DIR}/${TARGET_NAME}.xcframework"

cp -af ./${TARGET_NAME}/Resources/en.lproj ${XCFRAMEWORK_DIR}/
cp -af ./${TARGET_NAME}/Resources/zh-Hans.lproj ${XCFRAMEWORK_DIR}/
cp -af ./${TARGET_NAME}/Resources/ar.lproj ${XCFRAMEWORK_DIR}/
cp -af ./${TARGET_NAME}/Resources/${TARGET_NAME}.bundle ${XCFRAMEWORK_DIR}/

#codesign xcframework
#codesign 真机
#XCFRAMEWORK_IOS="${XCFRAMEWORK_DIR}/$TARGET_NAME.xcframework/ios-arm*/$TARGET_NAME.framework"

#if [ -d $XCFRAMEWORK_IOS ]; then
#echo "▸ codesign ${XCFRAMEWORK_IOS}"
## 给 SDK 签名
#codesign -fs - ${XCFRAMEWORK_IOS}
#echo "▸ codesign info ${XCFRAMEWORK_IOS}"
## 打印签名信息
#codesign -dvvv ${XCFRAMEWORK_IOS}
#fi

#codesign 模拟器
#XCFRAMEWORK_SIMULATOR="${XCFRAMEWORK_DIR}/$TARGET_NAME.xcframework/ios-*simulator/$TARGET_NAME.framework"
#
#if [ -d $XCFRAMEWORK_SIMULATOR ]; then
#echo "▸ codesign ${XCFRAMEWORK_SIMULATOR}"
## 给 SDK 签名
#codesign -fs - ${XCFRAMEWORK_SIMULATOR}
#echo "▸ codesign info ${XCFRAMEWORK_SIMULATOR}"
## 打印签名信息
#codesign -dvvv ${XCFRAMEWORK_SIMULATOR}
#fi

echo "------${TARGET_NAME} xcframework build end ----------------"
