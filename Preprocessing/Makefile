CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS =
LDLIBS = `pkg-config --libs sdl2` -lSDL2_image -lm

SRC = tools/* contrast/contrast.c grayscale/grayscale.c canny/canny_tools.c \
canny/canny.c normalize/normalize.c morphological_ops/morphological_ops.c \
blur/blur.c main.c
#OBJ = ${SRC:.c=.o}
TOOLS = tools/* grayscale/grayscale.c

all:
	${CC} ${CFLAGS} ${SRC} ${LDLIBS} -o main.exe

.PHONY: grayscale
grayscale:
	${CC} ${CFLAGS} ${TOOLS} $@/* ${LDLIBS} -o $@.exe

.PHONY: rotation
rotation:
	${CC} ${CFLAGS} ${TOOLS} $@/* ${LDLIBS} -o $@.exe

.PHONY: contrast
contrast:
	${CC} ${CFLAGS} ${TOOLS} $@/* ${LDLIBS} -o $@.exe

.PHONY: blur
blur:
	${CC} ${CFLAGS} ${TOOLS} $@/* ${LDLIBS} -o $@.exe

.PHONY: canny
canny:
	${CC} ${CFLAGS} ${TOOLS} $@/* ${LDLIBS} -o $@.exe

.PHONY: normalize
normalize:
	${CC} ${CFLAGS} ${TOOLS} $@/* ${LDLIBS} -o $@.exe

.PHONY: morphological_ops
morphological_ops:
	${CC} ${CFLAGS} ${TOOLS} $@/* ${LDLIBS} -o $@.exe

.PHONY: perspective_correction
perspective_correction:
	${CC} ${CFLAGS} ${TOOLS} $@/* ${LDLIBS} -o $@.exe

clean:
	${RM} grayscale.exe result_grayscale.jpg \
	rotation.exe result_rotation.jpg \
	convolution.exe result_convolution.jpg \
	contrast.exe result_contrast.jpg \
	canny.exe result_canny.jpg \
	normalize.exe result_normalize.jpg \
	morphological_ops.exe result_morpho_ops.jpg \
	blur.exe result_blur.jpg \
	perspective_correction.exe result_perspective.jpg \
	result_image_0?.jpeg \
	main.exe result.jpg