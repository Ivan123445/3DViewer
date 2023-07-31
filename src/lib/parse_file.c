#include "../s21_3dviewer.h"

static status_t get_col_points_and_surfaces(gchar *filename, int *col_point, int *col_surfaces) {
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

static int get_col_points_in_surface(gchar *str) {
    int i = 0;
    gchar *nstr = str++;
    for (; strtod(str, &nstr) != 0 && str != nstr; ++i) {
        str = nstr;
    }
    return i;
}

static status_t alloc_data(points_t *points, surfaces_t *surfaces) {
    status_t status = OK;
    points->points = NULL;
    surfaces->surfaces = NULL;

    points->points = calloc(points->count_points, sizeof(point_t));
    if (!points->points) {
        status = ALLOC_ERR;
    } else {
        surfaces->surfaces = calloc(surfaces->count_surfaces, sizeof(points_t));
        if (!surfaces->surfaces) {
            free(points->points);
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

static status_t scan_point(gchar *str, point_t *point) {
    status_t status = OK;
    if (sscanf(str, "v %lf %lf %lf", &point->x, &point->y, &point->z) != 3) {
        status = FORMAT_FILE_ERR;
    }
    return status;
}

static status_t get_points (gchar *filename, points_t *points) {
    status_t status = OK;
    FILE *file = fopen(filename, "r");
    if (!file) {
        status = OPEN_FILE_ERR;
    }

    if(status == OK) {
        gchar *str = NULL;
        size_t n = 0;
        for (size_t i = 0; status == OK && getline(&str, &n, file) != -1; ) {
            if (str[0] == 'v') {
                replace_symb(str, '.', ',');
                status = scan_point(str, &points->points[i]);
                ++i;
            }
        }
        free(str);
    }
    fclose(file);
    return status;
}

static status_t get_surfaces (gchar *filename, points_t points, surfaces_t *surfaces) {
    status_t status = OK;
    FILE *file = fopen(filename, "r");
    if (!file) {
        status = OPEN_FILE_ERR;
    }

    if (status == OK) {
        gchar *str = NULL;
        size_t n = 0;
        for (int surf_num = 0; surf_num < surfaces->count_surfaces && getline(&str, &n, file) != -1; ++surf_num) {
            if (str[0] == 'f') {
                surfaces->surfaces[surf_num].count_points = get_col_points_in_surface(str);
                surfaces->surfaces[surf_num].points = calloc(surfaces->surfaces[surf_num].count_points, sizeof(points_t));
                if (!surfaces->surfaces[surf_num].points ) {
                    status = ALLOC_ERR;
                }

                int surf_point_num = 0;
                ++str;  // skip 'f'
                gchar *nstr = str;
                for (int point_num = 0; (point_num = (int)strtod(nstr, &str)) != -1 && str != nstr; ++point_num) {
                    nstr = str;
                    point_num--;  // since the numbering of points is from 1
                    surfaces->surfaces[surf_num].points[surf_point_num].x = points.points[point_num].x;
                    surfaces->surfaces[surf_num].points[surf_point_num].y = points.points[point_num].y;
                    surfaces->surfaces[surf_num].points[surf_point_num].z = points.points[point_num].z;
                }
            }
        }
    }

    return status;
}

status_t parse_file(gchar *filename, surfaces_t *surfaces) {
    points_t points;
    status_t status = get_col_points_and_surfaces(filename, &points.count_points, &surfaces->count_surfaces);

    if (status == OK) {
        status = alloc_data(&points, surfaces);
    }
    if (status == OK) {
        status = get_points(filename, &points);
    }
    if (status == OK) {
        status = get_surfaces(filename, points, surfaces);
        free(points.points);
    }

    return status;
}
