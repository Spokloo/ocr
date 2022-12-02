CC = gcc
CPPFLAGS = -MMD
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -Wextra -Werror -pedantic-errors -fsanitize=address
LDFLAGS = -fsanitize=address
LDLIBS = `pkg-config --libs gtk+-3.0`

SRC = main.c
EXE = main
DEP = ${SRC:.c=.d}

all: $(EXE) $(DEP)

$(foreach f, $(EXE), $(eval $(f):))

.PHONY: clean

clean:
	${RM} $(EXE)
	${RM} ${DEP}
