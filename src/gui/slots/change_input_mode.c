#include "../../s21_3dviewer.h"

void change_input_mode(GtkWidget *toggle_button, GPtrArray *data) {
    GtkBuilder *builder = data->pdata[0];
    gulong *signals_id = data->pdata[3];

    GtkToggleButton *controller_toggle_button = (GtkToggleButton *)gtk_builder_get_object(builder, "Controller_mode_button");
    GtkToggleButton *coordinates_toggle_button = (GtkToggleButton *)gtk_builder_get_object(builder, "Coordinates_mode_button");
    GtkWidget *buttons_input_grid = (GtkWidget *) gtk_builder_get_object(builder, "Buttons_input_grid");
    GtkWidget *entry_input_grid = (GtkWidget *) gtk_builder_get_object(builder, "Entry_input_grid");

    g_signal_handler_block(controller_toggle_button, signals_id[controller_signal]);
    g_signal_handler_block(coordinates_toggle_button, signals_id[coordinates_signal]);

    const gchar *toggle_button_name = gtk_widget_get_name(toggle_button);
    if (!strcmp(toggle_button_name, "Controller_mode_button")) {
        gtk_toggle_button_set_active(controller_toggle_button, TRUE);
        gtk_toggle_button_set_active(coordinates_toggle_button, FALSE);

        gtk_widget_set_visible(buttons_input_grid, TRUE);
        gtk_widget_set_visible(entry_input_grid, FALSE);
    } else if (!strcmp(toggle_button_name, "Coordinates_mode_button")) {
        gtk_toggle_button_set_active(controller_toggle_button, FALSE);
        gtk_toggle_button_set_active(coordinates_toggle_button, TRUE);

        gtk_widget_set_visible(buttons_input_grid, FALSE);
        gtk_widget_set_visible(entry_input_grid, TRUE);
    }

    g_signal_handler_unblock(controller_toggle_button, signals_id[controller_signal]);
    g_signal_handler_unblock(coordinates_toggle_button, signals_id[coordinates_signal]);


}
