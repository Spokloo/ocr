C = gcc
CPPFLAGS =
CFLAGS = -g -Wall -Wextra 
LDLIBS = -lm

all : xornetwork

SRC = xornetwork.c 
OBJ = ${SRC:.c=.o}
EXE = ${SRC:.c=}

xor: xornetwork.o
.PHONY: clean
main:
	xornetwork.o
clean:
	${RM} ${OBJ}
	${RM} ${EXE}

# END
