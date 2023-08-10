#include "../s21_3dviewer.h"

void buttons_change_display(GtkWidget *button, GPtrArray *data) {
    status_t status = OK;
    GtkBuilder *builder = data->pdata[0];
    obj_data_t *obj_data = data->pdata[1];
    work_mode_t *work_mode = data->pdata[2];
    GtkImage *image = (GtkImage *) gtk_builder_get_object(builder, "Model_image");

    coordinates_t offset = {0, 0, 0};

    const gchar *button_name = gtk_widget_get_name(button);
    if (!strcmp(button_name, "Up_button")) {
        offset.y += OFFSET_IN_ONE_CLICK;
    } else if (!strcmp(button_name, "Down_button")) {
        offset.y -= OFFSET_IN_ONE_CLICK;
    } else if (!strcmp(button_name, "Right_button")) {
        offset.x += OFFSET_IN_ONE_CLICK;
    } else if (!strcmp(button_name, "Left_button")) {
        offset.x -= OFFSET_IN_ONE_CLICK;
    } else if (!strcmp(button_name, "Z_up_button")) {
        offset.z += OFFSET_IN_ONE_CLICK;
    } else if (!strcmp(button_name, "Z_down_button")) {
        offset.z -= OFFSET_IN_ONE_CLICK;
    } else {
        status = WRONG_BUTTON_ERR;
    }

    if (status == OK) {
        switch (*work_mode) {
            case moving_mode:
                move(obj_data, offset);
                break;
            case rotation_mode:
                rotate(obj_data, offset);
                break;
            case scaling_mode:
                scale(obj_data, offset);
                break;
        }
    }

    if (status == OK) {
        render_obj(image, obj_data);
    }

}

