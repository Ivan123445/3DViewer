#include "../s21_3dviewer.h"

G_MODULE_EXPORT GtkWidget *create_open_file_window(
        GtkButton *button, GtkWidget *open_file_window) {
    gtk_widget_show(open_file_window);

    return open_file_window;
}

static void signals_connect(GtkBuilder *builder) {
    GPtrArray *data = g_ptr_array_new();
    obj_data_t *obj_data = calloc(1, sizeof(obj_data_t));
//    work_mode_t *work_mode = NULL;
    g_ptr_array_add(data, builder);
    g_ptr_array_add(data, obj_data);
//    g_ptr_array_add(data, work_mode);

    gtk_builder_connect_signals(builder, NULL);  // auto connect some signals

    GtkFileChooser *chooser = (GtkFileChooser *)gtk_builder_get_object(builder, "File_chooser_widget");
    g_signal_connect(chooser, "file_activated", G_CALLBACK(open_file), data);

}

static GtkWidget *create_main_window() {
    GtkWidget *window;
    GtkBuilder *builder;
    GError *error = NULL;

    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(builder, GLADE_FILE, &error)) {
        g_critical("Не могу загрузить файл: %s", error->message);
        g_error_free(error);
    }
    signals_connect(builder);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "Main"));
    if (!window) {
        g_critical("Ошибка при получении виджета окна");
    }
//    g_object_unref(builder);

    return window;
}

int main (int argc, char *argv[]) {
    GtkWidget *window;
    GtkCssProvider *provider = gtk_css_provider_new();
    GError *error;

    gtk_init(&argc, &argv);

    window = create_main_window();
    if (!gtk_css_provider_load_from_path(provider, CSS_FILE, &error)) {
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