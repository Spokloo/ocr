#include "gridokucr-gui.h"

///////////////////   CUSTOM FUNCTIONS   ////////////////////////

UI * init_ui(GtkBuilder *builder)
{
    UI *ui = malloc(sizeof(UI));

    ui->window = GTK_WINDOW(gtk_builder_get_object(builder, "org.gtk.gridokucr"));
    ui->stack = GTK_STACK(gtk_builder_get_object(builder, "stack"));

    /* STEP 1 */
    Step *step1 = malloc(sizeof(Step));
    step1->file_chooser_button = malloc(sizeof(GtkFileChooserButton *));
    step1->paths = malloc(sizeof(char *));

    step1->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step1"));
    step1->file_chooser_button = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "file_chooser_button"));

    /* STEP 2 */
    Step *step2 = malloc(sizeof(Step));
    step2->buttons = malloc(sizeof(GtkButton *) *2);
    step2->draw_areas = malloc(sizeof(GtkDrawingArea *));
    step2->labels = malloc(sizeof(GtkLabel *));
    step2->paths = malloc(sizeof(char *));
    step2->images = malloc(sizeof(Image *) * 8);

    step2->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step2"));
    step2->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "select_button_step2"));
    step2->buttons[1] = GTK_BUTTON(gtk_builder_get_object(builder, "confirm_button_step2"));
    step2->draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step2"));
    step2->labels[0] = GTK_LABEL(gtk_builder_get_object(builder, "image_path_step2"));

    /* STEP 3 */
    Step *step3 = malloc(sizeof(Step));
    step3->buttons = malloc(sizeof(GtkButton *) * 3);
    step3->draw_areas = malloc(sizeof(GtkDrawingArea *));
    step3->labels = malloc(sizeof(GtkLabel *));
    step3->paths = malloc(sizeof(char *));

    step3->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step3"));
    step3->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "previous_step3"));
    step3->buttons[1] = GTK_BUTTON(gtk_builder_get_object(builder, "next_step3"));
    step3->buttons[2] = GTK_BUTTON(gtk_builder_get_object(builder, "last_step3"));
    step3->draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step3"));
    step3->labels[0] = GTK_LABEL(gtk_builder_get_object(builder, "sub_step_name_step3"));

    /* STEP 4 */
    Step *step4 = malloc(sizeof(Step));
    step4->buttons = malloc(sizeof(GtkButton *));
    step4->draw_areas = malloc(sizeof(GtkDrawingArea *));
    step4->scales = malloc(sizeof(GtkWidget *) * 2);
    step4->paths = malloc(sizeof(char *));

    step4->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step4"));
    step4->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "comfirm_rotation_step4"));
    step4->draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step4"));
    step4->scales[0] = GTK_WIDGET(gtk_builder_get_object(builder, "spin_step4"));
    step4->scales[1] = GTK_WIDGET(gtk_builder_get_object(builder, "scale_step4"));
    
    /* STEP 5 */
    Step *step5 = malloc(sizeof(Step));
    step5->buttons = malloc(sizeof(GtkButton *));
    step5->draw_areas = malloc(sizeof(GtkDrawingArea *));
    step5->paths = malloc(sizeof(char *));

    step5->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step5"));
    step5->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "grid_detect_step5"));
    step5->draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step5"));

    /* STEP 6 */
    Step *step6 = malloc(sizeof(Step));
    step6->buttons = malloc(sizeof(GtkButton *));
    step6->draw_areas = malloc(sizeof(GtkDrawingArea *));
    step6->event_box = malloc(sizeof(GtkEventBox *));
    step6->paths = malloc(sizeof(char *));

    step6->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step6"));
    step6->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "confirm_crop_step6"));
    step6->draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step6"));
    step6->event_box = GTK_EVENT_BOX(gtk_builder_get_object(builder, "crop_box_step6"));
    
    /* STEP 7 */
    Step *step7 = malloc(sizeof(Step));
    step7->buttons = malloc(sizeof(GtkButton *));
    step7->draw_areas = malloc(sizeof(GtkDrawingArea *));
    step7->paths = malloc(sizeof(char *));

    step7->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step7"));
    step7->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "digit_recog_step7"));
    step7->draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step7"));

    /* STEP 8 */
    Step *step8 = malloc(sizeof(Step));
    step8->buttons = malloc(sizeof(GtkButton *) * 2);
    step8->draw_areas = malloc(sizeof(GtkDrawingArea *) * 2);
    step8->entries = malloc(sizeof(GtkEntry *) * 3);
    step8->paths = malloc(sizeof(char *) * 2);

    step8->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step8"));
    step8->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "place_digit_step8"));
    step8->buttons[1] = GTK_BUTTON(gtk_builder_get_object(builder, "comfirm_recog_step8"));
    step8->draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_det_step8"));
    step8->draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_gen_step8"));
    step8->entries[0] = GTK_ENTRY(gtk_builder_get_object(builder, "line_entry_step8"));
    step8->entries[1] = GTK_ENTRY(gtk_builder_get_object(builder, "column_entry_step8"));
    step8->entries[2] = GTK_ENTRY(gtk_builder_get_object(builder, "digit_entry_step8"));

    /* STEP 9 */
    Step *step9 = malloc(sizeof(Step));
    step9->buttons = malloc(sizeof(GtkButton *));
    step9->draw_areas = malloc(sizeof(GtkDrawingArea *));
    step9->paths = malloc(sizeof(char *));

    step9->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step9"));
    step9->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "launch_solver_step9"));
    step9->draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step9"));
   
    /* STEP 10 */
    Step *step10 = malloc(sizeof(Step));
    step10->buttons = malloc(sizeof(GtkButton *));
    step10->draw_areas = malloc(sizeof(GtkDrawingArea *));

    step10->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step10"));
    step10->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "save_solved_grid_step10"));
    step10->draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step10"));

    ui->steps[0] = step1;
    ui->steps[1] = step2;
    ui->steps[2] = step3;
    ui->steps[3] = step4;
    ui->steps[4] = step5;
    ui->steps[5] = step6;
    ui->steps[6] = step7;
    ui->steps[7] = step8;
    ui->steps[8] = step9;
    ui->steps[9] = step10;

    /* HEADER BAR */
    ui->header = malloc(sizeof(Header *));
    ui->header->header_bar = GTK_HEADER_BAR(gtk_builder_get_object(builder, "header_bar"));
    ui->header->buttons = malloc(sizeof(GtkButton *) * 3);
    ui->header->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "reload_button"));
    ui->header->buttons[1] = GTK_BUTTON(gtk_builder_get_object(builder, "open_img_button"));
    ui->header->buttons[2] = GTK_BUTTON(gtk_builder_get_object(builder, "save_img_button"));

    /* PROGRESS BAR */
    ui->progress = malloc(sizeof(Progress *));

    ui->progress->box = GTK_BOX(gtk_builder_get_object(builder, "steps"));
    ui->progress->progress_bar = GTK_PROGRESS_BAR(gtk_builder_get_object(builder, "progress_bar"));

    ui->progress->buttons = malloc(sizeof(GtkButton *) * 8);
    ui->progress->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "step_button1"));
    ui->progress->buttons[1] = GTK_BUTTON(gtk_builder_get_object(builder, "step_button2"));
    ui->progress->buttons[2] = GTK_BUTTON(gtk_builder_get_object(builder, "step_button3"));
    ui->progress->buttons[3] = GTK_BUTTON(gtk_builder_get_object(builder, "step_button4"));
    ui->progress->buttons[4] = GTK_BUTTON(gtk_builder_get_object(builder, "step_button5"));
    ui->progress->buttons[5] = GTK_BUTTON(gtk_builder_get_object(builder, "step_button6"));
    ui->progress->buttons[6] = GTK_BUTTON(gtk_builder_get_object(builder, "step_button7"));
    ui->progress->buttons[7] = GTK_BUTTON(gtk_builder_get_object(builder, "step_button8"));

    ui->curr_step = 0;
    
    ui->curr_img = malloc(sizeof(Image));

    return ui;
}

void connect_signals(UI *ui)
{
    g_signal_connect(ui->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(ui->steps[0]->file_chooser_button, "file-set", G_CALLBACK(on_file_set), ui);

    g_signal_connect(ui->steps[1]->draw_areas[0], "draw", G_CALLBACK(draw_image), ui);
    g_signal_connect(ui->steps[1]->buttons[0], "clicked", G_CALLBACK(cancel_select), ui);
    g_signal_connect(ui->steps[1]->buttons[1], "clicked", G_CALLBACK(confirm_select), ui);

    g_signal_connect(ui->steps[2]->draw_areas[0], "draw", G_CALLBACK(draw_image), ui);
}

void set_step(UI *ui, int num)
{
    gtk_stack_set_visible_child(ui->stack, GTK_WIDGET(ui->steps[num]->viewport));
    ui->curr_step = num;
}

void display_image(GtkDrawingArea *draw_area, Image *img, UI *ui)
{
    copy_image(img, ui->curr_img);
    gtk_widget_queue_draw(GTK_WIDGET(draw_area));
}




////////////





///////////////////   CALLBACKS   ////////////////////////



/* STEP 1*/
void on_file_set(GtkFileChooserButton *button, gpointer user_data)
{
    UI *ui = user_data;

    GFile *file = gtk_file_chooser_get_file(GTK_FILE_CHOOSER(button));
    char *path = g_file_get_path(file);
    
    Image img = load_image(path);

    display_image(ui->steps[1]->draw_areas[0], &img, ui);

    g_print("File selected.\nPath: %s\n", ui->curr_img->path);

    gchar buffer[200];
    g_snprintf(buffer, 200, "Image path: %s", path);
    gtk_label_set_text(ui->steps[1]->labels[0], buffer);

    set_step(ui, 1);
}

void draw_image(GtkDrawingArea *draw_area, cairo_t *cr, gpointer user_data)
{
    UI *ui = user_data;
    GError *error = NULL;

    // Scaling coords and image size //
    gint width = gtk_widget_get_allocated_width(GTK_WIDGET(draw_area));
    gint height = gtk_widget_get_allocated_height(GTK_WIDGET(draw_area));
    gint image_w = ui->curr_img->width;
    gint image_h = ui->curr_img->height;

    gdouble tmp_x = (gdouble) width / image_w;
    gdouble tmp_y = (gdouble) height / image_h;
    gdouble scale = MIN(tmp_x, tmp_y);

    gint image_w_res = image_w * scale;
    gint image_h_res = image_h * scale;
    gint x = (width - image_w_res) /2;
    gint y = (height - image_h_res) /2;


    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(ui->curr_img->path, &error);
    if (pixbuf == NULL)
    {
        g_printerr("Error creating pixbuf: %s\n", error->message);
        g_clear_error(&error);
    } else {

        pixbuf = gdk_pixbuf_scale_simple(pixbuf, image_w_res, image_h_res, GDK_INTERP_BILINEAR);

        cairo_surface_t *surface = gdk_cairo_surface_create_from_pixbuf(pixbuf, 1, NULL);

        cairo_set_source_surface(cr, surface, x, y);
        cairo_rectangle(cr, x, y, image_w_res, image_h_res);

        cairo_fill(cr);
    }

    g_print("Drawing image!\n");
}

void cancel_select(GtkButton *button, gpointer user_data)
{
    UI *ui = user_data;
    gtk_button_get_label(button); // prevent unused param
    set_step(ui, 0);
}

void confirm_select(GtkButton *button, gpointer user_data)
{
    UI *ui = user_data;
    gtk_button_get_label(button); // prevent unused param
    set_step(ui, 2);
    display_image(ui->steps[2]->draw_areas[0], ui->curr_img, ui);
}

////////////





///////////////////   MAIN   ////////////////////////

int launch_gui(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;
    if (gtk_builder_add_from_file(builder, "assets/main.glade", &error) == 0)
    {
        g_printerr("Error loading builder: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    UI *ui = init_ui(builder);
    connect_signals(ui);

    gtk_header_bar_set_subtitle(ui->header->header_bar, "");
    gtk_widget_show(GTK_WIDGET(ui->window));

    gtk_main();

    return 0;
}

////////////
