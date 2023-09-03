#include "../s21_3dviewer.h"

G_MODULE_EXPORT GtkWidget *show_file_window(GtkButton *button,
                                            GtkWidget *file_window) {
  gtk_widget_show(file_window);

  return file_window;
}

G_MODULE_EXPORT GtkWidget *hide_file_window(GtkWidget *button,
                                            GtkWidget *file_window) {
  gtk_widget_hide_on_delete(file_window);

  return file_window;
}

static GtkWidget *create_main_window() {
  GtkWidget *window;
  GtkBuilder *builder;
  GPtrArray *data;
  GError *error = NULL;

  builder = gtk_builder_new();
  if (!gtk_builder_add_from_file(builder, GLADE_FILE, &error)) {
    g_critical(OPEN_GLADE_FILE_ERR_MSG "%s", error->message);
    g_error_free(error);
  }
  data = signals_connect(builder);
  apply_initial_settings(data);

  window = GTK_WIDGET(gtk_builder_get_object(builder, "Main_window"));
  if (!window) {
    g_critical(GETTING_WINDOW_WIDGET_ERR_MSG);
  }

  return window;
}

int main(int argc, char *argv[]) {
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
  //    gtk_window_set_icon_from_file (GTK_WINDOW(window), ICON_FILE, NULL);

  gtk_widget_show(window);

  gtk_main();

  return 0;
}