#include "../s21_3dviewer.h"

void open_file(GtkFileChooser *chooser, GPtrArray *data) {
    GtkBuilder *builder = data->pdata[0];
    obj_data_t *obj_data = data->pdata[1];

    GtkLabel *file_name_label = (GtkLabel *)gtk_builder_get_object(builder, "File_name_label");
    GtkWidget *move_grid = (GtkWidget *) gtk_builder_get_object(builder, "Move_grid");

    char *file_name = gtk_file_chooser_get_preview_filename(chooser);
    if (parse_file(file_name, obj_data) == OK) {
        gtk_widget_set_sensitive(move_grid, TRUE);
        gtk_label_set_label(file_name_label, file_name);  // TODO output filename without path
        render(obj_data);
    } else {
        g_print(FORMAT_FILE_ERR_MSG"\n");
    }
}