CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS =
LDLIBS = `pkg-config --libs sdl2` -lSDL2_image -lm

#SRC = main.c sdl_tools.c image.c
#OBJ = ${SRC:.c=.o}
TOOLS = tools/*

all:
	echo "Nothing"

.PHONY: grayscale
grayscale:
	${CC} ${CFLAGS} ${TOOLS} $@/* ${LDLIBS} -o $@.exe

.PHONY: rotation
rotation:
	${CC} ${CFLAGS} ${TOOLS} $@/* ${LDLIBS} -o $@.exe

.PHONY: convolution
convolution:
	${CC} ${CFLAGS} ${TOOLS} grayscale/*e.[ch] $@/* ${LDLIBS} -o $@.exe

clean:
	${RM} grayscale.exe result_grayscale.jpg \
	rotation.exe result_rotation.jpg \
	convolution.exe result_convolution.jpg
