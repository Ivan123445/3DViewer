#include "../s21_3dviewer.h"

void change_work_mode(GtkWidget *toggle_button, GPtrArray *data) {
    GtkBuilder *builder = data->pdata[0];
    display_change_mode_t *work_mode = data->pdata[2];
    gulong *signals_id_work_mode_button = data->pdata[3];

    GtkToggleButton *moving_toggle_button = (GtkToggleButton *)gtk_builder_get_object(builder, "Moving_toggle_button");
    GtkToggleButton *rotation_toggle_button = (GtkToggleButton *) gtk_builder_get_object(builder, "Rotation_toggle_button");
    GtkToggleButton *scaling_toggle_button = (GtkToggleButton *) gtk_builder_get_object(builder, "Scaling_toggle_button");

    g_signal_handler_block(moving_toggle_button, signals_id_work_mode_button[moving_signal]);
    g_signal_handler_block(rotation_toggle_button, signals_id_work_mode_button[rotation_signal]);
    g_signal_handler_block(scaling_toggle_button, signals_id_work_mode_button[scaling_signal]);

    const gchar *toggle_button_name = gtk_widget_get_name(toggle_button);
    if (!strcmp(toggle_button_name, "Moving_toggle_button")) {
        *work_mode = moving_mode;
    } else if (!strcmp(toggle_button_name, "Rotation_toggle_button")) {
        *work_mode = rotation_mode;
    } else if (!strcmp(toggle_button_name, "Scaling_toggle_button")) {
        *work_mode = scaling_mode;
    }

    gtk_toggle_button_set_active(moving_toggle_button, *work_mode == moving_mode);
    gtk_toggle_button_set_active(rotation_toggle_button, *work_mode == rotation_mode);
    gtk_toggle_button_set_active(scaling_toggle_button, *work_mode == scaling_mode);

    g_signal_handler_unblock(moving_toggle_button, signals_id_work_mode_button[moving_signal]);
    g_signal_handler_unblock(rotation_toggle_button, signals_id_work_mode_button[rotation_signal]);
    g_signal_handler_unblock(scaling_toggle_button, signals_id_work_mode_button[scaling_signal]);
}
