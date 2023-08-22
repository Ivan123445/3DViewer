#include "../s21_3dviewer.h"

gboolean close_app(GtkWidget* window, GPtrArray *data) {  // TODO
    free(data);
    return FALSE;
}
