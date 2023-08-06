#include "../s21_3dviewer.h"

#define RADIANS_TO_DEGREE(val) ((val) * M_PI / 180)

void move(obj_data_t *data, coordinates_t coord) {
    for (int i = 0; i < data->count_points; i++) {
        data->points[i].x += coord.x;
        data->points[i].y += coord.y;
        data->points[i].z += coord.z;
    }
}

void scale(obj_data_t *data, coordinates_t coord) {
    coord.x = 1 + coord.x/10;
    coord.y = 1 + coord.y/10;
    coord.z = 1 + coord.z/10;

    for (int i = 0; i < data->count_points; i++) {
            data->points[i].x *= coord.x;
            data->points[i].y *= coord.y;
            data->points[i].z *= coord.z;
        }
}

static void rotate_x(coordinates_t *coord, double angle) {
    angle = RADIANS_TO_DEGREE(angle);
    float z = coord->z, x = coord->x;
    coord->x = x * cos(angle) + z * sin(angle);
    coord->z = -x * sin(angle) + z * cos(angle);
}

static void rotate_y(coordinates_t *coord, double angle) {
    angle = RADIANS_TO_DEGREE(angle);
    float z = coord->z, y = coord->y;
    coord->y = y * cos(angle) + z * sin(angle);
    coord->z = -y * sin(angle) + z * cos(angle);
}

static void rotate_z(coordinates_t *coord, double angle) {
    angle = RADIANS_TO_DEGREE(angle);
    float x = coord->x, y = coord->y;
    coord->x = x * cos(angle) + y * sin(angle);
    coord->y = -x * sin(angle) + y * cos(angle);
}

status_t rotate(obj_data_t *data, coordinates_t coord) {
    coord.x = coord.x*2;
    coord.y = coord.y*2;
    coord.z = coord.z*2;

    for (int i = 0; i < data->count_points; i++) {
        rotate_x(&data->points[i], coord.x);
        rotate_y(&data->points[i], coord.y);
        rotate_z(&data->points[i], coord.z);
    }
}


