#include "../s21_3dviewer.h"

static GtkWidget *create_main_window() {
    GtkWidget *window;
    GtkBuilder *builder;
    GError *error = NULL;

    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(builder, "../src/gui/3dviewer.glade", &error)) {
        g_critical("Не могу загрузить файл: %s", error->message);
        g_error_free(error);
    }
    gtk_builder_connect_signals(builder, NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "Main"));
    if (!window) {
        g_critical("Ошибка при получении виджета окна");
    }
    g_object_unref(builder);

    return window;
}

G_MODULE_EXPORT GtkWidget *create_open_file_window(
        GtkButton *button, GtkWidget *open_file_window) {
    gtk_widget_show(open_file_window);

    return open_file_window;
}

G_MODULE_EXPORT void change_to_scaling_mode (GtkButton *button) {
    g_print("Here\n");
}

G_MODULE_EXPORT void open_file(GtkFileChooser *chooser, GtkLabel *files_name_label) {
    char *files_name = gtk_file_chooser_get_preview_filename(chooser);
    FILE *file = fopen(files_name, "r");
    printf("%s\n", files_name);
    if(!file) {
        printf(ERR_FILE_OPENING"\n");
        gtk_label_set_label(files_name_label, ERR_FILE_OPENING);
    } else {
        gtk_label_set_label(files_name_label, files_name);

    }

    printf("Here\n");
    fscanf(file, "%s\n", files_name);


    fclose(file);
}

int main (int argc, char *argv[]) {
    GtkWidget *window;
    GtkCssProvider *provider = gtk_css_provider_new();
    GError *error;

    gtk_init(&argc, &argv);

    window = create_main_window();
    if (!gtk_css_provider_load_from_path(provider, "../src/gui/common.css", &error)) {
        g_critical("Ошибка загрузки css стилей: %s", error->message);
    } else {
        gtk_style_context_add_provider_for_screen(
                gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider),
                GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    }

    gtk_widget_show(window);

    gtk_main();

    return 0;
}