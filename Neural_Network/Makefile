CC = gcc
CPPFLAGS =

CFLAGS = -g -Wall -Wextra -fsanitize=address 
LDFLAGS= -fsanitize=address
LDLIBS = -lm

all : xornetwork

SRC = xornetwork.c 
OBJ = ${SRC:.c=.o}
EXE = xornetwork 

xor: ${OBJ}
.PHONY: clean
main:
	xornetwork.o
clean:
	${RM} ${OBJ}
	${RM} ${EXE}

# END
