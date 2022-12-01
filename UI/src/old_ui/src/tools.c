#include <gtk/gtk.h>

int load_gtk_image(GtkImage *image, char *filename, int width, int height)
{

    if (filename != NULL)
    {

        GError *error = NULL;
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(
            filename, width / 1.8, height / 1.8, TRUE, &error);

        if (pixbuf == NULL)
        {
            g_printerr("Error loading pixbuf: %s\n", error->message);
            g_clear_error(&error);
            return 1;
        }

        gtk_image_set_from_pixbuf(image, pixbuf);
        return 0;
    }

    return 1;
}
