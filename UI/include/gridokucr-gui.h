#ifndef GRIDOKUCR_H
#define GRIDOKUCR_H

#include <gtk/gtk.h>
#include "image.h"

typedef struct step {
    GtkViewport *viewport;
    GtkButton **buttons;
    GtkFileChooserButton *file_chooser_button;
    GtkDrawingArea **draw_areas;
    GtkEventBox *event_box;
    GtkLabel **labels;
    GtkEntry **entries;
    GtkWidget **scales;
    Image **images;
} Step;

typedef struct progress {
    GtkBox *box;
    GtkProgressBar *progress_bar;
    GtkButton **buttons;
} Progress;

typedef struct header {
    GtkHeaderBar *header_bar;
    GtkButton **buttons;
} Header;

typedef struct ui {
    GtkWindow *window;
    GtkStack *stack;

    Step *steps[10];
    Header *header;
    Progress *progress;

    int curr_step;
    Image *curr_img;
} UI;



// CUSTOM FUNCTIONS //

/*
 * Initialise the whole UI with malloc
 * @param: *builder -> pointer to builder
 */
UI * init_ui(GtkBuilder *builder);
void connect_signals(UI *ui);
void set_step(UI *ui, int num);

// CALLBACKS //

/*
 * Callback for step1 file chooser button
 * @param: *button -> the file chooser button,
 *         *user_data -> pointer to the ui struct
 */
void on_file_set(GtkFileChooserButton *button, gpointer user_data);

// MAIN //

/*
 * Main function of the gui, meant to be launched in the main function
 */
int launch_gui(int argc, char **argv);

#endif
