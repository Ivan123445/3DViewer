#include "../../s21_3dviewer.h"

GPtrArray *signals_connect(GtkBuilder *builder) {
    GPtrArray *data = g_ptr_array_new();
    obj_data_t *obj_data = calloc(1, sizeof(obj_data_t));
    gulong *signals_id = calloc(5, sizeof (gulong));
    work_mode_t *display_change_mode = calloc(1, sizeof(display_change_mode));
    *display_change_mode = INITIAL_WORK_MODE;
    g_ptr_array_add(data, builder);
    g_ptr_array_add(data, obj_data);
    g_ptr_array_add(data, display_change_mode);
    g_ptr_array_add(data, signals_id);  // to temporarily disable the signals in change_work_mode


    gtk_builder_connect_signals(builder, NULL);  // auto connect some signals

    GtkWindow *window = (GtkWindow *) gtk_builder_get_object(builder, "Main_window");
    g_signal_connect(window, "destroy", G_CALLBACK(close_app), data);

    GtkFileChooser *chooser = (GtkFileChooser *)gtk_builder_get_object(builder, "File_chooser_widget");
    g_signal_connect(chooser, "file_activated", G_CALLBACK(open_file), data);


    GtkToggleButton *moving_toggle_button = (GtkToggleButton *)gtk_builder_get_object(builder, "Moving_toggle_button");
    GtkToggleButton *rotation_toggle_button = (GtkToggleButton *)gtk_builder_get_object(builder, "Rotation_toggle_button");
    GtkToggleButton *scaling_toggle_button = (GtkToggleButton *)gtk_builder_get_object(builder, "Scaling_toggle_button");
    signals_id[moving_signal] = g_signal_connect(moving_toggle_button, "clicked", G_CALLBACK(change_work_mode), data);
    signals_id[rotation_signal] = g_signal_connect(rotation_toggle_button, "clicked", G_CALLBACK(change_work_mode), data);
    signals_id[scaling_signal] = g_signal_connect(scaling_toggle_button, "clicked", G_CALLBACK(change_work_mode), data);

    GtkButton *up_button     = (GtkButton *)gtk_builder_get_object(builder, "X_up_button");
    GtkButton *down_button   = (GtkButton *)gtk_builder_get_object(builder, "X_down_button");
    GtkButton *left_button   = (GtkButton *)gtk_builder_get_object(builder, "Y_up_button");
    GtkButton *right_button  = (GtkButton *)gtk_builder_get_object(builder, "Y_down_button");
    GtkButton *z_up_button   = (GtkButton *)gtk_builder_get_object(builder, "Z_up_button");
    GtkButton *z_down_button = (GtkButton *)gtk_builder_get_object(builder, "Z_down_button");
    g_signal_connect(up_button,     "clicked", G_CALLBACK(buttons_change_display), data);
    g_signal_connect(down_button,   "clicked", G_CALLBACK(buttons_change_display), data);
    g_signal_connect(left_button,   "clicked", G_CALLBACK(buttons_change_display), data);
    g_signal_connect(right_button,  "clicked", G_CALLBACK(buttons_change_display), data);
    g_signal_connect(z_up_button,   "clicked", G_CALLBACK(buttons_change_display), data);
    g_signal_connect(z_down_button, "clicked", G_CALLBACK(buttons_change_display), data);

    GtkButton *plus_scale_button = (GtkButton *)gtk_builder_get_object(builder, "Plus_scale_button");
    GtkButton *minus_scale_button = (GtkButton *)gtk_builder_get_object(builder, "Minus_scale_button");
    g_signal_connect(plus_scale_button,  "clicked", G_CALLBACK(buttons_change_display), data);
    g_signal_connect(minus_scale_button, "clicked", G_CALLBACK(buttons_change_display), data);


    GtkButton *render_button = (GtkButton *) gtk_builder_get_object(builder, "Render_button");
    g_signal_connect(render_button, "clicked", G_CALLBACK(entrys_change_display), data);

    GtkToggleButton *controller_button = (GtkToggleButton *) gtk_builder_get_object(builder, "Controller_mode_button");
    GtkToggleButton *coordinates_button = (GtkToggleButton *) gtk_builder_get_object(builder, "Coordinates_mode_button");
    signals_id[controller_signal]  = g_signal_connect(controller_button, "clicked", G_CALLBACK(change_input_mode), data);
    signals_id[coordinates_signal] = g_signal_connect(coordinates_button, "clicked", G_CALLBACK(change_input_mode), data);

    GtkFileChooserButton  *image_gif_folder_chooser = (GtkFileChooserButton *) gtk_builder_get_object(builder, "Save_image_folder_chooser_button");
    GtkButton *save_image_button = (GtkButton *) gtk_builder_get_object(builder, "Save_image_button");
    GtkButton *save_gif_button   = (GtkButton *) gtk_builder_get_object(builder, "Save_gif_button");
    g_signal_connect(save_image_button, "clicked", G_CALLBACK(save_image), image_gif_folder_chooser);
//    g_signal_connect(save_gif_button, "clicked", G_CALLBACK(), data);

    return data;
}
