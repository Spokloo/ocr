#ifndef GRIDOKUCR_H
#define GRIDOKUCR_H

#include <gtk/gtk.h>

#include "image.h"
#include "image_tools.h"
#include "rotate.h"

#include "blur.h"
#include "canny.h"
#include "canny_tools.h"
#include "grayscale.h"
#include "morphological_ops.h"
#include "normalize.h"

#include "houghtransform.h"
#include "auto_rotation.h"
#include "squares.h"
#include "perspective.h"

#include "images_post_grid.h"


typedef struct hs {
    int **real_lines;
    unsigned int lines_len;
    Square *sq;
    Square *gs;
    Image **result_imgs;
} HoughS;

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
    int curr_img;
    int sub_step;
    HoughS **hough_param;
    gboolean is_display;
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

    Step *steps[11];
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
void draw_image(GtkDrawingArea *draw_area, cairo_t *cr, UI *ui, int step, int img);
void set_label_sub_step(UI *ui);
void previous_sub_step(GtkButton *button, UI *ui, int step);
void next_sub_step(GtkButton *button, UI *ui, int step);
void last_step(GtkButton *button, UI *ui, int step);

// CALLBACKS //

// Drawing areas
void on_draw_step2(GtkDrawingArea *draw_area, cairo_t *cr, gpointer user_data);
void on_draw_step3(GtkDrawingArea *draw_area, cairo_t *cr, gpointer user_data);
void on_draw_step4(GtkDrawingArea *draw_area, cairo_t *cr, gpointer user_data);
void on_draw_step5(GtkDrawingArea *draw_area, cairo_t *cr, gpointer user_data);
void on_draw_step6(GtkDrawingArea *draw_area, cairo_t *cr, gpointer user_data);
void on_draw_step8(GtkDrawingArea *draw_area, cairo_t *cr, gpointer user_data);

// Buttons
void cancel_select(GtkButton *button, gpointer user_data);
void confirm_select(GtkButton *button, gpointer user_data);
void on_previous_step3(GtkButton *button, gpointer user_data);
void on_next_step3(GtkButton *button, gpointer user_data);
void on_skip_step3(GtkButton *button, gpointer user_data);
void confirm_sub_steps2(GtkButton *button, gpointer user_data);
void confirm_sub_steps5(GtkButton *button, gpointer user_data);
void confirm_rotation(GtkButton *button, gpointer user_data);
void on_previous_step6(GtkButton *button, gpointer user_data);
void on_next_step6(GtkButton *button, gpointer user_data);
void on_skip_step6(GtkButton *button, gpointer user_data);
void launch_grid_detect(GtkButton *button, gpointer user_data);

// Custom buttons
void on_file_set(GtkFileChooserButton *button, gpointer user_data);
void on_spin_value_changed(GtkSpinButton *spin, gpointer user_data);
void on_scale_value_changed(GtkScale *scale, gpointer user_data);

// MAIN //

/*
 * Main function of the gui, meant to be launched in the main function
 */
int launch_gui(int argc, char **argv);

#endif
