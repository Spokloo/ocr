CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDLIBS = `pkg-config --libs sdl2` -lSDL2_image -lm

SRC = grid_gen.c
OBJ = $(SRC:.c=.o)
INC = ../Tools
OBJ_DIR = $(patsubst %,obj/%,$(OBJ))
EXE = grid_gen


all: init tools grid_gen


init:
	mkdir -p obj

tools: $(INC)
	$(CC) $(CFLAGS) -c ../Tools/image.c	-o obj/image.o $(LDLIBS)
	$(CC) $(CFLAGS) -c ../Solver/solver_fun.c -o obj/solver_fun.o $(LDLIBS)

grid_gen: $(OBJ_DIR)
	$(CC) $(CFLAGS) $(addprefix obj/, $(shell ls obj)) $(LDLIBS) -o $(EXE)

obj/%.o: %.c
	$(CC) $(CFLAGS) -I../Solver -I$(INC) -c $< -o $@ $(LDLIBS)


clean:
	rm -r obj
	rm $(EXE)
	rm res.png
