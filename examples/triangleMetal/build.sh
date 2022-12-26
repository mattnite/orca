#!/bin/bash

BINDIR=../../bin
RESDIR=../../resources
SRCDIR=../../src

INCLUDES="-I$SRCDIR -I$SRCDIR/util -I$SRCDIR/platform -I$SRCDIR/app"
LIBS="-L$BINDIR -lmilepost -framework Carbon -framework Cocoa -framework Metal -framework QuartzCore"
FLAGS="-mmacos-version-min=10.15.4 -DDEBUG -DLOG_COMPILE_DEBUG -Wl,-dead_strip"

xcrun -sdk macosx metal -c -o shader.air shader.metal
xcrun -sdk macosx metallib -o shader.metallib shader.air

clang -g $FLAGS $LIBS $INCLUDES -o test main.m
