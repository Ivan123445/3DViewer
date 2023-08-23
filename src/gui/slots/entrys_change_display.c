#include "../../s21_3dviewer.h"

void entrys_change_display(GtkWidget *button, GPtrArray *data) {
    GtkBuilder *builder = data->pdata[0];
    obj_data_t *obj_data = data->pdata[1];
    display_change_mode_t *work_mode = data->pdata[2];
    GtkImage *image = (GtkImage *) gtk_builder_get_object(builder, "Model_image");

    GtkEntry *x_offset_entry = (GtkEntry *) gtk_builder_get_object(builder, "X_offset_entry");
    GtkEntry *y_offset_entry = (GtkEntry *) gtk_builder_get_object(builder, "Y_offset_entry");
    GtkEntry *z_offset_entry = (GtkEntry *) gtk_builder_get_object(builder, "Z_offset_entry");

    coordinates_t offset = {0, 0, 0};
    offset.x = strtof(gtk_entry_get_text(x_offset_entry), NULL);
    offset.y = strtof(gtk_entry_get_text(y_offset_entry), NULL);
    offset.z = strtof(gtk_entry_get_text(z_offset_entry), NULL);

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

    render(image, obj_data);

}

