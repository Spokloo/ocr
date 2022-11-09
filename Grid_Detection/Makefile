CC = gcc
CFLAGS = -Wall -Wextra -g
LDLIBS = `pkg-config --libs sdl2` -lSDL2_image -lm

EXEC = main
SRC = main.c houghtransform.c
TOOLS = ../Tools/*
OBJ = ${SRC:.c=.o}

all: ${EXEC}

${EXEC}: ${OBJ}
		${CC} ${CFLAGS} ${TOOLS} $^ ${LDLIBS} -o $@

clean:
	rm -f ${OBJ}
	rm -f ${EXEC}
	rm -f result_hough.jpg
