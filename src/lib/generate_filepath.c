#include "../s21_3dviewer.h"

char *generate_filepath(gchar *recording_folder, char *filename,
                        gboolean is_gif) {
  char str_date[9];
  time_t now;
  time(&now);
  struct tm *local = localtime(&now);

  sprintf(str_date, "_%d%d%d", local->tm_hour, local->tm_min, local->tm_sec);

  size_t recording_file_len =
      strlen(recording_folder) + strlen(filename) + strlen(str_date);
  char *recording_file = calloc(recording_file_len + 1, sizeof(char));

  sprintf(recording_file, "%s/%s%s", recording_folder, filename, str_date);

  if (is_gif) {
    strcat(recording_file, ".gif");
  } else {
    strcat(recording_file, ".png");
  }
  return recording_file;
}
