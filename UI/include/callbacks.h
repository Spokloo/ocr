#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "tools.h"

void on_save_button_clicked(GtkButton *button, gpointer user_data);

void on_open_button_clicked(GtkButton *button, gpointer user_data);

void on_rotate_scale_value_changed(GtkRange *rotate, gpointer user_data);

void on_solve_button_clicked(GtkButton *button, gpointer user_data);

void on_resize(GtkWindow *window, gpointer user_data);


#endif
