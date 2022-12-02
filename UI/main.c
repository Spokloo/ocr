#include <gtk/gtk.h>

int main(void)
{
    gtk_init(NULL, NULL);
    
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;
    if (gtk_builder_add_from_file(builder, "source/main.glade", &error) == 0)
    {
        g_printerr("Error loading builder: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    GtkWindow *window = GTK_WINDOW(gtk_builder_get_object(builder, "org.gtk.gridokucr"));
    
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show(GTK_WIDGET(window));

    gtk_main();

    return 0;
}
