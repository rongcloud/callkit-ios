#!/bin/sh

pwd

DST_DIR="./framework"

if [ ! -d ${DST_DIR} ]; then
    mkdir -p ${DST_DIR}
fi

cp -af  ../../ios-imsdk/imlibcore/bin/RongIMLibCore.framework ${DST_DIR}
cp -af  ../../ios-imsdk/chatroom/bin/RongChatRoom.framework ${DST_DIR}
cp -af  ../../ios-imsdk/discussion/bin/RongDiscussion.framework ${DST_DIR}
cp -af  ../../ios-imsdk/publicservice/bin/RongPublicService.framework ${DST_DIR}
cp -af  ../../ios-imsdk/customerservice/bin/RongCustomerService.framework ${DST_DIR}
cp -af  ../../ios-imsdk/location/bin/RongLocation.framework ${DST_DIR}
cp -af  ../../ios-imsdk/imlib/bin/RongIMLib.framework ${DST_DIR}
cp -af  ../../ios-imsdk/imkit/bin/RongIMKit.framework ${DST_DIR}
cp -af  ../RongCallLib/bin/RongCallLib.framework ${DST_DIR}

