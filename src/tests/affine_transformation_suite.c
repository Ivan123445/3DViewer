#include "tests.h"


START_TEST(move_test) {
    obj_data_t data;

    status_t result_code =
            parse_file("../src/tests/test_files/ten_points_five_surface.obj", &data);
    ck_assert_int_eq(result_code, OK);

    for (int num_points = 0; num_points < 9; ++num_points) {
        ck_assert_double_eq(data.points[num_points].x, num_points+1);
        ck_assert_double_eq(data.points[num_points].y, num_points+1);
        ck_assert_double_eq(data.points[num_points].z, num_points+1);
    }

    coordinates_t move_offset = {-1, -1, -1};
    move(&data, move_offset);

    for (int num_points = 0; num_points < 9; ++num_points) {
        ck_assert_double_eq(data.points[num_points].x, num_points);
        ck_assert_double_eq(data.points[num_points].y, num_points);
        ck_assert_double_eq(data.points[num_points].z, num_points);
    }

}
END_TEST

START_TEST(scale_test) {
    obj_data_t data;

    status_t result_code =
            parse_file("../src/tests/test_files/ten_points_five_surface.obj", &data);
    ck_assert_int_eq(result_code, OK);

    coordinates_t scale_offset = {0, 0, 0};
    scale(&data,  scale_offset);

    for (int num_points = 0; num_points < 9; ++num_points) {
        ck_assert_double_eq(data.points[num_points].x, num_points+1);
        ck_assert_double_eq(data.points[num_points].y, num_points+1);
        ck_assert_double_eq(data.points[num_points].z, num_points+1);
    }

    scale_offset.x = 2;
    scale_offset.y = 2;
    scale_offset.z = 2;
    scale(&data,  scale_offset);

    for (int num_points = 0; num_points < 10; ++num_points) {
        ck_assert_double_eq(data.points[num_points].x, (num_points+1)*2);
        ck_assert_double_eq(data.points[num_points].y, (num_points+1)*2);
        ck_assert_double_eq(data.points[num_points].z, (num_points+1)*2);
    }

}
END_TEST

START_TEST(rotate_test) {
    obj_data_t data;
    data.count_points = 1;

    data.points = (coordinates_t *)calloc(1, sizeof(coordinates_t));
    ck_assert_ptr_nonnull(data.points);
    data.points[0].x = 1;
    data.points[0].y = 0;
    data.points[0].z = 0;
    coordinates_t angles = {45, 0, 0};
    rotate(&data, angles);

    ck_assert_double_eq_tol(data.points[0].x, 1, ACCURACY);
    ck_assert_double_eq_tol(data.points[0].y, 0, ACCURACY);
    ck_assert_double_eq_tol(data.points[0].z, 0, ACCURACY);

    angles.x = 0;
    angles.y = 45;
    rotate(&data, angles);

    ck_assert_double_eq_tol(data.points[0].x, sqrt(2) / 2, ACCURACY);
    ck_assert_double_eq_tol(data.points[0].y, 0, ACCURACY);
    ck_assert_double_eq_tol(data.points[0].z, -sqrt(2) / 2, ACCURACY);

    free(data.points);
}
END_TEST

Suite* affine_transformation_suite() {
    Suite* s = suite_create("affine_transformation_suite");

    TCase* affine_transformations_cases =
            tcase_create("affine_transformation_cases");

    suite_add_tcase(s, affine_transformations_cases);

    tcase_add_test(affine_transformations_cases, move_test);
    tcase_add_test(affine_transformations_cases, scale_test);
    tcase_add_test(affine_transformations_cases, rotate_test);

    return s;
}