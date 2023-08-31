#include "../../s21_3dviewer.h"

static void init_input_mode_buttons(GtkBuilder *builder, gulong *signals_id) {
    GtkToggleButton *controller_toggle_button = (GtkToggleButton *)gtk_builder_get_object(builder, "Controller_mode_button");
    GtkToggleButton *coordinates_toggle_button = (GtkToggleButton *)gtk_builder_get_object(builder, "Coordinates_mode_button");
    GtkWidget *buttons_input_grid = (GtkWidget *) gtk_builder_get_object(builder, "Buttons_input_grid");
    GtkWidget *entry_input_grid = (GtkWidget *) gtk_builder_get_object(builder, "Entry_input_grid");

    g_signal_handler_block(controller_toggle_button, signals_id[controller_signal]);
    g_signal_handler_block(coordinates_toggle_button, signals_id[coordinates_signal]);

    gtk_toggle_button_set_active(controller_toggle_button, INITIAL_INPUT_MODE == 1);
    gtk_toggle_button_set_active(coordinates_toggle_button, INITIAL_INPUT_MODE == 2);

    gtk_widget_set_visible(buttons_input_grid, INITIAL_INPUT_MODE == 1);
    gtk_widget_set_visible(entry_input_grid, INITIAL_INPUT_MODE == 2);

    g_signal_handler_unblock(controller_toggle_button, signals_id[controller_signal]);
    g_signal_handler_unblock(coordinates_toggle_button, signals_id[coordinates_signal]);
}

static void init_work_mode_buttons(GtkBuilder *builder, gulong *signals_id) {
    GtkToggleButton *moving_toggle_button = (GtkToggleButton *)gtk_builder_get_object(builder, "Moving_toggle_button");
    GtkToggleButton *rotation_toggle_button = (GtkToggleButton *) gtk_builder_get_object(builder, "Rotation_toggle_button");
    GtkToggleButton *scaling_toggle_button = (GtkToggleButton *) gtk_builder_get_object(builder, "Scaling_toggle_button");

    g_signal_handler_block(moving_toggle_button, signals_id[moving_signal]);
    g_signal_handler_block(rotation_toggle_button, signals_id[rotation_signal]);
    g_signal_handler_block(scaling_toggle_button, signals_id[scaling_signal]);

    gtk_toggle_button_set_active(moving_toggle_button, INITIAL_WORK_MODE == moving_mode);
    gtk_toggle_button_set_active(rotation_toggle_button, INITIAL_WORK_MODE == rotation_mode);
    gtk_toggle_button_set_active(scaling_toggle_button, INITIAL_WORK_MODE == scaling_mode);

    g_signal_handler_unblock(moving_toggle_button, signals_id[moving_signal]);
    g_signal_handler_unblock(rotation_toggle_button, signals_id[rotation_signal]);
    g_signal_handler_unblock(scaling_toggle_button, signals_id[scaling_signal]);
}

static void init_folder_to_save(GtkBuilder *builder) {
    GtkFileChooser *save_image_gif_folder_chooser = (GtkFileChooser *) gtk_builder_get_object(builder, "Save_image_folder_chooser_button");
    gtk_file_chooser_set_filename(save_image_gif_folder_chooser, INITIAL_FOLDER_TO_SAVE);
}

status_t apply_initial_settings(GPtrArray *data) {
    GtkBuilder *builder = data->pdata[0];
    gulong *signals_id = data->pdata[3];

    init_input_mode_buttons(builder, signals_id);
    init_work_mode_buttons(builder, signals_id);

    init_folder_to_save(builder);
}
