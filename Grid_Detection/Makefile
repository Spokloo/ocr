CC = gcc
CFLAGS = -Wall -Wextra -g
LDLIBS = `pkg-config --libs sdl2` -lSDL2_image -lm

SRC_DIR = source
SRC_TOOLS = Tools
SRC_POST_GRID = Images_Post_Grid/$(SRC_DIR)
INC_DIR = include ../$(SRC_TOOLS) ../Images_Post_Grid/include
DIR_OBJ = obj
DIR_RES = results
DIR_CELLS = cells
EXEC = main

SRC = $(shell find $(SRC_DIR) -name "*.c") main.c
INC = $(shell find $(INC_DIR) -name "*.h")
TOOLS = $(shell find ../$(SRC_TOOLS) -name "*.c")
POST_GRID = $(shell find ../$(SRC_POST_GRID) -name "*.c")
OBJ = $(addprefix $(DIR_OBJ)/, $(SRC:c=o))
TMP = $(TOOLS:../%=%)
TMP2 = $(POST_GRID:../%=%)
OBJ_TOOLS = $(addprefix $(DIR_OBJ)/, $(TMP:c=o))
OBJ_POST_GRID = $(addprefix $(DIR_OBJ)/, $(TMP2:c=o))
INC_DIR_ARG = $(addprefix -I, $(INC_DIR))

all: init tools post_grid $(EXEC)

init:
	@mkdir -p $(DIR_OBJ)
	@mkdir -p $(addprefix $(DIR_OBJ)/, $(SRC_DIR))
	@mkdir -p $(addprefix $(DIR_OBJ)/, $(SRC_TOOLS))
	@mkdir -p $(addprefix $(DIR_OBJ)/, $(SRC_POST_GRID))
	@mkdir -p $(DIR_RES)
	@mkdir -p $(addprefix $(DIR_RES)/, $(DIR_CELLS))

tools:
	$(foreach file,$(TOOLS), \
	$(CC) $(CFLAGS) -c $(file) -o $(DIR_OBJ)/$(SRC_TOOLS)/$(basename $(notdir $(file))).o;)

post_grid:
	$(foreach file,$(POST_GRID), \
	$(CC) $(INC_DIR_ARG) $(CFLAGS) -c $(file) -o $(DIR_OBJ)/$(SRC_POST_GRID)/$(basename $(notdir $(file))).o;)

$(EXEC): $(OBJ)
	$(CC) $(INC_DIR_ARG) $(CFLAGS) $(OBJ) $(OBJ_TOOLS) $(OBJ_POST_GRID) $(LDLIBS) -o $@

$(DIR_OBJ)/%.o: %.c $(INC_DIR)
	$(CC) $(INC_DIR_ARG) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(DIR_OBJ)
	rm -rf $(DIR_RES)
	rm -f $(EXEC)

