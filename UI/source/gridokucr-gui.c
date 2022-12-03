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

    step1->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step1"));
    step1->file_chooser_button = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "file_chooser_button"));

    /* STEP 2 */
    Step *step2 = malloc(sizeof(Step));
    step2->buttons = malloc(sizeof(GtkButton *) *2);
    step2->draw_areas = malloc(sizeof(GtkDrawingArea *));
    step2->labels = malloc(sizeof(GtkLabel *));
    step2->images = malloc(sizeof(Image *));
    step2->images[0] = malloc(sizeof(Image));

    step2->curr_img = 0;
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
    step3->images = malloc(sizeof(Image *) * 8);
    for (int i = 0; i < 8; i++)
        step3->images[i] = malloc(sizeof(Image));
    
    step3->curr_img = 0;
    step3->sub_step = 0;
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

    step4->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step4"));
    step4->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "comfirm_rotation_step4"));
    step4->draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step4"));
    step4->scales[0] = GTK_WIDGET(gtk_builder_get_object(builder, "spin_step4"));
    step4->scales[1] = GTK_WIDGET(gtk_builder_get_object(builder, "scale_step4"));
    
    /* STEP 5 */
    Step *step5 = malloc(sizeof(Step));
    step5->buttons = malloc(sizeof(GtkButton *));
    step5->draw_areas = malloc(sizeof(GtkDrawingArea *));

    step5->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step5"));
    step5->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "grid_detect_step5"));
    step5->draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step5"));

    /* STEP 6 */
    Step *step6 = malloc(sizeof(Step));
    step6->buttons = malloc(sizeof(GtkButton *));
    step6->draw_areas = malloc(sizeof(GtkDrawingArea *));
    step6->event_box = malloc(sizeof(GtkEventBox *));

    step6->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step6"));
    step6->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "confirm_crop_step6"));
    step6->draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step6"));
    step6->event_box = GTK_EVENT_BOX(gtk_builder_get_object(builder, "crop_box_step6"));
    
    /* STEP 7 */
    Step *step7 = malloc(sizeof(Step));
    step7->buttons = malloc(sizeof(GtkButton *));
    step7->draw_areas = malloc(sizeof(GtkDrawingArea *));

    step7->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step7"));
    step7->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "digit_recog_step7"));
    step7->draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step7"));

    /* STEP 8 */
    Step *step8 = malloc(sizeof(Step));
    step8->buttons = malloc(sizeof(GtkButton *) * 2);
    step8->draw_areas = malloc(sizeof(GtkDrawingArea *) * 2);
    step8->entries = malloc(sizeof(GtkEntry *) * 3);

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

    g_signal_connect(ui->steps[1]->draw_areas[0], "draw", G_CALLBACK(on_draw_step2), ui);
    g_signal_connect(ui->steps[1]->buttons[0], "clicked", G_CALLBACK(cancel_select), ui);
    g_signal_connect(ui->steps[1]->buttons[1], "clicked", G_CALLBACK(confirm_select), ui);

    g_signal_connect(ui->steps[2]->draw_areas[0], "draw", G_CALLBACK(on_draw_step3), ui);
    g_signal_connect(ui->steps[2]->buttons[1], "clicked", G_CALLBACK(next_sub_step), ui);
}

void set_step(UI *ui, int num)
{
    gtk_stack_set_visible_child(ui->stack, GTK_WIDGET(ui->steps[num]->viewport));
    ui->curr_step = num;
}

void display_image(GtkDrawingArea *draw_area, Image *img, UI *ui, int step, int image)
{
    copy_image(img, ui->steps[step]->images[image]);
    gtk_widget_queue_draw(GTK_WIDGET(draw_area));
}

GdkPixbuf * Image_to_pixbuf(Image *img)
{
    GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, img->width, img->height);

    int width = gdk_pixbuf_get_width(pixbuf);
    int height = gdk_pixbuf_get_height(pixbuf);

    int n_channels = gdk_pixbuf_get_n_channels(pixbuf);
    int rowstride = gdk_pixbuf_get_rowstride(pixbuf);
    guchar *pixels = gdk_pixbuf_get_pixels(pixbuf);

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            guchar *p = pixels + y * rowstride + x * n_channels;
            p[0] = img->matrix[x][y].r;
            p[1] = img->matrix[x][y].g;
            p[2] = img->matrix[x][y].b;
            p[3] = 255;
        }
    }

    return pixbuf;
}

void draw_image(GtkDrawingArea *draw_area, cairo_t *cr, UI *ui, int step, int img)
{
    GdkPixbuf *pixbuf = Image_to_pixbuf(ui->steps[step]->images[img]);

    // Scaling coords and image size //
    gint width = gtk_widget_get_allocated_width(GTK_WIDGET(draw_area));
    gint height = gtk_widget_get_allocated_height(GTK_WIDGET(draw_area));
    gint image_w = ui->steps[step]->images[img]->width;
    gint image_h = ui->steps[step]->images[img]->height;

    gdouble tmp_x = (gdouble) width / image_w;
    gdouble tmp_y = (gdouble) height / image_h;
    gdouble scale = MIN(tmp_x, tmp_y);

    gint image_w_res = image_w * scale;
    gint image_h_res = image_h * scale;
    gint x = (width - image_w_res) /2;
    gint y = (height - image_h_res) /2;
    /////

    pixbuf = gdk_pixbuf_scale_simple(pixbuf, image_w_res, image_h_res, GDK_INTERP_BILINEAR);

    cairo_surface_t *surface = gdk_cairo_surface_create_from_pixbuf(pixbuf, 1, NULL);

    cairo_set_source_surface(cr, surface, x, y);
    cairo_rectangle(cr, x, y, image_w_res, image_h_res);

    cairo_fill(cr);

    g_object_unref(pixbuf);
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

    display_image(ui->steps[1]->draw_areas[0], &img, ui, 1, 0);

    g_print("File selected.\nPath: %s\n", ui->steps[1]->images[0]->path);

    gchar buffer[200];
    g_snprintf(buffer, 200, "Image path: %s", path);
    gtk_label_set_text(ui->steps[1]->labels[0], buffer);

    set_step(ui, 1);
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
    display_image(ui->steps[2]->draw_areas[0], ui->steps[1]->images[0], ui, 2, 0);
}


/* STEP 2 */
void next_sub_step(GtkButton *button, gpointer user_data)
{
    UI *ui = user_data;
    ++ui->steps[2]->sub_step;
    g_print("Clicked: curr sub step: %d\n", ui->steps[2]->sub_step);

    switch (ui->steps[2]->sub_step)
    {
        case 1:
        {
            Image gray_scale;
            copy_image(ui->steps[2]->images[0], &gray_scale);
            ++ui->steps[2]->curr_img;

            grayscale(&gray_scale);
            copy_image(&gray_scale, ui->steps[2]->images[1]);

            gtk_widget_queue_draw(GTK_WIDGET(ui->steps[2]->draw_areas[0]));
            g_print("Displaying gray_scale!\n");
            break;
        }

        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
    }


    gtk_button_get_label(button); // prevent unused param

}

void on_draw_step2(GtkDrawingArea *draw_area, cairo_t *cr, gpointer user_data)
{
    UI *ui = user_data;
    draw_image(draw_area, cr, ui, 1, 0);
}

void on_draw_step3(GtkDrawingArea *draw_area, cairo_t *cr, gpointer user_data)
{
    UI *ui = user_data;
    draw_image(draw_area, cr, ui, 2, ui->steps[2]->curr_img);
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
