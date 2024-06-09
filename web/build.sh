#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "usage: ./build.sh <raylib_source_dir> <libraylib_a_path>"
    exit 1
fi

raysrc=$1
libpath=$2

shopt -s extglob

mkdir build
cd build

cp ../index.html .
cp ../style.css .

em++ -o voxel-builder.html \
   ../web_main.cpp ../../src/!(main).cpp $libpath -O3 -Wall \
   -I$raysrc -I. -L. -I../../src \
   -s USE_GLFW=3  -DPLATFORM_WEB
