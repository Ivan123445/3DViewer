#include "../s21_3dviewer.h"

G_MODULE_EXPORT GtkWidget *show_file_window(
        GtkButton *button, GtkWidget *file_window) {
    gtk_widget_show(file_window);

    return file_window;
}

G_MODULE_EXPORT GtkWidget *hide_file_window(
        GtkWidget *button, GtkWidget *file_window) {
    gtk_widget_hide(file_window);  // TODO throws an warning

    return file_window;
}

static void signals_connect(GtkBuilder *builder) {
    GPtrArray *data = g_ptr_array_new();
    obj_data_t *obj_data = calloc(1, sizeof(obj_data_t));
    gulong *signals_id = calloc(5, sizeof (gulong));
    display_change_mode_t *display_change_mode = calloc(1, sizeof(display_change_mode));
    *display_change_mode = INITIAL_WORK_MODE;
    g_ptr_array_add(data, builder);
    g_ptr_array_add(data, obj_data);
    g_ptr_array_add(data, display_change_mode);
    g_ptr_array_add(data, signals_id);  // to temporarily disable the signals in change_work_mode


    gtk_builder_connect_signals(builder, NULL);  // auto connect some signals

    GtkWindow *window = (GtkWindow *) gtk_builder_get_object(builder, "Main_window");
    g_signal_connect(window, "delete-event", G_CALLBACK(close_app), data);

    GtkFileChooser *chooser = (GtkFileChooser *)gtk_builder_get_object(builder, "File_chooser_widget");
    g_signal_connect(chooser, "file_activated", G_CALLBACK(open_file), data);
    g_signal_connect(chooser, "file_activated", G_CALLBACK(hide_file_window), data);


    GtkToggleButton *moving_toggle_button = (GtkToggleButton *)gtk_builder_get_object(builder, "Moving_toggle_button");
    GtkToggleButton *rotation_toggle_button = (GtkToggleButton *)gtk_builder_get_object(builder, "Rotation_toggle_button");
    GtkToggleButton *scaling_toggle_button = (GtkToggleButton *)gtk_builder_get_object(builder, "Scaling_toggle_button");
    signals_id[moving_signal] = g_signal_connect(moving_toggle_button, "clicked", G_CALLBACK(change_work_mode), data);
    signals_id[rotation_signal] = g_signal_connect(rotation_toggle_button, "clicked", G_CALLBACK(change_work_mode), data);
    signals_id[scaling_signal] = g_signal_connect(scaling_toggle_button, "clicked", G_CALLBACK(change_work_mode), data);

    GtkButton *up_button = (GtkButton *)gtk_builder_get_object(builder, "Up_button");
    GtkButton *down_button = (GtkButton *)gtk_builder_get_object(builder, "Down_button");
    GtkButton *left_button = (GtkButton *)gtk_builder_get_object(builder, "Left_button");
    GtkButton *right_button = (GtkButton *)gtk_builder_get_object(builder, "Right_button");
    GtkButton *z_up_button = (GtkButton *)gtk_builder_get_object(builder, "Z_up_button");
    GtkButton *z_down_button = (GtkButton *)gtk_builder_get_object(builder, "Z_down_button");
    g_signal_connect(up_button, "clicked", G_CALLBACK(buttons_change_display), data);
    g_signal_connect(down_button, "clicked", G_CALLBACK(buttons_change_display), data);
    g_signal_connect(left_button, "clicked", G_CALLBACK(buttons_change_display), data);
    g_signal_connect(right_button, "clicked", G_CALLBACK(buttons_change_display), data);
    g_signal_connect(z_up_button, "clicked", G_CALLBACK(buttons_change_display), data);
    g_signal_connect(z_down_button, "clicked", G_CALLBACK(buttons_change_display), data);

    GtkButton *plus_scale_button = (GtkButton *)gtk_builder_get_object(builder, "Plus_scale_button");
    GtkButton *minus_scale_button = (GtkButton *)gtk_builder_get_object(builder, "Minus_scale_button");
    g_signal_connect(plus_scale_button, "clicked", G_CALLBACK(buttons_change_display), data);
    g_signal_connect(minus_scale_button, "clicked", G_CALLBACK(buttons_change_display), data);


    GtkButton *render_button = (GtkButton *) gtk_builder_get_object(builder, "Render_button");
    g_signal_connect(render_button, "clicked", G_CALLBACK(entrys_change_display), data);

    GtkToggleButton *controller_button = (GtkToggleButton *) gtk_builder_get_object(builder, "Controller_mode_button");
    GtkToggleButton *coordinates_button = (GtkToggleButton *) gtk_builder_get_object(builder, "Coordinates_mode_button");
    signals_id[controller_signal] = g_signal_connect(controller_button, "clicked", G_CALLBACK(change_input_mode), data);
    signals_id[coordinates_signal] = g_signal_connect(coordinates_button, "clicked", G_CALLBACK(change_input_mode), data);
}

static GtkWidget *create_main_window() {
    GtkWidget *window;
    GtkBuilder *builder;
    GError *error = NULL;

    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(builder, GLADE_FILE, &error)) {
        g_critical(OPEN_GLADE_FILE_ERR_MSG "%s", error->message);
        g_error_free(error);
    }
    signals_connect(builder);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "Main_window"));
    if (!window) {
        g_critical(GETTING_WINDOW_WIDGET_ERR_MSG);
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
        g_critical(OPEN_CSS_FILE_ERR_MSG "%s", error->message);
    } else {
        gtk_style_context_add_provider_for_screen(
                gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider),
                GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    }

    gtk_widget_show(window);

    gtk_main();

    return 0;
}