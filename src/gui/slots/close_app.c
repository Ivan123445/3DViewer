#include "../../s21_3dviewer.h"

gboolean close_app(GtkWidget* window, GPtrArray *data) {
    obj_data_t *obj_data = data->pdata[1];
    display_change_mode_t *display_change_mode = data->pdata[2];
    gulong *signals_id = data->pdata[3];

    free_obj_data(obj_data);
    free(obj_data);
    free(display_change_mode);
    free(signals_id);

    free(data);
    return FALSE;
}
