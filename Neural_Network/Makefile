CC = gcc
CFLAGS = -Wall -Wextra -g -fsanitize=address
LDLIBS = -lm

SRC = nn.c nn_tools.c weights.c
OBJ = ${SRC:c=o}
EXEC = NeuralNetwork

all: ${EXEC}

${EXEC}: ${OBJ}
	${CC} $^ -o $@ ${CFLAGS} ${LDLIBS} 

%.o: %.c $(SRC)
	${CC} -c $< -o $@ ${CFLAGS} ${LDLIBS}

clean:
	${RM} ${OBJ} ${EXEC} weights
