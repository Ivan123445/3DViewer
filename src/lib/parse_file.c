#include "../s21_3dviewer.h"

static status_t get_col_points_and_surfaces(gchar *filename, unsigned int *col_point, unsigned int *col_surfaces) {
    status_t status = OK;
    *col_point = 0;
    *col_surfaces = 0;
    FILE *file = fopen(filename, "r");
    if(!file) {
        status = OPEN_FILE_ERR;
    }

    char *str = NULL;
    size_t n = 0;
    while (status == OK && getline(&str, &n, file) != -1) {
        switch (str[0]) {
            case 'v':
                ++*col_point;
                break;
            case 'f':
                ++*col_surfaces;
                break;
            case '#':
                break;
            default:
                status = FORMAT_FILE_ERR;
        }
    }

    free(str);
    fclose(file);
    return status;
}

static status_t alloc_data(obj_data_t *obj_data) {
    status_t status = OK;
    obj_data->points = NULL;
    obj_data->surfaces = NULL;

    obj_data->points = calloc(obj_data->count_points, sizeof(coordinates_t));
    if (!obj_data->points) {
        status = ALLOC_ERR;
    } else {
        obj_data->surfaces = calloc(obj_data->count_surfaces, sizeof(surface_t));
        if (!obj_data->surfaces) {
            free(obj_data->points);
            status = ALLOC_ERR;
        }
    }
    return status;
}

static void replace_symb(gchar *str, gchar replaceable, gchar replacing) {
    for (int i = 0; str[i] != '\n'; ++i) {
        str[i] == replaceable ? str[i] = replacing : 0;
    }
}

static status_t scan_point(gchar *str, coordinates_t *point) {
    status_t status = OK;
    if (sscanf(str, "v %f %f %f\n", &point->x, &point->y, &point->z) != 3) {
        status = FORMAT_FILE_ERR;
    }
    return status;
}

static status_t scan_surface(gchar *str, surface_t *surface) {
    status_t status = OK;
    gchar *start_str = str++;
    gchar *nstr = str++;
    for (; strtod(str, &nstr) != 0 && str != nstr; ++surface->count_points) {
        str = nstr;
    }
    str = ++start_str;

    surface->points = calloc(surface->count_points, sizeof(unsigned short));
    for (int point_num = 0; point_num < surface->count_points; ++point_num) {
        surface->points[point_num] = (unsigned short)strtod(str, &str) - 1;  // since the numbering is from 1
    }
    if (surface->count_points == 0) {
        status = FORMAT_FILE_ERR;
    }
    return status;
}

static status_t get_obj_data (gchar *filename, obj_data_t *obj_data) {
    status_t status = OK;
    FILE *file = fopen(filename, "r");
    if (!file) {
        status = OPEN_FILE_ERR;
    }

    if (status == OK) {
        gchar *str = NULL;
        size_t n = 0;
        for (int point_num = 0, surface_num = 0; status == OK && getline(&str, &n, file) != -1;) {
            if (str[0] == 'v') {
                replace_symb(str, '.', ',');
                status = scan_point(str, &obj_data->points[point_num]);
                point_num++;
            } else if (str[0] == 'f') {
                status = scan_surface(str, &obj_data->surfaces[surface_num]);
                surface_num++;
            }
        }
    }

    return status;
}

status_t parse_file(gchar *filename,  obj_data_t *obj_data) {
    status_t status = get_col_points_and_surfaces(filename, &obj_data->count_points, &obj_data->count_surfaces);

    if (status == OK) {
        status = alloc_data(obj_data);
    }
    if (status == OK) {
        status = get_obj_data(filename, obj_data);
    }

    return status;
}
