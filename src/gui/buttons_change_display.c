#include "../s21_3dviewer.h"

static void apply_multiplier(coordinates_t *coord, double multiplier) {
    coord->x = coord->x*multiplier;
    coord->y = coord->y*multiplier;
    coord->z = coord->z*multiplier;
}

void buttons_change_display(GtkWidget *button, GPtrArray *data) {
    status_t status = OK;
    GtkBuilder *builder = data->pdata[0];
    obj_data_t *obj_data = data->pdata[1];
    display_change_mode_t *work_mode = data->pdata[2];
    GtkImage *image = (GtkImage *) gtk_builder_get_object(builder, "Model_image");

    coordinates_t offset = {0, 0, 0};

    const gchar *button_name = gtk_widget_get_name(button);
    if (!strcmp(button_name, "Up_button")) {
        offset.y += AXIS_BUTTONS_OFFSET;
    } else if (!strcmp(button_name, "Down_button")) {
        offset.y -= AXIS_BUTTONS_OFFSET;
    } else if (!strcmp(button_name, "Right_button")) {
        offset.x += AXIS_BUTTONS_OFFSET;
    } else if (!strcmp(button_name, "Left_button")) {
        offset.x -= AXIS_BUTTONS_OFFSET;
    } else if (!strcmp(button_name, "Z_up_button")) {
        offset.z += AXIS_BUTTONS_OFFSET;
    } else if (!strcmp(button_name, "Z_down_button")) {
        offset.z -= AXIS_BUTTONS_OFFSET;
    } else if (!strcmp(button_name, "Plus_scale_button")) {
        obj_data->scale -= obj_data->scale > 1 ? SCALE_OFFSET : 0;
    } else if (!strcmp(button_name, "Minus_scale_button")) {
        obj_data->scale += SCALE_OFFSET;
    } else {
        status = WRONG_BUTTON_ERR;
    }

    if (status == OK) {
        switch (*work_mode) {
            case moving_mode:
                apply_multiplier(&offset, MOVING_MULTIPLIER);
                move(obj_data, offset);
                break;
            case rotation_mode:
                apply_multiplier(&offset, ROTATING_MULTIPLIER);
                rotate(obj_data, offset);
                break;
            case scaling_mode:
                apply_multiplier(&offset, SCALE_MULTIPLIER);
                scale(obj_data, offset);
        }
    }

    if (status == OK) {
        render(image, obj_data);
    }

}

