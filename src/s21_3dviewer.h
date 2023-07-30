#ifndef INC_3DVIEWER_S21_3DVIEWER_H
#define INC_3DVIEWER_S21_3DVIEWER_H

#include <gtk/gtk.h>
#include <stdlib.h>

// UI
#define GLADE_FILE "../src/gui/3dviewer.glade"
#define CSS_FILE   "../src/gui/common.css"

// MESSAGES
#define ERR_FILE_OPENING "Не удалось открыть файл"

typedef enum status {
    OK,

} status_t;

typedef enum work_mode {
    moving,
    rotation,
    scaling
} work_mode_t;

typedef struct coord {
    int x;
    int y;
    int z;
} coord_t;

typedef struct points {
    int col_points;
    coord_t *points;
} points_t;

typedef struct surfaces {
    int col_surfaces;
    points_t *surfaces;
} surfaces_t;

// gui_utils
void open_file(GtkFileChooser *chooser, GPtrArray *data);

// lib
status_t parse_file(gchar *filename, surfaces_t *surfaces);

#endif //INC_3DVIEWER_S21_3DVIEWER_H
