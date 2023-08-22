#include "../s21_3dviewer.h"

#define RADIANS_TO_DEGREE(val) ((val) * M_PI / 180)

static void apply_multiplier(coordinates_t *coord, float multiplier) {
    coord->x = coord->x*multiplier;
    coord->y = coord->y*multiplier;
    coord->z = coord->z*multiplier;
}

void move(obj_data_t *data, coordinates_t coord) {
    apply_multiplier(&coord, MOVING_MULTIPLIER);
    for (int i = 0; i < data->count_points; i++) {
        data->points[i].x += coord.x;
        data->points[i].y += coord.y;
        data->points[i].z += coord.z;
    }
}

void scale(obj_data_t *data, coordinates_t coord) {
    coord.x = coord.x ? coord.x : 1;  // if there is no offset, we leave the coordinates unchanged
    coord.y = coord.y ? coord.y : 1;
    coord.z = coord.z ? coord.z : 1;
    for (int i = 0; i < data->count_points; i++) {
        data->points[i].x *= coord.x;
        data->points[i].y *= coord.y;
        data->points[i].z *= coord.z;
    }
}

static void rotate_x(coordinates_t *coord, double angle) {
    double z = coord->z, y = coord->y;
    coord->y = y * cos(angle) + z * sin(angle);
    coord->z = -y * sin(angle) + z * cos(angle);
}

static void rotate_y(coordinates_t *coord, double angle) {
    double z = coord->z, x = coord->x;
    coord->x = x * cos(angle) + z * sin(angle);
    coord->z = -x * sin(angle) + z * cos(angle);
}

static void rotate_z(coordinates_t *coord, double angle) {
    double y = coord->y, x = coord->x;
    coord->x = x * cos(angle) + y * sin(angle);
    coord->y = -x * sin(angle) + y * cos(angle);
}

status_t rotate(obj_data_t *data, coordinates_t coord) {
    coord.x = DEGREE_TO_RADIANS(coord.x);
    coord.y = DEGREE_TO_RADIANS(coord.y);
    coord.z = DEGREE_TO_RADIANS(coord.z);
    for (int i = 0; i < data->count_points; i++) {
        coord.x ? rotate_x(&data->points[i], coord.x) : 0;
        coord.y ? rotate_y(&data->points[i], coord.y) : 0;
        coord.z ? rotate_z(&data->points[i], coord.z) : 0;
    }
}


