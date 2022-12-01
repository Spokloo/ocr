CC = gcc
CFLAGS = -Wall -Wextra
LDLIBS = -lm

SRC = xor.c xor_tools.c main.c
OBJ = ${SRC:c=o}
EXEC = xor

all: ${EXEC}

${EXEC}: ${OBJ}
	${CC} $^ -o $@ ${CFLAGS} ${LDLIBS} 

%.o: %.c $(SRC)
	${CC} -c $< -o $@ ${CFLAGS} ${LDLIBS}

clean:
	${RM} ${OBJ} ${EXEC} weights