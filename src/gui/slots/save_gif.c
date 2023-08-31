#include "../../s21_3dviewer.h"

void *record_gif(void *data) {
    GPtrArray *gdata = data;
    GtkWidget *save_gif_button = gdata->pdata[0];
    char *gif_filepath = gdata->pdata[1];
    gtk_widget_set_sensitive(GTK_WIDGET(save_gif_button), FALSE);
    MagickWandGenesis();
    MagickWand * wand;
    wand = NewMagickWand();
    char seconds_str[3];
    for (int seconds = SECONDS_IN_GIF; seconds > 0; --seconds) {
        sprintf(seconds_str, "%d", seconds);
        gtk_button_set_label(GTK_BUTTON(save_gif_button), seconds_str);

        MagickReadImage(wand, RENDERED_IMAGE_FILE);

        sleep(1);
    }

    MagickWriteImages(wand, gif_filepath, MagickTrue);
    MagickWandTerminus();
    gtk_button_set_label(GTK_BUTTON(save_gif_button), "Save gif\0");
    gtk_widget_set_sensitive(GTK_WIDGET(save_gif_button), TRUE);

    free(gif_filepath);
    pthread_exit(NULL);
}

void save_gif(GtkWidget *button, GtkWidget *folder_chooser) {
    GPtrArray *data = g_ptr_array_new();
    g_ptr_array_add(data, button);

    gchar *recording_folder = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(folder_chooser));
    char *recording_file = generate_filepath(recording_folder, SAVE_GIF_NAME, TRUE);
    g_ptr_array_add(data, recording_file);

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, record_gif, data);
    pthread_detach(thread_id);
}
