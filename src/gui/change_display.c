#include "../s21_3dviewer.h"

void change_display(GtkWidget *button, GPtrArray *data) {
    status_t status = OK;
    GtkBuilder *builder = data->pdata[0];
    obj_data_t *obj_data = data->pdata[1];
    work_mode_t *work_mode = data->pdata[2];
    GtkImage *image = (GtkImage *) gtk_builder_get_object(builder, "Model_image");

    coordinates_t coord = { 0, 0, 0};

    const gchar *button_name = gtk_widget_get_name(button);
    if (!strcmp(button_name, "Up_button")) {
        coord.y += OFFSET_IN_ONE_CLICK;
    } else if (!strcmp(button_name, "Down_button")) {
        coord.y -= OFFSET_IN_ONE_CLICK;
    } else if (!strcmp(button_name, "Right_button")) {
        coord.x += OFFSET_IN_ONE_CLICK;
    } else if (!strcmp(button_name, "Left_button")) {
        coord.x -= OFFSET_IN_ONE_CLICK;
    } else if (!strcmp(button_name, "Z_up_button")) {
        coord.z += OFFSET_IN_ONE_CLICK;
    } else if (!strcmp(button_name, "Z_down_button")) {
        coord.z -= OFFSET_IN_ONE_CLICK;
    } else {
        status = WRONG_BUTTON_ERR;
    }

    if (status == OK) {
        switch (*work_mode) {
            case moving:
                move(obj_data, coord);
                break;
            case rotation:
                rotate(obj_data, coord);
                break;
            case scaling:
                scale(obj_data, coord);
                break;
        }
    }

    if (status == OK) {
        render_obj(image, obj_data);
    }

}

