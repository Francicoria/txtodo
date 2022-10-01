#!/bin/sh

CC="gcc"
CFLAGS="-std=c99 -O2 -Wall -Wextra -Wpedantic"
SRC="src/start.c"
EXE="txtodo"

set -xe

rm -f ${EXE}
exec ${CC} ${CFLAGS} ${SRC} -o ${EXE}
