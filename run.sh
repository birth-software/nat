#!/bin/sh
set -e
source ./compile.sh
gf2 -ex=r --args $MY_BUILD_DIR/nativity -main bootstrap/main.c
