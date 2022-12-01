CC = gcc
CFLAGS = -Wall -Wextra -g
LDLIBS = `pkg-config --libs sdl2` -lSDL2_image -lm

EXEC = main
SRC = main.c $(shell find source -name "*.c")
TOOLS = ../Tools/* ../Images_Post_Grid/include/* ../Images_Post_Grid/source/*
OBJ = ${SRC:.c=.o}

all: ${EXEC}

${EXEC}: ${OBJ}
		${CC} ${CFLAGS} ${TOOLS} $^ ${LDLIBS} -o $@

clean:
	rm -f ${OBJ}
	rm -f ${EXEC}
	rm -f hough_lines.jpeg
	rm -f hough_rotated.jpeg
	rm -f squares_detection.jpeg
	rm -f main_grid_detection.jpeg
	rm -f corrected_perspective.jpeg
	rm -f ??.jpeg
