#include "gridokucr-gui.h"

UI * init_ui(GtkBuilder *builder)
{
    UI *ui = malloc(sizeof(UI));

    ui->window = GTK_WINDOW(gtk_builder_get_object(builder, "org.gtk.gridokucr"));
    ui->stack = GTK_STACK(gtk_builder_get_object(builder, "stack"));

    Step step1 = {
        .viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step1")),
        .file_chooser_button = malloc(sizeof(GtkFileChooserButton *))
    };
    step1.file_chooser_button = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "file_chooser_button"));

    Step step2 = {
        .viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step2")),
        .buttons = malloc(sizeof(GtkButton *) *2),
        .draw_areas = malloc(sizeof(GtkDrawingArea *)),
        .labels = malloc(sizeof(GtkLabel *)),
    };
    step2.buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "select_button_step2"));
    step2.buttons[1] = GTK_BUTTON(gtk_builder_get_object(builder, "confirm_button_step2"));
    step2.draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step2"));
    step2.labels[0] = GTK_LABEL(gtk_builder_get_object(builder, "image_path_step2"));

    Step step3 = {
        .viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step3")),
        .buttons = malloc(sizeof(GtkButton *) * 3),
        .draw_areas = malloc(sizeof(GtkDrawingArea *)),
        .labels = malloc(sizeof(GtkLabel *))
    };
    step3.buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "previous_step3"));
    step3.buttons[1] = GTK_BUTTON(gtk_builder_get_object(builder, "next_step3"));
    step3.buttons[2] = GTK_BUTTON(gtk_builder_get_object(builder, "last_step3"));
    step3.draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step3"));
    step3.labels[0] = GTK_LABEL(gtk_builder_get_object(builder, "sub_step_name_step3"));

    Step step4 = {
        .viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step4")),
        .buttons = malloc(sizeof(GtkButton *)),
        .draw_areas = malloc(sizeof(GtkDrawingArea *)),
        .scales = malloc(sizeof(GtkWidget *) * 2)
    };
    step4.buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "comfirm_rotation_step4"));
    step4.draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step4"));
    step4.scales[0] = GTK_WIDGET(gtk_builder_get_object(builder, "spin_step4"));
    step4.scales[1] = GTK_WIDGET(gtk_builder_get_object(builder, "scale_step4"));
    
    Step step5 = {
        .viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step5")),
        .buttons = malloc(sizeof(GtkButton *)),
        .draw_areas = malloc(sizeof(GtkDrawingArea *)),
    };
    step5.buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "grid_detect_step5"));
    step5.draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step5"));

    Step step6 = {
        .viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step6")),
        .buttons = malloc(sizeof(GtkButton *)),
        .draw_areas = malloc(sizeof(GtkDrawingArea *)),
        .event_box = malloc(sizeof(GtkEventBox *))
    };
    step6.buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "confirm_crop_step6"));
    step6.draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step6"));
    step6.event_box = GTK_EVENT_BOX(gtk_builder_get_object(builder, "crop_box_step6"));
    
    Step step7 = {
        .viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step7")),
        .buttons = malloc(sizeof(GtkButton *)),
        .draw_areas = malloc(sizeof(GtkDrawingArea *))
    };
    step7.buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "digit_recog_step7"));
    step7.draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step7"));


    Step step8 = {
        .viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step8")),
        .buttons = malloc(sizeof(GtkButton *) * 2),
        .draw_areas = malloc(sizeof(GtkDrawingArea *) * 2),
        .entries = malloc(sizeof(GtkEntry *) * 3)
    };
    step8.buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "place_digit_step8"));
    step8.buttons[1] = GTK_BUTTON(gtk_builder_get_object(builder, "comfirm_recog_step8"));
    step8.draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_det_step8"));
    step8.draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_gen_step8"));
    step8.entries[0] = GTK_ENTRY(gtk_builder_get_object(builder, "line_entry_step8"));
    step8.entries[1] = GTK_ENTRY(gtk_builder_get_object(builder, "column_entry_step8"));
    step8.entries[2] = GTK_ENTRY(gtk_builder_get_object(builder, "digit_entry_step8"));

    Step step9 = {
        .viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step9")),
        .buttons = malloc(sizeof(GtkButton *)),
        .draw_areas = malloc(sizeof(GtkDrawingArea *))
    };
    step9.buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "launch_solver_step9"));
    step9.draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step9"));
    
    Step step10 = {
        .viewport = GTK_VIEWPORT(gtk_builder_get_object(builder, "step10")),
        .buttons = malloc(sizeof(GtkButton *)),
        .draw_areas = malloc(sizeof(GtkDrawingArea *))
    };
    step10.buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "save_solved_grid_step10"));
    step10.draw_areas[0] = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "draw_area_step10"));

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

    ui->header = malloc(sizeof(Header *));
    ui->header->header_bar = GTK_HEADER_BAR(gtk_builder_get_object(builder, "header_bar"));
    ui->header->buttons = malloc(sizeof(GtkButton *) * 3);
    ui->header->buttons[0] = GTK_BUTTON(gtk_builder_get_object(builder, "reload_button"));
    ui->header->buttons[1] = GTK_BUTTON(gtk_builder_get_object(builder, "open_img_button"));
    ui->header->buttons[2] = GTK_BUTTON(gtk_builder_get_object(builder, "save_img_button"));

    ui->progress = malloc(sizeof(Progress *));
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

    return ui;
}










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

    g_signal_connect(ui->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show(GTK_WIDGET(ui->window));

    gtk_main();

    return 0;
}
