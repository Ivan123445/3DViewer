#ifndef INC_3DVIEWER_S21_3DVIEWER_H
#define INC_3DVIEWER_S21_3DVIEWER_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <math.h>

// UI
#define GLADE_FILE "../src/gui/3dviewer.glade"
#define CSS_FILE   "../src/gui/common.css"

// Render
#define RENDER_FILE "/home/ivan/School/3DViewer/src/$render_data.txt"
#define IMAGE_FILE "/home/ivan/School/3DViewer/src/$graph.png"
#define GNUPLOT_SCRIPT "set output '%s'\n         \
  set terminal pngcairo size %d,%d\n    \
  set decimalsign locale\n              \
  set xyplane at 0\n                    \
  set view equal xyz\n                  \
  unset border\n                        \
  set xlabel \"X\"\n                    \
  set ylabel \"Y\"\n                    \
  set zlabel \"Z\"\n                    \
  set pm3d depth\n                      \
  set pm3d border lc \"black\" lw 1.5\n \
  splot '%s' notitle with polygons fs transparent solid 0.8 fc \"gray75\"\n"

#define INITIAL_WORK_MODE moving
#define OFFSET_IN_ONE_CLICK 1

// MESSAGES
#define FILE_OPENING_ERR_MSG "Не удалось открыть файл: "
#define FORMAT_FILE_ERR_MSG  "Ошибка формата файла"

typedef enum status {
    OK,
    OPEN_FILE_ERR,
    FORMAT_FILE_ERR,
    ALLOC_ERR,
    OPEN_RENDER_FILE_ERR,
    PIPE_OPEN_ERR,
    WRONG_BUTTON_ERR,
    ZERO_SCALING_ERR
} status_t;

typedef enum work_mode {
    moving,
    rotation,
    scaling,
    block
} work_mode_t;

typedef struct coordinates {
    float x;
    float y;
    float z;
} coordinates_t;

typedef struct surface {
    unsigned short count_points;
    unsigned short *points;
} surface_t;

typedef struct obj_data {
    unsigned int count_points;
    coordinates_t *points;
    unsigned int count_surfaces;
    surface_t *surfaces;
} obj_data_t;

// gui
void open_file(GtkWidget *chooser, GPtrArray *data);
void change_work_mode(GtkWidget *toggle_button, GPtrArray *data);
void change_display(GtkWidget *button, GPtrArray *data);

// lib
status_t parse_file(gchar *filename, obj_data_t *obj_data);
status_t render_obj(GtkImage *image, obj_data_t *obj_data);

void move(obj_data_t *data, coordinates_t coord);
void scale(obj_data_t *data, coordinates_t coord);
status_t rotate(obj_data_t *data, coordinates_t coord);

#endif //INC_3DVIEWER_S21_3DVIEWER_H
