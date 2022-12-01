CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDLIBS = `pkg-config --libs sdl2` -lSDL2_image -lm

INC = ../Tools include
EXE = grid_gen


all: init tools grid_gen


init:
	mkdir -p obj

tools: $(INC)
	$(CC) $(CFLAGS) -c ../Tools/image.c	-o obj/image.o $(LDLIBS)
	$(CC) $(CFLAGS) -c ../Solver/source/solver_fun.c -o obj/solver_fun.o $(LDLIBS)

grid_gen:
	$(CC) $(CFLAGS) $(addprefix obj/, $(shell ls obj)) -Iinclude -I../Tools -I../Solver/include source/grid_gen.c main.c $(LDLIBS) -o $(EXE)

obj/%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -I../Solver/include -I../Tools -c $< -o $@ $(LDLIBS)


clean:
	${RM} -r obj
	${RM} $(EXE)
	${RM} res.png
