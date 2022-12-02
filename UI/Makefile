CC = gcc
CPPFLAGS =
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -Wextra -Werror -pedantic-errors -g
LDFLAGS =
LDLIBS = `pkg-config --libs gtk+-3.0`

SRC = main.c
EXE = main

all: $(EXE)

$(foreach f, $(EXE), $(eval $(f):))

.PHONY: clean

clean:
	${RM} $(EXE)
	${RM} ${DEP}
