#ifndef INC_3DVIEWER_S21_3DVIEWER_H
#define INC_3DVIEWER_S21_3DVIEWER_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <wand/MagickWand.h>

// UI
#define GLADE_FILE "../src/gui/3dviewer.glade"
#define CSS_FILE   "../src/gui/common.css"
#define ICON_FILE  "../misc/icon.png"

// Render
#define DATA_FOR_RENDER_FILE    "/tmp/$render_data.txt"
#define RENDERED_IMAGE_FILE     "/tmp/$graph.png"
#define ERROR_IMAGE             "../misc/error_image.png"
#define GNUPLOT_SCRIPT \
  "set output '%s'\n                   \
  set terminal pngcairo size %d,%d\n    \
  set decimalsign locale\n              \
  set xlabel \"X\"\n                    \
  set ylabel \"Y\"\n                    \
  set zlabel \"Z\"\n                    \
  set pm3d border lc \"black\" lw 0.3\n \
  splot [-%d:%d][-%d:%d][-%d:%d] '%s' notitle with polygons fs transparent solid 0.8 fc \"gray\"\n"

// Control visibility
#define INITIAL_WORK_MODE   moving_mode
#define INITIAL_INPUT_MODE  1  // 1 - controller, 2 - coordinates
#define INITIAL_GRAPH_SCALE 10
#define GRAPH_SCALE_STEP    1
#define AXIS_BUTTONS_STEP   1
#define MOVE_MULTIPLIER     1
#define SCALE_MULTIPLIER    0.1
#define ROTATE_MULTIPLIER   4

// Additional settings
#define INITIAL_FOLDER_TO_SAVE "../misc/"
#define SAVE_IMAGE_NAME        "3DV_image_"  // a date is added to the end
#define SAVE_GIF_NAME          "3DV_gif_"   // a date is added to the end

#define SECONDS_IN_GIF         3

// Messages
#define OPEN_GLADE_FILE_ERR_MSG       "Unable to load glade file:"
#define OPEN_CSS_FILE_ERR_MSG         "Unable to load css file:"
#define GETTING_WINDOW_WIDGET_ERR_MSG "Error getting the window widget"
#define MODEL_FILE_FORMAT_ERR_MSG     "Model file format error"

typedef enum status {
    OK,
    OPEN_FILE_ERR,
    FORMAT_FILE_ERR,
    ALLOC_ERR,
    OPEN_RENDER_FILE_ERR,
    PIPE_OPEN_ERR,
    WRONG_BUTTON_ERR
} status_t;

typedef enum work_mode {
    moving_mode,
    rotation_mode,
    scaling_mode
} work_mode_t;

typedef enum signals_id_indexes {
  moving_signal,
  rotation_signal,
  scaling_signal,
  controller_signal,
  coordinates_signal
} signals_id_indexes_t;

typedef struct coordinates {
    double x;
    double y;
    double z;
} coordinates_t;

typedef struct surface {
    unsigned short count_points;
    unsigned short *points;
} surface_t;

typedef struct obj_data {
    unsigned short graph_scale;
    unsigned int count_points;
    coordinates_t *points;
    unsigned int count_surfaces;
    surface_t *surfaces;
} obj_data_t;

// gui/slots
void buttons_change_display(GtkWidget *button, GPtrArray *data);
void change_input_mode(GtkWidget *toggle_button, GPtrArray *data);
void change_work_mode(GtkWidget *toggle_button, GPtrArray *data);
gboolean close_app(GtkWidget* window, GPtrArray *data);
void create_gif(GtkWidget *button, GtkWidget *folder_chooser);
void entrys_change_display(GtkWidget *button, GPtrArray *data);
status_t apply_initial_settings(GPtrArray *data);
void open_file(GtkWidget *chooser, GPtrArray *data);
void save_image(GtkWidget *button, GtkWidget *folder_chooser);
GPtrArray *signals_connect(GtkBuilder *builder);

// lib
void free_obj_data(obj_data_t *obj_data);
char *generate_filepath(gchar *folder, char *filename);
status_t parse_file(gchar *filename, obj_data_t *obj_data);
status_t render(GtkImage *image, obj_data_t *obj_data);

void move(obj_data_t *data, coordinates_t coord);
void scale(obj_data_t *data, coordinates_t coord);
status_t rotate(obj_data_t *data, coordinates_t coord);

#endif //INC_3DVIEWER_S21_3DVIEWER_H
