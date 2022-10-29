@ECHO OFF

SET CC=gcc
SET CFLAGS=-std=c99 -s -O2 -Wall -Wextra -Wpedantic
SET SRC=src/start.c
SET EXE=txtodo

IF EXIST %EXE% del %EXE%
%CC% %CFLAGS% %SRC% -o %EXE%
