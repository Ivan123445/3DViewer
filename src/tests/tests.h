#ifndef INC_3DVIEWER_TESTS_H
#define INC_3DVIEWER_TESTS_H

#include <check.h>

#include "../s21_3dviewer.h"

#define ACCURACY 1e-6

Suite *affine_transformation_suite();
Suite *parse_file_suite();

#endif //INC_3DVIEWER_TESTS_H
