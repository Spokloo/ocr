############## DEPENDECIES
IDIR = ../include
ODIR = obj

_DEP = image.h rotate.h tools.h callbacks.h
DEP = $(patsubst %,$(IDIR)/%,$(_DEP))

_OBJ = image.o rotate.o tools.o callbacks.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
#########



############ FLAGS AND LIBS
CC = gcc
CPPFLAGS =
CFLAGS = -I$(IDIR) -Wall -Wextra -Werror `pkg-config --cflags gtk+-3.0` `pkg-config --cflags sdl2` -g
LDFLAGS = 
LDLIBS = `pkg-config --libs gtk+-3.0` `pkg-config --libs sdl2` -lSDL2_image -lm

FLAGS = $(CPPFLAGS) $(CFLAGS) $(LDLIBS)
#########



############## RULES
all: init sudocr-gui

init:
	mkdir -p obj

$(ODIR)/%.o: %.c $(DEP)
	$(CC) -c -o $@ $< $(FLAGS)

sudocr-gui: $(OBJ)
	$(CC) -o $@ $^ $(FLAGS)
#########




############# CLEAN
.PHONY: clean

clean:
	rm -rf $(ODIR)/*.o sudocr-gui res solv $(ODIR)
