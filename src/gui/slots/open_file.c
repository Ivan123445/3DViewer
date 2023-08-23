#include "../../s21_3dviewer.h"

static gchar * get_filename_position(gchar *file_path) {
    gchar *filename = file_path;
    for (; *file_path != '\0'; ++file_path) {
        if (*file_path == '/') {
            filename = file_path;
        }
    }
    return ++filename;
}

void open_file(GtkWidget *chooser, GPtrArray *data) {
    GtkBuilder *builder = data->pdata[0];
    obj_data_t *obj_data = data->pdata[1];

    GtkLabel *file_name_label = (GtkLabel *)gtk_builder_get_object(builder, "File_name_label");
    GtkWidget *axis_buttons_grid = (GtkWidget *) gtk_builder_get_object(builder, "Control_visibility_grid");
    GtkImage *image = (GtkImage *)gtk_builder_get_object(builder, "Model_image");

    free_obj_data(obj_data);
    char *file_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser));
    if (parse_file(file_path, obj_data) == OK) {
        gtk_widget_set_sensitive(axis_buttons_grid, TRUE);
        gtk_label_set_label(file_name_label, get_filename_position(file_path));
        render(image, obj_data);
    } else {
        gtk_widget_set_sensitive(axis_buttons_grid, FALSE);
        gtk_image_set_from_file(image, ERROR_IMAGE);
        gtk_label_set_label(file_name_label, MODEL_FILE_FORMAT_ERR_MSG);
    }
}