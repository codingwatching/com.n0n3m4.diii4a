#!/bin/sh

# need install tools: cmake, gcc/g++ | clang/clang++, make
# need install libraries: SDL2, curl, OpenAL-soft, zlib, FFMPEG


# Setup build type: Release | Debug
BUILD_TYPE=Release
TARGET_PATH="`pwd`/Q3E/src/main/jni/doom3bfg/neo";

cd ${TARGET_PATH};

echo "Configure and generate GNU makefile ......";
cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} CMakeLists.txt;

echo "Build ${BUILD_TYPE} ......";
make;

# clean: make clean;

echo "Target directory: ${TARGET_PATH} ......"

echo "Done";

exit 0;
