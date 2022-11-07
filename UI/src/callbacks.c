#include <gtk/gtk.h>
#include <string.h>

#include "tools.h"

void on_save_button_clicked(GtkButton *button, gpointer user_data) {

    GVariables *var = user_data;


    if (var->filename_solv != NULL) {
        GtkWidget *dialog;
        GtkFileChooser *chooser;
        GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
        GError *error = NULL;
        gint res;

        gtk_button_set_label(button, "Save");

        dialog = gtk_file_chooser_dialog_new("Save file", GTK_WINDOW(var->parent_window), action,
                                             "Cancel", GTK_RESPONSE_CANCEL,
                                             "Save", GTK_RESPONSE_ACCEPT,
                                             NULL);


        chooser = GTK_FILE_CHOOSER(dialog);
        gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);
        gtk_file_chooser_set_current_name(chooser, "Untitled");

        res = gtk_dialog_run(GTK_DIALOG(dialog));
        if (res == GTK_RESPONSE_ACCEPT) {
            char *res, *filename;
            res = gtk_file_chooser_get_filename(chooser);

            filename = malloc(strlen(res) + 6);
            strcpy(filename, res);
            strcat(filename, ".jpeg\0");

            GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(var->filename_solv, &error);

            if (pixbuf == NULL) {

                g_printerr("Error loading pixbuf :%s\n", error->message);
                g_clear_error(&error);

            } else if (!gdk_pixbuf_save(pixbuf, filename, "jpeg", &error, "quality", "100", NULL)) {

                g_printerr("Error saving file :%s\n", error->message);
                g_clear_error(&error);

            } else {

                gtk_button_set_label(button, "Saved!");
                g_free(filename);

            }
        }

        gtk_widget_destroy(dialog);

    }

}


void on_open_button_clicked(GtkButton *button, gpointer user_data) {

    GVariables *var = user_data;
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    gtk_button_set_label(button, "Open");

    dialog = gtk_file_chooser_dialog_new("Open file", GTK_WINDOW(var->parent_window), action,
                                         "Cancel", GTK_RESPONSE_CANCEL,
                                         "Save", GTK_RESPONSE_ACCEPT,
                                         NULL);

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        char *filename;
        
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
    
        if (load_gtk_image(var->former_image, filename) == 0) {
            var->filename_base = filename;
        }

    }

    gtk_widget_destroy(dialog);
}



void on_rotate_scale_value_changed(GtkRange *rotate_scale, gpointer user_data) {

    GVariables *var = user_data;

    if (gtk_image_get_storage_type(GTK_IMAGE(var->former_image)) == GTK_IMAGE_PIXBUF) {
        double value = gtk_range_get_value(rotate_scale);
        Image img = load_image(var->filename_base);

        rotate(&img, value);
        
        save_image(&img, "res");
        var->filename_rot = "res";

        load_gtk_image(var->former_image, var->filename_rot);

        free_image(&img);
    }
}



void on_solve_button_clicked(GtkButton *button, gpointer user_data) {

    GVariables *var = user_data;

    if (var->filename_rot != NULL) {
        load_gtk_image(var->solved_image, var->filename_rot);
        Image solv = load_image(var->filename_rot);
        save_image(&solv, "solv");
        var->filename_solv = "solv";
        gtk_button_set_label(button, "SOLVED!");
    } else if (var->filename_base != NULL) {
        load_gtk_image(var->solved_image, var->filename_base);
        var->filename_solv = var->filename_base;
        gtk_button_set_label(button, "SOLVED!");
    }
}
