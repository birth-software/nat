#/bin/sh
export MY_BUILD_DIR=build
mkdir $MY_BUILD_DIR || true
pushd $MY_BUILD_DIR
#cmake ..
ninja
popd
