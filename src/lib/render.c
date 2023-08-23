#include "../s21_3dviewer.h"

static status_t write_obj_data_to_file(gchar *filename, obj_data_t *obj_data) {
    status_t status = OK;
    FILE *file = fopen(filename, "w");
    if (!file) {
        status = OPEN_RENDER_FILE_ERR;
    }

    if (status == OK) {
        for (int surface_num = 0; surface_num < obj_data->count_surfaces; ++surface_num) {
            for (int point_num = 0; point_num < obj_data->surfaces->count_points; ++point_num) {
                fprintf(file, "%f %f %f\n",
                        obj_data->points[obj_data->surfaces[surface_num].points[point_num]].x,
                        obj_data->points[obj_data->surfaces[surface_num].points[point_num]].y,
                        obj_data->points[obj_data->surfaces[surface_num].points[point_num]].z
                );
            }
            fprintf(file, "\n");
        }
    }

    fclose(file);
    return status;
}

static status_t call_gnuplot(unsigned short width, unsigned short height, unsigned short scale) {
    status_t status = OK;
    FILE *pipe_gnuplot = popen("/usr/bin/gnuplot", "w");
    if (!pipe_gnuplot) {
        status = PIPE_OPEN_ERR;
    }

    fprintf(pipe_gnuplot, GNUPLOT_SCRIPT, IMAGE_FILE, width, height,
            scale, scale, scale, scale, scale, scale,  // set graph_scale for each axis
            RENDER_FILE);

    pclose(pipe_gnuplot);
    return status;
}

static status_t set_image(GtkImage *image) {
    gtk_image_set_from_file(image, IMAGE_FILE);
}

status_t render(GtkImage *image, obj_data_t *obj_data) {
    status_t status = write_obj_data_to_file(RENDER_FILE, obj_data);

    if (status == OK) {
        GtkWidget *image_widget = (GtkWidget *)image;
        status = call_gnuplot(gtk_widget_get_allocated_width(image_widget), gtk_widget_get_allocated_height(image_widget),
                                obj_data->graph_scale);
    }

    if (status == OK) {
        set_image(image);
    }

    return OK;
}
