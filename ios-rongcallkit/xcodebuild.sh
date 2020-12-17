#!/bin/sh

BIN_DIR="bin"
if [ ! -d "$BIN_DIR" ]; then
mkdir -p "$BIN_DIR"
fi

BIN_DIR_TMP="bin_tmp"
if [ ! -d "$BIN_DIR_TMP" ]; then
mkdir -p "$BIN_DIR_TMP"
fi


cp -af ./${TARGET_NAME}/Resources/en.lproj ${BIN_DIR}/
cp -af ./${TARGET_NAME}/Resources/zh-Hans.lproj ${BIN_DIR}/
cp -af ./${TARGET_NAME}/Resources/RongCallKit.bundle ${BIN_DIR}/


cp -af ${BUILT_PRODUCTS_DIR}/${TARGET_NAME}.framework/ ${BIN_DIR_TMP}/${PLATFORM_NAME}-${TARGET_NAME}.framework
cp -af ${BUILT_PRODUCTS_DIR}/${TARGET_NAME}.framework/ ${BIN_DIR}/${TARGET_NAME}.framework
lipo -create $BIN_DIR_TMP/*-${TARGET_NAME}.framework/${TARGET_NAME} -output ${BIN_DIR}/${TARGET_NAME}.framework/${TARGET_NAME}


echo "callkit xcodebuild end"



