#include <gtk/gtk.h>

#include "callbacks.h"


int main(int argc, char **argv) {
    
    GtkBuilder *builder;
    GObject *window;
    GObject *save_button;
    GObject *open_button;
    GObject *solve_button;
    GObject *rotate_scale;
    GObject *former_image;
    GObject *solved_image;
    GError *error = NULL;

    
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, "ui.glade", &error) == 0) {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    window = gtk_builder_get_object(builder, "main_window");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    former_image = gtk_builder_get_object(builder, "former_image");
    solved_image = gtk_builder_get_object(builder, "solved_image");

    GVariables var = {
        .parent_window = GTK_WIDGET(window),
        .former_image = GTK_WIDGET(former_image),
        .solved_image = GTK_WIDGET(solved_image),
        .filename_base = NULL,
        .filename_rot = NULL,
        .filename_solv = NULL
    };


    save_button = gtk_builder_get_object(builder, "save_button");
    g_signal_connect(save_button, "clicked", G_CALLBACK(on_save_button_clicked), &var);

    open_button = gtk_builder_get_object(builder, "open_button");
    g_signal_connect(open_button, "clicked", G_CALLBACK(on_open_button_clicked), &var);

    solve_button = gtk_builder_get_object(builder, "solve_button");
    g_signal_connect(solve_button, "clicked", G_CALLBACK(on_solve_button_clicked), &var);

    rotate_scale = gtk_builder_get_object(builder, "rotate_scale");
    gtk_range_set_range(GTK_RANGE(rotate_scale), 0, 360);
    g_signal_connect(rotate_scale, "value-changed", G_CALLBACK(on_rotate_scale_value_changed), &var);


    gtk_main();

    return 0;
}
