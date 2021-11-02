#!/bin/sh

pwd

DST_DIR="./framework"

if [ ! -d ${DST_DIR} ]; then
    mkdir -p ${DST_DIR}
fi

cp -af  ../../ios-imsdk/imlibcore/bin/*.framework ${DST_DIR}
cp -af  ../../ios-imsdk/chatroom/bin/*.framework ${DST_DIR}
cp -af  ../../ios-imsdk/discussion/bin/*.framework ${DST_DIR}
cp -af  ../../ios-imsdk/publicservice/bin/*.framework ${DST_DIR}
cp -af  ../../ios-imsdk/customerservice/bin/*.framework ${DST_DIR}
cp -af  ../../ios-imsdk/location/bin/*.framework ${DST_DIR}
cp -af  ../../ios-imsdk/imlib/bin/*.framework ${DST_DIR}
cp -af  ../../ios-imsdk/imkit/bin/*.framework ${DST_DIR}
cp -af  ../RongCallLib/bin/*.framework ${DST_DIR}

