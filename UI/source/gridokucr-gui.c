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
    step2->is_display = FALSE;

    /* STEP 3 */
    Step *step3 = malloc(sizeof(Step));
    step3->buttons = malloc(sizeof(GtkButton *) * 4);
    step3->draw_areas = malloc(sizeof(GtkDrawingArea *));
    step3->labels = malloc(sizeof(GtkLabel *));
    step3->images = malloc(sizeof(Image *) * 7);
    for (int i = 0; i < 7; i++)
        step3->images[i] = malloc(sizeof(Image));
    
    step3->curr_img = 0;
    step3->sub_step = 0;
    step3->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step3"));
    step3->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "previous_step3"));
    step3->buttons[1] = GTK_BUTTON(gtk_builder_get_object(builder, "next_step3"));
    step3->buttons[2] = GTK_BUTTON(gtk_builder_get_object(builder, "last_step3"));
    step3->buttons[3] = GTK_BUTTON(gtk_builder_get_object(builder, "confirm_filters_step3"));
    step3->draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step3"));
    step3->labels[0] = GTK_LABEL(gtk_builder_get_object(builder, "sub_step_name_step3"));
    step3->is_display = FALSE;

    /* STEP 4 */
    Step *step4 = malloc(sizeof(Step));
    step4->buttons = malloc(sizeof(GtkButton *));
    step4->draw_areas = malloc(sizeof(GtkDrawingArea *));
    step4->scales = malloc(sizeof(GtkWidget *) * 2);
    step4->images = malloc(sizeof(Image *) * 2);
    step4->images[0] = malloc(sizeof(Image));
    step4->images[1] = malloc(sizeof(Image));

    step4->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step4"));
    step4->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "confirm_rotation_step4"));
    step4->draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step4"));
    step4->scales[0] = GTK_WIDGET(gtk_builder_get_object(builder, "spin_step4"));
    step4->scales[1] = GTK_WIDGET(gtk_builder_get_object(builder, "scale_step4"));
    step4->is_display = FALSE;
    
    /* STEP 5 */
    Step *step5 = malloc(sizeof(Step));
    step5->buttons = malloc(sizeof(GtkButton *));
    step5->draw_areas = malloc(sizeof(GtkDrawingArea *));
    step5->images = malloc(sizeof(Image *));
    step5->images[0] = malloc(sizeof(Image));

    step5->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step5"));
    step5->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "grid_detect_step5"));
    step5->draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step5"));
    step5->is_display = FALSE;

    /* STEP 6 */
    Step *step6 = malloc(sizeof(Step));
    step6->buttons = malloc(sizeof(GtkButton *) * 4);
    step6->draw_areas = malloc(sizeof(GtkDrawingArea *));
    step6->labels = malloc(sizeof(GtkLabel *));
    step6->images = malloc(sizeof(Image *) * 6);
    for (int i = 0; i < 6; i++)
        step6->images[i] = malloc(sizeof(Image));
    step6->hough_param = malloc(sizeof(HoughS *) * 4);
    for (int j = 0; j < 4; j++)
    {
        step6->hough_param[j] = malloc(sizeof(HoughS));
        step6->hough_param[j]->result_imgs = malloc(sizeof(Image *) * 5);
        for (int i = 0; i < 5; i++)
            step6->hough_param[j]->result_imgs[i] = NULL;
    }
    
    step6->curr_img = 0;
    step6->sub_step = 0;
    step6->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step6"));
    step6->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "previous_step6"));
    step6->buttons[1] = GTK_BUTTON(gtk_builder_get_object(builder, "next_step6"));
    step6->buttons[2] = GTK_BUTTON(gtk_builder_get_object(builder, "last_step6"));
    step6->buttons[3] = GTK_BUTTON(gtk_builder_get_object(builder, "confirm_detect_step6"));
    step6->draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step6"));
    step6->labels[0] = GTK_LABEL(gtk_builder_get_object(builder, "sub_step_name_step6"));
    for (int i = 0; i < 4; i++)
    {
        step6->hough_param[i]->real_lines = NULL;
        step6->hough_param[i]->lines_len = 0;
        step6->hough_param[i]->sq = NULL;
        step6->hough_param[i]->gs = NULL;
    }
    step6->is_display = FALSE;

    /* STEP 7 */
    Step *step7 = malloc(sizeof(Step));
    step7->buttons = malloc(sizeof(GtkButton *));
    step7->draw_areas = malloc(sizeof(GtkDrawingArea *));
    step7->event_box = malloc(sizeof(GtkEventBox *));
    step7->images = malloc(sizeof(Image *));
    step7->images[0] = malloc(sizeof(Image));

    step7->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step7"));
    step7->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "confirm_crop_step7"));
    step7->draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step7"));
    step7->event_box = GTK_EVENT_BOX(gtk_builder_get_object(builder, "crop_box_step7"));
    
    /* STEP 8 */
    Step *step8 = malloc(sizeof(Step));
    step8->buttons = malloc(sizeof(GtkButton *));
    step8->draw_areas = malloc(sizeof(GtkDrawingArea *));
    step8->images = malloc(sizeof(Image *));
    step8->images[0] = malloc(sizeof(Image));

    step8->curr_img = 0;
    step8->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step8"));
    step8->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "digit_recog_step8"));
    step8->draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step8"));
    step8->is_display = FALSE;

    /* STEP 9 */
    Step *step9 = malloc(sizeof(Step));
    step9->buttons = malloc(sizeof(GtkButton *) * 2);
    step9->draw_areas = malloc(sizeof(GtkDrawingArea *) * 2);
    step9->entries = malloc(sizeof(GtkEntry *) * 3);
    step9->images = malloc(sizeof(Image *) * 2);
    for (int i = 0; i < 2; i++)
        step9->images[i] = malloc(sizeof(Image));

    step9->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step9"));
    step9->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "place_digit_step9"));
    step9->buttons[1] = GTK_BUTTON(gtk_builder_get_object(builder, "confirm_recog_step9"));
    step9->draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_det_step9"));
    step9->draw_areas[1] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_gen_step9"));
    step9->entries[0] = GTK_ENTRY(gtk_builder_get_object(builder, "line_entry_step9"));
    step9->entries[1] = GTK_ENTRY(gtk_builder_get_object(builder, "column_entry_step9"));
    step9->entries[2] = GTK_ENTRY(gtk_builder_get_object(builder, "digit_entry_step9"));
    step9->is_display = FALSE;
    step9->curr_img = 0;

    /* STEP 10 */
    Step *step10 = malloc(sizeof(Step));
    step10->buttons = malloc(sizeof(GtkButton *));
    step10->draw_areas = malloc(sizeof(GtkDrawingArea *));
    step10->images = malloc(sizeof(Image *));
    step10->images[0] = malloc(sizeof(Image));

    step10->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step10"));
    step10->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "launch_solver_step10"));
    step10->draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step10"));
    step10->is_display = FALSE;
   
    /* STEP 11 */
    Step *step11 = malloc(sizeof(Step));
    step11->buttons = malloc(sizeof(GtkButton *));
    step11->draw_areas = malloc(sizeof(GtkDrawingArea *));
    step11->images = malloc(sizeof(Image *));
    step11->images[0] = malloc(sizeof(Image));

    step11->viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step11"));
    step11->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "save_solved_grid_step11"));
    step11->draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step11"));
    step11->is_display = FALSE;

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
    ui->steps[10] = step11;

    /* HEADER BAR */
    ui->header = malloc(sizeof(Header *));
    ui->header->header_bar = GTK_HEADER_BAR(gtk_builder_get_object(builder, "header_bar"));
    ui->header->buttons = malloc(sizeof(GtkButton *) * 2);
    ui->header->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "reload_button"));
    ui->header->buttons[1] = GTK_BUTTON(gtk_builder_get_object(builder, "save_img_button"));
    ui->header->button = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "open_img_button"));

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
    ///////// STEPS /////////////
    g_signal_connect(ui->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(ui->steps[0]->file_chooser_button, "file-set", G_CALLBACK(on_file_set), ui);

    g_signal_connect(ui->steps[1]->draw_areas[0], "draw", G_CALLBACK(on_draw_step2), ui);
    g_signal_connect(ui->steps[1]->buttons[0], "clicked", G_CALLBACK(cancel_select), ui);
    g_signal_connect(ui->steps[1]->buttons[1], "clicked", G_CALLBACK(confirm_select), ui);

    g_signal_connect(ui->steps[2]->draw_areas[0], "draw", G_CALLBACK(on_draw_step3), ui);
    g_signal_connect(ui->steps[2]->buttons[0], "clicked", G_CALLBACK(on_previous_step3), ui);
    g_signal_connect(ui->steps[2]->buttons[1], "clicked", G_CALLBACK(on_next_step3), ui);
    g_signal_connect(ui->steps[2]->buttons[2], "clicked", G_CALLBACK(on_skip_step3), ui);
    g_signal_connect(ui->steps[2]->buttons[3], "clicked", G_CALLBACK(confirm_sub_steps2), ui);

    g_signal_connect(ui->steps[3]->draw_areas[0], "draw", G_CALLBACK(on_draw_step4), ui);
    g_signal_connect(ui->steps[3]->scales[0], "value-changed", G_CALLBACK(on_spin_value_changed), ui);
    g_signal_connect(ui->steps[3]->scales[1], "value-changed", G_CALLBACK(on_scale_value_changed), ui);
    g_signal_connect(ui->steps[3]->buttons[0], "clicked", G_CALLBACK(confirm_rotation), ui);

    g_signal_connect(ui->steps[4]->draw_areas[0], "draw", G_CALLBACK(on_draw_step5), ui);
    g_signal_connect(ui->steps[4]->buttons[0], "clicked", G_CALLBACK(launch_grid_detect), ui);

    g_signal_connect(ui->steps[5]->draw_areas[0], "draw", G_CALLBACK(on_draw_step6), ui);
    g_signal_connect(ui->steps[5]->buttons[0], "clicked", G_CALLBACK(on_previous_step6), ui);
    g_signal_connect(ui->steps[5]->buttons[1], "clicked", G_CALLBACK(on_next_step6), ui);
    g_signal_connect(ui->steps[5]->buttons[2], "clicked", G_CALLBACK(on_skip_step6), ui);
    g_signal_connect(ui->steps[5]->buttons[3], "clicked", G_CALLBACK(confirm_sub_steps5), ui);

    g_signal_connect(ui->steps[7]->draw_areas[0], "draw", G_CALLBACK(on_draw_step8), ui);
    g_signal_connect(ui->steps[7]->buttons[0], "clicked", G_CALLBACK(on_launch_digit_recog), ui);

    g_signal_connect(ui->steps[8]->draw_areas[0], "draw", G_CALLBACK(on_draw_step9_0), ui);
    g_signal_connect(ui->steps[8]->draw_areas[1], "draw", G_CALLBACK(on_draw_step9_1), ui);
    g_signal_connect(ui->steps[8]->buttons[0], "clicked", G_CALLBACK(on_place), ui);
    g_signal_connect(ui->steps[8]->buttons[1], "clicked", G_CALLBACK(on_confirm_digit), ui);

    g_signal_connect(ui->steps[9]->draw_areas[0], "draw", G_CALLBACK(on_draw_step10), ui);
    g_signal_connect(ui->steps[9]->buttons[0], "clicked", G_CALLBACK(launch_solver), ui);

    g_signal_connect(ui->steps[10]->draw_areas[0], "draw", G_CALLBACK(on_draw_step11), ui);
    g_signal_connect(ui->steps[10]->buttons[0], "clicked", G_CALLBACK(save_solved_image), ui);

    ///// HEADER BAR /////
    g_signal_connect(ui->header->button, "file-set", G_CALLBACK(on_open_header), ui);
    g_signal_connect(ui->header->buttons[0], "clicked", G_CALLBACK(on_restart), ui);
    g_signal_connect(ui->header->buttons[1], "clicked", G_CALLBACK(on_save_header), ui);
}

void set_step(UI *ui, int num)
{
    gtk_stack_set_visible_child(ui->stack, GTK_WIDGET(ui->steps[num]->viewport));

    if (num != 0)
    {
        gtk_widget_set_sensitive(GTK_WIDGET(ui->header->button), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(ui->header->buttons[1]), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(ui->header->buttons[0]), TRUE);
    }

    ui->steps[ui->curr_step]->is_display = FALSE;
    ui->curr_step = num;
    ui->steps[ui->curr_step]->is_display = TRUE;
}

void display_image(GtkDrawingArea *draw_area, Image *img, UI *ui, int step, int image)
{
    copy_image(img, ui->steps[step]->images[image]);
    gtk_widget_queue_draw(GTK_WIDGET(draw_area));
}

void copy_hough_param(UI *ui, int from, int to)
{
    ui->steps[5]->hough_param[to]->lines_len = ui->steps[5]->hough_param[from]->lines_len;

    if (ui->steps[5]->hough_param[from]->sq != NULL) 
    {
        ui->steps[5]->hough_param[to]->sq = ui->steps[5]->hough_param[from]->sq;
    }

    if (ui->steps[5]->hough_param[from]->gs != NULL)
    {
        ui->steps[5]->hough_param[to]->gs = ui->steps[5]->hough_param[from]->gs;
    }

    ui->steps[5]->hough_param[to]->real_lines = malloc(sizeof(int *) * 
            ui->steps[5]->hough_param[to]->lines_len);
    for (unsigned int i = 0; i < ui->steps[5]->hough_param[from]->lines_len; i++)
    {
        ui->steps[5]->hough_param[to]->real_lines[i] = malloc(sizeof(int) * 3);
        for (int j = 0; j < 3; j++)
        {
            ui->steps[5]->hough_param[to]->real_lines[i][j]= 
                ui->steps[5]->hough_param[from]->real_lines[i][j];
        }
    }

    for (int i = 0; i < 5; i++)
    {
        if (ui->steps[5]->hough_param[from]->result_imgs[i] != NULL)
        {
            ui->steps[5]->hough_param[to]->result_imgs[i] = malloc(sizeof(Image));
            copy_image(ui->steps[5]->hough_param[from]->result_imgs[i],
                ui->steps[5]->hough_param[to]->result_imgs[i]);
        }
    }
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
    copy_image(ui->steps[step]->images[img], ui->curr_img);
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

    cairo_surface_destroy(surface);
    g_object_unref(pixbuf);
}

void set_sub_step_label(UI *ui, int step)
{
    switch (ui->steps[step]->sub_step)
    {
        case 0:
        {
            if (step == 5)
                gtk_label_set_text(ui->steps[5]->labels[0], "Pre-processed image");
            else
                gtk_label_set_text(ui->steps[2]->labels[0], "Original image");
            break;
        } 
        case 1:
        {
            if (step == 5)
                gtk_label_set_text(ui->steps[5]->labels[0], "Applied Hough transform");
            else
                gtk_label_set_text(ui->steps[2]->labels[0], "Applied gray scale");
            break;
        }
        case 2:
        {
            if (step == 5)
                gtk_label_set_text(ui->steps[5]->labels[0], "Applied auto-rotation");
            else
                gtk_label_set_text(ui->steps[2]->labels[0], "Applied normalization");
            break;
        }
        case 3:
        {
            if (step == 5)
                gtk_label_set_text(ui->steps[5]->labels[0], "Applied square detection");
            else
                gtk_label_set_text(ui->steps[2]->labels[0], "Applied Gaussian blur");
            break;
        }
        case 4:
        {
            if (step == 5)
                gtk_label_set_text(ui->steps[5]->labels[0], "Applied perspective correction");
            else
                gtk_label_set_text(ui->steps[2]->labels[0], "Applied dilation");
            break;
        }
        case 5:
        {
            gtk_label_set_text(ui->steps[2]->labels[0], "Applied erosion");
            break;
        }
        case 6:
        {
            gtk_label_set_text(ui->steps[2]->labels[0], "Applied Canny");
            break;
        }
    }
}

void rotate_pixbuf(GtkWidget *widget, UI *ui, gboolean is_scale)
{
    gdouble angle = is_scale ? gtk_range_get_value(GTK_RANGE(widget)) : gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));

    copy_image(ui->steps[3]->images[1], ui->steps[3]->images[0]);
    rotate(ui->steps[3]->images[0], angle);
    rotate(ui->steps[2]->images[5], angle);
    copy_image(ui->steps[2]->images[5], ui->steps[3]->images[0]);

    gtk_widget_queue_draw(GTK_WIDGET(ui->steps[3]->draw_areas[0]));
}

void previous_sub_step(GtkButton *button, UI *ui, int step)
{
    --ui->steps[step]->sub_step;
    g_print("Clicked previous: curr sub step: %d\n", ui->steps[step]->sub_step);
    gtk_widget_set_sensitive(GTK_WIDGET(ui->steps[step]->buttons[1]), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(ui->steps[step]->buttons[2]), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(ui->steps[step]->buttons[3]), FALSE);

    if (ui->steps[step]->sub_step >= 0)
    {
        if (ui->steps[step]->sub_step == 0)
            gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE);
        if (step == 5 && ui->steps[5]->curr_img == 5)
            --ui->steps[5]->curr_img;
        --ui->steps[step]->curr_img;
        gtk_widget_queue_draw(GTK_WIDGET(ui->steps[step]->draw_areas[0]));
    } else {
        ui->steps[step]->sub_step = 0;
    }

    set_sub_step_label(ui, step);
    
}


void next_sub_step(GtkButton *button, UI *ui, int step)
{
    ++ui->steps[step]->sub_step;
    gtk_widget_set_sensitive(GTK_WIDGET(ui->steps[step]->buttons[0]), TRUE);
    g_print("Clicked: curr sub step: %d\n", ui->steps[step]->sub_step);

    if (step == 2)
    {
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
                g_print("Displaying grayscale!\n");
                break;
            }

            case 2:
            {
                Image normal;
                copy_image(ui->steps[2]->images[1], &normal);
                ++ui->steps[2]->curr_img;

                normalize(&normal);
                copy_image(&normal, ui->steps[2]->images[2]);

                gtk_widget_queue_draw(GTK_WIDGET(ui->steps[2]->draw_areas[0]));
                g_print("Displaying normalize!\n");
                break;
            }
            case 3:
            {
                Image blur;
                copy_image(ui->steps[2]->images[2], &blur);
                ++ui->steps[2]->curr_img;
                
                unsigned char filter_size = blur.width > blur.height ? blur.width /300 : blur.height /300;
                gaussian_blur(&blur, filter_size);
                copy_image(&blur, ui->steps[2]->images[3]);

                gtk_widget_queue_draw(GTK_WIDGET(ui->steps[2]->draw_areas[0]));
                g_print("Displaying gaussian blur!\n");
                break;
            }
            case 4:
            {
                Image dilat;
                copy_image(ui->steps[2]->images[3], &dilat);
                ++ui->steps[2]->curr_img;
                
                unsigned char filter_size = dilat.width > dilat.height ? dilat.width /300 : dilat.height /300;
                dilation(&dilat, filter_size);
                copy_image(&dilat, ui->steps[2]->images[4]);

                gtk_widget_queue_draw(GTK_WIDGET(ui->steps[2]->draw_areas[0]));
                g_print("Displaying dilation!\n");
                break;
            }
            case 5:
            {
                Image eros;
                copy_image(ui->steps[2]->images[4], &eros);
                ++ui->steps[2]->curr_img;
                
                unsigned char filter_size = eros.width > eros.height ? eros.width /300 : eros.height /300;
                erosion(&eros, filter_size);
                copy_image(&eros, ui->steps[2]->images[5]);

                gtk_widget_queue_draw(GTK_WIDGET(ui->steps[2]->draw_areas[0]));
                g_print("Displaying erosion!\n");
                break;
            }
            case 6:
            {
                Image can;
                copy_image(ui->steps[2]->images[5], &can);
                ++ui->steps[2]->curr_img;
                
                canny(&can);
                copy_image(&can, ui->steps[2]->images[6]);

                gtk_widget_queue_draw(GTK_WIDGET(ui->steps[2]->draw_areas[0]));
                g_print("Displaying canny!\n");

                gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE);
                gtk_widget_set_sensitive(GTK_WIDGET(ui->steps[2]->buttons[2]), FALSE);
                gtk_widget_set_sensitive(GTK_WIDGET(ui->steps[2]->buttons[3]), TRUE);
                break;
            }
            default:
            {
                ui->steps[2]->sub_step = 7; 
            }
        }

        set_sub_step_label(ui, 2);

    } else {

        switch (ui->steps[5]->sub_step)
        {
            case 1:
            {
                Image hough;
                copy_image(ui->steps[5]->images[0], &hough);
                ++ui->steps[5]->curr_img;
                
                hough_transform(&hough, &ui->steps[5]->hough_param[0]->lines_len, &ui->steps[5]->hough_param[0]->real_lines);
                ui->steps[5]->hough_param[0]->result_imgs[0] = &hough;

                //copy_image(&hough, ui->steps[5]->hough_param->result_imgs[0]);
                copy_image(&hough, ui->steps[5]->images[1]);
                copy_hough_param(ui, 0, 1);

                gtk_widget_queue_draw(GTK_WIDGET(ui->steps[5]->draw_areas[0]));
                g_print("Displaying hough transform!\n");
                break;
            }
            case 2:
            {
                Image auto_rot;
                copy_image(ui->steps[5]->images[1], &auto_rot);
                ++ui->steps[5]->curr_img;

                Image tmp;
                copy_image(ui->steps[5]->images[0], &tmp);
                
                int angle = auto_rotation(&auto_rot, ui->steps[5]->images[0], &ui->steps[5]->hough_param[1]->lines_len,
                        &ui->steps[5]->hough_param[1]->real_lines, &ui->steps[5]->hough_param[1]->result_imgs);

                copy_image(ui->steps[2]->images[5], ui->steps[5]->images[4]);
                if (ui->steps[5]->hough_param[1]->result_imgs[1] != NULL)
                {
                    g_print("Autorotate before canny");
                    rotate(ui->steps[5]->images[4], -angle);
                }

                copy_image(&tmp, ui->steps[5]->images[0]);
                copy_image(&auto_rot, ui->steps[5]->images[2]);
                copy_hough_param(ui, 1, 2);

                gtk_widget_queue_draw(GTK_WIDGET(ui->steps[5]->draw_areas[0]));
                g_print("Displaying auto_rotation!\n");
                break;
            }
            case 3:
            {
                Image squ;
                copy_image(ui->steps[5]->images[2], &squ);
                ++ui->steps[5]->curr_img;
                
                squares(&squ, &ui->steps[5]->hough_param[2]->lines_len, &ui->steps[5]->hough_param[2]->real_lines,
                        &ui->steps[5]->hough_param[2]->sq, &ui->steps[5]->hough_param[2]->gs, &ui->steps[5]->hough_param[2]->result_imgs);
                copy_image(&squ, ui->steps[5]->images[3]);
                copy_hough_param(ui, 2, 3);

                gtk_widget_queue_draw(GTK_WIDGET(ui->steps[5]->draw_areas[0]));
                g_print("Displaying square detection!\n");
                break;
            }
            case 4:
            {
                ++ui->steps[5]->curr_img;
                copy_image(ui->steps[5]->images[4], ui->steps[5]->images[5]);
                
                Square gs = *ui->steps[5]->hough_param[3]->gs;
                int points[8] = {gs.p1.x, gs.p1.y, gs.p2.x, gs.p2.y,
                    gs.p3.x, gs.p3.y, gs.p4.x, gs.p4.y};
                correct_perspective(ui->steps[5]->images[5], points);
                ++ui->steps[5]->curr_img;

                gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE);
                gtk_widget_set_sensitive(GTK_WIDGET(ui->steps[5]->buttons[2]), FALSE);
                gtk_widget_set_sensitive(GTK_WIDGET(ui->steps[5]->buttons[3]), TRUE);

                gtk_widget_queue_draw(GTK_WIDGET(ui->steps[5]->draw_areas[0]));
                g_print("Displaying perspective!\n");
                break;
            }
            default:
            {
                ui->steps[5]->sub_step = 5; 
            }
        }
        set_sub_step_label(ui, 5);
    }


}

void last_step(GtkButton *button, UI *ui, int step)
{
    for (;ui->steps[step]->sub_step < (step == 5 ? 4 : 6);)
        next_sub_step(ui->steps[step]->buttons[1], ui, step);

    gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE);
}

void Image_to_grid(UI *ui)
{
    //// POST GRID DETECTION ////
    Image **cells = malloc(sizeof(Image *) * 81);
    Image *tmp;
    
    get_cells(ui->steps[7]->images[0], cells);

    for (unsigned char i = 0; i < 81; i++)
    {
        post_processing(cells[i]);
        tmp = get_number_in_cell(cells[i]);
        free(cells[i]);
        cells[i] = tmp;
        cells[i] = resize_28(cells[i]);
    }

    //// DIGIT RECOGNITION /// /
    NeuralNetwork nn = new_nn();
    load_weights(&nn, "Neural_Network/weights");
    
    int **grid = load_result(cells, &nn);
    free_nn(&nn);
    for (unsigned char i = 0; i < 81; i++)
    {
        free_image(cells[i]);
        free(cells[i]);
    }
    free(cells);

    ui->steps[7]->grid = grid;
}

void gen_grid(UI *ui, int **old_grid, int **solved_grid, int step)
{
    Image grid_img = load_image("Solved_Grid_Gen/images/blank_grid.png");
    int x = 8, y = 8;

    Pixel normal_color = {.r = 0, .g = 0, .b = 0};
    Pixel red_color = {.r = 255, .g = 0, .b = 0};

    for (unsigned int i = 0; i < 9; i++)
    {
        for (unsigned int j = 0; j < 9; j++)
        {
            if (solved_grid[i][j] != 0)
            {
                if(old_grid != NULL)
                {
                    if(old_grid[i][j] != solved_grid[i][j])
                        place_img(&grid_img, &red_color, solved_grid[i][j], x, y);
                    else
                        place_img(&grid_img, &normal_color, solved_grid[i][j], x, y);
                } else
                    place_img(&grid_img, &normal_color, solved_grid[i][j], x, y);
            }

            if (j == 2 || j == 5)
            {
                x += 4;
            }

            x += 104;
        }
        if (i == 2 || i == 5)
        {
            y += 4;
        }
        y += 104;
        x = 8;
    }

    if (step == 8)
        copy_image(&grid_img, ui->steps[8]->images[1]);
    else
        copy_image(&grid_img, ui->steps[step]->images[0]);

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

    gtk_header_bar_set_subtitle(ui->header->header_bar, g_file_get_basename(file));

    set_step(ui, 1);
}

/* STEP 2 */
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
    set_sub_step_label(ui, 2);
}

void on_draw_step2(GtkDrawingArea *draw_area, cairo_t *cr, gpointer user_data)
{
    UI *ui = user_data;
    if (ui->steps[1]->is_display)
        draw_image(draw_area, cr, ui, 1, 0);
}

void confirm_sub_steps2(GtkButton *button, gpointer user_data)
{
    UI *ui = user_data;

    set_step(ui, 3);
    copy_image(ui->steps[2]->images[ui->steps[2]->curr_img], ui->steps[3]->images[0]);
    copy_image(ui->steps[2]->images[ui->steps[2]->curr_img], ui->steps[3]->images[1]);

    gtk_button_get_label(button); // prevent unused param
}




/* STEP 3 */

void on_previous_step3(GtkButton *button, gpointer user_data)
{
    previous_sub_step(button, user_data, 2);
}
void on_next_step3(GtkButton *button, gpointer user_data)
{
    next_sub_step(button, user_data, 2);
}
void on_skip_step3(GtkButton *button, gpointer user_data)
{
    last_step(button, user_data, 2);
}

void on_draw_step3(GtkDrawingArea *draw_area, cairo_t *cr, gpointer user_data)
{
    UI *ui = user_data;
    if (ui->steps[2]->is_display)
        draw_image(draw_area, cr, ui, 2, ui->steps[2]->curr_img);
}


/* STEP 4 */
void on_draw_step4(GtkDrawingArea *draw_area, cairo_t *cr, gpointer user_data)
{
    UI *ui = user_data;
    if (ui->steps[3]->is_display)
        draw_image(draw_area, cr, ui, 3, 0);
}

void on_scale_value_changed(GtkScale *scale, gpointer user_data)
{
    UI *ui = user_data;
    rotate_pixbuf(GTK_WIDGET(scale), ui, TRUE);
}

void on_spin_value_changed(GtkSpinButton *spin, gpointer user_data)
{
    UI *ui = user_data;
    rotate_pixbuf(GTK_WIDGET(spin), ui, FALSE);
}

void confirm_rotation(GtkButton *button, gpointer user_data)
{
    UI *ui = user_data;

    set_step(ui, 4);
    copy_image(ui->steps[3]->images[0], ui->steps[4]->images[0]);

    gtk_button_get_label(button);
}


/* STEP 5 */
void on_draw_step5(GtkDrawingArea *draw_area, cairo_t *cr, gpointer user_data)
{
    UI *ui = user_data;
    if (ui->steps[4]->is_display)
        draw_image(draw_area, cr, ui, 4, 0);
}

void launch_grid_detect(GtkButton *button, gpointer user_data)
{
    UI *ui = user_data;

    set_step(ui, 5);
    copy_image(ui->steps[4]->images[0], ui->steps[5]->images[0]);

    set_sub_step_label(ui, 5);
    gtk_button_get_label(button);
}

void confirm_sub_steps5(GtkButton *button, gpointer user_data)
{
    UI *ui = user_data;

    set_step(ui, 7);
    copy_image(ui->steps[5]->images[5], ui->steps[7]->images[0]);

    gtk_button_get_label(button); // prevent unused param
}

/* STEP 6 */
void on_draw_step6(GtkDrawingArea *draw_area, cairo_t *cr, gpointer user_data)
{
    UI *ui = user_data;
    if (ui->steps[5]->is_display)
        draw_image(draw_area, cr, ui, 5, ui->steps[5]->curr_img);
}

void on_previous_step6(GtkButton *button, gpointer user_data)
{
    previous_sub_step(button, user_data, 5);
}
void on_next_step6(GtkButton *button, gpointer user_data)
{
    next_sub_step(button, user_data, 5);
}
void on_skip_step6(GtkButton *button, gpointer user_data)
{
    last_step(button, user_data, 5);
}



/* STEP 8 */
void on_draw_step8(GtkDrawingArea *draw_area, cairo_t *cr, gpointer user_data)
{
    UI *ui = user_data;
    if (ui->steps[7]->is_display)
        draw_image(draw_area, cr, ui, 7, ui->steps[7]->curr_img);
}

void on_launch_digit_recog(GtkButton *button, gpointer user_data)
{
    UI *ui = user_data;
    Image_to_grid(ui);

    copy_image(ui->steps[7]->images[0], ui->steps[8]->images[0]);
    gen_grid(ui, NULL, ui->steps[7]->grid, 8);

    set_step(ui, 8);

    gtk_button_get_label(button);
}


/* STEP 9 */
void on_draw_step9_0(GtkDrawingArea *draw_area, cairo_t *cr, gpointer user_data)
{
    UI *ui = user_data;
    if (ui->steps[8]->is_display)
        draw_image(draw_area, cr, ui, 8, 0);
}

void on_draw_step9_1(GtkDrawingArea *draw_area, cairo_t *cr, gpointer user_data)
{
    UI *ui = user_data;
    if (ui->steps[8]->is_display)
        draw_image(draw_area, cr, ui, 8, 1);
}

void on_place(GtkButton *button, gpointer user_data)
{
    UI *ui = user_data;

    int num = atoi(gtk_entry_get_text(ui->steps[8]->entries[2]));
    int row = atoi(gtk_entry_get_text(ui->steps[8]->entries[0]));
    int col = atoi(gtk_entry_get_text(ui->steps[8]->entries[1]));

    if(row < 9 && col < 9)
    {
        ui->steps[7]->grid[row][col] = num;
        gen_grid(ui, NULL, ui->steps[7]->grid, 8);

        gtk_widget_queue_draw(GTK_WIDGET(ui->steps[8]->draw_areas[1]));
    }

    gtk_button_get_label(button);
}

void on_confirm_digit(GtkButton *button, gpointer user_data)
{
    UI *ui = user_data;

    copy_image(ui->steps[8]->images[1], ui->steps[9]->images[0]); 
    set_step(ui, 9);

    gtk_button_get_label(button);
}


/* STEP 10 */
void on_draw_step10(GtkDrawingArea *draw_area, cairo_t *cr, gpointer user_data)
{
    UI *ui = user_data;
    if (ui->steps[9]->is_display)
        draw_image(draw_area, cr, ui, 9, 0);
}

void launch_solver(GtkButton *button, gpointer user_data)
{
    UI *ui = user_data;

    int **tmp = malloc(sizeof(int *) * 9);
    for (int i = 0; i < 9; i++)
    {
        tmp[i] = malloc(sizeof(int) * 9);
        for(int j = 0; j < 9; j++)
        {
            tmp[i][j] = ui->steps[7]->grid[i][j];
        }
    }

    ui->steps[10]->grid = solve(tmp);
    gen_grid(ui, ui->steps[7]->grid, ui->steps[10]->grid, 10);

    for (int i = 0; i < 9; i++)
        free(tmp[i]);
    free(tmp);

    set_step(ui, 10);
    gtk_button_get_label(button);
}


/* STEP 11 */
void on_draw_step11(GtkDrawingArea *draw_area, cairo_t *cr, gpointer user_data)
{
    UI *ui = user_data;
    if (ui->steps[10]->is_display)
        draw_image(draw_area, cr, ui, 10, 0);
}

void save_solved_image(GtkButton *button, gpointer user_data)
{
    UI *ui = user_data;

    // SAVE DIALOG
    GtkWidget *dialog;
    GtkFileChooser *chooser;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
    gint res;

    dialog = gtk_file_chooser_dialog_new(
        "Save file", GTK_WINDOW(ui->window), action, "Cancel",
        GTK_RESPONSE_CANCEL, "Save", GTK_RESPONSE_ACCEPT, NULL);

    chooser = GTK_FILE_CHOOSER(dialog);
    gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);
    gtk_file_chooser_set_current_name(chooser, "Untitled");
    ///

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *res, *filename;
        res = gtk_file_chooser_get_filename(chooser);

        filename = malloc(strlen(res) + 6);
        strcpy(filename, res);
        strcat(filename, ".jpeg\0");

        save_image(ui->steps[10]->images[0], filename);
    }

    gtk_widget_destroy(dialog);
    gtk_button_get_label(button);
}


/* HEADER BAR */
void on_save_header(GtkButton *button, gpointer user_data)
{
    UI *ui = user_data;

    if (ui->curr_step != 0)
    {
        // SAVE DIALOG
        GtkWidget *dialog;
        GtkFileChooser *chooser;
        GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
        gint res;

        dialog = gtk_file_chooser_dialog_new(
            "Save file", GTK_WINDOW(ui->window), action, "Cancel",
            GTK_RESPONSE_CANCEL, "Save", GTK_RESPONSE_ACCEPT, NULL);

        chooser = GTK_FILE_CHOOSER(dialog);
        gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);
        gtk_file_chooser_set_current_name(chooser, "Untitled");
        ///

        res = gtk_dialog_run(GTK_DIALOG(dialog));
        if (res == GTK_RESPONSE_ACCEPT)
        {
            char *res, *filename;
            res = gtk_file_chooser_get_filename(chooser);

            filename = malloc(strlen(res) + 6);
            strcpy(filename, res);
            strcat(filename, ".jpeg\0");

            save_image(ui->curr_img, filename);
        }

        gtk_widget_destroy(dialog);
    }
    gtk_button_get_label(button);
}

void on_open_header(GtkFileChooserButton *button, gpointer user_data)
{
    UI *ui = user_data;

    GFile *file = gtk_file_chooser_get_file(GTK_FILE_CHOOSER(button));
    char *path = g_file_get_path(file);
    
    Image img = load_image(path);

    display_image(ui->steps[ui->curr_step]->draw_areas[0], &img, ui, ui->curr_step, 0);

    set_step(ui, ui->curr_step);
}

void on_restart(GtkButton *button, gpointer user_data)
{
    UI *ui = user_data;

    set_step(ui, 0);
    gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(ui->header->buttons[1]), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(ui->header->button), FALSE);

    gtk_button_get_label(button);
}

////////////





///////////////////   MAIN   ////////////////////////

int launch_gui(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;
    if (gtk_builder_add_from_file(builder, "UI/assets/main.glade", &error) == 0)
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
