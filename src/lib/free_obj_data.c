#include "../s21_3dviewer.h"

void free_obj_data(obj_data_t *obj_data) {
  if (obj_data) {
    for (int i = 0; i < obj_data->count_surfaces; ++i) {
      free(obj_data->surfaces[i].points);
      obj_data->surfaces[i].points = NULL;
    }
    if (obj_data->points) {
      free(obj_data->points);
      obj_data->points = NULL;
    }
    if (obj_data->surfaces) {
      free(obj_data->surfaces);
      obj_data->surfaces = NULL;
    }
    obj_data->count_points = 0;
    obj_data->count_surfaces = 0;
  }
}
