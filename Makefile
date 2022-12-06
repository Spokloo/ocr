#- - - - - - - - VARIABLES - - - - - - - -
CC = gcc -pedantic-errors -O3
CFLAGS = -Wall -Wextra `pkg-config --cflags gtk+-3.0` `pkg-config --cflags sdl2`
LDLIBS = `pkg-config --libs gtk+-3.0 ` `pkg-config --libs sdl2` -lSDL2_image -lm

SRC_DIR = source
INC_DIR = include
DIR_OBJ = obj

#- - - - - - - - AUTOMATIC VARIABLES - - - - - - - -
SRC = $(shell find -name "*.c" -not -path '*main.c*' | sed 's/.\///')
INC = $(shell find -name "*.h")

OBJ = $(addprefix $(DIR_OBJ)/, $(SRC:c=o))
INC_DIR_ARG = $(addprefix -I, $(shell find -type d -name $(INC_DIR) -not -path '*obj*' | sed 's/.\///')) -ITools/

FLAGS = $(INC_DIR_ARG) $(CFLAGS) $(LDLIBS)

#- - - - - - - - RULES - - - - - - - -
all: init gridoku-ocr clear

init:
	@mkdir -p $(DIR_OBJ)
	@mkdir -p $(addprefix $(DIR_OBJ)/, $(shell find -type d -not -path '*/.*'))

clear:
	@find $(DIR_OBJ) -type d -empty -delete

gridoku-ocr: $(OBJ)
	$(CC) $^ -o $@ $(FLAGS)

$(DIR_OBJ)/%.o: %.c $(INC)
	$(CC) -c $< -o $@ $(FLAGS)

clean:
	rm -fr $(DIR_OBJ)
	rm -f gridoku-ocr
