#include "../../s21_3dviewer.h"

void save_image(GtkWidget *button, GtkWidget *folder_chooser) {
    gchar *recording_folder = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(folder_chooser));
    char *image_filepath = generate_filepath(recording_folder, SAVE_IMAGE_NAME, FALSE);

    int src_file = open(RENDERED_IMAGE_FILE, O_RDONLY);
    if (src_file != -1) {

         int receive_file = open(image_filepath,
                      O_WRONLY | O_CREAT,
                      S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        char buf;
        while(read(src_file, &buf, 1)) {
            write(receive_file, &buf, 1);
        }
        close(receive_file);
    }
    free(recording_folder);
    free(image_filepath);
    close(src_file);
}
