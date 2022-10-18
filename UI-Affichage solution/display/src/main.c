#include <gtk/gtk.h>
#include "rotate.h"
#include <string.h>
#include <stdio.h>


typedef struct GImage {

    GtkImage image;
    char *path;

} GImage;

// okrtj
// qeb
// oigầaguqùeoifiga74
// qgija$ef54a"$e)dfb,a
// = =
//     ézêerf  éjepfiuzsduvnap"etoruig )   épzerd$
//     R
//         PÉIIZEFJ    É⁾'PEOFR =$ ẐEPFVK  87  7
//         ZE+9
//
//             ÉZFÀOIAEÀRÇFG_I Z   ²&ÉZR=F OEDIVHRKZS*QZPORFU  ÀÉ)ÀRGOV 6  578 Z
//
//             AED)ÀI AZZ)EÊR NF   $*Q

char * format_path(char * src) {
    int last_slash = 0, i = 0, j = 0;

    while (src[i] != '\0') {
        if (src[i] == '/') {last_slash = i;}
        i++;
    }
    printf("%s, %d, %d\n", src, last_slash, i);
    
    if (last_slash == 0 && src[0] != '/') {
        return src;
    }
    char * res = malloc(i - last_slash);
    i = last_slash +1;
    while (src[i] != '\0') {
        res[j] = src[i];
        j++;
        i++;
    }
    printf("%s, %li\n", res, strlen(res));

    return res;
}


void on_open_button_file_activated(GtkFileChooserButton *open_button, gpointer user_data) {
    printf("Image loaded\n");

    GImage *f_img = user_data;

    gchar * filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(open_button));

    f_img->path = filename;
    
    GError **error = NULL;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(filename, 200, 200, TRUE, error);
    gtk_image_set_from_pixbuf(&f_img->image, pixbuf);

}


void on_rotate_scale_value_changed(GtkRange *range, gpointer user_data) {
    double value = gtk_range_get_value(range);

    GImage *f_img = user_data;

    Image img = load_image(f_img->path);
   
    rotate(&img, value);

    /*char * path = format_path(f_img->path);*/
    /*char *buffer = malloc(7 + sizeof(f_img->path));*/
    /*strcpy(buffer, "rotate_");*/
    /*strcat(buffer, path);*/
    save_image(&img, "res.jpg");

    GError **error = NULL;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("res.jpg", 200, 200, TRUE, error);
    gtk_image_set_from_pixbuf(&f_img->image, pixbuf);

    //free(buffer);
    free_image(&img);
    g_object_unref(pixbuf);
}



void on_activate(GtkApplication *app)
{
    GtkBuilder *builder = gtk_builder_new_from_file("test.glade");

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    GtkImage *image = GTK_IMAGE(gtk_builder_get_object(builder, "former_image"));
    GtkScale *scale = GTK_SCALE(gtk_builder_get_object(builder, "rotate_scale"));
    GtkFileChooserButton *open_button = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "open_button"));
    //GtkButton *solve_button = GTK_BUTTON(gtk_builder_get_object(builder, "solve_button"));
    

    // VARIABLES
    GImage *former_image = malloc(sizeof(GImage));
    former_image->image = *image;
    //////////


    // OPEN FILE DIALOG
    g_signal_connect(open_button, "file-set", G_CALLBACK(on_open_button_file_activated), former_image);
    /////////////



    // IMAGE ROTATION
    gtk_range_set_range(GTK_RANGE(scale), 0, 360);

    g_signal_connect(GTK_RANGE(scale), "value-changed", G_CALLBACK(on_rotate_scale_value_changed), former_image);
    //////////////////

    

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
