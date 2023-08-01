#ifndef INC_3DVIEWER_S21_3DVIEWER_H
#define INC_3DVIEWER_S21_3DVIEWER_H

#include <gtk/gtk.h>
#include <stdlib.h>

// UI
#define GLADE_FILE "../src/gui/3dviewer.glade"
#define CSS_FILE   "../src/gui/common.css"

// MESSAGES
#define FILE_OPENING_ERR_MSG "Не удалось открыть файл: "
#define FORMAT_FILE_ERR_MSG  "Ошибка формата файла"

typedef enum status {
    OK,
    OPEN_FILE_ERR,
    FORMAT_FILE_ERR,
    ALLOC_ERR
} status_t;

typedef enum work_mode {
    moving,
    rotation,
    scaling
} work_mode_t;

typedef struct point {
    float x;
    float y;
    float z;
} point_t;

typedef struct surface {
    unsigned short count_points;
    unsigned short *points;
} surface_t;

typedef struct obj_data {
    unsigned int count_points;
    point_t *points;
    unsigned int count_surfaces;
    surface_t *surfaces;
} obj_data_t;

// gui_utils
void open_file(GtkFileChooser *chooser, GPtrArray *data);

// lib
status_t parse_file(gchar *filename, obj_data_t *obj_data);
status_t render(obj_data_t *obj_data);

#endif //INC_3DVIEWER_S21_3DVIEWER_H
