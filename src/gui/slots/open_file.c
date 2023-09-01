#include "../../s21_3dviewer.h"

static gchar *get_filename_position(gchar *file_path) {
    gchar *filename = file_path;
    for (; *file_path != '\0'; ++file_path) {
        if (*file_path == '/') {
            filename = file_path;
        }
    }
    return ++filename;
}

static gchar *get_file_characteristics(obj_data_t *obj_data) {
    gchar *characteristics = NULL;
    int len = 0;
    for (size_t i = obj_data->count_points; i > 0; i /= 10, len++);
    for (size_t i = obj_data->count_surfaces; i > 0 ; i /=10, len++);

    characteristics = calloc(20 + len, sizeof(char));
    sprintf(characteristics, "Points:%d  Surfaces:%d", obj_data->count_points, obj_data->count_surfaces);
    return characteristics;
}

void open_file(GtkWidget *chooser, GPtrArray *data) {
    GtkBuilder *builder = data->pdata[0];
    obj_data_t *obj_data = data->pdata[1];

    GtkLabel *file_name_label = (GtkLabel *)gtk_builder_get_object(builder, "File_name_label");
    GtkLabel *file_characteristics_label = (GtkLabel *)gtk_builder_get_object(builder, "File_characteristics_label");
    GtkFileChooser *obj_file_chooser = (GtkFileChooser *) gtk_builder_get_object(builder, "File_chooser_widget");
    GtkWidget *control_visibility_grid = (GtkWidget *) gtk_builder_get_object(builder, "Control_visibility_grid");
    GtkWidget *additional_settings_grid = (GtkWidget *) gtk_builder_get_object(builder, "Additional_settings_grid");
    GtkImage *image = (GtkImage *)gtk_builder_get_object(builder, "Model_image");

    free_obj_data(obj_data);
    char *file_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser));
    char *characteristics = NULL;
    if (parse_file(file_path, obj_data) == OK) {
        gtk_widget_set_sensitive(control_visibility_grid, TRUE);
        gtk_widget_set_sensitive(additional_settings_grid, TRUE);

        gtk_label_set_label(file_name_label, get_filename_position(file_path));
        characteristics = get_file_characteristics(obj_data);
        gtk_label_set_label(file_characteristics_label, characteristics);
        gtk_file_chooser_set_current_folder(obj_file_chooser, INITIAL_FOLDER_TO_OBJ);
        free(characteristics);
        render(image, obj_data);
    } else {
        gtk_widget_set_sensitive(control_visibility_grid, FALSE);
        gtk_widget_set_sensitive(additional_settings_grid, FALSE);
        gtk_image_set_from_file(image, ERROR_IMAGE);
        gtk_label_set_label(file_name_label, MODEL_FILE_FORMAT_ERR_MSG);
    }
}