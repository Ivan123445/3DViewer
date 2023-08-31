#include "../../s21_3dviewer.h"

void *record_gif(void *data) {
    GPtrArray *dataarr = data;
    GtkWidget *save_gif_button = dataarr->pdata[0];
    char *gif_filename = dataarr->pdata[1];
    char second_label[3];
    gtk_widget_set_sensitive(GTK_WIDGET(save_gif_button), FALSE);
    MagickWandGenesis();
    MagickWand * wand;
    wand = NewMagickWand();
    for (int seconds = SECONDS_IN_GIF; seconds > 0; --seconds) {
        sprintf(second_label, "%d", seconds);
        gtk_button_set_label(GTK_BUTTON(save_gif_button), second_label);

        MagickReadImage(wand, RENDERED_IMAGE_FILE);

        sleep(1);
    }

    MagickWriteImages(wand, gif_filename, MagickTrue);
    MagickWandTerminus();
    gtk_button_set_label(GTK_BUTTON(save_gif_button), "Save gif\0");
    gtk_widget_set_sensitive(GTK_WIDGET(save_gif_button), TRUE);

    pthread_exit(NULL);
}

void create_gif(GtkWidget *button, GtkWidget *folder_chooser) {
    GPtrArray *data = g_ptr_array_new();
    g_ptr_array_add(data, button);

    gchar *recording_folder = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(folder_chooser));
    char *recording_file = generate_filepath(recording_folder, SAVE_GIF_NAME);
    g_ptr_array_add(data, recording_file);

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, record_gif, data);
    pthread_detach(thread_id);
}
