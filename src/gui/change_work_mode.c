#include "../s21_3dviewer.h"

void change_work_mode(GtkWidget *toggle_button, GPtrArray *data) {  // TODO remake
    GtkBuilder *builder = data->pdata[0];
    work_mode_t *work_mode = data->pdata[2];
    if(*work_mode == block) {  // mutexes for weaklings
        return;
    }
    *work_mode = block;
    GtkToggleButton *moving_toggle_button = (GtkToggleButton *)gtk_builder_get_object(builder, "Moving_toggle_button");
    GtkToggleButton *rotation_toggle_button = (GtkToggleButton *) gtk_builder_get_object(builder, "Rotation_toggle_button");
    GtkToggleButton *scaling_toggle_button = (GtkToggleButton *) gtk_builder_get_object(builder, "Scaling_toggle_button");

    const gchar *toggle_button_name = gtk_widget_get_name(toggle_button);
    if (!strcmp(toggle_button_name, "Moving_toggle_button")) {
        gtk_toggle_button_set_active(moving_toggle_button, TRUE);
        gtk_toggle_button_set_active(rotation_toggle_button, FALSE);
        gtk_toggle_button_set_active(scaling_toggle_button, FALSE);
        *work_mode = moving;
    } else if (!strcmp(toggle_button_name, "Rotation_toggle_button")) {
        gtk_toggle_button_set_active(moving_toggle_button, FALSE);
        gtk_toggle_button_set_active(rotation_toggle_button, TRUE);
        gtk_toggle_button_set_active(scaling_toggle_button, FALSE);
        *work_mode = rotation;
    } else if (!strcmp(toggle_button_name, "Scaling_toggle_button")) {
        gtk_toggle_button_set_active(moving_toggle_button, FALSE);
        gtk_toggle_button_set_active(rotation_toggle_button, FALSE);
        gtk_toggle_button_set_active(scaling_toggle_button, TRUE);
        *work_mode = scaling;
    }
}
