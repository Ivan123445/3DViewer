#include "../s21_3dviewer.h"

G_MODULE_EXPORT GtkWidget *create_open_file_window(
        GtkButton *button, GtkWidget *open_file_window) {
    gtk_widget_show(open_file_window);

    return open_file_window;
}

static void signals_connect(GtkBuilder *builder) {
    GPtrArray *data = g_ptr_array_new();
    obj_data_t *obj_data = calloc(1, sizeof(obj_data_t));
    work_mode_t *work_mode = calloc(1, sizeof(work_mode));
    *work_mode = INITIAL_WORK_MODE;
    g_ptr_array_add(data, builder);
    g_ptr_array_add(data, obj_data);
    g_ptr_array_add(data, work_mode);

    gtk_builder_connect_signals(builder, NULL);  // auto connect some signals

    GtkFileChooser *chooser = (GtkFileChooser *)gtk_builder_get_object(builder, "File_chooser_widget");
    g_signal_connect(chooser, "file_activated", G_CALLBACK(open_file), data);

    GtkToggleButton *moving_toggle_button = (GtkToggleButton *)gtk_builder_get_object(builder, "Moving_toggle_button");
    GtkToggleButton *rotation_toggle_button = (GtkToggleButton *)gtk_builder_get_object(builder, "Rotation_toggle_button");
    GtkToggleButton *scaling_toggle_button = (GtkToggleButton *)gtk_builder_get_object(builder, "Scaling_toggle_button");
    g_signal_connect(moving_toggle_button, "clicked", G_CALLBACK(change_work_mode), data);
    g_signal_connect(rotation_toggle_button, "clicked", G_CALLBACK(change_work_mode), data);
    g_signal_connect(scaling_toggle_button, "clicked", G_CALLBACK(change_work_mode), data);


    GtkButton *up_button = (GtkButton *)gtk_builder_get_object(builder, "Up_button");
    GtkButton *down_button = (GtkButton *)gtk_builder_get_object(builder, "Down_button");
    GtkButton *left_button = (GtkButton *)gtk_builder_get_object(builder, "Left_button");
    GtkButton *right_button = (GtkButton *)gtk_builder_get_object(builder, "Right_button");
    GtkButton *z_up_button = (GtkButton *)gtk_builder_get_object(builder, "Z_up_button");
    GtkButton *z_down_button = (GtkButton *)gtk_builder_get_object(builder, "Z_down_button");
    g_signal_connect(up_button, "clicked", G_CALLBACK(change_display), data);
    g_signal_connect(down_button, "clicked", G_CALLBACK(change_display), data);
    g_signal_connect(left_button, "clicked", G_CALLBACK(change_display), data);
    g_signal_connect(right_button, "clicked", G_CALLBACK(change_display), data);
    g_signal_connect(z_up_button, "clicked", G_CALLBACK(change_display), data);
    g_signal_connect(z_down_button, "clicked", G_CALLBACK(change_display), data);

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