#- - - - - - - - VARIABLES - - - - - - - - 
CC = gcc
CFLAGS = -Wall -Wextra
LDLIBS = `pkg-config --libs sdl2` -lSDL2_image -lm

SRC_DIR = source
SRC_TOOLS = Tools
INC_DIR = include ../$(SRC_TOOLS)
DIR_OBJ = obj
EXEC = neural_network

#- - - - - - - - AUTOMATIC VARIABLES - - - - - - - -
SRC = $(shell find $(SRC_DIR) -name "*.c") main.c
INC = $(shell find $(INC_DIR) -name "*.h")
TOOLS = $(shell find ../$(SRC_TOOLS) -name "*.c")
OBJ = $(addprefix $(DIR_OBJ)/, $(SRC:c=o))
TMP = $(TOOLS:../%=%)
OBJ_TOOLS = $(addprefix $(DIR_OBJ)/, $(TMP:c=o))
INC_DIR_ARG = $(addprefix -I, $(INC_DIR))

#- - - - - - - - RULES - - - - - - - -
all: init tools $(EXEC)

init:
	@mkdir -p $(DIR_OBJ)
	@mkdir -p $(addprefix $(DIR_OBJ)/, $(SRC_DIR))
	@mkdir -p $(addprefix $(DIR_OBJ)/, $(SRC_TOOLS))

tools:
	$(foreach file,$(TOOLS), \
	$(CC) $(CFLAGS) -c $(file) -o $(DIR_OBJ)/$(SRC_TOOLS)/$(basename $(notdir $(file))).o;)

$(EXEC): $(OBJ)
	$(CC) $(INC_DIR_ARG) $(CFLAGS) $(OBJ) $(OBJ_TOOLS) $(LDLIBS) -o $@

$(DIR_OBJ)/%.o: %.c $(INC)
	$(CC) $(INC_DIR_ARG) $(CFLAGS) -c $< -o $@
	
clean:
	rm -rf $(DIR_OBJ)
	rm -f $(EXEC)