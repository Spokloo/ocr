#ifndef TOOLS_H
#define TOOLS_H

#include "rotate.h"

typedef struct GVariables
{

    GtkWidget *parent_window;
    GtkWidget *former_image;
    GtkWidget *solved_image;
    char *filename_base;
    char *filename_rot;
    char *filename_solv;

} GVariables;

int load_gtk_image(GtkWidget *former_image, char *filename, int width,
                   int height);

#endif
