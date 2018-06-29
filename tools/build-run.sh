#!/bin/bash

# setup environment
export CPU=x86
export OS=linux
export VARIANT=debug
#export AJ_ROOT=$HOME/src/core-alljoyn
export AJ_ROOT=$HOME/Src/alljoyn_src/core/alljoyn

export AJLIB=$AJ_ROOT/build/linux/$CPU/$VARIANT/dist/cpp/lib
export AJINC=$AJ_ROOT/build/linux/$CPU/$VARIANT/dist/cpp/inc
export LD_LIBRARY_PATH=$AJLIB:$LD_LIBRARY_PATH

# build
src=custEV
make -C ../$src

# run
./../$src/bin/debug/custEV -c ../data/custEV.ini -m Tesla -d commuter -t 300
