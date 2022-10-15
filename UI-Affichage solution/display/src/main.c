#include <stdio.h>
#include "rotate.h"
#include <gtk/gtk.h>
#include <string.h>


typedef struct GImage {

    GtkImage image;
    char *path;

} GImage;


void on_rotate_scale_value_changed(GtkRange *range, gpointer user_data) {
    double value = gtk_range_get_value(range);

    GImage *f_img = user_data;

    Image img = load_image(f_img->path);
   
    rotate(&img, value);

    char *buffer = malloc(7 + sizeof(f_img->path));
    strcpy(buffer, "rotate_");
    strcat(buffer, f_img->path);
    save_image(&img, buffer);

    GError **error = NULL;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(buffer, 200, 200, TRUE, error);
    gtk_image_set_from_pixbuf(&f_img->image, pixbuf);

    free(buffer);
    free_image(&img);
    g_object_unref(pixbuf);

}



void on_activate(GtkApplication *app)
{
    GtkBuilder *builder = gtk_builder_new_from_file("test.glade");

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    //GtkButton *save_button = GTK_BUTTON(gtk_builder_get_object(builder, "save_button"));
    //GtkButton *load_button = GTK_BUTTON(gtk_builder_get_object(builder, "load_button"));
    //GtkButton *solve_button = GTK_BUTTON(gtk_builder_get_object(builder, "solve_button"));

    GtkScale *scale = GTK_SCALE(gtk_builder_get_object(builder, "rotate_scale"));
    gtk_range_set_range(GTK_RANGE(scale), 0, 360);
    //g_signal_connect(scale, "value-changed", G_CALLBACK(print_scale), NULL);


    GError **error = NULL;
    char * path = "image_01.jpeg";
    GtkImage *image = GTK_IMAGE(gtk_builder_get_object(builder, "former_image"));
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(path, 200, 200, TRUE, error);
    gtk_image_set_from_pixbuf(image, pixbuf);

    GImage *former_image = malloc(sizeof(GImage));
    former_image->image = *image;
    former_image->path = path;

    g_signal_connect(GTK_RANGE(scale), "value-changed", G_CALLBACK(on_rotate_scale_value_changed), former_image);

    

    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);
    gtk_window_set_application(GTK_WINDOW(window), app);
    gtk_widget_show_all(window);
}


int main(int argc, char **argv) 
{
    GtkApplication *app = gtk_application_new("org.gtk.ocr", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
