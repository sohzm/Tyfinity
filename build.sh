#!/bin/sh

CC=g++
CFLAGS="-O3"
SRC="main.cpp"
INCLUDE="-lncurses"

mkdir bin
$CC $SRC $INCLUDE -o bin/out
