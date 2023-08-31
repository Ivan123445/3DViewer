#include "../../s21_3dviewer.h"

static char *generate_filename(gchar *recording_folder, char *filename) {
    size_t recording_file_len;
    time_t now;
    struct tm *local;
    time(&now);
    local = localtime(&now);

    recording_file_len = strlen(recording_folder) + strlen(SAVE_IMAGE_NAME) + 10;  // 8 for date

    char *recording_file = calloc(recording_file_len + 1, sizeof(char));

    sprintf(recording_file, "%s/%s%d_%d_%d", recording_folder, filename, local->tm_hour, local->tm_min, local->tm_sec);
    return recording_file;
}

void save_image(GtkWidget *button, GtkWidget *folder_chooser) {
    gchar *recording_folder = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(folder_chooser));
    char *recording_file = generate_filename(recording_folder, SAVE_IMAGE_NAME);
    printf("%s\n", recording_file);
    char buf;
    int src_file = open(RENDERED_IMAGE_FILE, O_RDONLY);
    if (src_file != -1) {

         int receive_file = open(recording_file,
                      O_WRONLY | O_CREAT,
                      S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        while(read(src_file, &buf, 1)) {
            write(receive_file, &buf, 1);
        }
        close(receive_file);
    }
    free(recording_folder);
    free(recording_file);
    close(src_file);
}
