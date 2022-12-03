CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` `pkg-config --cflags sdl2` -Wall -Wextra -Werror -g
LDLIBS = `pkg-config --libs gtk+-3.0`  `pkg-config --libs sdl2` -lSDL2_image -lm

SRC_DIR = ../Images_Processing/source source
TOOLS_DIR = Tools
INC_DIR = include
OBJ_DIR = obj

SRC = $(shell find $(SRC_DIR) -name "*.c") main.c
TOOLS = $(shell find ../$(TOOLS_DIR) -name "*.c")
INC = $(shell find -name "*.h")

TMP_OBJ = $(SRC:../%=./%)
OBJ = $(addprefix $(OBJ_DIR)/, $(TMP_OBJ:c=o))
TMP = $(TOOLS:../%=%)
OBJ_TOOLS = $(addprefix $(OBJ_DIR)/, $(TMP:c=o))

INC_DIR_ARG = $(addprefix -I, $(shell find -type d -name $(INC_DIR) -not -path '*obj*')) -I../Tools/ -I../Images_Processing/include/

FLAGS = $(INC_DIR_ARG) $(CFLAGS) $(LDLIBS)
EXE = gridokucr-gui

all: init tools $(EXE) clear

init:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(addprefix $(OBJ_DIR)/, $(shell find -type d -not -path '*/.*'))
	@mkdir -p $(OBJ_DIR)/Images_Processing/source
	@mkdir -p $(addprefix $(OBJ_DIR)/, $(TOOLS_DIR))

tools:
	$(foreach file,$(TOOLS), $(CC) $(CFLAGS) -c $(file) -o $(OBJ_DIR)/$(TOOLS_DIR)/$(basename $(notdir $(file))).o;)

clear:
	@find $(OBJ_DIR) -type d -empty -delete

$(EXE): $(OBJ)
	$(CC) $^ $(OBJ_TOOLS) -o $@ $(FLAGS)

$(OBJ_DIR)/%.o: %.c $(INC)
	$(CC) -c $< -o $@ $(FLAGS)

$(OBJ_DIR)/./%.o: ../%.c $(INC)
	$(CC) -c $< -o $@ $(FLAGS)

.PHONY: clean

clean:
	${RM} $(EXE)
	${RM} -rf $(OBJ_DIR)
