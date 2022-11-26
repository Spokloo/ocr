CC = gcc
CFLAGS = -Wall -Wextra
LDLIBS = -lm

SRC = adapt_softmax.c xor.c xor_tools.c
OBJ = ${SRC:c=o}
EXEC = xor

all: ${EXEC}

${EXEC}: ${OBJ}
	${CC} $^ -o $@ ${CFLAGS} ${LDLIBS} 

%.o: %.c $(SRC)
	${CC} -c $< -o $@ ${CFLAGS} ${LDLIBS}

clean:
	${RM} ${OBJ} ${EXEC} weights
