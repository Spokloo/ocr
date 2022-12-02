#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    
    GtkBuilder *builder = gtk_builder_new();
    GError *error;
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

    g_object_unref(G_OBJECT(window));
    g_object_unref(G_OBJECT(builder));

    return 0;
}
