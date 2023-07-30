#include "../s21_3dviewer.h"

void open_file(GtkFileChooser *chooser, GPtrArray *data) {
    GtkBuilder *builder = data->pdata[0];
    surfaces_t *surfaces = data->pdata[1];

    GtkLabel *file_name_label = (GtkLabel *)gtk_builder_get_object(builder, "File_name_label");
    GtkWidget *move_grid = (GtkWidget *) gtk_builder_get_object(builder, "Move_grid");

    char *file_name = gtk_file_chooser_get_preview_filename(chooser);
    if (parse_file(file_name, surfaces) == OK) {
        gtk_label_set_label(file_name_label, file_name);  // TODO output filename without path
        gtk_widget_set_sensitive(move_grid, TRUE);
    }
}

//void
