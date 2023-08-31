#include "../s21_3dviewer.h"

char *generate_filepath(gchar *recording_folder, char *filename) {
    size_t recording_file_len;
    time_t now;
    struct tm *local;
    time(&now);
    local = localtime(&now);

    recording_file_len = strlen(recording_folder) + strlen(SAVE_IMAGE_NAME) + 10;  // 8 for date

    char *recording_file = calloc(recording_file_len + 1, sizeof(char));

    sprintf(recording_file, "%s/%s%d_%d_%d.gif", recording_folder, filename, local->tm_hour, local->tm_min, local->tm_sec);
    return recording_file;
}
