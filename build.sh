#!/bin/sh

CC="gcc"
CFLAGS="-std=c99 -Os -Wall -Wextra -Wpedantic"
SRC="src/start.c"
EXE="txtodo"

set -xe

rm -f ${EXE}
rm -f tmp_*
exec ${CC} ${CFLAGS} ${SRC} -o ${EXE}
