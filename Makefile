CC = gcc
CFLAGS = -std=c99 -O2 -Wall -Wextra -Wpedantic
SRC = $(wildcard src/*.c)
EXE = txtodo

all: clean compile run

clean:
	rm -f "${EXE}"

compile:
	${CC} ${CFLAGS} ${SRC} -o ${EXE}

run:
	./${EXE} example.todo.txt

.PHONY: all clean compile run
