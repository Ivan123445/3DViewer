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
    apply_multiplier(&coord, SCALE_MULTIPLIER);
    for (int i = 0; i < data->count_points; i++) {
            data->points[i].x *= coord.x + 1;
            data->points[i].y *= coord.y + 1;
            data->points[i].z *= coord.z + 1;
        }
}

static void rotate_x(coordinates_t *coord, double angle) {
    angle = RADIANS_TO_DEGREE(angle);
    coord->x = (float)(coord->x * cos(angle) + coord->z * sin(angle));
    coord->z = (float)(-coord->x * sin(angle) + coord->z * cos(angle));
}

static void rotate_y(coordinates_t *coord, double angle) {
    angle = RADIANS_TO_DEGREE(angle);
    coord->y = (float)(coord->y * cos(angle) + coord->z * sin(angle));
    coord->z = (float)(-coord->y * sin(angle) + coord->z * cos(angle));
}

static void rotate_z(coordinates_t *coord, double angle) {
    angle = RADIANS_TO_DEGREE(angle);
    coord->x = (float)(coord->x * cos(angle) + coord->y * sin(angle));
    coord->y = (float)(-coord->x * sin(angle) + coord->y * cos(angle));
}

status_t rotate(obj_data_t *data, coordinates_t coord) {
    apply_multiplier(&coord, ROTATING_MULTIPLIER);

    for (int i = 0; i < data->count_points; i++) {
        rotate_x(&data->points[i], coord.x);
        rotate_y(&data->points[i], coord.y);
        rotate_z(&data->points[i], coord.z);
    }
}


