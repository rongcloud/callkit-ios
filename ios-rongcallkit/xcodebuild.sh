#!/bin/sh

BIN_DIR="bin"
if [ ! -d "$BIN_DIR" ]; then
mkdir -p "$BIN_DIR"
fi

BIN_DIR_TMP="bin_tmp"
if [ ! -d "$BIN_DIR_TMP" ]; then
mkdir -p "$BIN_DIR_TMP"
fi

DST_DIR="./../ios/ios-rongimdemo/framework"
if [ ! -d "$DST_DIR" ]; then
mkdir -p "$DST_DIR"
fi

DST_DIR2="./../ios/ios-hybrid/apicloud/development/UZApp/RongCloudLib"
if [ ! -d "$DST_DIR2" ]; then
mkdir -p "$DST_DIR2"
fi

DST_DIR3="./../ios/ios-hybrid/apicloud/module/RongCloud/RongCloudLib"
if [ ! -d "$DST_DIR3" ]; then
mkdir -p "$DST_DIR3"
fi

DST_DIR4="./../ios/ios-hybrid/cordova/Plugin/src/ios"
if [ ! -d "$DST_DIR4" ]; then
mkdir -p "$DST_DIR4"
fi

DST_DIR5="./../ios/ios-hybrid/cordova/CordovaDemo/platforms/ios/CordovaDemo/Plugins/cn.rongcloud.imlib"
if [ ! -d "$DST_DIR5" ]; then
mkdir -p "$DST_DIR5"
fi

DST_DIR6="./../ios/ios-rongenterpriseapp/framework"
if [ ! -d "$DST_DIR6" ]; then
mkdir -p "$DST_DIR6"
fi


cp -af ${BUILT_PRODUCTS_DIR}/${TARGET_NAME}.framework/ ${BIN_DIR_TMP}/${PLATFORM_NAME}-${TARGET_NAME}.framework
cp -af ${BUILT_PRODUCTS_DIR}/${TARGET_NAME}.framework/ ${BIN_DIR}/${TARGET_NAME}.framework
lipo -create $BIN_DIR_TMP/*-${TARGET_NAME}.framework/${TARGET_NAME} -output ${BIN_DIR}/${TARGET_NAME}.framework/${TARGET_NAME}


cp -af ${BIN_DIR}/* ${DST_DIR}/
cp -af ${BIN_DIR}/* ${DST_DIR2}/
cp -af ${BIN_DIR}/* ${DST_DIR3}/
cp -af ${BIN_DIR}/* ${DST_DIR4}/
cp -af ${BIN_DIR}/* ${DST_DIR5}/
cp -af ${BIN_DIR}/* ${DST_DIR6}/

echo "callkit xcodebuild end"



