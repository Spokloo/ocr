CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` `pkg-config --cflags sdl2` -Wall -Wextra -Werror -pedantic-errors
LDLIBS = `pkg-config --libs gtk+-3.0`  `pkg-config --libs sdl2` -lSDL2_image -lm

SRC_DIR = source
INC_DIR = include
OBJ_DIR = obj

SRC = $(shell find -name "*.c")
INC = $(shell find -name "*.h")
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:c=o))
INC_DIR_ARG = $(addprefix -I, $(shell find -type d -name $(INC_DIR) -not -path '*obj*')) -I../Tools/

FLAGS = $(INC_DIR_ARG) $(CFLAGS) $(LDLIBS)
EXE = gridokucr-gui

all: init $(EXE) clear

init:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(addprefix $(OBJ_DIR)/, $(shell find -type d -not -path '*/.*'))

clear:
	@find $(OBJ_DIR) -type d -empty -delete

$(EXE): $(OBJ)
	$(CC) $^ -o $@ $(FLAGS)

$(OBJ_DIR)/%.o: %.c $(INC)
	$(CC) -c $< -o $@ $(FLAGS)

.PHONY: clean

clean:
	${RM} $(EXE)
	${RM} -rf $(OBJ_DIR)
