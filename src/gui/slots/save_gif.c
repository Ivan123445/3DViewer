#include "../../s21_3dviewer.h"

int record_gif(void *data) {
    GPtrArray *gdata = data;
    GtkWidget *save_gif_button = gdata->pdata[0];
    char *gif_filepath = gdata->pdata[1];
    static int seconds = SECONDS_IN_GIF;
    static MagickWand * wand;

    if (seconds == SECONDS_IN_GIF) {
        gtk_widget_set_sensitive(GTK_WIDGET(save_gif_button), FALSE);
        wand = NewMagickWand();
        MagickWandGenesis();
    }

    char seconds_str[2];
    sprintf(seconds_str, "%d", seconds);
    gtk_button_set_label(GTK_BUTTON(save_gif_button), seconds_str);

    MagickReadImage(wand, RENDERED_IMAGE_FILE);
    seconds--;
    if (seconds == -1) {
        printf("%s\n", gif_filepath);
        MagickWriteImages(wand, gif_filepath, MagickTrue);
        MagickWandTerminus();
        gtk_button_set_label(GTK_BUTTON(save_gif_button), "Save gif\0");
        gtk_widget_set_sensitive(GTK_WIDGET(save_gif_button), TRUE);
        free(gif_filepath);
        seconds = SECONDS_IN_GIF;
        return G_SOURCE_REMOVE;
    }
    return G_SOURCE_CONTINUE;
}

void save_gif(GtkWidget *button, GtkWidget *folder_chooser) {
    GPtrArray *data = g_ptr_array_new();
    g_ptr_array_add(data, button);

    gchar *recording_folder = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(folder_chooser));
    char *gif_filepath = generate_filepath(recording_folder, SAVE_GIF_NAME, TRUE);
    g_ptr_array_add(data, gif_filepath);

    g_timeout_add_seconds(1, record_gif, data);
}
