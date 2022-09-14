CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS =
LDLIBS = `pkg-config --libs sdl2` -lSDL2_image

SRC = main.c sdl_tools.c image.c
#OBJ = ${SRC:.c=.o}
EXEC = echo "Nothing"

all:
	echo "Nothing"

grayscale:
	${CC} ${CFLAGS} ${SRC} ${LDLIBS} -o $@

clean_grayscale:
	${RM} grayscale result_grayscale.png
