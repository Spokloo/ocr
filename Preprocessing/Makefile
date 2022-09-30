CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS =
LDLIBS = `pkg-config --libs sdl2` -lSDL2_image -lm

SRC = contrast/contrast.c grayscale/grayscale.c canny/canny.c main.c
#OBJ = ${SRC:.c=.o}
TOOLS = tools/*

all:
	${CC} ${CFLAGS} ${TOOLS} ${SRC} ${LDLIBS} -o main.exe

.PHONY: grayscale
grayscale:
	${CC} ${CFLAGS} ${TOOLS} $@/* ${LDLIBS} -o $@.exe

.PHONY: rotation
rotation:
	${CC} ${CFLAGS} ${TOOLS} $@/* ${LDLIBS} -o $@.exe

.PHONY: contrast
contrast:
	${CC} ${CFLAGS} ${TOOLS} $@/* ${LDLIBS} -o $@.exe

clean:
	${RM} grayscale.exe result_grayscale.jpg \
	rotation.exe result_rotation.jpg \
	convolution.exe result_convolution.jpg \
	contrast.exe result_contrast.jpg \
	main.exe result.jpg
