#!/bin/sh

CC=g++
CFLAGS="-O3"
SRC="main.cpp"
INCLUDE="-lncurses"

$CC $SRC $INCLUDE -o bin/out
