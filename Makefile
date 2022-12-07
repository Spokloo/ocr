#- - - - - - - - VARIABLES - - - - - - - -
CC = gcc -O3#-pedantic-errors -g
CFLAGS = -Wall -Wextra `pkg-config --cflags gtk+-3.0` `pkg-config --cflags sdl2`
LDLIBS = `pkg-config --libs gtk+-3.0 ` `pkg-config --libs sdl2` -lSDL2_image -lm

SRC_DIR = source
INC_DIR = include
DIR_OBJ = obj

#- - - - - - - - AUTOMATIC VARIABLES - - - - - - - -
SRC = $(shell find -name "*.c" -not -path '*main.c*' -not -path '*gridoku-cr-gui.c*'| sed 's/.\///')
SRC_GUI = $(shell find -name "*.c" -not -path '*main.c*' -not -path '*ocr.c*'| sed 's/.\///')
INC = $(shell find -name "*.h")

OBJ = $(addprefix $(DIR_OBJ)/, $(SRC:c=o))
OBJ_GUI = $(addprefix $(DIR_OBJ)/, $(SRC_GUI:c=o))
INC_DIR_ARG = $(addprefix -I, $(shell find -type d -name $(INC_DIR) -not -path '*obj*' | sed 's/.\///')) -ITools/

FLAGS = $(INC_DIR_ARG) $(CFLAGS) $(LDLIBS)

#- - - - - - - - RULES - - - - - - - -
all: init gridoku-cr gridoku-cr-gui clear

init:
	@mkdir -p $(DIR_OBJ)
	@mkdir -p $(addprefix $(DIR_OBJ)/, $(shell find -type d -not -path '*/.*'))

clear:
	@find $(DIR_OBJ) -type d -empty -delete

gridoku-cr: $(OBJ)
	@echo -e "\e[1;31m\\nCompiling Console\e[0m"
	$(CC) $^ -o $@ $(FLAGS)

gridoku-cr-gui: $(OBJ_GUI)
	@echo -e "\e[1;31m\\nCompiling GUI\e[0m"
	$(CC) $^ -o $@ $(FLAGS)

$(DIR_OBJ)/%.o: %.c $(INC)
	$(CC) -c $< -o $@ $(FLAGS)

clean:
	rm -fr $(DIR_OBJ)
	rm -fr gridoku-cr-gui
	rm -f gridoku-cr
